//This is a template Program For All(most) CG Programs

#include "pch.h"
#include<GL/glut.h>
#include<iostream>
#include<sstream>
#include<vector>
#include<math.h>
using namespace std;

//global variables
int width = 800;
int height = 600;

void Clear();
//essentials
void MouseFunc(int button, int state, int x, int y);
void _khelper(double x1, double y1, double x2, double y2, int itr,int);
void KochCurve(double x1, double y1, double x2, double y2, int itr,int);

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
}
void ReshapeFunc(int w, int h)
{
	if (width == w && height == h) return;
	glutReshapeWindow(width, height);
}
//keyoard func
void Keyboard(unsigned char key, int, int)
{
	MouseFunc(0, 0, 0, 0);
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
	if (state == GLUT_UP)  return;

	y = -y + height;

	if (point.size()%2== 0)
	{
		point.push_back(tempPoint(x, y));
	}
	else
	{
		point.push_back(tempPoint(x, y));
		if (button == GLUT_LEFT_BUTTON)
		{
			int s = point.size();
			KochCurve(point[s-2].x,point[s-2].y,point[s-1].x,point[s-1].y,3,60);
			//KochCurve(point[s-2].x,point[s-2].y,point[s-1].x,point[s-1].y,10,-60);
			glFlush();
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{

		}
	}
}

void MouseMotionFunc(int x, int y)
{
}

//clear the screen
void Clear()
{
	glClearColor(0, 0, 0, 1);
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
void _khelper(double x1, double y1, double x2, double y2, int itr,int angle)
{

	//calculate point p1 2:1		;section formula
	float p1y = (2 * y1 + y2) / 3;
	float p1x = (2 * x1 + x2) / 3;

	//calculate point p2 1:2		;section formula
	float p2x = (x1 + 2 * x2) / 3;
	float p2y = (y1 + 2 * y2) / 3;

	//find the top point _/\_	//explanation is at the end for this equation
	double rad = (3.14 / (double)180) * -angle;
	double y = -p2x * sin(rad) + p2y * cos(rad) + p1x * sin(rad) - p1y * cos(rad) + p1y;
	double x = p2x * cos(rad) + p2y * sin(rad) - p1x * cos(rad) - p1y * sin(rad) + p1x;

	if (itr - 1 == 0)//draw pattern
	{
		glColor3f(1,0,0);
		glVertex2f(x1, y1);		 //  
		glColor3f(1, 1, 0);
		glVertex2f(p1x, p1y);	 //  _ 
		glColor3f(1, 0, 1);
		glVertex2f(x, y);        //  _/                                   ;
		glColor3f(0, 0, 1);
		glVertex2f(p2x, p2y);	 //  _/\ 
		glColor3f(0, 1, 1);
		glVertex2f(x2, y2);      // _/\_ 

		//for visual purposes
		//DDALine(x1, y1, p1x, p1y);	// _
		//DDALine(p1x, p1y, x, y);	//  /
		//DDALine(x, y, p2x, p2y);	//   \ 
		//DDALine(p2x, p2y, x2, y2);  //    _

	}
	else//go deeper
	{
		_khelper(x1, y1, p1x, p1y, itr - 1,angle);	// _
		_khelper(p1x, p1y, x, y, itr - 1,angle);	//  /
		_khelper(x, y, p2x, p2y, itr - 1,angle);	//   \ 
		_khelper(p2x, p2y, x2, y2, itr - 1,angle);  //    _

	}
}

void KochCurve(double x1, double y1, double x2, double y2, int itr,int angle)
{
	glBegin(GL_LINE_STRIP);
	_khelper(x1, y1, x2, y2, itr,angle);
	glEnd();
}


//====================================================================//
//                              MAIN                                  //
//====================================================================//
void Help()
{
	cout << "****************[HELP]***************\n" << endl;
/*
	cout << "Press 'Left  Mouse Button' For DDA_LINE" << endl;
	cout << "Press 'Right Mouse Button' For Bresenham_LINE\n" << endl;
*/
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




//EXPLANATION:
//we need to rotate p2 w.r.t p1 at an angle 60(counterclockwise)
//we first translate p1 to origin
//perform rotation
//perform inverse translation on point p1
//multiply matrices to get that equation