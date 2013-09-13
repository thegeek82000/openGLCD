/*********************************************************************
 *  BMP2GLCD - BMP to GLCD image 
 *  
 * vi: ts=4
 *
 *     workfile: bmp2glcd.cpp
 *
 *      Purpose: Convert a bitmap to binary bitmap with desired 
 *               dimensions and write a c-header file that contains
 *               the pixel data in 8-bit pages rather than in lines.
 *               This header file can be used for example with 
 *               graphical LCD displays. 
 *    
 *    Author(s): Sami J.O. Varjo,
 *		 Roberto Oriadne Dalla Valle is acknowledged for 
 *		 some debugging and support for PIC30
 *		 Bill Perry added glcd lib bitmap format support
 *	
 *      version: 1.02
 *      created: 31.7.2008
 *      revised: 10.1.2009
 *
 *      License: GPL which can be found at
 *               http://www.gnu.org/licenses/gpl.txt
 *
 *   Depends on: EasyBMP library (published under BDS license)
 *                          
 *   Usage: bmp2glcd <image.bmp> -h <height> -w <width> 
 *         -v   (verbose mode)
 *         -pgm (create header with __attribute__ progmem for AVR)
 *         -pic30 (create header with __attribute__((space(auto_psv))) for PIC30
 *         -openGLCD (create bitmap data in openGLCD library format)
 *
 *          (Note! there has to be space between switches -h and -w)
 *    
 *********************************************************************/
#include <iostream>
#include <fstream>
#include "EasyBMP.h"
#include <stdlib.h>


#define WRITE_BYTES_PER_LINE 16

using namespace std;

//Forward declarations
void printHelp(void);
bool saveHeaderFile(string name, BMP &image);

//global variables
bool verbose=false;
bool pgm=false;
bool pic30=false;
bool openGLCD=false;

int main( int argc, char* argv[] )
{
  BMP imageIn, imageOutput;
  int targetWidth, targetHeight, i;
  double coeff;
  ifstream test;
  
  if (argc<2)
    {
      printHelp();
      return -2;
    }

  targetWidth=-1;
  targetHeight=-1;

  SetEasyBMPwarningsOff();
    
  for(int i=2;i<argc;i++){
    if(strcmp(argv[i],"-h")==0)      
      targetHeight=atoi(argv[i+1]);
	else if(strcmp (argv[i],"-w")==0)
      targetWidth=atoi(argv[i+1]);
    else if(strcmp (argv[i],"-v")==0){
      verbose=true;
      SetEasyBMPwarningsOn();
    }
	else if(strcmp (argv[i],"-pgm")==0)    
      pgm=true;
	else if(strcmp (argv[i],"-pic30")==0)
      pic30=true;      
	else if(strcmp (argv[i],"-openGLCD")==0)
      openGLCD=true;      
  }

  // Make sure no scaling when using openGLCD format

  if(openGLCD && ((targetHeight > 00) || (targetWidth > 0)))
  {
	cerr << "Error: -h or -w Scaling not allowed with openGLCD Mode" << endl;
	return -1;
  }

  //Check if the file exists
  test.open(argv[1]);
  if (test.is_open() != true) {
    cerr << "Error: source file \""<<argv[1]<<"\" can not be openend"<<endl;
    return -1;
  }
  else test.close();

  //Read the image in
  try {
    imageIn.ReadFromFile(argv[1]);    
  }
  catch(...){
    cerr << "Error opening file \""<<argv[1]<<"\""<<endl<<endl;
    return -1;
  }    

  if(verbose){
    cout<<"Source height:"<<imageIn.TellHeight()<<"    source width:"
	<<imageIn.TellWidth()<<endl;
  }

  if(targetHeight>0 && targetWidth<0){
    coeff=(double)targetHeight/imageIn.TellHeight();
    targetWidth=(int)(imageIn.TellWidth()*coeff);
  }
  else if (targetHeight<0 && targetWidth>0){
    coeff=(double)targetWidth/imageIn.TellWidth();
    targetHeight=(int)(imageIn.TellHeight()*coeff);
  }
  else if (targetHeight<0 && targetWidth<0 ){
    targetHeight=imageIn.TellHeight();
    targetWidth=imageIn.TellWidth();
  }
    
  if(targetWidth<targetHeight)
    Rescale( imageIn, 'w' , targetWidth );
  else
    Rescale( imageIn, 'h' , targetHeight );
    
  if(verbose)
    cout <<"Target height:"<< targetHeight <<"    target width:" << targetWidth<<endl;

  imageOutput.SetSize( targetWidth , targetHeight );
  RangedPixelToPixelCopy( imageIn, 0, targetWidth-1, targetHeight-1, 0, imageOutput, 0,0);
  imageOutput.SetBitDepth( 1 );    
  CreateGrayscaleColorTable( imageOutput );

  string glcdname(argv[1]), outname;
  i=glcdname.find(".bmp",1);
  if(i!=string::npos)
    glcdname = glcdname.replace(i,4,"_glcd");
  
  do{// '-' is not allowed in c header variable name
    i=glcdname.find('-');
    if(i!=string::npos)
      glcdname=glcdname.replace(i,1,"_");
  }while(  i!=string::npos );
 
  outname=glcdname;
  outname+=".bmp";
  if(verbose)
    cout << "writing a 1bpp image as \"" << outname.c_str() <<"\""<< endl;
  imageOutput.WriteToFile (outname.c_str() );//the pixel data is updated only in write in EasyBMP
  imageOutput.ReadFromFile(outname.c_str() ); 

  if(openGLCD)
  	glcdname +="bmp"; // glcdname will be XXX_glcdbmp

  if (!saveHeaderFile(glcdname, imageOutput)){
    cerr << "Error on creating header file\n";
    return -2;
  }
    
  return 0;
}


