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
  ERR_(CORE_NULL_PLUGIN);
  ERR_(CORE_NULL_DEVICE_2D);
  ERR_(CORE_NULL_DEVICE_3D);
  ERR_(CORE_NULL_DEVICE_AUDIO);
  
  /// \brief The Core object which wires all subsystems
  //------------------------------------------------------------------
  class Core : public Error { 
   public:
    static Core* self_;
    
    explicit Core() : Error(OK) {
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

   private:
    PluginObject* plugin_;
    pthread_t loop_;	
  };  
}       // namespace crml
#endif  // CORE_H_



















