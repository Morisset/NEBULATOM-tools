v1.1.2

===============
WHAT TO INSTALL
===============

This is the list of the different packages/software you will have to install for the NEBULATOM workshop.
`https://eventos.redclara.net/indico/event/343/ <https://eventos.redclara.net/indico/event/343/>`_

In case of any problems, don't hesitate to contact Christophe Morisset before going to the school, as it will be hard to find time for this once on site: chris.morisset@gmail.com

git
===

You will need to have installed git software. You can verify if you already have it by doing in a terminal:

``which git``

if no link is given, you have to download this tool that we will use during the workshop.
Depending on your operating system:

I. Mac OSX: install the package from https://git-scm.com/download/mac
II. Linux: depending on your distribution:
 a. ``sudo yum install git``
 b. ``sudo apt-get install git``

Once done, from a new terminal create a directory dedicated for NEBULATOM3, and from it, verify that git is running well by executing:

``git clone https://github.com/Morisset/NEBULATOM-tools.git``

This will download some of the needed files for the school.

You need to do this and all the following **as soon as possible**, so we can detect and correct any problem.

Just **before leaving for NEBULATOM school**, you need to update the files in this directory by running from it:

``git pull``

This will only download the files that were modified.

python 3
======

NEBULATOM students are supposed to know basics of programing. Most of the hands-on will be done using Python (`https://www.python.org/ <https://www.python.org/>`_), version 3.6.
The most simple way to have all the needed packages is to install a full python distribution using for example Anaconda. If you already have Anaconda installed, you still may need to install the 3.6 version and some packages.

To verify if you have anaconda installed, just look at the answer of ``which python`` command in a terminal. If it points to a directory which name contains "anaconda", it means that you already have anaconda installed and you should go to point 2 below. If not, go to point 1.

1. If you don't have anaconda installed: The anaconda package is available following this link: `https://www.continuum.io/downloads <https://www.continuum.io/downloads>`_. We will use the python 3.6 package.

 Once done, from a new terminal, do the following:
 ``conda install pymysql``

2. If you already have an anaconda distribution installed for python 2: you only need to install a 3.6 environment, by writing the following in a terminal:

 ``conda create --name py3k6 python=3.6 matplotlib scipy numpy ipython h5py astropy pymysql pandas pytest ipykernel``

 ``source activate py3k6``

 ``ipython kernel install --user``

In both cases, once you have python 3.6 installed, you still need some additional libraries. From a terminal, do the following:

``pip install atpy``

``pip install pillow``

PyNeb
=====

The normal way to install PyNeb is the following:

``pip install -U pyneb``

but we may need to work with the latest development version, in which case you will do the following (only if I ask it during the workshop):

``pip install -U git+https://github.com/Morisset/PyNeb_devel.git``

pyCloudy
========

The normal way to install pyCloudy is the following:

``pip install -U pycloudy``

but we may need to work with the latest development version, in which case you will do the following (only if I ask it during the workshop):

``pip install -U git+https://github.com/Morisset/pyCloudy.git``

CLOUDY
======

Installation
------------

You need to install Cloudy. We will use the version 17.

You need to follow the instructions on this page: http://www.nublado.org/wiki/StepByStep

**IMPORTANT**

After downloading the code and before compiling the code (before running make), you need to do the following:

Edit the source/Makefile file to change the line number 116, by adding ".:" before "+":
You will obtain the following line:

``CDP = .:+``

This will indicate Cloudy that some files can be found in your current dirrectory, and not only in the place where Cloudy store its data.

Once this is done, you can compile Cloudy by using the make command in the source directory. This will create a programe file named cloudy.exe.

If you do not succeed to compile Cloudy, contact Christophe.

Run CLOUDY from everywhere
--------------------------

Once Cloudy is installed,

Once you have obtained the cloudy.exe program, you must inform your operating system where to find it from everywhere.

This can be done in different ways, most of them requiring editing the preferences file of the operating system.

There are 2 shells that are widely used: bash and (t)csh. To know which one is yours, type the following in a terminal:

``echo $shell``

Depending on the answer, follow these instructions:

1. /bin/sh or /bin/bash
 Edit or create the file .bashrc in your home directory and add the following line (you must adapt it to the actual location of cloudy.exe on your system):

 alias cloudy.exe="/home/morisset/Cloudy/c17.00_rc1/source/cloudy.exe"

2. /bin/csh or /bin/tcsh
 Edit or create the file .tcshrc in your home directory and add the following line (you must adapt it to the actual location of cloudy.exe on your system):

 alias cloudy.exe "/home/morisset/Cloudy/c17.00_rc1/source/cloudy.exe"

From a **new** terminal window, you can verify that the simple command below executed from any other directory than the source directory actually runs the cloudy smoke test:

``echo 'test' | cloudy.exe``

Test your installation
======================

Once all the above is done, you can open a terminal and go to the directory where the NEBULATOM-tools have been downloaded using git (at the beginning of this page). 

Go to Notebooks subdirectory. Enter:

``jupyter notebook``

This should open a new tab in your web browser. 

Click on ``test_install.ipynb``

A new page appears. You can execute each of the instructions from this page by clicking on the "PLAY" button in the upper part of the page. Or press SHIFT-ENTER.

If everything is OK, you should see the different versions of the packages we will use.

Just **before leaving for NEBULATOM school**, you need to update the files in the NEBULATOM-tools directory by running from it:

``git pull``

This will only download the files that were modified.

A directory to work in
======================

A lot of models will be run when doing all the exercises from this cookbook. To avoid having the results of the models invading the directory where the ipython notebooks are, the best is to create a special directory that will hold all those files. In our workshop, this directory is "Models", and has to be created on the same level as NEBULATOM-tools.


DO NOT HESITATE!!!
==================

In case of any problems, don't hesitate to contact Christophe **before going to the school**, as it will be hard to find time for this once on site: chris.morisset@gmail.com

YOU'RE NOT FINISHED!
====================

You now need to install the packages needed for Starlight, see there:
https://github.com/Morisset/NEBULATOM-tools/tree/master/What2install_Starlight
