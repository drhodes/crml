/* _.-{ license management }-._ 
IMPORTANT:  This Apple software is supplied to you by Apple Computer, Inc.
("Apple") in consideration of your agreement to the following terms, and
your use, installation, modification or redistribution of this Apple software
constitutes acceptance of these terms.  If you do not agree with these terms,
please do not use, install, modify or redistribute this Apple software.

In consideration of your agreement to abide by the following terms, and
subject to these terms, Apple grants you a personal, non-exclusive license,
under Apple's copyrights in this original Apple software
(the "Apple Software"), to use, reproduce, modify and redistribute the Apple
Software, with or without modifications, in source and/or binary forms;
provided that if you redistribute the Apple Software in its entirety and
without modifications, you must retain this notice and the following text and
disclaimers in all such redistributions of the Apple Software.  Neither the
name, trademarks, service marks or logos of Apple Computer, Inc. may be used
to endorse or promote products derived from the Apple Software without
specific prior written permission from Apple. Except as expressly stated in
this notice, no other rights or licenses, express or implied, are granted by
Apple herein, including but not limited to any patent rights that may be
infringed by your derivative works or by other works in which the Apple
Software may be incorporated.

The Apple Software is provided by Apple on an "AS IS" basis.  APPLE MAKES NO
WARRANTIES, EXPRESS OR IMPLIED, INCLUDING WITHOUT LIMITATION THE IMPLIED
WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY AND FITNESS FOR A PARTICULAR
PURPOSE, REGARDING THE APPLE SOFTWARE OR ITS USE AND OPERATION ALONE OR IN
COMBINATION WITH YOUR PRODUCTS.

IN NO EVENT SHALL APPLE BE LIABLE FOR ANY SPECIAL, INDIRECT, INCIDENTAL OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) ARISING IN ANY WAY OUT OF THE USE, REPRODUCTION, MODIFICATION
AND/OR DISTRIBUTION OF THE APPLE SOFTWARE, HOWEVER CAUSED AND WHETHER UNDER
THEORY OF CONTRACT, TORT (INCLUDING NEGLIGENCE), STRICT LIABILITY OR
OTHERWISE, EVEN IF APPLE HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.


*/
// _.-{{ apple }}-._

#include "plugin_object.h"

#include <assert.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <GLES2/gl2.h>

#include <limits>
#include <sstream>

#include "event_handler.h"
//#include "gles2_demo_cc.h"
#include "md5.h"
#include "test_object.h"
#include "core.h"
//#include <nacl/npapi_extensions.h>
#include "npapi_extensions_private.h"

NPNetscapeFuncs* browser;

