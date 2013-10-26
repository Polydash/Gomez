#include "GfxImage.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/ImageResource.h"

GfxImage::GfxImage(int layer, const std::string &fileName):
GfxElement(layer),
m_fileName(fileName),
m_angle(0.0),
m_scale(1.0f)
{
}

GfxImage::GfxImage(int layer, const std::string &fileName, const SDL_Rect &position):
GfxElement(layer, position),
m_fileName(fileName),
m_angle(0.0),
m_scale(1.0f)
{
} 

GfxImage::~GfxImage()
{
	if(m_pTexture)
	{
		SDL_DestroyTexture(m_pTexture);
		m_pTexture = NULL;
	}
}

bool GfxImage::VInit(SDL_Renderer *pRenderer)
{
	const IResource* pResource = ResourceManager::Get()->GetResource(m_fileName.c_str(), RT_IMG);
	if(!pResource)
		return false;
		
	const ImageResource* pImgResource = static_cast<const ImageResource*>(pResource);
	m_pTexture = pImgResource->CreateTexture(pRenderer);
	if(!m_pTexture)
		return false;
		
	int w, h;
	SDL_QueryTexture(m_pTexture, NULL, NULL, &w, &h);
	m_position.w = w;
	m_position.h = h;
	
	if(SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND) < 0)
	{
		ERROR("Failed to enable blending mode : " << m_fileName);
		return false;
	}
		
	return true;
}

void GfxImage::VRender(SDL_Renderer *pRenderer)
{	
	m_renderingPos.x = m_position.x - (m_position.w*m_scale / 2);
	m_renderingPos.y = m_position.y - (m_position.h*m_scale / 2);
	m_renderingPos.w = m_position.w*m_scale;
	m_renderingPos.h = m_position.h*m_scale;
	
	SDL_SetTextureAlphaMod(m_pTexture, m_alpha);
	SDL_RenderCopyEx(pRenderer, m_pTexture, NULL, &m_renderingPos, m_angle, NULL, SDL_FLIP_NONE);
}
