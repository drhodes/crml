#ifndef LOG_MACRO_CC
#define LOG_MACRO_CC

#include <string>
#define Log(x) printf(std::string(std::string(x) + "\n").c_str());

#endif
