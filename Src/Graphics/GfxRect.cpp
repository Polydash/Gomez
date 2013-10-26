#include "GfxRect.h"

GfxRect::GfxRect(int layer):
GfxElement(layer)
{
}

GfxRect::GfxRect(int layer, const SDL_Rect &dimension):
GfxElement(layer, dimension)
{
	m_dimension.w = dimension.w;
	m_dimension.h = dimension.h;
}

GfxRect::~GfxRect()
{
}

bool GfxRect::VInit(SDL_Renderer *pRenderer)
{ 
	return true;
}

void GfxRect::VRender(SDL_Renderer* pRenderer)
{
	SDL_SetRenderDrawColor(pRenderer, m_color.r, m_color.g, m_color.b, m_color.a);
	SDL_RenderFillRect(pRenderer, &m_dimension);
}

bool GfxRect::VIsVisible() const
{
	return true;
}

void GfxRect::SetDimension(int x, int y, int w, int h)
{
	m_dimension.x = x;
	m_dimension.y = y;
	m_dimension.w = w;
	m_dimension.h = h;
}
void GfxRect::SetDimension(const SDL_Rect &dimension)
{
	m_dimension = dimension;
}
