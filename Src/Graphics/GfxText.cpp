#include "GfxText.h"
#include "../Resource/FontResource.h"
#include "../Resource/ResourceManager.h"

GfxText::GfxText(int layer, const std::string &fileName, const std::string &text):
GfxImage(layer, fileName),
m_text(text)
{
}

GfxText::GfxText(int layer, const std::string &fileName, const std::string &text, float posX, float posY):
GfxImage(layer, fileName, posX, posY),
m_text(text)
{
}

GfxText::~GfxText()
{
}

bool GfxText::VInit(SDL_Renderer *pRenderer)
{
	const IResource* pResource = ResourceManager::Get()->GetResource(m_fileName.c_str(), RT_FONT);
	if(!pResource)
		return false;
		
	const FontResource* pFontResource = static_cast<const FontResource*>(pResource);
	
	SDL_Color color;
	color.r = 255;
	color.g = 255;
	color.b = 255;
	color.a = 255;
	
	SDL_Surface *pSurface = TTF_RenderText_Solid(pFontResource->GetFont(), m_text.c_str(), color);
	if(!pSurface)
	{
		ERROR("Failed to render TTF text : \"" << m_text << "\"");
		return false;
	}
	
	m_pTexture = SDL_CreateTextureFromSurface(pRenderer, pSurface);
	SDL_FreeSurface(pSurface);
	if(!m_pTexture)
	{
		ERROR("Failed to create texture from text : \"" << m_text << "\"");
		return false;
	}
	
	SDL_QueryTexture(m_pTexture, NULL, NULL, &m_width, &m_height);
	
	if(SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND) < 0)
	{
		ERROR("Failed to enable blending mode : " << m_fileName);
		return false;
	}
	
	return true;
}
