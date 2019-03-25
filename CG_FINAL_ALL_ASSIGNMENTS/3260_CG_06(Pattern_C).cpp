//This is a template Program For All(most) CG Programs

#include "pch.h"
#include<GL/glut.h>
#include<iostream>
#include<sstream>
#include<math.h>
#include<vector>
using namespace std;

//global variables
int width = 800;
int height = 600;
int toolAreaLength = width * 0.25;
bool shapeComplete = false;
bool kaleidoscope = true;

void Clear();
void DDALine(double x1, double y1, double x2, double y2);
void BresenhamCircle(double h, double k, double r);
void DrawPattern(double h, double k, double r);
void ColorPaneSelector(int x, int y);
void DrawColorPane();

//essentials

double TriangleArea(double x1, double y1, double  x2, double y2, double x3, double y3)//Shoelace formula
{
	return abs((x1*(y2 - y3) + x2 * (y3 - y1) + x3 * (y1 - y2)) / (double)2);
}
struct Vector2
{
	double x, y;
	Vector2(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
	}

	double Distance(Vector2 b) { return sqrt((x - b.x)*(x - b.x) + (y - b.y)*(y - b.y)); }
	
	Vector2 operator ()(double x = 0, double y = 0)
	{
		Vector2 temp(x, y);
		return temp;
	}
}tempPoint;//tempPoint for easily pushing back new points in point vector

vector<Vector2> point;
Vector2 top(width - toolAreaLength / 2 + 2, height / 2 + 70);
Vector2 bottomLeft(width - toolAreaLength + 10, height / 2 - 70);
Vector2 bottomRight(width - 10, height / 2 - 70);


//CallBacks Functions
void Display() {}
void ReshapeFunc(int w, int h)
{
	if (width == w && height == h) return;
	glutReshapeWindow(width, height);
}
//keyoard func
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
	case 'k':
		kaleidoscope = !kaleidoscope;
		Clear();
		break;
	}
}
//mouse func
void MouseFunc(int button, int state, int x, int y)
{
	if (state == GLUT_UP)  return;

	y = -y + height;

	if (x > width - toolAreaLength)//user clicked in tool Area
	{
		ColorPaneSelector(x, y);
		if (shapeComplete)
			DrawPattern(point[0].x, point[0].y, point[0].Distance(point[1]));
		glFlush();

		return;
	}

	if (shapeComplete)
		point.clear();
	
	if (point.size() % 2 == 0)
	{
		point.push_back(tempPoint(x, y));
		shapeComplete = false;
	}
	else
	{
		point.push_back(tempPoint(x, y));
		double r = point[0].Distance(point[1]);
		if (button == GLUT_LEFT_BUTTON)
		{
			DrawPattern(point[0].x,point[0].y,r);
			shapeComplete = true;
		}
		else if (button == GLUT_RIGHT_BUTTON)
		{

		}

	}
}

void MouseMotionFunc(int x, int y)
{
	y = -y + height;
	if (x > width - toolAreaLength)//user clicked in tool Area
	{
		ColorPaneSelector(x, y);
		if (shapeComplete)
			DrawPattern(point[0].x, point[0].y, point[0].Distance(point[1]));
		glFlush();

		return;
	}
}

//clear the screen
void Clear()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	
	DrawColorPane();
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
void DisplayText(string text, int x, int y, int font, unsigned char* color = NULL)
{
	void *p = NULL;
	if (font < 8 && font>1)	p = ((void *)font);
	else				    p = ((void *)5);

	if (color == NULL)
		glColor3f(1, 1, 0);
	else
		glColor3ub(color[0], color[1], color[2]);

	glRasterPos2f(x, y);
	size_t len = text.length();
	for (int i = 0; i < len; i++)
		glutBitmapCharacter(p, (int)text[i]);

	glColor3f(1, 0, 0);
}
//====================================================================//
//                              PROGRAM                               //
//====================================================================//

void DrawPattern(double h,double k,double R)
{
	//Draw Outer Circle
	BresenhamCircle(h,k,R);
	//Draw inner circle
	BresenhamCircle(h, k, R/2.0);
	
	//draw triangle
	double r = R / 2.0;
	DDALine(0 + h, R + k, -sqrt(3)*r + h, -r + k);
	DDALine(0 + h, R + k,  sqrt(3)*r + h, -r + k);
	DDALine(-sqrt(3)*r + h, -r + k, sqrt(3)*r + h, -r + k);

	glFlush();

	if (kaleidoscope && r>5)
	{
		DrawPattern(h,k,r);
	}
}

