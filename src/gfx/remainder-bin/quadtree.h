// Copyright 2010 <Derek A. Rhodes>

#ifndef QUADTREE_H_
#define QUADTREE_H_

/*
  Need to request the objects associated with the points

       ?  unbounded tree. it can grow both ways.
       |
  +--+-+-+--+
  |  |   |  |
  ?  ?   ?  ?
  
  +---+---+   
  | 2 | 1 |
  +---+---+
  | 3 | 4 |
  +---+---+
*/

#include "../core/error.h"
#include "./drawer.h"

#include <set>
#include <vector>

namespace crml {
  typedef std::set<Drawer*> Bin;
  
  ERR_(QUADTREE_OK);
  ERR_(QUADTREE_TRYING_TO_INIT_LIVE_TREE);
  ERR_(QUADTREE_FOUND_EMPTY_BIN);
  ERR_(QUADTREE_NULL_DRAWER);
    
  //------------------------------------------------------------------
  class Quadtree : public Error {    
   public:
    explicit Quadtree() :
    Error(QUADTREE_OK) {
      ClassName("Quadtree");
    }
    
    ~Quadtree();
    void MinFromBin(Drawer* dwr, Bin& bin);
    void InsertDrawer(Drawer* dwr);
    void FindClosest(Drawer* dwr);
    void Init();
    
   private:
    struct Node {
      Bin bin_;
      struct Node* q1;
      struct Node* q2;
      struct Node* q3;
      struct Node* q4;
    };

    Node* tree_;
    int size_;

    int closest_dist_;
    Drawer* closest_dwr_;
  };
  
}       // namespace crml
#endif  // QUADTREE_H_












