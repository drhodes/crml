// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.

#ifndef HEX_STORE_CC
#define HEX_STORE_CC

#include <string>
#include <map>
#include "./hex_store.h"
#include "./hexdecode.cc"

namespace crml {

HexStore::~HexStore() {}

void HexStore::Store(std::string key, std::string val) {
  store_[key] = val;
  Err(OK);
}

bool HexStore::EmptyVal(std::string key) {
  return store_.count(key) == 0;
}

int HexStore::ValLength(std::string key) {
  if (EmptyVal(key)) {
    Err(HEXSTORE_KEY_ERROR);
    return -1;
  }
  return store_[key].size();
}

std::string HexStore::GetValue(std::string key) {
  if (EmptyVal(key)) {
    Err(HEXSTORE_KEY_ERROR);
    return "";
  }
  return store_[key];
}

void HexStore::Append(std::string key, std::string val) {
  if (EmptyVal(key)) {
    printf("HexStore:: Trying to append to a nonexistant key:val\n");
    Err(HEXSTORE_KEY_ERROR);
    return;
  }
  store_[key] += val;
}

const char* HexStore::ByteArray(std::string key) {
  if (EmptyVal(key)) {
    Err(HEXSTORE_KEY_ERROR);
    return NULL;
  }
  return hexdecode(store_[key]).c_str();
}

}  // namespace scm

#endif
