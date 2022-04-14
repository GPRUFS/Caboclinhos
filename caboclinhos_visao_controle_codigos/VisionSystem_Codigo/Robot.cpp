#include "Robot.h"

using namespace cv;

Robot::Robot()
{
	camisa_identificador = Point(0,0);
	camisa_time =Point(0,0);
	centro_robo = Point(0,0);
	orientacao = 0;
	zonamorta_d = 0;
	zonamorta_e = 0;
    prop_roda_d = 1;
    prop_roda_e = 1;
}
Robot::Robot(Point cor_time, Point cor_id)
{
	Refresh_Position(cor_time,cor_id);
	zonamorta_d = 0;
	zonamorta_e = 0;
}
void Robot::Refresh_Position(Point cor_time, Point cor_id)
{
	camisa_identificador = cor_id;
	camisa_time = cor_time;
	calc_center_robot();
	calc_orientation();
}
void Robot::calc_center_robot()
{
	centro_robo = Point(camisa_time.x + 0.3814 * (camisa_identificador.x - camisa_time.x ),camisa_time.y + 0.3814 * (camisa_identificador.y-camisa_time.y));
}
void Robot::calc_orientation()
{
	orientacao = atan2(camisa_identificador.y-camisa_time.y,camisa_identificador.x-camisa_time.x)*180/3.1415;
}

Point Robot::get_center_robot(){
		return centro_robo;
}
	double Robot::get_orientation(){
		return orientacao;
}

Robot::~Robot() {}

