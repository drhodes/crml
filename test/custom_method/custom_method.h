// Copyright 2010 The Native Client Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#ifndef CUSTOM_METHOD_H_
#define CUSTOM_METHOD_H_

#include <pthread.h>
#include <crml-core.h>
#include <crml-win.h>


namespace crml {

  //ERR_(PIGENERATOR_ON);

  class PiGenerator {// : public ScriptingBridge {
   public:
    //PiGenerator(NPP npp);    
    //~PiGenerator();
    
    //bool Paint();
    bool Paint1( const NPVariant* args, uint32_t arg_count, NPVariant* result);

    //void DerivedSetup();

    /*
    bool quit() const {
      return quit_;
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
    */
    
   protected:    
    //void CreateContext();
    //void DestroyContext();
    
    //NPWindow* window_;  
    //bool quit_;
    //double pi_;
  };

}       // namespace crml
#endif  // CUSTOM_METHOD_H_
