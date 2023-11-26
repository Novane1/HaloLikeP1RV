#include "Crosshair.h"
#include "glad/glad.h"
#include <glut.h>

void Crosshair::affichageCrosshair()
{
    glPushMatrix();
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glDisable(GL_DEPTH_TEST);
    glTranslatef(0, 0, -100); // Placement du point de visée
    GLUquadricObj* quadric = gluNewQuadric();
    gluPartialDisk(quadric, 0.0, 1.0, 100, 1, 0.0, 360.0);
    glEnable(GL_DEPTH_TEST);
    glPopMatrix();
}
