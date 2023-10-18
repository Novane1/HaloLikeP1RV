#include "UI.h"

void UI::AddObject(Objet3D o)
{
	listeUI.push_back(o);
	isShowed.push_back(true);
}

void UI::changeState(bool b, int i)
{
	isShowed[i] = !isShowed[i];
}

void UI::affichage()
{
	glDisable(GL_DEPTH_TEST);
	for (int i = 0; i < listeUI.size(); i++) {
		listeUI[i].affichage();
	}
	glEnable(GL_DEPTH_TEST);
	
}




