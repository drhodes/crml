// Copyright 2010 The Native Client Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can
// be found in the LICENSE file.

#include "./scripting_bridge.h"
#include <assert.h>
#include <string.h>
//#include "./pi_generator.h"

extern NPDevice* NPN_AcquireDevice(NPP instance, NPDeviceID device);

namespace bridge {

NPIdentifier ScriptingBridge::id_paint;

// Method table for use by HasMethod and Invoke.
std::map<NPIdentifier, ScriptingBridge::Method>*
    ScriptingBridge::method_table;

// Property table for use by {Has|Get|Set|Remove}Property.
std::map<NPIdentifier, ScriptingBridge::Property>*
    ScriptingBridge::property_table;

NPObject* ScriptingBridge::GetScriptableObject() {
  printf("++ NPObject* ScriptingBridge::GetScriptableObject() {\n");
  if (scriptable_object_ == NULL) {
    scriptable_object_ =
        NPN_CreateObject(npp_, &ScriptingBridge::np_class);
  }
  if (scriptable_object_) {
    NPN_RetainObject(scriptable_object_);
  }
  return scriptable_object_;
}

/// Describe this problem.
/// AFter the 2D "drawing context" comment below
/// the issue is that stuff needs to go back to pi_generator.cc
/// but the question is what to call that function? If it's Set Window
/// then maybe it's called from outside.

/// Find out where SetWindow is being called from.  find a way to execute
/// the last three lines.  A pure virtual function declared in ScriptingBridge
/// maybe called 2DInit ?  It starts a thread,
/// What is pi?  these questions and more to be answered after dinner.

/// ALSO
/// Move initializer lists from pi_generator.h?cc to scripting_bridge.cc
/// some of them should be declared here because there's two copies of
/// some properties.

NPError ScriptingBridge::SetWindow(NPWindow* window) {
  printf("++ NPError ScriptingBridge::SetWindow(NPWindow* window) {\n");
  if (!window)
    return NPERR_NO_ERROR;
  if (!IsContextValid())
    CreateContext();
  if (!IsContextValid())
    return NPERR_GENERIC_ERROR;
  // Clear the 2D drawing context.
  //pthread_create(&thread_, NULL, pi, this);
  window_ = window;
  // return Paint() ? NPERR_NO_ERROR : NPERR_GENERIC_ERROR;
  return NPERR_NO_ERROR;
}

void ScriptingBridge::CreateContext() {
  printf("++ void ScriptingBridge::CreateContext() {\n");
  if (IsContextValid())
    return;
  device2d_ = NPN_AcquireDevice(npp_, NPPepper2DDevice);
  assert(IsContextValid());
  memset(&context2d_, 0, sizeof(context2d_));
  NPDeviceContext2DConfig config;
  NPError init_err = device2d_->initializeContext(npp_, &config, &context2d_);
  assert(NPERR_NO_ERROR == init_err);
}


// Sets up method_table and property_table.
bool ScriptingBridge::InitializeIdentifiers() {
  printf("++ bool ScriptingBridge::InitializeIdentifiers() {\n");
  id_paint = NPN_GetStringIdentifier("paint");

  method_table =
      new(std::nothrow) std::map<NPIdentifier, Method>;
  if (method_table == NULL) {
    return false;
  }
  
  AddMethod("paint", &ScriptingBridge::Paint, id_paint);
  
  property_table =
      new(std::nothrow) std::map<NPIdentifier, Property>;
  if (property_table == NULL) {
    return false;
  }

  return true;
}


/// Adds a method to the bridge, it will be visible to javascript.
/// \param meth_name The name of the method to be exposed
/// \param meth A function pointer to the function to be called and associated with the meth_name
/// \return a bool to indicate success or failure
bool ScriptingBridge::AddMethod(std::string meth_name, Method meth, NPIdentifier meth_id){
  printf("++ bool ScriptingBridge::AddMethod(std::string meth_name, Method meth, NPIdentifier meth_id){\n");
  meth_id = NPN_GetStringIdentifier(meth_name.c_str());  
  method_table->insert(
      std::pair<NPIdentifier, Method>(meth_id, meth));
  //  method_table[id_paint] = &ScriptingBridge::Paint; 
  return true;
}


ScriptingBridge::~ScriptingBridge() {
  printf("++ ScriptingBridge::~ScriptingBridge() {\n");
}

/*
bool ScriptingBridge::Paint( const NPVariant* args,
                             uint32_t arg_count,
                             NPVariant* result) {
  PiGenerator* pi_generator = static_cast<PiGenerator*>(npp_->pdata);
  if (pi_generator) {
    DOUBLE_TO_NPVARIANT(pi_generator->pi(), *result);
    return pi_generator->Paint();
  }
  return false;
}
*/

// Class-specific implementation of HasMethod, used by the C-style one
// below.
bool ScriptingBridge::HasMethod(NPIdentifier name) {
  //printf("++ bool ScriptingBridge::HasMethod(NPIdentifier name) {\n");
  std::map<NPIdentifier, Method>::iterator i;
  i = method_table->find(name);
  return i != method_table->end();
}

// Class-specific implementation of HasProperty, used by the C-style one
// below.
bool ScriptingBridge::HasProperty(NPIdentifier name) {
  //printf("++ bool ScriptingBridge::HasProperty(NPIdentifier name) {\n");
  std::map<NPIdentifier, Property>::iterator i;
  i = property_table->find(name);
  return i != property_table->end();
}

// Class-specific implementation of GetProperty, used by the C-style one
// below.
bool ScriptingBridge::GetProperty(NPIdentifier name, NPVariant *result) {
  printf("++ bool ScriptingBridge::GetProperty(NPIdentifier name, NPVariant *result) {\n");
  VOID_TO_NPVARIANT(*result);

  std::map<NPIdentifier, Property>::iterator i;
  i = property_table->find(name);
  if (i != property_table->end()) {
    return (this->*(i->second))(result);
  }
  return false;
}

// Class-specific implementation of SetProperty, used by the C-style one
// below.
bool ScriptingBridge::SetProperty(NPIdentifier name, const NPVariant* value) {
  printf("++ bool ScriptingBridge::SetProperty(NPIdentifier name, const NPVariant* value) {\n");
  return false;  // Not implemented.
}

// Class-specific implementation of RemoveProperty, used by the C-style one
// below.
bool ScriptingBridge::RemoveProperty(NPIdentifier name) {
  printf("++ bool ScriptingBridge::RemoveProperty(NPIdentifier name) {\n");
  return false;  // Not implemented.
}

// Class-specific implementation of InvokeDefault, used by the C-style one
// below.
bool ScriptingBridge::InvokeDefault(const NPVariant* args,
                                    uint32_t arg_count,
                                    NPVariant* result) {
  printf("++ bool ScriptingBridge::InvokeDefault(const NPVariant* args,\n");
  return false;  // Not implemented.
}

// Class-specific implementation of Invoke, used by the C-style one
// below.
bool ScriptingBridge::Invoke(NPIdentifier name,
                             const NPVariant* args, uint32_t arg_count,
                             NPVariant* result) {
  //printf("++ bool ScriptingBridge::Invoke(NPIdentifier name,\n");
  std::map<NPIdentifier, Method>::iterator i;
  i = method_table->find(name);
  if (i != method_table->end()) {
    return (this->*(i->second))(args, arg_count, result);
  }
  return false;
}

// Class-specific implementation of Invalidate, used by the C-style one
// below.
void ScriptingBridge::Invalidate() {
  printf("++ void ScriptingBridge::Invalidate() {\n");
  // Not implemented.
}


// Called by the browser when a plugin is being destroyed to clean up any
// remaining instances of NPClass.
// Documentation URL: https://developer.mozilla.org/en/NPClass
void Invalidate(NPObject* object) {
  printf("++ void Invalidate(NPObject* object) {\n");
  return static_cast<ScriptingBridge*>(object)->Invalidate();
}

// Returns |true| if |method_name| is a recognized method.
// Called by NPN_HasMethod, declared in npruntime.h
// Documentation URL: https://developer.mozilla.org/en/NPClass
bool HasMethod(NPObject* object, NPIdentifier name) {
  //printf("++ bool HasMethod(NPObject* object, NPIdentifier name) {\n");
  return static_cast<ScriptingBridge*>(object)->HasMethod(name);
}

// Called by the browser to invoke a function object whose name is |name|.
// Called by NPN_Invoke, declared in npruntime.h
// Documentation URL: https://developer.mozilla.org/en/NPClass
bool Invoke(NPObject* object, NPIdentifier name,
            const NPVariant* args, uint32_t arg_count,
            NPVariant* result) {
  //printf("++ bool Invoke(NPObject* object, NPIdentifier name,\n");
  return static_cast<ScriptingBridge*>(object)->Invoke(
      name, args, arg_count, result);
}

// Called by the browser to invoke the default method on an NPObject.
// In this case the default method just returns false.
// Apparently the plugin won't load properly if we simply
// tell the browser we don't have this method.
// Called by NPN_InvokeDefault, declared in npruntime.h
// Documentation URL: https://developer.mozilla.org/en/NPClass
bool InvokeDefault(NPObject* object, const NPVariant* args, uint32_t arg_count, NPVariant* result) {
  printf("++ bool InvokeDefault(NPObject* object, const NPVariant* args, uint32_t arg_count, NPVariant* result) {\n");
  return static_cast<ScriptingBridge*>(object)->InvokeDefault(
      args, arg_count, result);
}

// Returns true if |name| is actually the name of a public property on the
// plugin class being queried.
// Called by NPN_HasProperty, declared in npruntime.h
// Documentation URL: https://developer.mozilla.org/en/NPClass
bool HasProperty(NPObject* object, NPIdentifier name) {
  //printf("++ bool HasProperty(NPObject* object, NPIdentifier name) {\n");
  return static_cast<ScriptingBridge*>(object)->HasProperty(name);
}

// Returns the value of the property called |name| in |result| and true.
// Returns false if |name| is not a property on this object or something else
// goes wrong.
// Called by NPN_GetProperty, declared in npruntime.h
// Documentation URL: https://developer.mozilla.org/en/NPClass
bool GetProperty(NPObject* object, NPIdentifier name, NPVariant* result) {
  printf("++ bool GetProperty(NPObject* object, NPIdentifier name, NPVariant* result) {\n");
  return static_cast<ScriptingBridge*>(object)->GetProperty(name, result);
}

// Sets the property |name| of |object| to |value| and return true.
// Returns false if |name| is not the name of a settable property on |object|
// or if something else goes wrong.
// Called by NPN_SetProperty, declared in npruntime.h
// Documentation URL: https://developer.mozilla.org/en/NPClass
bool SetProperty(NPObject* object, NPIdentifier name, const NPVariant* value) {
  printf("++ bool SetProperty(NPObject* object, NPIdentifier name, const NPVariant* value) {\n");
  return static_cast<ScriptingBridge*>(object)->SetProperty(name, value);
}

// Removes the property |name| from |object| and returns true.
// Returns false if it can't be removed for some reason.
// Called by NPN_RemoveProperty, declared in npruntime.h
// Documentation URL: https://developer.mozilla.org/en/NPClass
bool RemoveProperty(NPObject* object, NPIdentifier name) {
  printf("++ bool RemoveProperty(NPObject* object, NPIdentifier name) {\n");
  return static_cast<ScriptingBridge*>(object)->RemoveProperty(name);
}

// Creates the plugin-side instance of NPObject.
// Called by NPN_CreateObject, declared in npruntime.h
// Documentation URL: https://developer.mozilla.org/en/NPClass
NPObject* Allocate(NPP npp, NPClass* npclass) {
  printf("++ NPObject* Allocate(NPP npp, NPClass* npclass) {\n");
  return new ScriptingBridge(npp);
}

// Cleans up the plugin-side instance of an NPObject.
// Called by NPN_ReleaseObject, declared in npruntime.h
// Documentation URL: https://developer.mozilla.org/en/NPClass
void Deallocate(NPObject* object) {
  printf("++ void Deallocate(NPObject* object) {\n");
  delete static_cast<ScriptingBridge*>(object);
}

}  // namespace bridge



// Represents a class's interface, so that the browser knows what functions it
// can call on this plugin object.  The browser can use the methods in this
// class to discover the rest of the plugin's interface.
// Documentation URL: https://developer.mozilla.org/en/NPClass

NPClass bridge::ScriptingBridge::np_class = {
  NP_CLASS_STRUCT_VERSION,
  bridge::Allocate,
  bridge::Deallocate,
  bridge::Invalidate,
  bridge::HasMethod,
  bridge::Invoke,
  bridge::InvokeDefault,
  bridge::HasProperty,
  bridge::GetProperty,
  bridge::SetProperty,
  bridge::RemoveProperty
};