namespace {

// Properties ------------------------------------------------------------------

enum {
  ID_PROPERTY_PROPERTY = 0,
  ID_PROPERTY_TEST_OBJECT,
  NUM_PROPERTY_IDENTIFIERS
};

static NPIdentifier plugin_property_identifiers[NUM_PROPERTY_IDENTIFIERS];
static const NPUTF8*
    plugin_property_identifier_names[NUM_PROPERTY_IDENTIFIERS] = {
  "property",
  "testObject",
};

// Methods ---------------------------------------------------------------------

enum {
  ID_TEST_GET_PROPERTY = 0,
  ID_SET_TEXT_BOX,
  ID_MODULE_READY,
  ID_REPORT_CHECKSUM,
  ID_IS_CHECKSUM_CHECK_SUCCESS,
  ID_MAIN_LOOP,
  NUM_METHOD_IDENTIFIERS = 6,
};

static NPIdentifier plugin_method_identifiers[NUM_METHOD_IDENTIFIERS];
static const NPUTF8* plugin_method_identifier_names[NUM_METHOD_IDENTIFIERS] = {
  "testGetProperty",
  "setTextBox",
  "moduleReady",
  "reportChecksum",
  "isChecksumCheckSuccess",
  "MainLoop",
};

void EnsureIdentifiersInitialized() {
  //////printf("plugin_object.cc -> void EnsureIdentifiersInitialized() {\n");
  static bool identifiers_initialized = false;
  if (identifiers_initialized)
    return;

  browser->getstringidentifiers(plugin_property_identifier_names,
                                NUM_PROPERTY_IDENTIFIERS,
                                plugin_property_identifiers);
  browser->getstringidentifiers(plugin_method_identifier_names,
                                NUM_METHOD_IDENTIFIERS,
                                plugin_method_identifiers);
  identifiers_initialized = true;
}

// Helper functions ------------------------------------------------------------

std::string CreateStringFromNPVariant(const NPVariant& variant) {
  ////printf("pluggin_object.cc -> std::string CreateStringFromNPVariant(const NPVariant& variant) {\n");
  return std::string(NPVARIANT_TO_STRING(variant).UTF8Characters,
                     NPVARIANT_TO_STRING(variant).UTF8Length);
}

bool TestGetProperty(PluginObject* obj,
                     const NPVariant* args, uint32_t arg_count,
                     NPVariant* result) {
  if (arg_count == 0)
    return false;

  NPObject *object;
  browser->getvalue(obj->npp(), NPNVWindowNPObject, &object);

  for (uint32_t i = 0; i < arg_count; i++) {
    assert(NPVARIANT_IS_STRING(args[i]));
    std::string property_string = CreateStringFromNPVariant(args[i]);
    NPIdentifier property_identifier =
        browser->getstringidentifier(property_string.c_str());

    NPVariant variant;
    bool retval = browser->getproperty(obj->npp(), object, property_identifier,
                                       &variant);
    browser->releaseobject(object);

    if (!retval)
      break;

    if (i + 1 < arg_count) {
      assert(NPVARIANT_IS_OBJECT(variant));
      object = NPVARIANT_TO_OBJECT(variant);
    } else {
      *result = variant;
      return true;
    }
  }

  VOID_TO_NPVARIANT(*result);
  return false;
}

// Plugin class functions ------------------------------------------------------

NPObject* PluginAllocate(NPP npp, NPClass* the_class) {
  ////printf("pluggin_object.cc -> NPObject* PluginAllocate(NPP npp, NPClass* the_class) {\n");  
  EnsureIdentifiersInitialized();
  PluginObject* newInstance = new PluginObject(npp);
  return reinterpret_cast<NPObject*>(newInstance);
}

void PluginDeallocate(NPObject* header) {
  ////printf("pluggin_object.cc -> void PluginDeallocate(NPObject* header) {\n");  
  PluginObject* plugin = reinterpret_cast<PluginObject*>(header);
  delete plugin;
}

void PluginInvalidate(NPObject* obj) {
  ////printf("pluggin_object.cc -> void PluginInvalidate(NPObject* obj) {\n");
  
}

bool PluginHasMethod(NPObject* obj, NPIdentifier name) {
  ////printf("pluggin_object.cc -> bool PluginHasMethod(NPObject* obj, NPIdentifier name) {\n");  
  for (int i = 0; i < NUM_METHOD_IDENTIFIERS; i++) {
    if (name == plugin_method_identifiers[i])
      return true;
  }
  return false;
}

bool PluginInvoke(NPObject* header,
                  NPIdentifier name,
                  const NPVariant* args, uint32_t arg_count,
                  NPVariant* result) {
  ////printf("pluggin_object.cc -> bool PluginInvoke(NPObject* header,\n");  
  PluginObject* plugin = reinterpret_cast<PluginObject*>(header);
  
  if (name == plugin_method_identifiers[ID_TEST_GET_PROPERTY]) {
    return TestGetProperty(plugin, args, arg_count, result);
  } else if (name == plugin_method_identifiers[ID_SET_TEXT_BOX]) {
    if (1 == arg_count && NPVARIANT_IS_OBJECT(args[0])) {
      return event_handler->set_text_box(NPVARIANT_TO_OBJECT(args[0]));
    }
  } else if (name == plugin_method_identifiers[ID_MODULE_READY]) {
    INT32_TO_NPVARIANT(1, *result);
    return true;
  } else if (name == plugin_method_identifiers[ID_REPORT_CHECKSUM]) {
    return event_handler->addText(plugin->ReportChecksum().c_str());
  } else if (name == plugin_method_identifiers[ID_IS_CHECKSUM_CHECK_SUCCESS]) {
    BOOLEAN_TO_NPVARIANT(plugin->IsChecksumCheckSuccess(), *result);
    return true;
  } else if (name == plugin_method_identifiers[ID_MAIN_LOOP]) {
    crml::Core::self_->MainLoop();
    // and here we will spin until the game is done.
    return true;
  }
  return false;
}

bool PluginInvokeDefault(NPObject* obj,
                         const NPVariant* args, uint32_t arg_count,
                         NPVariant* result) {
  ////printf("pluggin_object.cc -> bool PluginInvokeDefault(NPObject* obj,\n");
  
  INT32_TO_NPVARIANT(1, *result);
  return true;
}

bool PluginHasProperty(NPObject* obj, NPIdentifier name) {
  ////printf("pluggin_object.cc -> bool PluginHasProperty(NPObject* obj, NPIdentifier name) {\n");
  
  for (int i = 0; i < NUM_PROPERTY_IDENTIFIERS; i++) {
    if (name == plugin_property_identifiers[i])
      return true;
  }
  return false;
}

bool PluginGetProperty(NPObject* obj,
                       NPIdentifier name,
                       NPVariant* result) {
  ////printf("pluggin_object.cc -> bool PluginGetProperty(NPObject* obj,\n");
  return false;
}

bool PluginSetProperty(NPObject* obj,
                       NPIdentifier name,
                       const NPVariant* variant) {
  ////printf("pluggin_object.cc -> bool PluginSetProperty(NPObject* obj,\n");
  return false;
}

NPClass plugin_class = {
  NP_CLASS_STRUCT_VERSION,
  PluginAllocate,
  PluginDeallocate,
  PluginInvalidate,
  PluginHasMethod,
  PluginInvoke,
  PluginInvokeDefault,
  PluginHasProperty,
  PluginGetProperty,
  PluginSetProperty,
};

// Bitmap painting -------------------------------------------------------------

// Ugly gradient filled rectangle.
void DrawSampleBitmap(NPDeviceContext2D* context, int width, int height) {
  ////printf("pluggin_object.cc -> void DrawSampleBitmap(NPDeviceContext2D* context, int width, int height) {\n");
  int stride = context->stride;
  unsigned char* buffer = reinterpret_cast<unsigned char*>(context->region);
  static const int kPixelStride = 4;

  if (0 == height || 0 == width)
    return;

  static const float kVStep = 1.0 / static_cast<float>(height);
  static const float kHStep = 1.0 / static_cast<float>(width);
  static const float kAlphaStep = 1.0 / static_cast<float>(width + height);
  for (int i = 0; i < height; ++i) {
    for (int j = 0; j < width; ++j) {
      int index = i * stride + j * kPixelStride;
      float alpha = 1.0 - (i + j) * kAlphaStep;
      float red = i * kVStep;
      float green = j * kHStep;
      // BGRA, premultiplied alpha.
      buffer[index + 0] = 0x00;
      buffer[index + 1] = static_cast<unsigned char>(green * alpha * 255);
      buffer[index + 2] = static_cast<unsigned char>(red * alpha * 255);
      buffer[index + 3] = static_cast<unsigned char>(alpha * 255);
    }
  }
}

uint32_t HexStringToUInt(std::string hex_str) {
  ////printf("pluggin_object.cc -> uint32_t HexStringToUInt(std::string hex_str) {\n");
  static const int hex_base = 16;
  uint64_t res = strtoul(hex_str.c_str(), NULL, hex_base);
#if __LP64__
  // Long is 64-bits, we have to handle under/overflow ourselves.  Test to see
  // if the result can fit into 32-bits (as signed or unsigned).
  if (static_cast<int32_t>(static_cast<int64_t>(res)) !=
      static_cast<int64_t>(res) &&
      static_cast<uint32_t>(res) != res) {
    res = kuint32max;
  }
#endif
  return static_cast<uint32_t>(res);
}

std::string Get2DImageChecksum(const NPDeviceContext2D* context) {
  ////printf("pluggin_object.cc -> std::string Get2DImageChecksum(const NPDeviceContext2D* context) {\n");
  int row_count = context->dirty.bottom - context->dirty.top;
  int stride = context->dirty.right - context->dirty.left;
  static const int kPixelStride = 4;
  size_t length = row_count * stride * kPixelStride;
  MD5Digest md5_result;   // 128-bit digest
  MD5Sum(context->region, length, &md5_result);
  std::string hex_md5 = MD5DigestToBase16(md5_result);
  // Return the least significant 8 characters (i.e. 4 bytes)
  // of the 32 character hexadecimal result as an int.
  return hex_md5.substr(24);
}

void FlushCallback(NPP instance, NPDeviceContext* context,
                   NPError err, void* user_data) {
}

NPExtensions* extensions = NULL;


// Sine wave similar to one from simple_sources.cc
// F is the desired frequency (e.g. 200), T is sample type (e.g. int16)
template <int F, typename T> void SineWaveCallback(
    NPDeviceContextAudio *context) {

  const size_t n_samples  = context->config.sampleFrameCount;
  const size_t n_channels = context->config.outputChannelMap;
  const double th = 2 * 3.141592653589 * F / context->config.sampleRate;
  // store time value to avoid clicks on buffer boundries
  intptr_t t = (intptr_t)context->config.userData;

  T* buf = reinterpret_cast<T*>(context->outBuffer);
  for (size_t sample = 0; sample < n_samples; ++sample) {
    T value = static_cast<T>(sin(th * t++) * std::numeric_limits<T>::max());
    for (size_t channel = 0; channel < n_channels; ++channel) {
      *buf++ = value;
    }
  }
  context->config.userData = reinterpret_cast<void *>(t);
}

const int32_t kCommandBufferSize = 1024 * 1024;

}  // namespace


