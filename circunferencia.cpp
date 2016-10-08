#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

float xc, yc, r;

void inicio()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-20,20,-20,20);      //largo y ancho
    glClearColor(0.0,0.0,0.0,0.0);  //color
}

// Procedimento CirclePoints
void circleP()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.18,0.67,0.65);  //color RGB = X/255
    glBegin(GL_POINTS);

    glVertex2f(xc, yc);
    glVertex2f(xc, -yc);
    glVertex2f(-xc, yc);
    glVertex2f(-xc, -yc);
    glVertex2f(yc, xc);
    glVertex2f(yc, -xc);
    glVertex2f(-yc, xc);
    glVertex2f(-yc, -xc);

    glEnd();

    glFlush();
}

void MidPointCircle()
{
    glClear(GL_COLOR_BUFFER_BIT);

    float x, y, p;
    float d;
    p = 0.01;
    // Valores iniciales
    x = 0.0;
    y = r/p;
    //d = 5.0/4.0 - r;
    d = 1.0 - r;    //usando aritmetica entera

    glColor3f(0.18,0.67,0.65);  //color RGB = X/255
    glBegin(GL_POINTS);
    glVertex2f(x, y*p);   glVertex2f(x, -y*p);
    glVertex2f(-x, y*p);  glVertex2f(-x, -y*p);
    glVertex2f(y*p, x);   glVertex2f(y, -x*p);
    glVertex2f(-y*p, x);  glVertex2f(-y, -x*p);
    while (y > x)
    {
        if (d < 0.0)
        {// Selecione E
            d = d + 2 * x + 3;
        }
        else
        {// Selecione SE
            d = d + 2 * (x - y) + 5;
            y -= 1.0;
        }/*end if*/
        x += 1.0;

        glColor3f(0.18,0.67,0.65);  //color RGB = X/255
        glBegin(GL_POINTS);
        glVertex2f(x*p, y*p);   glVertex2f(x*p, -y*p);
        glVertex2f(-x*p, y*p);  glVertex2f(-x*p, -y*p);
        glVertex2f(y*p, x*p);   glVertex2f(y*p, -x*p);
        glVertex2f(-y*p, x*p);  glVertex2f(-y*p, -x*p);
    }/* end while */
    glEnd();
    glFlush();
}/* end MidpointCircle */

void MidPointCircleInt()
{
    // Funcion que utiliza diferencias de 2do orden para incrementar variable de
    // decision d. Circunferencia centrada en el origen
    glClear(GL_COLOR_BUFFER_BIT);

    float x, y, p;
    float d;
    p = 0.01;
    // Valores iniciales
    x = 0.0;
    y = r/p;
    //d = 5.0/4.0 - r;
    d = 1.0 - r;    //usando aritmetica entera
    float deltaE = 3;
    float deltaSE = -2 * r / p + 5;

    glColor3f(0.18,0.67,0.65);  //color RGB = X/255
    glBegin(GL_POINTS);
    glVertex2f(x, y*p);   glVertex2f(x, -y*p);
    glVertex2f(-x, y*p);  glVertex2f(-x, -y*p);
    glVertex2f(y*p, x);   glVertex2f(y, -x*p);
    glVertex2f(-y*p, x);  glVertex2f(-y, -x*p);
    while (y > x)
    {
        if (d < 0.0)
        {// Selecione E
            d += deltaE;
            deltaE += 2.0;
            deltaSE += 2.0;
        }
        else
        {// Selecione SE
            d += deltaSE;
            deltaE += 2.0;
            deltaSE += 4.0;
            y -= 1.0;
        }/*end if*/
        x += 1.0;

        glColor3f(0.18,0.67,0.65);  //color RGB = X/255
        glBegin(GL_POINTS);
        glVertex2f(x*p, y*p);   glVertex2f(x*p, -y*p);
        glVertex2f(-x*p, y*p);  glVertex2f(-x*p, -y*p);
        glVertex2f(y*p, x*p);   glVertex2f(y*p, -x*p);
        glVertex2f(-y*p, x*p);  glVertex2f(-y*p, -x*p);
    }/* end while */
    glEnd();
    glFlush();
}/* end MidpointCircle */

int main(int argc, char *argv[])
{
    cout << "CIrcunferencia :: \nIngrese el tamaño del radio : " <<endl;
    cin >> r;

    glutInit(&argc, argv);
    glutInitWindowSize(500,500);    //ancho y largo de la pantalla
    glutInitWindowPosition(10,10);  //posicion de aparicion de la pantalla
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("PRIMER PROGRAMA");
    inicio(); //entorno de trabajo
    glutDisplayFunc(MidPointCircleInt);
    glutMainLoop();     //Llamar la funcon repetidamente
    return EXIT_SUCCESS;    //Finalizacion del programa
}
