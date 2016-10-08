#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

float a, b;

void inicio()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-20,20,-20,20);      //largo y ancho
    glClearColor(0.0,0.0,0.0,0.0);  //color
}

void MidpointElipse()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float x, y, p;
    float d1, d2;
    // Valores iniciales
    p = 0.2;
    a = a/p;
    b = b/p;
    x = 0.0;
    y = b;

    d1 = b*b - a*a*b + a*a / 4.0;

    glColor3f(0.18,0.67,0.65);  //color RGB = X/255
    glBegin(GL_POINTS); // Simetria de orden 4
    glVertex2f(x, y*p*p);   glVertex2f(x, -y*p*p);
    glVertex2f(-x, y*p*p);  glVertex2f(-x, -y*p*p);

    while((a*a*(y - 0.5)) > (b*b*(x + 1)))
    {// Region 1
        if (d1 < 0.0)
        {
            d1 = d1 + b*b*(2*x + 3);
            x += 1.0;
        }
        else
        {
            d1 = d1 + b*b*(2*x + 3) + a*a*(-2*y + 2);
            x += 1.0;
            y -= 1.0;
        }// end if
        glBegin(GL_POINTS); // Simetria de orden 4
        glVertex2f(x*p*p, y*p*p);   glVertex2f(x*p*p, -y*p*p);
        glVertex2f(-x*p*p, y*p*p);  glVertex2f(-x*p*p, -y*p*p);
    }// end while
    d2 = b*b*(x + 0.5)*(x + 0.5) + a*a*(y - 1)*(y - 1) - a*a*b*b;
    while(y > 0)
    {
        // Region 2
        if (d2 < 0)
        {
            d2 = d2 + b*b*(2*x + 2) + a*a*(-2*y + 3);
            x += 1.0;
            y -= 1.0;
        }
        else
        {
            d2 = d2 + a*a*(-2*y + 3);
            y -= 1.0;
        }// end if
        glBegin(GL_POINTS); // Simetria de orden 4
        glVertex2f(x*p*p, y*p*p);   glVertex2f(x*p*p, -y*p*p);
        glVertex2f(-x*p*p, y*p*p);  glVertex2f(-x*p*p, -y*p*p);
    }// end while
    glEnd();
    glFlush();
}// end MidpointElipse


int main(int argc, char *argv[])
{
    cout << "ELIPSE :: Ingrese el tamaño de  los radio a & b" <<endl;
    cin >> a >> b;

    glutInit(&argc, argv);
    glutInitWindowSize(500,500);    //ancho y largo de la pantalla
    glutInitWindowPosition(10,10);  //posicion de aparicion de la pantalla
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("PRIMER PROGRAMA");
    inicio(); //entorno de trabajo
    glutDisplayFunc(MidpointElipse);
    glutMainLoop();     //Llamar la funcon repetidamente
    return EXIT_SUCCESS;    //Finalizacion del programa
}
