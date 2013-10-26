#ifndef GFXIMAGE_H
#define GFXIMAGE_H

#include <SDL2/SDL.h>
#include <string>

#include "GfxElement.h"

class GfxImage : public GfxElement
{
	protected :
	
		SDL_Texture *m_pTexture;
		SDL_Rect	 m_renderingPos;
		SDL_Color	 m_color;
		
		std::string m_fileName;
		
		double m_angle;
		float  m_scale;

	public :
	
		GfxImage(int layer, const std::string &m_fileName);
		GfxImage(int layer, const std::string &m_fileName, const SDL_Rect &position);
		virtual ~GfxImage();
		
		virtual bool VInit(SDL_Renderer *pRenderer);
		virtual void VRender(SDL_Renderer *pRenderer);
		
		void SetAngle(double angle){ m_angle = angle; }
		double GetAngle() const{ return m_angle; }
		void SetScale(float scale){ m_scale = scale; }
		float GetScale() const{ return m_scale; }
		
		void SetColor(byte r, byte g, byte b);
		void ResetColor();
		SDL_Color GetColor() const{ return m_color; }
		
		virtual void VSetAlpha(byte alpha);
		
		//To complete
		virtual bool VIsVisible() const{ return true; }
};

#endif
