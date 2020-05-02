#pragma once
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <glut.h>
#include <time.h>

#include "AiShip.h"

struct Points
{

	float x, y;  // initializor
	Points() { x = 0.0; y = 0.0; } // constructor

	Points(float _x, float _y) : x(_x), y(_y) {}
};

class Square
{
public:
	Points pts[4]; // square structure
	bool flag_stay, flag_life;
	bool flag_danger;			//for Ai
	int life_square;
	int count_must_not;
	int link_AiShip;
	AiShip *sh;
	Square() // initialize constructor
	{
		pts[0] = Points(0, 0);
		pts[1] = Points(0, 0);
		pts[2] = Points(0, 0);
		pts[3] = Points(0, 0);
		flag_stay = false;
		flag_life = false;
		flag_danger = false;
		life_square = 0;
		count_must_not = 0;
		link_AiShip = -1;
		sh = nullptr;
	};
	void Draw_square()
	{
		if ((flag_stay) && (flag_life))
		{
			glColor3f(0.70, 0.00, 0.70);// поле
			glBegin(GL_QUADS);

			glVertex2d(pts[0].x, pts[0].y);
			glVertex2d(pts[1].x, pts[1].y);
			glVertex2d(pts[2].x, pts[2].y);
			glVertex2d(pts[3].x, pts[3].y);

			glEnd();
		}
		else
		{
			if ((!flag_life)& (flag_stay))
			{
				glColor3f(0.70, 0.70, 0.00);
				glBegin(GL_QUADS);

				glVertex2d(pts[0].x, pts[0].y);
				glVertex2d(pts[1].x, pts[1].y);
				glVertex2d(pts[2].x, pts[2].y);
				glVertex2d(pts[3].x, pts[3].y);

				glEnd();
			}
		}
	};


	//void draw(Square *sqr); // draw square
	Points mouse(int x, int y); // get mouse coordintaes
	//Square* drag(Square *sqr, Points *mouse); // change points of sqr
};
