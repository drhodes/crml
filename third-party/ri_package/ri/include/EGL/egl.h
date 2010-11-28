#ifndef __egl_h_
#define __egl_h_

/*------------------------------------------------------------------------
 *
 * OpenVG 1.0.1 Reference Implementation
 * -------------------------------------
 *
 * Copyright (c) 2007 The Khronos Group Inc.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and /or associated documentation files
 * (the "Materials "), to deal in the Materials without restriction,
 * including without limitation the rights to use, copy, modify, merge,
 * publish, distribute, sublicense, and/or sell copies of the Materials,
 * and to permit persons to whom the Materials are furnished to do so,
 * subject to the following conditions: 
 *
 * The above copyright notice and this permission notice shall be included 
 * in all copies or substantial portions of the Materials. 
 *
 * THE MATERIALS ARE PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
 * OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE MATERIALS OR
 * THE USE OR OTHER DEALINGS IN THE MATERIALS.
 *
 *//**
 * \file
 * \brief	EGL 1.2 API.
 *//*-------------------------------------------------------------------*/


/*------------------------------------------------------------------------
 * Platform-independent types.
 *----------------------------------------------------------------------*/

typedef int             EGLint;
typedef int             EGLenum;
typedef unsigned int    EGLBoolean;
typedef int             EGLConfig;
typedef void*           EGLContext;
typedef int             EGLDisplay;
typedef void*           EGLSurface;
typedef unsigned int    EGLClientBuffer;

#if defined(EGL_STATIC_LIBRARY)
#	define EGL_APICALL 
#else
#	if defined(_WIN32) || defined(__VC32__)				/* Win32 */
#		if defined (OPENVG_DLL_EXPORTS)
#			define EGL_APICALL __declspec(dllexport)
#		else
#			define EGL_APICALL __declspec(dllimport)
#		endif
#	elif defined(__APPLE__)
#		define EGL_APICALL extern
#	endif /* defined(_WIN32)... */
#endif /* defined(EGL_STATIC_LIBRARY) */

typedef struct
{
	int				format;		/*VGImageFormat cast to int*/
	int				width;
	int				height;
	int				stride;		/*in bytes*/
	void*			data;
} NativePixmap;

typedef EGLint          NativeDisplayType;
typedef void*           NativeWindowType;
typedef NativePixmap*	NativePixmapType;

/*------------------------------------------------------------------------
 * EGL Enumerants.
 *----------------------------------------------------------------------*/

/* Versioning and extensions */
#define EGL_VERSION_1_0				1
#define EGL_VERSION_1_1				1
#define EGL_VERSION_1_2				1

/* EGL aliases */
#define EGL_FALSE					0
#define EGL_TRUE					1

/* Out-of-band handle values */
/* These values may vary depending on semantics of native concepts */
#define EGL_DEFAULT_DISPLAY			((NativeDisplayType)1)
#define EGL_NO_CONTEXT				((EGLContext)0)
#define EGL_NO_DISPLAY				((EGLDisplay)0)
#define EGL_NO_SURFACE				((EGLSurface)0)

/* Out-of-band attribute value */
#define EGL_DONT_CARE				((EGLint)-1)

/* Errors / GetError return values */
#define EGL_SUCCESS					0x3000
#define EGL_NOT_INITIALIZED			0x3001
#define EGL_BAD_ACCESS				0x3002
#define EGL_BAD_ALLOC				0x3003
#define EGL_BAD_ATTRIBUTE			0x3004
#define EGL_BAD_CONFIG				0x3005
#define EGL_BAD_CONTEXT				0x3006
#define EGL_BAD_CURRENT_SURFACE		0x3007
#define EGL_BAD_DISPLAY				0x3008
#define EGL_BAD_MATCH				0x3009
#define EGL_BAD_NATIVE_PIXMAP		0x300A
#define EGL_BAD_NATIVE_WINDOW		0x300B
#define EGL_BAD_PARAMETER			0x300C
#define EGL_BAD_SURFACE				0x300D
#define EGL_CONTEXT_LOST			0x300E	/* EGL 1.1 - IMG_power_management */

/* Reserved 0x300F-0x301F for additional errors */

