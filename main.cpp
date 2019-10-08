

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <stdlib.h>
#include <math.h>
#include <unistd.h>

float angulo = 0, seno, coseno;

float px1 = 1.0;
float py1 = 1.0;
float pz1 = 1.0;

float px2 = 3.0;
float py2 = 3.0;
float pz2 = 3.0;


//Declaramoz la Matriz Piramide, que contiene los 5 vertices de la piramide.
float piramide[4][5] =
{
    //x1     x2      x3       x4       x5
    {-1,     1,      1,      -1,      0},
    //y1     y2      y3       y4       y5
    { 0,     0,      0,       0,      2},
    //z1     z2      z3       z4       z5
    {-1,    -1,      1,       1,      0},

    { 1,     1,      1,       1,      1}, //cumpla la condicion de Matriz Cuadrada.
};


float rotaX[4][4] =   //Matriz Identidad de Rotacion en X.
{
    {1, 0,  0,  0},
    {0, 1,  0,  0},
    {0, 0,  1,  0},
    {0, 0,  0,  1},
};

float rotaY[4][4] =   //Matriz Identidad de Rotacion en Y.
{
    {1, 0,  0,  0},
    {0, 1,  0,  0},
    {0, 0,  1,  0},
    {0, 0,  0,  1},
};
float rotaZ[4][4] =   //Matriz Identidad de Rotacion en Z.
{
    {1, 0,  0,  0},
    {0, 1,  0,  0},
    {0, 0,  1,  0},
    {0, 0,  0,  1},
};

float trasladaP[4][4] =   //Matriz Identidad de TRASLACION
{
    {1, 0,  0,  0},
    {0, 1,  0,  0},
    {0, 0,  1,  0},
    {0, 0,  0,  1},
};

float mA[4][5] =   //Matriz DONDE se almacenan los resultados de la multiplicacion de matrices.
{
    {0, 0,  0,  0,  0},
    {0, 0,  0,  0,  0},
    {0, 0,  0,  0,  0},
    {0, 0,  0,  0,  0},
};
float mB[4][5] =   //Matriz DONDE se almacenan los resultados de la multiplicacion de matrices.
{
    {0, 0,  0,  0,  0},
    {0, 0,  0,  0,  0},
    {0, 0,  0,  0,  0},
    {0, 0,  0,  0,  0},
};
float mC[4][5] =   //Matriz DONDE se almacenan los resultados de la multiplicacion de matrices.
{
    {0, 0,  0,  0,  0},
    {0, 0,  0,  0,  0},
    {0, 0,  0,  0,  0},
    {0, 0,  0,  0,  0},
};

void multiplicacion()
{
    for (int i = 0; i<4; i++) //Limpia la matriz en donde se guardan los resultadoss
    {
        for(int j = 0; j<5; j++)
        {
            mA[i][j]=0;
            mB[i][j]=0;
            mC[i][j]=0;
        }
    }
    //Recorre las columnas
    for(int x = 0; x < 4; x++){
        //Recorre las filas
        for(int y = 0; y<5; y++){
            //recorre las columnas de la matriz ROTACION para ir haciendo la sumatoria
            for(int z = 0; z<4; z++){
                mC[x][y] += rotaX[x][z] * piramide[z][y];
            }
        }
    }

    for(int x = 0; x < 4; x++){
        //Recorre las filas
        for(int y = 0; y<5; y++){

            //recorre las columnas de la matriz ROTACION para ir haciendo la sumatoria
            for(int z = 0; z<4; z++){
                mB[x][y] += rotaY[x][z] * mC[z][y];
            }
        }
    }

    for(int x = 0; x < 4; x++){
        //Recorre las filas
        for(int y = 0; y<5; y++){

            //recorre las columnas de la matriz ROTACION para ir haciendo la sumatoria
            for(int z = 0; z<4; z++){
                mA[x][y] += rotaZ[x][z] * mB[z][y];
            }
        }
    }
    //Guarda los resultados en piramide;
    for(int i = 0; i<4; i++)
    {
        for(int j = 0; j<5;j++)
        {
            piramide[i][j] = mA[i][j];
        }
    }
}


