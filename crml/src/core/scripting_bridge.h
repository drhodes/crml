// Copyright 2010 <Derek A. Rhodes>

#ifndef SCRIPTINGBRIDGE_H_
#define SCRIPTINGBRIDGE_H_

#include <map>

#include "npapi.h"
#include "nphostapi.h"

namespace crml {
  class ScriptingBridge : public NPObject {
   public:
    typedef bool (ScriptingBridge::*Method)(const NPVariant* args,
                                            uint32_t arg_count,
                                            NPVariant* result);
    typedef bool (ScriptingBridge::*Property)(NPVariant* result);

    explicit ScriptingBridge(NPP npp) : npp_(npp) {}
    virtual ~ScriptingBridge();

    // These methods represent the NPObject implementation.  The browser calls
    // these methods by calling functions in the |np_class| struct.
    void Invalidate();
    bool HasMethod(NPIdentifier name);
    bool Invoke(NPIdentifier name,
                        const NPVariant* args,
                        uint32_t arg_count,
                        NPVariant* result);
    bool InvokeDefault(const NPVariant* args,
                               uint32_t arg_count,
                               NPVariant* result);
    bool HasProperty(NPIdentifier name);
    bool GetProperty(NPIdentifier name, NPVariant* result);
    bool SetProperty(NPIdentifier name, const NPVariant* value);
    bool RemoveProperty(NPIdentifier name);

    static bool InitializeIdentifiers();

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

   private:
    NPP npp_;
    NPObject* window_object_;

    static NPIdentifier id_paint;

    static std::map<NPIdentifier, Method>* method_table;
    static std::map<NPIdentifier, Property>* property_table;
  };

}       /// namespace crml
#endif  /// SCRIPTING_BRIDGE_H_
