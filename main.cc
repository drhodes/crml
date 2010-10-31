// see apple.copyright for license.

#include <stdlib.h>
#include <stdio.h>
#include <nacl/nacl_npapi.h>
#include <pgl/pgl.h>

#include "plugin_object.h"
#include "event_handler.h"
#include "game.cc"
#include "log_macro.cc"

#ifdef WIN32
#define NPAPI WINAPI
#else
#define NPAPI
#endif

// Plugin entry points
extern "C" {
  NPError NPAPI NP_Initialize(NPNetscapeFuncs* browser_funcs,
                              NPPluginFuncs* plugin_funcs);
  NPError NPAPI NP_GetEntryPoints(NPPluginFuncs* plugin_funcs);

  NPError NPAPI NP_Shutdown() {
    pglTerminate();
    return NPERR_NO_ERROR;
  }

  NPError NP_GetValue(void* instance, NPPVariable variable, void* value);
  char* NP_GetMIMEDescription();
}  // extern "C"

// Plugin entry points

NPError NPAPI NP_Initialize(NPNetscapeFuncs* browser_funcs,
							NPPluginFuncs* plugin_funcs) {
  printf("NPError NPAPI NP_Initialize(NPNetscapeFuncs* browser_funcs,\n");
  Log("<-- NP_Initialize");
  browser = browser_funcs;
  pglInitialize();
  return NP_GetEntryPoints(plugin_funcs);
}

// Entrypoints -----------------------------------------------------------------

NPError NPAPI NP_GetEntryPoints(NPPluginFuncs* plugin_funcs) {
  printf("NPError NPAPI NP_GetEntryPoints(NPPluginFuncs* plugin_funcs) {\n");
  plugin_funcs->version = 11;
  plugin_funcs->size = sizeof(plugin_funcs);
  plugin_funcs->newp = NPP_New;
  plugin_funcs->destroy = NPP_Destroy;
  plugin_funcs->setwindow = NPP_SetWindow;
  plugin_funcs->newstream = NPP_NewStream;
  plugin_funcs->destroystream = NPP_DestroyStream;
  plugin_funcs->asfile = NPP_StreamAsFile;
  plugin_funcs->writeready = NPP_WriteReady;
  plugin_funcs->write = (NPP_WriteUPP)NPP_Write;
  plugin_funcs->print = NPP_Print;
  plugin_funcs->event = NPP_HandleEvent;
  plugin_funcs->urlnotify = NPP_URLNotify;
 plugin_funcs->getvalue = NPP_GetValue;
  plugin_funcs->setvalue = NPP_SetValue;

  Log("NP_GetEntryPoints");
  return NPERR_NO_ERROR;
}

scm::Game* GAME;

NPError NPP_New(NPMIMEType pluginType,
				NPP instance,
				uint16_t mode,
				int16_t argc, char* argn[], char* argv[],
				NPSavedData* saved) {
  printf("NPError NPP_New(NPMIMEType pluginType,\n");
  if (browser->version >= 14) {
    PluginObject* obj = reinterpret_cast<PluginObject*>
        (browser->createobject(instance, PluginObject::GetPluginClass()));
    instance->pdata = obj;
    event_handler = new EventHandler(instance);

    obj->New(pluginType, argc, argn, argv);

    //  REFACTOR ASAP
    //
    GAME = new scm::Game(obj->npp());
    //GAME->Init();
    GAME->RegisterEvent(event_handler);
    //
    //
  }

  Log("NPP_New");
  return NPERR_NO_ERROR;
}

NPError NPP_Destroy(NPP instance, NPSavedData** save) {
  printf("NPError NPP_Destroy(NPP instance, NPSavedData** save) {\n");
  PluginObject* obj = static_cast<PluginObject*>(instance->pdata);
  if (obj)
    NPN_ReleaseObject(obj->header());

  fflush(stdout);
  Log("NPP_Destroy");
  return NPERR_NO_ERROR;
}

NPError NPP_SetWindow(NPP instance, NPWindow* window) {
  printf("NPError NPP_SetWindow(NPP instance, NPWindow* window) {\n");
  PluginObject* obj = static_cast<PluginObject*>(instance->pdata);
  if (obj) {      
    obj->SetWindow(*window);    
  }
  Log("NPP_SetWindow");

  //  REFACTOR ASAP
  //
  GAME->RegisterPlugin(obj);
  GAME->RegisterContext2D(obj->GetContext2D());
  //
  //
  
  return NPERR_NO_ERROR;
}

