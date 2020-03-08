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
void DrawPattern(double h, double k, double,double);
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
			DrawPattern(point[0].x, point[0].y, point[1].x,point[1].y);
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
		if (button == GLUT_LEFT_BUTTON)
		{
			DrawPattern(point[0].x, point[0].y, point[1].x, point[1].y);
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
			DrawPattern(point[0].x, point[0].y, point[1].x, point[1].y);
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
void DrawRectangle(double X_min, double Y_min, double X_max, double Y_max)
{
	DDALine(X_min, Y_min, X_min, Y_max);
	DDALine(X_min, Y_max, X_max, Y_max);
	DDALine(X_max, Y_max, X_max, Y_min);
	DDALine(X_max, Y_min, X_min, Y_min);
}
void DrawPattern(double X_min, double Y_min, double X_max,double Y_max)
{

	double centreX = (X_min + X_max) / 2.0;
	double centreY = (Y_min + Y_max) / 2.0;
	double length = abs(X_max - X_min);
	double width =  abs(Y_max - Y_min);

	
	//draw outer Rectangle
	DrawRectangle(X_min,Y_min,X_max,Y_max);
	//draw inner Rectangle
	DrawRectangle(centreX-length/4.0, centreY - width / 4.0, centreX + length / 4.0, centreY + width / 4.0);
	
	//inner rhombus
	DDALine(centreX+length/2.0,centreY,centreX,centreY+width/2.0);
	DDALine(centreX,centreY+width/2.0, centreX-length/2.0, centreY);
	DDALine(centreX-length/2.0, centreY, centreX, centreY-width/2.0);
	DDALine(centreX, centreY-width/2.0,centreX + length / 2.0, centreY);
	
	glFlush();

	if (kaleidoscope && (length>20 || width>20))
	{
		DrawPattern(centreX - length / 4.0, centreY - width / 4.0, centreX + length / 4.0, centreY + width / 4.0);
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

	DisplayText("Kaleidoscope: ", width - toolAreaLength + 18, height - toolAreaLength / 2, 2);
	if (kaleidoscope)
		DisplayText("TRUE ", width - toolAreaLength + 135, height - toolAreaLength / 2, 2, green);
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
		char color[3];
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

	cout << "First Click  = Corner Point of Outer Rectangle" << endl;
	cout << "Second Click  =  Opposite Corner Point of Outer Rectangle" << endl;
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
