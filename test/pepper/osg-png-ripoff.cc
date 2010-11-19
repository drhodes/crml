
void png_read_istream(png_structp png_ptr, png_bytep data, png_size_t length) {
  std::istream *stream = (std::istream*)png_get_io_ptr(png_ptr); //Get pointer to istream
  stream->read((char*)data,length); //Read requested amount of data  
}

void readPNGStream(std::istream& fin){
  int trans = PNG_ALPHA;
  pngInfo pInfo;
  pngInfo *pinfo = &pInfo;

  unsigned char header[8];
  png_structp png;
  png_infop   info;
  png_infop   endinfo;
  png_bytep   data;    //, data2;
  png_bytep  *row_p;
  double  fileGamma;

  png_uint_32 width, height;
  int depth, color;
  
  png_uint_32 i;
  png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);

  // Set custom error handlers
  // png_set_error_fn(png, png_get_error_ptr(png), user_error_fn, user_warning_fn);
  info = png_create_info_struct(png);
  endinfo = png_create_info_struct(png);


  fin.read((char*)header,8);  

  if (fin.gcount() == 8 && png_sig_cmp(header, 0, 8) == 0)    
    png_set_read_fn(png,&fin,png_read_istream); //Use custom read function that will get data from istream
  else {
    png_destroy_read_struct(&png, &info, &endinfo);
    printf("File not handled\n");
    return;
  }
 
  png_set_sig_bytes(png, 8);

  // png_read_info is toast.
  png_read_info(png, info);

  return;
  png_get_IHDR(png, info, &width, &height, &depth, &color, NULL, NULL, NULL);


  if (pinfo != NULL) {
    pinfo->Width  = width;
    pinfo->Height = height;
    pinfo->Depth  = depth;
  }

  // png default to big endian, so we'll need to swap bytes if on a little endian machine.
  // if (depth>8 && getCpuByteOrder()==osg::LittleEndian)
  png_set_swap(png);

  
  if (color == PNG_COLOR_TYPE_GRAY || color == PNG_COLOR_TYPE_GRAY_ALPHA) {
    //png_set_gray_to_rgb(png);
  }
  
  if (color&PNG_COLOR_MASK_ALPHA && trans != PNG_ALPHA) {
    png_set_strip_alpha(png);
    color &= ~PNG_COLOR_MASK_ALPHA;
  }

  if (color == PNG_COLOR_TYPE_PALETTE)
    png_set_palette_to_rgb(png);
  if (color == PNG_COLOR_TYPE_GRAY && depth < 8)
    png_set_expand_gray_1_2_4_to_8(png);
  if (png_get_valid(png, info, PNG_INFO_tRNS))
    png_set_tRNS_to_alpha(png);

  // Make sure that files of small depth are packed properly.
  if (depth < 8)
    png_set_packing(png);
  

  /*--GAMMA--*/
  //    checkForGammaEnv();
  double screenGamma = 2.2 / 1.0;
  if (png_get_gAMA(png, info, &fileGamma))
    png_set_gamma(png, screenGamma, fileGamma);
  else
    png_set_gamma(png, screenGamma, 1.0/2.2);

  png_read_update_info(png, info);
  
  data = (png_bytep) new unsigned char [png_get_rowbytes(png, info)*height];
  row_p = new png_bytep [height];

  bool StandardOrientation = true;
  for (i = 0; i < height; i++)
  {
    if (StandardOrientation)
      row_p[height - 1 - i] = &data[png_get_rowbytes(png, info)*i];
    else
      row_p[i] = &data[png_get_rowbytes(png, info)*i];
  }

  png_read_image(png, row_p);
  delete [] row_p;
  png_read_end(png, endinfo);
  
  GLenum pixelFormat = 0;
  GLenum dataType = depth<=8?GL_UNSIGNED_BYTE:GL_UNSIGNED_SHORT;
  switch(color)
  {
    case(PNG_SOLID): pixelFormat = GL_LUMINANCE; break;
    case(PNG_ALPHA): pixelFormat = GL_ALPHA; break;
    case(PNG_COLOR_TYPE_GRAY): pixelFormat =GL_LUMINANCE ; break;
    case(PNG_COLOR_TYPE_GRAY_ALPHA): pixelFormat = GL_LUMINANCE_ALPHA; break;
    case(PNG_COLOR_TYPE_RGB): pixelFormat = GL_RGB; break;
    case(PNG_COLOR_TYPE_PALETTE): pixelFormat = GL_RGB; break;
    case(PNG_COLOR_TYPE_RGB_ALPHA): pixelFormat = GL_RGBA; break;
    default: break;                
  }

  if (pixelFormat == GL_RGB && png_get_channels(png, info) == 4)
    pixelFormat = GL_RGBA;
  
  int internalFormat = pixelFormat;

  png_destroy_read_struct(&png, &info, &endinfo);
}  
