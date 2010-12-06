// Copyright 2010 <Derek A. Rhodes>

#ifndef TGALOADER_CC
#define TGALOADER_CC

#include "../core/error.h"
#include "./tga_loader.h"
#include "./utility.cc"

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
  LoadImageSpec();
}

// Header
void TgaLoader::LoadHeader(){
  LoadIdLength();
  LoadColorMapType();
  LoadImageType();
  LoadImageSpec();
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

void TgaLoader::LoadImageSpec(){
  uint8 offset = 8;
  uint8 fieldlen = 10;
  
  for(int i=offset; i<offset+fieldlen; i++){
    image_spec_.push_back(uint8(stash_[i]));
  }
    
  // X-origin (2 bytes): absolute coordinate of lower-left corner
  // for displays where origin is at the lower left 
  x_ = glue2bytes( image_spec_[1],
                   image_spec_[0] );  
  DebugNum(x_, "x");
  
  // Y-origin (2 bytes): as for X-origin
  y_ = glue2bytes( image_spec_[3],
                   image_spec_[2] );
  DebugNum(y_, "y");
  
  // Image width (2 bytes): width in pixels
  width_ = glue2bytes( uint8(image_spec_[5]),
                       uint8(image_spec_[4]));  
  DebugNum(width_, "width_");
  
  // Image height (2 bytes): height in pixels
  height_ = glue2bytes( uint8(image_spec_[7]),
                        uint8(image_spec_[6]));  
  DebugNum(height_, "height_");
  
  // Pixel depth (1 byte): bits per pixel
  depth_ = image_spec_[8];
  DebugNum(depth_, "depth_");
  
  // Image descriptor (1 byte): bits 3-0 give the alpha channel depth, bits 5-4 give direction
  image_descriptor_ = image_spec_[9];
  DebugNum(image_descriptor_, "image_descriptor_");
}

void TgaLoader::LoadColorMapSpec(){
  uint8 offset = 3;
  uint8 fieldlen = 5;
  
  for(int i=offset; i<offset+fieldlen; i++){
    color_map_spec_.push_back(uint8(stash_[i]));
  }
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

// Image and Color map data
// (2 bytes): absolute coordinate of lower-left corner
// for displays where origin is at the lower left
uint16 TgaLoader::XOrigin(){
  return x_;
}

uint16 TgaLoader::YOrigin(){
  return y_;
}

uint16 TgaLoader::Width(){
  return width_;
}

uint16 TgaLoader::Height(){
  return height_;
}

uint8 TgaLoader::Depth(){
  return depth_;
}

uint8 TgaLoader::Descriptor(){
  return image_descriptor_;
}

std::vector<Color> TgaLoader::PixelVector(){
  std::vector<Color> s;
  return s;
}

//void TgaLoader::ColorMapLength(){
//}

bool TgaLoader::Ok(){
  return Err() == TGALOADER_OK;
}

}       // namespace crml
#endif  // TGALOADER_CC
