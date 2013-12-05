/**
 * \file GfxElement.cpp 
 * \brief Graphic Element base class
 */

#include "GfxElement.h"
#include "../GameStd.h"
#include "../GameApp/SDLApp.h"

GfxElement::GfxElement(int layer):
m_posX(0.0f),
m_posY(0.0f),
m_layer(layer),
m_alpha(255)
{
}

GfxElement::GfxElement(int layer, float posX, float posY):
m_posX(posX),
m_posY(posY),
m_layer(layer),
m_alpha(255)
{
}

GfxElement::~GfxElement()
{
}

void GfxElement::SetPosition(float posX, float posY)
{
	m_posX = posX;
	m_posY = posY;
}

void GfxElement::Translate(float deltaX, float deltaY)
{
	m_posX += deltaX;
	m_posY += deltaY;
}

void GfxElement::VSetColor(byte r, byte g, byte b)
{
	m_color.r = r;
	m_color.g = g;
	m_color.b = b;
}
