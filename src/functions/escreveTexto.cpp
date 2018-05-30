/*
 * escreveTexto.cpp
 *
 *  Created on: 12 de abr de 2018
 *      Author: Júlio Sena
 */
#include <GL/glew.h>
#include <GL/freeglut.h>
#include <string.h>
#include "../models/Rgb.h"
#include "../models/Position.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;


void escreverTexto(Rgb rgb, void * font, char *s, Position *position) {
	glColor3f(rgb.getR(), rgb.getG(), rgb.getB());
    glRasterPos3f(position->getX(), position->getY(), position->getZ());

    for (int i = 0; i < strlen(s); i++) {
        glutBitmapCharacter(font, s[i]);
    }
}

void escreveHUD(Rgb rgb, Rgb alternative, float velocidade, float orientacaoEmGraus, float y, int combustivel, float pontuacao, int vidas) {
	char velocidadeChar[16];
	sprintf(velocidadeChar, "%.2f", velocidade * 100);

	char str[80];
	strcpy (str, "Velocidade: ");
	strcat (str, velocidadeChar );

	char orientacao[16];
	sprintf(orientacao, "%.2f", orientacaoEmGraus - 90);

	char str2[80];
	strcpy (str2, "Orientacao: ");
	strcat (str2, orientacao );

	char altura[16];
	sprintf(altura, "%.0f", y + 84);

	char str3[80];
	strcpy (str3, "Altura: ");
	strcat (str3, altura );

	char com[16];
	sprintf(com, "%.2f", (float)combustivel);

	char str4[80];
	strcpy (str4, "Combustivel: ");
	strcat (str4, com );

	char pont[16];
	sprintf(pont, "%.2f", (float)pontuacao);

	char str5[80];
	strcpy (str5, "Pontuacao: ");
	strcat (str5, pont );

	char vid[16];
	sprintf(vid, "%.2f", (float)vidas);

	char str6[80];
	strcpy (str6, "Vidas: ");
	strcat (str6, vid );

	escreverTexto(rgb, GLUT_BITMAP_TIMES_ROMAN_10, str, new Position(-90, 90, 0));

	if (orientacaoEmGraus - 90 == 0) {
		escreverTexto(rgb, GLUT_BITMAP_TIMES_ROMAN_10, str2, new Position(-90, 85, 0));
	} else {
		escreverTexto(alternative, GLUT_BITMAP_TIMES_ROMAN_10, str2, new Position(-90, 85, 0));
	}

	escreverTexto(rgb, GLUT_BITMAP_TIMES_ROMAN_10, str3, new Position(-90, 80, 0));
	if (combustivel > 100) {
		escreverTexto(rgb, GLUT_BITMAP_TIMES_ROMAN_10, str4, new Position(-90, 75, 0));
	} else {
		escreverTexto(alternative, GLUT_BITMAP_TIMES_ROMAN_10, str4, new Position(-90, 75, 0));
	}

	escreverTexto(rgb, GLUT_BITMAP_TIMES_ROMAN_10, str5, new Position(-90, 70, 0));
	escreverTexto(rgb, GLUT_BITMAP_TIMES_ROMAN_10, str6, new Position(-90, 65, 0));


}


