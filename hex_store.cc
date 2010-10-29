#ifndef HEX_STORE_CC
#define HEX_STORE_CC

#include <string>
#include <map>

#include "hex_store.h"

namespace scm {
	HexStore::HexStore(){}
	HexStore::~HexStore(){}
		
	/*
	void HexStore::Init(HexMap* hm) {
		if (hm == NULL) {
			throw HEX_STORE_INIT_FAIL;
		}
		//store_ = hm;
	}
	*/
	void HexStore::StoreHex(std::string key, std::string val){		
		store_[key] = val;
	}	

	void HexStore::AppendHex(std::string key, std::string val){		
		try {
			store_[key] += val;
		} catch (...) {
			printf("HexStore:: Trying to append to a nonexistant key:val\n");
			throw HEXSTORE_APPEND_FAIL;
		}
	}

	const char* HexStore::ByteArray(std::string key) {
		return store_[key].c_str();
	}	

}// namespace scm
#endif
