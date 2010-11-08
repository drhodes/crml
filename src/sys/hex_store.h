// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.

#ifndef HEX_STORE_H_
#define HEX_STORE_H_

#include <string>
#include <map>

namespace scm {  
  // resource-class/name -> hex encoded binary resource.
  // "png/your-image.png" -> "a037c748b898d9effffff893..."
  typedef std::map<std::string, std::string> HexMap;

  enum HexStoreErr {
    HEXSTORE_OK,
    HEXSTORE_KEY_ERROR,
  };
  
  class HexStore {
 public:
    HexStore();
    ~HexStore();

    // Error specific methods
    bool Ok(); // Is the object in OK state?
    int Err(); // What is the error?
    void ReportErr();
    
    void Store(std::string, std::string);
    int ValLength(std::string);
    bool EmptyVal(std::string);
    void Append(std::string, std::string);
    std::string GetValue(std::string);    
    const char* ByteArray(std::string);

 private:
    int err_;
    HexMap store_;
  };

}  // namespace scm
#endif  // HEX_STORE_H_
