// openGl.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <iostream>
#include <vector>
#include <glut.h>
#include <time.h>

#include "Ship.h"
#include "Square.h"
#include "AiFleet.h"

using namespace std;

const short int size_field = 8;
const short int Size_ship = 4;
const unsigned short int Count_Ship = 7;




Points mouse(int x, int y)
{
	int windowWidth = 600, windowHeight = 600;
	return Points(float(x) / (windowWidth/2)-1,(-1)* float(y) / (windowHeight/2)+1);
}

vector <vector <Square>> my_field;
vector <Square> Ships_versions;
vector <vector<Square>> enemy_field;
/*
class Ship
{
public:
	int gun;
	bool existence;
	vector<short int> x;
	vector<short int> y;
	short int unsigned size_ship;
	Ship()
	{
		gun = 0;
		existence = true;
		x.resize(1, -1);
		y.resize(1, -1);
		size_ship = 1;
	};
	void check_ship()
	{
		int f = 0;
		unsigned int n = size_ship;
		for (int i = 0; i<n; i++)
		{
			if (!(!my_field[x[i]][y[i]].flag_life))
			{
				f++;
			}
		}
		if (n == f){ existence = false; }
	}
	void initVecVec(vector<short int> &_vec, unsigned int _nSize, short int _value = -1)
	{
		_vec.resize(_nSize, _value);
	}
};
*/

vector <Ship> my_ship;
vector <Ship> enemy_ship;
short int number_ship=-1;
short int size_ship=-1;