//--------------------------------------------------------------------------
//Program commandline help
//
void printHelp(void){
  cout << "bmp2glcd - Bitmap to GLCD bitmap ver 1.01 by S.Varjo 2008" <<endl
       << "Usage: bmp2glcd <image.bmp> <options>" << endl
       << "\t-h <height>\ttarget image height in pixels" << endl
       << "\t-w <width>\ttarget image width in pixels" << endl 
       << "\t-v\t\tverbose mode" << endl
       << "\t-pgm\t\tcreate header with __attribute__ ((progmem)) for AVR"<< endl
       << "\t-pic30\t\tcreate header whith __attribute__((space(auto_psv))) for PIC30" << endl
       << "\t-openGLCD\tcreate bitmap data in GLCDlib format" << endl
	<<endl
       << "This program converts a bitmap to binary bitmap (black and white) with 8bit page"  
       <<endl
       << "height that can be written directly to graphical lcd display. A c-header file is" 
       <<endl
       << "created where data bytes represent pixels in page columns rather than in lines."  
       <<endl
       << "The created bitmap is solely to see the result image in simple way."
       <<endl <<endl;
}

bool saveHeaderFile(string name, BMP &image){

  string basename=name;
  name+=".h";
  ofstream out(name.c_str());
  if (!out)
    return false;
  
  int pages, single_lines, i, j, bi, count;  
  
  int byte; 
  
  pages=(int)image.TellHeight()/8;
  single_lines=image.TellHeight()-pages*8;

  if(verbose)
    cout <<"writing header file as  \"" << name.c_str() << "\""<<endl;
  
  if(!openGLCD)
  {

	for(unsigned int i=0; i < basename.length(); i++)
		basename[i]=toupper(basename[i]);
  }

  out << "//---------------------------------------------------------------------------"
      << endl
      << "//    A header datafile for glcd bitmap created with bmp2glcd by S.Varjo " 
      << endl;

  if(openGLCD)
  {
	out << "//    The glcd bitmap data contained in this file is in a format"<< endl
	    << "//    suitable for use by openGLCD." << endl
		<< "//    It contains embedded width and height format information."<< endl
		<< "//" << endl
	    << endl;
  }

  out << "//---------------------------------------------------------------------------"
      <<  endl 
      <<  endl 

      << "#ifndef _"<<basename.c_str()<<"_H " <<endl
      << "#define _"<<basename.c_str()<<"_H " <<endl<<endl;
  if(openGLCD)
  {
		<< endl;
  }
  else
  {
	out << "#define "<<basename.c_str()<<"_HEIGHT "<<image.TellHeight() <<" "<< endl
		<< "#define "<<basename.c_str()<<"_WIDTH  "<<image.TellWidth() << " "<< endl;
  
  
   for(unsigned int i=0; i < basename.length(); i++)
	basename[i]=tolower(basename[i]);

  }

  if (openGLCD)
    out <<"GLCDBMAPDECL(" << basename.c_str() <<") ={"<<endl;
  else if (pgm)
    out <<"static unsigned char __attribute__ ((progmem)) " << basename.c_str() <<"_bmp[]={"<<endl;
  else if(pic30)
    out <<"static unsigned char __attribute__((space(auto_psv))) " << basename.c_str() <<"_bmp[]={"<<endl;
  else
    out << "static char "<< basename.c_str() <<"_bmp[]={"<<endl;

  if(openGLCD)
  {
	out << image.TellWidth() << ",\t// bitmap width  (openGLCD format)" << endl;
	out << image.TellHeight() << ",\t// bitmap height (openGLCD format)" << endl;
  }

  count=image.TellWidth()*image.TellHeight();

  j=0;
  //whole pages
  while(j<pages){
    i=0;
    while(i<image.TellWidth()){
      byte=0x00;
      for(bi=0;bi<8;bi++){	
	if((int)image(i,j*8+bi)->Green==0){ //pixel is black RGB=(0,0,0)
	  byte |= (1<<bi); 
	}
      }
      out <<"0x";
      if (byte<16) out <<"0"; //for a best format
      out<<hex<<byte;

      if(--count != 0) out << ", ";
      
      if((i+1)%WRITE_BYTES_PER_LINE==0) out<<endl;  //include first and
	                                                // i no zero  
      i++;
    }    
    out << endl;
    j++;
  }

  i=0;
  if (single_lines>0){
    while(i<image.TellWidth()){
      byte=0x00;
      for(bi=0;bi<single_lines;bi++){	
	if((int)image(i,j*8+bi)->Green==0){
	  byte |= (1<<bi);
	}
      }
      out <<"0x";
      if (byte<16) out <<"0"; //for a best format
      out<<hex<<byte;
            
      if(--count != 0) out << ", ";
      i++;      
    } 
  }
  long pos=out.tellp(); 
  out.seekp (pos-2); //del last comma 
  out << endl;
  
  //transform(basename.begin(),basename.end(),basename.begin(), ::toupper);

  if(!openGLCD)
  {
	for(unsigned int i=0; i < basename.length(); i++)
		basename[i]=toupper(basename[i]);
  }

  out << "};"<<endl
	  << "#endif  //define _"<<basename.c_str()<<"_H " <<endl;

  out.close();

  return true;
}
