#include "pch.h"
#include<GL/glut.h>
#include<iostream>
#include<vector>

using namespace std;

//global variables
int width = 600;
int height = 600;

//tools
bool isLineToolActive = false;
bool isRectangleToolActive = true;
bool passive = false;

const int TOP = 8;
const int BOTTOM = 4;
const int LEFT = 1;
const int RIGHT = 2;

int xmax, xmin, ymax, ymin;

//glut
void Init2D();
void InitCallbacks();
void Clear();

//callbacks
void Display();
void Keyboard(unsigned char, int, int);
void MouseFunc(int, int, int, int);
void Passive(int, int);

//application
int GetCode(int, int);
void ClipLine(double, double, double, double);
void Driver(double, double);
void LinesClipper();
void ToolToggler(bool&);
//----------------------------------------------------
//					CLASSES
//----------------------------------------------------
class Shape
{
protected:
	float R, G, B;
public:
	virtual void Draw() = 0;
	void SetColor(GLubyte r, GLubyte g, GLubyte b)
	{
		R = r;
		G = g;
		B = b;
	}
};

class Line :public Shape
{
public:
	double x1, x2, y1, y2;
	Line(double x1, double y1, double x2, double y2)
	{
		this->x1 = x1;
		this->y1 = y1;
		this->x2 = x2;
		this->y2 = y2;
	}
	void Draw()
	{
		glColor3ub(R, G, B);
		glColor3ub(255,0,0);

		glBegin(GL_LINES);
		glVertex2d(x1, y1);
		glVertex2d(x2, y2);
		glEnd();
	}
};

class RectAngle :public Shape
{
public:
	double x_min, x_max, y_min, y_max;
	RectAngle(double x1, double y1, double x2, double y2)
	{
		x_min = x1 < x2 ? x1 : x2;
		y_min = y1 < y2 ? y1 : y2;
		x_max = x2 > x1 ? x2 : x1;
		y_max = y2 > y1 ? y2 : y1;
	}

	void Draw()
	{
		glColor3ub(R, G, B);
		glBegin(GL_LINE_LOOP);
		glVertex2d(x_min, y_min);
		glVertex2d(x_max, y_min);
		glVertex2d(x_max, y_max);
		glVertex2d(x_min, y_max);
		glEnd();
	}
};

RectAngle *clipWindow;
vector<Line*> lineBuffer;
vector<Line*> clippedLine;
//----------------------------------------------------
//									GLUT
//----------------------------------------------------
void Init2D()																					//-----:) Init2D (:-----
{
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, width, 0, height);

	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();
}

void InitCallbacks()																	//-----:) InitCallBacks (:-----
{
	glutDisplayFunc(Display);
	glutKeyboardFunc(Keyboard);
	glutMouseFunc(MouseFunc);
	glutPassiveMotionFunc(Passive);
}

void Clear()
{
	glClearColor(1, 1, 1, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	int cachedSize = clippedLine.size();
	for (int i = 0; i < cachedSize; i++)
		clippedLine[i]->Draw();
	
	glFlush();
}
//----------------------------------------------------
//					CALLBACKS
//----------------------------------------------------

void Display()																				//-----:) Display (:-----
{
	glFlush();
}

void Keyboard(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 'r':
		ToolToggler(isRectangleToolActive);
		break;
	case 'l':
		ToolToggler(isLineToolActive);
		break;
	case 'c':
		LinesClipper();
		break;
	case 'p':
		passive = !passive;
		break;
	}
}

void MouseFunc(int button, int state, int x, int y)
{
	if (state == GLUT_DOWN)
		Driver(x, height - y);
}

void Passive(int x, int y)
{
	if (passive)
	{
		//system("clear");
		system("CLS");
		cout << "(" << x << "," << -y + height << ")" << endl;
	}
}
//----------------------------------------------------
//									APPLICATION
//----------------------------------------------------
int GetCode(int x, int y)									//-----:) GETCODE (:-----
{
	int code = 0;//inside

	if (x < xmin)
		code |= LEFT;
	else if (x > xmax)
		code |= RIGHT;

	if (y < ymin)
		code |= BOTTOM;
	else if (y > ymax)
		code |= TOP;

	return code;
}

