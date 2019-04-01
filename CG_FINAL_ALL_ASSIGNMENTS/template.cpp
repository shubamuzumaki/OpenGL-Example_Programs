//This is a template Program For All(most) CG Programs

#include "pch.h"
#include<GL/glut.h>
#include<iostream>
#include<sstream>
#include<vector>
using namespace std;

//global variables
int width = 800;
int height = 600;

void Clear();
//essentials
void MouseFunc(int button, int state, int x, int y);

//essentials
struct Vector2
{
	double x, y;
	Vector2(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
	}

	Vector2 operator ()(double x = 0, double y = 0)
	{
		Vector2 temp(x, y);
		return temp;
	}
}tempPoint;//tempPoint for easily pushing back new points in point vector

vector<Vector2> point;


//CallBacks Functions
void Display()
{
	cout << "lol";
}
void ReshapeFunc(int w, int h)
{
	if (width == w && height == h) return;
	glutReshapeWindow(width, height);
}
//keyoard func
void Keyboard(unsigned char key, int, int)
{
	MouseFunc(0,0,0,0);
	switch (key)
	{
	case 27:
		exit(0);
		break;
	case 'd':
		Clear();
		break;
	}

}
//mouse func
void MouseFunc(int button, int state, int x, int y)
{
	cout << "hello";
	if (state == GLUT_UP)  return;

	y = -y + height;

	if (point.size()  == 0)
	{
		point.push_back(tempPoint(x, y));
	}
	else
	{
		point.push_back(tempPoint(x, y));
		if (button == GLUT_LEFT_BUTTON)
		{
			
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{

		}
	}
}

void MouseMotionFunc(int x, int y)
{
	cout << x << "," << y<<endl;
}

//clear the screen
void Clear()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	point.clear();
	glFlush();
}

//This Function Initialize the Window and viewport
void Initialize()
{
	//This will Create Window
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("Circle");

	//this will initialize the ViewPort
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, width, 0, height);

	Clear();
	glFlush();
}

//Register All Callback Function here
void InitCallBacks()
{
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseFunc);
	glutMotionFunc(MouseMotionFunc);
	glutReshapeFunc(ReshapeFunc);
}
//this Function is used to DiaplatText
void DisplayText(string text, int x, int y, int font)
{
	void *p = NULL;
	if (font < 8 && font>1)	p = ((void *)font);
	else				    p = ((void *)5);

	glColor3f(1, 1, 0);
	glRasterPos2f(x, y);
	size_t len = text.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(p, (int)text[i]);

	glColor3f(1, 0, 0);
}
//====================================================================//
//                              PROGRAM                               //
//====================================================================//


//====================================================================//
//                              MAIN                                  //
//====================================================================//
void Help()
{
	cout << "****************[HELP]***************\n" << endl;

	cout << "Press 'Left  Mouse Button' For DDA_LINE" << endl;
	cout << "Press 'Right Mouse Button' For Bresenham_LINE\n" << endl;

	cout << "Esc to Exit" << endl;
	cout << "'d' to Clear The Screen\n" << endl;

	cout << "First Click  = FIRST POINT OF THE LINE" << endl;
	cout << "Second Click = SECOND POINT OF THE LINE" << endl;
}
int main(int argc, char **argv)
{
	glutInit(&argc, argv);

	Initialize();
	InitCallBacks();
	Help();
	glutMainLoop();
	return 0;
}
