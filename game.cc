// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.

#ifndef GAME_CC
#define GAME_CC

#include <stdlib.h>
#include <stdio.h>

#include <string>

#include "./log_macro.cc"
#include "./game.h"
#include "./event.cc"

namespace scm {
//  Game::Game() {}
Game::~Game() {}

inline int MakeRGBA2(int r, int g, int b, int a) {
  return (((a) << 24) | ((r) << 16) | ((g) << 8) | (b));
}

std::string Game::Err() {
  return err_;
}

bool Game::Ok() {
  return err_ == GAME_OK;
}

void Game::ReportErr() {
  printf("!! Game: Error > %s\n", err_.c_str());
}

void Game::RegisterLua() {
  LuaClose();

  lua_ = luaL_newstate();
  luaL_dostring(lua_, "a = 10 + 5");
  lua_getglobal(lua_, "a");
  //  int i = lua_tointeger(lua_, -1);
  //  printf("%d\n", i);
  err_ = GAME_OK;
}

void Game::LuaClose() {
  if (lua_ != 0) {
    lua_close(lua_);
  }
}

void Game::RegisterPlugin(PluginObject* po) {
  if (po == NULL) {
    err_ = GAME_NULL_PLUGIN;
    goto fail;
  }
  plugin_ = po;

  RegisterDevice2D();
  if (!Ok()) goto fail;

  RegisterLua();
  if (!Ok()) goto fail;

  Log("<-- Registered Plugin");
  err_ = GAME_OK;
  return;

 fail:
  ReportErr();
}

void Game::RegisterEvent(EventHandler* eh) {
  if (eh == 0) {
    err_ = GAME_NULL_EVENTHANDLER;
    ReportErr();
    return;
  }

  event_ = new Event;
  eh->Init(event_);

  Log("<-- Registered Event");
  err_ = GAME_OK;
}

void Game::RegisterDevice2D() {
  device2d_ = plugin_->GetDevice2D();
  Log("<-- RegisterDevice2D");
  err_ = GAME_OK;
}

void Game::SetWindow(const NPWindow& window) {
  // This should needs to be completely rethought.
  Log("<-- SetWindow");
  width_ = window.width;
  height_ = window.height;

  NPDeviceContext2DConfig config;
  NPDeviceContext2D context;

  if (device2d_ == 0) {
    Log("<-- SetWindow/device2d was null, bailing.");
    err_ = GAME_NULL_DISPLAY;
    ReportErr();
    return;
  }

  device2d_->initializeContext(npp_, &config, &context);
  NPError error = device2d_->initializeContext(npp_, &config, &context);

  if (error != NPERR_NO_ERROR) {
    Log("Failed to initialize 2D context\n");
    exit(1);
  }

  context2d_ = &context;
  err_ = GAME_OK;
}

}  // namespace scm
#endif
