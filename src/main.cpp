#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include "models/Rgb.h"
#include "models/World.h"
#include "models/Asteroids.h"
#include "functions/escreveTexto.h"
#include <time.h>

using namespace std;

int numberRan(int smaller, int bigger);
static bool isLightingOn = true;
static float d = 1.0;           // Intensidade da cor difusa da luz branca
static float e = 1.0;           // Intensidade da cor especular da luz branca
static float m = 0.2;           // Intensidade da luz ambiente global
static float p = 1.0;           // A luz branca é posicional?
static float s = 50.0;          // Expoente especular do material (shininess)
float matShine[] = { s };                       // expoente especular (shininess)
static long font = (long)GLUT_BITMAP_8_BY_13;
static float xAngle = 0.0, yAngle = 0.0;        // Rotação da luz branca
static char theStringBuffer[10];                // String buffer
static float xMouse = 150, yMouse = 1050;        // (x,y) do ponteiro do mouse
static float larguraJanela, alturaJanela;       // (w,h) da janela
static float anguloEsferaY = 0;                 // Rotação da esfera em torno do eixo y
static int esferaLados = 20;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static bool localViewer = false;

int posAsteroids[1000];
float sizeAsteroids[1000];
float posXAsteroids[1000];
bool isView = true;
float distancePlanet = 2;
int posCam = 1;
int planetSelected = -1;
float posX = 0;
float posY = 0;
char namePlanet[100] = "";
char sizePlanet[100] = "";

static float angles[100];

Rgb *yellow = new Rgb(1.0, 1.0, 0);
Rgb *blue = new Rgb(0, 0, 1.0);
Rgb *white = new Rgb(1.0, 1.0, 1.0);
Rgb *red = new Rgb (0.6, 0, 0);
Rgb *grey = new Rgb (0.3, 0.3, 0.3);


// Converte um número decimal em string
void floatParaString(char * destStr, int precision, float val)
{
    sprintf(destStr,"%f",val);
    destStr[precision] = '\0';
}

void escreveTextoNaTela(void *font, char *string)
{
    char *c;
    for (c = string; *c != '\0'; c++) glutBitmapCharacter(font, *c);
}

// Escreve as informações variáveis na tela
void informacoesTela(void)
{
    glDisable(GL_LIGHTING); // Desabilita iluminação
    glColor3f(.85f, .85f, .85f);

    glRasterPos3f(-1.0, 1.10, -2.0);
    escreveTextoNaTela((void*)font, (char*)"Planeta: ");
    escreveTextoNaTela((void*)font, namePlanet);

    floatParaString(theStringBuffer, 4, m);
	glRasterPos3f(-1.0, 1.00, -2.0);
	escreveTextoNaTela((void*)font, (char*)"Raio do planeta: ");
	escreveTextoNaTela((void*)font, sizePlanet);

    glRasterPos3f(-1.0, 0.85, -2.0);
    glRasterPos3f(-1.0, 0.80, -2.0);
    floatParaString(theStringBuffer, 4, d);
    glRasterPos3f(-1.0, 0.75, -2.0);
    floatParaString(theStringBuffer, 4, e);


    glRasterPos3f(-1.0, 0.65, -2.0);
    glRasterPos3f(-1.0, 0.60, -2.0);
    floatParaString(theStringBuffer, 5, s);

}

// Configuração inicial do OpenGL e GLUT
void setup(void)
{
    //glClearColor(.4,.4,.4, 0.0);                    // fundo cinza
    glClearColor(0, 0, 0, 0.0);
    glEnable(GL_DEPTH_TEST);                        // Ativa teste Z

    // Propriedades do material da esfera
    float matAmbAndDif[] = {1.0, 1.0, 1.0, 1.0};    // cor ambiente e difusa: branca
    float matSpec[] = { 1.0, 1.0, 1,0, 1.0 };       // cor especular: branca

    // Definindo as propriedades do material
    glMaterialfv(GL_FRONT, GL_AMBIENT_AND_DIFFUSE, matAmbAndDif);
    glMaterialfv(GL_FRONT, GL_SPECULAR, matSpec);
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    // Não mostrar faces do lado de dentro
    glEnable(GL_CULL_FACE);
    glCullFace(GL_BACK);

}

