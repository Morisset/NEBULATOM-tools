/* This file is part of Cloudy and is copyright (C)1978-2010 by Gary J. Ferland and
 * others.  For conditions of distribution and use see copyright notice in license.txt */
/*dense_fabden called by dlaw command, returns density for any density law */
#include "cddefines.h"
#include "rfield.h"
#include "dense.h"
#include "physconst.h"
#include "phycon.h"
#include "geometry.h" 

/*dense_fabden called by dlaw command, returns density for any density law */
double dense_fabden(double radius, 
  double depth)
{
	double fabden_v;
	double fluc;
	double var1;
	double R_shell;
#	ifdef DEBUG_FUN
	fputs( "<+>fabden()\n", debug_fp );
#	endif

	/* this routine is called when the DLAW command is given,
	 * and must return the hydrogen density at the current radius or depth
	 * RADIUS is the radius, the distance from the center of symmetry.
	 * DEPTH is the depth into the cloud, from the illuminated face
	 * both are in cm
	 *
	 * radius, depth, and the array DensityLaw are double precision, although
	 * FABDEN itself is not
	 *
	 * this is one way to generate a density
	 * fabden = radius * depth
	 *
	 * this is how to use the parameters on the dlaw command
	 * fabden = DensityLaw(1) + radius * DensityLaw(2)
	 *
	 * following must be removed if this sub is to be used */
	fabden_v = 0.0;
	 /*    fprintf(ioQQQ,"TTT %.2f\n",fabden_v);*/

	if( depth > radius )
		TotalInsanity();


	switch((int)(dense.DensityLaw[0]))
	  {
	  case 0:
	    /* dens = P1 */
	    fabden_v = dense.DensityLaw[1];
	    break;
	  case 1:
	    /* dens = P1 * exp(-(Depth/P2)^2) */
	    fabden_v = dense.DensityLaw[1]*
	      exp(-(pow(depth/pow(10.,dense.DensityLaw[2]),2.)));
	    break;
	  case 2:
	    /* dens = 10^P1 * exp((R*sin(P2)-P3)/P4) */
	    fabden_v = pow(10.,dense.DensityLaw[1])*
	      exp((radius*sin(dense.DensityLaw[2])-pow(10.,dense.DensityLaw[3]))/
		  pow(10.,dense.DensityLaw[4]));
	    break;
	  case 21:
	    /* dens = 10^P1 * MIN[exp((R*sin(P2)-P3)/P4),1.0] */
	    fabden_v = pow(10.,dense.DensityLaw[1])*
	      MIN2(exp((radius*sin(dense.DensityLaw[2])-pow(10.,dense.DensityLaw[3]))/
		  pow(10.,dense.DensityLaw[4])),1.0);
	    break;
          case 22:
            fabden_v = MAX2(pow(10.,dense.DensityLaw[1])*
              MIN2(exp((radius*sin(dense.DensityLaw[2])-pow(10.,dense.DensityLaw[3]))/
                  pow(10.,dense.DensityLaw[4])),1.0),pow(10.,dense.DensityLaw[5]));
            break;
          case 320:
            /* dens = A1+(A2-A1)*exp(-(r/A3)^A4)   */
            fabden_v = dense.DensityLaw[1]+(dense.DensityLaw[2]-dense.DensityLaw[1])*
              exp(-(pow((radius/3.0856780e+18/dense.DensityLaw[3]),dense.DensityLaw[4])));
            break;
	  case 3:
	    /* dens = P1 + P2*exp(-((depth-P3)/P4)^2) + P5*exp(-((depth-P6)/P7)^2   */
	    fabden_v = dense.DensityLaw[1]+dense.DensityLaw[2]*
	      exp(-(pow((depth-pow(10.,dense.DensityLaw[3]))/pow(10.,dense.DensityLaw[4]),2.)))+
	      dense.DensityLaw[5]*
	      exp(-(pow((depth-pow(10.,dense.DensityLaw[6]))/pow(10.,dense.DensityLaw[7]),2.)));
	    break;
          case 311:
            /* dens = P1 + P2*exp(-((depth-P3)/P4)^2) + P5*exp(-((depth-P6)/P7)^2   */
            fabden_v = dense.DensityLaw[1]+dense.DensityLaw[2]*
              exp(-(pow((radius-pow(10.,dense.DensityLaw[3]))/pow(10.,dense.DensityLaw[4]),2)))+
              dense.DensityLaw[5]*
              exp(-(pow((radius-pow(10.,dense.DensityLaw[6]))/pow(10.,dense.DensityLaw[7]),2)));
            if( radius >  pow(10.,dense.DensityLaw[8]))
              fabden_v = pow(10.,dense.DensityLaw[9])/pow(phycon.te/1e4,1.2) ;
            break;
	  case 31:
	    /* dens = P1 + P2*exp(-((depth-P3)/P4)^2) + P5*exp(-((depth-P6)/P7)^2   */
	    /* if depth LT P3 then dens = dens + P8 */
	    fabden_v = dense.DensityLaw[1]+dense.DensityLaw[2]*
	      exp(-(pow((depth-pow(10.,dense.DensityLaw[3]))/pow(10.,dense.DensityLaw[4]),2.)))+
	      dense.DensityLaw[5]*
	      exp(-(pow((depth-pow(10.,dense.DensityLaw[6]))/pow(10.,dense.DensityLaw[7]),2.)));
	    if (depth < pow(10.,dense.DensityLaw[3])) fabden_v = fabden_v + dense.DensityLaw[8];
	    break;
	  case 33:
	    /* fluc = 1/(1+exp(10*sin(depth/P8)+P9))*/
	    /* dens = P1/4.+fluc*(P1+P2*exp(-((depth-P3)/P4)^2.) + P5*exp(-((depth-P6)/P7)^2.))   */
	    fabden_v = dense.DensityLaw[1]+dense.DensityLaw[2]*
	      exp(-(pow((depth-pow(10.,dense.DensityLaw[3]))/pow(10.,dense.DensityLaw[4]),2.)))+
	      dense.DensityLaw[5]*
	      exp(-(pow((depth-pow(10.,dense.DensityLaw[6]))/pow(10.,dense.DensityLaw[7]),2.)));
	    fluc = 1./(1.+exp(10.*sin(depth/pow(10.,dense.DensityLaw[8]))+dense.DensityLaw[9]));
	    fabden_v = dense.DensityLaw[1]/4. + fabden_v * fluc;
	    break;
	  case 34:
	    /* fluc = 1/(1+exp(P3*sin(depth/P4)+P5))*/
	    /* dens = P1/2.+fluc*(P1*2.+P2*6.3*exp(-((depth-P2.)/P2.)^2.) + P2*1000.*exp(-((depth-P2.)/P2.)^2.))   */
	    fabden_v = dense.DensityLaw[1]*2.0+dense.DensityLaw[1]*6.3*
	      exp(-(pow((depth-pow(10.,dense.DensityLaw[2]+0.2))/pow(10.,dense.DensityLaw[2]+0.05),2.)))+
	      dense.DensityLaw[1]*10.*
	      exp(-(pow((depth-pow(10.,dense.DensityLaw[2]+1.))/pow(10.,dense.DensityLaw[2]+0.55),2.)));
	    fluc = 1./(1.+exp(dense.DensityLaw[3]*sin(depth/pow(10.,dense.DensityLaw[4])+dense.DensityLaw[7])
			      +dense.DensityLaw[5]));
	    fabden_v = dense.DensityLaw[6] + fabden_v * fluc;
	    break;
	  case 35:
	    /* fluc = 1/(1+exp(P3*sin(depth/P4+P6)+P5))*/
	    /* dens = P1*fluc + P2   */
	    fabden_v = dense.DensityLaw[1];
	    fluc = 1./(1.+exp(dense.DensityLaw[3]*sin(depth/pow(10.,dense.DensityLaw[4])+dense.DensityLaw[6])
			      +dense.DensityLaw[5]));
	    fabden_v = dense.DensityLaw[2] + fabden_v * fluc;
	    break;
          case 36:
            /* dens = P1 + P2*exp(-((depth-P3)/P4)^2) + P5*exp(-((depth-P6)/P7)^2   */
            fabden_v = dense.DensityLaw[1]+dense.DensityLaw[2]*
              exp(-(pow((depth-pow(10.,dense.DensityLaw[3]))/pow(10.,dense.DensityLaw[4]),2.)))+
              dense.DensityLaw[5]*
              exp(-(pow((depth-pow(10.,dense.DensityLaw[6]))/pow(10.,dense.DensityLaw[7]),2.)));
            if( depth >  pow(10.,dense.DensityLaw[8]))
              fabden_v = dense.DensityLaw[9];
            break;
          case 39:
            /* dens = P1 + P2*exp(-((depth-P3)/P4)^2) + P5*exp(-((depth-P6)/P7)^2   */
            fabden_v = dense.DensityLaw[1]+dense.DensityLaw[2]*
              exp(-(pow((depth-pow(10.,dense.DensityLaw[3]))/pow(10.,dense.DensityLaw[4]),2.)))+
              dense.DensityLaw[5]*
              exp(-(pow((depth-pow(10.,dense.DensityLaw[6]))/pow(10.,dense.DensityLaw[7]),2.)));
            if( depth >  pow(10.,dense.DensityLaw[8]))
              fabden_v = dense.DensityLaw[9]/pow(phycon.te/1e4,1.2) ;
            break;
          case 393:
            /* dens = P1 + P2*exp(-((depth-P3)/P4)^2) + P5*exp(-((depth-P6)/P7)^2   */
            fabden_v = 2850.+7317*
              exp(-(pow((depth-pow(10.,16.14))/pow(10.,15.96),2.)))+
              11702*
              exp(-(pow((depth-pow(10.,16.93))/pow(10.,16.46),2.)));
	    var1 = dense.xIonDense[ipHYDROGEN][0]/dense.gas_phase[ipHYDROGEN];
	    fabden_v += var1 * dense.DensityLaw[1] /pow(phycon.te/1e4,dense.DensityLaw[2]);
            break;
          case 391:
            /* dens = P1 + P2*exp(-((depth-P3)/P4)^2) + P5*exp(-((depth-P6)/P7)^2   */
            fabden_v = dense.DensityLaw[1]+dense.DensityLaw[2]*
              exp(-(pow((depth-pow(10.,dense.DensityLaw[3]))/pow(10.,dense.DensityLaw[4]),2.)))+
              dense.DensityLaw[5]*
              exp(-(pow((depth-pow(10.,dense.DensityLaw[6]))/pow(10.,dense.DensityLaw[7]),2.)));
            if( depth >  pow(10.,dense.DensityLaw[8]))
              fabden_v = dense.DensityLaw[9] * pow(10., 0.4 / (1.7 + log10(phycon.te/1e4)));
            break;
          case 392:
            /* dens = P1 + P2*exp(-((depth-P3)/P4)^2) + P5*exp(-((depth-P6)/P7)^2   */
            fabden_v = 2850.+7317*
              exp(-(pow((depth-pow(10.,16.14))/pow(10.,15.96),2.)))+
              11702*
              exp(-(pow((depth-pow(10.,16.93))/pow(10.,16.46),2.)));
	    var1 = dense.xIonDense[ipHYDROGEN][0]/dense.gas_phase[ipHYDROGEN];
	    fabden_v += var1 * dense.DensityLaw[1] * pow(10., dense.DensityLaw[2] / (dense.DensityLaw[3] + log10(phycon.te/1e4)));
            break;
	  case 4:
	    /* dens = P1 * exp(-depth / 10.^P2) */ 
	    fabden_v = dense.DensityLaw[1] * exp(-radius/pow(10.,dense.DensityLaw[2]));
	    break;
	  case 5:
	    /* Excentred shell: 
	       P6: Log10(background density)
	       P1: Log10(shell density)
	       P2: Log10(distance to the shell center)
	       P3: Theta (rad, pi/2: direction of the shell)
	       P4: Log10(Shell radius)
	       P5: Log10(Shell thickness)
	       P7: Plateau value
	      Rs = sqrt(R^2+P2^2 - 2*R*P2*cos(P3))  and dens = P6 + P1*min[1,P7*exp(-(Rs-P4/P5)^2)]    */
	    R_shell = sqrt(pow(radius,2.)+pow(10.,2.*dense.DensityLaw[2])-2.*radius*pow(10.,dense.DensityLaw[2])*sin(dense.DensityLaw[3]));
	    fabden_v = pow(10.,dense.DensityLaw[6]) + 
	      pow(10.,dense.DensityLaw[1]) * MIN2(dense.DensityLaw[7]*exp(-(pow((R_shell-pow(10.,dense.DensityLaw[4]))/pow(10.,dense.DensityLaw[5]),2.))),1.);
	    break;
          case 51:
            /* Excentred shell: 
               P6: Log10(background density)
               P1: Log10(shell density)
               P2: Log10(distance to the shell center)
               P3: Theta (rad, pi/2: direction of the shell)
               P4: Log10(Shell radius)
               P5: Log10(Shell thickness)
               P7: Plateau value
	       Rs = sqrt(R^2+P2^2 - 2*R*P2*sin(P3))  and FF = P6 + P1*min[1,P7*exp(-(Rs-P4/P5)^2)]    */
            R_shell = sqrt(pow(radius,2.)+pow(10.,2.*dense.DensityLaw[2])-2.*radius*pow(10.,dense.DensityLaw[2])*sin(dense.DensityLaw[3]));
            fabden_v = pow(10.,dense.DensityLaw[6]) + 
              pow(10.,dense.DensityLaw[1]) * MIN2(dense.DensityLaw[7]*exp(-(pow((R_shell-pow(10.,dense.DensityLaw[4]))/pow(10.,dense.DensityLaw[5]),2.))),1.);
            geometry.FillFac = pow(10.,dense.DensityLaw[8]) + 
              pow(10.,dense.DensityLaw[9]) * MIN2(dense.DensityLaw[7]*
                                                 exp(-(pow((R_shell-pow(10.,dense.DensityLaw[4]))/pow(10.,dense.DensityLaw[5]),2.))),1.);
            break;
	  case 52:
	    /* Excentred shell: 
	       P6: Log10(background density)
	       P1: Log10(shell density)
	       P2: Log10(distance to the shell center)
	       P3: Theta (rad, pi/2: direction of the shell)
	       P4: Log10(Shell radius)
	       P5: Log10(Shell thickness)
	       P7: Plateau value
	      Rs = sqrt(R^2+P2^2 - 2*R*P2*cos(P3))  and dens = 1/R^2 *( P6 + P1*min[1,P7*exp(-(Rs-P4/P5)^2)] )   */
	    R_shell = sqrt(pow(radius,2.)+pow(10.,2.*dense.DensityLaw[2])-2.*radius*pow(10.,dense.DensityLaw[2])*sin(dense.DensityLaw[3]));
	    fabden_v = pow(10.,dense.DensityLaw[6]) + 
	      pow(10.,dense.DensityLaw[1]) * MIN2(dense.DensityLaw[7]*exp(-(pow((R_shell-pow(10.,dense.DensityLaw[4]))/pow(10.,dense.DensityLaw[5]),2.))),1.);
	    fabden_v = fabden_v / pow(radius,2.) * pow(10.,2.*dense.DensityLaw[2]);
	    break;
	  case 6:
	    /* Constant pressure P1: Density at 1d4 K  */
	    fabden_v = dense.DensityLaw[1]/phycon.te*1e4 ;
	    break;
	  case 61:
	    /* P1: Density at 1d4 K  */
	    fabden_v = 
	      (dense.DensityLaw[1]/phycon.te*1e4 + 
	       dense.DensityLaw[2]/phycon.te*1e4 ) / 2 +
	      (dense.DensityLaw[2]/phycon.te*1e4 -
	       dense.DensityLaw[1]/phycon.te*1e4 ) *	  	
	      atan((depth - dense.DensityLaw[3])/dense.DensityLaw[4]) / 
	      3.141592654 ;
	    /* fprintf(ioQQQ,"density profile %.2f\n",fabden_v); */
	    break;
          case 71:
            /* Atan law with constant pressure in PDR*/
            fabden_v = 
              pow(10.,dense.DensityLaw[1]) + (pow(10.,dense.DensityLaw[2])-pow(10.,dense.DensityLaw[1])) *   
              (0.5+atan((radius - pow(10.,dense.DensityLaw[3]))/pow(10.,dense.DensityLaw[4])) / 
               3.141592654) ;
            if( radius >  pow(10.,dense.DensityLaw[5]))
              fabden_v = pow(10.,dense.DensityLaw[6])/pow(phycon.te/1e4,dense.DensityLaw[7]) ;
            break;
	  case 8:
	    /*    
	       dens = P1 + P3 * Sin(pi/2*R/10**P4)**P5 * (R/10**P2)**P6 
	       if dens < 0: dens = P1 
	    */
	    fabden_v = dense.DensityLaw[1] + dense.DensityLaw[3] * 
	      pow(cos(1.5707963267948966 * radius/pow(10.,dense.DensityLaw[4])),dense.DensityLaw[5]) *
	      pow(radius/pow(10.,dense.DensityLaw[2]), dense.DensityLaw[6]);
	    if (fabden_v < 0)
	      fabden_v = dense.DensityLaw[1] ;
	    break;
          case 9:
	    /* 
             dens = P1 * P2 / R
	    */
	    fabden_v = dense.DensityLaw[1] * dense.DensityLaw[2] / radius;
	    break;
	  }

#	ifdef DEBUG_FUN
	fputs( " <->fabden()\n", debug_fp );
#	endif
	return( fabden_v );

}

