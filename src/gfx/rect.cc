// -*- c++ -*-
// _.-{{ crml }}-._

#ifndef RECT_CC
#define RECT_CC

#include <stdio.h>
#include "./rect.h"

namespace crml {
// some min/max utility functions
// ------------------------------------------------------------------
inline float64 max( float64 a, float64 b){
  if (a >= b)
    return a;
  return b;
}

inline float64 max4( float64 a, float64 b,
                     float64 c, float64 d ){
  return max(max(a, b), max(c, d));  
}

inline float64 min( float64 a, float64 b){
  if (a <= b)
    return a;
  return b;
}

inline float64 min4( float64 a, float64 b,
                     float64 c, float64 d ){
  return min(min(a, b), min(c, d));  
}

// -------------------------------------------------------------------------
int32 Rect::ID__ = 0;

Rect::Rect(float64 x1, float64 y1, float64 x2, float64 y2) : id__(ID__++) {
  topleft_ = Vector(x1, y1);
  topright_ = Vector(x2, y1);
  bottomleft_ = Vector(x1, y2);
  bottomright_ = Vector(x2, y2);
}

Rect::Rect(Vector v1, Vector v2) : id__(ID__++) {
  topleft_ = v1;
  topright_ = Vector(v2.X(), v1.Y());
  bottomleft_ = Vector(v1.X(), v2.Y());
  bottomright_ = v2;
}

Rect::Rect(Vector v1, Vector v2,
           Vector v3, Vector v4) : id__(ID__++) {
  topleft_ = v1;
  topright_ = v2;
  bottomleft_ = v3;
  bottomright_ = v4;
}

void Rect::CopyInto(Rect& other){ // rethink this.
  other.topleft_ = topleft_;
  other.topright_ = topright_;
  other.bottomleft_ = bottomleft_;
  other.bottomright_ = bottomright_;
}

// the stretches are done with vector scaling multiplication.
// n is a scaling factor, not number of pixels.
void Rect::StretchLeft(float64 n){
  Vector topAug = topleft_.Subtract(topright_).Normalize().Multiply(n);
  Vector botAug = bottomleft_.Subtract(bottomright_).Normalize().Multiply(n);
  topleft_ = topleft_.Add(topAug);
  bottomleft_ = bottomleft_.Add(botAug);  
}

void Rect::StretchRight(float64 n){
  Vector topAug = topright_.Subtract(topleft_).Normalize().Multiply(n);
  Vector botAug = bottomright_.Subtract(bottomleft_).Normalize().Multiply(n);
  topright_ = topright_.Add(topAug);
  bottomright_ = bottomright_.Add(botAug);  
}

void Rect::StretchTop(float64 n){
  Vector leftAug = topleft_.Subtract(bottomleft_).Normalize().Multiply(n);
  Vector rightAug = topright_.Subtract(bottomright_).Normalize().Multiply(n);
  topleft_ = topleft_.Add(leftAug);
  topright_ = topright_.Add(rightAug);
}

void Rect::StretchBottom(float64 n){
  Vector leftAug = bottomleft_.Subtract(topleft_).Normalize().Multiply(n);
  Vector rightAug = bottomright_.Subtract(topright_).Normalize().Multiply(n);
  bottomleft_ = bottomleft_.Add(leftAug);
  bottomright_ = bottomright_.Add(rightAug);
}

float64 Rect::Top(){
  return min4(topleft_.Y(), topright_.Y(), bottomleft_.Y(), bottomright_.Y());
}

float64 Rect::Bottom(){
  return max4(topleft_.Y(), topright_.Y(), bottomleft_.Y(), bottomright_.Y());
}

float64 Rect::Left(){
  return min4(topleft_.X(), topright_.X(), bottomleft_.X(), bottomright_.X());
}

float64 Rect::Right(){
  return max4(topleft_.X(), topright_.X(), bottomleft_.X(), bottomright_.X());
}

Vector Rect::Center() {
  // the average of X of all points, ... same with Y
  float64 x = (topleft_.X() + topright_.X() + bottomleft_.X() + bottomright_.X()) / 4;
  float64 y = (topleft_.Y() + topright_.Y() + bottomleft_.Y() + bottomright_.Y()) / 4;
  return Vector(x, y);
}

float64 Rect::Width(){
  return Right() - Left();
}

float64 Rect::Height(){
  return Bottom() - Top();
}

void Rect::Move(Vector v){
  Vector delta = v.Subtract(topleft_);
  MoveRel(delta);
}

void Rect::Move(float64 x, float64 y){
  Move(Vector(x, y));
}

void Rect::MoveRel(float64 x, float64 y){
  MoveRel(Vector(x, y));
}

void Rect::MoveRel(Vector v){
  topleft_ = topleft_.Add(v);
  topright_ = topright_.Add(v);
  bottomleft_ = bottomleft_.Add(v);
  bottomright_ = bottomright_.Add(v);
}

Vector Rect::TopLeft(){ return topleft_; }
Vector Rect::TopRight(){ return topright_; }
Vector Rect::BottomRight(){ return bottomright_; }
Vector Rect::BottomLeft(){ return bottomleft_; }

void Rect::TopLeft(Vector v) {
  topleft_ = v;
}

void Rect::TopRight(Vector v) {
  topright_ = v;
}

void Rect::BottomLeft(Vector v) {
  bottomleft_ = v;
}

void Rect::BottomRight(Vector v) {
  bottomright_ = v;
}

// ------------------------------------------------------------------

Rect Rect::BoundingBox(){
  return Rect(Left(), Top(), Right(), Bottom());  
}

std::string Rect::ShowRect(){
  char buffer[200];
  sprintf(buffer, "<id: %d |\n tl:%s, \n tr:%s, \n bl:%s, \n br:%s>",
          int(id__),
          topleft_.ShowVector().c_str(),
          topright_.ShowVector().c_str(),
          bottomleft_.ShowVector().c_str(),
          bottomright_.ShowVector().c_str() );
  return std::string(buffer);
}

int32 Rect::Id() {
  return id__;
}

}       // namespace crml
#endif  // RECT_CC
