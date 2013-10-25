#ifndef GFXELEMENT_H
#define GFXELEMENT_H

#include <SDL/SDL.h>

#include "../GameStd.h"

class GfxElement
{
	private :
	
		SDL_Rect m_position;

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
		virtual void VSetAlpha(byte alpha) = 0;
		byte GetAlpha() const{ return m_alpha; } 
		
		//Layering
		int GetLayer() const{ return m_layer; }
		
		//Visibility
		virtual bool VIsVisible() const = 0;
		
	private :
	
		//Visibilty helper function
		bool IsPointOnScreen(int x, int y, int sWidth, int sHeight) const;
};

#endif