/* Config attributes */
#define EGL_BUFFER_SIZE				0x3020
#define EGL_ALPHA_SIZE				0x3021
#define EGL_BLUE_SIZE				0x3022
#define EGL_GREEN_SIZE				0x3023
#define EGL_RED_SIZE				0x3024
#define EGL_DEPTH_SIZE				0x3025
#define EGL_STENCIL_SIZE			0x3026
#define EGL_CONFIG_CAVEAT			0x3027
#define EGL_CONFIG_ID				0x3028
#define EGL_LEVEL					0x3029
#define EGL_MAX_PBUFFER_HEIGHT		0x302A
#define EGL_MAX_PBUFFER_PIXELS		0x302B
#define EGL_MAX_PBUFFER_WIDTH		0x302C
#define EGL_NATIVE_RENDERABLE		0x302D
#define EGL_NATIVE_VISUAL_ID		0x302E
#define EGL_NATIVE_VISUAL_TYPE		0x302F
#define EGL_PRESERVED_RESOURCES		0x3030
#define EGL_SAMPLES					0x3031
#define EGL_SAMPLE_BUFFERS			0x3032
#define EGL_SURFACE_TYPE			0x3033
#define EGL_TRANSPARENT_TYPE		0x3034
#define EGL_TRANSPARENT_BLUE_VALUE	0x3035
#define EGL_TRANSPARENT_GREEN_VALUE	0x3036
#define EGL_TRANSPARENT_RED_VALUE	0x3037
#define EGL_NONE					0x3038	/* Attrib list terminator */
#define EGL_BIND_TO_TEXTURE_RGB		0x3039
#define EGL_BIND_TO_TEXTURE_RGBA	0x303A
#define EGL_MIN_SWAP_INTERVAL		0x303B
#define EGL_MAX_SWAP_INTERVAL		0x303C
#define EGL_LUMINANCE_SIZE			0x303D
#define EGL_ALPHA_MASK_SIZE			0x303E
#define EGL_COLOR_BUFFER_TYPE		0x303F
#define EGL_RENDERABLE_TYPE			0x3040
#define EGL_MATCH_NATIVE_PIXMAP		0x3041	/* Pseudo-attribute (not queryable) */

/* Reserved 0x3041-0x304F for additional config attributes */

/* Config attribute values */
#define EGL_SLOW_CONFIG				0x3050	/* EGL_CONFIG_CAVEAT value */
#define EGL_NON_CONFORMANT_CONFIG	0x3051	/* EGL_CONFIG_CAVEAT value */
#define EGL_TRANSPARENT_RGB			0x3052	/* EGL_TRANSPARENT_TYPE value */
#define EGL_RGB_BUFFER				0x308E	/* EGL_COLOR_BUFFER_TYPE value */
#define EGL_LUMINANCE_BUFFER		0x308F	/* EGL_COLOR_BUFFER_TYPE value */

/* More config attribute values, for EGL_TEXTURE_FORMAT */
#define EGL_NO_TEXTURE				0x305C
#define EGL_TEXTURE_RGB				0x305D
#define EGL_TEXTURE_RGBA			0x305E
#define EGL_TEXTURE_2D				0x305F

/* Config attribute mask bits */
#define EGL_PBUFFER_BIT				0x01	/* EGL_SURFACE_TYPE mask bits */
#define EGL_PIXMAP_BIT				0x02	/* EGL_SURFACE_TYPE mask bits */
#define EGL_WINDOW_BIT				0x04	/* EGL_SURFACE_TYPE mask bits */
#define EGL_OPENGL_ES_BIT			0x01	/* EGL_RENDERABLE_TYPE mask bits */
#define EGL_OPENVG_BIT				0x02	/* EGL_RENDERABLE_TYPE mask bits */
#define EGL_OPENGL_ES2_BIT			0x04	/* EGL_RENDERABLE_TYPE mask bits */

/* QueryString targets */
#define EGL_VENDOR					0x3053
#define EGL_VERSION					0x3054
#define EGL_EXTENSIONS				0x3055
#define EGL_CLIENT_APIS				0x308D

