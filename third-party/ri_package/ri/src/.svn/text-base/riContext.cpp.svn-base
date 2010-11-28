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
 * \brief	Implementation of VGContext functions.
 * \note	
 *//*-------------------------------------------------------------------*/

#include "riContext.h"

namespace OpenVGRI
{

/*-------------------------------------------------------------------*//*!
* \brief	VGContext constructor.
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

VGContext::VGContext(VGContext* shareContext) :
	// Mode settings
	m_matrixMode(VG_MATRIX_PATH_USER_TO_SURFACE),
	m_fillRule(VG_EVEN_ODD),
	m_imageQuality(VG_IMAGE_QUALITY_FASTER),
	m_renderingQuality(VG_RENDERING_QUALITY_BETTER),
	m_blendMode(VG_BLEND_SRC_OVER),
	m_imageMode(VG_DRAW_IMAGE_NORMAL),

	// Scissor rectangles
	m_scissor(),
		
	// Stroke parameters
	m_strokeLineWidth(1.0f),
	m_strokeCapStyle(VG_CAP_BUTT),
	m_strokeJoinStyle(VG_JOIN_MITER),
	m_strokeMiterLimit(4.0f),
	m_strokeDashPattern(),
	m_strokeDashPhase(0.0f),
	m_strokeDashPhaseReset(VG_FALSE),
		
	// Edge fill color for vgConvolve and pattern paint
	m_tileFillColor(0,0,0,0, Color::sRGBA),
		
	// Color for vgClear
	m_clearColor(0,0,0,0, Color::sRGBA),

	m_masking(VG_FALSE),
	m_scissoring(VG_FALSE),

	m_pixelLayout(VG_PIXEL_LAYOUT_UNKNOWN),

	m_filterFormatLinear(VG_FALSE),
	m_filterFormatPremultiplied(VG_FALSE),
	m_filterChannelMask(VG_RED|VG_GREEN|VG_BLUE|VG_ALPHA),

	// Matrices
	m_pathUserToSurface(),
	m_imageUserToSurface(),
	m_fillPaintToUser(),
	m_strokePaintToUser(),

	m_fillPaint(VG_INVALID_HANDLE),
	m_strokePaint(VG_INVALID_HANDLE),

	m_error(VG_NO_ERROR),

	m_imageManager(NULL),
	m_pathManager(NULL),
	m_paintManager(NULL),
	m_backBuffer(NULL),
	m_mask(NULL)
{
	if(shareContext)
	{
		m_imageManager = shareContext->m_imageManager;
		m_pathManager = shareContext->m_pathManager;
		m_paintManager = shareContext->m_paintManager;
	}
	else
	{
		try
		{
			m_imageManager = RI_NEW(OpenVGRI::ResourceManager<Image>, ());	//throws bad_alloc
			m_pathManager = RI_NEW(OpenVGRI::ResourceManager<Path>, ());	//throws bad_alloc
			m_paintManager = RI_NEW(OpenVGRI::ResourceManager<Paint>, ());	//throws bad_alloc
		}
		catch(std::bad_alloc)
		{
			RI_DELETE(m_imageManager);
			RI_DELETE(m_pathManager);
			RI_DELETE(m_paintManager);
			throw;
		}
	}
	RI_ASSERT(m_imageManager);
	RI_ASSERT(m_pathManager);
	RI_ASSERT(m_paintManager);
	m_imageManager->addReference();
	m_pathManager->addReference();
	m_paintManager->addReference();
}

/*-------------------------------------------------------------------*//*!
* \brief	VGContext destructor.
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

VGContext::~VGContext()
{
	releasePaint(VG_FILL_PATH | VG_STROKE_PATH);

	//destroy own images, paths and paints
	while(Image* i = m_imageManager->getFirstResource(this))
		m_imageManager->removeResource(i);
	while(Path* p = m_pathManager->getFirstResource(this))
		m_pathManager->removeResource(p);
	while(Paint* t = m_paintManager->getFirstResource(this))
		m_paintManager->removeResource(t);

	//decrease the reference count of resource managers
	if(!m_imageManager->removeReference())
		RI_DELETE(m_imageManager);
	if(!m_pathManager->removeReference())
		RI_DELETE(m_pathManager);
	if(!m_paintManager->removeReference())
		RI_DELETE(m_paintManager);

	RI_ASSERT(!m_mask);	//mask image has been destroyed already by resize(NULL)
}

/*-------------------------------------------------------------------*//*!
* \brief	Sets a new backbuffer and resizes the mask image to match.
* \param	backBuffer New backbuffer image or NULL when context is unbound
* \return	
* \note		if mask resizing fails, the old mask image is retained
*//*-------------------------------------------------------------------*/

void VGContext::resize(Image* backBuffer, Image* maskBuffer)
{
	m_backBuffer = NULL;
	m_mask = NULL;
	if( backBuffer )
	{
		RI_ASSERT(maskBuffer);
		m_backBuffer = backBuffer;
		m_mask = maskBuffer;
	}
}

/*-------------------------------------------------------------------*//*!
* \brief	Returns true if the given image is generated through any
*			context that is shared with this one.
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

bool VGContext::isValidImage(VGImage image)
{
	return m_imageManager->isValid((Image*)image);
}

/*-------------------------------------------------------------------*//*!
* \brief	Returns true if the given path is generated through any
*			context that is shared with this one.
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

bool VGContext::isValidPath(VGPath path)
{
	return m_pathManager->isValid((Path*)path);
}

/*-------------------------------------------------------------------*//*!
* \brief	Returns true if the given paint is generated through any
*			context that is shared with this one.
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

bool VGContext::isValidPaint(VGPaint paint)
{
	return m_paintManager->isValid((Paint*)paint);
}

/*-------------------------------------------------------------------*//*!
* \brief	Releases the given paint objects of the context.
* \param	
* \return	
* \note		
*//*-------------------------------------------------------------------*/

void VGContext::releasePaint(VGbitfield paintModes)
{
	if(paintModes & VG_FILL_PATH)
	{
		//release previous paint
		Paint* prev = (Paint*)m_fillPaint;
		if(prev)
		{
			if(!prev->removeReference())
				RI_DELETE(prev);
		}
		m_fillPaint = VG_INVALID_HANDLE;
	}
	if(paintModes & VG_STROKE_PATH)
	{
		//release previous paint
		Paint* prev = (Paint*)m_strokePaint;
		if(prev)
		{
			if(!prev->removeReference())
				RI_DELETE(prev);
		}
		m_strokePaint = VG_INVALID_HANDLE;
	}
}

//==============================================================================================

}	//namespace OpenVGRI
