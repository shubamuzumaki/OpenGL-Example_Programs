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
	Color(unsigned char R=0,unsigned char G=0,unsigned char B=0)
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
		glColor3ub(r,g,b);
	}
};


void Clear()
{
	//clears the window
	glClearColor(0.1,0.1,0.1,1);
	glClear(GL_COLOR_BUFFER_BIT);
	glFlush();

	//set pen color
	glColor3f(1,0,0);
}

//recursive Function, It takes Point inside Shape(x,y) FillColor,Background Color
void _sfill(int x,int y,Color fillColor,Color bgColor)
{
	Color currPixelColor;
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&currPixelColor);
	if (currPixelColor == bgColor && currPixelColor != fillColor)
	{
		glBegin(GL_POINTS);
		glVertex2i(x,y);
		glEnd();

		//4 Connected Approach
		_sfill(x+1,y  ,fillColor,bgColor);
		_sfill(x-1,y  ,fillColor,bgColor);
		_sfill(x  ,y+1,fillColor,bgColor);
		_sfill(x  ,y-1,fillColor,bgColor);
	}
}

//It takes Point Inside the Shape and The FillColor
void SeedFill(int x,int y,Color fillColor)
{
	//store backGround Color
	Color bgColor;
	glReadPixels(x,y,1,1,GL_RGB,GL_UNSIGNED_BYTE,&bgColor);
	
	//our function which is hidden from user(assume)
	fillColor.SetGlColor();
	_sfill(x,y,fillColor,bgColor);
}

//Draws a Rectangle with Centre(c_x,c_y),Height(h),Width(w)
void DrawRectangle(int c_x,int c_y,int h,int w)
{
	glBegin(GL_LINE_LOOP);
	glVertex2i(c_x+w/2,c_y+h/2);
	glVertex2i(c_x+w/2,c_y-h/2);
	glVertex2i(c_x-w/2,c_y-h/2);
	glVertex2i(c_x-w/2,c_y+h/2);
	glEnd();
}

void Init()
{
	//Initialize Window
	glutInitWindowPosition(0,0);
	glutInitWindowSize(width,height);
	glutCreateWindow("seedFill");

	//initialize viewPort
	glMatrixMode(GL_PROJECTION);
	gluOrtho2D(0,width,0,height);

	//clear the screen
	Clear();
}
int main(int argc,char**argv)
{
	glutInit(&argc,argv);
	Init();
	
	Color fillColor(0,255,0);
	DrawRectangle(width/2,height/2,80,100);
	SeedFill(width/2,height/2,fillColor);
	
	
	glFlush();

	glutMainLoop();
	return 0;
}