#ifndef _MENUSTATE_H_
#define _MENUSTATE_H_


#include "GameFont.h"
#include "TextControl.h"
#include "Image.h"

class MenuState
{

public:

	MenuState();
	~MenuState();

	void Draw();
	void keyPressed(WPARAM key); // switch of the keys pressed in the menu

private:

	void SelectUp();
	void SelectDown();
	void SelectChosen();

	CGameFont* m_pFont;
	int m_iCurrentSelection; // indice del elemento actual seleccionado del menu

	// Main backgrouind and title
	CImage* m_pBackgroundImg;
	CImage* m_pTitleImg;
	
	// Background of each element
	CImage* m_pItemNormal;
	CImage* m_pItemSelected;

	// Text
	CTextControl* m_pNewGameText;
	CTextControl* m_pResumeGameText;
	CTextControl* m_pExitText;

};

#endif  // _MENUSTATE_H_
