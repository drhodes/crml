// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.
#ifndef ERROR_CC
#define ERROR_CC

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include "./error_macro.cc"
#include "./error.h"

namespace scm {
Error::Error(ErrString es){
  err_ = es;
}

ErrString Error::Err(){
  return err_;
}

// set the err_ string
// die trying if err_ is not Ok();
void Error::Err(scm::ErrString es){
  if (!Ok()) {
    printf("Setting the error string while in an error state!\n");
    ReportErr();
  }
  err_ = es;
}
  
void Error::ReportErr(){
  printf("!! %s: Error > %s\n", class_name_.c_str(), err_.c_str());
}

void Error::SetReportErr(ErrString es){
  Err(es);
  ReportErr();  
}


}       // namespace scm
#endif  // ERROR_CC
