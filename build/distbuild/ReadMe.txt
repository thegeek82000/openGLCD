Instructions for how to build a zip.

Generic notes based on current operation:

The zip image is built by mkzip.sh which is a bash shell script.
A Windoze batch file wrapper (mkzip.bat) is supplied to start
it on non *nix machines. However unix tools must be present to allow
the bash script to properly run. (they come with WinAVR & Arduino installs)

- checkout/create a temporary working tree from VCS repo
- create the build information files in the tmp working directory
- update/create any needed documenation in the tmp working directory
    includes all doxygen based documenation
- remove any uneeded/unwanted subdirectories from the tmp working directory
- remove the VCS tracking stuff from the tmp working directory
- create a zip file of the working directory.
- remove the tmp working directory.

The zip image will land in the same directory where the build script is located.
The zip image name will include the date.

*nix environment builds
===========================================
See the mkzip.sh for full details
and for what additional tools are needed.

After all the necessary tools are in place,
simply run the script to create the zip image


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
