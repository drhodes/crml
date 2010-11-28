/*------------------------------------------------------------------------
 *
 * OpenVG 1.0.1 Reference Implementation sample code
 * -------------------------------------------------
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
 * \brief	Tiger sample application. Resizing the application window
 *			rerenders the tiger in the new resolution. Pressing 1,2,3
 *			or 4 sets pixel zoom factor, mouse moves inside the zoomed
 *			image.
 * \note	
 *//*-------------------------------------------------------------------*/

#ifdef WIN32
#pragma warning(disable:4115)	/* named type definition in parentheses (this comes from a visual studio include file) */
#include <windows.h>
#include <gl/gl.h>
#include <gl/glut.h>
#include <gl/glext.h>
#pragma warning(disable:4505)	/* unreferenced local function has been removed (this comes from GLUT)*/

#elif defined __APPLE__

#include <OpenGL/gl.h>
#include <GLUT/glut.h>
#endif

#include <stdio.h>
#include <stdarg.h>
#include <assert.h>
#include <string.h>
#define UNREF(X) ((void)(X))

#ifdef HG_FLAT_INCLUDES
#	include "openvg.h"
#	include "vgu.h"
#	include "egl.h"
#else
#	include "VG/openvg.h"
#	include "VG/vgu.h"
#	include "EGL/egl.h"
#endif

#include "tiger.h"

/*--------------------------------------------------------------*/

float				pixelScale = 1.0f;
float				aspectRatio;
int					initialWidth;
int					initialHeight;
int					rerender = 1;
float				mousex, mousey;
int					mouseButton = 0;
int					window;
EGLDisplay			egldisplay;
EGLConfig			eglconfig;
EGLSurface			eglsurface;
EGLContext			eglcontext;

/*--------------------------------------------------------------*/

typedef struct
{
	VGFillRule		m_fillRule;
	VGPaintMode		m_paintMode;
	VGCapStyle		m_capStyle;
	VGJoinStyle		m_joinStyle;
	float			m_miterLimit;
	float			m_strokeWidth;
	VGPaint			m_fillPaint;
	VGPaint			m_strokePaint;
	VGPath			m_path;
} PathData;

typedef struct
{
	PathData*			m_paths;
	int					m_numPaths;
} PS;

