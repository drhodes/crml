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
// _.-{{ crml }}-._

#ifndef CAMERA_CC
#define CAMERA_CC

#include "./camera.h"

namespace crml {

void Camera::DrawSprite(Sprite* spr){
  if (spr) printf("Drawing %p\n", spr);
 
}

void Camera::DrawLayer(Layer& lyr){  
  Rect view(0,0,0,0);
  CopyInto(view);
  view.StretchRight(lyr.CamDistance() * Width());
  view.StretchBottom(lyr.CamDistance() * Height());

  printf("%s\n", view.ShowRect().c_str());

  // a weird error.
  /*
  std::set<Rect*> nbrs = lyr.GetNeighbors(view);
  std::set<Rect*>::iterator it;

  for ( it=nbrs.begin(); it != nbrs.end(); it++ ) {
    DrawDraw(static_cast<Sprite*>(*it));
  }
  */
}

void Camera::DrawDraw(Sprite* spr) {
  /*
  if (spr == 0) {
    SetReportErr(CAMERA_NULL_SPRITE);
    return;
  }
  
  CheckGLError("GLFromCPPDraw", __LINE__);

  GLfloat mat[16];
  spr->CopyGlMatrix(mat);

  // enable transparency.
  glEnable (GL_BLEND);
  glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  
  // Note: the viewport is automatically set up to cover the entire Canvas.
  // Clear the color buffer
  glClear(GL_COLOR_BUFFER_BIT);
  CheckGLError("GLFromCPPDraw", __LINE__);
  
  // Use the program object
  glUseProgram(spr->Program());
  CheckGLError("GLFromCPPDraw", __LINE__);
  
  // Set up the model matrix
  glUniformMatrix4fv(spr->WorldMatrixLoc(), 1, GL_FALSE, mat);

  // Load the vertex data
  glBindBuffer(GL_ARRAY_BUFFER, spr->Vbo());
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0,
                        reinterpret_cast<const void*>(spr->TexCoordOffset()));
  CheckGLError("GLFromCPPDraw", __LINE__);
  
  // Bind the texture to texture unit 0
  glBindTexture(GL_TEXTURE_2D, spr->Texture());
  CheckGLError("GLFromCPPDraw", __LINE__);
  
  // Point the uniform sampler to texture unit 0
  glUniform1i(spr->TextureLoc(), 0);
  CheckGLError("GLFromCPPDraw", __LINE__);
  
  glDrawArrays(GL_TRIANGLES, 0, 6);
  //glDrawArrays(GL_TRIANGLES, 0, 3);
  
  CheckGLError("GLFromCPPDraw", __LINE__);
  
  glFlush();
  */
}


}       // namespace crml
#endif  // CAMERA_CC






