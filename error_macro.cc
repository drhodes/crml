// Copyright 2010 <Derek A. Rhodes> All Rights Reseverd.
#ifndef ERR_CC
#define ERR_CC

#include <string>

namespace scm {

typedef const std::string ErrString;

// Where x is the name of a ERROR_CODE, expands to
// const std::string ERROR_CODE = std::string("ERROR_CODE");
#define ERR_(x) const std::string (x) = std::string(#x);

}       // namespace scm
#endif  // ERR_CC
