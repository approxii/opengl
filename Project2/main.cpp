#define _USE_MATH_DEFINES
#include <cmath>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <windows.h>

float angle = 180.0;
float radius = 7.5;
float radius_move = 11;
float angleStep = -0.5;
int is_day = 1;
float sunX = -50.0;

void drawPolana() 
{
    float x = 0.0f;
    float y = -45.0f;

    if (is_day == 0)
    {
        glColor3f(0.15, 0.45, 0.35);
    }
    else
    {
        glColor3f(0.0, 1.0, 0.15);
    }

    glBegin(GL_POLYGON);
    for (size_t i = 0; i <= 360; i++)
    {
        float theta = i * M_PI / 180.0;
        float pol_x = x + 120 * cos(theta);
        float pol_y = y + 40 * sin(theta);
        glVertex2f(pol_x, pol_y);
    }
    glEnd();
}

void drawHouse()
{
    if (is_day == 1)
    {
        glColor3f(0.8, 0.6, 0.4); //дом днем
    }
    else
    {
        glColor3f(0.4, 0.3, 0.2); //дом ночью
    }

    glBegin(GL_POLYGON);
    glVertex2f(-10, -10);
    glVertex2f(10, -10);
    glVertex2f(10, 10);
    glVertex2f(-10, 10);
    glEnd();

    if (is_day == 1)
    {
        glColor3f(0.1, 0.5, 1.0); //окно днем
    }
    else
    {
        glColor3f(0.05, 0.25, 0.5); //окно ночью
    }
    glBegin(GL_POLYGON);
    glVertex2f(-5, -5);
    glVertex2f(5, -5);
    glVertex2f(5, 5);
    glVertex2f(-5, 5);
    glEnd();

    if (is_day == 1)
    {
        glColor3f(1.0, 1.0, 1.0);; //рамы днем
    }
    else
    {
        glColor3f(0.7, 0.7, 0.7); //рамы ночью
    }
    glBegin(GL_LINES);
    glVertex2f(0, -5);
    glVertex2f(0, 5);
    glEnd();

    glBegin(GL_LINES);
    glVertex2f(-5, 0);
    glVertex2f(5, 0);
    glEnd();

    if (is_day == 1)
    {
        glColor3f(0.5, 0.4, 0.3);  //крыша днем
    }
    else
    {
        glColor3f(0.25, 0.2, 0.15); //крыша ночью
    }

    glBegin(GL_TRIANGLES);
    glVertex2f(-12, 10);
    glVertex2f(0, 20);
    glVertex2f(12, 10);
    glEnd();
}

void drawSun()
{
    float x = radius_move * 5 * cos(angle * M_PI / 180);
    float y = radius_move * 5 * sin(angle * M_PI / 180);

    if (is_day == 1)
    {
        glClearColor(0.0, 120.0, 255.0, 0.0);
        glColor3f(1.0, 1.0, 0.0); // yellow
    }
    else
    {
        glClearColor(0.0, 0.0, 0.1, 1.0);
        glColor3f(0.5, 0.5, 0.5); // grey
    }

    glBegin(GL_POLYGON);
    for (size_t i = 0; i <= 360; i++)
    {
        float theta = i * M_PI / 180;
        float cx = x + radius * cos(theta);
        float cy = y + radius * sin(theta);
        glVertex2f(cx, cy);
    }

    glEnd();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    drawSun();
    drawPolana();
    drawHouse();
    glFlush();
}

void update(int value)
{
    angle += angleStep;
    if (angle < -25.0)
    {
        angle = 225.0;
        is_day += 1;
        is_day %= 2;
    }
    glutPostRedisplay();
    glutTimerFunc(4, update, 0);
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1280, 720);
    glutCreateWindow("House and Sun/Moon");

    glClearColor(0.0, 0.0, 0.0, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-55.0, 55.0, -55.0, 55.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);

    glutMainLoop();
    return 0;
}

