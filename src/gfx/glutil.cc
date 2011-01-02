#ifndef GLUTIL_CC
#define GLUTIL_CC

#include "./glutil.h"
#include <stdio.h>

namespace crml{

void CheckGLError(const char* func_name, int line_no) {
  GLenum error = GL_NO_ERROR;
  while ((error = glGetError()) != GL_NO_ERROR) {
    printf( "GL Error in %s at line %d: 0x%4x\n",
            func_name, line_no, error);
  }
}


} // namespace crml
#endif // #GLUTIL_CC
