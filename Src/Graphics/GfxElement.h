#ifndef GFXELEMENT_H
#define GFXELEMENT_H

/**
 * \file GfxElement.h 
 * \brief Graphic Element base class
 */

#include <SDL2/SDL.h>
#include <tr1/memory>
using std::tr1::shared_ptr;

#include "../GameStd.h"

class GfxElement;

typedef shared_ptr<GfxElement> GfxElementSharedPtr;

class GfxElement
{
	protected :
	
		float m_posX, m_posY;
		SDL_Color m_color;

		int m_layer;
		byte m_alpha;
		
	public :
		
		GfxElement(int layer);
		GfxElement(int layer, float posX, float posY);
		virtual ~GfxElement();
		
		//Methods to override
		virtual bool VInit(SDL_Renderer *pRenderer) = 0;
		virtual void VRender(SDL_Renderer* pRenderer) = 0;
		virtual bool VIsVisible() const = 0;
		
		//Position methods
		void SetPosition(float posX, float posY);
		void Translate(float deltaX, float deltaY);
		const float GetPosX() const{ return m_posX; }
		const float GetPosY() const{ return m_posY; }
		
		virtual void VSetColor(byte r, byte g, byte b);
		SDL_Color GetColor() const{ return m_color; }
		
		//Alpha blending methods
		virtual void VSetAlpha(byte alpha){ m_alpha = alpha; }
		byte GetAlpha() const{ return m_alpha; } 
		
		//Layering
		int GetLayer() const{ return m_layer; }
};

#endif
