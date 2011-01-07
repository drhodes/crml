/*  
  -*- c++ -*-
  Copyright (c) 2009 The Chromium Authors. All rights reserved.
  Use of this source code is governed by a BSD-style license that can be
  found in the /crml/license/google-bsd file  
*/  

#include <math.h>
#include <stdio.h>
#include <GLES2/gl2.h>
#include <string>
#include <vector>
#include <cstring>
#include <iostream>
#include <sstream>

#include <crml-core.h>
#include <crml-win.h>
#include <crml-sys.h>
#include <crml-evt.h>
#include <crml-gfx.h>

namespace {

void CheckGLError2(const char* func_name, int line_no) {
#ifndef NDEBUG
  GLenum error = GL_NO_ERROR;
  while ((error = glGetError()) != GL_NO_ERROR) {
    printf("GL Error in %s at line %d: 0x%4x\n",
        func_name, line_no, error);
  }
#endif
}

GLuint LoadShaderFromStash(GLenum type, const char* stash) {
CheckGLError2("LoadShader", __LINE__);
  GLuint shader = glCreateShader(type);
  if (shader == 0) {
    return 0;
  }
  
  glShaderSource(shader, 1, &stash, NULL);
   
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
    return 0;
  }
  return shader;
}
 
GLuint LoadShader(GLenum type, const char* shaderSrc) {
  //printf("gles2_demo_cc.cc -> GLuint LoadShader(GLenum type, const char* shaderSrc) {\n");
  CheckGLError2("LoadShader", __LINE__);
  GLuint shader = glCreateShader(type);
  if (shader == 0) {
    return 0;
  }
  
  // Load the shader source  
  glShaderSource(shader, 1, &shaderSrc, NULL);   
  
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
    return 0;
  }
  
  return shader;
}

void InitShaders() {
  //printf("gles2_demo_cc.cc -> void InitShaders() {\n");

  CheckGLError2("InitShaders", __LINE__);

  GLuint vertexShader = LoadShaderFromStash(GL_VERTEX_SHADER, txt__gl_v_shader);
  GLuint fragmentShader = LoadShaderFromStash(GL_FRAGMENT_SHADER, txt__gl_f_shader);

  // Create the program object
  GLuint programObject = glCreateProgram();
  if (programObject == 0) {
    printf("Creating program failed\n");
    return;
  }
  
  glAttachShader(programObject, vertexShader);
  glAttachShader(programObject, fragmentShader);

  // Bind crml::Display::g_Position to attribute 0
  glBindAttribLocation(programObject, 0, "crml::Display::g_Position");

  // Bind crml::Display::g_TexCoord0 to attribute 1
  glBindAttribLocation(programObject, 1, "crml::Display::g_TexCoord0");

  // Link the program
  glLinkProgram(programObject);

  // Check the link status
  GLint linked;

  glGetProgramiv(programObject, GL_LINK_STATUS, &linked);
  if (linked == 0) {
    char buffer[1024];
    GLsizei length = 0;
    glGetProgramInfoLog(programObject, sizeof(buffer), &length, buffer);
    std::string log(buffer, length);
    printf("Error linking program: %s\n", log.c_str());
    glDeleteProgram(programObject);
    return;
  }
  
  crml::Display::g_programObject = programObject;
  crml::Display::g_worldMatrixLoc = glGetUniformLocation(crml::Display::g_programObject, "worldMatrix");
  crml::Display::g_textureLoc = glGetUniformLocation(crml::Display::g_programObject, "tex");
  glGenBuffers(1, &crml::Display::g_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, crml::Display::g_vbo);

  /*
      0.25,  0.75, 0.0,
     -0.75,  0.75, 0.0,
     -0.75, -0.25, 0.0,
      0.25,  0.75, 0.0,
     -0.75, -0.25, 0.0,
      0.25, -0.25, 0.0,
  };
  static float texCoords[] = {
    1.0, 1.0,
    0.0, 1.0,
    0.0, 0.0,
    1.0, 1.0,
    0.0, 0.0,
    1.0, 0.0,
  };
*/
  
  static float vertices[] = {
    /* bl */ -1, -1, 0,
    /* br */ 1, -1, 0,
    /* ur */ 1, 1, 0,
    
    /* bl */ -1, -1, 0,
    /* ur */ 1, 1, 0,
    /* ul */ -1, 1, 0,
  };

  static float texCoords[] = {
    0, 0,
    1, 0,
    1, 1,   
    0, 0,
    1, 1,
    0, 1,
  };
  
  crml::Display::g_texCoordOffset = sizeof(vertices);
  glBufferData( GL_ARRAY_BUFFER,
                sizeof(vertices) + sizeof(texCoords),
                NULL,
                GL_STATIC_DRAW);
  glBufferSubData( GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
  glBufferSubData( GL_ARRAY_BUFFER, crml::Display::g_texCoordOffset,
                   sizeof(texCoords), texCoords);
  CheckGLError2("InitShaders", __LINE__);
}



GLuint CreateCheckerboardTexture(uint8* texels, uint16 w, uint16 h) {
  //printf("gles2_demo_cc.cc -> GLuint CreateCheckerboardTexture() {\n");
  CheckGLError2("CreateCheckerboardTexture", __LINE__);

  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  //                                      w  h
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE,
               texels);
  CheckGLError2("CreateCheckerboardTexture", __LINE__);
  return texture;
}

}  // anonymous namespace.

