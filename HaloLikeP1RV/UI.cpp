#include "UI.h"
#include <GLFW/glfw3.h>
void UI::AddObject(Objet3D o)
{
	listeUI.push_back(o);
	isShowed.push_back(true);
}

void UI::changeState(bool b, int i)
{
	isShowed[i] = !isShowed[i];
}

void UI::affichage(std::vector<bool> keys)
{

	glDisable(GL_DEPTH_TEST);
	for (int i = 0; i < listeUI.size(); i++) {
		if (!(keys[GLFW_KEY_LEFT_SHIFT]))
		{
			frame = 0;
		}
		if (isShowed[i])
		{

			if ((i == 0))
			{
				glPushMatrix();
				glRotatef(-35, 1, 0, 0);
				glRotatef(10*sin(frame/25), 0, 1, 0);
				listeUI[i].affichage();
				glPopMatrix();
				frame += 1;
			}
			else
			{
				listeUI[i].affichage();
			}
			
		}
		
		
			
		
		
	}
	glEnable(GL_DEPTH_TEST);
	
}




