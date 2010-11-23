// Copyright 2010 <Derek A. Rhodes>

#ifndef LAYERGROUP_CC
#define LAYERGROUP_CC

#include <vector>

#include "../core/error.h"
#include "./layer_group.h"
#include <stdio.h>
namespace crml {
        
LayerGroup::~LayerGroup(){
}

void LayerGroup::AddTop(std::string layerName){
  Insert(layerName, Layer(), 0);
}

void LayerGroup::AddBottom(std::string layerName){
  Insert(layerName, Layer(), layers_.size());
}

StringVec::iterator LayerGroup::GetLayerNameIter(std::string layerName){
  for (uint i = 0; i<layerNames_.size(); i++){
    if (layerNames_[i] == layerName) {
      return layerNames_.begin() + i;
    }
  }
  SetReportErr(LAYERGROUP_LAYER_DOESNT_EXIST);  
  return layerNames_.end();
}

int LayerGroup::GetLayerNameIndex(std::string layerName){
  for (uint i = 0; i<layerNames_.size(); i++){
    if (layerNames_[i] == layerName) {
      return int(i);
    }
  }
  SetReportErr(LAYERGROUP_LAYER_DOESNT_EXIST);  
  return -1;
}

void LayerGroup::Remove(std::string layerName){
  if (Contains(layerName)){
    SetReportErr(LAYERGROUP_LAYER_DOESNT_EXIST);
  }

  layerNames_.erase(GetLayerNameIter(layerName));
  layers_.erase(layerName);
}

void LayerGroup::Insert(std::string layerName, Layer layer, int listIndex){
  if (Contains(layerName)){
    SetReportErr(LAYERGROUP_LAYER_ALREADY_EXISTS);
  }
    
  layerNames_.insert(layerNames_.begin() + listIndex, layerName);
  layers_[layerName] = layer;
}

Layer* LayerGroup::GetLayer(std::string layerName){
  if (!Contains(layerName)){
    SetReportErr(LAYERGROUP_LAYER_DOESNT_EXIST);
  }
  return &layers_[layerName];
}

bool LayerGroup::Contains(std::string layerName){
  return layers_.count(layerName) != 0;
}

void LayerGroup::Swap(std::string lyr1, std::string lyr2){
  if (!Contains(lyr1)){
    SetReportErr(LAYERGROUP_LAYER_DOESNT_EXIST);
  }
  if (!Contains(lyr2)){
    SetReportErr(LAYERGROUP_LAYER_DOESNT_EXIST);
  }

  // these need to happen together or the layergroup's names
  // will not match the layers in the map.  An indexed map would be great here.
  // consider creating a generic IndexMap type
  
  int i1 = GetLayerNameIndex(lyr1);
  int i2 = GetLayerNameIndex(lyr2);
  layerNames_[i1] = lyr2;
  layerNames_[i2] = lyr1;
        
  Layer tmp1 = layers_[lyr1]; 
  layers_[lyr1] = layers_[lyr2];
  layers_[lyr2] = tmp1; 
}

bool LayerGroup::Ok(){
  return Err() == LAYERGROUP_OK;
}

}       // namespace crml
#endif  // LAYERGROUP_CC






