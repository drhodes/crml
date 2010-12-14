// _.-{{crml}}-._

#ifndef CORE_H_
#define CORE_H_

#include "error.h"
#include <string.h>
#include <assert.h>
#include <stdlib.h>

#include "./plugin_object.h"

namespace crml { 
  /// error codestrings.
  ERR_(CORE_NULL);
  ERR_(CORE_OK);
  ERR_(CORE_NULL_PLUGIN);
  ERR_(CORE_NULL_DEVICE_2D);
  ERR_(CORE_NULL_DEVICE_3D);
  ERR_(CORE_NULL_DEVICE_AUDIO);
  
  /// \brief The Core object which wires all subsystems
  //------------------------------------------------------------------
  class Core : public Error { 
   public:
    static Core* self_;
    
    explicit Core() : Error(CORE_OK) {
      ClassName("Core");
      self_ = 0;
    }    
    
    ~Core();
    void SetPlugin(PluginObject* plugin);                        
    void Redraw();

    void MainLoop();
    void __MainLoop__();
    void Main3D();
    
    // Pluggin Getters.
    NPObject Header();
    NPP Npp();
    int Dimensions();
    NPDevice* Device2d();
    NPDevice* Device3d();
    PGLContext PglContext();
    NPDevice* DeviceAudio();
    NPDeviceContext3D Context3d();
    NPDeviceContextAudio ContextAudio();
    unsigned int Device2dChecksum();
    unsigned int Plugin2dChecksum();
    int Width();
    int Height();

    static void Alert(std::string msg);
    
    
    /// \return a context2D, be careful.
    NPDeviceContext2D GetContext2D();

    virtual bool Ok();  // Is the object in a OK state?
   private:
    PluginObject* plugin_;
    pthread_t loop_;	
  };  
}       // namespace crml
#endif  // CORE_H_



















