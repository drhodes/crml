// Copyright 2010 <Derek A. Rhodes>

#ifndef TGALOADER_CC
#define TGALOADER_CC

#include "../core/error.h"
#include "./tga_loader.h"

namespace crml {

TgaLoader::~TgaLoader() {
  //if (stash_)
  //delete stash_;    
}

void TgaLoader::LoadFromStash(char* src, int32 len){
  printf("Buildtime: %s \n", __TIME__);     
  
  stash_.clear();

  int32 i = 0;
  while(i < len) {
    stash_ += char(src[i]);
    i++;
  }

  printf("stash_: %s\n", stash_.c_str());
  printf("Header length is?: %d\n", stash_.size());
   
  uint32 headerLen = 18;
  // if the entire file is smaller than a well formed header
  if (stash_.size() < headerLen) { 
    SetReportErr(TGALOADER_INVALID_HEADER); 
    return;
  }
   
  LoadHeader();
}

// Header
void TgaLoader::LoadHeader(){
  LoadIdLength();
  LoadColorMapType();
  LoadImageType();
  LoadColorMapSpec();
}

void TgaLoader::LoadIdLength(){
  id_length_ = uint8(stash_[0]);
}

void TgaLoader::LoadColorMapType(){
  color_map_type_ = uint8(stash_[1]);
}

void TgaLoader::LoadImageType(){
  image_type_ = uint8(stash_[2]);
}

TgaImageType TgaLoader::GetImageType(){
  switch (image_type_) {
    case 0:
      SetReportErr(TGALOADER_IMAGEDATA_NOT_FOUND);
      return TgaNoData;
    case 1: return TgaUncompressedColorMappedImage;
    case 2: return TgaUncompressedTrueColorImage;
    case 3: return TgaUncompressedBWImage;

      // nacl modules should be gzipped on the wire anyways.
      // so tga RLE compression not supported, yet :).
    case 9:
      SetReportErr(TGALOADER_COMPRESSION_NOT_SUPPORTED);
      return TgaRunLengthColorMappedImage;

    case 10:
      SetReportErr(TGALOADER_COMPRESSION_NOT_SUPPORTED);
      return TgaRunLengthTrueColorImage;

    case 11:
      SetReportErr(TGALOADER_COMPRESSION_NOT_SUPPORTED);
      return TgaRunLengthBWImage;
  }
  SetReportErr(TGALOADER_IMAGETYPE_UNDEFINED);
  return TgaNoData;  
}

void TgaLoader::LoadColorMapSpec(){
  uint8 offset = 3;
  uint8 fieldlen = 5;
  
  for(int i=offset; i<offset+fieldlen; i++){
    color_map_spec_.push_back(uint8(stash_[i]));
  }
}

void TgaLoader::LoadImageSpec(){  
}

// Image and Color map data
// (2 bytes): absolute coordinate of lower-left corner
// for displays where origin is at the lower left

int16 TgaLoader::XOrigin(){
  return 0;
}

int16 TgaLoader::YOrigin(){
  return 0;
}

int16 TgaLoader::Width(){
  return 0;
}

int16 TgaLoader::Height(){
  return 0;
}

uint8 TgaLoader::Depth(){
  return 0;
}

uint8 TgaLoader::Descriptor(){
  return 0;
}


//void TgaLoader::ColorMapLength(){
//}

bool TgaLoader::Ok(){
  return Err() == TGALOADER_OK;
}

}       // namespace crml
#endif  // TGALOADER_CC
