Geant4 Version Number/ROOT:

I am using geant4.9.6.p02 and Root version 5.18.00. . However, I have
sucessfully compiled this code under a number of different versions of Geant
and different flavors of Linux and on Macosx and it has worked fine. However,
I have had to make some modifications (usually to the Physics List) to get it
to run using a different version of Geant. 

---------------------------------------------------------------------

Before you Compile:

Step 1: Set all your Geant4 environment variables $G4INSTALL ect. and make
sure that $ROOTSYS is set as well. I do this by sourcing the gean4make.sh file.

Change Paths in Makefile Program
There are two files: /Debug/makefile and Debug/src/subdir.mk that have
hard-coded paths to where my geant4 libraries are. So change them to where
you have yours. ie) Look for -I/home/saull/geant/geant4.9.6.p02-install/lib64

---------------------------------------------------------------------

To Compile:

in /Debug
make (or make -jN where N is the number of cores.)

---------------------------------------------------------------------

To Run: 

in /Debug
./SimpleSim RunFile.mac

Note that I have provided two mac files. One for a source placed 10 m away and
at 10 degrees (RunFile.mac) and vis.mac that is just for visualization the
detector. After running, several outputs are created:
-positions.dat: file will be created with the position and oritentation of the
 cells. Not used for anything except as a sanity-check.
-output.root: The output file (tree) containing all the data.

---------------------------------------------------------------------

The Code:
in ./src

Right now this package only simulates the Pixel Imager. The file that holds
the detector construction is FullDetectorConstruction.cpp and it makes use of
the SiPMs defined in SenSL60035SiPMArray.cpp. 

---------------------------------------------------------------------

Modifications:

There are many options to modify the detector geometry and output from the mac
file. See all the messenger classes for more info. For example
CIRunActionMessenger shows some of the possible outputs, which are ROOT or
ASCII. There are also many possible types of outputs like SaveProcessedHits
(current default), that allow saving more/or less details about the
interactions as well. CIFullDetectorConstructorMessenger shows how one could
modify the crytal sizes, and plane separations ect. from the macfile. 

---------------------------------------------------------------------