PS* PS_construct(const char* commands, int commandCount, const float* points, int pointCount)
{
	PS* ps = (PS*)malloc(sizeof(PS));
	int p = 0;
	int c = 0;
	int i = 0;
	int paths = 0;
	int maxElements = 0;
	unsigned char* cmd;
	UNREF(pointCount);

	while(c < commandCount)
	{
		int elements, e;
		c += 4;
		p += 8;
		elements = (int)points[p++];
		assert(elements > 0);
		if(elements > maxElements)
			maxElements = elements;
		for(e=0;e<elements;e++)
		{
			switch(commands[c])
			{
			case 'M': p += 2; break;
			case 'L': p += 2; break;
			case 'C': p += 6; break;
			case 'E': break;
			default:
				assert(0);		//unknown command
			}
			c++;
		}
		paths++;
	}

	ps->m_numPaths = paths;
	ps->m_paths = (PathData*)malloc(paths * sizeof(PathData));
	cmd = (unsigned char*)malloc(maxElements);

	i = 0;
	p = 0;
	c = 0;
	while(c < commandCount)
	{
		int elements, startp, e;
		float color[4];

		//fill type
		int paintMode = 0;
		ps->m_paths[i].m_fillRule = VG_NON_ZERO;
		switch( commands[c] )
		{
		case 'N':
			break;
		case 'F':
			ps->m_paths[i].m_fillRule = VG_NON_ZERO;
			paintMode |= VG_FILL_PATH;
			break;
		case 'E':
			ps->m_paths[i].m_fillRule = VG_EVEN_ODD;
			paintMode |= VG_FILL_PATH;
			break;
		default:
			assert(0);		//unknown command
		}
		c++;

		//stroke
		switch( commands[c] )
		{
		case 'N':
			break;
		case 'S':
			paintMode |= VG_STROKE_PATH;
			break;
		default:
			assert(0);		//unknown command
		}
		ps->m_paths[i].m_paintMode = (VGPaintMode)paintMode;
		c++;

		//line cap
		switch( commands[c] )
		{
		case 'B':
			ps->m_paths[i].m_capStyle = VG_CAP_BUTT;
			break;
		case 'R':
			ps->m_paths[i].m_capStyle = VG_CAP_ROUND;
			break;
		case 'S':
			ps->m_paths[i].m_capStyle = VG_CAP_SQUARE;
			break;
		default:
			assert(0);		//unknown command
		}
		c++;

		//line join
		switch( commands[c] )
		{
		case 'M':
			ps->m_paths[i].m_joinStyle = VG_JOIN_MITER;
			break;
		case 'R':
			ps->m_paths[i].m_joinStyle = VG_JOIN_ROUND;
			break;
		case 'B':
			ps->m_paths[i].m_joinStyle = VG_JOIN_BEVEL;
			break;
		default:
			assert(0);		//unknown command
		}
		c++;

		//the rest of stroke attributes
		ps->m_paths[i].m_miterLimit = points[p++];
		ps->m_paths[i].m_strokeWidth = points[p++];

		//paints
		color[0] = points[p++];
		color[1] = points[p++];
		color[2] = points[p++];
		color[3] = 1.0f;
		ps->m_paths[i].m_strokePaint = vgCreatePaint();
		vgSetParameteri(ps->m_paths[i].m_strokePaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
		vgSetParameterfv(ps->m_paths[i].m_strokePaint, VG_PAINT_COLOR, 4, color);

		color[0] = points[p++];
		color[1] = points[p++];
		color[2] = points[p++];
		color[3] = 1.0f;
		ps->m_paths[i].m_fillPaint = vgCreatePaint();
		vgSetParameteri(ps->m_paths[i].m_fillPaint, VG_PAINT_TYPE, VG_PAINT_TYPE_COLOR);
		vgSetParameterfv(ps->m_paths[i].m_fillPaint, VG_PAINT_COLOR, 4, color);

		//read number of elements

		elements = (int)points[p++];
		assert(elements > 0);
		startp = p;
		for(e=0;e<elements;e++)
		{
			switch( commands[c] )
			{
			case 'M':
				cmd[e] = VG_MOVE_TO | VG_ABSOLUTE;
				p += 2;
				break;
			case 'L':
				cmd[e] = VG_LINE_TO | VG_ABSOLUTE;
				p += 2;
				break;
			case 'C':
				cmd[e] = VG_CUBIC_TO | VG_ABSOLUTE;
				p += 6;
				break;
			case 'E':
				cmd[e] = VG_CLOSE_PATH;
				break;
			default:
				assert(0);		//unknown command
			}
			c++;
		}

		ps->m_paths[i].m_path = vgCreatePath(VG_PATH_FORMAT_STANDARD, VG_PATH_DATATYPE_F, 1.0f, 0.0f, 0, 0, (unsigned int)VG_PATH_CAPABILITY_ALL);
		vgAppendPathData(ps->m_paths[i].m_path, elements, cmd, points + startp);
		i++;
	}
	free(cmd);
	return ps;
}

void PS_destruct(PS* ps)
{
	int i;
	assert(ps);
	for(i=0;i<ps->m_numPaths;i++)
	{
		vgDestroyPaint(ps->m_paths[i].m_fillPaint);
		vgDestroyPaint(ps->m_paths[i].m_strokePaint);
		vgDestroyPath(ps->m_paths[i].m_path);
	}
	free(ps->m_paths);
	free(ps);
}

void PS_render(PS* ps)
{
	int i;
	assert(ps);
	vgSeti(VG_BLEND_MODE, VG_BLEND_SRC_OVER);

	for(i=0;i<ps->m_numPaths;i++)
	{
		vgSeti(VG_FILL_RULE, ps->m_paths[i].m_fillRule);
		vgSetPaint(ps->m_paths[i].m_fillPaint, VG_FILL_PATH);

		if(ps->m_paths[i].m_paintMode & VG_STROKE_PATH)
		{
			vgSetf(VG_STROKE_LINE_WIDTH, ps->m_paths[i].m_strokeWidth);
			vgSeti(VG_STROKE_CAP_STYLE, ps->m_paths[i].m_capStyle);
			vgSeti(VG_STROKE_JOIN_STYLE, ps->m_paths[i].m_joinStyle);
			vgSetf(VG_STROKE_MITER_LIMIT, ps->m_paths[i].m_miterLimit);
			vgSetPaint(ps->m_paths[i].m_strokePaint, VG_STROKE_PATH);
		}

		vgDrawPath(ps->m_paths[i].m_path, ps->m_paths[i].m_paintMode);
	}
	assert(vgGetError() == VG_NO_ERROR);
}

PS* tiger = NULL;

/*--------------------------------------------------------------*/

char kbdBuffer[256];
void mainloop(void);
const char * STR(const char *format, ...)
{
	static char string[1024];
	va_list arg;
    va_start( arg, format );
    vsprintf( string, format, arg );
    va_end( arg );
	return string;
}
void kbdfunc(unsigned char key, int x, int y)
{
	UNREF(x);
	UNREF(y);
	kbdBuffer[key] = 1;

	if( key == 27 )
		exit(0);	//esc or alt-F4 exits
	if( key == '1' ) pixelScale = 1.0f;
	if( key == '2' ) pixelScale = 2.0f;
	if( key == '3' ) pixelScale = 4.0f;
	if( key == '4' ) pixelScale = 16.0f;
}
void kbdupfunc(unsigned char key, int x, int y)
{
	UNREF(x);
	UNREF(y);
	kbdBuffer[key] = 0;
}
void specialfunc(int key, int x, int y)
{
	UNREF(x);
	UNREF(y);
	if( key == GLUT_KEY_F4 && glutGetModifiers() == GLUT_ACTIVE_ALT )
		exit(0);	//esc or alt-F4 exits
	kbdBuffer[key] = 1;
}
void specialupfunc(int key, int x, int y)
{
	UNREF(x);
	UNREF(y);
	kbdBuffer[key] = 0;
}
void mousefunc(int x, int y)
{
	mousex = (float)x;
	mousey = (float)(glutGet(GLUT_WINDOW_HEIGHT) - y);
}
void mouseButtonFunc(int button, int state, int x, int y)
{
	UNREF(x);
	UNREF(y);
	if( button == GLUT_LEFT_BUTTON )
		mouseButton = (state == GLUT_DOWN);
}
void idlefunc(void) { glutPostRedisplay(); }
void reshape(int w, int h)
{
	eglSwapBuffers(egldisplay, eglsurface);	//resizes the rendering surface
	glViewport(0,0,w,h);
	glutSetWindowTitle(STR("OpenVG Tiger sample (%dx%d)",w,h));
	rerender = 1;
}
void exitfunc(void)
{
	PS_destruct(tiger);
	eglMakeCurrent(egldisplay, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
	assert(eglGetError() == EGL_SUCCESS);
	eglTerminate(egldisplay);
	assert(eglGetError() == EGL_SUCCESS);
}

/*--------------------------------------------------------------*/

void mainloop(void)
{
#ifdef WIN32
	static PFNGLWINDOWPOS2FPROC glWindowPos2f = NULL;
	if (!glWindowPos2f)
		glWindowPos2f = (PFNGLWINDOWPOS2FPROC)wglGetProcAddress("glWindowPos2f");
#endif

	if(rerender)
	{
		int w = glutGet(GLUT_WINDOW_WIDTH);
		int h = glutGet(GLUT_WINDOW_HEIGHT);
		float clearColor[4] = {1,1,1,1};
		float scale = w / (tigerMaxX - tigerMinX);

		vgSetfv(VG_CLEAR_COLOR, 4, clearColor);
		vgClear(0, 0, w, h);

		vgLoadIdentity();
		vgScale(scale, scale);
		vgTranslate(-tigerMinX, -tigerMinY + 0.5f * (h / scale - (tigerMaxY - tigerMinY)));

		PS_render(tiger);
		assert(vgGetError() == VG_NO_ERROR);
		rerender = 0;
	}

	//clear screen and set position and zoom for glDrawPixels called from eglSwapBuffers
	glColor3f(0,0,0);
	glClear(GL_COLOR_BUFFER_BIT);
	if(glWindowPos2f)
		glWindowPos2f(mousex * (1.0f - pixelScale), mousey * (1.0f - pixelScale));
	glPixelZoom(pixelScale, pixelScale);

	eglSwapBuffers(egldisplay, eglsurface);	//copies the OpenVG back buffer to window (uses internally glDrawPixels)
	assert(eglGetError() == EGL_SUCCESS);
}

/*--------------------------------------------------------------*/

int main(void)
{
	int c = 1;
	char empty[] = "tiger.exe";
	char* param = (char*)empty;
	static const EGLint s_configAttribs[] =
	{
		EGL_RED_SIZE,		8,
		EGL_GREEN_SIZE, 	8,
		EGL_BLUE_SIZE,		8,
		EGL_ALPHA_SIZE, 	8,
		EGL_LUMINANCE_SIZE, EGL_DONT_CARE,			//EGL_DONT_CARE
		EGL_SURFACE_TYPE,	EGL_WINDOW_BIT,
		EGL_NONE
	};
	EGLint numconfigs;

	aspectRatio = (tigerMaxY - tigerMinY) / (tigerMaxX - tigerMinX);
	initialWidth = 400;
	initialHeight = (int)(aspectRatio * initialWidth);

	memset(kbdBuffer,0,256*sizeof(char));

	//open a window using GLUT
	glutInit( &c, &param );
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
	glutInitWindowSize(initialWidth, initialHeight);
	window = glutCreateWindow("OpenVG Tiger sample");

	//initialize EGL
	egldisplay = eglGetDisplay(EGL_DEFAULT_DISPLAY);
	eglInitialize(egldisplay, NULL, NULL);
	assert(eglGetError() == EGL_SUCCESS);
	eglBindAPI(EGL_OPENVG_API);

	eglChooseConfig(egldisplay, s_configAttribs, &eglconfig, 1, &numconfigs);
	assert(eglGetError() == EGL_SUCCESS);
	assert(numconfigs == 1);

	eglsurface = eglCreateWindowSurface(egldisplay, eglconfig, (void*)window, NULL);
	assert(eglGetError() == EGL_SUCCESS);
	eglcontext = eglCreateContext(egldisplay, eglconfig, NULL, NULL);
	assert(eglGetError() == EGL_SUCCESS);
	eglMakeCurrent(egldisplay, eglsurface, eglsurface, eglcontext);
	assert(eglGetError() == EGL_SUCCESS);

	tiger = PS_construct(tigerCommands, tigerCommandCount, tigerPoints, tigerPointCount);

	glutDisplayFunc(mainloop);
	glutKeyboardFunc(kbdfunc);
	glutPassiveMotionFunc(mousefunc);
	glutMotionFunc(mousefunc);
	glutMouseFunc(mouseButtonFunc);
	glutSpecialFunc(specialfunc);
	glutKeyboardUpFunc(kbdupfunc);
	glutSpecialUpFunc(specialupfunc);
	glutReshapeFunc(reshape);
	glutIdleFunc(idlefunc);
	atexit(exitfunc);
	glutMainLoop();
	return 0;
}

/*--------------------------------------------------------------*/
