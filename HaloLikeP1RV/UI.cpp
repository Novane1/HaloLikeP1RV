#include "UI.h"
#include <iostream>
#include <GLFW/glfw3.h>

void UI::AddObject(Objet3D o)
{
    listeUI.push_back(o);
    isShowed.push_back(true);
}

void UI::changeState(bool b, int i)
{
    isShowed[i] = b;
}

void UI::affichage(std::vector<bool> keys, std::vector<bool> mouseClick, Shader healthShader,glm::vec3 pos,glm::vec3 target,int health,int frameHealth)
{
	for (int i = 0; i < listeUI.size(); i++) {
		//reset des animations
		if (!(keys[GLFW_KEY_LEFT_SHIFT])) // si on ne court plus, fin des animations
		{
			frame = 0;
			frameRunKnife = 0;
		}
		if ((mouseClick[0]) && (frameRightClick == 0)) // Si on donne un coup de couteau (bouton gauche souris) et que l'on est pas déjà dans cette animation, on la lance
		{
			frameRightClick = 1;
		}
		if (frameRightClick >= 133) // Si on arrive à la fin de l'animation du coup de couteau, on remet la frame à 0
			// Une frame à 0 indique une animation qui n'est pas en cours
			// temps de l'animation de coup de couteau, fait à la main
		{
			frameRightClick = 0;
		}
		if (isShowed[i]) // si l'objet est bien affiché
		{
			// Arme
			//////////////////////////////////

			if ((i == 0) && (keys[GLFW_KEY_LEFT_SHIFT]))// arme + courir -> animation de course de l'arme
			{
				glPushMatrix();

				glRotatef(0, 1, 0, 0);
				glRotatef(-15, 1, 0, 0);
				glRotatef(10 * sin(frame / 5), 0, 1, 0);
				listeUI[i].affichage();
				glPopMatrix();
				frame += 1;
			}

			//Couteau
			/////////////////////////////////

			else if (((i == 1) || (i == 2) || (i == 3))) // ces 3 valeur de i correspondent au couteau
			{
				if (frameRightClick != 0) // si on est dans l'animation de coup de couteau
				{
					glPushMatrix();

					glRotatef(45 * sin(frameRightClick / 20), -1, 6, 3);// on l'affiche en focntion de la frame
					listeUI[i].affichage();
					glPopMatrix();
					frameRightClick += 1;// et on incrémente la frame
				}
				else if (keys[GLFW_KEY_LEFT_SHIFT]) // si on run avec le couteau (on fonctionnera de la mmême manière
				{
					glPushMatrix();

					glRotatef(20 * sin(frameRunKnife / 15), -1, 6, 3);
					listeUI[i].affichage();

					listeUI[i].affichage();
					glPopMatrix();
					frameRunKnife += 1;
				}
				else { listeUI[i].affichage(); }// si rien de spécial, on l'affiche juste
			}
			//Reste
			//////////////////////
			else if (i==4)
			{
				listeUI[i].affichageHeartBar(healthShader, pos, target, glm::vec3(0.0, 1.0, 0.0),health,frameHealth); // si rien de tout ca, on affiche juste
			}
			else
			{
				listeUI[i].affichage(); // si rien de tout ca, on affiche juste
			}

		}

		else // Si l'arme n'est pas affiché, c'est qu'on a changé de type d'arme
		{
			if (i == 0) { // si c'est l'arme qui n'est pas affiché, on reset son animation
				frame = 0;
			}
			if ((i == 1) || (i == 2) || (i == 3)) { // si c'est le couteau, on reset l'animation
				frameRightClick = 0; frameRunKnife = 0;
			}

		}

	}


}