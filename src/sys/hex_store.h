/* _.-{ license management }-._ 
Copyright (c) 2010, Derek A. Rhodes
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
3. Neither the name of the PostgreSQL Global Development Group nor the names
   of its contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/
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
