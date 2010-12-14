// -*- c++ -*-
/* _.-{ license management }-._ 
Copyright (c) 2010, Derek A. Rhodes
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice,
   this list of conditions and the following disclaimer.
2. Redistributions in binary form must reproduce the above copyright notice,
   this list of conditions and the following disclaimer in the documentation
   and/or other materials provided with the distribution.
3. Neither the name of the PostgreSQL Global Development Group nor the names
   of its contributors may be used to endorse or promote products derived
   from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
POSSIBILITY OF SUCH DAMAGE.

*/
// _.-{{crml}}-._

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
  ERR_(TGALOADER_INVALID_HEADER);
  ERR_(TGALOADER_COMPRESSION_NOT_SUPPORTED);
  ERR_(TGALOADER_IMAGETYPE_UNDEFINED);
  ERR_(TGALOADER_IMAGEDATA_NOT_FOUND);
  ERR_(TGALOADER_BLACK_AND_WHITE_NOT_YET_SUPPORTED);
  ERR_(TGALOADER_COLORMAPS_NOT_YET_SUPPORTED);
  ERR_(TGALOADER_CORRUPT_PIXELS);

  //------------------------------------------------------------------
  class TgaLoader: public Error {
   public:
    uint8 header_len_;
    
    explicit TgaLoader() :
    Error(OK) {
      header_len_ = 18;
    }
    
    ~TgaLoader();
    
    void LoadFromString(std::string str);
    void LoadFromStash(char* stash, uint32 len);
    
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
    uint8 Depth();       // bits per pixel

    // Still need to implement image wide alpha channel.
    // This isn't a stub but the loader doesn't look at any alpha information except
    // the 4th byte of each pixel.
    uint8 Descriptor();  // bits 3-0 give the alpha channel depth, bits 5-4 give direction
      
    int8 ColorMapLength(); 

    void FillImageId();
    void FillColorMapData();
    void FillImageData();
    
    std::vector<Color> PixelVector();
    
    bool Ok();
    
   private:
    
    std::string stash_;
    uint8 id_length_;       // Length of the image id field
    uint8 color_map_type_;  // Is a color map included?
    uint8 image_type_;      // compression and color types

    std::vector<uint8> color_map_spec_;  // describes the color map
    uint16 color_map_length_;
    uint16 color_map_pixel_size_;
    uint8 color_map_offset_;
    
    std::vector<uint8> image_spec_;  // image dimensions and format
    uint16 x_, y_;                   // origins of first pixel.
    uint16 width_, height_;
    uint8 depth_;
    uint8 image_descriptor_;
       
    std::vector<uint8> image_id_;        // Optional field containing identifying information
    std::vector<uint8> color_map_data_;  // Look-up table containing color map data
    std::vector<uint8> image_data_;      // Stored according to the image descriptor
  };
  
}       // namespace crml
#endif  // TGALOADER_H_














