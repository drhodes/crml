/*------------------------------------------------------------------------
 *
 * EGL 1.2 for Windows and Mac OS X
 * --------------------------------
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
 * \brief	Simple implementation of EGL 1.2 for Windows and Mac OS X, running on GLUT
 * \note	caveats compared to a proper EGL implementation
			- only the default display is supported
			- always renders into the backbuffer and blits it to window (no single buffered rendering)
			- no power management events
			- eglSwapBuffers can copy to any kinds of windows supported by OpenGL/GLUT implementation, but there is no extension describing the supported formats
			- no support for swap interval
			- on Windows, requires installation of GLUT, glext.h and graphics card supporting OpenGL 1.4
			- Mac OS X version 10.4 should contain all necessary components
 * \todo	what happens in egl functions when eglTerminate has been called but the context and surface are still in use?
 *//*-------------------------------------------------------------------*/

#include "egl.h"
#include "openvg.h"
#include "riArray.h"
#include "riMath.h"
#include "riContext.h"
#include "riImage.h"

//==============================================================================================

//TODO proper platform detection
#if defined(_MSC_VER) || defined(__CYGWIN32__)

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

#include <windows.h>
#include <GL/gl.h>
#include <GL/glext.h>
#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>

#define RI_STRNCMP(STR1, STR2, LENGTH) strncmp(STR1, STR2, LENGTH)

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

