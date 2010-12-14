// -*- c++ -*-
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
