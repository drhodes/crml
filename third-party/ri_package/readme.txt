OpenVG 1.0.1 Reference Implementation
-------------------------------------

Copyright (c) 2007 The Khronos Group Inc.

Permission is hereby granted, free of charge, to any person obtaining a
copy of this software and /or associated documentation files
(the "Materials "), to deal in the Materials without restriction,
including without limitation the rights to use, copy, modify, merge,
publish, distribute, sublicense, and/or sell copies of the Materials,
and to permit persons to whom the Materials are furnished to do so,
subject to the following conditions: 

The above copyright notice and this permission notice shall be included 
in all copies or substantial portions of the Materials. 

THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE MATERIALS OR
THE USE OR OTHER DEALINGS IN THE MATERIALS.


Version
-------
Official RI for OpenVG 1.0.1
Released: February 27, 2007


Release Notes
-------------

This release is based on OpenVG 1.0.1 and EGL 1.2 specifications.
This release is Windows-only, although the source code
compiles at least on Mac OS X 10.4 and Cygwin. Project files are
provided for MSVC 6.

This archive contains sources for OpenVG RI, VGU and EGL 1.2. There's
also a precompiled libOpenVG.dll that contains all the API
implementations.

To compile EGL, you must have GLUT and glext.h installed. The graphics
card drivers must support OpenGL 1.2.
http://www.xmission.com/~nate/glut.html
http://oss.sgi.com/projects/ogl-sample/ABI/glext.h


Package Structure
-----------------

bin
  win32
    libOpenVG.dll         OpenVG Windows .dll
    tiger.exe             Windows executable of the Tiger sample
    glut32.dll            GLUT dll against which tiger.exe has been linked
lib
  libOpenVG.lib           MSVC 6 dll import library
  glut32.lib
  glut.h
ri
  openvg_ri.dsp           MSVC 6 project file for libOpenVG.dll
  src                     .cpp and .h -files of the reference implementation
  include                 Public OpenVG and EGL headers
    EGL
      egl.h
    VG
      openvg.h
      vgu.h
samples
  samples.dsw             MSVC 6 workspace file for tiger sample and libOpenVG.dll
  samples.dsp             MSVC 6 project file for tiger.exe
  tiger
    main.c
    tiger.c
    tiger.h
readme.txt
license.txt


Samples
-------

Tiger

The release contains a sample application that renders an image of a
tiger. Note that the sample doesn't start immediately, since it takes
a few seconds to render the image. You can change the pixel zoom
factor by pressing keys 1-4. Mouse moves inside the image. Resizing
the window rerenders the image in the new resolution.


Known Issues
------------

-EGL functionality is incomplete (some functions lack proper error checking, some
 attribs may not be processed, etc.)
-When opening samples.dsw, MSVC may complain about missing Perforce connection. Just
 ignore that.


Changes
-------
February 27, 2007
-changed to MIT open source license.
-bugfix, bugzilla 820: RGB and luminance are now treated as different color spaces.
-bugfix, bugzilla 1094/1095: vgGetParent now returns the input image in case its parent is already destroyed.

December 1, 2006
-bugfix, bugzilla 649: allowed image quality is now taken into account when deciding resampling filter.
-bugfix, bugzilla 650, bad stroking accuracy reported by TK Chan and Mika Tuomi: curve tessellation is now increased from 64 to 256. RI_MAX_EDGES has been increased from 100000 to 262144 to facilitate the increased number of edges.
-bugfix, reported by Chris Wynn, affects I30206: degenerate gradients in repeat mode now render the first stop color instead of the last one.
-changed float to RIfloat, added an option to compile RIfloat into a class to test reduced precision float ops

September 6, 2006
-bugfix, bugzilla 591: CLOSE_PATH followed by a MOVE_TO doesn't produce an extra end cap anymore
-abs values of arc axis lengths are taken only just before rendering
-undefined bits of bitfields are now ignored in the API

September 1, 2006
-changed colorToInt to use mathematical round-to-nearest as recommended by new language in section 3.4.4.
-implemented VG_PAINT_COLOR_RAMP_PREMULTIPLIED
-implemented VG_STROKE_DASH_PHASE_RESET
-implemented new language for filter channelMasks (section 11.2)
-tangents returned by vgPointAlongPath are now normalized
-implemented VG_MAX_GAUSSIAN_STD_DEVIATION, rewrote Gaussian blur code
-vgGetString: if no context, return NULL. VG_VERSION returns the spec version (1.0).
-bugfix, bugzilla 542: vgSeparableConvolve now convolves the edge color with the horizontal kernel and uses that as the edge color for the vertical pass
-ellipse rh and rv are replaced by their absolute values whenever read for processing, the absolute values are not written into the path data

