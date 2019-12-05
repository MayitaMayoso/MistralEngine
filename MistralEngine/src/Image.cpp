
#include "Image.h"
#include "Exception.h"


using namespace std;

CImage::CImage(const string& strFileName) : m_rectTextureCoord(), m_pTexture(strFileName){
	
	// TODO set texture

	// TODO igualar margenes de la textura con su objeto rectangulo
	//m_rectTextureCoord.m_Top = m_rectTextureCoord.m_Left = 0;
	//m_rectTextureCoord.m_Bottom = m_pTexture->GetHeight();
	//m_rectTextureCoord.m_Right = m_pTexture->GetWidth();
}

CImage::CImage(const string& strFileName, const TRectanglei& textCoord) : m_rectTextureCoord(textCoord), m_pTexture(strFileName) {

	// TODO init texture

	// TODO set texture
}
  


CImage::~CImage()
{

}

void CImage::Draw() {




}

void CImage::Draw(int xOffset, int yOffset) const
{
		/*
		// TODO generar la textura en el buffer de opengl

		// get the coordinates of the image in the texture, expressed as a value from 0 to 1
		float Top	 = ((float)m_rectTextureCoord.m_Top) / m_pTexture->GetHeight();
		float Bottom = ((float)m_rectTextureCoord.m_Bottom) / m_pTexture->GetHeight();
		float Left   = ((float)m_rectTextureCoord.m_Left) / m_pTexture->GetWidth();
		float Right  = ((float)m_rectTextureCoord.m_Right) / m_pTexture->GetWidth();

		// Sets the limits of the texture in the buffer
		glBegin(GL_QUADS);

		glTexCoord2f(Left,Top);
		glVertex3i(xOffset,yOffset,0);

		glTexCoord2f(Left,Bottom);	
		glVertex3i(xOffset,yOffset+m_rectTextureCoord.GetHeight(),0);

		glTexCoord2f(Right,Bottom);	
		glVertex3i(xOffset+m_rectTextureCoord.GetWidth(),yOffset+m_rectTextureCoord.GetHeight(),0);
		
		glTexCoord2f(Right,Top);	
		glVertex3i(xOffset+m_rectTextureCoord.GetWidth(),yOffset,0);

		glEnd();
		*/
	
}



