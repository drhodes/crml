// _.-{{ apple-bsd }}-._

#ifndef NATIVE_CLIENT_TESTS_PEPPER_PLUGIN_EVENT_HANDLER_H_
#define NATIVE_CLIENT_TESTS_PEPPER_PLUGIN_EVENT_HANDLER_H_

#include <nacl/npapi.h>
#include <nacl/npruntime.h>
#include <nacl/npapi_extensions.h>
#include <string>

class EventHandler {
 public:
  explicit EventHandler(NPP npp);
  ~EventHandler();
  bool addText(const char* cstr);
  int handle(void* event);
  bool is_text_box_set();
  bool set_text_box(NPObject* text_box_object);

 private:
  static char* string_duplicate(const char* cstr, size_t* len);
  static void MakeNPVariant(const char* cstr, NPVariant* var);
  std::string EventName(double timestamp, int32_t type);

  NPP npp_;
  NPObject* text_box_;
};

extern EventHandler* event_handler;

#endif  // NATIVE_CLIENT_TESTS_PEPPER_PLUGIN_EVENT_HANDLER_H_
