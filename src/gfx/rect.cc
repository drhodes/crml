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

#ifndef RECT_CC
#define RECT_CC

#include <stdio.h>
#include "./rect.h"

namespace crml {
int32 Rect::ID__ = 0;

Rect::Rect() : id__(ID__++) {
  topleft_ = Vector(0, 0);
  bottomright_ = Vector(0, 0);
}

Rect::Rect(int32 x1, int32 y1, int32 x2, int32 y2) : id__(ID__++) {
  topleft_ = Vector(x1, y1);
  bottomright_ = Vector(x2, y2);
}

Rect::Rect(Vector v1, Vector v2) : id__(ID__++) {
  topleft_ = v1;
  bottomright_ = v2;
}

// may be able to scrap this copy constructor.
Rect::Rect(const Rect& r) {
  topleft_ = r.topleft_;
  bottomright_ = r.bottomright_;
  id__ = ID__++;
}

void Rect::CopyInto(Rect& other){ // rethink this.
  other.Left(Left()); // hesitating on the copy constructer
  other.Right(Right()); // because __id__ can't be copied without messing up the 
  other.Top(Top()); // quick delete.
  other.Bottom(Bottom());
}

void Rect::StretchLeft(int32 n){
  topleft_.X(Left() - n);
}

void Rect::StretchRight(int32 n){
  bottomright_.X(Right() + n);
}

void Rect::StretchTop(int32 n){
  topleft_.Y(Top() - n);
}

void Rect::StretchBottom(int32 n){
  bottomright_.Y(Bottom() + n);
}

int32 Rect::Top(){
  return topleft_.Y();
}

int32 Rect::Bottom(){
  return bottomright_.Y();
}

int32 Rect::Left(){
  return topleft_.X();
}

int32 Rect::Right(){
  return bottomright_.X();
}

void Rect::Top(int32 n){
  topleft_.Y(n);
}

void Rect::Bottom(int32 n){
  bottomright_.Y(n);
}

void Rect::Left(int32 n){
  topleft_.X(n);
}

void Rect::Right(int32 n){
  bottomright_.X(n);
}

void Rect::Move(Vector v){
  topleft_.X(v.X());
  bottomright_.X(v.X());
  topleft_.Y(v.Y());
  bottomright_.Y(v.Y());
}

void Rect::Move(int32 x, int32 y){
  topleft_.X(x);
  bottomright_.X(x);
  topleft_.Y(y);
  bottomright_.Y(y);
}

void Rect::MoveRel(int32 x, int32 y){
  topleft_.X(topleft_.X() + x);
  bottomright_.X(bottomright_.X() + x);
  topleft_.Y(topleft_.Y() + y);
  bottomright_.Y(bottomright_.Y() + y);
}

void Rect::MoveRel(Vector v){
  topleft_.X(topleft_.X() + v.X());
  bottomright_.X(bottomright_.X() + v.X());
  topleft_.Y(topleft_.Y() + v.Y());
  bottomright_.Y(bottomright_.Y() + v.Y());
}

const Vector Rect::TopLeft(){
  return topleft_;
}

const Vector Rect::BottomRight(){
  return bottomright_;
}

std::string Rect::ShowRect(){
  char buffer[100];
  sprintf(buffer, "<id: %d | left:%d, top:%d, right:%d, bottom%d>",
          int(id__), int(Left()), int(Top()), int(Right()), int(Bottom()));
  return std::string(buffer);
}

int32 Rect::Id() {
  return id__;
}



}       // namespace crml
#endif  // RECT_CC
