// Copyright 2010 <Derek A. Rhodes>

#ifndef RECT_CC
#define RECT_CC

#include "./rect.h"

namespace crml {

Rect::Rect(){
  topleft_ = Vector(0, 0);
  bottomright_ = Vector(0, 0);
}

Rect::Rect(int x1, int y1, int x2, int y2){
  topleft_ = Vector(x1, y1);
  bottomright_ = Vector(x2, y2);
}

Rect::Rect(Vector v1, Vector v2){
  topleft_ = v1;
  bottomright_ = v2;
}

Rect::Rect(const Rect& r) {
  topleft_ = r.topleft_;
  bottomright_ = r.bottomright_;
}

void Rect::StretchLeft(int n){
  topleft_.X(Left() - n);
}

void Rect::StretchRight(int n){
  bottomright_.X(Right() + n);
}

void Rect::StretchTop(int n){
  topleft_.Y(Top() - n);
}

void Rect::StretchBottom(int n){
  bottomright_.Y(Bottom() + n);
}

int Rect::Top(){
  return topleft_.Y();
}

int Rect::Bottom(){
  return bottomright_.Y();
}

int Rect::Left(){
  return topleft_.X();
}

int Rect::Right(){
  return bottomright_.X();
}

void Rect::Move(Vector v){
  topleft_.X(v.X());
  bottomright_.X(v.X());
  topleft_.Y(v.Y());
  bottomright_.Y(v.Y());
}

void Rect::Move(int x, int y){
  topleft_.X(x);
  bottomright_.X(x);
  topleft_.Y(y);
  bottomright_.Y(y);
}

void Rect::MoveRel(int x, int y){
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

}       // namespace crml
#endif  // RECT_CC













