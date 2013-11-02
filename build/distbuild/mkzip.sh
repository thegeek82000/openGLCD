#################################################################
# create openGLCD distribution zip image.
#
# This is a bash shell script to check out a openGLCD tree and build
# a distribution zip image.
#
# build process overview:
#
# - checkout/create a tmp working tree from VCS repo
# - create the build information files in the tmp working dirctory
# - update/create any needed documenation in the tmp working directory
#     includes all doxygen based documenation
# - remove any uneeded/unwanted subdirectories from the tmp working directory
#      (currently the build directory)
# - remove the VCS tracking stuff from the tmp working directory
# - create 3 zip images from tmp working directory.
# 	- the working directory.
# 	- only the doc directory of the working directory. (DocOnly)
# 	- the working directory without the doc directory (NoDoc)
# - remove the tmp working directory.
#
# It is a bit complicated/messy because it has to capabable of running in
# multiple environments on multiple OSs.
# Becasue of the different OS's you can't force the shell processor using
# something like #!/bin/bash because the locations are not all the same and
# the windows bash shell is not even called bash.exe
#
# other uglies:
#
# Windoze uses @#!@# spaces in many directory names.
# Plus Windows has problems when the full path/filename exceeds 254 characters.
# So there are a few change directory commands used as well lots of
# quoted strings and also using some full
# paths when relative would have worked to get around stupid Windoze issues.
# Also, the windows svn has some code internally to work aound long 
# paths but it only works if you use full paths vs relative paths.
#
# Not only are there issues with Windoze but there issues whith linux too,
# especially when running this script from the nautilus GUI shell. 
# nautilus does not always properly set the $PWD variable to reflect the
# location where the script is launched from.
# Also Nautilus does not use $SHELL to determine which shell intrpreter
# to launch;
# It uses /bin/sh 
# This creates an issues as the Ubuntu boys in their
# infinite wisdom have changed the default shell in /bin to be dash
# instead of bash but use bash for the login shells (which Nautilus does use
# when starting a terminal. So this means that when using Nautilus the script
# may start with bash or dash.
# The biggest issue is with the built in echo command in dash.
# The brilliant boys that wrote dash have broken decades of compability with 
# the echo command by not supporting  options like -e to
# process escape characters. 
# They support escape character processing by default, which is good,
# but but then they don't swallow a -e option to maintain compatibilty with
# the echo command (VERY stupid). This is why the printf command must be used
# instead of echo when wanting escaped character processing
#
# bottom line is that while written assuming bash, it is a goal to make
# it work on  bash,  dash, sh so that it can run without having to set
# the shell processor at the top since this will not work across platforms.
# *nix users that use ksh may have to run it by typing 'bash xxx'
#
#
#
# Needed Tools:
# -------------
# you must have a commandline VCS tool:
#   GIT:
#	debian package: git
#   SVN:
#	http://www.open.collab.net/downloads/subversion/
#	debian package: subversion
#
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
##################################################################

#
# use TMPDIR if set otherwise assume right here for temp stuff
#

if [ "$TMPDIR" ] 
then
	PROGTEMP=$TMPDIR
else
	PROGTEMP=$(pwd)
	PROGTEMP=/tmp
fi

#
# Setup some date variable strings
#

MYDATE=`date +%Y%m%d`
MYDATETIME=`date`

# grab short name of script

PROGNAME=`basename $0`

#
# set PROGWD (program working directory) variable
#

#PROGWD=`dirname $0`
PROGWD=$(pwd)

#
# LOG file name (create based on baename of script file)
#

LOGFILE="$PROGWD/$PROGNAME.log"

##################################################################
#
# Define working variables
#
##################################################################

#
# name of library
# This name will be used for the name of the distribution
# directory inside the zip file.
# it is the name of the directory that will be in the
# "libraries" directory
#

GLCDLIBNAME=openGLCD

#
# location of repository
#

#GLCDREPO=http://glcd-arduino.googlecode.com/svn/trunk/glcd

# cheat and use local repo
GLCDREPO="$PROGWD/../.."

#
# VCS commands
#

#SVN
#VCSCMD="svn checkout"
# for SVN get the svn version# returned by svnversion
#VCSBUILDSTR=svnversion

#GIT
# cheat for now and simpy copy the local git repo
VCSCMD="cp -r"
#VCSBUILDSTR="git log --oneline |wc -l"
# create build and rev string
VCSBUILDSTR=$(git describe --dirty)
# strip out leading "v" and remove trailing git stuff
VCSBUILDREV=$(echo $VCSBUILDSTR | sed -e "s/^v//" -e "s/-g.*//")

#
# zip command
#
ZIPCMD="7z a"

#
# Name of working directory for distibution tree
#  note/warning the path needs to be full vs relative
#  as svn has special code to deal with the @#@$@! 
#  windows long path issue but it only kicks in on absolute paths.
#
GLCDDISTDIR="$PROGTEMP/$GLCDLIBNAME"


