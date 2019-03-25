//This is a template Program For All(most) CG Programs

#include "pch.h"//remove this
#include<GL/glut.h>
#include<iostream>
#include<sstream>
#include<vector>
#include<math.h>
using namespace std;

//global variables
int width = 800;
int height = 600;

void BresenhamCircle(double h, double k, double r);
void MidCircle(double h, double k, double r);
void DisplayText(string text, int x, int y, int font);
void Clear();

//essentials
struct Vector2
{
	double x, y;
	Vector2(double x = 0, double y = 0)
	{
		this->x = x;
		this->y = y;
	}

	double Distance(Vector2 b) {	return sqrt( (x-b.x)*(x - b.x) + (y-b.y)*(y - b.y) );}
	double Distance(Vector2 *b){	return sqrt( (x-b->x)*(x - b->x) + (y-b->y)*(y - b->y) );}
};

vector<Vector2*> point;


//CallBacks Functions
void Display() {}
void ReshapeFunc(int w, int h)
{
	if (width == w && height == h) return;
	glutReshapeWindow(width, height);
}
//keyboard
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
//mouse
void MouseFunc(int button, int state, int x, int y)
{
	if (state == GLUT_UP)  return;

	y = -y + height;

	if (point.size() % 2 == 0)
	{
		point.push_back(new Vector2(x,y));
	}
	else
	{
		point.push_back(new Vector2(x, y));
		double r = point[0]->Distance(point[1]);

		//display points
		stringstream ss;
		ss << "(" << point[0]->x << "," << point[0]->y << ")";
		string text = ss.str();
		DisplayText(text, point[0]->x - 15, point[0]->y - 10, 6);

		ss.str("");
		ss << "r = " << (int)r;
		text = ss.str();
		DisplayText(text, point[0]->x - r/1.5, point[0]->y + 10, 6);

		glBegin(GL_LINES);
		glVertex2d(point[0]->x, point[0]->y);
		glVertex2d(point[0]->x-r, point[0]->y);
		glEnd();


		if (button == GLUT_LEFT_BUTTON)
		{
			MidCircle(point[0]->x,point[0]->y,r);
			DisplayText("MID_CIRCLE", point[0]->x, point[0]->y-r-25 + 10, 6);

		}
		else if (button == GLUT_RIGHT_BUTTON)
		{
			BresenhamCircle(point[0]->x, point[0]->y, r);
			DisplayText("BRESENHAM_CIRCLE", point[0]->x, point[0]->y - r - 25 + 10, 6);
		}
		glFlush();
		point.clear();
	}
}

void MouseMotionFunc(int, int) {}

//clear the screen
void Clear()
{
	glClearColor(0.5, 0.5, 0.5, 1);
	glClear(GL_COLOR_BUFFER_BIT);
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


void MidCircle(double h, double k, double r)
{
	double P = 1 - r;
	int x = 0;
	int y = r;

	glBegin(GL_POINTS);
	glVertex2d(h,k);


	glVertex2d(x + h, y + k);
	glVertex2d(x + h, -y + k);
	glVertex2d(y + h, x + k);
	glVertex2d(-y + h, x + k);
	while (y > x)
	{
		x++;
		if (P <= 0)
		{
			P += 2 * x + 1;
		}
		else
		{
			y--;
			P += 2 * x - 2 * y + 1;
		}

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

//====================================================================//
//                              MAIN                                  //
//====================================================================//
void Help()
{
	cout << "****************[HELP]***************\n" << endl;
	
	cout << "Press 'Left  Mouse Button' For MidPointCircle" << endl;
	cout << "Press 'Right Mouse Button' For BresenhamCircle\n" << endl;
	
	cout << "Esc to Exit" << endl;
	cout << "'d' to Clear The Screen\n" << endl;
	
	cout << "First Click  = Centre of The Circle" << endl;
	cout << "Second Click = Point on The Circle" << endl;
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
