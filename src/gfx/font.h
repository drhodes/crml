// Copyright 2010 <Derek A. Rhodes>

#ifndef FONT_H_
#define FONT_H_

#include <ft2build.h>
#include FT_FREETYPE_H

#include "../core/error.h"
#include "./font.h"
#include "./color.h"
#include "./drawer.h"
#include "./layer.h"
#include <string>

namespace crml {
  ERR_(FONT_OK);
  ERR_(FONT_INIT_FAILED);
  ERR_(FONT_NEW_MEMORY_FAILED);
  ERR_(FONT_SET_CHAR_SIZE_FAILED);
  ERR_(FONT_SET_PIXEL_SIZE_FAILED);
  
  class Font : public Error {
   public:
    Font(char* filedata);
    ~Font();

    void Size(int s);
    int Size();
    void Text(std::string t);
    void SetColor(Color c);

    // inherited virtual
    bool Ok();
    
   private:
    FT_Library library_;
    FT_Face face_;      

    int size_;
    std::string text_;
    Color color_;    
    FT_Error ft_error_;
    
  };  
}       // namespace crml
#endif  // FONT_H_
