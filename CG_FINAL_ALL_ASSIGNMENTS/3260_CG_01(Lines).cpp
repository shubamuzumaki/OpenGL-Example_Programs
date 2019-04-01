
#include "pch.h"
#include<GL/glut.h>
#include<iostream>
#include<sstream>
#include<vector>
using namespace std;

//global variables
int width = 800;
int height = 600;
void DDALine(double x1, double y1, double x2, double y2);
void BLine(double x1, double y1, double x2, double y2);
void Clear();
void DisplayText(string text, int x, int y, int font);

//essentials
struct Vector2
{
	double x, y;
	Vector2(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
	}
};

vector<Vector2*> linePoint;


//CallBacks Functions
void Display()
{
	//DDALine(0, 0, 50, 50);
	//glFlush();
}
void ReshapeFunc(int w, int h)
{
	if (width == w && height == h) return;
	glutReshapeWindow(width, height);
}
void Keyboard(unsigned char key, int, int) 
{
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
void MouseFunc(int button, int state, int x, int y) 
{
	y = -y + height;

	if (state == GLUT_UP) return;

	if (linePoint.size()%2==0)
		linePoint.push_back(new Vector2(x,y));
	else
	{

		linePoint.push_back(new Vector2(x, y));

		//display 1st point
		stringstream ss;
		ss << "(" << linePoint[0]->x << "," << linePoint[0]->y << ")";
		string text = ss.str();
		DisplayText(text, linePoint[0]->x - 10, linePoint[0]->y - 10, 2);
		//display 2nd point 
		ss.str("");
		ss << "(" << linePoint[1]->x << "," << linePoint[1]->y << ")";
		text = ss.str();
		DisplayText(text, linePoint[1]->x + 10, linePoint[1]->y + 10, 2);

		if (button == GLUT_LEFT_BUTTON)
		{
			DDALine(linePoint[0]->x, linePoint[0]->y, linePoint[1]->x, linePoint[1]->y);
			DisplayText("DDA_LINE", 50, height - 50, 3);

		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			BLine(linePoint[0]->x, linePoint[0]->y, linePoint[1]->x, linePoint[1]->y);
			DisplayText("BRESENHAM_LINE", width-width*0.2, height - 50, 3);
		}
		glFlush();
		linePoint.clear();
	}
}
void MouseMotionFunc(int, int) {}

//clear the screen
void Clear()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1,0,0);
	linePoint.clear();
	glFlush();
}

//This Function Initialize the Window and viewport
void Initialize()
{
	//This will Create Window
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("LINE DRAWING ALGOS");

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
	//glutReshape(ReshapeFunc);
}

//this Function is used to DiaplatText
void DisplayText(string text,int x,int y,int font)
{
	glColor3f(1,1,0);
	glRasterPos2f(x, y);
	size_t len = text.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_10, (int)text[i]);

	glColor3f(1, 0, 0);
}
  //====================================================================//
 //                       LINE_DRAWING ALGOS                           //
//====================================================================//

//------------------------------DDALINE------------------------------
void DDALine(double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;

	int step = abs(dx)>abs(dy)?abs(dx): abs(dy);//max of abs(dx),abs(dy)
	double xinc = dx / step;
    double yinc = dy / step;
	
	double x = x1;
	double y = y1;

	glBegin(GL_POINTS);
	while (step--)
	{
		glVertex2d(x,y);
		x += xinc;
		y += yinc;
	}
	glEnd();
}


//------------------------------BRESENHAM_LINE------------------------------
void BLine(double x1, double y1, double x2, double y2)
{
	double dy = abs(y2 - y1);
	double	dx = abs(x2 - x1);
	int xinc = 1,
		yinc = 1;
	int G;

	if (x1 > x2)
		xinc = -1;
	if (y1 > y2)
		yinc = -1;

	if (dy < dx)//gentle slope
	{
		G = 2 * dy - dx;

		glBegin(GL_POINTS);
		while (x1 != (x2 + xinc))
		{
			glVertex2d(x1,y1);
			//cerr << "(" << x1 << "," << y1 << ")" << endl;
			x1 += xinc;
			if (G >= 0)
			{
				G -= 2 * dx;
				y1 += yinc;
			}
			G += 2 * dy;
		}
		glEnd();
	}
	//steep slope
	else
	{
		G = 2 * dx - dy;

		glBegin(GL_POINTS);
		while (y1 != (y2 + yinc))
		{
			glVertex2d(x1,y1);
			//cerr << "(" << x1 << "," << y1 << ")" << endl;
			y1 += yinc;
			if (G >= 0)
			{
				G -= 2 * dy;
				x1 += xinc;
			}
			G += 2 * dx;
		}
		glEnd();
	}
}

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