void GLFromCPPInit(uint8* texels, uint16 w, uint16 h) {
  printf("gles2_demo_cc.cc -> void GLFromCPPInit() {\n");
  CheckGLError2("GLFromCPPInit", __LINE__);
  //glClearColor(0.f, 0.f, .7f, 1.f);
  glClearColor(0.2f, 0.2f, 0.2f, 1.f);
  //glClearColor(0.0f, 0.0f, 0.0f, 1.f);
  crml::Display::g_texture = CreateCheckerboardTexture(texels, w, h);
  InitShaders();
  CheckGLError2("GLFromCPPInit", __LINE__);
}




























/*
void GLFromCPPDraw(float scale) {
  //printf("gles2_demo_cc.cc -> void GLFromCPPDraw() {\n");
  const float kPi = 3.1415926535897932384626433832795f;
  
  CheckGLError2("GLFromCPPDraw", __LINE__);
  // TODO(kbr): base the angle on time rather than on ticks
  crml::Display::g_angle = (crml::Display::g_angle + 1) % 360;
  //crml::Display::g_angle = 0;//(crml::Display::g_angle + 1) % 360;`
  // Rotate about the Z axis
  GLfloat rot_matrix[16];
  GLfloat cos_angle = cosf(static_cast<GLfloat>(crml::Display::g_angle) * kPi / 180.0f) / 10.0;
  GLfloat sin_angle = sinf(static_cast<GLfloat>(crml::Display::g_angle) * kPi / 180.0f);

  // OpenGL matrices are column-major
  //printf("scale: %f", scale);
  
  rot_matrix[0] = scale * cos_angle;
  rot_matrix[1] = -sin_angle;
  rot_matrix[2] = 0.0f;
  rot_matrix[3] = 0.0f;
  
  rot_matrix[4] = sin_angle;
  rot_matrix[5] = scale * cos_angle;
  rot_matrix[6] = 0.0f;
  rot_matrix[7] = 0.0f;
  
  rot_matrix[8] =  0.0f;
  rot_matrix[9] =  0.0f;
  rot_matrix[10] = scale;
  rot_matrix[11] = 0.0f;
  
  rot_matrix[12] = 0.0f;
  rot_matrix[13] = 0.0f;
  rot_matrix[14] = 0.0f;
  rot_matrix[15] = 1.0f;

  // enable transparency.
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  // Note: the viewport is automatically set up to cover the entire Canvas.
  // Clear the color buffer
  glClear(GL_COLOR_BUFFER_BIT);
  CheckGLError2("GLFromCPPDraw", __LINE__);

  // Use the program object
  glUseProgram(crml::Display::g_programObject);
  CheckGLError2("GLFromCPPDraw", __LINE__);
  
  // Set up the model matrix
  glUniformMatrix4fv(crml::Display::g_worldMatrixLoc, 1, GL_FALSE, rot_matrix);

  // Load the vertex data
  glBindBuffer(GL_ARRAY_BUFFER, crml::Display::g_vbo);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,
                        reinterpret_cast<const void*>(crml::Display::g_texCoordOffset));
  CheckGLError2("GLFromCPPDraw", __LINE__);
  
  // Bind the texture to texture unit 0
  glBindTexture(GL_TEXTURE_2D, crml::Display::g_texture);
  CheckGLError2("GLFromCPPDraw", __LINE__);
  
  // Point the uniform sampler to texture unit 0
  glUniform1i(crml::Display::g_textureLoc, 0);
  CheckGLError2("GLFromCPPDraw", __LINE__);
  
  glDrawArrays(GL_TRIANGLES, 0, 6);
  //glDrawArrays(GL_TRIANGLES, 0, 3);
  
  CheckGLError2("GLFromCPPDraw", __LINE__);
  
  glFlush();
}
*/

