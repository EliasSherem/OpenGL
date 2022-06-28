#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <math.h>

enum colores {negro=0,gris,azul,verde};
GLubyte paleta[5][3]={ {0,0,0},{150,150,150},{0,0,255},{0,255,0} };
enum colores col=azul;
typedef struct nodo{
	int xi;
	int yi;
    int xf;
    int yf;
    enum colores color;
	struct nodo* siguiente;

} nodo;
int xi, yi =0;
nodo* primero = NULL;
nodo* ultimo = NULL;
void insertarNodo();
void desplegarLista();
int puntos=0;
double area2=0;
int rad =0;
GLboolean fin=GL_FALSE;
GLboolean twopoints = GL_FALSE;
GLboolean conv = GL_FALSE;
int pos_x[60], pos_y[60];


void circulo(nodo *n){
        float det;
        int  rad=0,dx, dy, x=0,y;
        dx=abs(n->xf-n->xi);        dy=abs(n->yf-n->yi);
        rad=sqrt(pow(dx,2)+pow(dy,2));
        det=3-2*rad;
        y=rad;
        int yi=n->yi, xi=n->xi;

        while(x<=y){
            PintaPixel(x+xi,y+yi,n->color);
            PintaPixel(-x+xi,-y+yi,n->color);
            PintaPixel(-x+xi,y+yi,n->color);
            PintaPixel(x+xi,-y+yi,n->color);

            PintaPixel(y+xi,x+yi,n->color);
            PintaPixel(-y+xi,-x+yi,n->color);
            PintaPixel(-y+xi,x+yi,n->color);
            PintaPixel(y+xi,-x+yi,n->color);

            if(det<=0){
                det+= 4*x+6;
            }else{
                det+=4*(x-y)+10;
                y--;
            }
             x++;
        }
}
void PintaPixel(int x, int y , enum colores c){
    glBegin(GL_POINTS);
    glColor3ubv(paleta[c]);
    glVertex2d(x,y);
    glEnd();
}
 
void ajusta(int ancho, int alto){
    glClearColor(1.0,1.0,1.0,0.0);
    glColor3f(0.0f, 0.0f, 0.0f);   // color de dibujo negro
    glPointSize(4);             // tama?o del punto 4
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, 640.0, 0.0, 480.0);
}
void raton(int boton, int estado, int x, int y){
        int alto_ventana=480;

            if(boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN && twopoints==GL_FALSE)
            {
                insertarNodo(x,alto_ventana-y);
                twopoints=GL_TRUE;

            }else if(boton == GLUT_LEFT_BUTTON && estado == GLUT_UP  && twopoints==GL_TRUE ){


                ultimo->xf=x;
                ultimo->yf=alto_ventana-y;
                twopoints=GL_FALSE;
            }

            glutPostRedisplay();

}

void pageUp_Down(int tecla, int x, int y){
    switch(tecla) {
      case GLUT_KEY_END:
          if(conv)fin=GL_TRUE;
                         break;
      case GLUT_KEY_HOME: puntos=0;
                fin=GL_FALSE;
                glColor3f(0.0,0.0,0.0);
      default:break;
    }
    glutPostRedisplay();
}

void teclado(unsigned char tecla, int x, int y){
    switch(tecla) {
      case 27:	exit(0);	// Esc =>Salir del programa
      case 8:	borrar();  
			    break;
    }
    glutPostRedisplay();
}

void borrar(){
    nodo* actual = (nodo*) malloc(sizeof(nodo));
	actual = primero;
    do{
     actual = actual->siguiente;

    }while(actual->siguiente!=ultimo);
    actual->siguiente = primero;
    puntos--;
    ultimo = actual;
}
void pinta(unsigned char tecla, int x, int y) {
    switch(tecla) {
      case 'n':	col= negro; break;
      case 'g':	col = gris; break;
      case 'v':	col = verde; break;
      case 'a':	col= azul;
    }
    glutPostRedisplay();
}
void dibuja(void){

	glClear(GL_COLOR_BUFFER_BIT);
    nodo* actual = (nodo*) malloc(sizeof(nodo));
	actual = primero;
    glPointSize(2);
     

    actual = primero;

        if(primero!=NULL){

            actual = primero;
                    while(actual->siguiente != primero){
                        circulo(actual);
                        actual = actual->siguiente;
                    }

                printf("\n");
        }

    glFlush();
}

void insertarNodo(int x, int y){
	nodo* nuevo = (nodo*) malloc(sizeof(nodo));

	if(primero==NULL){
		primero = nuevo;
		primero->xi =x;
		primero->yi =y;
		primero->siguiente = primero;
		primero->color=col;
		ultimo = nuevo;
		puntos++;
	}else{
		ultimo->siguiente = nuevo;
		nuevo->siguiente = primero;
		nuevo->color=col;
		nuevo->xi =x;
		nuevo->yi =y;
		ultimo = nuevo;
		puntos++;
	}
}

int main(int argc, char** argv){
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_SINGLE | GLUT_RGBA);
   glutInitWindowSize(640,480);
   glutInitWindowPosition(100, 150);
   glutCreateWindow("Bresenham");
   // Registro de funciones
   glutDisplayFunc(dibuja);
   glutMouseFunc(raton);
   glutKeyboardFunc(pinta);
   glutSpecialFunc(pageUp_Down);
   glutReshapeFunc(ajusta);
   glutMainLoop();
   return 0;
}