bool line_hitting(Points mouse_coord, int line_number,bool fl)
{
	unsigned int number_delete=0;
	if (((size_ship > 0) && (fl)) || (!fl))
	{
		if ((!(fl)) && (number_ship<0))
		{
			return false;
		}
		if ((number_ship < Count_Ship - 1) && (fl))
		{
			number_ship++;
		}
		else
		{
			if ((!(number_ship < Count_Ship - 1)) && (fl))
			{
				cout << "No more! "<<endl;
				return false;
			}
		}
		for (int i = 0; i < size_field; i++)
		{
			if ((my_field[line_number][i].pts[0].x < mouse_coord.x) && (mouse_coord.x < my_field[line_number][i].pts[3].x))
			{
				if (fl)
				{
					my_ship.resize(number_ship + 1);
					my_ship[number_ship].initVecVec(my_ship[number_ship].x, size_ship);
					my_ship[number_ship].initVecVec(my_ship[number_ship].y, size_ship);
					my_ship[number_ship].size_ship = size_ship-1;
					for (int sh7 = 0; sh7 < size_ship; sh7++)
					{
						if (i + size_ship <= size_field)
						{
							my_ship[number_ship].x[sh7] = line_number;
							my_ship[number_ship].y[sh7] = i + sh7;
							if ((my_field[line_number][i + sh7].flag_stay != true) && (my_field[line_number][i + sh7].count_must_not == 0))
							{
								my_field[line_number][i + sh7].life_square = 1;
								my_field[line_number][i + sh7].flag_stay = true;
								my_field[line_number][i + sh7].flag_life = true;
								/*if (line_number + 1 < size_field)
								{
									my_field[line_number+1][i + sh7].count_must_not++;
								}
								if (line_number -1 > -1)
								{
									my_field[line_number - 1][i + sh7].count_must_not++;
								}
								if ((i +sh7+ 1 < size_field) && (sh7==size_ship-1))
								{
									my_field[line_number][i + sh7+1].count_must_not++;
								}
								if ((i + sh7 - 1 > -1) && (sh7 == 0))
								{
									my_field[line_number][i + sh7-1].count_must_not++;
								}
								if ((i + sh7 + 1 < size_field) && (sh7 == size_ship - 1) && (line_number + 1 < size_field))
								{
									my_field[line_number + 1][i + sh7 + 1].count_must_not++;
								}
								if ((i + sh7 - 1 > -1) && (sh7 == 0) && (line_number + 1 < size_field))
								{
									my_field[line_number + 1][i + sh7 - 1].count_must_not++;
								}
								if ((i + sh7 + 1 < size_field) && (sh7 == size_ship - 1) && (line_number - 1 > -1))
								{
									my_field[line_number - 1][i + sh7 + 1].count_must_not++;
								}
								if ((i + sh7 - 1 > -1) && (sh7 == 0) && (line_number - 1 > -1))
								{
									my_field[line_number - 1][i + sh7 - 1].count_must_not++;
								}*/


								if (my_field[line_number][i + sh7].link_ship == -1)
								{
									my_field[line_number][i + sh7].link_ship = number_ship;
									//cout << number_ship;
								}
							}
						}
						else
						{
							if (line_number + size_ship <= size_field)
							{
								my_ship[number_ship].x[sh7] = line_number + sh7;
								my_ship[number_ship].y[sh7] = i;
								if ((my_field[line_number + sh7][i].flag_stay != true) && (my_field[line_number + sh7][i].count_must_not == 0))
								{
									my_field[line_number + sh7][i].life_square = 1;
									my_field[line_number + sh7][i].flag_stay = true;
									my_field[line_number + sh7][i].flag_life = true;
									if (my_field[line_number + sh7][i].link_ship == -1)
									{
										my_field[line_number + sh7][i].link_ship = number_ship;
									}

									/*if (line_number + 1 < size_field)
									{
										my_field[line_number + 1][i + sh7].count_must_not++;
									}
									if (line_number - 1 > -1)
									{
										my_field[line_number - 1][i + sh7].count_must_not++;
									}
									if ((i + sh7 + 1 < size_field) && (sh7 == size_ship - 1))
									{
										my_field[line_number][i + sh7 + 1].count_must_not++;
									}
									if ((i + sh7 - 1 > -1) && (sh7 == 0))
									{
										my_field[line_number][i + sh7 - 1].count_must_not++;
									}
									if ((i + sh7 + 1 < size_field) && (sh7 == size_ship - 1) && (line_number + 1 < size_field))
									{
										my_field[line_number + 1][i + sh7 + 1].count_must_not++;
									}
									if ((i + sh7 - 1 > -1) && (sh7 == 0) && (line_number + 1 < size_field))
									{
										my_field[line_number + 1][i + sh7 - 1].count_must_not++;
									}
									if ((i + sh7 + 1 < size_field) && (sh7 == size_ship - 1) && (line_number - 1 > -1))
									{
										my_field[line_number - 1][i + sh7 + 1].count_must_not++;
									}
									if ((i + sh7 - 1 > -1) && (sh7 == 0) && (line_number - 1 > -1))
									{
										my_field[line_number - 1][i + sh7 - 1].count_must_not++;
									}*/

								}
							}
							else
							{
								my_ship[number_ship].x[sh7] = line_number;
								my_ship[number_ship].y[sh7] = i - sh7;
								if ((my_field[line_number][i - sh7].flag_stay != true) && (my_field[line_number][i - sh7].count_must_not == 0))
								{
									my_field[line_number][i - sh7].life_square = 1;
									my_field[line_number][i - sh7].flag_stay = true;
									my_field[line_number][i - sh7].flag_life = true;
									if (my_field[line_number][i - sh7].link_ship == -1)
									{
										my_field[line_number][i - sh7].link_ship = number_ship;
									}
									/*if (line_number + 1 < size_field)
									{
										my_field[line_number + 1][i + sh7].count_must_not++;
									}
									if (line_number - 1 > -1)
									{
										my_field[line_number - 1][i + sh7].count_must_not++;
									}
									if ((i + sh7 + 1 < size_field) && (sh7 == size_ship - 1))
									{
										my_field[line_number][i + sh7 + 1].count_must_not++;
									}
									if ((i + sh7 - 1 > -1) && (sh7 == 0))
									{
										my_field[line_number][i + sh7 - 1].count_must_not++;
									}
									if ((i + sh7 + 1 < size_field) && (sh7 == size_ship - 1) && (line_number + 1 < size_field))
									{
										my_field[line_number + 1][i + sh7 + 1].count_must_not++;
									}
									if ((i + sh7 - 1 > -1) && (sh7 == 0) && (line_number + 1 < size_field))
									{
										my_field[line_number + 1][i + sh7 - 1].count_must_not++;
									}
									if ((i + sh7 + 1 < size_field) && (sh7 == size_ship - 1) && (line_number - 1 > -1))
									{
										my_field[line_number - 1][i + sh7 + 1].count_must_not++;
									}
									if ((i + sh7 - 1 > -1) && (sh7 == 0) && (line_number - 1 > -1))
									{
										my_field[line_number - 1][i + sh7 - 1].count_must_not++;
									}*/
								}
							}
						}
					}
					size_ship = 0;
					return true;

				}
				else
				{
					number_delete = my_field[line_number][i].link_ship;
					if (number_delete == -1)
					{
						return false;
					}
					size_ship = my_ship[my_field[line_number][i].link_ship].size_ship;
					for (int sh7 = 0; sh7 <= size_ship; sh7++)
					{
						my_field[my_ship[number_delete].x[sh7]][my_ship[number_delete].y[sh7]].life_square = 0;
						my_field[my_ship[number_delete].x[sh7]][my_ship[number_delete].y[sh7]].flag_stay = false;
						my_field[my_ship[number_delete].x[sh7]][my_ship[number_delete].y[sh7]].flag_life = false;
						my_field[my_ship[number_delete].x[sh7]][my_ship[number_delete].y[sh7]].link_ship = -1;
						/*if (my_ship[number_delete].x[sh7] + 1 < size_field)
						{
							my_field[my_ship[number_delete].x[sh7] + 1][my_ship[number_delete].y[sh7] + sh7].count_must_not++;
						}
						if (my_ship[number_delete].x[sh7] - 1 > -1)
						{
							my_field[my_ship[number_delete].x[sh7] - 1][my_ship[number_delete].y[sh7] + sh7].count_must_not++;
						}
						if ((my_ship[number_delete].y[sh7] + sh7 + 1 < size_field) && (sh7 == size_ship - 1))
						{
							my_field[my_ship[number_delete].x[sh7]][my_ship[number_delete].y[sh7] + sh7 + 1].count_must_not++;
						}
						if ((my_ship[number_delete].y[sh7] + sh7 - 1 > -1) && (sh7 == 0))
						{
							my_field[my_ship[number_delete].x[sh7]][my_ship[number_delete].y[sh7] + sh7 - 1].count_must_not++;
						}
						if ((my_ship[number_delete].y[sh7] + sh7 + 1 < size_field) && (sh7 == size_ship - 1) && (my_ship[number_delete].x[sh7] + 1 < size_field))
						{
							my_field[my_ship[number_delete].x[sh7] + 1][my_ship[number_delete].y[sh7] + sh7 + 1].count_must_not++;
						}
						if ((my_ship[number_delete].y[sh7] + sh7 - 1 > -1) && (sh7 == 0) && (my_ship[number_delete].x[sh7] + 1 < size_field))
						{
							my_field[my_ship[number_delete].x[sh7] + 1][my_ship[number_delete].y[sh7] + sh7 - 1].count_must_not++;
						}
						if ((my_ship[number_delete].y[sh7] + sh7 + 1 < size_field) && (sh7 == size_ship - 1) && (my_ship[number_delete].x[sh7] - 1 > -1))
						{
							my_field[my_ship[number_delete].x[sh7] - 1][my_ship[number_delete].y[sh7] + sh7 + 1].count_must_not++;
						}
						if ((my_ship[number_delete].y[sh7] + sh7 - 1 > -1) && (sh7 == 0) && (my_ship[number_delete].x[sh7] - 1 > -1))
						{
							my_field[my_ship[number_delete].x[sh7] - 1][my_ship[number_delete].y[sh7] + sh7 - 1].count_must_not++;
						}*/
					}
					size_ship = 0;
					number_ship--;
					//cout << number_delete << endl;
					//cout << number_ship << endl;
					for (int sh7 = number_delete; sh7 < number_ship; sh7++)
					{
						my_ship[sh7].x.resize( my_ship[sh7 + 1].size_ship+1);
						my_ship[sh7].y.resize(my_ship[sh7 + 1].size_ship+1);
						my_ship[sh7].size_ship = 1;
						my_ship[sh7].x = my_ship[sh7+1].x;
						my_ship[sh7].y = my_ship[sh7 + 1].y;
					}
					return true;
				}

			}
		}
	}
	//else
	//{
			//cout << number_ship << endl;
			/*for (int sh5 = 0; sh5 < number_ship; sh5++)
			{
			cout << my_ship[sh5].x[0] << endl;
			}*/
		//cout << "No More!" << endl;
			//string message = "You did not enter";
			//MessageBox(message);
			//ShowMessage(" ");
	//}
		return false;
	//}
	//else
	//{
	//	return false;
	//}
}

