// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.

#ifndef HEX_STORE_CC
#define HEX_STORE_CC

#include <string>
#include <map>
#include "./hex_store.h"
#include "./hexdecode.cc"

namespace scm {
HexStore::HexStore() {}
HexStore::~HexStore() {}


int HexStore::Err() {
  return err_;
}

bool HexStore::Ok() {
  return err_ == HEXSTORE_OK;
}

void HexStore::ReportErr() {
  printf("HexStore: Error >> ");
  switch (err_) {
    case HEXSTORE_OK:
      printf("Everything OK");
      break;
    case HEXSTORE_KEY_ERROR:
      printf("Could not find a key for store_");
      break;
    default :
      printf("Unknown Error");
  }
  printf("\n");
}



void HexStore::Store(std::string key, std::string val) {
  store_[key] = val;
  err_ = HEXSTORE_OK;
}

bool HexStore::EmptyVal(std::string key) {
  return store_.count(key) == 0;
}

int HexStore::ValLength(std::string key) {
  if (EmptyVal(key)) {
    err_ = HEXSTORE_KEY_ERROR;
    return -1;
  }
  err_ = HEXSTORE_OK;
  return store_[key].size();
}

std::string HexStore::GetValue(std::string key) {
  if (EmptyVal(key)) {
    err_ = HEXSTORE_KEY_ERROR;
    return "";
  }
  err_ = HEXSTORE_OK;
  return store_[key];
}

void HexStore::Append(std::string key, std::string val) {
  if (EmptyVal(key)) {
    printf("HexStore:: Trying to append to a nonexistant key:val\n");
    err_ = HEXSTORE_KEY_ERROR;
    return;
  }
  err_ = HEXSTORE_OK;
  store_[key] += val;
}



const char* HexStore::ByteArray(std::string key) {
  if (EmptyVal(key)) {
    err_ = HEXSTORE_KEY_ERROR;
    return NULL;
  }
  err_ = HEXSTORE_OK;
  return hexdecode(store_[key]).c_str();
}

}  // namespace scm

#endif