August 18, 2006
-bugfix, M30301: the arguments for vguComputeWarpQuadToQuad were the wrong way around, destination should come before source.
-bugfix, M10102: check for degeneracy in vguComputeWarpSquareToQuad is done before the affinity check so that degenerate affine matrices also produce the bad warp error
-bugfix, bugzilla 491: Chris Wynn's vgComputeWarpSquareToQuad -case. There was a wrong mapping between vertices, (1,1) was mapped to (dx2,dy2)
-bugfix, bugzilla 519: vguPolygon wrong error check. vguPolygon didn't have an error check for the count argument
-bugfix, bugzilla 518: vgGetParameterfv/iv wrong errors. vgGetParametrtfv/iv error checking was for count < 0 instead of count <= 0.
-bugfix, bugzilla 517: wrong cap flag checked in vgPathTransformedBounds
-bugfix, bugzilla 494: egl.h has wrong values for OPENVG_BIT and OPENGL_ES_BIT. Copied the enumerations from the 1.3 egl.h on the Khronos site (OpenKode/egl/egl.h)
-bugfix, bugzilla 492: gradient filter window was biased
-bugfix: when appending paths, there was a loop over coordinates to replace arc axis lengths by their absolute values. However, if the path wasn't empty, the loop accessed wrong coordinates. Fixes: Qingping Zhang's cases 2&3.
-bugfix: image filter write mask was ignored when writing to VG_A_8 images. Fixes: Qingping Zhang's case 13.
-bugfix: if image filter processing format is premultiplied, color channels are clamped to alpha before conversion to destination format
-bugfix: in eglReleaseThread the EGL instance was freed when its reference count reached zero, but the pointer wasn't made NULL, causing the use of uninitialized instance.
-bugfix: vgClearImage didn't clamp the clear color to [0,1] range
-bugfix: a zero-length dash at a path vertex produces a join
-bugfix: vgSetParameter now checks paramType for all object types
-bugfix: convolution filters incorrectly restricted the area read from the source image to the intersection of source and destination image sizes
-bugfix: EGL surface creation now defaults correctly to EGL_COLOR_SPACE_sRGB
-antialiasing is done in the linear color space as the spec recommends.
-image filters clamp the result to [0,1] range.
-Color::pack and Color::convert assert that their input is in [0,1] range
-in case a projective transform is used, VGImageMode is always VG_DRAW_IMAGE_NORMAL
-the default value for VG_FILTER_FORMAT_LINEAR is now VG_FALSE
-added Matrix::isAffine for easy affinity check
-Color::clamp clamps color channels to alpha for premultiplied colors
-VG_BLEND_LIGHTEN: color channels cannot exceed alpha anymore
-RI now supports flexible pixel formats. Any bit depth for RGBA is now supported.
-eglGetProcAddress is now properly implemented, it returns a function pointer for eglSetConfigPreferenceHG extension
-eglQueryString now returns "eglSetConfigPreferenceHG" for EGL_EXTENSIONS
-location of egl.h in RI. use EGL/egl.h, VG/openvg.h, VG/vgu.h
-OpenVG 1.0.1 spec changes
 +use the latest openvg.h
 +2.8: AA happens in linear space
 +3.4: alpha channel depth of zero results in alpha=1 when read
 +4.1: return VG_NO_CONTEXT_ERROR from vgGetError in case no context is current
 +5.1: VG_SCREEN_LAYOUT (default = screen layout of the display)
 +5.2, 5.3: vgSet, vgGet, vgSetParameter, vgGetParameter: handling of invalid values of count
 +5.2.1: new default for VG_FILTER_FORMAT_LINEAR is VG_FALSE
 +8.5.3: get rid of VG_PATH_DATATYPE_INVALID and VG_IMAGE_FORMAT_INVALID enums
 +10.2: get rid of old extension image formats, add the official ones
 +10.5: when reading/writing pixels, clamp color channels to [0, alpha]
 +10.8: when a projective transform is used, always use VG_DRAW_IMAGE_NORMAL mode
 +10.8: VG_DRAW_IMAGE_MULTIPLY: if color spaces of paint and image don't match, no conversion takes place, result is in image color space
 +12.4: clamp the result of additive blend to [0,1]

October 20, 2005
-Gradients are filtered to avoid aliasing
-Subpaths that ended with a close path segment were capped and joined incorrectly. Fixed.
-Alpha mask was allocated per context, not per EGL surface. Fixed.

August 22, 2005
-Updated to spec amendment
-Fixed bugs
-Implemented eglChooseConfig and eglReleaseThread

July 22, 2005
-Updated to 18th July 2005 version of the OpenVG 1.0 spec.
-Updated to 20th July 2005 version of the EGL 1.2 spec.
-Fixed bugs.
-openvg.h, vgu.h and egl.h are now contained in include/vg directory.

May 4, 2005
-Updated to April 26th 2005 version of the OpenVG 1.0 spec.
-Can share images, paths, and paint between contexts.
-Fixed path tangent computation.
-Implemented image filters.
-Fixed bugs.
-Changed directory structure a bit.

March 29, 2005
-Updated to March 28th 2005 version of the OpenVG 1.0 spec.
-Changed rasterizer to use 32 samples per pixel in the high quality
 mode (renders faster at the expense of some aliasing).
-EGL allocates sRGB rendering surfaces.
-Includes GLUT dll against which tiger.exe was linked.

March 24, 2005
-Initial release.
