// Copyright 2010 <Derek A. Rhodes>

#ifndef CORE_HPP_
#define CORE_HPP_

namespace crml {
  /// \brief The Core object which wires all subsystems
  ///        and maintains an open channel with javascript.
  class Core {
   public:
    Core();
    ~Core();
    
    /// Initialize an event system    
    InitEvent();
    
   private:
        
  };
  
}       // namespace crml
#endif  // CORE_HPP_



