//DDA Line
void DDALine(double x1, double y1, double x2, double y2)
{
	double dx = x2 - x1;
	double dy = y2 - y1;

	int step = abs(dx) > abs(dy) ? abs(dx) : abs(dy);//max of abs(dx),abs(dy)
	double xinc = dx / step;
	double yinc = dy / step;

	double x = x1;
	double y = y1;

	glBegin(GL_POINTS);
	while (step--)
	{
		glVertex2d(x, y);
		x += xinc;
		y += yinc;
	}
	glEnd();
}
//BRESENHAM CIRCLE
void BresenhamCircle(double h, double k, double r)
{
	double P = 3 - 2 * r;
	double x = 0;
	double y = r;

	glBegin(GL_POINTS);
	glVertex2d(h, k);


	glVertex2d(x + h, y + k);
	glVertex2d(x + h, -y + k);
	glVertex2d(y + h, x + k);
	glVertex2d(-y + h, x + k);

	while (x < y)
	{
		if (P <= 0)
		{
			P += 4 * x + 6;
		}
		else if (P > 0)
		{
			P += 4 * (x - y) + 10;
			--y;
		}
		++x;

		{//octant symmetry
			glVertex2d(x + h, y + k);//1st point
			glVertex2d(x + h, -y + k);//2nd point
			glVertex2d(-x + h, y + k);//3rd point
			glVertex2d(-x + h, -y + k);//4th point

			glVertex2d(y + h, x + k);//5th point
			glVertex2d(y + h, -x + k);//6th point
			glVertex2d(-y + h, x + k);//7th point
			glVertex2d(-y + h, -x + k);//8th point
		}
	}
	glEnd();

}

void DrawColorPane()
{
	DisplayText("TOOL SELECTOR MENU", width - toolAreaLength + 10, height - 50, 2);


	//draw boundary
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex2d(width - toolAreaLength, 0);
	glVertex2d(width - toolAreaLength, height);

	glColor3f(0, 0, 1);
	glVertex2d(width - toolAreaLength + 1, 0);
	glVertex2d(width - toolAreaLength + 1, height);

	glColor3f(1, 0, 0);
	glVertex2d(width - toolAreaLength + 2, 0);
	glVertex2d(width - toolAreaLength + 2, height);
	glEnd();

	unsigned char red[] = { 255,0,0 };
	unsigned char green[] = { 0,255,0 };
	unsigned char blue[] = { 0,0,255 };
	//option for KaliedoScope
	
	DisplayText("Kaleidoscope: ",width-toolAreaLength+18,height-toolAreaLength/2,2);
	if(kaleidoscope)
		DisplayText("TRUE ", width - toolAreaLength + 135, height - toolAreaLength / 2, 2,green);
	else
		DisplayText("FALSE ", width - toolAreaLength + 135, height - toolAreaLength / 2, 2, red);


	//Displat 'R','G','B'
	DisplayText("R", top.x - 7, top.y + 7, 5, red);
	glColor3f(0, 0, 0);

	DisplayText("G", bottomLeft.x, bottomLeft.y - 20, 5, green);
	glColor3f(0, 0, 0);

	DisplayText("B", bottomRight.x - 17, bottomLeft.y - 20, 5, blue);
	glColor3f(0, 0, 0);


	glBegin(GL_TRIANGLES);

	//draw actual triangle
	glColor3f(1, 0, 0);
	glVertex2d(top.x, top.y);
	glColor3f(0, 1, 0);
	glVertex2d(bottomLeft.x, bottomLeft.y);
	glColor3f(0, 0, 1);
	glVertex2d(bottomRight.x, bottomRight.y);

	glEnd();

}

//selects 
void ColorPaneSelector(int x, int y)
{
	//code for triangle colliders
	double areaOfTriangle = TriangleArea(top.x, top.y, bottomLeft.x, bottomLeft.y, bottomRight.x, bottomRight.y);
	double A1 = TriangleArea(x, y, bottomLeft.x, bottomLeft.y, bottomRight.x, bottomRight.y);
	double A2 = TriangleArea(top.x, top.y, x, y, bottomRight.x, bottomRight.y);
	double A3 = TriangleArea(top.x, top.y, bottomLeft.x, bottomLeft.y, x, y);

	if (areaOfTriangle == (A1 + A2 + A3))//point is in triangle
	{
		//color selector logic here
		unsigned char color[3];
		glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &color);
		glColor3ub(color[0], color[1], color[2]);
	}

	//code for rectangle collider(Kaliedoscope)
	//if(y<height-toolAreaLength/2.0)
}


//====================================================================//
//                              MAIN                                  //
//====================================================================//
void Help()
{
	cout << "****************[HELP]***************\n" << endl;

	cout << "Press 'Left  Mouse Button' For Pattern" << endl;

	cout << "Esc to Exit" << endl;
	cout << "'d' to Clear The Screen\n" << endl;
	cout << "'k' to Toggle Kaleidoscope\n" << endl;

	cout << "First Click  = Centre Point of Outer Circle" << endl;
	cout << "Second Click  = Any Point of Outer Circle" << endl;
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