#
# Doxygen command and config file stuff
#  note: doxygen must be started in the directory
#  where the config file is since all paths in the config file
#  are relative to that point.
#

DOXYGEN=doxygen
DOXYGENDIR="$GLCDDISTDIR/build/doc/doxygen"
DOXYGENCFG=Doxyfile.doxcfg
#
# override project name and number in doxyfile
#
DOXYPROJNAME="Arduino $GLCDLIBNAME Library"
DOXYPROJNUM="Version $VCSBUILDSTR"

#
# name of Build Information file
#
GLCDBUILDINFO="$GLCDDISTDIR/Buildinfo.txt"
GLCDBUILDINFO_HDR="$GLCDDISTDIR/openGLCD_Buildinfo.h"
# create header file guard define name from header file name
GLCDBUILDINFO_HDR_GUARD=__$(basename "$GLCDBUILDINFO_HDR" .h)_h__ 

#
# names of build string defines
#
GLCD_GLCDLIB_DATESTR_NAME=GLCD_GLCDLIB_BUILD_DATESTR
GLCD_GLCDLIB_BUILDSTR_NAME=GLCD_GLCDLIB_BUILD_BUILDSTR
GLCD_GLCDLIB_REVSTR_NAME=GLCD_GLCDLIB_BUILD_REVSTR

#
# list of unwanted directories
# these are all relative the top level library directory
# i.e. "openGLCD"
# put a space between each desired directory
#
GLCDUNWANTED="debug build .git"

#
# files/directories that no matter where they are,
# remove them from the GLCD dist directory
# be careful with this.
#
GLCDTRASH=".svn"

##################################################################
# Now start to actually do something

echo Starting build $MYDATETIME >"$LOGFILE"

rm -rf "$GLCDDISTDIR"
echo Checking out VCS working tree to: $GLCDDISTDIR
echo ======== Checkout VCS tree to $GLCDDISTDIR >> "$LOGFILE"
echo $VCSCMD $GLCDREPO "$GLCDDISTDIR" >>"$LOGFILE"
$VCSCMD $GLCDREPO "$GLCDDISTDIR" >>"$LOGFILE"

if [ $? != 0 ]; then
	echo $PROGNAME: Fatal Error: could not checkout VCS tree
	exit 1
fi

echo ======== Working tree is ready for processing >> "$LOGFILE"
echo Working tree is ready for processing

# 
# Must deal with and grab VCS build number string before we do any mucking around with tree
# note: VCSBUILDSTR and VCSBUILDREV have commands in them
# that must be run in the distribution directory.
#
cd "$GLCDDISTDIR"
GLCDBUILDSTR=$VCSBUILDSTR
GLCDBUILDREV=$VCSBUILDREV


cd "$PROGWD"


#
# Create BuildInfo file(s)
# NOTE: The text file is created in DOS format for the Windoze users
#
echo Creating BuildInfo Text File "$GLCDBUILDINFO" in DOS format
echo ======== Creating BuildInfo Text File "$GLCDBUILDINFO" in DOS format >> "$LOGFILE"
printf "Distribution files created $MYDATETIME\r\n" > "$GLCDBUILDINFO"
printf "=====================================================================\r\n" >> "$GLCDBUILDINFO"
printf "Revision: $GLCDBUILDREV \r\n">> "$GLCDBUILDINFO"
printf "Build: $GLCDBUILDSTR \r\n">> "$GLCDBUILDINFO"
printf "=====================================================================\r\n" >> "$GLCDBUILDINFO"

echo Creating BuildInfo Header file
echo ======== Creating BuildInfo Header File "$GLCDBUILDINFO_HDR" >> "$LOGFILE"
echo "//" > "$GLCDBUILDINFO_HDR"
echo "// $GLCDLIBNAME build information" >> "$GLCDBUILDINFO_HDR"
echo "// This headerfile is automatically generated" >> "$GLCDBUILDINFO_HDR"
echo "//" >> "$GLCDBUILDINFO_HDR"
echo >> "$GLCDBUILDINFO_HDR"
echo "#ifndef $GLCDBUILDINFO_HDR_GUARD"  >> "$GLCDBUILDINFO_HDR"
echo "#define $GLCDBUILDINFO_HDR_GUARD"  >> "$GLCDBUILDINFO_HDR"
echo  >> "$GLCDBUILDINFO_HDR"
printf "#define $GLCD_GLCDLIB_DATESTR_NAME\\t\"$MYDATETIME\"">> "$GLCDBUILDINFO_HDR"
echo  >> "$GLCDBUILDINFO_HDR"
printf "#define $GLCD_GLCDLIB_REVSTR_NAME\\t\"$GLCDBUILDREV\"" >> "$GLCDBUILDINFO_HDR"
echo  >> "$GLCDBUILDINFO_HDR"
printf "#define $GLCD_GLCDLIB_BUILDSTR_NAME\\t\"$GLCDBUILDSTR\"" >> "$GLCDBUILDINFO_HDR"
echo  >> "$GLCDBUILDINFO_HDR"
echo "#endif" >> "$GLCDBUILDINFO_HDR"