/* QuerySurface / CreatePbufferSurface targets */
#define EGL_HEIGHT					0x3056
#define EGL_WIDTH					0x3057
#define EGL_LARGEST_PBUFFER			0x3058
#define EGL_TEXTURE_FORMAT			0x3080
#define EGL_TEXTURE_TARGET			0x3081
#define EGL_MIPMAP_TEXTURE			0x3082
#define EGL_MIPMAP_LEVEL			0x3083
#define EGL_RENDER_BUFFER			0x3086
#define EGL_COLORSPACE				0x3087
#define EGL_ALPHA_FORMAT			0x3088
#define EGL_HORIZONTAL_RESOLUTION	0x3090
#define EGL_VERTICAL_RESOLUTION		0x3091
#define EGL_PIXEL_ASPECT_RATIO		0x3092
#define EGL_SWAP_BEHAVIOR			0x3093

/* EGL_RENDER_BUFFER values / BindTexImage / ReleaseTexImage buffer targets */
#define EGL_BACK_BUFFER				0x3084
#define EGL_SINGLE_BUFFER			0x3085

/* OpenVG color spaces */
#define EGL_COLORSPACE_sRGB			0x3089	/* EGL_COLORSPACE value */
#define EGL_COLORSPACE_LINEAR		0x308A	/* EGL_COLORSPACE value */

/* OpenVG alpha formats */
#define EGL_ALPHA_FORMAT_NONPRE		0x308B	/* EGL_ALPHA_FORMAT value */
#define EGL_ALPHA_FORMAT_PRE		0x308C	/* EGL_ALPHA_FORMAT value */

/* Constant scale factor by which fractional display resolutions &
 * aspect ratio are scaled when queried as integer values.
 */
#define EGL_DISPLAY_SCALING			10000

/* Unknown display resolution/aspect ratio */
#define EGL_UNKNOWN					((EGLint)-1)

/* Back buffer swap behaviors */
#define EGL_BUFFER_PRESERVED		0x3094	/* EGL_SWAP_BEHAVIOR value */
#define EGL_BUFFER_DESTROYED		0x3095	/* EGL_SWAP_BEHAVIOR value */

/* CreatePbufferFromClientBuffer buffer types */
#define EGL_OPENVG_IMAGE			0x3096

/* QueryContext targets */
#define EGL_CONTEXT_CLIENT_TYPE		0x3097

/* CreateContext attributes */
#define EGL_CONTEXT_CLIENT_VERSION	0x3098

/* BindAPI/QueryAPI targets */
#define EGL_OPENGL_ES_API			0x30A0
#define EGL_OPENVG_API				0x30A1

/* GetCurrentSurface targets */
#define EGL_DRAW					0x3059
#define EGL_READ					0x305A

/* WaitNative engines */
#define EGL_CORE_NATIVE_ENGINE		0x305B

/*------------------------------------------------------------------------
 * EGL Functions.
 *----------------------------------------------------------------------*/

