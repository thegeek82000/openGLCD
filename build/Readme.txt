This directory (build) is for building and storing build related files.
The subdirectory distbuild is where zip distributions are built.
(see the readme in that directory for more details).

The subdirectory debug is used to aid in creating special builds for debugging

The main idea behind this directory is that this build directory and 
its files will not be included in a distribution zip image.

For documenation.
If the document is to always be distributed, it could be put it in openGLCD/doc.
If put here under doc, then the build tool will have to know how to copy it to over to openGLCD/doc

If it is internal or requires some amount processing before it goes into
openGLCD/doc, then put it here under doc.

For example, the doxygen configuration file information as well
as the non source code related doxygen files are all here under doc/doxygen
while the html generated output is over under openGLCD/doc/html.
