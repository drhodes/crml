// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.
#ifndef ERROR_H_
#define ERROR_H_

#include <string>
#include "./error_macro.cc"

namespace crml {
  ERR_(OK);
  
  class Error {
   public:
    static bool DEBUG;
    static void DebugOn(){ DEBUG = true; }
    static void DebugOff(){ DEBUG = false; }
    
    Error(ErrString es);
    
    /// Are we in an OK state?
    bool Ok();

    // How about creating a stack, and popping them all on err?
    // make a convenient function SetOk().
   
    /// \return the current error
    ErrString Err();
    
    /// set the err_ string
    void Err(ErrString es);
    void ReportErr();
    void SetReportErr(ErrString es);
    void Check();
    
    void ClassName(std::string cn){
      class_name_ = cn;
    }
    
   private:
    std::string err_;
    std::string class_name_;   
  };

}       // namespace crml
#endif  // ERROR_H_                                      
