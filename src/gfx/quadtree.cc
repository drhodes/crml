// Copyright 2010 <Derek A. Rhodes>

#ifndef QUADTREE_CC
#define QUADTREE_CC

#include "./quadtree.h"

namespace crml {

Quadtree::~Quadtree(){
  // figure this out soon.
}

void Quadtree::Init(){
  if (tree_ != 0) {
    SetReportErr(QUADTREE_TRYING_TO_INIT_LIVE_TREE);
  }
  
  tree_ = new Node;
  /*
  tree_->q1 = new Node;
  tree_->q2 = new Node;
  tree_->q3 = new Node;
  tree_->q4 = new Node;
  */  
  size_ = 0;    
}

void Quadtree::MinFromBin(Drawer* dwr, Bin& bin) {
  int min_dist = 1<<30;
  Drawer* tmp_dwr = 0;       
  Bin::iterator it;

  if (bin.empty()){
    SetErrReport(QUADTREE_FOUND_EMPTY_BIN);
    // This shouldn't happen because the bin should have been
    // deleted if it is empty.
    return 0;
  }
  
  // look at all the elements in this bin
  for (it = bin.begin(); it != bin.end(); it++){
    int d = dwr->Distance(*it);
    // pick the closest one.
    if (d < min_dist){
      min_dist = d;
      tmp_dwr = *it;
    }
  }
  closest_dwr_ = tmp_dwr;
}

void Quadtree::FindClosest(Drawer* dwr){
  closest_dwr_ = 0;
  Drawer* tmp_dwr, *tq1, *tq2, *tq3, *tq4;

  if (dwr == 0) {
    SetErrReport(QUADTREE_NULL_DRAWER);
    return 0;
  }
  
  // look at all the elements in this bin
  // pick the closest one.  
  MinFromBin(dwr, &bin_);
  tmp_dwr = closest_dwr_;
  
  // look at all the elements on each quadrant's bin.
  // pick the closest one.

  ///////////////////////////////////////////////////////////////////
  //////////////////////////////////////////////////////////////////
  // RETHINK THIS WHOLE THING.
  

  
  if (tree_->q1) {
    MinFromBin(dwr, &tree_->q1.bin);
    tq1 = closest_dwr_;
  }
  if (tree_->q2) {
    MinFromBin(dwr, &tree_->q2.bin);
    tq2 = closest_dwr_;
  }
  if (tree_->q3) {
    MinFromBin(dwr, &tree_->q3.bin);
    tq3 = closest_dwr_;
  }
  if (tree_->q4) {
    MinFromBin(dwr, &tree_->q4.bin);
    tq4 = closest_dwr_;
  }
  
  // if dwr is closer to an element in this bin keep a reference to it.
  // we have found the closest point.
  // 
  // else recurse in to the quad with the closest point.
  // 
}


void Quadtree::InsertDrawer(Drawer* dwr){
  if (size_ == 0) {
    tree_->bin.insert(dwr);
    size_ += 1;
  }
}

  
}       // namespace crml
#endif  // QUADTREE_CC












