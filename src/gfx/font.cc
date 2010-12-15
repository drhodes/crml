// Copyright 2010 <Derek A. Rhodes>

#ifndef FONT_CC
#define FONT_CC

#include "./font.h"

namespace crml {
Font::~Font(){}
 
Font::Font(char* fontdata) : Error(OK) {
  ClassName("Font");
  
  ft_error_ = FT_Init_FreeType( &library_ );  
  if (ft_error_){
    SetReportErr(FONT_INIT_FAILED);   
  }

  ft_error_ = FT_New_Memory_Face( library_,
                                  (FT_Byte*)fontdata,
                                  58465, 
                                  0,     
                                  &face_ );
  if (ft_error_){
    SetReportErr(FONT_NEW_MEMORY_FAILED);    
  }
  
  ft_error_ = FT_Set_Char_Size(
      face_,    // handle to face object           
      0,       // char_width in 1/64th of points  
      16*64,   // char_height in 1/64th of points 
      300,     // horizontal device resolution    
      300 );   // vertical device resolution      
  
  if (ft_error_){
    SetReportErr(FONT_SET_CHAR_SIZE_FAILED);
  }
  
  ft_error_ = FT_Set_Pixel_Sizes(
      face_,   // handle to face object 
      0,      // pixel_width           
      Size() );   // pixel_height          
  if (ft_error_){
    SetReportErr(FONT_SET_PIXEL_SIZE_FAILED);
  }
  
  /*
  ft_error_ = FT_Render_Glyph( face_->glyph,   // glyph slot  
                               FT_RENDER_MODE_NORMAL ); // render mode 
    
  //FT_GlyphSlot slot = face_->glyph;  // a small shortcut
  
  //int pen_x, pen_y, n;  
  //pen_x = 0;
  //pen_y = 0;


    for ( n = 0; n < stringsize; n++ ) {
    // load glyph image into the slot (erase previous one) 
    ft_error_ = FT_Load_Char( face_, ss.str()[n], FT_LOAD_RENDER );
    
    if ( ft_error_ )
    printf("Ft_Error_!\n with LoadChar\n");
   
    dsp.FontDraw( &slot->bitmap,                  
    pen_x + slot->bitmap_left,
    pen_y - slot->bitmap_top );    
    // increment pen position 
    pen_x += slot->advance.x >> 6;
    }
  */
  
}



void Font::SetColor(Color c){}  
void Font::Size(int s){}
int Font::Size(){
  return size_;
}

}       // namespace crml
#endif  // FONT_CC
