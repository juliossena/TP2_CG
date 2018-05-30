/*
 * Asteroids.h
 *
 *  Created on: 30 de mai de 2018
 *      Author: Júlio Sena
 */

#ifndef SRC_MODELS_ASTEROIDS_H_
#define SRC_MODELS_ASTEROIDS_H_


class Asteroids {
public:
	Asteroids(int lenght, float sizeAsteroids[], float posXAsteroids[], float angles[], int posAsteroids[]);
	virtual ~Asteroids();
};

#endif /* SRC_MODELS_ASTEROIDS_H_ */
