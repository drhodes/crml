// Copyright 2010 The Native Client Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#ifndef EXAMPLES_PI_GENERATOR_H_
#define EXAMPLES_PI_GENERATOR_H_

#include <pthread.h>
#include <nacl/nacl_npapi.h>
#include <nacl/npapi_extensions.h>
//#include "./scripting_bridge.h"
#include <crml-core.h>

#include <map>

namespace bridge {
  class PiGenerator : public ScriptingBridge {
   public:
    PiGenerator(NPP npp);    
    ~PiGenerator();
    
    bool Paint();
    //void DerivedSetup();
    
    bool quit() const {
      return quit_;
    }
    double pi() const {
      return pi_;
    }
    void* pixels() const {
      return context2d_.region;
    }
    int width() const {
      return window_ ? window_->width : 0;
    }
    int height() const {
      return window_ ? window_->height : 0;
    }

    
   protected:   
    // Create and initialize the 2D context used for drawing.
    void CreateContext();

    // Destroy the 2D drawing context.
    void DestroyContext();

    //NPWindow* window_;
    bool quit_;
    double pi_;

    static void* pi(void* param);
  };

}  // namespace bridge

#endif  // EXAMPLES_PI_GENERATOR_H_
