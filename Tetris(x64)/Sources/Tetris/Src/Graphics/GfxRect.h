#ifndef GFXRECT_H
#define GFXRECT_H

/**
 * \file GfxRect.h 
 * \brief Graphic Element representing a colored Rectangle 
 */

#include "GfxElement.h"

class GfxRect;

/// Typedef defining a rectangle shared pointer
typedef shared_ptr<GfxRect> GfxRectSharedPtr;

/**
 * \class GfxRect
 * \brief Graphic Element representing a colored Rectangle
 * 
 * Graphic element inheriting from GfxElement. It allows a colored 
 * rectangle to be rendered (useful for fadein/out).
 */
class GfxRect : public GfxElement
{
	private :
	
		float m_width, m_height;
	
	public :
	
		GfxRect(int layer);
		GfxRect(int layer, float posX, float posY);
		~GfxRect();
	
		virtual bool VInit(SDL_Renderer *pRenderer);
		virtual void VRender(SDL_Renderer* pRenderer);
		virtual bool VIsVisible() const;
		
		void SetDimensions(float w, float h);
		float GetWidth() const{ return m_width; }
		float GetHeight() const{ return m_height; }
};

#endif
