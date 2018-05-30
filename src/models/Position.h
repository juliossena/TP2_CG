/*
 * Position.h
 *
 *  Created on: 12 de abr de 2018
 *      Author: Júlio Sena
 */

#ifndef MODELS_POSITION_H_
#define MODELS_POSITION_H_

class Position {
	int x;
	int y;
	int z;
public:
	Position(int X, int Y, int Z);
	virtual ~Position();
	int getX();
	int getY();
	int getZ();
};

#endif /* MODELS_POSITION_H_ */
