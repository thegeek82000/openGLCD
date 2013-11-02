Instructions for how to build zip installation files.

Generic notes on script operation based on current operation:

The zip images are built by mkzip.sh which is a bash shell script.
A Windoze batch file wrapper (mkzip.bat) is supplied to start
it on non *nix machines. However unix tools must be present to allow
the bash script to properly run. (they come with WinAVR & Arduino installs)
NOTE: Windoze batch wrapper is not yet working so *nix OS is required as of now.

The script performs these operations:

- checkout/create a temporary working tree from VCS repo
NOTE: currently the script uses the local working development directory.
So for building older release simply manually set the local working directory
to the proper version or manually checkout the desired version and then run the script.

- create the build information files in the tmp working directory
- update/create any needed documenation in the tmp working directory
    includes all doxygen based documenation
    NOTE: the script will patch the PROJECT_NAME and PROJECT_NUMBER
	to override what is in the doxyfile
	They are set in the sript. The PROJECT_NUMBER will be set to match
	the GLCDBIULDVERSION. This ensures that the version reported in doxygen
	always matches the VCS version and the doxyfile doesn't have to be manually
	updated.
    NOTE: Also because of the way the script gets its VCS information you must
	have a git development tree in place for the script to run.

- remove any uneeded/unwanted subdirectories from the tmp working directory
- remove the VCS tracking stuff from the tmp working directory
- create 3 zip images from the working directory
	- the working directory.
	- only the doc directory of the working directory. (DocOnly)
	- the working directory without the doc directory (NoDoc)
- remove the tmp working directory.

The zip images will land in a subdirectory under where the build script
is located named according to the VCS revision.
The zip image name will include VCS revision information

*nix environment builds
===========================================
See the mkzip.sh for full details
and for what additional tools are needed.

After all the necessary tools are in place,
simply run the script to create the zip images


PC environement builds
===========================================
See the mkzip.bat for full details
and for what additional tools are needed.

Once the tools are in place you can simply double click on the mkzip.bat file.

If something is going wrong and the cmd window is going away
before any error message can be read,
use runmkzip.bat instead.
The only diference is that runmkzip.bat is a wrapper that will
pause after mkzip finishes so the command window will automatically
go away on a fatal batch processing error.
