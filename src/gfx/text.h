// Copyright 2010 <Derek A. Rhodes>

#ifndef TEXT_H_
#define TEXT_H_

#include "../core/error.h"
#include "./font.h"

namespace crml {
  
  class Text: public Error, public Drawer { 
   public:
    Text(char*, Font& fnt, int height);
    ~Text();
    
    // inherited virtuals
    void Draw();

   private:        
  };
  
}       // namespace crml
#endif  // TEXT_H_














