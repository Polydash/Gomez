#ifndef GFXRESIMAGE_H
#define GFXRESIMAGE_H

#include "GfxResource.h"

class GfxResImage : public GfxResource
{
	private :
	
		std::string m_resName;
		
	public :
	
		GfxResImage(const std::string &resName);
		~GfxResImage();
		
		virtual bool VLoad();
};

#endif
