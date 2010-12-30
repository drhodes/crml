// -*- c++ -*-
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
// _.-{{ crml }}-._
#ifndef ERROR_CC
#define ERROR_CC

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include "./error.h"

namespace crml {
bool Error::DEBUG = true;

Error::Error(ErrString es){  
  err_ = es;
}

/// \return The latest error
ErrString Error::Err(){
  return err_;
}

/// \brief Set the error, if the current error is not OK
/// then report the current error and set the error string
/// \param An error string describing some malfunction.
void Error::Err(ErrString es){
  if (!Ok()) {
    printf("Setting the error string while in an error state!\n");
    ReportErr();
  }
  if (DEBUG == true){
    ReportErr();
  }
  err_ = es;
}

/// \brief Report an error to stdout.
void Error::ReportErr(){  
  if (!Ok())    
    printf("!! %s: Error > %s\n", class_name_.c_str(), err_.c_str());
  else
    printf("!! %s: -OK!- > %s\n", class_name_.c_str(), err_.c_str());
}

void Error::Check(){
  if (!Ok()) {
    ReportErr();
  }        
}

bool Error::Ok(){
  return Err() == OK;
}


/// \brief Convenience function, set the error string and report it.
void Error::SetReportErr(ErrString es){
  Err(es);
  ReportErr();  
}

}       // namespace crml
#endif  // ERROR_CC
