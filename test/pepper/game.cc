#include <crml-core.h>
#include <crml-win.h>
#include <crml-sys.h>
#include <crml-evt.h>

#include "./square.h"
#include <media-blob.h>
#include <png.h>
#include <zlib.h>

#include <osg/GL>
#include <osg/Endian>

#include <ft2build.h>
#include FT_FREETYPE_H

#include <sstream>

using namespace crml;
#define NUMSQUARES 20000

Event evt;
Display dsp;
Clock timer1, timer2;

int frame = 0;
int fps = 15;
uint32_t* pixels_;
bool firstrun = true;
NPPepperEvent e;
int x = 1;
int y = 1;
Square sqs[NUMSQUARES];

FT_Library library;   // handle to library     
FT_Face face;         // handle to face object 

// move this off to color.h in the lib under gfx.
inline uint32_t MakeRGBA(uint32_t r, uint32_t g, uint32_t b, uint32_t a) {
  return  (a << 24) | (r << 16) | (g << 8) | b ;
}

// the following two function have been ripped from osg/plugins/png.

void RunOnce() {
  dsp.Init();
  pixels_ = dsp.Pixels();
  firstrun = false;
  //std::istringstream pic1(img__doodle_png, std::istringstream::out);
  //readPNGStream(img__doodle_png);   
}

void Core::MainLoop() {
  if (firstrun) {
    RunOnce();
    for(int i=0; i<NUMSQUARES; i++){
      sqs[i] = Square();
      sqs[i].Randomize(timer1.ElapsedNano());
      usleep(1);
    }   
  }
  /*
  if (timer1.ElapsedMilli() < ){
    return;
  }
  */
  timer1.Reset();
  dsp.Wipe();



  /////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////

  FT_Error error;

  error = FT_Init_FreeType( &library );  
  if (error){
    printf("Error in   FT_Init_FreeType( &library );\n");
  }

  error = FT_New_Memory_Face( library,
                              (FT_Byte*)fnt__inconsolata_otf,
                              58465, 
                              0,     
                              &face );
  if (error){
    printf("Error in    FT_New_Memory_Face( library,\n");
  }

  error = FT_Set_Char_Size(
      face,    /* handle to face object           */
      0,       /* char_width in 1/64th of points  */
      16*64,   /* char_height in 1/64th of points */
      300,     /* horizontal device resolution    */
      300 );   /* vertical device resolution      */
  if (error){
    printf("Error  FT_Set_Char_Size( ");
  }
  
  error = FT_Set_Pixel_Sizes(
      face,   /* handle to face object */
      0,      /* pixel_width           */
      100 );   /* pixel_height          */
  if (error){
    printf("Error  FT_Set_Pixel_Sizes( ");
  }

  error = FT_Render_Glyph( face->glyph,   /* glyph slot  */
                           FT_RENDER_MODE_NORMAL ); /* render mode */
  
  FT_GlyphSlot slot = face->glyph;  /* a small shortcut */
  int pen_x, pen_y, n;

  pen_x = 300;
  pen_y = 200;

  std::stringstream ss;
  ss << frame / timer2.ElapsedSec(); 
  //char what[11] = (ss.str()).c_str();
  //char what[11] = "1234567890";



  
  //for ( n = 0; n < sizeof(txt__hello_txt); n++ )
  for ( n = 0; n < 10; n++ ) {
    /* load glyph image into the slot (erase previous one) */
    error = FT_Load_Char( face, ss.str()[n], FT_LOAD_RENDER );
    
    if ( error )
      printf("Error!\n with LoadChar\n");
   
    dsp.FontDraw( &slot->bitmap,                  
                  pen_x + slot->bitmap_left,
                  pen_y - slot->bitmap_top );    
    /* increment pen position */
    pen_x += slot->advance.x >> 6;
  }
  
  /////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
  /////////////////////////////////////////////////////////////////////////////
 
  printf(txt__hello_txt_gz);
  
  while(evt.GetEvent(&e)) {
    switch(e.type) {
      case NPEventType_MouseDown:
        x = e.u.mouse.x;
        y = e.u.mouse.y;
        for(int i=0; i<NUMSQUARES; i++){
          sqs[i].X(x);
          sqs[i].Y(y);
        }
        break;
      case NPEventType_KeyDown:
        printf("%d\n", int(e.u.key.normalizedKeyCode));
        if (e.u.key.normalizedKeyCode == 40){          
          for(int i=0; i<NUMSQUARES; i++){
            sqs[i].Stop();
          }
        }          
        break;        
    }
  }

  if (frame%100 == 0){      
    printf("Flick!\n");
  }  

  for(int i=0; i<NUMSQUARES; i++){
    sqs[i].Draw(pixels_, dsp.Width(), dsp.Height());
    sqs[i].Move(dsp.Width(), dsp.Height());
    if (frame%10 == 0){
      sqs[i].Flick(timer1.ElapsedNano());
    }
  }
  
  frame += 1;  
  dsp.Redraw();
  if ( frame > 1000 ){
    frame = 1;
    timer2.Reset();
  }
  
}
  
//Image img1("gopher.png"); 
//Coord c1(0, 0);
//Sprite spr1(img1, c1);
  
//while(Core::Running()){
//dsp.ShowAt(c1, spr1);    
//c1.MoveX(1);
//}

