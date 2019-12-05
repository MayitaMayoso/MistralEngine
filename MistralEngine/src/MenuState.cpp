#include "MenuState.h"


MenuState::MenuState() {

	m_iCurrentSelection = 0;
	m_pFont = new CGameFont();
	m_pFont->CreateFont("Verdana", 30, FW_NORMAL);

	// Init de las img
	m_pBackgroundImg = new CImage("MainMenuBackground.png", TRectanglei(0, 600, 0, 800));
	m_pTitleImg = new CImage("MenuTitle.png", TRectanglei(0, 600, 0, 800));
	m_pItemNormal = new CImage("MenuItems.png", TRectanglei(0, 57, 0, 382));
	m_pItemSelected = new CImage("MenuItems.png", TRectanglei(58, 114, 0, 382));


	// Texto del menu
	m_pNewGameText = new CTextControl(m_pFont, TRectanglei(150, 207, 209, 591));
	m_pNewGameText->SetAlignement(CTextControl::TACenter);
	m_pNewGameText->SetText("New game");
	
	m_pResumeGameText = new CTextControl(m_pFont, TRectanglei(250, 307, 209, 591));
	m_pResumeGameText->SetAlignement(CTextControl::TACenter);
	m_pResumeGameText->SetText("Resume game");

	m_pExitText = new CTextControl(m_pFont, TRectanglei(450, 507, 209, 591));
	m_pExitText->SetAlignement(CTextControl::TACenter);
	m_pExitText->SetText("Exit");
}

MenuState::~MenuState() {

}

void MenuState::keyPressed(WPARAM key) {

	switch (key)
	{
	case VK_DOWN:
		SelectDown();
		break;
	case VK_UP:
		SelectUp();
		break;
	case VK_RETURN:
		SelectChosen();
		break;
	}
}

void MenuState::Draw() {

	m_pBackgroundImg->Draw();
	m_pTitleImg->Draw();
	// Draw the menu item backgrounds
	for (int i = 0; i < 3; i++)
	{
		if (i == m_iCurrentSelection)
			m_pItemSelected->Draw(200, 150 + i * 100);
		else
			m_pItemNormal->Draw(200, 150 + i * 100);
	}

	m_pNewGameText->Draw();
	m_pResumeGameText->Draw();
	m_pExitText->Draw();
}


void MenuState::SelectUp() {
	m_iCurrentSelection--;
	if (m_iCurrentSelection == -1)
		m_iCurrentSelection = 2;
}

void MenuState::SelectDown() {
	m_iCurrentSelection++;
	if (m_iCurrentSelection == 3)
		m_iCurrentSelection = 0;
}

void MenuState::SelectChosen() {

}
