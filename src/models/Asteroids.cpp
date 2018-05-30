/*
 * Asteroids.cpp
 *
 *  Created on: 30 de mai de 2018
 *      Author: J�lio Sena
 */

#include "Asteroids.h"
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <time.h>

int numberRandonAst(int smaller, int bigger);

Asteroids::Asteroids(int lenght, float sizeAsteroids[], float posXAsteroids[], float angles[], int posAsteroids[]) {
	// TODO Auto-generated constructor stub
	for (int i = 0 ; i < lenght ; i++) {
		glPushMatrix();
			glRotatef(0, 1.0, 0.0, 0.0); // Rotação no eixo x
			glRotatef(posAsteroids[i] + angles[1], 0.0, 1.0, 0.0); // Rotação no eixo y

			glTranslatef(posXAsteroids[i], 0, 0);
			glutWireSphere(sizeAsteroids[i], 20, 20);
		glPopMatrix();
	}
}

Asteroids::~Asteroids() {
	// TODO Auto-generated destructor stub
}

int numberRandonAst(int smaller, int bigger) {
	static int Init = 0;
	int rc;

	if (Init == 0) {
		srand(time(NULL));
		Init = 1;
	}
	rc = (rand() % (bigger - smaller + 1) + smaller);

	return (rc);
}