bool hitting(Points mouse_coord, bool fl)
{
	int flag;

	if ((my_field[0][0].pts[0].x < mouse_coord.x) && (mouse_coord.x< my_field[size_field - 1][size_field - 1].pts[3].x) && (my_field[0][0].pts[0].y > mouse_coord.y)&&(mouse_coord.y > my_field[size_field - 1][size_field - 1].pts[1].y))
	{
		for (int j = 0; j<size_field; j++)
		{
			if ((my_field[j][0].pts[0].y > mouse_coord.y) && (mouse_coord.y > my_field[j][size_field - 1].pts[2].y))
			{
				flag = line_hitting(mouse_coord, j,fl);
				
				if (flag)
				{
					//cout<<size_ship<<endl;
					//for (int sh4 = 0; sh4 <= number_ship; sh4++)
					//{
					/*	cout << my_ship[0].x[0] << endl << my_ship[0].y[0] << endl;
						cout << my_field[my_ship[0].x[0]][my_ship[0].y[0]].flag_stay<<endl;
						cout << my_ship[0].x[1] << endl << my_ship[0].y[1] << endl;
						cout << my_field[my_ship[0].x[1]][my_ship[0].y[1]].flag_stay << endl;*/

						//cout << "point 1";
					//}
					
					return true;
				}
			}
		}

	}
	else
	{
		for (int sh2 = 0; sh2 < Size_ship; sh2++)
		{
			if ((Ships_versions[sh2].pts[0].x < mouse_coord.x) && (mouse_coord.x< Ships_versions[sh2].pts[3].x) && (Ships_versions[sh2].pts[0].y > mouse_coord.y) && (mouse_coord.y > Ships_versions[sh2].pts[1].y))
			{
				size_ship = sh2+1;
				//number_ship++;
				//cout << number_ship << endl;
				return false;
			}
		}
		return false;
	}
	return false;
}

