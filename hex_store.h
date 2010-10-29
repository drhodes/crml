#ifndef HEX_STORE_H
#define HEX_STORE_H

#include <string>
#include <map>

namespace scm {
	// resource-class/name -> hex encoded binary resource.
	// "png/your-image.png" -> "a037c748b898d9effffff893..."
	typedef std::map<std::string, std::string> HexMap;

	enum HexStoreErr {
		HEXSTORE_OK,
		HEXSTORE_FAIL,
		HEXSTORE_APPEND_FAIL,
		HEXSTORE_INIT_FAIL,
	};

	class HexStore {	
	public:
		HexStore();
		~HexStore();
		
		void Init(HexMap*);
		void StoreHex(std::string, std::string);
		void AppendHex(std::string, std::string);
		const char* ByteArray(std::string); 
	private:
		HexMap store_;
	};


}// namespace scm
#endif
