/*
 * World.cpp
 *
 *  Created on: 29 de mai de 2018
 *      Author: J�lio Sena
 */

#include "World.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <time.h>

void solidSphereIntern(float radius, int stacks, int columns);
int numberRandon(int smaller, int bigger);

World::World(float angle, float angleSatellitesfloat, float pos[], float scale, int numberSatellites, bool isEarth) {
	// TODO Auto-generated constructor stub
	glPushMatrix();
		glRotatef(0, 1.0, 0.0, 0.0); // Rotação no eixo x
		glRotatef(angle, 0.0, 1.0, 0.0); // Rotação no eixo y

		glTranslatef(pos[0], pos[1], pos[2]);
		solidSphereIntern(scale, 20, 20);
		for (int i = 0 ; i < numberSatellites ; i++) {
			glPushMatrix();
				glRotatef(0, 1, 0.0, 0.0); // Rotação no eixo x
				glRotatef(angleSatellitesfloat / (i + 1), 0, 1.0, 0.0); // Rotação no eixo y
				glTranslatef(1, 0, 0);
				solidSphereIntern(scale / 10.0 , 20, 20);

			glPopMatrix();
		}

		if (isEarth) {
			glPushMatrix();
				glRotatef(0, 1, 0.0, 0.0); // Rotação no eixo x
				glRotatef(angleSatellitesfloat / 2, 0, 1.0, 0.0); // Rotação no eixo y
				glTranslatef(0.5, 0, 0);
				glutWireSphere(scale / 2.0 , 2, 2);
			glPopMatrix();
		}


	glPopMatrix();
}

World::~World() {
	// TODO Auto-generated destructor stub
}

void solidSphereIntern(float radius, int stacks, int columns)
{
    GLUquadric* quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    gluQuadricTexture(quadObj, GL_TRUE);
    gluSphere(quadObj, radius, stacks, columns);
    gluDeleteQuadric(quadObj);
}

int numberRandon(int smaller, int bigger) {
	static int Init = 0;
	int rc;

	if (Init == 0) {
		srand(time(NULL));
		Init = 1;
	}
	rc = (rand() % (bigger - smaller + 1) + smaller);

	return (rc);
}
