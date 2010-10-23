#ifndef GAME_H
#define GAME_H

#include "event.h"

extern "C" { 
#include <lua.h> 
#include <lauxlib.h> 
#include <lualib.h> 
} 

namespace scm{
	enum GameErr {
		GameNullPlugin,
		GameNullEventHandler,
		GameNullDisplay,
		GameLuaOK,
		GameOK,
		GameUnknown
	};
	
	class Game {
	public:
		Game();
		~Game();	
		GameErr RegisterNPP();
		GameErr RegisterPlugin(PluginObject*);
		GameErr RegisterEvent(EventHandler*);
		GameErr RegisterDevice2D();
		GameErr SetWindow(const NPWindow&);		

		GameErr RegisterLua();
		void LuaClose();

	private:
		// THEM / boooooooooooo!
		EventHandler* event_handler_;
		NPDevice* device2d_;
		int width_;
		int height_;
		NPP npp_;		
		PluginObject* plugin_;
              
		// US woot woot woot / dance a little happy dance.
		lua_State* lua_;

		Event* event_;

		// ScmDisplay* display_;


		/*
		  Layers
		  
		*/
	};
} //namespace scm
#endif
