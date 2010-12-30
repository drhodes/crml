// -*- c++ -*-
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
Game::~Game() {  
}

/*
void Game::Init(){
  ClassName("Game");
  Err(GAME_OK);
}
*/

inline int MakeRGBA2(int r, int g, int b, int a) {
  return (((a) << 24) | ((r) << 16) | ((g) << 8) | (b));
}

bool Game::Ok() {
  return Err() == GAME_OK;
}

void Game::RegisterLua() {
  LuaClose();

  lua_ = luaL_newstate();
  luaL_dostring(lua_, "a = 10 + 5");
  lua_getglobal(lua_, "a");
  //  int i = lua_tointeger(lua_, -1);
  //  printf("%d\n", i);
  Err(GAME_OK);
}

void Game::LuaClose() {
  if (lua_ != 0) {
    lua_close(lua_);
  }
}

void Game::RegisterPlugin(PluginObject* po) {
  ReportErr();
  if (po == NULL) {
    Err(GAME_NULL_PLUGIN);
    goto fail;
  }
  plugin_ = po;

  //RegisterDevice2D();
  //if (!Ok()) goto fail;

  RegisterLua();
  if (!Ok()) goto fail;

  Log("<-- Registered Plugin");
  Err(GAME_OK);

  //printf("the context is null: %d\n", context2d_ == NULL);
  return;

 fail:
  ReportErr();
}

void Game::RegisterEvent(EventHandler* eh) {
  if (eh == 0) {
    SetReportErr(GAME_NULL_EVENTHANDLER);
    return;
  }

  event_ = new Event;
  eh->Init(event_);

  Log("<-- Registered Event"); 
  Err(GAME_OK);
}
/*
void Game::RegisterDevice2D() {
  device2d_ = plugin_->GetDevice2D();
  Log("<-- RegisterDevice2D");
  Err(GAME_OK);
}
*/
void Game::DrawSampleBitmap2(NPDeviceContext2D* context, int width, int height) {
  printf("void DrawSampleBitmap(NPDeviceContext2D* context, int width, int height) {\n");
  //int stride = context->stride;
  unsigned char* buffer = reinterpret_cast<unsigned char*>(context->region);
  
  if (buffer == NULL){
    SetReportErr(GAME_NULL_CONTEXT_BUFFER);
    exit(1);
  }
  /*  
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
      buffer[index + 0] = 0x00;   /// ITS BARFING RIGHT HERE . WHY?
      buffer[index + 1] = static_cast<unsigned char>(green * alpha * 255);
      buffer[index + 2] = static_cast<unsigned char>(red * alpha * 255);
      buffer[index + 3] = static_cast<unsigned char>(alpha * 255);
    }
  }
  */
  
  //device2d_->flushContext(npp_, context, NULL, NULL);    
}

void Game::RegisterContext2D(NPDeviceContext2D* ctx) {
  if (ctx == 0) {
    SetReportErr(GAME_NULL_CONTEXT_2D);
    return;
  }  
  context2d_ = ctx;
  DrawTrashMe();
  Err(GAME_OK);
}

void Game::DrawTrashMe() {
  printf("!! WIDTH: %d, HEIGHT: %d\n", 1100, 600);
  DrawSampleBitmap2(context2d_, 1100, 600);
}

void Game::SetWindow(const NPWindow& window) {  
  //err_ = GAME_OK;
}

}  // namespace scm
#endif
