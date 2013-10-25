#include "GfxElement.h"
#include "../GameStd.h"
#include "../GameApp/SDLApp.h"

GfxElement::GfxElement(int layer):
m_pTexture(NULL),
m_layer(layer),
m_alpha(255)
{	
	m_position.x = 0;
	m_position.y = 0;
}

GfxElement::GfxElement(int layer, const SDL_Rect &position):
m_position(position),
m_pTexture(NULL),
m_layer(layer),
m_alpha(255)
{
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
