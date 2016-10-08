#include <windows.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;
#define ABS(x)	(x < 0 ? -x : x)

float px=0.0, py=0.0, radio=10.0, calx, caly;
float PI = 3.1415926535897932;
float vertices;
vector< vector<float> > puntos;

void inicio()
{
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-20,20,-20,20);      //largo y ancho
    glClearColor(0.0,0.0,0.0,0.0);  //color
}

// Algoritmo simple para convers˜ion matricial de rectas.
void fline(float x1, float y1, float x2, float y2)
{
    puntos.clear();
    vector<float> p;
    vector<float> q;
    float x, y;
    float a;
    float valor;
    a = (y2-y1)/(x2-x1);
    for (x=x1; x<=x2; x+=0.01)
    {
        // alrededor de y
        y = (y1 + a * (x - x1));
        p.push_back(x);
        q.push_back(-y);
    }// end for
    puntos.push_back(p);
    puntos.push_back(q);
    p.clear();
    q.clear();
}//end line

// Algoritmo de Punto-Medio incremental.
void inc_line(float x1, float y1, float x2, float y2)
{
    puntos.clear();
    vector<float> p;
    vector<float> q;
    float dx, dy, incE, incNE, d, x, y;
    dx = ABS(x2 - x1);
    dy = ABS(y2 - y1);
    d = 2.0 * dy - dx; // Valor inicial de d
    cout<<dx<<"\t"<<dy<<"\t"<<d<<endl;
    incE = 2.0 * dy; // Incremento de E
    incNE = 2.0 * (dy - dx); // Incremento de NE
    x = x1;
    y = y1;
    p.push_back(x);
    q.push_back(y);
    float r = 0.01;
    while (x < x2)
    {
        if (d <= 0.0)
        {//  E
            d = d + incE;
        }
        else
        {//  NE
            d = d + incNE;
            y += r;
        }// end if
        x += r;
        p.push_back(x);
        q.push_back(y);
    }// end while
    puntos.push_back(p);
    puntos.push_back(q);
    p.clear();
    q.clear();
}// end inc_line

// Grafico de una linea
void linea()
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.18,0.67,0.65);  //color RGB = X/255
    glBegin(GL_POINTS);
    for (int i = 0; i < puntos[0].size(); i++)
    {
        glVertex2f(puntos[0][i],puntos[1][i]);
    }
    glEnd();

    glFlush();
}

// Grafico de un poligono
void poligono()
{
    glClear(GL_COLOR_BUFFER_BIT);

    vector<float> a;
    vector<float> b;
    for(float i = 0.0; i < vertices; i++)
    {
        calx = radio*cos(2.0*PI*i/vertices) + px;
        caly = radio*sin(2.0*PI*i/vertices) + py;
        a.push_back(calx);
        b.push_back(caly);
    }

    glColor3f(0.28,0.47,0.65);  //color RGB = X/255
    glBegin(GL_LINES);  //Trazado del perimetro
    float x1=a[vertices-1], y1=b[vertices-1];
    for(int j = 0; j < vertices; j++)
    {
        /*int k;    //usando la funcion fline
        fline(x1,y1,a[j],b[j]);
        for (k = 0; k < puntos[0].size(); k++)
            glVertex2f(puntos[0][k],puntos[1][k]);
        */
        glVertex2f(x1,y1);
        glVertex2f(a[j],b[j]);
        x1 = a[j];
        y1 = b[j];
    }
    glEnd();

    a.clear();
    b.clear();
    //puntos.clear();

    glBegin(GL_POLYGON);    //Relleno del polígono
    float c1, c2, c3;
    for(int i = 0; i < vertices; i++)
    {
        c1 = (rand() % 255) / 255.0;
        c2 = (rand() % 255) / 255.0;
        c3 = (rand() % 255) / 255.0;
        glColor3f(c1, c2, c3); //color aleatorio
        glVertex3f(a[i], b[i], 0.0);
    }
    glEnd();

    glFlush();
}


int main(int argc, char *argv[])
{
    //inc_line(-7.0,-3.0,8.0,5.0);

    cout << "POLIGONO :: Ingrese el Numero de Vertices" <<endl;
    cin >> vertices;

    glutInit(&argc, argv);
    glutInitWindowSize(500,500);    //ancho y largo de la pantalla
    glutInitWindowPosition(10,10);  //posicion de aparicion de la pantalla
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutCreateWindow("PRIMER PROGRAMA");
    inicio(); //entorno de trabajo
    //glutDisplayFunc(linea);
    glutDisplayFunc(poligono);
    glutMainLoop();     //Llamar la funcon repetidamente
    return EXIT_SUCCESS;    //Finalizacion del programa
}
