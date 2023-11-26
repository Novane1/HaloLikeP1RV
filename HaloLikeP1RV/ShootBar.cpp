#include "ShootBar.h"
#include "glad/glad.h"
#include <glut.h>
ShootBar::ShootBar()
{
	numAmoMax = 300.0f;
	amo = numAmoMax;
}

void ShootBar::affichage()
{
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST); 
    glBegin(GL_QUADS);

    glColor3f(1.0f, 0, 0);
    
    glVertex3f(-0.5f, 0.5f, -10.0f);
    glVertex3f(-0.5f,0.3f, -10.0f);

    glVertex3f(-0.5f+amo/numAmoMax, 0.5f, -10.0f);
    glVertex3f(-0.5f + amo / numAmoMax, 0.3f, -10.0f);

    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5f + amo / numAmoMax, 0.5f, -10.0f);
    glVertex3f(-0.5f + amo / numAmoMax, 0.3f, -10.0f);

    glVertex3f(0.5f, 0.5f, -10.0f);
    glVertex3f(0.5f, 0.3f, -10.0f);
    
    glColor3f(1.0, 1.0, 1.0);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
}

void ShootBar::downAmo()
{
    amo-=10;
    
}

void ShootBar::resetAmo()
{
    amo = numAmoMax;
}

float ShootBar::getAmo()
{
    return amo;
}
