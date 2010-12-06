// Copyright 2010 <Derek A. Rhodes>

#ifndef TGALOADER_H_
#define TGALOADER_H_

#include "../core/crmlint.h"
#include "../core/error.h"
#include "./color.h"
#include <stdio.h>
#include <vector>

namespace crml {
  enum TgaImageType {    
    TgaNoData = 0,
    TgaUncompressedColorMappedImage = 1,
    TgaUncompressedTrueColorImage = 2,
    TgaUncompressedBWImage = 3,
    TgaRunLengthColorMappedImage = 9,
    TgaRunLengthTrueColorImage = 10,
    TgaRunLengthBWImage = 11
  };

  enum TgaColorMap {
    TgaNoColorMapPresent = 0,
    TgaColorMapPresent = 1
  };
     
  ERR_(TGALOADER_NO_DATA);
  ERR_(TGALOADER_OK);
  ERR_(TGALOADER_INVALID_HEADER);
  ERR_(TGALOADER_COMPRESSION_NOT_SUPPORTED);
  ERR_(TGALOADER_IMAGETYPE_UNDEFINED);
  ERR_(TGALOADER_IMAGEDATA_NOT_FOUND);
  
  class TgaLoader: public Error {
   public:
    explicit TgaLoader() :
    Error(TGALOADER_OK) {
    }
    
    ~TgaLoader();
    
    void LoadFromStash(char* stash, int32 len);
    
    // Header
    void LoadHeader();
    void LoadIdLength();
    void LoadColorMapType();
    void LoadImageType();
    void LoadColorMapSpec();
    void LoadImageSpec();

    TgaImageType GetImageType();
    
    // Image and Color map data

    // (2 bytes): absolute coordinate of lower-left corner
    // for displays where origin is at the lower left
    uint16 XOrigin();    
    uint16 YOrigin();
    uint16 Width();      // width in pixels
    uint16 Height();     // height in pixels
    uint8 Depth();      // bits per pixel
    uint8 Descriptor(); // bits 3-0 give the alpha channel depth, bits 5-4 give direction

    int8 ColorMapLength(); 

    std::vector<Color> PixelVector();
    
    bool Ok();



    
   private:
    std::string stash_;
    uint8 id_length_;          // Length of the image id field
    uint8 color_map_type_;     // Is a color map included?
    uint8 image_type_;          // compression and color types
      
    std::vector<uint8> color_map_spec_;  // describes the color map

    std::vector<uint8> image_spec_;     // image dimensions and format
    uint16 x_, y_;
    uint16 width_, height_;
    uint8 depth_;
    uint8 image_descriptor_;
    
    std::vector<uint8> image_id_;        // Optional field containing identifying information
    std::vector<uint8> color_map_data_;  // Look-up table containing color map data
    std::vector<uint8> image_data_;      // Stored according to the image descriptor
  };
  
}       // namespace crml
#endif  // TGALOADER_H_














