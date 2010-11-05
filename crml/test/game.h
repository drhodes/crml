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
#include "./error.h"

namespace scm {
  ERR_(GAME_NULL_PLUGIN);
  ERR_(GAME_NULL_EVENTHANDLER);
  ERR_(GAME_NULL_DISPLAY);
  ERR_(GAME_NULL_CONTEXT_2D);
  ERR_(GAME_NULL_NPP);
  ERR_(GAME_OK);
  ERR_(GAME_UNKNOWN);
  ERR_(GAME_NULL_CONTEXT_BUFFER);

  class Game:
  public PluginObject, public Error {
   public:
    explicit Game(NPP npp) : PluginObject(npp), Error(GAME_OK) {
      ClassName("Game");
    }
    ~Game();

    //void Init();
    void RegisterDevice2D();
    void RegisterEvent(EventHandler* eh);
    void RegisterHexStore();
    void RegisterPlugin(PluginObject* po);
    void RegisterContext2D(NPDeviceContext2D* ctx);

    void RegisterLua();
    void LuaClose();

    void SetWindow(const NPWindow& npw);
    void Wipe();
    void DrawSampleBitmap();
    void DrawTrashMe();

    void DrawSampleBitmap2(NPDeviceContext2D* context, int width, int height);
    
    virtual bool Ok();  // Is the object in a OK state?
   private:    
    lua_State* lua_;
    Event* event_;
    unsigned int* pixels_;
    // ScmDisplay* display_;

    EventHandler* event_handler_;
    NPDevice* device2d_;
    //int width_;
    //int height_;
    NPP npp_;
    PluginObject* plugin_;
    NPDeviceContext2D* context2d_;
  };

}  // namespace scm
#endif  // GAME_H_