// PluginObject ----------------------------------------------------------------

PluginObject::PluginObject(NPP npp)
    : npp_(npp),
      test_object_(browser->createobject(npp, GetTestClass())),
      device2d_(NULL),
      device3d_(NULL),
      pgl_context_(NULL),
      deviceaudio_(NULL) {
  memset(&context_audio_, 0, sizeof(context_audio_));
}

PluginObject::~PluginObject() {
  ////printf("pluggin_object.cc -> PluginObject::~PluginObject() {\n");
  if (pgl_context_)
    Destroy3D();

  browser->releaseobject(test_object_);
}

// static
NPClass* PluginObject::GetPluginClass() {
  ////printf("pluggin_object.cc -> NPClass* PluginObject::GetPluginClass() {\n");
  return &plugin_class;
}

namespace {
void Draw3DCallback(void* data) {
  ////printf("pluggin_object.cc -> void Draw3DCallback(void* data) {\n");
  //crml::Core::Alert("This is where the custom draw call is invoked");
  //crml::Core::self_->Alert("custom draw from a singleton");
  static_cast<PluginObject*>(data)->Draw3D();
}
}

void PluginObject::New(NPMIMEType pluginType,
                       int16_t argc,
                       char* argn[],
                       char* argv[]) {
  ////printf("pluggin_object.cc -> void PluginObject::New(NPMIMEType pluginType,\n");
  // Default to 2D rendering.
  dimensions_ = 2;

  for (int i = 0; i < argc; ++i) {
    if (strcmp(argn[i], "dimensions") == 0)
      dimensions_ = atoi(argv[i]);
  }

  if (!extensions) {
    browser->getvalue(npp_, NPNVPepperExtensions,
                      reinterpret_cast<void*>(&extensions));
    // CHECK(extensions);
  }
  device2d_ = extensions->acquireDevice(npp_, NPPepper2DDevice);
  if (device2d_ == NULL) {
    ////printf("Failed to acquire 2DDevice\n");
    exit(1);
  }

  device3d_ = extensions->acquireDevice(npp_, NPPepper3DDevice);
  if (device3d_ == NULL) {
    ////printf("Failed to acquire 3DDevice\n");
    exit(1);
  }

  deviceaudio_ = extensions->acquireDevice(npp_, NPPepperAudioDevice);
  if (deviceaudio_ == NULL) {
    ////printf("Failed to acquire AudioDevice\n");
    exit(1);
  }
}

