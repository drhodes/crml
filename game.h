// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.

#ifndef GAME_H_
#define GAME_H_

extern "C" {
#include <lua.h>
#include <lauxlib.h>
#include <lualib.h>
}

#include <string>

#include "./event.h"
#include "./plugin_object.h"
#include "./hex_store.h"
#include "./error_macro.cc"

namespace scm {
  ERR_(GAME_NULL_PLUGIN);
  ERR_(GAME_NULL_EVENTHANDLER);
  ERR_(GAME_NULL_DISPLAY);
  ERR_(GAME_NULL_NPP);
  ERR_(GAME_OK);
  ERR_(GAME_UNKNOWN);
  ERR_(GAME_NUM_ER);

  class Game : public PluginObject {
   public:
    explicit Game(NPP npp)
        : PluginObject(npp) {
      err_ = GAME_OK;
    }
    Game();
    ~Game();
    
    void RegisterDevice2D();
    void RegisterEvent(EventHandler* eh);
    void RegisterHexStore();
    void RegisterPlugin(PluginObject* po);

    void RegisterLua();
    void LuaClose();

    void SetWindow(const NPWindow& npw);
    void Wipe();
    void DrawSampleBitmap();

    bool Ok();  // Is the object in a OK state?
    std::string Err();  // What is the error?
    void ReportErr();

   private:
    std::string err_;
   
    lua_State* lua_;
    Event* event_;
    unsigned int* pixels_;
    // ScmDisplay* display_;

    EventHandler* event_handler_;
    NPDevice* device2d_;
    int width_;
    int height_;
    NPP npp_;
    PluginObject* plugin_;
    NPDeviceContext2D* context2d_;
  };

}  // namespace scm
#endif  // GAME_H_
