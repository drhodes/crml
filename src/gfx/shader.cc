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

#ifndef SHADER_CC
#define SHADER_CC
#include "./shader.h"


namespace crml {

GLuint Shader::Compile(GLuint shader, std::string err){
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
    printf("Error compiling shader: %s\n", log.c_str());
    glDeleteShader(shader);
    SetReportDie(err);
  }
 
  return shader;
}

void Shader::Link(){
  // Link the program
  glAttachShader(program_, vertex_shader_);
  glAttachShader(program_, fragment_shader_);

  glBindAttribLocation(program_, 0, "position_");
  glBindAttribLocation(program_, 1, "tex_coord_0");
  
  glLinkProgram(program_);

  // Check the link status
  GLint linked;
  
  glGetProgramiv(program_, GL_LINK_STATUS, &linked);
  if (linked == 0) {
    char buffer[1024];
    GLsizei length = 0;
    glGetProgramInfoLog(program_, sizeof(buffer), &length, buffer);
    std::string log(buffer, length);
    printf("Error linking program: %s\n", log.c_str());
    glDeleteProgram(program_);
    SetReportDie(SHADER_LINKING_PROGRAM_FAILS);
  }
}

void Shader::CreateProgram() {
  program_ = glCreateProgram();
  if (program_ == 0) {
    SetReportDie(SHADER_CREATE_PROGRAM_FAILS);
  }
}

void Shader::LoadVertexShader(const char* stash){
  CheckGLError("LoadShader", __LINE__);
  GLuint shader = glCreateShader(GL_VERTEX_SHADER);
  if (shader == 0) {
    SetReportDie(SHADER_ALLOCATE_VERTEX_SHADER_FAILS);
  }

  glShaderSource(shader, 1, &stash, NULL);  
  vertex_shader_ = Compile(shader, SHADER_COMPILE_VERTEX_SHADER_FAILS);
}

void Shader::LoadFragmentShader(const char* stash){
  CheckGLError("LoadShader", __LINE__);
  GLuint shader = glCreateShader(GL_FRAGMENT_SHADER);
  if (shader == 0) {
    SetReportDie(SHADER_ALLOCATE_FRAGMENT_SHADER_FAILS);
  }
  
  glShaderSource(shader, 1, &stash, NULL);
  fragment_shader_ = Compile(shader, SHADER_COMPILE_FRAGMENT_SHADER_FAILS);
}

void Shader::InitShaders() {
  CheckGLError("InitShaders", __LINE__);
  CreateProgram();  
  UseProgram();
  
  //glAttachShader(program_, vertex_shader_);
  //glAttachShader(program_, fragment_shader_);

  // Bind crml::Display::g_Position to attribute 0
  // glBindAttribLocation(program_, 0, "crml::Display::g_Position");

  // Bind crml::Display::g_TexCoord0 to attribute 1
  // glBindAttribLocation(program_, 1, "crml::Display::g_TexCoord0");

  Link();

  world_matrix_loc_ = glGetUniformLocation(program_, "worldMatrix");
  texture_loc_ = glGetUniformLocation(program_, "tex");
  glGenBuffers(1, &vbo_);
  glBindBuffer(GL_ARRAY_BUFFER, vbo_);


  // these are coordinate in gl space.
  // 
  static float vertices[] = {
    -1, -1, 0, // bl
    +1, -1, 0, // br
    +1, +1, 0, // ur     
    -1, -1, 0, // bl
    +1, +1, 0, // ur
    -1, +1, 0, // ul
  };
  
  static float texCoords[] = {
    0, 0,
    1, 0,
    1, 1,   
    0, 0,
    1, 1,
    0, 1,
  };
  
  tex_coord_offset_ = sizeof(vertices);
  glBufferData( GL_ARRAY_BUFFER,
                sizeof(vertices) + sizeof(texCoords),
                NULL,
                GL_STATIC_DRAW);  
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  glBufferSubData( GL_ARRAY_BUFFER, tex_coord_offset_,
                   sizeof(texCoords), texCoords);
  CheckGLError("InitShaders", __LINE__);
}

void Shader::UseProgram(){
  glUseProgram(program_);
}


GLuint Shader::VertexShader() { return vertex_shader_;}
GLuint Shader::FragmentShader() { return fragment_shader_;}
GLuint Shader::Program() { return program_;}
int Shader::TextureLoc() { return texture_loc_;}
GLuint Shader::WorldMatrixLoc() { return world_matrix_loc_;}
GLuint Shader::Vbo() { return vbo_;}
GLsizei Shader::TexCoordOffset() { return tex_coord_offset_;}

}       // namespace crml
#endif  // SHADER_CC



