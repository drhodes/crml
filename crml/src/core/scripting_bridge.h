// Copyright 2010 The Native Client Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#ifndef SCRIPTING_BRIDGE_H_
#define SCRIPTING_BRIDGE_H_

#include <map>
#include <string>
#include <nacl/nacl_npapi.h>
#include <nacl/npapi_extensions.h>

namespace bridge {
  class ScriptingBridge : public NPObject {
   public:
    typedef bool (ScriptingBridge::*Method)(const NPVariant* args,
                                            uint32_t arg_count,
                                            NPVariant* result);

    typedef bool (ScriptingBridge::*Property)( NPVariant* result);
    
    explicit ScriptingBridge(NPP npp)
        : npp_(npp),
        scriptable_object_(NULL),
        device2d_(NULL),
        thread_(0),
        window_(NULL)
        {
          InitializeIdentifiers();
        }

    virtual ~ScriptingBridge();

    NPObject* GetScriptableObject();     
    NPError SetWindow(NPWindow* window);
    
    // These methods represent the NPObject implementation.  The browser calls
    // these methods by calling functions in the |np_class| struct.
    virtual void Invalidate();
    bool AddMethod(std::string, Method, NPIdentifier);
    void CreateContext();
    
    virtual bool HasMethod(NPIdentifier name);
    virtual bool Invoke(NPIdentifier name,
                        const NPVariant* args,
                        uint32_t arg_count,
                        NPVariant* result);
    virtual bool InvokeDefault(const NPVariant* args,
                               uint32_t arg_count,
                               NPVariant* result);
    virtual bool HasProperty(NPIdentifier name);
    virtual bool GetProperty(NPIdentifier name, NPVariant* result);
    virtual bool SetProperty(NPIdentifier name, const NPVariant* value);
    virtual bool RemoveProperty(NPIdentifier name);

    /// 
    ///
    //virtual void DerivedSetup();
    
    // static bool InitializeIdentifiers();
    bool InitializeIdentifiers();

    static NPClass np_class;

    // These methods are exposed via the scripting bridge to the browser.
    // Each one is mapped to a string id, which is the name of the method that
    // the broswer sees.  For example, Paint() has id 'paint', so in the browser
    // JavaScript, you would write tumbler.paint() to invoke the Paint() method
    // in this object.
    //
    // Each of these methods wraps a method in the associated Pepper3D object,
    // which is where the actual implementation lies.

    // Draws the quarter-circle image representing the stochasitc PI generator.
    bool Paint(const NPVariant* args, uint32_t arg_count, NPVariant* result);

    bool IsContextValid() {
      return device2d_ != NULL;
    }
    
   protected:
    NPP npp_;
    NPObject* window_object_;
    NPObject* scriptable_object_;  // strong reference
    NPDevice* device2d_;  // The PINPAPI 2D device.
    pthread_t thread_;

    NPWindow* window_;    
    NPDeviceContext2D context2d_;  // The PINPAPI 2D drawing context.
    
    static NPIdentifier id_paint;
    static std::map<NPIdentifier, Method>* method_table;
    static std::map<NPIdentifier, Property>* property_table;
  };

}  // namespace bridge

#endif  // EXAMPLES_PI_GENERATOR_SCRIPTING_BRIDGE_H_