#if defined (__cplusplus)
extern "C" {
#endif

EGL_APICALL EGLint      eglGetError					(void);

EGL_APICALL EGLDisplay  eglGetDisplay				(NativeDisplayType displayID);
EGL_APICALL EGLBoolean  eglInitialize				(EGLDisplay dpy, EGLint* major, EGLint* minor);
EGL_APICALL EGLBoolean  eglTerminate				(EGLDisplay dpy);

EGL_APICALL const char* eglQueryString				(EGLDisplay dpy, EGLint name);

EGL_APICALL EGLBoolean  eglGetConfigs				(EGLDisplay dpy, EGLConfig* configs, EGLint config_size, EGLint* num_config);
EGL_APICALL EGLBoolean  eglChooseConfig				(EGLDisplay dpy, const EGLint* attrib_list, EGLConfig* configs, EGLint config_size, EGLint* num_config);
EGL_APICALL EGLBoolean  eglGetConfigAttrib			(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint* value);

EGL_APICALL EGLSurface  eglCreateWindowSurface		(EGLDisplay dpy, EGLConfig config, NativeWindowType win, const EGLint* attrib_list);
EGL_APICALL EGLSurface  eglCreatePbufferSurface		(EGLDisplay dpy, EGLConfig config, const EGLint* attrib_list);
EGL_APICALL EGLSurface  eglCreatePixmapSurface		(EGLDisplay dpy, EGLConfig config, NativePixmapType pixmap, const EGLint* attrib_list);
EGL_APICALL EGLBoolean  eglDestroySurface			(EGLDisplay dpy, EGLSurface surface);
EGL_APICALL EGLBoolean  eglQuerySurface				(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint* value);

EGL_APICALL EGLBoolean eglSurfaceAttrib				(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value);
EGL_APICALL EGLBoolean eglBindTexImage				(EGLDisplay dpy, EGLSurface surface, EGLint buffer);
EGL_APICALL EGLBoolean eglReleaseTexImage			(EGLDisplay dpy, EGLSurface surface, EGLint buffer);

EGL_APICALL EGLBoolean  eglSwapInterval				(EGLDisplay dpy, EGLint interval);

EGL_APICALL EGLContext  eglCreateContext			(EGLDisplay dpy, EGLConfig config, EGLContext share_list, const EGLint* attrib_list);
EGL_APICALL EGLBoolean  eglDestroyContext			(EGLDisplay dpy, EGLContext ctx);
EGL_APICALL EGLBoolean  eglMakeCurrent				(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx);

EGL_APICALL EGLContext  eglGetCurrentContext		(void);
EGL_APICALL EGLSurface  eglGetCurrentSurface		(EGLint readdraw);
EGL_APICALL EGLDisplay  eglGetCurrentDisplay		(void);
EGL_APICALL EGLBoolean  eglQueryContext				(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint* value);

EGL_APICALL EGLBoolean  eglWaitGL					(void);
EGL_APICALL EGLBoolean  eglWaitNative				(EGLint engine);
EGL_APICALL EGLBoolean  eglSwapBuffers				(EGLDisplay dpy, EGLSurface surface);
EGL_APICALL EGLBoolean  eglCopyBuffers				(EGLDisplay dpy, EGLSurface surface, NativePixmapType target);

EGL_APICALL void (*eglGetProcAddress(const char *procname)) (void);

EGL_APICALL EGLSurface	eglCreatePbufferFromClientBuffer (EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list);
EGL_APICALL EGLBoolean  eglWaitClient				(void);
EGL_APICALL	EGLBoolean	eglBindAPI					(EGLenum api);
EGL_APICALL	EGLenum		eglQueryAPI					(void);

EGL_APICALL	EGLBoolean	eglReleaseThread			(void);

/* Hybrid's extension functions */

/*-------------------------------------------------------------------*//*!
 * \ingroup egli
 * \brief	Sets the way EGL acts when the function eglChooseConfig is called.
 *			EGL specification 1.2 states that the EGL configurations returned
 *			after a succesful call to eglChooseConfig are sorted so that
 *			the configurations with the largest number of total colorbits
 *			is the first element of the list and this is highly unusable
 *			when choosing only one config; therefore in Hybrid Graphics'
 *			implementation you can switch EGL to a mode, where it sorts
 *			the returned configurations so that the first configuration in
 *			the list is the one with the least total colorbits.
 *			(Of course this configuration passes the other tests relating
 *			 to configuration choice parameters. See the EGL specification
 *			 for more information. It can be found on www.khronos.org )
 *
 * \param	useHybridPreference	A boolean variable that states whether the
 *								Hybrid Graphics' configuration sorting
 *								scheme should be used. 
 *								(EGL_TRUE for yes, EGL_FALSE for no)
 *
 * \return	EGL_TRUE on a succesful call, EGL_FALSE if not.
 *			
 * \note	This function can return EGL_FALSE only in a situation
 *			where EGL was not able to allocate a small internal state,
 *			which means that the device has VERY limited - therefore
 *			this function does not raise an EGL error, since the error
 *			in itself is stored in the internal state, whose allocation
 *			failed.
 *//*-------------------------------------------------------------------*/

EGL_APICALL	EGLBoolean eglSetConfigPreferenceHG (EGLBoolean useHybridPreference);

/* functions for use in an OpenVG implementation */
EGL_APICALL void* eglGetCurrentVGContext(void);
EGL_APICALL int   eglIsInUse(void* image);
EGL_APICALL void  eglAcquireMutex(void);
EGL_APICALL void  eglReleaseMutex(void);

#if defined (__cplusplus)
}
#endif

/*----------------------------------------------------------------------*/
#endif /* __egl_h_ */