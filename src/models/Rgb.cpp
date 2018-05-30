/*
 * Rgb.cpp
 *
 *  Created on: 12 de abr de 2018
 *      Author: Júlio Sena
 */

#include "Rgb.h"

Rgb::Rgb(float r, float g, float b) {
	// TODO Auto-generated constructor stub
	R = r;
	G = g;
	B = b;
}

float Rgb::getR(){
	return R;
}

float Rgb::getG(){
	return G;
}

float Rgb::getB(){
	return B;
}

Rgb::~Rgb() {
	// TODO Auto-generated destructor stub
}

