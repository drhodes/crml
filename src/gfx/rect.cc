// -*- c++ -*-
// _.-{{ crml }}-._

#ifndef RECT_CC
#define RECT_CC

#include <stdio.h>
#include "./rect.h"

namespace crml {
int32 Rect::ID__ = 0;

Rect::Rect(float64 x1, float64 y1, float64 x2, float64 y2) : id__(ID__++) {
  topleft_ = Vector(x1, y1);
  bottomright_ = Vector(x2, y2);
}

Rect::Rect(Vector v1, Vector v2) : id__(ID__++) {
  topleft_ = v1;
  bottomright_ = v2;
}

void Rect::CopyInto(Rect& other){ // rethink this.
  other.Left(Left()); // hesitating on the copy constructer
  other.Right(Right()); // because __id__ can't be copied without messing up the 
  other.Top(Top()); // quick delete.
  other.Bottom(Bottom());
}

void Rect::StretchLeft(float64 n){
  topleft_.X(Left() - n);
}

void Rect::StretchRight(float64 n){
  bottomright_.X(Right() + n);
}

void Rect::StretchTop(float64 n){
  topleft_.Y(Top() - n);
}

void Rect::StretchBottom(float64 n){
  bottomright_.Y(Bottom() + n);
}

float64 Rect::Top(){
  return topleft_.Y();
}

float64 Rect::Bottom(){
  return bottomright_.Y();
}

float64 Rect::Left(){
  return topleft_.X();
}

float64 Rect::Right(){
  return bottomright_.X();
}

Vector Rect::Center() {
  return Vector(Right() - Width()/2, Bottom() - Height()/2);
}

float64 Rect::Width(){
  return Right() - Left();
}

float64 Rect::Height(){
  return Bottom() - Top();
}

void Rect::Top(float64 n){
  topleft_.Y(n);
}

void Rect::Bottom(float64 n){
  bottomright_.Y(n);
}

void Rect::Left(float64 n){
  topleft_.X(n);
}

void Rect::Right(float64 n){
  bottomright_.X(n);
}

void Rect::Move(Vector v){
  topleft_.X(v.X());
  topleft_.Y(v.Y());
  
  bottomright_.X(v.X());
  bottomright_.Y(v.Y());
}

void Rect::Move(float64 x, float64 y){
  float64 h = Height();
  float64 w = Width();  
  topleft_.X(x);
  topleft_.Y(y);
  bottomright_.X( topleft_.X() + w );
  bottomright_.Y( topleft_.Y() + h );  
}

void Rect::MoveRel(float64 x, float64 y){
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

Vector Rect::TopLeft(){
  return topleft_;
}

Vector Rect::TopRight(){
  return Vector(bottomright_.X(), topleft_.Y());
}

Vector Rect::BottomLeft(){
  return Vector(topleft_.X(), bottomright_.Y());
}

Vector Rect::BottomRight(){
  return bottomright_;
}

// some min/max utility functions
// ------------------------------------------------------------------
inline float64 max( float64 a, float64 b){
  if (a >= b)
    return a;
  return b;
}

inline float64 max4( float64 a,
                     float64 b,
                     float64 c,
                     float64 d ){
  return max(max(a, b), max(c, d));  
}

inline float64 min( float64 a, float64 b){
  if (a <= b)
    return a;
  return b;
}

inline float64 min4( float64 a,
                     float64 b,
                     float64 c,
                     float64 d ){
  return min(min(a, b), min(c, d));  
}
// ------------------------------------------------------------------

Rect Rect::BoundingBox(){
  float64 t, b, l, r;
  // find topmost
  t = min4( TopLeft().Y(), TopRight().Y(),
            BottomLeft().Y(), BottomRight().Y() );
  
  // find bottommost
  b = max4( TopLeft().Y(), TopRight().Y(),
            BottomLeft().Y(), BottomRight().Y() );
  
  // find leftmost
  l = min4( TopLeft().X(), TopRight().X(),
            BottomLeft().X(), BottomRight().X() );
  
  // find rightmost
  r = max4( TopLeft().X(), TopRight().X(),
            BottomLeft().X(), BottomRight().X() );

  return Rect(l, t, r, b);  
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