NPError NPP_NewStream(NPP instance,
					  NPMIMEType type,
					  NPStream* stream,
					  NPBool seekable,
					  uint16_t* stype) {
  *stype = NP_ASFILEONLY;
  Log("NPP_NewStream");
  return NPERR_NO_ERROR;
}

NPError NPP_DestroyStream(NPP instance, NPStream* stream, NPReason reason) {
  printf("NPError NPP_DestroyStream(NPP instance, NPStream* stream, NPReason reason) {\n");
  Log("NPP_DestroyStream");
  return NPERR_NO_ERROR;
}

void NPP_StreamAsFile(NPP instance, NPStream* stream, const char* fname) {
  printf("void NPP_StreamAsFile(NPP instance, NPStream* stream, const char* fname) {\n");
  Log("NPP_StreamAsFile");
}

int32_t NPP_Write(NPP instance,
				  NPStream* stream,
				  int32_t offset,
				  int32_t len,
				  void* buffer) {
  printf("int32_t NPP_Write(NPP instance,\n");
  Log("NPP_NPP");
  return 0;
}

int32_t NPP_WriteReady(NPP instance, NPStream* stream) {
  printf("int32_t NPP_WriteReady(NPP instance, NPStream* stream) {\n");
  return 0;
}

void NPP_Print(NPP instance, NPPrint* platformPrint) {
  printf("void NPP_Print(NPP instance, NPPrint* platformPrint) {\n");
  Log("NPP_Print");
}

int16_t NPP_HandleEvent(NPP instance, void* event) {
  printf("int16_t NPP_HandleEvent(NPP instance, void* event) {\n");
  // push events here.
  Log("NPP_HandleEvent");	
  return event_handler->handle(event);
}

void NPP_URLNotify(NPP instance,
				   const char* url,
				   NPReason reason,
				   void* notify_data) {
  Log("NPP_URLNotify");
  // PluginObject* obj = static_cast<PluginObject*>(instance->pdata);
}

NPError NPP_GetValue(NPP instance, NPPVariable variable, void* value) {
  printf("NPError NPP_GetValue(NPP instance, NPPVariable variable, void* value) {\n");
  NPError err = NPERR_NO_ERROR;

  switch (variable) {
	case NPPVpluginNameString:
      *(reinterpret_cast<const char**>(value)) = "Pepper Test PlugIn";
      break;
	case NPPVpluginDescriptionString:
      *(reinterpret_cast<const char**>(value)) =
          "Simple Pepper plug-in for manual testing.";
      break;
	case NPPVpluginNeedsXEmbed:
      // TODO(msneck): The definition of TRUE and FALSE seem to have
      // disappeared on the BuildBot while building the partial SDK.  Once
      // the CL is to update the Chrome revision in native_client/DEPS has
      // been submitted and works, then we can try to track down the new
      // location, spelling, and definition of TRUE and FALSE.  But until
      // then, we're going to have to use 1 and 0.  A very temporary hack
      // just to get the BuildBots to work.
      *(reinterpret_cast<NPBool*>(value)) = 1;
      break;
	case NPPVpluginScriptableNPObject: {
      void** v = reinterpret_cast<void**>(value);
      PluginObject* obj = static_cast<PluginObject*>(instance->pdata);
      if (NULL == obj) {
        obj = reinterpret_cast<PluginObject*>(
            browser->createobject(instance, PluginObject::GetPluginClass()));
        instance->pdata = reinterpret_cast<void*>(obj);
      } else {
        // Return value is expected to be retained.
        browser->retainobject(reinterpret_cast<NPObject*>(obj));
      }
      *v = obj;
      break;
	}
	default:
      fprintf(stderr, "Unhandled variable to NPP_GetValue\n");
      err = NPERR_GENERIC_ERROR;
      break;
  }

  Log("NPP_GetValue");
  return err;
}

NPError NPP_SetValue(NPP instance, NPNVariable variable, void* value) {
  printf("NPError NPP_SetValue(NPP instance, NPNVariable variable, void* value) {\n");
  Log("NPP_SetValue");
  return NPERR_GENERIC_ERROR;
}

NPError NP_GetValue(void* instance, NPPVariable variable, void* value) {
  printf("NPError NP_GetValue(void* instance, NPPVariable variable, void* value) {\n");
  Log("NP_GetValue");
  return NPP_GetValue(reinterpret_cast<NPP>(instance), variable, value);
}

char* NP_GetMIMEDescription() {
  printf("char* NP_GetMIMEDescription() {\n");
  Log("NP_GetMIMEDescription");
  return const_cast<char*>("pepper-application/x-pepper-test-plugin;");
}


