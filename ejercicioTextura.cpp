#include <GL/glut.h>
#include "girasol.h"      //archivo .h
#define anchoTextura 16    //ancho portencia de 2
#define altoTextura 16    //alto potencia de 2
#define R 0
#define G 1
#define B 2
GLubyte imagen[altoTextura][anchoTextura][3];
//Copiar paleta de color
GLubyte paleta[6][3] = {
	{0,255,255},{255,255,0},{255,128,0},
	{0,255,0},{0,128,64},{0,0,0}
 };

void creaTextura(void){
	for (int i=0; i<altoTextura; i++)
		for (int j=0; j<anchoTextura; j++){
			imagen[i][j][R]=(i<ALTO && j<ANCHO)?paleta[girasol[i][j]][R]:paleta[0][0];
			imagen[i][j][G]=paleta[(i<ALTO && j<ANCHO)?girasol[i][j]:0][G];
			imagen[i][j][B]=paleta[(i<ALTO && j<ANCHO)?girasol[i][j]:0][B];
		}
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER,GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER,GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, anchoTextura,altoTextura,
	0, GL_RGB, GL_UNSIGNED_BYTE, imagen);
}
void original(){
	glBegin(GL_POINTS);
		for(int i=0; i<ALTO; i++)
			for(int j=0; j<ANCHO;j++){
				glColor3ubv(paleta[girasol[i][j]]);
				glVertex2i(i*.05-2,j*.05-2);
			}
	glEnd();
}
void dibuja(void){
	glClear(GL_COLOR_BUFFER_BIT);
	glBegin(GL_QUADS);
		glTexCoord2f(0.0, 0.0); 
		glVertex2f(4.0, 4.0);
		glTexCoord2f(0.0, 1.0); 
		glVertex2f(4.0, 0.0);
		glTexCoord2f(1.0, 1.0); 
		glVertex2f(0.0, 0.0);
		glTexCoord2f(1.0, 0.0); 
		glVertex2f(0.0, 4.0);
	glEnd();
	original();
	glFlush();
}
void ajusta(int w, int h){
	glClearColor (1.0, 1.0, 1.0, 0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(-4.5,4.5,-4.5,4.5);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
	glutInitWindowSize(400, 400);
	glutCreateWindow("Ejemplo Textura Procedural");
	creaTextura();
	glutReshapeFunc(ajusta);
	glutDisplayFunc(dibuja);
	glutMainLoop();
	return 0;
}
