#include "GfxRect.h"
#include "../GameApp/SDLApp.h"

GfxRect::GfxRect(int layer):
GfxElement(layer)
{
}

GfxRect::GfxRect(int layer, float posX, float posY):
GfxElement(layer, posX, posY)
{
}

GfxRect::~GfxRect()
{
}

bool GfxRect::VInit(SDL_Renderer *pRenderer)
{ 
	if(SDL_SetRenderDrawBlendMode(pRenderer, SDL_BLENDMODE_BLEND) < 0)
	{
		ERROR("Failed to enable blending mode");
		return false;
	}
	
	return true;
}

void GfxRect::VRender(SDL_Renderer* pRenderer)
{
	SDL_Rect renderingPos;
	
	renderingPos.x = m_posX - (m_width / 2);
	renderingPos.y = m_posY - (m_height / 2);
	renderingPos.w = m_width;
	renderingPos.h = m_height;
	
	SDL_SetRenderDrawColor(pRenderer, m_color.r, m_color.g, m_color.b, m_alpha);
	SDL_RenderFillRect(pRenderer, &renderingPos);
}

bool GfxRect::VIsVisible() const
{
	int sWidth    = g_pApp->GetScreenWidth();
	int sHeight   = g_pApp->GetScreenHeight();
	
	if(m_posX + m_width/2 < 0)
		return false;
		
	if(m_posX - m_width/2 > sWidth)
		return false;
		
	if(m_posY + m_height/2 < 0)
		return false;
		
	if(m_posY - m_height/2 > sHeight)
		return false;
	
	return true;
}

void GfxRect::SetDimensions(float w, float h)
{
	m_width = w;
	m_height = h;
}
