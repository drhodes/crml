// -*- c++ -*-
/* _.-{ license management }-._ 
Copyright (c) 2010, Derek A. Rhodes
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
3. Neither the name of the PostgreSQL Global Development Group nor the names
   of its contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/
// _.-{{ crml }}-._

#ifndef DISPLAY_H_
#define DISPLAY_H_

#include "../core/core.h"
#include "../gfx/drawer.h"
#include <GLES2/gl2.h>

namespace crml {
  ERR_(DISPLAY_CREATE_CONTEXT_FAILED);
  ERR_(DISPLAY_ACQUIRE_DEVICE_FAILED);
  ERR_(DISPLAY_NULL_REGION);
  ERR_(DISPLAY_NULL_WINDOW);
  ERR_(DISPLAY_NOT_YET_INITED);
  ERR_(DISPLAY_CANT_GET_HEIGHT);
  ERR_(DISPLAY_CANT_GET_WIDTH);
  
  //------------------------------------------------------------------
  class Display : public Error {
   public:
    static GLuint g_texture;
    static int g_textureLoc;
    static GLuint g_programObject;
    static GLuint g_worldMatrixLoc;
    static GLuint g_vbo;
    static GLsizei g_texCoordOffset;
    static int g_angle;
    
    explicit Display() : Error(OK) {
      inited_ = false;
      ClassName("Display");
    }    
    
    ~Display();
    
    // \return A pointer, Core::context2d_.region
    uint32_t* Pixels();
    int Height();
    int Width();
    
    void Redraw();
    void Init();
    void Wipe();
    void Wipe(uint32_t color);

    //void FontDraw(FT_Bitmap*, int, int);
    void Draw(Drawer&);
    void Draw3D();
    
    /// Satisfies Event.
    virtual bool Ok();  // Is the object in a OK state?
    
   private:
    bool inited_;
    
    NPDeviceContext2D context_;
    NPDevice* device2d_;
    uint32_t* pixels_;

    NPDevice* device3d_;
    PGLContext pgl_context_;
    NPDeviceContext3D context3d_;
    
    void CreateContext();
    void DestroyContext();
        
  };
}       // namespace crml
#endif  // DISPLAY_HPP_
