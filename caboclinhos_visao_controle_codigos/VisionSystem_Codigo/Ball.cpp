#include "Ball.h"
Ball::Ball()
{
	x=-1;
	y=-1;

}
void Ball::Refresh_Position(Point bola)
{
	x = bola.x;
	y = bola.y;

}
void Ball::Refresh_Position(int xa, int ya)
{
	    x = xa;
		y = ya;		
}

Ball::~Ball()
{

}

