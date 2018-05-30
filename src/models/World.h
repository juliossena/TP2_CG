/*
 * World.h
 *
 *  Created on: 29 de mai de 2018
 *      Author: Júlio Sena
 */

#ifndef SRC_MODELS_WORLD_H_
#define SRC_MODELS_WORLD_H_

class World {
public:
	World(float angle, float angleSatellites, float pos[], float scale, int numberSatellites);
	virtual ~World();
};


#endif /* SRC_MODELS_WORLD_H_ */
