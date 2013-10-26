#ifndef GFXELEMENT_H
#define GFXELEMENT_H

#include <SDL2/SDL.h>

#include "../GameStd.h"

class GfxElement
{
	protected :
	
		SDL_Rect  m_dimension;
		SDL_Color m_color;

		int m_layer;
		byte m_alpha;
		
	public :
		
		GfxElement(int layer);
		GfxElement(int layer, const SDL_Rect &position);
		virtual ~GfxElement();
		
		//Methods to override
		virtual bool VInit(SDL_Renderer *pRenderer) = 0;
		virtual void VRender(SDL_Renderer* pRenderer) = 0;
		virtual bool VIsVisible() const = 0;
		
		//Position methods
		void SetPosition(int x, int y);
		void SetPosition(const SDL_Rect &pos);
		void Translate(int deltaX, int deltaY);
		void Translate(const SDL_Rect &deltaPos);
		const SDL_Rect& GetDimension() const;
		
		virtual void VSetColor(byte r, byte g, byte b);
		SDL_Color GetColor() const{ return m_color; }
		
		//Alpha blending methods
		virtual void VSetAlpha(byte alpha){ m_alpha = alpha; }
		byte GetAlpha() const{ return m_alpha; } 
		
		//Layering
		int GetLayer() const{ return m_layer; }
};

#endif