void event_handling(int button, int state, int x, int y)
{
	Points mouse_coordinate;
	if (button == GLUT_LEFT_BUTTON) 
	{
		if ((state == GLUT_DOWN))
		{
			mouse_coordinate = mouse(x, y);
			
			if (hitting(mouse_coordinate, true))
			{
				glutPostRedisplay();
			}
		}
	}
	else
	{
		if (button == GLUT_RIGHT_BUTTON)
		{
			if ((state == GLUT_DOWN))
			{
				mouse_coordinate = mouse(x, y);

				if (hitting(mouse_coordinate,false))
				{
					glutPostRedisplay();
				}
			}
		}
	}
}

void line_create(double x1, double y1, double x2, double y2, double x3, double y3, double x4, double y4, bool flag)
{
	short int j = 0, k = 0;
	for (int i = 0; i <= size_field; i++)
	{
		if (flag)
		{
			k = i;
		}
		else
		{
			j = i;
		}

		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2d(x1 + 0.1*k, y1 + 0.1*j);
		glVertex2d(x2 + 0.1*k, y2 + 0.1*j);

		glEnd();

		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2d(x3 + (0.1*k), y3 + 0.1*j);
		glVertex2d(x4 + (0.1*k), y4 + 0.1*j);

		glEnd();
	}

}
/*void line_create_1(double x1, double y1, double x2, double y2, bool flag)
{
	short int j = 0, k = 0;
	for (int i = 0; i < 2; i++)
	{
		if (flag)
		{
			k = i;
		}
		else
		{
			j = i;
		}

		glColor3f(0, 0, 0);
		glBegin(GL_LINES);
		glVertex2d(x1 + 0.1*k, y1 + 0.1*j);
		glVertex2d(x2 + 0.1*k, y2 + 0.1*j);

		glEnd();
	}
}*/

void display()
{

	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(0.10, 0.70, 0.70);// поле

	glBegin(GL_QUADS);

	glVertex2d(-0.95, 0.2);
	glVertex2d(-0.15, 0.2);
	glVertex2d(-0.15, 1);
	glVertex2d(-0.95, 1);

	glEnd();

	glBegin(GL_QUADS);//враг

	glVertex2d(0.15, 0.2);
	glVertex2d(0.95, 0.2);
	glVertex2d(0.95, 1);
	glVertex2d(0.15, 1);

	glEnd();




	glColor3f(0.51, 0.826, 0.773);//корабли
	glBegin(GL_QUADS);

	glVertex2f(-0.5, -0.7);
	glVertex2f(0.1, -0.7);
	glVertex2f(0.1, -0.15);
	glVertex2f(-0.5, -0.15);

	glEnd();

	for (int sh1 = 0; sh1 < Size_ship; sh1++)
	{
		Ships_versions[sh1].Draw_square();
	}


	for (int sh1 = 0; sh1 < size_field; sh1++)
	{
		for (int sh2 = 0; sh2 < size_field; sh2++)
		{
			if (my_field[sh1][sh2].flag_stay)
			{
				my_field[sh1][sh2].Draw_square();
			}
		}
	}

	line_create(-0.95, 0.2, -0.95, 1, 0.15, 0.2, 0.15, 1, true);
	line_create(-0.95, 0.2, -0.15, 0.2, 0.15, 0.2, 0.95, 0.2, false);

	glutSwapBuffers();

}

