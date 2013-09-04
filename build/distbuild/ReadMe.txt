Instructions for how to build a zip.

Generic notes based on current operation:

The zip image is built by mkzip.sh which is a bash shell script.
A Windoze batch file wrapper (mkzip.bat) is supplied to start
it on non *nix machines. However unix tools must be present to allow
the bash script to properly run. (they come with WinAVR & Arduino installs)

- The head of the SVN tree is checked out into a working directory
- build information files are generated
- doxygen documentation is updated.
- directories not needed/used in the distribution are removed removed from the working directory
	(currently debug and build)
- All the .svn directories are stripped away
- All other files and directories are left "as is".
 (No other files like word docs are touched, modified, or removed)

The zip image will land in the same directory where the build script is located.
The zip image name will include the date.

*nix environment builds
===========================================
(See the mkzip.sh for full details)
Simply run the script to create the zip image
make sure all the proper tools are installed:

# Needed Tools:
# -------------
# you must have a commandline SVN tool:
#	http://www.open.collab.net/downloads/subversion/
#	debian package: subversion
#
# you must have 7zip installed.
#	http://www.7-zip.org/
#	debian package: p7zip-full
#
# you must have doxygen/doxywizard installed.
#	http://www.doxygen.nl/download.html#latestsrc
#	(Make sure to have version 1.6.3 or later)
#	debian package: doxygen
#



PC environement builds
===========================================
(See the mkzip.bat file for full details)
First make sure all the proper tools are installed:
 # Needed Tools:
 # -------------
 # you must have a commandline SVN tool:
 #	http://www.open.collab.net/downloads/subversion/
 #
 # you must have 7zip installed.
 #	http://www.7-zip.org/
 # 	Make sure to manually add the install dir to your path as the
 #	default install does not do this.
 # 	normally it is: $SystemDrive:\Program Files\7-Zip
 #
 # you must have doxygen/doxywizard installed.
 #	http://www.doxygen.nl/download.html#latestsrc
 #	(Make sure to have version 1.6.3 or later)
 #


Once the tools are in place you can simply double click on the mkzip.bat file.

If something is going wrong and the cmd windows is going away
before any error message can be read,
use runmkzip.bat instead.
The only diference is that runmkzip.bat is a wrapper that will
pause after mkzip finishes so the command window will automatically
go away on a fatal batch processing error.
