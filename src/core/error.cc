// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.
#ifndef ERROR_CC
#define ERROR_CC

#include <stdio.h>
#include <stdlib.h>

#include <string>
#include "./error.h"

namespace crml {
bool Error::DEBUG = false;

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
    printf("!! %s: -OK!-  > %s\n", class_name_.c_str(), err_.c_str());
}


void Error::Check(){
  if (!Ok()) {
    ReportErr();
  }        
}


/// \brief Convenience function, set the error string and report it.
void Error::SetReportErr(ErrString es){
  Err(es);
  ReportErr();  
}

}       // namespace crml
#endif  // ERROR_CC
