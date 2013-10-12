OVERVIEW
========
openGLCD is an open source project.

openGLCD makes it easy to use Graphical LCDs (GLCD) with Arduino.
The library supports several different chips and is easy to integrate with
different GLCD panels.
The configuration mechanism allows using a broad range of GLCD panels
and Arduino controllers.

LICENSE
=======
The Arduino openGLCD library files are part of the openGLCD project.
openGLCD is an open source project licensed for use in open source projects
under the terms of the GNU General Public License.
See License.txt for details.

DOCUMENTATION
=============
The documentation can be found in the doc directory. There is
detailed reference material in openGLCDref.htm.


INSTALL (Newer Arduino Releases)
================================
On newer Arduino releases (1.0.5 and newer) the library can be
installed using the IDE.

Use: [Sketch]->[Import Library]->[Add Library...]

To install the library from a downloaded pre-built zip file.

INSTALL (Older Arduino Releases)
================================
This library should be unziped into a folder named openGLCD in the libraries
directory. If you already have a folder called libraries in your Arduino 
sketchbook directory, unzip the glcd files there. If not, create a
folder called libraries in the sketchbook folder, and drop the library
folder here.

To locate your sketchbook directory
bring up the IDE and click on [File]->Preferences

You sketchbook directory can be anywhere you want.
The location where the IDE is looking for your sketchbook directory is
in the text box right there at the top of the "preferences" dialog.

Wherever that directory is, you will need to create a directory called
"libraries", then extract the zip image into that directory.
So you will end up with {sketchbook directory}/libraries/glcd ...

Alternatively you can install the openGLCD library directly in the Arduino
distribution by placing it in the libraries directory where the
Arduino distribution was installed.
For Arduino release 0018 and later that would be:
{Arduino install directory}/libraries
So you will end up with {Arduino install directory}/libraries/openGLCD ...

Then re-start the Arduino programming environment (IDE), and you should see the openGLCD 
library in the Sketch > Import Library menu. 

CONFIGURE
=========
Configuration files for defining pins and panel characteristics are in the
config folder. The library is capable of auto-configuring when using a
standard processor and panel with the suggested wiring.
If you need to modify the configuration see the documentation for details
on how to do this.

EXAMPLES
The example sketches are in the examples folder and can be accessed from 
the IDE menu by selecting File > Examples > openGLCD

Within the examples folder is a subfolder called APIexamples
that has an example sketch for most of each of the openGLCD functions.

GLCDdiags is a test sketch to help get things up and running and provides
diagnostic information that can help with troubleshooting.

Other example sketches and demos are provided that show how to use various
capabilities of the library.

FONTS
=====
The library is supplied with fixed and variable width font definitons 
located in the fonts folder. See the documentation for information on adding
your own fonts to this folder.

BITMAPS
=======
Bitmap images are stored in the bitmaps folder. The documentation 
describes how to create you own bitmaps using a utility provided in the 
bitmaps/glcdMakeBitmaps folder

OTHER FOLDERS
=============
The include and device folders contain low level system files.
These do not need to be modifed for normal operation.