void PluginObject::SetWindow(const NPWindow& window) {
  ////printf("pluggin_object.cc -> void PluginObject::SetWindow(const NPWindow& window) {\n");
  width_ = window.width;
  height_ = window.height;

  if (dimensions_ == 2) {
    NPDeviceContext2DConfig config;
    NPDeviceContext2D context;
    NPError err = device2d_->initializeContext(npp_, &config, &context);
    if (err != NPERR_NO_ERROR) {
      ////printf("Failed to initialize 2D context\n");
      exit(1);
    }

    //DrawSampleBitmap(&context, window.width, window.height);

    plugin2d_checksum_ = HexStringToUInt(Get2DImageChecksum(&context));
    err = device2d_->getStateContext(npp_, &context,
        NPExtensionsReservedStateSharedMemoryChecksum,
        reinterpret_cast<intptr_t*>(&device2d_checksum_));
    if (err != NPERR_NO_ERROR) {
      ////printf("Failed to retrieve the 2D context checksum\n");
      exit(1);
    }

    // TODO(brettw) figure out why this cast is necessary, the functions seem
    // to match. Could be a calling convention mismatch?
    NPDeviceFlushContextCallbackPtr callback =
        reinterpret_cast<NPDeviceFlushContextCallbackPtr>(&FlushCallback);
    device2d_->flushContext(npp_, &context, callback, NULL);
  } else {
    if (!pgl_context_){
      Initialize3D();
    }
    
    // Schedule the first call to Draw.
    browser->pluginthreadasynccall(npp_, Draw3DCallback, this);
  }

  /*
  // Audio is only produced on the 2d version, because we embed two in the page.
  if (dimensions_ == 2 && !context_audio_.config.callback) {
    NPDeviceContextAudioConfig cfg;
    cfg.sampleRate       = 44100;
    cfg.sampleType       = NPAudioSampleTypeInt16;
    cfg.outputChannelMap = NPAudioChannelStereo;
    cfg.inputChannelMap  = NPAudioChannelNone;
    cfg.sampleFrameCount = 1024;
    cfg.startThread      = 1;  // Start a thread for the audio producer.
    cfg.flags            = 0;
    cfg.callback         = &SineWaveCallback<200, int16_t>;
    NPError err = deviceaudio_->initializeContext(npp_, &cfg, &context_audio_);
    if (err != NPERR_NO_ERROR) {
      ////printf("Failed to initialize audio context\n");
      exit(1);
    }
  }
  */
}

