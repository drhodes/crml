#include "jslog.cc"
#include <string>

#define log(msg) s->Log(msg);
#define pass(msg) s->Log((modulename + std::string(" -- passed: ") + msg).c_str()); //log(msg);
#define fail(msg) s->Log((std::string("!FAIL!: ") + msg).c_str()); //log(msg);
#define ok(cond, msg) if(cond) { pass(msg); } else { fail(msg); };
