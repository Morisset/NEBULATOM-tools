# WHAT TO INSTALL FOR THE STARLIGHT HANDS-ON ACTIVITIES

In case of any problems, don't hesitate to contact Natalia Vale Asari (natalia@astro.ufsc.br) **before the school**, as it will be hard to find time for this once on site.



## Download STARLIGHT

Please go to [http://www.starlight.ufsc.br/node/3](http://www.starlight.ufsc.br/node/3)
and download the following.

From **STARLIGHT version 04 - Public release**:  
(1) An executable suitable to your OS.   
(2) and (3) of this section are not needed (they are already in the
NEBULATOM-tools distribution).  

From **Base Files**, download:  
- Base.bc03.Padova1994.chab.tar.bz2  
- Base.bc03.Padova1994.salp.tar.bz2  
- Base.bc03.Padova2000.chab.tar.bz2  
- Base.bc03.Padova2000.salp.tar.bz2  


## Test STARLIGHT

Create a directory (e.g. `~/Downloads/starlight/`) where you place all the files you have downloaded
above:

    Starlight_v04_[my_version].exe
    Base.bc03.Padova1994.chab.tar.bz2  
    Base.bc03.Padova1994.salp.tar.bz2  
    Base.bc03.Padova2000.chab.tar.bz2  
    Base.bc03.Padova2000.salp.tar.bz2    

Also copy the files from NEBULATOM-tools/Starlight_data/ to the same
directory:

    cp NEBULATOM-tools/Starlight_data/* ~/Downloads/starlight/

From a terminal, go to the directory where you have downloaded the files
above, e.g.

    cd ~/Downloads/starlight/

Untar the STARLIGHT distribution (this will create a directory named STARLIGHTv04/):

    tar xvfj StarlightChains_v04.Distrib.tar.bz2
    
Make the STARLIGHT you have just downloaded executable and move it to
STARLIGHTv04/ directory:

    chmod 755 Starlight_v04_[my_version].exe
    mv Starlight_v04_[my_version].exe STARLIGHTv04/

Go to the STARLIGHT ditribution directory and change this grid file:

    cd STARLIGHTv04/
    [open grid_example1.in with your favourite text editor]

Edit lines 2--5 (copied below) to the directory where your STARLIGHT
distribution is. For instance, 

    [old]
    /home/cid/STARLIGHTv04/BasesDir/                 [base_dir]
    /home/cid/STARLIGHTv04/                          [obs_dir]
    /home/cid/STARLIGHTv04/                          [mask_dir]
    /home/cid/STARLIGHTv04/                          [out_dir]

    [new]
    /home/natalia/Downloads/STARLIGHTv04/BasesDir/   [base_dir]
    /home/natalia/Downloads/STARLIGHTv04/            [obs_dir]
    /home/natalia/Downloads/STARLIGHTv04/            [mask_dir]
    /home/natalia/Downloads/STARLIGHTv04/            [out_dir]

Be careful, the total path cannot be too large (i.e. STARLIGHT will
complain if your directories are like
`/home/natalia/projects/schools/2017/nebulatom3/hands_on/natalia/starlight/STARLIGHTv04/`). Also
please avoid spaces in directory names.

Save your `grid_example1.in` and try to run STARLIGHT:

    ./Starlight_v04_Mac.exe < grid_example1.in

If STARLIGHT complains it has not found a file, the most likely culprit
is your directory path: it may be too large. Try moving your files so
that your path is smaller (or symlink to it in a smaller path), edit the
`grid_example1.in` to reflect your changes, and please try again.

After it has finished, inspect the creation date and the contents of the
following files:

    ls -l 0784.52327.478.cxt.sc4.C11.im.CCM.BN
    more 0784.52327.478.cxt.sc4.C11.im.CCM.BN
    ls -l 0414.51901.393.cxt.sc4.C11.im.CCM.BN
    more 0414.51901.393.cxt.sc4.C11.im.CCM.BN
    
    
## Get the new base ready

Go to the directory where you have downloaded the files above and untar
the new SSP base:

    cd ~/Downloads/starlight/
    tar xvfj BASE.gsd01.tar.bz2
    mv BASE.gsd01/BASE.gsd01 STARLIGHTv04/
    mv BASE.gsd01/* STARLIGHTv04/BasesDir/
    rm -rf BASE.gsd01


    
## Install git, Anaconda, python, etc.

Please follow the instructions below after Christophe Morisset's at
[https://github.com/Morisset/NEBULATOM-tools/tree/master/What2install](https://github.com/Morisset/NEBULATOM-tools/tree/master/What2install),
since you will find how to install git and Anaconda.

## Install python 2.7

Install python 2.7 with Anaconda:

    conda create --name python2.7 python=2.7 ipython numpy matplotlib astropy ipython ipykernel cython

Check it has been created:

    conda info --envs


## Using python 2.7

Activate python 2.7:

    source activate python2.7

Install atpy and pystarlight for python 2.7:
    
    pip install atpy
    pip install https://bitbucket.org/astro_ufsc/pystarlight/get/27600142ec48.zip
    
From a new terminal window, test:

    ipython
    import atpy
    import astropy
    import matplotlib
    import numpy
    import pystarlight
    atpy.__version__
    astropy.__version__
    matplotlib.__version__
    numpy.__version__

If there are no warnings or complaints, you are good to go.

Go back to python 3:

    source deactivate python2.7


## Any problems? Email me!

In case of any problems, don't hesitate to contact Natalia Vale Asari
(natalia@astro.ufsc.br) **before the school**, as it will be hard to
find time for this once on site. Please 

