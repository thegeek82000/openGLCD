@echo off
REM ##################################################################
REM # Windows batch file wrapper to create GLCD distribution zip image.
REM #
REM # This batch file looks for the unix tools, adds their path
REM # to the PATH variable, than calls a unix based tool
REM # to do the work to build the zip.
REM #
REM # Needed Tools:
REM # -------------
REM # you must have a commandline SVN tool:
REM #	http://www.open.collab.net/downloads/subversion/
REM #
REM # you must have 7zip installed.
REM #	http://www.7-zip.org/
REM # 	Make sure to manually add the install dir to your path as the
REM #	default install does not do this.
REM # 	normally it is: $SystemDrive:\Program Files\7-Zip
REM #
REM # you must have doxygen/doxywizard installed.
REM #	http://www.doxygen.nl/download.html#latestsrc
REM #	(Make sure to have version 1.6.3 or later)
REM #
REM # you must either put your svn glcd working directory in the Arduino
REM #	distribution "libraries" directory or install WinAVR.
REM #	This is because this batch file attempts to locate a unix tools directory
REM #	and can locate one in the arduino install area.
REM #	Alternatively, you can define WINAVR_UTILDIR in your windows enviroment to
REM #	point to the unix tools directory
REM #	If you install WinAVR or properly define WINAVR_UTILDIR, 
REM #	then this batch file and
REM #	the supporting bash shell script can be located anywhere and do not
REM #	depend on any other s/w other than those mentioned above.
REM #
REM ##################################################################

REM #
REM # grab short name of batch file: basename.extension
REM
set PROGNAME=%~n0.%~x0

REM #
REM # set PROGWD variable (grab it from path of batch file)
REM #
set PROGWD=%~dp0

echo CURRENT WORKING directory: %PROGWD%

REM #
REM # check to see if user supplied WINAVR_UTILDIR
REM # if so check to see if it exists, if not continue on looking elsewhere
REM #

if defined WINAVR_UTILDIR (
	echo WINAVR_UTILDIR exists
	if exist "%WINAVR_UTILDIR%" (
		goto endunixsearch
	)
	echo unix tool directory: %WINAVR_UTILDIR% not found
)



REM # 
REM # Look for a unix tools in Arduino binaries
REM # and then the WINAVR binaries.
REM #

echo looking for unix tools

REM #
REM # Use relative paths assuming this batch file is in a svn development
REM # glcd tree is that is underneath the Arduino distribution tree
REM # in the "libraries" directory
REM # Note that arduino  0018 and later use a different directory structure
REM #

set ARDUINO-0017_UTILDIR=%CD%\..\..\..\..\tools\avr\utils\bin
set ARDUINO-0018_UTILDIR=%PROGWD%..\..\..\..\hardware\tools\avr\utils\bin


REM #
REM # look for WinAVR installed on the machine
REM # (somewhat unpredictable which one we end up with if there are multiple)
REM # if you define WINAVR_UTILDIR, this file will use it 
REM #

if not defined WINAVR_UTILDIR (
	for /D %%G IN (%systemDrive%\WinAVR-*) do set WINAVR_UTILDIR=%%G\utils\bin
)

REM #
REM # look at all the possible directories (favor local Arduino directories)
REM #

if exist "%ARDUINO-0018_UTILDIR%" (
	set UNIX_TOOLDIR=%ARDUINO-0018_UTILDIR%
	goto endunixsearch
)
if exist "%ARDUINO-0017_UTILDIR%" (
	set UNIX_TOOLDIR=%ARDUINO-0017_UTILDIR%
	goto endunixsearch
)
if exist "%WINAVR_UTILDIR" (
	set UNIX_TOOLDIR=%WINAVR_UTILDIR%
	goto endunixsearch
)

REM for %%G in ("%ARDUINO-0018_UTILDIR%" "%ARDUINO-0017_UTILDIR%" "%WINAVR_UTILDIR%") do (
REM 	echo check for unix tools in %%G
REM 	if exist %%G (
REM 		echo found unix tool dir: %%G
REM 		set UNIX_TOOLDIR=%%G
REM 		goto endunixsearch
REM 	)
REM )

echo no unix tools found, cannot proceed
goto alldone

:endunixsearch
echo found unix tool dir: %UNIX_TOOLDIR%

REM #
REM # Windows defines TEMP but unix wants to see TMPDIR
REM # so we create a TMPDIR from TEMP
REM # note: the actual gnu shell on windows may override this
REM # using a fake mount point to the base location of the unix tools
REM # so don't freak if you see something like /tmp instead when
REM # it is actually referenced in the child shell script
REM #
set TMPDIR=%TEMP%


REM #
REM # set the PATH to include the directory with the unix tools
REM #

PATH %UNIX_TOOLDIR%;%PATH%

REM #
REM # now actually start doing something
REM #

sh.exe mkzip.sh

:alldone
REM #
REM # give the user a chance to see any potential output
REM #
pause
