#ifndef _IMAGE_H_
#define _IMAGE_H_


#include "Rectangle.h"
#include "SmartPtr.h"
#include "Model.h"


class CImage;

// Not needed
typedef CSmartPtr<CImage> TImagePtr;

class CImage
{
public:

	CImage(const std::string& strFileName);
	CImage(const std::string& strFileName, const TRectanglei& textCoord);
	~CImage();
	void Draw();
	void Draw(int iXOffset, int iYOffset) const;

private:
	
	// TODO CTexture*   m_pTexture;
	Model m_pTexture;
	// Rectangle that defines the position of the texture in screen
	TRectanglei  m_rectTextureCoord;
};

#endif  // _IMAGE_H_