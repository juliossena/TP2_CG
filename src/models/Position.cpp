/*
 * Position.cpp
 *
 *  Created on: 12 de abr de 2018
 *      Author: Júlio Sena
 */

#include "Position.h"

Position::Position(int X, int Y, int Z) {
	// TODO Auto-generated constructor stub
	x = X;
	y = Y;
	z = Z;
}

Position::~Position() {
	// TODO Auto-generated destructor stub
}

int Position::getX() {
	return x;
}

int Position::getY() {
	return y;
}


int Position::getZ() {
	return z;
}