typedef DWORD ThreadID;
bool areEqual(ThreadID id1, ThreadID id2)
{
	return id1 == id2 ? true : false;
}
ThreadID getCurrentThreadID(void)
{
	return GetCurrentThreadId();
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

static HANDLE mutex = NULL;
static int mutexRefCount = 0;
void initMutex(void)
{
	mutex = CreateMutex(NULL, FALSE, NULL);	//initially not locked
	mutexRefCount = 0;
	RI_ASSERT(mutex != NULL);
}
//acquired mutex cannot be deinited.
//TODO currently the mutex won't be deinited ever.
void deinitMutex(void)
{
	RI_ASSERT(mutex);
	RI_ASSERT(mutexRefCount == 0);
	BOOL ret = CloseHandle(mutex);
	RI_ASSERT(ret);
	RI_UNREF(ret);
}
void eglAcquireMutex(void)
{
	if(!mutex)
		initMutex();
	RI_ASSERT(mutex);
	DWORD ret = WaitForSingleObject(mutex, INFINITE);
	RI_ASSERT(ret != WAIT_FAILED);
	RI_UNREF(ret);
	mutexRefCount++;
}
void eglReleaseMutex(void)
{
	RI_ASSERT(mutex);
	mutexRefCount--;
	RI_ASSERT(mutexRefCount >= 0);
	BOOL ret = ReleaseMutex(mutex);
	RI_ASSERT(ret);
	RI_UNREF(ret);
}

//==============================================================================================

#elif defined __APPLE__

//==============================================================================================

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#include <pthread.h>
#include <sys/errno.h>

#define RI_STRNCMP(STR1, STR2, LENGTH) strncmp(STR1, STR2, LENGTH)

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

typedef pthread_t ThreadID;
bool areEqual(ThreadID id1, ThreadID id2)
{
	return pthread_equal(id1, id2) ? true : false;
}
ThreadID getCurrentThreadID(void)
{
	return pthread_self();
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

static pthread_mutex_t mutex;
static int mutexRefCount = 0;
static bool mutexInitialized = false;
void initMutex(void)
{
	int ret;
	pthread_mutexattr_t attr;
	ret = pthread_mutexattr_init(&attr);	//initially not locked
	RI_ASSERT(!ret);	//check that there aren't any errors
	ret = pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);	//count the number of recursive locks
	RI_ASSERT(!ret);	//check that there aren't any errors
	ret = pthread_mutex_init(&mutex, &attr);
	pthread_mutexattr_destroy(&attr);
	RI_ASSERT(!ret);	//check that there aren't more errors
	RI_UNREF(ret);
	mutexInitialized = true;
}
//acquired mutex cannot be deinited
void deinitMutex(void)
{
	RI_ASSERT(mutexInitialized);
	RI_ASSERT(mutexRefCount == 0);
	int ret = pthread_mutex_destroy(&mutex);
	RI_ASSERT(ret != EINVAL);	//assert that the mutex has been initialized
	RI_ASSERT(ret != EAGAIN);	//assert that the maximum number of recursive locks hasn't been exceeded
	RI_ASSERT(!ret);	//check that there aren't more errors
	RI_UNREF(ret);
}
void eglAcquireMutex(void)
{
	if(!mutexInitialized)
		initMutex();
	RI_ASSERT(mutexInitialized);
	int ret = pthread_mutex_lock(&mutex);
	RI_ASSERT(ret != EINVAL);	//assert that the mutex has been initialized
	RI_ASSERT(ret != EAGAIN);	//assert that the maximum number of recursive locks hasn't been exceeded
	RI_ASSERT(ret != EDEADLK);	//recursive mutexes shouldn't return this
	RI_ASSERT(!ret);	//check that there aren't more errors
	RI_UNREF(ret);
	mutexRefCount++;
}
void eglReleaseMutex(void)
{
	RI_ASSERT(mutexInitialized);
	mutexRefCount--;
	RI_ASSERT(mutexRefCount >= 0);
	int ret = pthread_mutex_unlock(&mutex);
	RI_ASSERT(ret != EPERM);	//assert that the current thread owns the mutex
	RI_ASSERT(!ret);	//check that there aren't more errors
	RI_UNREF(ret);
}
#endif

//==============================================================================================

namespace OpenVGRI
{

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

class Config
{
public:
	Config() : m_desc(Color::formatToDescriptor(VG_sRGBA_8888)), m_configID(0)	{}
	~Config()							{}
	void		set(int r, int g, int b, int a, int l, int bpp, int ID)
	{
		m_desc.redBits = r;
		m_desc.greenBits = g;
		m_desc.blueBits = b;
		m_desc.alphaBits = a;
		m_desc.luminanceBits = l;
		m_desc.alphaShift = 0;
		m_desc.luminanceShift = 0;
		m_desc.blueShift = b ? a : 0;
		m_desc.greenShift = g ? a + b : 0;
		m_desc.redShift = r ? a + b + g : 0;
		m_desc.format = (VGImageFormat)-1;
		m_desc.internalFormat = l ? Color::sLA : Color::sRGBA;
		m_desc.bitsPerPixel = bpp;
		RI_ASSERT(Color::isValidDescriptor(m_desc));
		m_configID = ID;
	}

	//EGL RED SIZE bits of Red in the color buffer
	//EGL GREEN SIZE bits of Green in the color buffer
	//EGL BLUE SIZE bits of Blue in the color buffer
	//EGL ALPHA SIZE bits of Alpha in the color buffer
	//EGL LUMINANCE SIZE bits of Luminance in the color buffer
	Color::Descriptor	m_desc;
	EGLint				m_configID;			//EGL CONFIG ID unique EGLConfig identifier
	//EGL BUFFER SIZE depth of the color buffer (sum of channel bits)
	//EGL ALPHA MASK SIZE number alpha mask bits (always 8)
	//EGL BIND TO TEXTURE RGB boolean True if bindable to RGB textures. (always EGL_FALSE)
	//EGL BIND TO TEXTURE RGBA boolean True if bindable to RGBA textures. (always EGL_FALSE)
	//EGL COLOR BUFFER TYPE enum color buffer type (EGL_RGB_BUFFER, EGL_LUMINANCE_BUFFER)
	//EGL CONFIG CAVEAT enum any caveats for the configuration (always EGL_NONE)
	//EGL DEPTH SIZE integer bits of Z in the depth buffer (always 0)
	//EGL LEVEL integer frame buffer level (always 0)
	//EGL MAX PBUFFER WIDTH integer maximum width of pbuffer (always INT_MAX)
	//EGL MAX PBUFFER HEIGHT integer maximum height of pbuffer (always INT_MAX)
	//EGL MAX PBUFFER PIXELS integer maximum size of pbuffer (always INT_MAX)
	//EGL MAX SWAP INTERVAL integer maximum swap interval (always 1)
	//EGL MIN SWAP INTERVAL integer minimum swap interval (always 1)
	//EGL NATIVE RENDERABLE boolean EGL TRUE if native rendering APIs can render to surface (always EGL_FALSE)
	//EGL NATIVE VISUAL ID integer handle of corresponding native visual (always 0)
	//EGL NATIVE VISUAL TYPE integer native visual type of the associated visual (always EGL_NONE)
	//EGL RENDERABLE TYPE bitmask which client rendering APIs are supported. (always EGL_OPENVG_BIT)
	//EGL SAMPLE BUFFERS integer number of multisample buffers (always 0)
	//EGL SAMPLES integer number of samples per pixel (always 0)
	//EGL STENCIL SIZE integer bits of Stencil in the stencil buffer (always 0)
	//EGL SURFACE TYPE bitmask which types of EGL surfaces are supported. (always EGL WINDOW BIT | EGL PIXMAP BIT | EGL PBUFFER BIT)
	//EGL TRANSPARENT TYPE enum type of transparency supported (always EGL_NONE)
	//EGL TRANSPARENT RED VALUE integer transparent red value (undefined)
	//EGL TRANSPARENT GREEN VALUE integer transparent green value (undefined)
	//EGL TRANSPARENT BLUE VALUE integer transparent blue value (undefined)
};

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

class Context
{
public:
	Context();
	~Context();
	void	addReference()				{ m_referenceCount++; }
	int		removeReference()			{ m_referenceCount--; RI_ASSERT(m_referenceCount >= 0); return m_referenceCount; }
	
	VGContext*		m_vgContext;
	EGLConfig		m_config;
	EGLBoolean		m_hasBeenCurrent;
private:
	Context(const Context&);
	Context& operator=(const Context&);
	int				m_referenceCount;
};

Context::Context() :
	m_vgContext(NULL),
	m_config(-1),
	m_hasBeenCurrent(EGL_FALSE),
	m_referenceCount(0)
{}
Context::~Context()
{
	RI_ASSERT(m_referenceCount == 0);
	RI_DELETE(m_vgContext);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

class Surface
{
public:
	Surface();
	~Surface();
	void	addReference()				{ m_referenceCount++; }
	int		removeReference()			{ m_referenceCount--; RI_ASSERT(m_referenceCount >= 0); return m_referenceCount; }
	
	int				m_window;
	EGLConfig		m_config;
	Image*			m_image;
	Image*			m_mask;
	bool			m_windowSurface;	//else a pbuffer surface
	bool			m_largestPbuffer;
	int				m_renderBuffer;		//EGL_BACK_BUFFER or EGL_SINGLE_BUFFER
private:
	Surface(const Surface&);
	Surface& operator=(const Surface&);
	int				m_referenceCount;
};

Surface::Surface() :
	m_window(0),
	m_config(-1),
	m_image(NULL),
	m_mask(NULL),
	m_windowSurface(false),
	m_largestPbuffer(false),
	m_renderBuffer(0),
	m_referenceCount(0)
{}
Surface::~Surface()
{
	RI_ASSERT(m_referenceCount == 0);
	if(m_image)
	{
		if(!m_image->removeReference())
			RI_DELETE(m_image);
	}
	if(m_mask)
	{
		if(!m_mask->removeReference())
			RI_DELETE(m_mask);
	}
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

#define EGL_NUMCONFIGS		8

class Display
{
public:
	Display();
	~Display() {}

	int		getNumConfigs() const		{ return EGL_NUMCONFIGS; }

	EGLDisplay		m_id;

	Array<Context*>	m_contexts;
	Array<Surface*>	m_surfaces;

	Config			m_configs[EGL_NUMCONFIGS];
private:
	Display(const Display& t);
	Display& operator=(const Display&t);
};

Display::Display() :
	m_id(0),
	m_contexts(),
	m_surfaces()
{
	RI_ASSERT(EGL_NUMCONFIGS == 8);

	//sorted by RGB/LUMINANCE (exact), larger total number of color bits (at least), buffer size (at least), config ID (exact)
	//NOTE: 16 bit configs need to be sorted on the fly if the request ignores some channels
	//NOTE: config IDs start from 1
	//               R  B  G  A  L  ID
	m_configs[0].set(8, 8, 8, 8, 0, 32, 1);	//EGL_RGB_BUFFER, buffer size = 32
	m_configs[1].set(8, 8, 8, 0, 0, 32, 2);	//EGL_RGB_BUFFER, buffer size = 24
	m_configs[2].set(5, 5, 5, 1, 0, 16, 3);	//EGL_RGB_BUFFER, buffer size = 16
	m_configs[3].set(5, 6, 5, 0, 0, 16, 4);	//EGL_RGB_BUFFER, buffer size = 16
	m_configs[4].set(4, 4, 4, 4, 0, 16, 5);	//EGL_RGB_BUFFER, buffer size = 16
	m_configs[5].set(0, 0, 0, 8, 0, 8, 6);	//EGL_RGB_BUFFER, buffer size = 8
	m_configs[6].set(0, 0, 0, 0, 8, 8, 7);	//EGL_LUMINANCE_BUFFER, buffer size = 8
	m_configs[7].set(0, 0, 0, 0, 1, 1, 8);	//EGL_LUMINANCE_BUFFER, buffer size = 1
/*
attrib                default        criteria order   priority
--------------------------------------------------------------
EGL_COLOR_BUFFER_TYPE EGL_RGB_BUFFER Exact    None    2 
EGL_RED_SIZE          0              AtLeast  Special 3 
EGL_GREEN_SIZE        0              AtLeast  Special 3 
EGL_BLUE_SIZE         0              AtLeast  Special 3 
EGL_LUMINANCE_SIZE    0              AtLeast  Special 3 
EGL_ALPHA_SIZE        0              AtLeast  Special 3 
EGL_BUFFER_SIZE       0              AtLeast  Smaller 4 
EGL_CONFIG_ID         EGL_DONT_CARE  Exact    Smaller 11
*/
}

#undef EGL_NUMCONFIGS

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

class Thread
{
public:
	Thread();
	~Thread();

	Context*		m_context;
	Surface*		m_surface;
	EGLint			m_error;
	ThreadID		m_threadID;
	EGLint			m_boundAPI;
	EGLBoolean		m_configPreferenceHG;
private:
	Thread(const Thread&);
	Thread operator=(const Thread&);
};

Thread::Thread() :
	m_context(NULL),
	m_surface(NULL),
	m_error(EGL_SUCCESS),
	m_threadID(getCurrentThreadID()),
	m_boundAPI(EGL_NONE),
	m_configPreferenceHG(EGL_FALSE)
{
}
Thread::~Thread()
{
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

class EGL
{
public:
	EGL();
	~EGL();

	void	addReference()				{ m_referenceCount++; }
	int		removeReference()			{ m_referenceCount--; RI_ASSERT(m_referenceCount >= 0); return m_referenceCount; }

	Array<Display*>		m_displays;
	Array<Thread*>		m_threads;			//threads that have called EGL
	Array<Thread*>		m_currentThreads;	//threads that have a bound context

private:
	EGL(const EGL&);						// Not allowed.
	const EGL& operator=(const EGL&);		// Not allowed.

	int					m_referenceCount;
};

EGL::EGL() :
	m_displays(),
	m_threads(),
	m_currentThreads(),
	m_referenceCount(0)
{
}
EGL::~EGL()
{
	for(int i=0;i<m_displays.size();i++)
	{
		RI_DELETE(m_displays[i]);
	}
	for(int i=0;i<m_threads.size();i++)
	{
		RI_DELETE(m_threads[i]);
	}
	//currentThreads contain just pointers to threads we just deleted
}

//==============================================================================================

}	//namespace OpenVGRI

using namespace OpenVGRI;

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

static EGL* g_egl = NULL;	//never use this directly
static EGL* getEGL()
{
	if(!g_egl)
	{
		try
		{
			g_egl = RI_NEW(EGL, ());				//throws bad_alloc
			g_egl->addReference();
		}
		catch(std::bad_alloc)
		{
			g_egl = NULL;
		}
	}
	return g_egl;
}
static void releaseEGL()
{
	if(g_egl)
	{
		if(!g_egl->removeReference())
		{
			RI_DELETE(g_egl);
			g_egl = NULL;
		}
	}
}

/*-------------------------------------------------------------------*//*!
* \brief	Given a display ID, return the corresponding object, or NULL
*			if the ID hasn't been initialized.
* \param	
* \return	
* \note		if egl has been initialized for this display, the display ID can
*			be found from egl->m_displays
*//*-------------------------------------------------------------------*/

static Display* getCurrentDisplay(EGLDisplay displayID)
{
	EGL* egl = getEGL();
	if(!egl)
		return NULL;	//error: the display hasn't been eglInitialized

	for(int i=0;i<egl->m_displays.size();i++)
	{
		if(displayID == egl->m_displays[i]->m_id)
			return egl->m_displays[i];
	}
	return NULL;		//error: the display hasn't been eglInitialized
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

static Thread* getCurrentThread()
{
	EGL* egl = getEGL();
	if(!egl)
		return NULL;	//error: the thread is not current

	ThreadID currentThreadID = getCurrentThreadID();
	for(int i=0;i<egl->m_currentThreads.size();i++)
	{
		if(currentThreadID == egl->m_currentThreads[i]->m_threadID)
			return egl->m_currentThreads[i];
	}
	return NULL;		//error: the thread is not current
}

static Thread* getThread()
{
	EGL* egl = getEGL();
	if(!egl)
		return NULL;

	ThreadID currentThreadID = getCurrentThreadID();
	for(int i=0;i<egl->m_threads.size();i++)
	{
		if(currentThreadID == egl->m_threads[i]->m_threadID)
			return egl->m_threads[i];
	}

	//add thread to EGL's list
	Thread* newThread = NULL;
	try
	{
		newThread = RI_NEW(Thread, ());	//throws bad_alloc
		egl->m_threads.push_back(newThread);	//throws bad_alloc
		return newThread;
	}
	catch(std::bad_alloc)
	{
		RI_DELETE(newThread);
		return NULL;
	}
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

// \todo [kalle 05/Jul/05] Should the display related error messages
// be combined into this macro? Now there are three repeated lines in
// the beginning of most API functions.
#define EGL_GET_DISPLAY(dpy) \
	eglAcquireMutex(); \
	Display* display = getCurrentDisplay(dpy); \

#define EGL_IF_ERROR(COND, ERRORCODE, RETVAL) \
	if(COND) { eglSetError(ERRORCODE); eglReleaseMutex(); return RETVAL; } \

#define EGL_RETURN(ERRORCODE, RETVAL) \
	{ \
		eglSetError(ERRORCODE); \
		eglReleaseMutex(); \
		return RETVAL; \
	}

// Note: egl error handling model differs from OpenVG. Only latest error is stored.
static void eglSetError(EGLint error)
{
	Thread* thread = getCurrentThread();
	if(thread)
		thread->m_error = error;
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

static Color::Descriptor configToDescriptor(const Config& c, bool sRGB, bool premultiplied)
{
	Color::Descriptor desc = c.m_desc;
	unsigned int f = c.m_desc.luminanceBits ? Color::LUMINANCE : 0;
	f |= sRGB ? Color::NONLINEAR : 0;
	f |= premultiplied ? Color::PREMULTIPLIED : 0;
	desc.internalFormat = (Color::InternalFormat)f;
	return desc;
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

static EGLBoolean eglContextExists(Display* display, EGLContext ctx)
{
	for(int i=0;i<display->m_contexts.size();i++)
	{
		if( display->m_contexts[i] == ctx )
			return EGL_TRUE;
	}
	return EGL_FALSE;
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

static EGLBoolean eglSurfaceExists(Display* display, EGLSurface surf)
{
	for(int i=0;i<display->m_surfaces.size();i++)
	{
		if( display->m_surfaces[i] == surf )
			return EGL_TRUE;
	}
	return EGL_FALSE;
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

static EGLBoolean eglConfigExists(Display* display, EGLConfig config)
{
	if(config >= 0 && config < display->getNumConfigs())
		return EGL_TRUE;
	return EGL_FALSE;
}





/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLint eglGetError()
{
	eglAcquireMutex();
	Thread* thread = getCurrentThread();
	EGLint ret = EGL_SUCCESS;
	if(thread)
		ret = thread->m_error;	//initialized, return error code
	eglReleaseMutex();
	return ret;
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLDisplay eglGetDisplay(int display_id)
{
	EGL_GET_DISPLAY(display_id);
	RI_UNREF(display);
	EGLDisplay ret = EGL_NO_DISPLAY;
	if(display_id == EGL_DEFAULT_DISPLAY)
		ret = EGL_DEFAULT_DISPLAY;	//NOTE in this implementation EGLDisplay type is an int, mark the only valid display by EGL_DEFAULT_DISPLAY
	EGL_RETURN(EGL_SUCCESS, ret);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglInitialize(EGLDisplay dpy, EGLint *major, EGLint *minor)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_FALSE);
	EGL_IF_ERROR(display, EGL_SUCCESS, EGL_TRUE);	//already initialized

	EGL* egl = getEGL();
	if(!egl)
		EGL_RETURN(EGL_BAD_ALLOC, EGL_FALSE);
	//create the current display
	//if a context and a surface are bound by the time of eglTerminate, they remain bound until eglMakeCurrent is called
	Display* newDisplay = NULL;
	try
	{
		newDisplay = RI_NEW(Display, ());	//throws bad_alloc
		newDisplay->m_id = dpy;
		egl->m_displays.push_back(newDisplay);	//throws bad_alloc
		display = newDisplay;
		RI_ASSERT(display);
	}
	catch(std::bad_alloc)
	{
		RI_DELETE(newDisplay);
		EGL_RETURN(EGL_BAD_ALLOC, EGL_FALSE);
	}

	if(major) *major = 1;
	if(minor) *minor = 2;
	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglTerminate(EGLDisplay dpy)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_SUCCESS, EGL_TRUE);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_FALSE);

	//mark everything for deletion, but don't delete the current context and surface
	for(int i=0;i<display->m_contexts.size();i++)
	{
		if(!display->m_contexts[i]->removeReference())
			RI_DELETE(display->m_contexts[i]);
	}
	display->m_contexts.clear();	//remove all contexts from the list (makes further references to the current contexts invalid)

	for(int i=0;i<display->m_surfaces.size();i++)
	{
		if(!display->m_surfaces[i]->removeReference())
			RI_DELETE(display->m_surfaces[i]);
	}
	display->m_surfaces.clear();	//remove all surfaces from the list (makes further references to the current surfaces invalid)

	EGL* egl = getEGL();
	if(!egl)
		EGL_RETURN(EGL_BAD_ALLOC, EGL_FALSE);

	//remove display from list
	int i=0;
	for(;i<egl->m_displays.size();i++)
	{
		if(egl->m_displays[i] == display)
		{
			RI_DELETE(egl->m_displays[i]);
			egl->m_displays[i] = NULL;
			break;
		}
	}
	RI_ASSERT(i < egl->m_displays.size());	//check that the display was found
	for(;i<egl->m_displays.size()-1;i++)
	{
		egl->m_displays[i] = egl->m_displays[i+1];
	}
	egl->m_displays.resize(egl->m_displays.size()-1);

	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

const char *eglQueryString(EGLDisplay dpy, EGLint name)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, NULL);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, NULL);

	static const char apis[] = "OpenVG";
	static const char extensions[] = "eglSetConfigPreferenceHG";
	static const char vendor[] = "Khronos Group";
	static const char version[] = "1.2";

	const char* ret = NULL;
	switch(name)
	{
	case EGL_CLIENT_APIS:
		ret = apis;
		break;

	case EGL_EXTENSIONS:
		ret = extensions;
		break;

	case EGL_VENDOR:
		ret = vendor;
		break;

	case EGL_VERSION:
		ret = version;
		break;

	default:
		EGL_RETURN(EGL_BAD_PARAMETER, NULL);
	}
	EGL_RETURN(EGL_SUCCESS, ret);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglGetConfigs(EGLDisplay dpy, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_FALSE);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_FALSE);
	EGL_IF_ERROR(!num_config, EGL_BAD_PARAMETER, EGL_FALSE);
	if(!configs)
	{
		*num_config = display->getNumConfigs();
		EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
	}
	*num_config = RI_INT_MIN(config_size, display->getNumConfigs());
	for(int i=0;i<*num_config;i++)
		configs[i] = i;

	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

static bool smaller(EGLint c, EGLint filter)
{
	return (filter != EGL_DONT_CARE) && (c < filter);
}

EGLBoolean eglChooseConfig(EGLDisplay dpy, const EGLint *attrib_list, EGLConfig *configs, EGLint config_size, EGLint *num_config)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_FALSE);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_FALSE);
	EGL_IF_ERROR(!num_config, EGL_BAD_PARAMETER, EGL_FALSE);

	if(!configs)
	{
		*num_config = display->getNumConfigs();
		EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
	}
	*num_config = 0;
	if(!config_size)
		EGL_RETURN(EGL_SUCCESS, EGL_TRUE);

	int bufferSize = 0;
	int redSize = 0;
	int greenSize = 0;
	int blueSize = 0;
	int luminanceSize = 0;
	int alphaSize = 0;
	int colorBufferType = EGL_RGB_BUFFER;
	int configID = EGL_DONT_CARE;
	if(attrib_list)
	{
		for(int i=0;attrib_list[i] != EGL_NONE;i+=2)
		{
			switch(attrib_list[i])
			{
			case EGL_BUFFER_SIZE:				//depth of the color buffer
				bufferSize = attrib_list[i+1];
				break;
			case EGL_RED_SIZE:					//bits of Red in the color buffer
				redSize = attrib_list[i+1];
				break;
			case EGL_GREEN_SIZE:				//bits of Green in the color buffer
				greenSize = attrib_list[i+1];
				break;
			case EGL_BLUE_SIZE:					//bits of Blue in the color buffer
				blueSize = attrib_list[i+1];
				break;
			case EGL_LUMINANCE_SIZE:			//bits of Luminance in the color buffer
				luminanceSize = attrib_list[i+1];
				break;
			case EGL_ALPHA_SIZE:				//bits of Alpha in the color buffer
				alphaSize = attrib_list[i+1];
				break;
			case EGL_ALPHA_MASK_SIZE:			//bits of Alpha in the alpha mask buffer
				if(attrib_list[i+1] > 8)
					EGL_RETURN(EGL_SUCCESS, EGL_TRUE);	//not supported
				break;
			case EGL_COLOR_BUFFER_TYPE:			//enum color buffer type (EGL_RGB_BUFFER, EGL_LUMINANCE_BUFFER)
				EGL_IF_ERROR(attrib_list[i+1] != EGL_RGB_BUFFER && attrib_list[i+1] != EGL_LUMINANCE_BUFFER && attrib_list[i+1] != EGL_DONT_CARE, EGL_BAD_ATTRIBUTE, EGL_FALSE);
				colorBufferType = attrib_list[i+1];
				break;
			case EGL_CONFIG_ID:					//unique EGLConfig identifier
				configID = attrib_list[i+1];
				break;

			case EGL_BIND_TO_TEXTURE_RGB:		//boolean True if bindable to RGB textures. (always EGL_FALSE)
			case EGL_BIND_TO_TEXTURE_RGBA:		//boolean True if bindable to RGBA textures. (always EGL_FALSE)
			case EGL_DEPTH_SIZE:				//integer bits of Z in the depth buffer (always 0)
			case EGL_LEVEL:						//integer frame buffer level (always 0)
			case EGL_NATIVE_RENDERABLE:			//boolean EGL TRUE if native rendering APIs can render to surface (always EGL_FALSE)
			case EGL_SAMPLE_BUFFERS:			//integer number of multisample buffers (always 0)
			case EGL_SAMPLES:					//integer number of samples per pixel (always 0)
			case EGL_STENCIL_SIZE:				//integer bits of Stencil in the stencil buffer (always 0)
				if(attrib_list[i+1])
					EGL_RETURN(EGL_SUCCESS, EGL_TRUE);	//not supported
				break;

			case EGL_CONFIG_CAVEAT:				//enum any caveats for the configuration (always EGL_NONE)
			case EGL_NATIVE_VISUAL_TYPE:		//integer native visual type of the associated visual (always EGL_NONE)
				if(attrib_list[i+1] != EGL_NONE)
					EGL_RETURN(EGL_SUCCESS, EGL_TRUE);	//not supported
				break;

			case EGL_MAX_SWAP_INTERVAL:			//integer maximum swap interval (always 1)
			case EGL_MIN_SWAP_INTERVAL:			//integer minimum swap interval (always 1)
				if(attrib_list[i+1] != 1)
					EGL_RETURN(EGL_SUCCESS, EGL_TRUE);	//not supported
				break;

			case EGL_RENDERABLE_TYPE:			//bitmask which client rendering APIs are supported. (always EGL_OPENVG_BIT)
				if(!(attrib_list[i+1] & EGL_OPENVG_BIT))
					EGL_RETURN(EGL_SUCCESS, EGL_TRUE);	//not supported
				break;

			case EGL_SURFACE_TYPE:				//bitmask which types of EGL surfaces are supported. (always EGL WINDOW BIT | EGL PIXMAP BIT | EGL PBUFFER BIT)
				break;	//all types are always supported

			case EGL_TRANSPARENT_TYPE:			//enum type of transparency supported (always EGL_NONE)
			case EGL_NATIVE_VISUAL_ID:			//integer handle of corresponding native visual (always 0)
			case EGL_MAX_PBUFFER_WIDTH:			//integer maximum width of pbuffer (always INT_MAX)
			case EGL_MAX_PBUFFER_HEIGHT:		//integer maximum height of pbuffer (always INT_MAX)
			case EGL_MAX_PBUFFER_PIXELS:		//integer maximum size of pbuffer (always INT_MAX)
			case EGL_TRANSPARENT_RED_VALUE:		//integer transparent red value (undefined)
			case EGL_TRANSPARENT_GREEN_VALUE:	//integer transparent green value (undefined)
			case EGL_TRANSPARENT_BLUE_VALUE:	//integer transparent blue value (undefined)
				break;	//ignored

			default:
				EGL_RETURN(EGL_BAD_ATTRIBUTE, EGL_FALSE);	//unknown attribute
			}
		}
	}

	if(configID && configID != EGL_DONT_CARE)
	{	//if CONFIG_ID is defined, ignore the rest of the attribs
		if(configID >= 1 && configID <= display->getNumConfigs())
		{
			*num_config = 1;
			*configs = configID-1;
		}
		EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
	}

	//go through all configs, add passed configs to return list
	int found[16];
	int numFound = 0;
	for(int i=0;i<display->getNumConfigs();i++)
	{
		const Config& c = display->m_configs[i];

		int colorBits = c.m_desc.redBits + c.m_desc.greenBits + c.m_desc.blueBits;
		int luminanceBits = c.m_desc.luminanceBits;
		int configBufferSize;
		if(colorBits)
		{
			RI_ASSERT(!luminanceBits);
			colorBits += c.m_desc.alphaBits;
			configBufferSize = colorBits;
		}
		else if(luminanceBits)
		{
			luminanceBits += c.m_desc.alphaBits;
			configBufferSize = luminanceBits;
		}
		else
		{	//alpha only surface
			colorBits = c.m_desc.alphaBits;
			luminanceBits = c.m_desc.alphaBits;
			configBufferSize = colorBits;
		}

		if (smaller(configBufferSize, bufferSize))
			continue;

		if (smaller(c.m_desc.redBits, redSize)
			|| smaller(c.m_desc.greenBits, greenSize)
			|| smaller(c.m_desc.blueBits, blueSize) 
			|| smaller(c.m_desc.alphaBits, alphaSize) )
			continue;

		if (smaller(c.m_desc.luminanceBits, luminanceSize))
			continue;

		if ((colorBufferType == EGL_RGB_BUFFER && !colorBits) ||
			(colorBufferType == EGL_LUMINANCE_BUFFER && !luminanceBits))
			continue;

		int sortKey = c.m_configID;	//sort from smaller to larger
		int sortBits = 0;
		if(redSize != 0 && redSize != EGL_DONT_CARE)
			sortBits += c.m_desc.redBits;
		if(greenSize != 0 && greenSize != EGL_DONT_CARE)
			sortBits += c.m_desc.greenBits;
		if(blueSize != 0 && blueSize != EGL_DONT_CARE)
			sortBits += c.m_desc.blueBits;
		if(alphaSize != 0 && alphaSize != EGL_DONT_CARE)
			sortBits += c.m_desc.alphaBits;
		if(luminanceSize != 0 && luminanceSize != EGL_DONT_CARE)
			sortBits += c.m_desc.luminanceBits;
		RI_ASSERT(c.m_configID < 16);	//if there are more configs, increase the shift value
		RI_ASSERT(sortBits <= 32);
		sortKey += (32-sortBits) << 4;	//sort from larger to smaller

		found[numFound++] = sortKey;
		found[numFound++] = i;
	}
	if(!numFound)
		EGL_RETURN(EGL_SUCCESS, EGL_TRUE);

	//sort return list into increasing order
	Thread* thread = getThread();
	RI_ASSERT(thread);
	numFound /= 2;
	for(int e=0;e<numFound-1;e++)
	{
		for(int f=e+1;f<numFound;f++)
		{
			if((!thread->m_configPreferenceHG && found[e*2] > found[f*2]) ||
				(thread->m_configPreferenceHG && found[e*2] <= found[f*2]))
			{
				RI_INT_SWAP(found[e*2], found[f*2]);
				RI_INT_SWAP(found[e*2+1], found[f*2+1]);
			}
		}
	}

	//write configs into return array
	numFound = RI_INT_MIN(numFound, config_size);
	for(int i=0;i<numFound;i++)
	{
		configs[i] = found[i*2+1];
	}
	*num_config = numFound;

	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglGetConfigAttrib(EGLDisplay dpy, EGLConfig config, EGLint attribute, EGLint *value)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_FALSE);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_FALSE);
	EGL_IF_ERROR(!eglConfigExists(display, config), EGL_BAD_CONFIG, EGL_FALSE);
	Config& c = display->m_configs[config];
	switch(attribute)
	{
	case EGL_BUFFER_SIZE:
		*value = RI_INT_MAX(c.m_desc.redBits + c.m_desc.greenBits + c.m_desc.blueBits + c.m_desc.alphaBits, c.m_desc.luminanceBits + c.m_desc.alphaBits);
		break;

	case EGL_RED_SIZE:
		*value = c.m_desc.redBits;
		break;

	case EGL_GREEN_SIZE:
		*value = c.m_desc.greenBits;
		break;

	case EGL_BLUE_SIZE:
		*value = c.m_desc.blueBits;
		break;

	case EGL_LUMINANCE_SIZE:
		*value = c.m_desc.luminanceBits;
		break;

	case EGL_ALPHA_SIZE:
		*value = c.m_desc.alphaBits;
		break;

	case EGL_ALPHA_MASK_SIZE:
		*value = 8;
		break;

	case EGL_BIND_TO_TEXTURE_RGB:
	case EGL_BIND_TO_TEXTURE_RGBA:
		*value = EGL_FALSE;
		break;

	case EGL_COLOR_BUFFER_TYPE:
		if(c.m_desc.redBits)
			*value = EGL_RGB_BUFFER;
		else
			*value = EGL_LUMINANCE_BUFFER;
		break;

	case EGL_CONFIG_CAVEAT:
		*value = EGL_NONE;
		break;

	case EGL_CONFIG_ID:
		*value = c.m_configID;
		break;

	case EGL_DEPTH_SIZE:
		*value = 0;
		break;

	case EGL_LEVEL:
		*value = 0;
		break;

	case EGL_MAX_PBUFFER_WIDTH:
	case EGL_MAX_PBUFFER_HEIGHT:
		*value = 16384;			//NOTE arbitrary maximum
		break;
		
	case EGL_MAX_PBUFFER_PIXELS:
		*value = 16384*16384;	//NOTE arbitrary maximum
		break;

	case EGL_MAX_SWAP_INTERVAL:
	case EGL_MIN_SWAP_INTERVAL:
		*value = 1;
		break;

	case EGL_NATIVE_RENDERABLE:
		*value = EGL_FALSE;
		break;

	case EGL_NATIVE_VISUAL_ID:
		*value = 0;
		break;

	case EGL_NATIVE_VISUAL_TYPE:
		*value = EGL_NONE;
		break;

	case EGL_RENDERABLE_TYPE:
		*value = EGL_OPENVG_BIT;
		break;

	case EGL_SAMPLE_BUFFERS:
		*value = 0;
		break;

	case EGL_SAMPLES:
		*value = 0;
		break;

	case EGL_STENCIL_SIZE:
		*value = 0;
		break;

	case EGL_SURFACE_TYPE:
		*value = EGL_WINDOW_BIT | EGL_PIXMAP_BIT | EGL_PBUFFER_BIT;
		break;

	case EGL_TRANSPARENT_TYPE:
		*value = EGL_NONE;
		break;

	case EGL_TRANSPARENT_RED_VALUE:
	case EGL_TRANSPARENT_GREEN_VALUE:
	case EGL_TRANSPARENT_BLUE_VALUE:
		*value = 0;
		break;

	default:
		EGL_RETURN(EGL_BAD_ATTRIBUTE, EGL_FALSE);
	}
	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLSurface eglCreateWindowSurface(EGLDisplay dpy, EGLConfig config, NativeWindowType win, const EGLint *attrib_list)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_NO_SURFACE);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_NO_SURFACE);
	EGL_IF_ERROR(!eglConfigExists(display, config), EGL_BAD_CONFIG, EGL_NO_SURFACE);

	int renderBuffer = EGL_BACK_BUFFER;
	int colorSpace = EGL_COLORSPACE_sRGB;
	int alphaFormat = EGL_ALPHA_FORMAT_NONPRE;
	if(attrib_list)
	{
		for(int i=0;attrib_list[i] != EGL_NONE;i+=2)
		{
			switch(attrib_list[i])
			{
			case EGL_RENDER_BUFFER:
				renderBuffer = attrib_list[i+1];
				break;

			case EGL_COLORSPACE:
				colorSpace = attrib_list[i+1];
				break;

			case EGL_ALPHA_FORMAT:
				alphaFormat = attrib_list[i+1];
				break;

			default:
				EGL_RETURN(EGL_BAD_ATTRIBUTE, EGL_NO_SURFACE);
			}
		}
	}
	//we ignore the renderBuffer parameter since we can only render to double buffered surfaces

	//TODO If the attributes of win do not correspond to config, then an EGL BAD MATCH error is generated.
	//TODO If win is not a valid native window handle, then an EGL BAD NATIVE WINDOW error should be generated.
	//TODO If there is already an EGLConfig associated with win (as a result of a previous eglCreateWindowSurface call), then an EGL BAD ALLOC error is generated

	//TODO what happens if window width or height is zero?

	int currWin = glutGetWindow();
	glutSetWindow((int)win);
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);
	glutSetWindow(currWin);

	Surface* s = NULL;
	try
	{
		s = RI_NEW(Surface,());	//throws bad_alloc
		RI_ASSERT(s);
		s->m_image = RI_NEW(Image, (configToDescriptor(display->m_configs[config],(colorSpace == EGL_COLORSPACE_LINEAR) ? false : true, (alphaFormat == EGL_ALPHA_FORMAT_PRE) ? true : false), width, height, 0));	//throws bad_alloc
		RI_ASSERT(s->m_image);
		s->m_mask = RI_NEW(Image, (Color::formatToDescriptor(VG_A_8), width, height, 0));	//throws bad_alloc
		RI_ASSERT(s->m_mask);
		s->m_image->addReference();
		s->m_mask->addReference();
		s->m_mask->clear(Color(1,1,1,1,Color::lRGBA), 0, 0, s->m_mask->getWidth(), s->m_mask->getHeight());
		s->m_window = (int)win;
		s->m_config = config;
		s->m_windowSurface = true;
		s->m_largestPbuffer = false;
		s->m_renderBuffer = renderBuffer;
		s->addReference();
		display->m_surfaces.push_back(s);	//throws bad_alloc
	}
	catch(std::bad_alloc)
	{
		if(s)
		{
			RI_DELETE(s->m_image);
			RI_DELETE(s->m_mask);
			RI_DELETE(s);
		}
		EGL_RETURN(EGL_BAD_ALLOC, EGL_NO_SURFACE);
	}
	EGL_RETURN(EGL_SUCCESS, (EGLSurface)s);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLSurface eglCreatePbufferSurface(EGLDisplay dpy, EGLConfig config, const EGLint *attrib_list)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_NO_SURFACE);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_NO_SURFACE);
	EGL_IF_ERROR(!eglConfigExists(display, config), EGL_BAD_CONFIG, EGL_NO_SURFACE);

	int width = 0, height = 0;
	bool largestPbuffer = false;
	int colorSpace = EGL_COLORSPACE_sRGB;
	int alphaFormat = EGL_ALPHA_FORMAT_NONPRE;
	if(attrib_list)
	{
		for(int i=0;attrib_list[i] != EGL_NONE;i+=2)
		{
			switch(attrib_list[i])
			{
			case EGL_WIDTH:
				width = attrib_list[i+1];
				break;

			case EGL_HEIGHT:
				height = attrib_list[i+1];
				break;

			case EGL_LARGEST_PBUFFER:
				largestPbuffer = attrib_list[i+1] ? true : false;
				break;

			case EGL_COLORSPACE:
				colorSpace = attrib_list[i+1];
				break;

			case EGL_ALPHA_FORMAT:
				alphaFormat = attrib_list[i+1];
				break;

			case EGL_TEXTURE_FORMAT:	//config doesn't support OpenGL ES
			case EGL_TEXTURE_TARGET:	//config doesn't support OpenGL ES
			case EGL_MIPMAP_TEXTURE:	//config doesn't support OpenGL ES
			default:
				EGL_RETURN(EGL_BAD_ATTRIBUTE, EGL_NO_SURFACE);
			break;
			}
		}
	}
	EGL_IF_ERROR(width <= 0 || height <= 0, EGL_BAD_ATTRIBUTE, EGL_NO_SURFACE);

	Surface* s = NULL;
	try
	{
		s = RI_NEW(Surface,());	//throws bad_alloc
		RI_ASSERT(s);
		s->m_image = RI_NEW(Image, (configToDescriptor(display->m_configs[config],(colorSpace == EGL_COLORSPACE_LINEAR) ? false : true, (alphaFormat == EGL_ALPHA_FORMAT_PRE) ? true : false), width, height, 0));	//throws bad_alloc
		RI_ASSERT(s->m_image);
		s->m_mask = RI_NEW(Image, (Color::formatToDescriptor(VG_A_8), width, height, 0));	//throws bad_alloc
		RI_ASSERT(s->m_mask);
		s->m_image->addReference();
		s->m_mask->addReference();
		s->m_mask->clear(Color(1,1,1,1,Color::lRGBA), 0, 0, s->m_mask->getWidth(), s->m_mask->getHeight());
		s->m_window = 0;
		s->m_config = config;
		s->m_windowSurface = false;
		s->m_largestPbuffer = largestPbuffer;
		s->m_renderBuffer = EGL_BACK_BUFFER;
		s->addReference();
		display->m_surfaces.push_back(s);	//throws bad_alloc
	}
	catch(std::bad_alloc)
	{
		if(s)
		{
			RI_DELETE(s->m_image);
			RI_DELETE(s->m_mask);
			RI_DELETE(s);
		}
		EGL_RETURN(EGL_BAD_ALLOC, EGL_NO_SURFACE);
	}
	EGL_RETURN(EGL_SUCCESS, (EGLSurface)s);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLSurface eglCreatePbufferFromClientBuffer(EGLDisplay dpy, EGLenum buftype, EGLClientBuffer buffer, EGLConfig config, const EGLint *attrib_list)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_NO_SURFACE);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_NO_SURFACE);
	EGL_IF_ERROR(buftype != EGL_OPENVG_IMAGE, EGL_BAD_PARAMETER, EGL_NO_SURFACE);
	EGL_IF_ERROR(!buffer, EGL_BAD_PARAMETER, EGL_NO_SURFACE);	//TODO should also check if buffer really is a valid VGImage object
	EGL_IF_ERROR(((Image*)buffer)->isInUse(), EGL_BAD_ACCESS, EGL_NO_SURFACE);	//buffer is in use by OpenVG
	EGL_IF_ERROR(!eglConfigExists(display, config), EGL_BAD_CONFIG, EGL_NO_SURFACE);
	EGL_IF_ERROR(attrib_list && attrib_list[0] != EGL_NONE, EGL_BAD_ATTRIBUTE, EGL_NO_SURFACE);	//there are no valid attribs for OpenVG
	const Color::Descriptor& bc = ((Image*)buffer)->getDescriptor();
	const Color::Descriptor& cc = display->m_configs[config].m_desc;
	EGL_IF_ERROR(bc.redBits != cc.redBits || bc.greenBits != cc.greenBits || bc.blueBits != cc.blueBits ||
				 bc.alphaBits != cc.alphaBits || bc.luminanceBits != cc.luminanceBits, EGL_BAD_MATCH, EGL_NO_SURFACE);

	//TODO If buffer is already bound to another pbuffer, an EGL BAD ACCESS error is generated.
	// \todo [kalle 05/Jul/05] Can the acccess control be achieved using OpenVG Image inUse counter?

	Surface* s = NULL;
	try
	{
		Image* image = (Image*)buffer;
		s = RI_NEW(Surface, ());	//throws bad_alloc
		RI_ASSERT(s);
		s->m_image = image;
		s->m_mask = RI_NEW(Image, (Color::formatToDescriptor(VG_A_8), image->getWidth(), image->getHeight(), 0));	//throws bad_alloc
		RI_ASSERT(s->m_mask);
		s->m_image->addReference();
		s->m_mask->addReference();
		s->m_mask->clear(Color(1,1,1,1,Color::lRGBA), 0, 0, s->m_mask->getWidth(), s->m_mask->getHeight());
		s->m_window = 0;
		s->m_config = config;
		s->m_windowSurface = false;
		s->m_largestPbuffer = false;
		s->m_renderBuffer = EGL_BACK_BUFFER;
		s->addReference();
		display->m_surfaces.push_back(s);	//throws bad_alloc
	}
	catch(std::bad_alloc)
	{
		RI_DELETE(s->m_mask);
		RI_DELETE(s);
		EGL_RETURN(EGL_BAD_ALLOC, EGL_NO_SURFACE);
	}
	EGL_RETURN(EGL_SUCCESS, (EGLSurface)s);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLSurface eglCreatePixmapSurface(EGLDisplay dpy, EGLConfig config, NativePixmapType pixmap, const EGLint *attrib_list)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_NO_SURFACE);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_NO_SURFACE);
	EGL_IF_ERROR(!eglConfigExists(display, config), EGL_BAD_CONFIG, EGL_NO_SURFACE);
	EGL_IF_ERROR(!pixmap || !isValidImageFormat(pixmap->format) || !pixmap->data || pixmap->width <= 0 || pixmap->height <= 0, EGL_BAD_NATIVE_PIXMAP, EGL_NO_SURFACE);
	RI_UNREF(attrib_list);
	const Color::Descriptor& cc = display->m_configs[config].m_desc;
	EGL_IF_ERROR(cc.redBits != 8 || cc.greenBits != 8 || cc.blueBits != 8 ||
				 (cc.alphaBits != 8 && cc.alphaBits != 0) || cc.luminanceBits != 0, EGL_BAD_MATCH, EGL_NO_SURFACE);

	//TODO If there is already an EGLSurface associated with pixmap (as a result of a previous eglCreatePixmapSurface call), then a EGL BAD ALLOC error is generated.

	Surface* s = NULL;
	try
	{
		s = RI_NEW(Surface, ());	//throw bad_alloc
		RI_ASSERT(s);
		s->m_image = RI_NEW(Image, (Color::formatToDescriptor((VGImageFormat)pixmap->format), pixmap->width, pixmap->height, pixmap->stride, (RIuint8*)pixmap->data));	//throws bad_alloc
		RI_ASSERT(s->m_image);
		s->m_mask = RI_NEW(Image, (Color::formatToDescriptor(VG_A_8), pixmap->width, pixmap->height, 0));	//throws bad_alloc
		RI_ASSERT(s->m_mask);
		s->m_image->addReference();
		s->m_mask->addReference();
		s->m_mask->clear(Color(1,1,1,1,Color::lRGBA), 0, 0, s->m_mask->getWidth(), s->m_mask->getHeight());
		s->m_window = 0;
		s->m_config = config;
		s->m_windowSurface = false;
		s->m_largestPbuffer = false;
		s->m_renderBuffer = EGL_BACK_BUFFER;
		s->addReference();
		display->m_surfaces.push_back(s);	//throws bad_alloc
	}
	catch(std::bad_alloc)
	{
		RI_DELETE(s->m_image);
		RI_DELETE(s->m_mask);
		RI_DELETE(s);
		EGL_RETURN(EGL_BAD_ALLOC, EGL_NO_SURFACE);
	}
	EGL_RETURN(EGL_SUCCESS, (EGLSurface)s);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglDestroySurface(EGLDisplay dpy, EGLSurface surface)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_FALSE);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_FALSE);
	EGL_IF_ERROR(!eglSurfaceExists(display, surface), EGL_BAD_SURFACE, EGL_FALSE);

	//remove reference to the surface
	if(!((Surface*)surface)->removeReference())
		RI_DELETE((Surface*)surface);

	//remove from surface list
	int i=0;
	for(;i<display->m_surfaces.size();i++)
	{
		if( display->m_surfaces[i] == (Surface*)surface )
			break;
	}
	RI_ASSERT(i < display->m_surfaces.size());	//context not found from the list
	for(;i<display->m_surfaces.size()-1;i++)
	{
		display->m_surfaces[i] = display->m_surfaces[i+1];
	}
	display->m_surfaces.resize(display->m_surfaces.size()-1);

	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglSurfaceAttrib(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint value)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_FALSE);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_FALSE);
	EGL_IF_ERROR(!eglSurfaceExists(display, surface), EGL_BAD_SURFACE, EGL_FALSE);
	RI_UNREF(attribute);
	RI_UNREF(value);
	//do nothing
	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglQuerySurface(EGLDisplay dpy, EGLSurface surface, EGLint attribute, EGLint *value)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_FALSE);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_FALSE);
	EGL_IF_ERROR(!eglSurfaceExists(display, surface), EGL_BAD_SURFACE, EGL_FALSE);
	//TODO give an error if value is NULL?

	Surface* s = (Surface*)surface;
	switch(attribute)
	{
	case EGL_ALPHA_FORMAT:
		*value = (s->m_image->getDescriptor().internalFormat & Color::PREMULTIPLIED) ? EGL_ALPHA_FORMAT_PRE : EGL_ALPHA_FORMAT_NONPRE;
		break;

	case EGL_COLORSPACE:
		*value = (s->m_image->getDescriptor().internalFormat & Color::NONLINEAR) ? EGL_COLORSPACE_sRGB : EGL_COLORSPACE_LINEAR;
		break;

	case EGL_CONFIG_ID:
		*value = display->m_configs[s->m_config].m_configID;
		break;

	case EGL_HEIGHT:
		*value = s->m_image->getHeight();
		break;

	case EGL_HORIZONTAL_RESOLUTION:
		*value = EGL_UNKNOWN;			//TODO Horizontal dot pitch
		break;

	case EGL_LARGEST_PBUFFER:
		if(!s->m_windowSurface)
			*value = s->m_largestPbuffer ? EGL_TRUE : EGL_FALSE;
		break;

	case EGL_MIPMAP_TEXTURE:
		if(!s->m_windowSurface)
			*value = EGL_FALSE;
		break;

	case EGL_MIPMAP_LEVEL:
		if(!s->m_windowSurface)
			*value = 0;
		break;

	case EGL_PIXEL_ASPECT_RATIO:
		*value = EGL_UNKNOWN;			//TODO Display aspect ratio
		break;

	case EGL_RENDER_BUFFER:
		*value = s->m_renderBuffer;
		break;

	case EGL_SWAP_BEHAVIOR:
		*value = EGL_BUFFER_PRESERVED;
		break;

	case EGL_TEXTURE_FORMAT:
		if(!s->m_windowSurface)
			*value = EGL_NO_TEXTURE;
		break;

	case EGL_TEXTURE_TARGET:
		if(!s->m_windowSurface)
			*value = EGL_NO_TEXTURE;
		break;

	case EGL_VERTICAL_RESOLUTION:
		*value = EGL_UNKNOWN;			//TODO Vertical dot pitch
		break;

	case EGL_WIDTH:
		*value = s->m_image->getWidth();
		break;

	default:
		EGL_RETURN(EGL_BAD_ATTRIBUTE, EGL_FALSE);
	}
	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLContext eglCreateContext(EGLDisplay dpy, EGLConfig config, EGLContext share_context, const EGLint *attrib_list)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_NO_CONTEXT);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_NO_CONTEXT);
	EGL_IF_ERROR(!eglConfigExists(display, config), EGL_BAD_CONFIG, EGL_NO_CONTEXT);
	RI_UNREF(attrib_list);

	Thread* thread = getThread();
	if(!thread)
		EGL_RETURN(EGL_BAD_ALLOC, EGL_NO_CONTEXT);

	//creation of OpenGL ES contexts is not allowed in this implementation
	if(thread->m_boundAPI != EGL_OPENVG_API)
		EGL_RETURN(EGL_BAD_PARAMETER, EGL_NO_CONTEXT);	//TODO spec issue: what's the error code?

	Context* c = NULL;
	try
	{
		c = RI_NEW(Context, ());	//throws bad_alloc
		c->m_vgContext = RI_NEW(OpenVGRI::VGContext, (share_context ? ((Context*)share_context)->m_vgContext : NULL));	//throws bad_alloc
		c->m_config = config;
		c->m_hasBeenCurrent = EGL_FALSE;
		c->addReference();
		display->m_contexts.push_back(c);	//throws bad_alloc
	}
	catch(std::bad_alloc)
	{
		if(c)
		{
			RI_DELETE(c);
		}
		EGL_RETURN(EGL_BAD_ALLOC, EGL_NO_CONTEXT);
	}

	EGL_RETURN(EGL_SUCCESS, (EGLContext)c);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglDestroyContext(EGLDisplay dpy, EGLContext ctx)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_FALSE);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_FALSE);
	EGL_IF_ERROR(!eglContextExists(display, ctx), EGL_BAD_CONTEXT, EGL_FALSE);

	Context* context = (Context*)ctx;

	//check if the context is still bound
	if(!context->removeReference() )
		RI_DELETE(context);

	// remove context from list
	int i=0;
	for(;i<display->m_contexts.size();i++)
	{
		if( display->m_contexts[i] == context )
			break;
	}
	RI_ASSERT(i < display->m_contexts.size());	//context not found
	for(;i<display->m_contexts.size()-1;i++)
	{
		display->m_contexts[i] = display->m_contexts[i+1];
	}
	display->m_contexts.resize(display->m_contexts.size()-1);
	
	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglMakeCurrent(EGLDisplay dpy, EGLSurface draw, EGLSurface read, EGLContext ctx)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_FALSE);
	EGL_IF_ERROR(ctx != EGL_NO_CONTEXT && !eglContextExists(display, ctx), EGL_BAD_CONTEXT, EGL_FALSE);
	EGL_IF_ERROR(draw != EGL_NO_SURFACE && !eglSurfaceExists(display, draw), EGL_BAD_SURFACE, EGL_FALSE);
	EGL_IF_ERROR(read != EGL_NO_SURFACE && !eglSurfaceExists(display, read), EGL_BAD_SURFACE, EGL_FALSE);
	EGL_IF_ERROR(draw != read, EGL_BAD_MATCH, EGL_FALSE);	//TODO what's the proper error code?
	EGL_IF_ERROR((draw != EGL_NO_SURFACE && ctx == EGL_NO_CONTEXT) || (draw == EGL_NO_SURFACE && ctx != EGL_NO_CONTEXT), EGL_BAD_MATCH, EGL_FALSE);

	EGL* egl = getEGL();
	if(!egl)
		EGL_RETURN(EGL_BAD_ALLOC, EGL_FALSE);

	Surface* s = NULL;
	Context* c = NULL;
	if(draw != EGL_NO_SURFACE && ctx != EGL_NO_CONTEXT)
	{
		EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_FALSE);

		s = (Surface*)draw;
		c = (Context*)ctx;

		//draw buffer is in use by OpenVG
		EGL_IF_ERROR(s->m_image->isInUse(), EGL_BAD_ACCESS, EGL_FALSE);


		//TODO properly check compatibility of surface and context:
		//-both have RGB or LUMINANCE configs
		//-buffer bit depths match
		//-configs support OpenVG
		//-both have the same display
		EGL_IF_ERROR(s->m_config != c->m_config, EGL_BAD_MATCH, EGL_FALSE);
		//TODO check if context or surfaces are already bound to another thread
		//TODO If a native window underlying either draw or read is no longer valid, an EGL BAD NATIVE WINDOW error is generated. (can this happen?)
		//TODO If the previous context of the calling display has unflushed commands, and the previous surface is no longer valid, an EGL BAD CURRENT SURFACE error is generated. (can this happen?)
		//TODO If the ancillary buffers for draw and read cannot be allocated, an EGL BAD ALLOC error is generated. (mask buffer?)
	}

	//check if the thread is current
	Thread* thread = getCurrentThread();
	if(thread)
	{	//thread is current, release the old bindinds and remove the thread from the current thread list
		Context* pc = thread->m_context;
		Surface* ps = thread->m_surface;
		if(pc)
		{
			vgFlush();
			pc->m_vgContext->resize(NULL, NULL);
			if(!pc->removeReference())
				RI_DELETE(pc);
		}
		if(ps)
		{
			if(!ps->removeReference())
				RI_DELETE(ps);
		}

		//remove from the current thread list
		int i=0;
		for(;i<egl->m_currentThreads.size();i++)
		{
			if(egl->m_currentThreads[i] == thread)
				break;
		}
		RI_ASSERT(i < egl->m_currentThreads.size());	//thread not found from the list
		for(;i<egl->m_currentThreads.size()-1;i++)
		{
			egl->m_currentThreads[i] = egl->m_currentThreads[i+1];
		}
		egl->m_currentThreads.resize(egl->m_currentThreads.size()-1);
	}

	if( c && s )
	{
		//bind context and surface to the current display
		Thread* newThread = getThread();
		if(!newThread)
			EGL_RETURN(EGL_BAD_ALLOC, EGL_FALSE);
		newThread->m_context = c;
		newThread->m_surface = s;

		try
		{
			c->m_vgContext->resize(s->m_image, s->m_mask);	//throws bad_alloc
			egl->m_currentThreads.push_back(newThread);	//throws bad_alloc
		}
		catch(std::bad_alloc)
		{
			EGL_RETURN(EGL_BAD_ALLOC, EGL_FALSE);
		}

		c->addReference();
		s->addReference();

		if( !c->m_hasBeenCurrent )
		{	//if we supported ES, we would update the viewport here
			c->m_hasBeenCurrent = EGL_TRUE;
		}
	}
	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLContext eglGetCurrentContext()
{
	eglAcquireMutex();
	Thread* thread = getThread();
	if(!thread)
		EGL_RETURN(EGL_BAD_ALLOC, EGL_NO_CONTEXT);
	if(thread->m_boundAPI != EGL_OPENVG_API)
		EGL_RETURN(EGL_SUCCESS, EGL_NO_CONTEXT);

	EGLContext ret = EGL_NO_CONTEXT;
	thread = getCurrentThread();
	if(thread)
		ret = thread->m_context;
	EGL_RETURN(EGL_SUCCESS, ret);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLSurface eglGetCurrentSurface(EGLint readdraw)
{
	eglAcquireMutex();
	EGL_IF_ERROR(readdraw != EGL_READ && readdraw != EGL_DRAW, EGL_BAD_PARAMETER, EGL_NO_SURFACE);

	EGL* egl = getEGL();
	if(!egl)
		EGL_RETURN(EGL_BAD_ALLOC, EGL_NO_SURFACE);

	Thread* thread = getCurrentThread();
	if(!thread || thread->m_boundAPI != EGL_OPENVG_API)
		EGL_RETURN(EGL_SUCCESS, EGL_NO_SURFACE);

	if(thread->m_surface)
		EGL_RETURN(EGL_SUCCESS, thread->m_surface);
	EGL_RETURN(EGL_SUCCESS, EGL_NO_SURFACE);
}

/*-------------------------------------------------------------------*//*!
* \brief	Returns the current display
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLDisplay eglGetCurrentDisplay(void)
{
	eglAcquireMutex();

	EGL* egl = getEGL();
	if(!egl)
		EGL_RETURN(EGL_BAD_ALLOC, EGL_NO_DISPLAY);

	Thread* thread = getCurrentThread();
	if(!thread || thread->m_boundAPI != EGL_OPENVG_API || !thread->m_context)
		EGL_RETURN(EGL_SUCCESS, EGL_NO_DISPLAY);

	Context* ctx = thread->m_context;
	for(int i=0;i<egl->m_displays.size();i++)
	{
		for(int j=0;j<egl->m_displays[i]->m_contexts.size();j++)
		{
			if(egl->m_displays[i]->m_contexts[j] == ctx)
				EGL_RETURN(EGL_SUCCESS, egl->m_displays[i]->m_id);
		}
	}

	EGL_RETURN(EGL_SUCCESS, EGL_NO_DISPLAY);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglQueryContext(EGLDisplay dpy, EGLContext ctx, EGLint attribute, EGLint* value)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_FALSE);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_FALSE);
	EGL_IF_ERROR(!eglContextExists(display, ctx), EGL_BAD_CONTEXT, EGL_FALSE);
	EGL_IF_ERROR(attribute != EGL_CONFIG_ID && attribute != EGL_CONTEXT_CLIENT_TYPE, EGL_BAD_ATTRIBUTE, EGL_FALSE);
	if(attribute == EGL_CONFIG_ID)
		*value = display->m_configs[((Context*)ctx)->m_config].m_configID;
	if(attribute == EGL_CONTEXT_CLIENT_TYPE)
		*value = EGL_OPENVG_API;
	// \todo [kalle 05/Jul/05] Handling of EGL_RENDER_BUFFER attribute is missing.
	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglBindAPI(EGLenum api)
{
	eglAcquireMutex();
	EGL_IF_ERROR(api != EGL_OPENVG_API && api != EGL_OPENGL_ES_API, EGL_BAD_PARAMETER, EGL_FALSE);
	Thread* thread = getThread();
	if(thread)
		thread->m_boundAPI = api;
	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLenum eglQueryAPI(void)
{
	eglAcquireMutex();
	Thread* thread = getThread();
	if(thread)
		EGL_RETURN(EGL_SUCCESS, thread->m_boundAPI);
	EGL_RETURN(EGL_SUCCESS, EGL_NONE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglWaitClient()
{
	eglAcquireMutex();
	Thread* thread = getThread();
	if(thread && thread->m_boundAPI == EGL_OPENVG_API)
		vgFinish();
	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	Waits for OpenGL ES
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglWaitGL(void)
{
	return EGL_TRUE;
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		We don't support native rendering
*//*-------------------------------------------------------------------*/

EGLBoolean eglWaitNative(EGLint engine)
{
	RI_UNREF(engine);
	return EGL_TRUE;
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglSwapBuffers(EGLDisplay dpy, EGLSurface surface)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_FALSE);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_FALSE);
	EGL_IF_ERROR(!eglSurfaceExists(display, surface), EGL_BAD_SURFACE, EGL_FALSE);

	EGL* egl = getEGL();
	if(!egl)
		EGL_RETURN(EGL_BAD_ALLOC, EGL_FALSE);

	Surface* s = (Surface*)surface;
	ThreadID currentThreadID = getCurrentThreadID();
	Thread* currentThread = NULL;
	for(int i=0;i<egl->m_currentThreads.size();i++)
	{
		if(egl->m_currentThreads[i]->m_threadID == currentThreadID)
		{
			currentThread = egl->m_currentThreads[i];
			break;
		}
	}
	EGL_IF_ERROR(!currentThread || currentThread->m_surface != s, EGL_BAD_SURFACE, EGL_FALSE);

	vgFlush();

	if(!s->m_windowSurface)
	{	//do nothing for other than window surfaces (NOTE: single-buffered window surfaces should return immediately as well)
		EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
	}
	RI_ASSERT(currentThread);

	//TODO return EGL_BAD_NATIVE_WINDOW if the native window is no longer valid

	int currWin = glutGetWindow();
	glutSetWindow(s->m_window);
	int width = glutGet(GLUT_WINDOW_WIDTH);
	int height = glutGet(GLUT_WINDOW_HEIGHT);

	if(width != s->m_image->getWidth() || height != s->m_image->getHeight())
	{	//resize the back buffer
		Context* c = currentThread->m_context;
		RI_ASSERT(c);
		try
		{
			s->m_image->resize(width, height, Color(0,0,0,0,Color::lRGBA));	//throws bad_alloc
			s->m_mask->resize(width, height, Color(1,1,1,1,Color::lRGBA));	//throws bad_alloc
			c->m_vgContext->resize(s->m_image, s->m_mask);	//throws bad_alloc
		}
		catch(std::bad_alloc)
		{
			c->m_vgContext->resize(NULL, NULL);
			glutSetWindow(currWin);		//restore the current window
			EGL_RETURN(EGL_BAD_ALLOC, EGL_FALSE);
		}
	}

	//blit the image to screen using OpenGL's glDrawPixels
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glMatrixMode( GL_MODELVIEW );
	glLoadIdentity();
	int w = s->m_image->getWidth();
	int h = s->m_image->getHeight();
	try
	{
		unsigned int* tmp = RI_NEW_ARRAY(unsigned int, w*h);	//throws bad_alloc
		//NOTE: we assume here that the display is always sRGBA
		vgReadPixels(tmp, w*sizeof(unsigned int), VG_sRGBA_8888, 0, 0, w, h);
		glDrawPixels(w, h, GL_RGBA, GL_UNSIGNED_INT_8_8_8_8, tmp);
		RI_DELETE_ARRAY(tmp);
	}
	catch(std::bad_alloc)
	{
		//do nothing
	}
	glutSwapBuffers();	//shows the OpenGL frame buffer

	glutSetWindow(currWin);		//restore the current window

	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglCopyBuffers(EGLDisplay dpy, EGLSurface surface, NativePixmapType target)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_FALSE);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_FALSE);
	EGL_IF_ERROR(!eglSurfaceExists(display, surface), EGL_BAD_SURFACE, EGL_FALSE);
	EGL_IF_ERROR(!target || !isValidImageFormat(target->format) || !target->data || target->width <= 0 || target->height <= 0, EGL_BAD_NATIVE_PIXMAP, EGL_FALSE);
	try
	{
		Image output(Color::formatToDescriptor((VGImageFormat)target->format), target->width, target->height, target->stride, (RIuint8*)target->data);
		output.blit(*((Surface*)surface)->m_image, 0, 0, 0, 0, target->width, target->height, false);	//throws bad_alloc
	}
	catch(std::bad_alloc)
	{
	}
	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		We support only swap interval one
