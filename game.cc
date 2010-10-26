#ifndef GAME_CC
#define GAME_CC

#include <string>
#include <stdlib.h>
#include <stdio.h>
#include "log_macro.cc"

#include "game.h"
#include "event.cc"

namespace scm{	
	//Game::Game(){}
	Game::~Game(){}

	inline int MakeRGBA2(int r, int g, int b, int a) {
        return (((a) << 24) | ((r) << 16) | ((g) << 8) | (b));
    }

	GameErr Game::RegisterLua(){
		if (lua_ != 0){
			LuaClose();
		}

		lua_ = luaL_newstate();      
		luaL_dostring(lua_, "a = 10 + 5"); 
		lua_getglobal(lua_, "a"); 
		int i = lua_tointeger(lua_, -1); 
		printf("%d\n", i); 
		return GameOK;
	}

	void Game::LuaClose(){
		if (lua_ != 0){
			lua_close(lua_);
		}			
	}

	GameErr Game::RegisterPlugin(PluginObject* po){
		if (po == 0) {
			return GameNullPlugin;
		}

		if (RegisterDevice2D() == GameOK)
			Log("<-- RegisterDevice2D");
		if (RegisterLua() == GameOK)
			Log("<-- Registered Lua");		
		if (RegisterNPP() == GameOK)
			Log("<-- Registered NPP");

		Log("<-- Registered Plugin")
		return GameOK;
	}

	GameErr Game::RegisterNPP(){
		npp_ = plugin_->npp();
		if (npp_ == 0)
			return GameNullNPP;
		return GameOK;
	}

	GameErr Game::RegisterEvent(EventHandler* eh){		
		if (eh == 0) {
			return GameNullEventHandler;
		}		
		event_ = new Event;  
		eh->Init(event_);

		Log("<-- Registered Event");
		return GameOK;
	}

	GameErr Game::RegisterDevice2D(){	   		
		if (plugin_ == 0){
			return GameNullPlugin;
		}
		device2d_ = plugin_->GetDevice2D();		
		return GameOK;
	}

	GameErr Game::SetWindow(const NPWindow& window) {
		// This should needs to be completely rethought.
		Log("<-- SetWindow");		
		width_ = window.width;
		height_ = window.height;

		NPDeviceContext2DConfig config;
		NPDeviceContext2D context;
		
		if (device2d_ == 0){
			Log("<-- SetWindow/device2d was null, bailing.");		
			return GameNullDisplay;
		}
		Log("<-- SetWindow::1");		

		device2d_->initializeContext(npp_, &config, &context);
		NPError err = device2d_->initializeContext(npp_, &config, &context);
		
		if (err != NPERR_NO_ERROR) {
			Log("Failed to initialize 2D context\n");
			exit(1);
		}		

		context2d_ = &context;
		//Draw(context2d_, width_, height_);
		return GameOK;
	}

} // namespace scm
#endif
