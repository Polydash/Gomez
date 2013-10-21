#include "GfxElement.h"
#include "../GameStd.h"
#include "../GameApp/SDLApp.h"

GfxElement::GfxElement(SDL_Surface *pSurface, int layer):
m_pSurface(pSurface),
m_layer(layer)
{
	if(!pSurface)
		ERROR("GfxElement initialized with null pointer");
	
	m_position.x = 0;
	m_position.y = 0;
}

GfxElement::GfxElement(SDL_Surface *pSurface, int layer, const SDL_Rect &position):
m_position(position),
m_pSurface(pSurface),
m_layer(layer)
{
	if(!pSurface)
		ERROR("GfxElement initialized with null pointer");
}

GfxElement::~GfxElement()
{
}

void GfxElement::SetPosition(int x, int y)
{
	m_position.x = x;
	m_position.y = y;
}

void GfxElement::SetPosition(const SDL_Rect &position)
{
	m_position = position;
}

void GfxElement::Translate(int deltaX, int deltaY)
{
	m_position.x += deltaX;
	m_position.y += deltaY;
}

void GfxElement::Translate(const SDL_Rect &deltaPos)
{
	m_position.x += deltaPos.x;
	m_position.y += deltaPos.y;
}

const SDL_Rect& GfxElement::GetPosition() const
{
	return m_position;
}

bool GfxElement::IsVisible() const
{
	int sWidth  = g_pApp->GetScreenWidth();
	int sHeight = g_pApp->GetScreenHeight();
	int posX    = m_position.x;
	int posY	= m_position.y;
	int width	= m_pSurface->w;
	int height	= m_pSurface->h;
	
	if(IsPointOnScreen(posX, posY, sWidth, sHeight))
		return true;
	
	if(IsPointOnScreen(posX + width, posY, sWidth, sHeight))
		return true;
		
	if(IsPointOnScreen(posX + width, posY + height, sWidth, sHeight))
		return true;
	
	if(IsPointOnScreen(posX, posY + height, sWidth, sHeight))
		return true;
	
	return false;
}

bool GfxElement::IsPointOnScreen(int x, int y, int sWidth, int sHeight) const
{
	return (x >= 0 && x <= sWidth && y >= 0 && y <= sHeight);
}
