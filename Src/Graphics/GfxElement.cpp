#include "GfxElement.h"
#include "../GameStd.h"
#include "../GameApp/SDLApp.h"

GfxElement::GfxElement(int layer):
m_layer(layer),
m_alpha(255)
{	
	m_dimension.x = 0;
	m_dimension.y = 0;
	m_dimension.w = 0;
	m_dimension.h = 0;
}

GfxElement::GfxElement(int layer, const SDL_Rect &position):
m_layer(layer),
m_alpha(255)
{
	m_dimension.x = position.x;
	m_dimension.y = position.y;
}

GfxElement::~GfxElement()
{
}

void GfxElement::SetPosition(int x, int y)
{
	m_dimension.x = x;
	m_dimension.y = y;
}

void GfxElement::SetPosition(const SDL_Rect &position)
{
	m_dimension.x = position.x;
	m_dimension.y = position.y;
}

void GfxElement::Translate(int deltaX, int deltaY)
{
	m_dimension.x += deltaX;
	m_dimension.y += deltaY;
}

void GfxElement::Translate(const SDL_Rect &deltaPos)
{
	m_dimension.x += deltaPos.x;
	m_dimension.y += deltaPos.y;
}

void GfxElement::VSetColor(byte r, byte g, byte b)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
}

const SDL_Rect& GfxElement::GetDimension() const
{
	return m_dimension;
}
