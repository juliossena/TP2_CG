/*
 * Rgb.h
 *
 *  Created on: 12 de abr de 2018
 *      Author: Júlio Sena
 */

#ifndef MODELS_RGB_H_
#define MODELS_RGB_H_

class Rgb {

private:
	float R;
	float G;
	float B;

public:
	Rgb(float r, float g, float b);
	float getR();
	float getG();
	float getB();
	virtual ~Rgb();
};

#endif /* MODELS_RGB_H_ */
