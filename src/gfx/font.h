// Copyright 2010 <Derek A. Rhodes>

#ifndef FONT_H_
#define FONT_H_

#include "./color.h"
#include <string>

namespace crml {

  class Font {
   public:
    //Font(FT_Library lib, FT_Face face);
    Font(char* filedata);
    ~Font();


    void Size(int s);
    int Size();
    void Text(std::string t);
    void SetColor(Color c);
           
   private:
    FT_Library library_;   // handle to library     
    FT_Face face_;         // handle to face object 

    int size_;
    std::string text_;
    Color color_;    
    FT_Error ft_error_;
    
  };  
}       // namespace crml
#endif  // FONT_H_