void GLFromCPPDraw(crml::Sprite& spr) {
  //printf("gles2_demo_cc.cc -> void GLFromCPPDraw() {\n");
  //const float kPi = 3.1415926535897932384626433832795f;
  
  CheckGLError2("GLFromCPPDraw", __LINE__);
  GLfloat rot_matrix[16];
  spr.CopyGlMatrix(rot_matrix);

  // enable transparency.
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  // Note: the viewport is automatically set up to cover the entire Canvas.
  // Clear the color buffer
  glClear(GL_COLOR_BUFFER_BIT);
  CheckGLError2("GLFromCPPDraw", __LINE__);

  // Use the program object
  glUseProgram(crml::Display::g_programObject);
  CheckGLError2("GLFromCPPDraw", __LINE__);
  
  // Set up the model matrix
  glUniformMatrix4fv(crml::Display::g_worldMatrixLoc, 1, GL_FALSE, rot_matrix);

  // Load the vertex data
  glBindBuffer(GL_ARRAY_BUFFER, crml::Display::g_vbo);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,
                        reinterpret_cast<const void*>(crml::Display::g_texCoordOffset));
  CheckGLError2("GLFromCPPDraw", __LINE__);
  
  // Bind the texture to texture unit 0
  glBindTexture(GL_TEXTURE_2D, crml::Display::g_texture);
  CheckGLError2("GLFromCPPDraw", __LINE__);
  
  // Point the uniform sampler to texture unit 0
  glUniform1i(crml::Display::g_textureLoc, 0);
  CheckGLError2("GLFromCPPDraw", __LINE__);
  
  glDrawArrays(GL_TRIANGLES, 0, 6);
  //glDrawArrays(GL_TRIANGLES, 0, 3);
  
  CheckGLError2("GLFromCPPDraw", __LINE__);
  
  glFlush();
}







/*
GLuint CreateCheckerboardTexture() {
  //printf("gles2_demo_cc.cc -> GLuint CreateCheckerboardTexture() {\n");
  CheckGLError2("CreateCheckerboardTexture", __LINE__);
  static unsigned char texels[] = {
    255, 0, 0,
    0, 255, 0,
    123, 123, 255,
    
    0, 0, 255,
    0, 123, 255,
    123, 123, 123,
    
    0, 123, 255,
    123, 123, 13,
    123, 23, 123,
  };
  
  GLuint texture;
  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MACRML::DISPLAY::G_FILTER, GL_NEAREST);
  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 3, 3, 0, GL_RGB, GL_UNSIGNED_BYTE,
               texels);
  CheckGLError2("CreateCheckerboardTexture", __LINE__);
  return texture;
}
*/
