#include "ScrollProcess.h"
#include "../../GameApp/SDLApp.h"
#include "../../Graphics/GfxManager.h"

ScrollProcess::ScrollProcess(float speed, int layer):
m_speed(speed),
m_layer(layer)
{
}

ScrollProcess::~ScrollProcess()
{
}