void drawAxis()
{
        glColor3f(1,1,1);
        glBegin(GL_LINES);
        glVertex3f(px1,py1,pz1);
        glVertex3f(px2,py2,pz2);
        glEnd();
     //glShadeModel(GL_SMOOTH);
     //X axis in red
     glColor3f(1.0f,0.0f,0.0f);
     glBegin(GL_LINES);
       glVertex3f(-3.0,0.0,0.0);
       glVertex3f(3.0,0.0,0.0);
     glEnd();
     //Y axis in green
     glColor3f(0.0f,1.0f,0.0f);
     glBegin(GL_LINES);
       glVertex3f(0.0,-3.0,0.0);
       glVertex3f(0.0,3.0,0.0);
     glEnd();
     //Z axis in blue
     glColor3f(0.0f,0.0f,1.0f);
     glBegin(GL_LINES);
       glVertex3f(0.0,0.0,-3.0);
       glVertex3f(0.0,0.0,3.0);
     glEnd();


        glBegin(GL_LINE_STRIP);
        glColor3f(1,1,1);//color del poligono
        glVertex3d(piramide[0][0],piramide[1][0],piramide[2][0]); //punto1.
        glVertex3d(piramide[0][1],piramide[1][1],piramide[2][1]); //punto2.
        glVertex3d(piramide[0][2],piramide[1][2],piramide[2][2]); //punto3
        glVertex3d(piramide[0][3],piramide[1][3],piramide[2][3]); //punto4
        glEnd();


        //Usamos GLTriangles y le damos los vertices a trazar (esta vez en 3 dimensiones)
        glBegin(GL_LINE_STRIP);
        //Parte Trasera
        glColor3f(0.2, 0.658, 0.101);
        glVertex3d(piramide[0][4],piramide[1][4],piramide[2][4]);
        glVertex3d(piramide[0][0],piramide[1][0],piramide[2][0]);
        glVertex3d(piramide[0][1],piramide[1][1],piramide[2][1]);
        glEnd();
//
        glBegin(GL_LINE_STRIP);
        //ParteIzquierda
        glColor3f(0.658, 0.101, 0.145);
        glVertex3d(piramide[0][4],piramide[1][4],piramide[2][4]);
        glVertex3d(piramide[0][1],piramide[1][1],piramide[2][1]);
        glVertex3d(piramide[0][2],piramide[1][2],piramide[2][2]);
        glEnd();
//
        glBegin(GL_LINE_STRIP);
        //Parte delantera.
        glColor3f(.682,.6,.141);
        glVertex3d(piramide[0][4],piramide[1][4],piramide[2][4]);
        glVertex3d(piramide[0][2],piramide[1][2],piramide[2][2]);
        glVertex3d(piramide[0][3],piramide[1][3],piramide[2][3]);
        glEnd();

        glBegin(GL_LINE_STRIP);
        //Parte Derecha
        glColor3f(0.101, 0.301, 0.658);
        glVertex3d(piramide[0][4],piramide[1][4],piramide[2][4]);
        glVertex3d(piramide[0][3],piramide[1][3],piramide[2][3]);
        glVertex3d(piramide[0][0],piramide[1][0],piramide[2][0]);
        glEnd();




 }

 void display()
{
    int p;
    glClear(GL_COLOR_BUFFER_BIT);
    drawAxis();


    glutSwapBuffers();

    seno = sin(angulo);
    coseno = cos(angulo);
    rotaX[1][1] = coseno;
    rotaX[1][2] = -1*seno;
    rotaX[2][1] = seno;
    rotaX[2][2] = coseno;

    rotaY[0][0] = coseno;
    rotaY[0][2] = seno;
    rotaY[2][0] = -1*seno;
    rotaY[2][2] = coseno;

    rotaZ[0][0] = coseno;
    rotaZ[0][1] = -1*seno;
    rotaZ[1][0] = seno;
    rotaZ[1][1] = coseno;

    //multiplicacion();
    usleep(5000);

    glFlush();
}

void init()
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-4, 4, -4, 4, -4, 4);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(1.5,0,0,0,0,0,0,1,0);
    glClearColor(0,0,0,0);
}
void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
    case GLUT_KEY_UP:
    case 'W':
    case 'w':
      angulo= 1;
      angulo = (angulo/180)*M_PI;
      multiplicacion();
      break;

    case GLUT_KEY_DOWN:
    case 'S':
    case 's':
      angulo=-1;
      angulo = (angulo/180)*M_PI;
      multiplicacion();
      break;

    case 27:   // escape
      exit(0);
      break;

  }
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 50);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Piramide en X, Y, Z.");
    init();
    glutDisplayFunc(display);
    glutIdleFunc(display);
    glutKeyboardFunc(keyboard);
    glutMainLoop();
    return 0;
}
