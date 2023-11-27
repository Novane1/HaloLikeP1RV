#include "ShootBar.h"
#include "glad/glad.h"
#include <glut.h>
#include "iostream"
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

    glColor3f(1.0, 0.0, 1.0);
    float ymax = -7.0f;
    float ymin = -8.0f;
    float xmax = 5.5f;
    float xmin = 0;
    glVertex3f(xmin, ymax, -10.0f);
    glVertex3f(xmin,ymin, -10.0f);

    glVertex3f(xmin+(amo/numAmoMax)*(xmax-xmin), ymax, -10.0f);
    glVertex3f(xmin + (amo / numAmoMax) * (xmax - xmin), ymin, -10.0f);

    glColor3f(0.5, 0.5, 0.5);
    glVertex3f(xmin + amo / numAmoMax, ymax, -10.0f);

    glVertex3f(xmin + amo / numAmoMax, ymin, -10.0f);

    glVertex3f(xmax, ymax, -10.0f);
    glVertex3f(xmax, ymin, -10.0f);
    
    glColor3f(1.0, 1.0, 1.0);
    glEnd();
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
}

void ShootBar::downAmo()
{
    amo-=10;
    if (amo < 0) { amo = 0; }
}

void ShootBar::resetAmo()
{
    amo = numAmoMax;
}

float ShootBar::getAmo()
{
    return amo;
}
