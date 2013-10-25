#ifndef GFXELEMENT_H
#define GFXELEMENT_H

#include <SDL2/SDL.h>

#include "../GameStd.h"

class GfxElement
{
	private :
	
		SDL_Rect 	 m_position;
		SDL_Texture	*m_pTexture;

		int m_layer;
		byte m_alpha;
		
	public :
	
		GfxElement(int layer);
		GfxElement(int layer, const SDL_Rect &position);
		virtual ~GfxElement();
		
		//Main method 
		virtual void VRender(SDL_Surface* pScreen) = 0;
		
		//Position methods
		void SetPosition(int x, int y);
		void SetPosition(const SDL_Rect &pos);
		void Translate(int deltaX, int deltaY);
		void Translate(const SDL_Rect &deltaPos);
		const SDL_Rect& GetPosition() const;
		
		//Alpha blending methods
		virtual void VSetAlpha(byte alpha){ m_alpha = alpha; }
		byte GetAlpha() const{ return m_alpha; } 
		
		//Layering
		int GetLayer() const{ return m_layer; }
		
		//Visibility
		virtual bool VIsVisible() const = 0;
};

#endif