void initializ()
{
	Ships_versions[0].pts[0].x = -0.5;
	Ships_versions[0].pts[0].y = -0.15;
	Ships_versions[0].pts[1].x = -0.5;
	Ships_versions[0].pts[1].y = -0.25;
	Ships_versions[0].pts[2].x = -0.4;
	Ships_versions[0].pts[2].y = -0.25;
	Ships_versions[0].pts[3].x = -0.4;
	Ships_versions[0].pts[3].y = -0.15;
	Ships_versions[0].flag_stay = true;
	Ships_versions[0].flag_life = true;

	Ships_versions[1].pts[0].x = -0.5;
	Ships_versions[1].pts[0].y = -0.30;
	Ships_versions[1].pts[1].x = -0.5;
	Ships_versions[1].pts[1].y = -0.40;
	Ships_versions[1].pts[2].x = -0.3;
	Ships_versions[1].pts[2].y = -0.40;
	Ships_versions[1].pts[3].x = -0.3;
	Ships_versions[1].pts[3].y = -0.30;
	Ships_versions[1].flag_life = true;
	Ships_versions[1].flag_stay = true;

	Ships_versions[2].pts[0].x = -0.5;
	Ships_versions[2].pts[0].y = -0.45;
	Ships_versions[2].pts[1].x = -0.5;
	Ships_versions[2].pts[1].y = -0.55;
	Ships_versions[2].pts[2].x = -0.2;
	Ships_versions[2].pts[2].y = -0.55;
	Ships_versions[2].pts[3].x = -0.2;
	Ships_versions[2].pts[3].y = -0.45;
	Ships_versions[2].flag_life = true;
	Ships_versions[2].flag_stay = true;

	Ships_versions[3].pts[0].x = -0.5;
	Ships_versions[3].pts[0].y = -0.60;
	Ships_versions[3].pts[1].x = -0.5;
	Ships_versions[3].pts[1].y = -0.70;
	Ships_versions[3].pts[2].x = -0.1;
	Ships_versions[3].pts[2].y = -0.70;
	Ships_versions[3].pts[3].x = -0.1;
	Ships_versions[3].pts[3].y = -0.60;
	Ships_versions[3].flag_life = true;
	Ships_versions[3].flag_stay = true;

}

void initVecVec(vector<vector<Square> > &_vec, unsigned int _nSize)
{
	_vec.resize(_nSize);
	for (unsigned int i = 0; i < _nSize; i++)
	{
		_vec[i].resize(_nSize);
	}
}

void initSh(unsigned int _nSize)
{
	Ships_versions.resize(_nSize);
}


int main(int argc, char **argv)
{
	initVecVec(my_field, size_field);
	initVecVec(enemy_field, size_field);
	my_ship.reserve(Count_Ship);
	enemy_ship.reserve( Count_Ship);
	for (int i = 0; i < size_field; i++)
	{
		for (int j = 0; j < size_field; j++)
		{
			my_field[i][j].pts[0].x = -0.95 + j*0.1;
			my_field[i][j].pts[0].y = 1.0 - i*0.1;
			my_field[i][j].pts[1].x = -0.95 + j*0.1;
			my_field[i][j].pts[1].y = 0.9 - i*0.1;
			my_field[i][j].pts[2].x = -0.85 + j*0.1;
			my_field[i][j].pts[2].y = 0.9 - i*0.1;
			my_field[i][j].pts[3].x = -0.85 + j*0.1;
			my_field[i][j].pts[3].y = 1.0 - i*0.1;
		}
	}

	for (int i = 0; i < size_field; i++)
	{
		for (int j = 0; j < size_field; j++)
		{
			enemy_field[i][j].pts[0].x = 0.15 + j*0.1;
			enemy_field[i][j].pts[0].y = 1.0 - i*0.1;
			enemy_field[i][j].pts[1].x = 0.15 + j*0.1;
			enemy_field[i][j].pts[1].y = 0.9 - i*0.1;
			enemy_field[i][j].pts[2].x = 0.25 + j*0.1;
			enemy_field[i][j].pts[2].y = 0.9 - i*0.1;
			enemy_field[i][j].pts[3].x = 0.25 + j*0.1;
			enemy_field[i][j].pts[3].y = 1.0 - i*0.1;
		}
	}
	initSh(Size_ship);
	initializ();

	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE);
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(200, 0);
	glutCreateWindow("Window");

	glClearColor(1, 1, 1, 0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//glOrtho(0, 0, 1, 1, 0, 0);
	glutDisplayFunc(display);


	glutMouseFunc(event_handling);


	glutMainLoop();
	return 0;
}