*//*-------------------------------------------------------------------*/

EGLBoolean eglSwapInterval(EGLDisplay dpy, EGLint interval)
{
	EGL_GET_DISPLAY(dpy);
	EGL_IF_ERROR(!display, EGL_NOT_INITIALIZED, EGL_FALSE);
	EGL_IF_ERROR(dpy != EGL_DEFAULT_DISPLAY, EGL_BAD_DISPLAY, EGL_FALSE);
	RI_UNREF(interval);
	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

typedef void RI_Proc();

void (*eglGetProcAddress(const char *procname))()
{
	if(!procname)
		return NULL;
	if(!RI_STRNCMP(procname, "eglSetConfigPreferenceHG", 24))
		return (RI_Proc*)eglSetConfigPreferenceHG;
	return NULL;
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglReleaseThread(void)
{
	eglAcquireMutex();
	EGL* egl = getEGL();
	if(!egl)
	{
		eglReleaseMutex();
		return EGL_FALSE;
	}

	//check if the thread is current
	Thread* thread = getCurrentThread();
	if(thread)
	{	//thread is current, release the old bindinds and remove the thread from the current thread list
		Context* pc = thread->m_context;
		Surface* ps = thread->m_surface;
		if(pc)
		{
			vgFlush();
			pc->m_vgContext->resize(NULL, NULL);
			if(!pc->removeReference())
				RI_DELETE(pc);
		}
		if(ps)
		{
			if(!ps->removeReference())
				RI_DELETE(ps);
		}

		//remove from the current thread list
		int i=0;
		for(;i<egl->m_currentThreads.size();i++)
		{
			if(egl->m_currentThreads[i] == thread)
				break;
		}
		RI_ASSERT(i < egl->m_currentThreads.size());	//thread not found from the list
		for(;i<egl->m_currentThreads.size()-1;i++)
		{
			egl->m_currentThreads[i] = egl->m_currentThreads[i+1];
		}
		egl->m_currentThreads.resize(egl->m_currentThreads.size()-1);
	}

	//delete the current thread
	int i=0;
	ThreadID currentThreadID = getCurrentThreadID();
	for(;i<egl->m_threads.size();i++)
	{
		if(currentThreadID == egl->m_threads[i]->m_threadID)
		{
			RI_DELETE(egl->m_threads[i]);
			egl->m_threads[i] = NULL;
			break;
		}
	}
	if(i == egl->m_threads.size())
	{
		eglReleaseMutex();
		return EGL_SUCCESS;	//thread hasn't been used yet from EGL
	}

	//remove the thread from EGL's list
	for(;i<egl->m_threads.size()-1;i++)
	{
		egl->m_threads[i] = egl->m_threads[i+1];
	}
	egl->m_threads.resize(egl->m_threads.size()-1);

	//destroy the EGL instance
	releaseEGL();

	eglReleaseMutex();
	return EGL_SUCCESS;
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

EGLBoolean eglSetConfigPreferenceHG (EGLBoolean useHybridPreference)
{
	eglAcquireMutex();
	Thread* thread = getThread();
	if(thread)
		thread->m_configPreferenceHG = useHybridPreference;
	EGL_RETURN(EGL_SUCCESS, EGL_TRUE);
}

/*-------------------------------------------------------------------*//*!
* \brief	
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

void* eglGetCurrentVGContext()
{
	//this function is always called inside OpenVG mutex
	Thread* thread = getCurrentThread();
	if(thread)
	{
		RI_ASSERT(thread->m_context && thread->m_surface);
		return thread->m_context->m_vgContext;
	}
	return NULL;	//not initialized or made current
}

/*-------------------------------------------------------------------*//*!
* \brief	Check if the image is current in any of the displays
* \param	
* \return	
* \note		This function is always called from mutexed API function
*//*-------------------------------------------------------------------*/

int eglIsInUse(void* image)
{
	EGL* egl = getEGL();
	RI_ASSERT(egl);
	for(int i=0;i<egl->m_currentThreads.size();i++)
	{
		Surface* s = egl->m_currentThreads[i]->m_surface;
		if(s && s->m_image == image)
			return 1;
	}
	return 0;
}
