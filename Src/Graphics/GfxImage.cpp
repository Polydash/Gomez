#include "GfxImage.h"
#include "../Resource/ResourceManager.h"
#include "../Resource/ImageResource.h"
#include "../GameApp/SDLApp.h"

GfxImage::GfxImage(int layer, const std::string &fileName):
GfxElement(layer),
m_fileName(fileName),
m_width(0),
m_height(0),
m_angle(0.0),
m_scale(1.0f)
{
}

GfxImage::GfxImage(int layer, const std::string &fileName, float posX, float posY):
GfxElement(layer, posX, posY),
m_fileName(fileName),
m_width(0),
m_height(0),
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
		
	SDL_QueryTexture(m_pTexture, NULL, NULL, &m_width, &m_height);
	
	if(SDL_SetTextureBlendMode(m_pTexture, SDL_BLENDMODE_BLEND) < 0)
	{
		ERROR("Failed to enable blending mode : " << m_fileName);
		return false;
	}
		
	return true;
}

void GfxImage::VRender(SDL_Renderer *pRenderer)
{	
	SDL_Rect renderingPos;
	
	renderingPos.x = m_posX - (m_width*m_scale / 2);
	renderingPos.y = m_posY - (m_height*m_scale / 2);
	renderingPos.w = m_width*m_scale;
	renderingPos.h = m_height*m_scale;
	
	SDL_RenderCopyEx(pRenderer, m_pTexture, NULL, &renderingPos, m_angle, NULL, SDL_FLIP_NONE);
}

void GfxImage::VSetColor(byte r, byte g, byte b)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
	SDL_SetTextureColorMod(m_pTexture, r, g, b);
}

void GfxImage::ResetColor()
{
	VSetColor(255, 255, 255);
}

void GfxImage::VSetAlpha(byte alpha)
{
	m_alpha = alpha;
	SDL_SetTextureAlphaMod(m_pTexture, m_alpha);
}

bool GfxImage::VIsVisible() const
{
	int sWidth    = g_pApp->GetScreenWidth();
	int sHeight   = g_pApp->GetScreenHeight();
	
	float cornerX = m_posX - m_width/2;
	float cornerY = m_posY - m_height/2;
	float radius  = sqrt(pow(cornerX - m_posX, 2) + pow(cornerY - m_posY, 2));
	
	if(m_posX + radius < 0)
		return false;
		
	if(m_posX - radius > sWidth)
		return false;
		
	if(m_posY + radius < 0)
		return false;
		
	if(m_posY - radius > sHeight)
		return false;
	
	return true;
}