void solidSphere(float radius, int stacks, int columns)
{
    GLUquadric* quadObj = gluNewQuadric();
    gluQuadricDrawStyle(quadObj, GLU_FILL);
    gluQuadricNormals(quadObj, GLU_SMOOTH);
    gluQuadricTexture(quadObj, GL_TRUE);
    gluSphere(quadObj, radius, stacks, columns);
    gluDeleteQuadric(quadObj);
}

// Callback de desenho
void desenhaCena()
{
    // Propriedades das fontes de luz
	float lightSol[] = { yellow->getR(), yellow->getG(), yellow->getB(), 1.0 };
    float lightAmb[] = { 0.0, 0.0, 0.0, 1.0 };
    float lightSpec0[] = { e, e, e, 1.0 };

    float posSol[] = { 0.0, 0.0, 0.0, p };

    float scaleSol = 1;
    float scale1 = 0.3;
    float scale2 = 0.1;

    float pos1[] = { 2.0, 0, 0, p };
	float pos2[] = { 4.0, 0, 0, p };
	float pos3[] = { 6.0, 0, 0, p };
	float pos4[] = { 8.0, 0, 0, p };
	float pos5[] = { 14.0, 0, 0, p };
	float pos6[] = { 16.0, 0, 0, p };
	float pos7[] = { 18.0, 0, 0, p };
	float pos8[] = { 20.0, 0, 0, p };

    // Propriedades da fonte de luz LIGHT0
    glLightfv(GL_LIGHT0, GL_AMBIENT, lightAmb);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightSol);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightSpec0);


    glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, localViewer);// Enable local viewpoint

    // Ativa as fontes de luz (branca e verde)
    glEnable(GL_LIGHT0);

    // Limpa a tela e o z-buffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glLoadIdentity();




    if (posCam == 1) {
    	gluLookAt(0, 30, 5,
				  0, 0, 0,
				  0, 1, 0);
    } else if (posCam == 2) {
    	gluLookAt(posX, posY, 5,
    			0, 0, 0,
				0, 1, 0);
    }
    if (posCam == 3) {
		gluLookAt(6.0, 0, distancePlanet,
				6.0, 0, 0,
				  0, 1, 0);

		glRotatef(0, 1.0, 0.0, 0.0); // Rotação no eixo x
		glRotatef(-angles[2], 0.0, 1.0, 0.0); // Rotação no eixo y
	}
    if (posCam == 4) {
    	informacoesTela();
    	switch(planetSelected) {
    	case 0:
    		strcpy (namePlanet, "Mercurio");
    		strcpy (sizePlanet, "2439 Km");
    		gluLookAt(pos1[0], 0, 2,
    				pos1[0], 0, 0,
					0, 1, 0);
    		break;
    	case 1:
    		strcpy (namePlanet, "Venus");
			strcpy (sizePlanet, "6051 Km");
			gluLookAt(pos2[0], 0, 2,
					pos2[0], 0, 0,
					0, 1, 0);
			break;
    	case 2:
    		strcpy (namePlanet, "Terra");
			strcpy (sizePlanet, "6378 Km");
			gluLookAt(pos3[0], 0, 2,
					pos3[0], 0, 0,
					0, 1, 0);
			break;
		case 3:
			strcpy (namePlanet, "Marte");
			strcpy (sizePlanet, "3397 Km");
			gluLookAt(pos4[0], 0, 2,
					pos4[0], 0, 0,
					0, 1, 0);
			break;
		case 4:
			strcpy (namePlanet, "Jupiter");
			strcpy (sizePlanet, "71492 Km");
			gluLookAt(pos5[0], 0, 2,
					pos5[0], 0, 0,
					0, 1, 0);
			break;
		case 5:
			strcpy (namePlanet, "Saturno");
			strcpy (sizePlanet, "60268 Km");
			gluLookAt(pos6[0], 0, 2,
					pos6[0], 0, 0,
					0, 1, 0);
			break;
		case 6:
			strcpy (namePlanet, "Urano");
			strcpy (sizePlanet, "51018 Km");
			gluLookAt(pos7[0], 0, 2,
					pos7[0], 0, 0,
					0, 1, 0);
			break;
		case 7:
			strcpy (namePlanet, "Netuno");
			strcpy (sizePlanet, "49538 Km");
			gluLookAt(pos8[0], 0, 2,
					pos8[0], 0, 0,
					0, 1, 0);
			break;
    	}

		glRotatef(0, 1.0, 0.0, 0.0); // Rotação no eixo x
		glRotatef(-angles[planetSelected], 0.0, 1.0, 0.0); // Rotação no eixo y
	}

    glDisable(GL_LIGHTING);

    glPushMatrix();
		glRotatef(angles[0], 0, 1, 0);
		glRotatef(90, 1, 1, 0);
		glLightfv(GL_LIGHT0, GL_POSITION, posSol);
		solidSphere(scaleSol, esferaLados, esferaLados);

	glPopMatrix();

	//Desenha asteroides
	new Asteroids(200, sizeAsteroids, posXAsteroids, angles, posAsteroids);

	if (isLightingOn) {
		glEnable(GL_LIGHTING);
	}

    // Define (atualiza) o valor do expoente de especularidade
    matShine[0] = s;
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glColor3f(1, 1, 1);

    // Desenha a esfera grande e bem arredondada



	//Mercurio
	new World(angles[0], angles[0], pos1, 0.1, isView ? 0 : 0, false);

	//Venus
	new World(angles[1], angles[0], pos2, 0.3, isView ? 0 : 0, false);

	//Terra
	new World(angles[2], angles[0], pos3, 0.2, isView ? 1 : 0, true);

	//Marte
	new World(angles[3], angles[1], pos4, 0.15, isView ? 2 : 0, false);

	//Jupiter
	new World(angles[4], angles[2], pos5, 0.7, isView ? 4 : 0, false);

	//Saturno
	new World(angles[5], angles[3], pos6, 0.6, isView ? 9 : 0, false);

	//Urano
	new World(angles[6], angles[4], pos7, 0.5, isView ? 5 : 0, false);

	//Netuno
	new World(angles[7], angles[5], pos8, 0.5, isView ? 3 : 0, false);

	//Plutao
	glPushMatrix();
		glRotatef(0, 1.0, 0.0, 0.0); // Rotação no eixo x
		glRotatef(angles[8], 1.0, 1.0, 0.0); // Rotação no eixo y

		glTranslatef(22.0, 0.0, 0.0);
		solidSphere(0.3, 20, 20);

	glPopMatrix();

    glutSwapBuffers();
}

