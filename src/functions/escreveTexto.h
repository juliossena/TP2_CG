/*
 * escreveTexto.h
 *
 *  Created on: 12 de abr de 2018
 *      Author: Júlio Sena
 */

#ifndef FUNCTIONS_ESCREVETEXTO_H_
#define FUNCTIONS_ESCREVETEXTO_H_
#include "../models/Rgb.h"
#include "../models/Position.h"

void escreverTexto(Rgb, void *, char *, Position *);
void escreveHUD(Rgb, Rgb, float, float, float, int, float, int);
int numberRandon(int smaller, int bigger);
bool gerarPossuirBonus(float chance);



#endif /* FUNCTIONS_ESCREVETEXTO_H_ */
