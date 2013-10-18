#ifndef GFXELEMENT_H
#define GFXELEMENT_H

#include <SDL/SDL.h>

class GfxElement
{
	private :
	
		SDL_Rect 	 m_position;
		SDL_Surface *m_pSurface;
		
	public :
	
		GfxElement(SDL_Surface* pSurface);
		GfxElement(SDL_Surface* pSurface, const SDL_Rect &position);
		~GfxElement();
		
		void SetPosition(int x, int y);
		void SetPosition(const SDL_Rect &pos);
		
		void Translate(int deltaX, int deltaY);
		void Translate(const SDL_Rect &deltaPos);
		
		const SDL_Rect& GetPosition() const;
		
		bool IsVisible() const;
		
	private :
	
		bool IsPointOnScreen(int x, int y, int sWidth, int sHeight) const;
};

#endif
