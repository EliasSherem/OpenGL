#include <gl/glut.h>
#include "girasol.h"
void ajusta(int ancho, int alto) {
	glClearColor(1.0,1.0,1.0,0.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
void dibuja(void){
	int i,j;
	int tam=20; // tamaño del punto
	glClear(GL_COLOR_BUFFER_BIT);
	glPointSize(tam);
	glBegin(GL_POINTS);
	for(i=0 ; i< ALTO; i++)
		for(j=0 ; j< ANCHO; j++){
			glColor3ubv(paleta[girasol[i][j]]);
			glVertex2i(190+j*tam,390-i*tam);
		}
	glEnd();
	glFlush();
}
int main(int argc, char** argv){
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
	glutInitWindowSize(640,480);
	glutInitWindowPosition(100, 150);
	glutCreateWindow("Girasol con puntos");
	glutDisplayFunc(dibuja);
	glutReshapeFunc(ajusta);
	glutMainLoop();
	return 0;
}