// Callback do evento de teclado
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
    case 32:
    	posCam = 4;
    	planetSelected += 1;
    	if (planetSelected > 7) planetSelected = 0;
    	break;
    case 27:
        exit(0);
        break;
    case 'l':
        case 'L':
		isLightingOn = !isLightingOn;
		break;
	case '1':
		posCam = 1;
		break;
	case '2':
		posCam = 2;
		break;
	case '3':
		posCam = 3;
		break;
	case 'o':
	case 'O':
		isView ? isView = false : isView = true;
		break;
    default:
        break;
    }
    glutPostRedisplay();
}

// Callback para setas do teclado
void specialKeyInput(int key, int x, int y)
{
	switch(key) {
		// Tecla para cima
		case 101:
			if (posCam == 3) {
				if (distancePlanet > 1.5)	 distancePlanet -= 0.5;
			} else {
				if (posY < 30) posY += 0.1;
			}


			break;

		//Tecla para baixo
		case 103:
			if (posCam == 3) {
				if (distancePlanet < 5) distancePlanet += 0.5;
			} else {
				if (posY > -30) posY -= 0.1;
			}


			break;

		// Tecla para direita
		case 100:
			if (posX < 10) posX += 0.1;
			break;

		// Teclas para esquerda
		case 102:
			if (posX > -10) posX -= 0.1;
			break;
	}
    glutPostRedisplay();
}