#
# Must build doxygen docs before build directory is removed
#
echo Building Doxygen Documents
echo ======== Building Doxygen Documents >> "$LOGFILE"
cd "$DOXYGENDIR"
echo "PROJECT_NAME=\"$DOXYPROJNAME\"" >> "$LOGFILE"
echo "PROJECT_NUMBER=\"$DOXYPROJNUM\"" >> "$LOGFILE"
echo "PROJECT_NAME=$DOXYPROJNAME"
echo "PROJECT_NUMBER=$DOXYPROJNUM"
(cat $DOXYGENCFG ; echo "PROJECT_NAME=\"$DOXYPROJNAME\""  ; echo "PROJECT_NUMBER=\"$DOXYPROJNUM\"" ) | $DOXYGEN - >> "$LOGFILE" 2>&1
cd "$PROGWD"

#
# Remove the unwanted directories from the distribution like "build" and "debug"
#
echo Removing unwanted directories "($GLCDUNWANTED)" from VCS working tree
echo ======== Removing unwanted directories "($GLCDUNWANTED)" from $GLCDDISTDIR >> "$LOGFILE"
cd "$GLCDDISTDIR"
for unwanted in $GLCDUNWANTED; do\
	rm -rf $unwanted ;\
done
#
# Remove the VCS control/trash directories from the distribution like .svn
#
echo Removing VCS control files/directories "($GLCDTRASH)" from VCS working tree
echo ======== Removing trash directories "($GLCDTRASH)" from $GLCDDISTDIR >> "$LOGFILE"
for trash in $GLCDTRASH; do\
	find . -depth -name $trash -exec rm -rf '{}' ';' ;\
done


#
# BaseName of ZIP files
#

#GLCDZIPBASENAME="$GLCDLIBNAME-$MYDATE.zip"
GLCDZIPBASENAME="$GLCDLIBNAME-$GLCDBUILDSTR"

#
# The created Zip files will reside in a sub directory
# by the same name as basname of the zip files.
# 

cd "$PROGWD"
rm -rf $GLCDZIPBASENAME
mkdir $GLCDZIPBASENAME
cd $GLCDZIPBASENAME

#
# Create 3 zip images
#	- 1 that includes documeantion (doc directory)
#	- 1 that is just the documenation (doc directory)
#	- 1 that does not include the documenation (doc directory)

GLCDZIPNAME="$GLCDZIPBASENAME.zip"
GLCDZIPNAME_DOCONLY="$GLCDZIPBASENAME-DocOnly.zip"
GLCDZIPNAME_NODOC="$GLCDZIPBASENAME-NoDoc.zip"


echo Creating Zip files
echo ======== Creating Zip files from $GLCDDISTDIR >> "$LOGFILE"
rm -f $GLCDZIPNAME $GLCDZIPNAME_DOCONLY $GLCDZIPNAME_NODOC

echo ======== Creating full Zip file from $GLCDDISTDIR >> "$LOGFILE"
$ZIPCMD $GLCDZIPNAME "$GLCDDISTDIR" >> "$LOGFILE"
echo Zip file $GLCDZIPNAME created
echo ======== Zip file $GLCDZIPNAME created >> "$LOGFILE"

echo ======== Creating Doc only Zip file from $GLCDDISTDIR >> "$LOGFILE"
$ZIPCMD $GLCDZIPNAME_DOCONLY "$GLCDDISTDIR/doc/*" >> "$LOGFILE"
echo Zip file $GLCDZIPNAME_DOCONLY created
echo ======== Zip file $GLCDZIPNAME_DOCONLY created >> "$LOGFILE"

echo ======== Creating NoDoc only Zip file from $GLCDDISTDIR >> "$LOGFILE"
#remove doc directory and create a dummy readme indicating no docs
rm -rf "$GLCDDISTDIR/doc"
mkdir "$GLCDDISTDIR/doc"
echo "This version of the distribution contains no documenation" >> "$GLCDDISTDIR/doc/ReadMe.txt"

$ZIPCMD $GLCDZIPNAME_NODOC "$GLCDDISTDIR" >> "$LOGFILE"
echo Zip file $GLCDZIPNAME_NODOC created
echo ======== Zip file $GLCDZIPNAME_NODOC created >> "$LOGFILE"

echo Removing VCS working tree $GLCDDISTDIR
rm -rf "$GLCDDISTDIR"
echo ======== Removed VCS working tree $GLCDDISTDIR >> "$LOGFILE"

echo ======== $PROGNAME completed normally >> "$LOGFILE"

#
# move log file into zip distribution directory
#
cd "$PROGWD"
mv "$LOGFILE" "$GLCDZIPBASENAME"

echo $PROGNAME Finished

exit 0
