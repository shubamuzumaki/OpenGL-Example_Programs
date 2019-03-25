#ifndef __SHAPES__
#define	__SHAPES__
double Max(double a, double b)
{
	return a > b ? a : b;
}
void DrawLine(int x1, int y1, int x2, int y2);				//-----DDA-----

struct Vector2
{	
	int x;
	int y;
	Vector2(int x=0,int y=0)
	{
		this->x = x;
		this->y = y;
	}
};

class PolyGon
{
	int sides;
	Vector2 *point;
	int count;
public:
	PolyGon(int s)
	{
		if (s < 3)//defence
		{
			std::cout << "ERROR!!!(Sides of PolyGon less than 3)";
			throw 2;
		}
		count = 0;
		sides = s;
		point = new Vector2[sides];
	}
	PolyGon(Matrix temp):PolyGon(temp.GetRow())
	{
		if (temp.GetCol() != 3)//defence
		{
			std::cout << "Matrix Columns are not 3";
			throw 4;
		}

		for (int i = 0; i < sides; i++)
		{
			Pushback(temp.mat[i][0], temp.mat[i][1]);
		}
	}
	void Pushback(int,int);
	void Draw();
	Matrix GetMatrix();//returns sides X 3 matrix
};


//----------------------------------------------------
void PolyGon::Pushback(int x, int y)
{
	if (count >= sides) return;

	Vector2 tempPoint(x,y);
	point[count++] = tempPoint;
}

void PolyGon::Draw()
{
	if (count != sides) return;//defence

	for (int i = 0; i < sides; i++)
	{
		//draw line beetween two consecutive points
		DrawLine(point[i].x,point[i].y, point[(i+1)%sides].x, point[(i+1)%sides].y);
	}
}

Matrix PolyGon::GetMatrix()
{
	Matrix temp(sides,3);
	for (int i = 0; i < sides; i++)
	{
		for (int j = 0; j < 3; j++)
		{
			switch (j)
			{
			case 0:
				temp.mat[i][j] = point[i].x;
				break;
			case 1:
				temp.mat[i][j] = point[i].y;
				break;
			case 2:
				temp.mat[i][j] = 1;
				break;
			}
		}
	}
	return temp;
}

//--------------------------------------------------
//				CG_ALGORITHMS
//--------------------------------------------------

void DrawLine(int x1, int y1, int x2, int y2)				//-----DDA-----
{
	double dx = x2 - x1,
		dy = y2 - y1;
	int step = Max(abs(dx), abs(dy));
	double xinc = dx / step,
		yinc = dy / step;
	double x = x1,
		y = y1;

	while (step--)
	{
		x += xinc;
		y += yinc;
		glBegin(GL_POINTS);
		glVertex2d(x, y);
		glEnd();
	}
	glFlush();
}
#endif // !__SHAPES__

