

//so First, we validate our stream with the validate function I just mentioned
if (!validate(source)) {
	std::cerr << "ERROR: Data is not valid PNG-data" << std::endl;
    return; //Do your own error recovery/handling here
 }

//Here we create the png read struct. The 3 NULL's at the end can be used
//for your own custom error handling functions, but we'll just use the default.
//if the function fails, NULL is returned. Always check the return values!
png_structp pngPtr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
if (!pngPtr) {
	std::cerr << "ERROR: Couldn't initialize png read struct" << std::endl;
    return; //Do your own error recovery/handling here
 }

//Here we create the png info struct.
//Note that this time, if this function fails, we have to clean up the read struct!
png_infop infoPtr = png_create_info_struct(pngPtr);
if (!infoPtr) {
	std::cerr << "ERROR: Couldn't initialize png info struct" << std::endl;
    png_destroy_read_struct(&pngPtr, (png_infopp)0, (png_infopp)0);
    return; //Do your own error recovery/handling here
 }
