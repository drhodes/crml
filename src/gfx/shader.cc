/*
  -*- c++ -*-
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
_.-{{crml}}-._
*/

#ifndef SHADER_CC
#define SHADER_CC
#include "./shader.h"

namespace crml {

void CheckGLError(const char* func_name, int line_no) {
  GLenum error = GL_NO_ERROR;
  while ((error = glGetError()) != GL_NO_ERROR) {
    printf( "GL Error in %s at line %d: 0x%4x\n",
            func_name, line_no, error);
  }
}

void Shader::Compile(GLuint shader, std::string err){
  // Compile the shader
  glCompileShader(shader);
  
  // Check the compile status
  GLint value;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &value);
  if (value == 0) {
    char buffer[1024];
    GLsizei length = 0;
    glGetShaderInfoLog(shader, sizeof(buffer), &length, buffer);
    std::string log(buffer, length);

    SetReportErr(err);
    printf("Error compiling shader: %s\n", log.c_str());
    glDeleteShader(shader);
  }
}

void Shader::LoadVertexShader(const char* stash){
  CheckGLError("LoadShader", __LINE__);
  GLuint shader = glCreateShader(GL_VERTEX_SHADER);
  if (shader == 0) {
    SetReportErr(SHADER_ALLOCATE_VERTEX_SHADER_FAILS);
  }

  glShaderSource(shader, 1, &stash, NULL);  
  Compile(shader, SHADER_COMPILE_VERTEX_SHADER_FAILS);
}

void Shader::LoadFragmentShader(const char* stash){
  CheckGLError("LoadShader", __LINE__);
  GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
  if (shader == 0) {
    SetReportErr(SHADER_ALLOCATE_FRAGMENT_SHADER_FAILS);
  }
  
  glShaderSource(shader, 1, &stash, NULL);
  Compile(shader, SHADER_COMPILE_FRAGMENT_SHADER_FAILS);
}
 
}       // namespace crml
#endif  // SHADER_CC