void ClipLine(double x1, double y1, double x2, double y2)		//-----:) CLIPLINE (:-----
{
	Clear();
	clipWindow->Draw();

	int codeP1 = GetCode(x1, y1);
	int codeP2 = GetCode(x2, y2);

	bool accepted = false;

	while (true)
	{
		if (codeP1 == 0 && codeP2 == 0)
		{
			accepted = true;
			break;
		}
		else if (codeP1 & codeP2)
			break;

		int code_out;
		double x, y;
		if (codeP1 != 0)
			code_out = codeP1;
		else if (codeP2 != 0)
			code_out = codeP2;

		if (code_out & TOP)//above
		{
			x = x1 + ((x2 - x1)*(ymax - y1)) / (y2 - y1);
			y = ymax;
		}
		else if (code_out & BOTTOM)//below
		{
			x = x1 + ((x2 - x1)*(ymin - y1)) / (y2 - y1);
			y = ymin;
		}
		else if (code_out & LEFT)//left
		{
			x = xmin;
			y = y1 + ((y2 - y1)*(xmin - x1)) / (x2 - x1);
		}
		else if (code_out & RIGHT)//right
		{
			x = xmax;
			y = y1 + (y2 - y1)*(xmax - x1) / (x2 - x1);
		}

		if (code_out == codeP1)
		{
			x1 = x;
			y1 = y;
			codeP1 = GetCode(x1, y1);
		}
		else if (code_out == codeP2)
		{
			x2 = x;
			y2 = y;
			codeP2 = GetCode(x2, y2);
		}
	}//while
	if (accepted)
	{
		Line *currClippedLine = new Line(x1, y1, x2, y2);
		currClippedLine->Draw();
		clippedLine.push_back(currClippedLine);
	}
	else
		cout << "REJECTED" << endl;
	glFlush();
}

void LinesClipper()
{
	int cachedSize = lineBuffer.size();
	for (int i = 0; i < cachedSize; i++)
	{
		ClipLine(lineBuffer[i]->x1, lineBuffer[i]->y1, lineBuffer[i]->x2, lineBuffer[i]->y2);
	}
	lineBuffer.clear();
	clippedLine.clear();
}

void Driver(double x, double y)								//=====:] DRIVER [:=====
{
	static int count = 0;
	static double x_old, y_old;

	if (count == 0)
	{
		x_old = x;
		y_old = y;
		count++;
		return;
	}
	//we have 2 points
	if (isRectangleToolActive)
	{
		clipWindow = new RectAngle(x_old, y_old, x, y);
		Clear();
		xmin = x_old < x ? x_old : x;
		xmax = x_old > x ? x_old : x;
		ymin = y_old < y ? y_old : y;
		ymax = y_old > y ? y_old : y;
		clipWindow->Draw();
	}
	else if (isLineToolActive)
	{
		Line *currLine = new Line(x_old, y_old, x, y);

		currLine->Draw();
		lineBuffer.push_back(currLine);
	}

	glFlush();
	count = 0;
}

void ToolToggler(bool &curr)						//=====:] TOGGLER [:=====
{
	bool temp = curr;
	isLineToolActive = isRectangleToolActive = false;
	curr = !temp;
	cout << "LINE TOOL      :" << (isLineToolActive ? "TRUE" : "FALSE") << endl;
	cout << "RECTANGLE TOOL :" << (isRectangleToolActive ? "TRUE" : "FALSE") << endl;
	cout << "==============================================" << endl;
}


void Help()
{
	cout << "****************[HELP]***************\n" << endl;


	cout << "Esc to Exit" << endl;
	cout << "'d' to Clear The Screen\n" << endl;
	cout << "'r' to Toggle ClippingWindowDraw" << endl;
	cout << "'l' to Toggle LineTool\n" << endl;
	cout << "'c' to Clip Lines\n" << endl;

	cout << "First Click  =   Corner Point/First point of Outer Rectangle/line" << endl;
	cout << "Second Click  =  Opposite Corner/Second point  of Outer Rectangle/line" << endl;
}
void MainMenu(int key)
{
	switch (key)
	{
	case 1:
		ToolToggler(isRectangleToolActive);
		break;
	case 2:
		ToolToggler(isLineToolActive);
		break;
	case 3:
		Clear();
		break;
	case 4:
		exit(0);
		break;
	case 5:
		LinesClipper();
		break;
	}
}
void Menu()
{
	glutCreateMenu(MainMenu);
	glutAddMenuEntry("CLIPPING WINDOW",1);
	glutAddMenuEntry("LINE TOOL",2);
	glutAddMenuEntry("CLIP",5);
	glutAddMenuEntry("CLEAR",3);
	glutAddMenuEntry("EXIT",4);
	glutAttachMenu(GLUT_RIGHT_BUTTON);
}

int main(int argc, char **argv)						//=====:] MAIN [:=====
{
	glutInit(&argc, argv);
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("CG_ASSIGNMENT 2");

	Init2D();
	Help();
	InitCallbacks();
	Menu();
	glutMainLoop();

	return 0;
}