bool PluginObject::IsChecksumCheckSuccess() {
  //////printf("pluggin_object.cc -> bool PluginObject::IsChecksumCheckSuccess() {\n");
  if (device2d_checksum_ != plugin2d_checksum_)
    return false;
  return true;
}

std::string PluginObject::ReportChecksum() {
  //////printf("pluggin_object.cc -> std::string PluginObject::ReportChecksum() {\n");
  std::ostringstream output;
  if (device2d_checksum_ == plugin2d_checksum_) {
    output << "Checksums matched\n";
  } else {
    output << "ERROR: Failed to match device and plugin checksums\n";
  }
  output << "Device checksum:" << device2d_checksum_ << "\n";
  output << "Plugin checksum:" << plugin2d_checksum_ << "\n";
  return output.str();
}

void PluginObject::Initialize3D() {
  //////printf("pluggin_object.cc -> void PluginObject::Initialize3D() {\n");
  // Initialize a 3D context.
  NPDeviceContext3DConfig config;
  config.commandBufferSize = kCommandBufferSize;
  NPError err = device3d_->initializeContext(npp_, &config, &context3d_);
  if (err != NPERR_NO_ERROR) {
    //////printf("Failed to initialize 3D context\n");
    exit(1);
  }

  // Create a PGL context.
  pgl_context_ = pglCreateContext(npp_, device3d_, &context3d_);

  // Initialize the demo GL state.
  pglMakeCurrent(pgl_context_);
  
  //GLFromCPPInit();
  pglMakeCurrent(NULL);
}

void PluginObject::Destroy3D() {
  //////printf("pluggin_object.cc -> void PluginObject::Destroy3D() {\n");
  // Destroy the PGL context.
  pglDestroyContext(pgl_context_);
  pgl_context_ = NULL;

  // Destroy the Device3D context.
  device3d_->destroyContext(npp_, &context3d_);
}

void PluginObject::Draw3D() {
  //////printf("pluggin_object.cc -> void PluginObject::Draw3D() {\n");
  if (!pglMakeCurrent(pgl_context_) && pglGetError() == PGL_CONTEXT_LOST) {
    Destroy3D();
    Initialize3D();
    pglMakeCurrent(pgl_context_);
  }

  crml::Core::self_->Main3D();
  //glViewport(1, 1, width_, height_);
  //GLFromCPPDraw();
  pglSwapBuffers();
  pglMakeCurrent(NULL);

  // Schedule another call to Draw.
  browser->pluginthreadasynccall(npp_, Draw3DCallback, this);

}
