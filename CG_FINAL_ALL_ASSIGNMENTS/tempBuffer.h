//this is just a temp file

#include "pch.h"
#include<GL/glut.h>
#include<iostream>

using namespace std;
int width = 500;
int height = 500;

//essentials
struct Color
{
	unsigned char r, g, b;
	Color(unsigned char R = 0, unsigned char G = 0, unsigned char B = 0)
	{
		r = R;
		g = G;
		b = B;
	}

	//to check wheteher two colors are equal
	bool operator==(Color &B)
	{
		if (r != B.r)  return false;
		if (g != B.g)  return false;
		if (b != B.b)  return false;
		return true;
	}

	//to check whether two colors are unequal
	bool operator!=(Color &B)
	{
		if (r != B.r)  return true;
		if (g != B.g)  return true;
		if (b != B.b)  return true;
		return false;
	}

	//set OpenGl Color
	void SetGlColor()
	{
		glColor3ub(r, g, b);
	}
};


void Clear()
{
	//clears the window
	glClearColor(0, 0, 0, 1);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	//set pen color
	glColor3f(1, 0, 0);
}

//8 Connected Approach
//              * * *
//              * P *
//              * * *
//recursive Function, It takes Point inside Shape(x,y) FillColor,Background Color
void _sfill_8C(double x, double y, Color fillColor, Color bgColor)
{
	Color currPixelColor;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &currPixelColor);
	if (currPixelColor == bgColor && currPixelColor != fillColor)
	{
		glBegin(GL_POINTS);
		glVertex2d(x, y);
		glEnd();
		//cout <<"::::"<< x << "," << y;
		glFlush();// this line is for visual purposes only 

		//8 Connected Approach
		_sfill_8C(x + 1, y, fillColor, bgColor);
		_sfill_8C(x, y + 1, fillColor, bgColor);
		_sfill_8C(x - 1, y, fillColor, bgColor);
		_sfill_8C(x, y - 1, fillColor, bgColor);

		//diagonal points
		Color leftPixelColor;
		Color rightPixelColor;
		Color topPixelColor;
		Color bottomPixelColor;
		glReadPixels(x - 1, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &leftPixelColor);
		glReadPixels(x + 1, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &rightPixelColor);
		glReadPixels(x, y + 1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &topPixelColor);
		glReadPixels(x, y - 1, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &bottomPixelColor);

		if (rightPixelColor == fillColor || topPixelColor == fillColor)
			_sfill_8C(x + 1, y + 1, fillColor, bgColor);

		if (topPixelColor == fillColor || leftPixelColor == fillColor)
			_sfill_8C(x - 1, y + 1, fillColor, bgColor);

		if (leftPixelColor == fillColor || bottomPixelColor == fillColor)
			_sfill_8C(x - 1, y - 1, fillColor, bgColor);

		if (bottomPixelColor == fillColor || rightPixelColor == fillColor)
			_sfill_8C(x + 1, y - 1, fillColor, bgColor);
	}
}



//4 Connected Approach
//                *
//              * P *
//                *
//recursive Function, It takes Point inside Shape(x,y) FillColor,Background Color
int s;
void _sfill_4C(double x, double y, Color fillColor, Color bgColor)
{
	//if (x<=5 || y<=5 || x>=width-5 || y>=height-5) return;
	Color currPixelColor;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &currPixelColor);
	if (currPixelColor != bgColor) return;

	{
		//draw pixel
		glBegin(GL_POINTS);
		glVertex2d(x, y);
		glEnd();
		cout << "::::" << x << "," << y;
		//if(x==)
		glFlush();// this line is for visual purposes only 

		//4 Connected Approach
		_sfill_4C(x - 1, y, fillColor, bgColor); 
		_sfill_4C(x + 1, y, fillColor, bgColor);
		_sfill_4C(x, y - 1, fillColor, bgColor);
		_sfill_4C(x, y + 1, fillColor, bgColor);
	}
}

//It takes Point Inside the Shape and The FillColor
void SeedFill(double x, double y, Color fillColor)
{
	//store backGround Color
	Color bgColor;
	glReadPixels(x, y, 1, 1, GL_RGB, GL_UNSIGNED_BYTE, &bgColor);

	//our function which is hidden from user(assume)
	fillColor.SetGlColor();
	_sfill_4C(x, y, fillColor, bgColor);
}

//Draws a Rectangle with Centre(c_x,c_y),Height(h),Width(w)
void DrawRectangle(double c_x, double c_y, double h, double w)
{
	glBegin(GL_LINE_LOOP);
	glVertex2d(c_x + w / 2.0, c_y + h / 2.0);
	glVertex2d(c_x + w / 2.0, c_y - h / 2.0);
	glVertex2d(c_x - w / 2.0, c_y - h / 2.0);
	glVertex2d(c_x - w / 2.0, c_y + h / 2.0);
	glEnd();
}

void Init()
{
	//Initialize Window
	glutInitWindowPosition(0, 0);
	glutInitWindowSize(width, height);
	glutCreateWindow("seedFill");

	//initialize viewPort
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0, width, 0, height);

	//clear the screen
	Clear();
}
void DisplayFunc(void) { }

int main(int argc, char**argv)
{
	glutInit(&argc, argv);
	Init();

	//register Display
	glutDisplayFunc(DisplayFunc);

	Color fillColor(0, 255, 0);
	DrawRectangle(103, 103, 90, 93);
	SeedFill(103, 103, fillColor);

	glFlush();
	glutMainLoop();
	return 0;
}
