#ifndef GAME_H
#define GAME_H

#include "event.h"
#include "plugin_object.h"

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
		GameNullNPP,
		GameLuaOK,
		GameOK,
		GameUnknown
	};
	
	class Game : public PluginObject {
	public:
		Game();
		~Game();	

		Game(NPP npp) : PluginObject(npp){
		}

		
		GameErr RegisterNPP();
		GameErr RegisterPlugin(PluginObject*);
		GameErr RegisterEvent(EventHandler*);
		GameErr RegisterDevice2D();
		GameErr SetWindow(const NPWindow&);		
		GameErr RegisterLua();

		void Wipe();
		void DrawSampleBitmap();
		void LuaClose();

		/*
        void* pixels() {
			return context2d_.region;
        }
		*/

	private:
		// THEM / boooooooooooo!
		EventHandler* event_handler_;
		NPDevice* device2d_;
		int width_;
		int height_;
		NPP npp_;		
		PluginObject* plugin_;
		NPDeviceContext2D* context2d_;
              
		// US woot woot woot / dance a little happy dance.

		lua_State* lua_;
		Event* event_;
		unsigned int* pixels_;
		// ScmDisplay* display_;


		/*
		  Layers
		  
		*/
	};
} //namespace scm
#endif

