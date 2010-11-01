// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.
#ifndef ERROR_H_
#define ERROR_H_

#include <string>
#include "./error_macro.cc"

namespace scm {
  class Error {
   public:
    Error(ErrString es);
    //virtual ~Error()=0;
    
    // Are we in an OK state?
    virtual bool Ok()=0;

    // What is the error?
    ErrString Err();

    // set the err_ string
    void Err(ErrString es);
    void ReportErr();
    void SetReportErr(ErrString es);

    void ClassName(std::string cn){
      class_name_ = cn;
    }
    
   private:
    std::string err_;
    std::string class_name_;   
  };

}  // namespace scm
#endif  // ERROR_H_                                      
