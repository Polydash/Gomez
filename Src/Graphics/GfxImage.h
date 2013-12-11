#ifndef GFXIMAGE_H
#define GFXIMAGE_H

/**
 * \file GfxImage.h 
 * \brief Graphic Element representing an Image 
 */

#include <SDL2/SDL.h>
#include <string>

#include "GfxElement.h"

class GfxImage;

/// Typedef defining an image shared pointer
typedef shared_ptr<GfxImage> GfxImageSharedPtr;

/**
 * \class GfxImage
 * \brief Graphic Element representing an Image
 * 
 * Graphic element inheriting from GfxElement. It allows any image to be
 * rendered by loading a texture. It also allows rotation and scale
 * effects. 
 */
class GfxImage : public GfxElement
{
	protected :
	
		SDL_Texture *m_pTexture;
		
		std::string m_fileName;
		
		int	   m_width, m_height;
		double m_angle;
		float  m_scale;

	public :
	
		GfxImage(int layer, const std::string &m_fileName);
		GfxImage(int layer, const std::string &m_fileName, float posX, float posY);
		virtual ~GfxImage();
		
		virtual bool VInit(SDL_Renderer *pRenderer);
		virtual void VRender(SDL_Renderer *pRenderer);
		
		void SetAngle(double angle){ m_angle = angle; }
		double GetAngle() const{ return m_angle; }
		void SetScale(float scale){ m_scale = scale; }
		float GetScale() const{ return m_scale; }
		
		virtual void VSetColor(byte r, byte g, byte b);
		void ResetColor();
		
		virtual void VSetAlpha(byte alpha);
		
		virtual bool VIsVisible() const;
};

#endif
