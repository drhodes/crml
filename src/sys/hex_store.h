// _.-{{crml}}-._
#ifndef HEX_STORE_H_
#define HEX_STORE_H_

#include <string>
#include <map>
#include "../core/error.h"

namespace crml {  
// resource-class/name -> hex encoded binary resource.
// "png/your-image.png" -> "a037c748b898d9effffff893..."
typedef std::map<std::string, std::string> HexMap;

ERR_(HEXSTORE_KEY_ERROR);

class HexStore: public Error {
 public:
  explicit HexStore(): Error(OK) {
    ClassName("HexStore");
  }
  ~HexStore();
  
  // Error specific methods
  void ReportErr();
  
  void Store(std::string, std::string);
  int ValLength(std::string);
  bool EmptyVal(std::string);
  void Append(std::string, std::string);
  std::string GetValue(std::string);    
  const char* ByteArray(std::string);
  
 private:
  HexMap store_;
};

}  // namespace crml
#endif  // HEX_STORE_H_