// Callback de redimensionamento
void resize(int w, int h)
{
    larguraJanela = 1000;
    alturaJanela = 1000;

    glMatrixMode (GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(70.0, 1, 1, 70.0);
    glMatrixMode(GL_MODELVIEW);
}

void rotacionaEsfera() {
	angles[0] += .99f;
	angles[1] += .4f;
	angles[2] += .2f;
	angles[3] += .1f;
	angles[4] += .02f;
	angles[5] += .008f;
	angles[6] += .004f;
	angles[7] += .002f;
	angles[8] += .4f;
	angles[9] += .04f;
	angles[10] += .34f;
	angles[11] += .42f;
	angles[12] += .32f;
	angles[13] += .54f;
	angles[14] += .12f;
	angles[15] += .321f;
	angles[16] += .65f;
	angles[17] += .323f;
	angles[18] += .643f;
	angles[19] += .425f;
	angles[20] += .78f;
	angles[21] += .587f;
	angles[22] += .7089f;
	angles[23] += .435f;
	angles[24] += .875f;
	angles[25] += .43f;
	angles[26] += .76f;
	angles[27] += .754f;
	angles[28] += .45f;
	angles[29] += .7654f;
    anguloEsferaY += .1f;
    glutPostRedisplay();
}

// Imprime a ajuda no console
void imprimirAjudaConsole(void)
{
    cout << "Ajuda:" << endl;
    cout << "  Aperte 'l' para ligar/desligar a iluminacao do OpenGL." << endl
         << "  Aperte 'w' para ligar/desligar a fonte de luz branca." << endl
         << "  Aperte 'g' para ligar/desligar a fonte de luz verde." << endl
         << "  Aperte 'd/D' para aumentar/reduzir a intensidade difusa da luz branca." << endl
         << "  Aperte 'e/E' para aumentar/reduzir a intensidade especular da luz branca." << endl
         << "  Aperte 'm/M' para aumentar/reduzir a intensidade da luz ambiente global." << endl
         << "  Aperte 's/S' para aumentar/reduzir o expoente especular do material." << endl
         << "  Aperte 'p' para alternar entre fonte posicional ou direcional." << endl
         << "  Aperte 't' para alternar entre modo com/sem textura." << endl
         << "  Aperte '+/-' para aumentar/diminuir a redondeza da esfera." << endl
         << "  Aperte as setas para rotacionar a fonte de luz branca" << endl;
}

void posicionaCamera(int x, int y) {
    xMouse = 1000;
    yMouse = 0;
    glutPostRedisplay();
}

void initPosAsteroids() {
	for (int i = 0 ; i < 1000 ; i ++) {
		posAsteroids[i] = numberRan(0, 360);
		sizeAsteroids[i] = numberRan(1, 10) / 100.0;
		posXAsteroids[i] = numberRan(9.5 * 100, 12.5 * 100) / 100.0;
	}
}

int numberRan(int smaller, int bigger) {
	static int Init = 0;
	int rc;

	if (Init == 0) {
		srand(time(NULL));
		Init = 1;
	}
	rc = (rand() % (bigger - smaller + 1) + smaller);

	return (rc);
}

int main(int argc, char *argv[])
{
	initPosAsteroids();
    imprimirAjudaConsole();
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutInitWindowPosition (100, 100);
    glutCreateWindow("Universo");
    glutDisplayFunc(desenhaCena);
    glutReshapeFunc(resize);
    glutKeyboardFunc(keyInput);
    glutPassiveMotionFunc(posicionaCamera);
    glutSpecialFunc(specialKeyInput);
    glutIdleFunc(rotacionaEsfera);

    setup();

    glutMainLoop();
}
