// -*- c++ -*-
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
  int32 w, h;
  w = Right() - Left();
  h = Bottom() - Top();  
  topleft_.X(x);
  topleft_.Y(y);
  bottomright_.X( topleft_.X() + w );
  bottomright_.Y( topleft_.Y() + h );  
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
