#ifndef GFXRESIMAGE_H
#define GFXRESIMAGE_H

#include "GfxResource.h"

class GfxResImage : public GfxResource
{
	private :
	
		std::string m_fileName;
		
	public :
	
		GfxResImage(const std::string &resName, const std::string &fileName);
		~GfxResImage();
		
		virtual bool VLoad();
		
		const std::string& GetFileName() const{ return m_fileName; }
};

#endif
