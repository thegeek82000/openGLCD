To use doxygen
you must have doxygen/doxywizard installed.
http://www.doxygen.nl/download.html#latestsrc
(Make sure to have version 1.6.3 or later)

The main doxgen config file is Doxyfile.doxcfg
The ".doxcfg" extension was added to the default doxygen configfile name
to make it easier on Windows machines. Ths allows assigning a file extension
assosiation to .doxcfg to bring up doxywizard.

When doxygen generates its output, the config file redirects it to be put into the glcd/doc/html directory
rather than under here.
The GLCDref.htm file is a dummy wrapper that will bring up the documents over
in glcd/doc/html

.dox files can be tossed into the doxfiles directory and they will be processed automatically.
and .dox file can use image references to image files in the doxfiles directory or prefereably
in the "images" directory under the doxfiles directory.
