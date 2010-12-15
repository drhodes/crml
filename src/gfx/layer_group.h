// Copyright 2010 <Derek A. Rhodes>

#ifndef LAYERGROUP_H_
#define LAYERGROUP_H_

#include <vector>
#include <map>

#include "../core/error.h"
#include "./layer.h"

typedef std::vector<std::string> StringVec;

namespace crml {
  ERR_(LAYERGROUP_LAYER_DOESNT_EXIST);
  ERR_(LAYERGROUP_INDEX_OUT_OF_RANGE);
  ERR_(LAYERGROUP_LAYER_ALREADY_EXISTS);
  
  class LayerGroup : public Error {
   public:    
    explicit LayerGroup() :
    Error(OK) {
      ClassName("LayerGroup");
    }

    ~LayerGroup();
    void AddTop(std::string layerName);
    void AddBottom(std::string layerName);
    void Remove(std::string layerName);
    void InsertNew(std::string layerName, int listIndex);
    void Insert(std::string layerName, Layer& layer, int listIndex);
    bool Contains(std::string layerName);
    void Swap(std::string a, std::string b); 
    Layer* GetLayer(std::string layerName);

    StringVec::iterator GetLayerNameIter(std::string layerName);
    int GetLayerNameIndex(std::string layerName);
    
   private:
    StringVec layerNames_;
    std::map<std::string, Layer*> layers_;
        
  };
}       // namespace crml
#endif  // LAYERGROUP_H_

