// Copyright 2010 <Derek A. Rhodes>

#ifndef TEXT_CC
#define TEXT_CC

#include "./text.h"

namespace crml {

Text::Text(char*, Font& fnt, int height) :   
    Error(TEXT_OK),
    Drawer() {
  ClassName("Text");
}

Text::~Text(){  
}

void Text::Draw(){
  //void Display::FontDraw(FT_Bitmap* bm, int left, int top){
  /*
  int row = top * Width() + left;
    
  for(int i=0; i<bm->rows; i++){
    for(int j=0; j<bm->width; j++){  
      pixels_[row + j] = MakeRGBA(0,0,0,bm->buffer[i*bm->pitch+j]);
    }
    row = (top+i-1) * Width() + left;
  }
  */
}

bool Text::Ok(){
  return Err() == TEXT_OK;
}


}       // namespace crml
#endif  // TEXT_CC














