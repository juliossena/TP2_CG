#include <iostream>
#include <fstream>

#include <GL/glew.h>
#include <GL/freeglut.h>
#include <cmath>
#include "models/Rgb.h"

using namespace std;

static bool isLightingOn = true;
static float d = 1.0;           // Intensidade da cor difusa da luz branca
static float e = 1.0;           // Intensidade da cor especular da luz branca
static float m = 0.2;           // Intensidade da luz ambiente global
static float p = 1.0;           // A luz branca é posicional?
static float s = 50.0;          // Expoente especular do material (shininess)
float matShine[] = { s };                       // expoente especular (shininess)
static float xAngle = 0.0, yAngle = 0.0;        // Rotação da luz branca
static char theStringBuffer[10];                // String buffer
static float xMouse = 150, yMouse = 1050;        // (x,y) do ponteiro do mouse
static float larguraJanela, alturaJanela;       // (w,h) da janela
static float anguloEsferaY = 0;                 // Rotação da esfera em torno do eixo y
static int esferaLados = 20;                   // Quantas subdivisões latitudinais/longitudinais da esfera
static bool localViewer = false;

int posCam = 1;
float posX = 0;
float posY = 0;

static float angles[50];

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

// Escreve as informações variáveis na tela
void informacoesTela(void)
{
    glDisable(GL_LIGHTING); // Desabilita iluminação
    glColor3f(.85f, .85f, .85f);

    glRasterPos3f(-1.0, 1.10, -2.0);

    floatParaString(theStringBuffer, 4, m);
    glRasterPos3f(-1.0, 1.00, -2.0);
    glRasterPos3f(-1.0, 0.95, -2.0);

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
    float pos1[] = { 1.0, 0, 0, p };
    float pos2[] = { 2.0, 0, 0, p };

    float scaleSol = 0.5;
    float scale1 = 0.3;
    float scale2 = 0.1;

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

    informacoesTela();

    if (posCam == 1) {
    	gluLookAt(0, 10, 5,
				  0, 0, 0,
				  0, 1, 0);
    } else if (posCam == 2) {
    	gluLookAt(posX, posY, 5,
    			0, 0, 0,
				0, 1, 0);
    }

    glDisable(GL_LIGHTING);

    glPushMatrix();
		glRotatef(angles[0], 0, 1, 0);
		glRotatef(90, 1, 1, 0);
		glLightfv(GL_LIGHT0, GL_POSITION, posSol);
		solidSphere(scaleSol, esferaLados, esferaLados);

	glPopMatrix();


	if (isLightingOn) {
		glEnable(GL_LIGHTING);
	}

    // Define (atualiza) o valor do expoente de especularidade
    matShine[0] = s;
    glMaterialfv(GL_FRONT, GL_SHININESS, matShine);
    glColor3f(1, 1, 1);

    // Desenha a esfera grande e bem arredondada

    glPushMatrix();
            glRotatef(0, 1.0, 0.0, 0.0); // Rotação no eixo x
            glRotatef(angles[6], 0.0, 1.0, 0.0); // Rotação no eixo y

            glTranslatef(pos1[0], pos1[1], pos1[2]);
            solidSphere(scale1, esferaLados, esferaLados);

            glPushMatrix();
				glRotatef(0, 1.0, 0.0, 0.0); // Rotação no eixo x
				glRotatef(angles[7], 0.0, 1.0, 0.0); // Rotação no eixo y
				glTranslatef(pos1[0], pos1[1], pos1[2]);
				solidSphere(scale2, esferaLados, esferaLados);

			glPopMatrix();
			if (posCam == 3) {
						    											gluLookAt(0, 0, 7,
						    													  0, 0, 0,
						    													  0, 1, 0);
						    										}
	glPopMatrix();

	glPushMatrix();
			glRotatef(0, 1.0, 0.0, 0.0); // Rotação no eixo x
			glRotatef(angles[2], 0.0, 1.0, 0.0); // Rotação no eixo y
			glTranslatef(pos2[0], pos2[1], pos2[2]);
			solidSphere(scale2, esferaLados, esferaLados);


	glPopMatrix();
    glutSwapBuffers();
}

// Callback do evento de teclado
void keyInput(unsigned char key, int x, int y)
{
    switch (key)
    {
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
    case 'p':
    case 'P':
        if (p) p = 0.0;
        else p = 1.0;
        break;
    case 'd':
        if (d > 0.0) d -= 0.05;
        break;
    case 'D':
        if (d < 1.0) d += 0.05;
        break;
    case 'e':
        if (e > 0.0) e -= 0.05;
        break;
    case 'E':
        if (e < 1.0) e += 0.05;
        break;
    case 's':
        if (s > 5.0) s -= 2.00;
        break;
    case 'S':
        if (s < 100.0) s += 2.00;
        break;
    case 'm':
        if (m > 0.0) m -= 0.05;
        break;
    case 'M':
        if (m < 1.0) m += 0.05;
        break;
    case 'v':
    case 'V':
        localViewer = !localViewer;
        break;
    case '+':
        esferaLados += 5;
        esferaLados = min(200, esferaLados);
        break;
    case '-':
        esferaLados -= 5;
        esferaLados = max(20, esferaLados);
        break;
    default:
        break;
    }
    glutPostRedisplay();
}

// Callback para setas do teclado
void specialKeyInput(int key, int x, int y)
{
    if(key == GLUT_KEY_DOWN)
    {
        xAngle++;
        if (xAngle > 360.0) xAngle -= 360.0;
    }
    if(key == GLUT_KEY_UP)
    {
        xAngle--;
        if (xAngle < 0.0) xAngle += 360.0;
    }
    if(key == GLUT_KEY_RIGHT)
    {
        yAngle++;
        if (yAngle > 360.0) yAngle -= 360.0;
    }
    if(key == GLUT_KEY_LEFT)
    {
        yAngle--;
        if (yAngle < 0.0) yAngle += 360.0;
    }
	switch(key) {
		// Tecla para cima
		case 101:
			if (posY < 10) posY += 0.1;

			break;

		//Tecla para baixo
		case 103:
			if (posY > -10) posY -= 0.1;

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
    gluPerspective(50.0, 1, 1, 20.0);
    glMatrixMode(GL_MODELVIEW);
}

void rotacionaEsfera() {
	angles[0] += .002f;
	angles[1] += .005f;
	angles[2] += .01f;
	angles[3] += .02f;
	angles[4] += .03f;
	angles[5] += .05f;
	angles[6] += .1f;
	angles[7] += .2f;
	angles[8] += .4f;
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

int main(int argc, char *argv[])
{
    imprimirAjudaConsole();
    glutInit(&argc, argv);

    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);
    glutInitWindowSize(500, 500);
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
