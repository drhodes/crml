// _.-{{ apple-bsd }}-._

#ifndef NATIVE_CLIENT_TESTS_PEPPER_PLUGIN_PLUGIN_OBJECT_H_
#define NATIVE_CLIENT_TESTS_PEPPER_PLUGIN_PLUGIN_OBJECT_H_

#include <nacl/npapi.h>
#include <nacl/npruntime.h>
#include <nacl/npapi_extensions.h>
#include <nacl/npupp.h>
#include <pgl/pgl.h>
#include <string>

extern NPNetscapeFuncs* browser;

class PluginObject {
 public:
  explicit PluginObject(NPP npp);
  ~PluginObject();

  static NPClass* GetPluginClass();

  NPObject* header() { return &header_; }
  NPP npp() const { return npp_; }

  void New(NPMIMEType pluginType, int16_t argc, char* argn[], char* argv[]);
  void SetWindow(const NPWindow& window);
  bool IsChecksumCheckSuccess();
  std::string ReportChecksum();
  void Initialize3D();
  void Destroy3D();
  void Draw3D();
  
 public: // <- Had to chance from private to public.  Don't want to inherit.
  bool InitializeCommandBuffer();

  NPObject header_;
  NPP npp_;
  NPObject* test_object_;
  int dimensions_;

  NPDevice* device2d_;
  NPDevice* device3d_;

  PGLContext pgl_context_;

  NPDevice* deviceaudio_;

  NPDeviceContext3D context3d_;
  NPDeviceContextAudio context_audio_;

  unsigned int device2d_checksum_;
  unsigned int plugin2d_checksum_;

  int width_;
  int height_;
  
 private:
  PluginObject(const PluginObject&);
  void operator=(const PluginObject&);
};


#endif  // NATIVE_CLIENT_TESTS_PEPPER_PLUGIN_PLUGIN_OBJECT_H_
