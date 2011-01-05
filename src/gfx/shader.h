// -*- c++ -*-
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
// _.-{{crml}}-._

#ifndef SHADER_H_
#define SHADER_H_

#include "../core/error.h"
#include "../core/crmltypes.h"

#include "./glutil.h"

#include <stdlib.h>
#include <stdio.h>

namespace crml {
ERR_(SHADER_ALLOCATE_VERTEX_SHADER_FAILS);
ERR_(SHADER_ALLOCATE_FRAGMENT_SHADER_FAILS);
ERR_(SHADER_COMPILE_VERTEX_SHADER_FAILS);
ERR_(SHADER_COMPILE_FRAGMENT_SHADER_FAILS);
ERR_(SHADER_CREATE_PROGRAM_FAILS);
ERR_(SHADER_LINKING_PROGRAM_FAILS);

class Shader: public Error {
 public:
  explicit Shader() : Error(OK){
    ClassName("Shader");
    texture_ = 0;
    texture_loc_ = -1;
    world_matrix_loc_ = 0;
    vbo_ = 0;
    tex_coord_offset_ = 0;

    // InitShaders();
  }

  GLuint Compile(GLuint shader, std::string err);
  void Link();
  void LoadVertexShader(const char* stash);
  void LoadFragmentShader(const char* stash);
  void CreateProgram();
  void UseProgram();
  void InitShaders();
  
  GLuint VertexShader();
  GLuint FragmentShader();  
  GLuint Program();
  GLuint Texture();
  int TextureLoc();
  GLuint WorldMatrixLoc();
  GLuint Vbo();
  GLsizei TexCoordOffset();

  // private:
  GLuint vertex_shader_;
  GLuint fragment_shader_;
  GLuint program_;
  GLuint texture_;
  int texture_loc_;
  GLuint world_matrix_loc_;
  GLuint vbo_;
  GLsizei tex_coord_offset_;
};

}       // namespace crml
#endif  // SHADER_H_



