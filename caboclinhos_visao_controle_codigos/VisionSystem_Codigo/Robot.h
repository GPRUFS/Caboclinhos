#ifndef ROBOT_H_
#define ROBOT_H_
//-------------------------------------------------------------------------
/*
 * Arquivo: Grouping.h
 *
 * Sistema:  VisionSystem
 * Nome do Componente: Grouping
 * Linguagem C++
 *
 * (c) Copyright GPRUFS 2015
 * Endereço:
 *    UFS
 *
 * Autor: GPRUFS
 * E-Mail:
 *
 *
 * Descrição:    Esse arquivo contém a definição da classe Robot
 *               que é responsável por armazenar características
 *               referentes a um determinado robô.
 *
 *               Segue as características armazenadas:
 *
 *               - Centros das Cores de identificação e da camisa do time
 *               - Coordenada (x,y) da posição do centro do robô com relação à imagem
 *               - Orientação do Robô em radianos
 *               - Zona morta das rodas direita e esquerda
 *               - Velocidade linear máxima
 *               - Velocidade angular máxima
 *               - Constante de proporcionalidade da velocidade linear
 *               - Constante de proporcionalidade da velocidade angular
 *
 *
 *
 *
*/
//-----------------------------------------------------------------------
#include <iostream>
#include "opencv2/opencv.hpp"
#include "Grouping.h"

using namespace cv;

class Robot
{
	private:
        Point camisa_identificador;// centro da cor da parte da camisa q identifica um robô
		Point camisa_time; // centro da cor da parte da camisa que identifica o time... azul ou amarelo
		Point centro_robo;
		double orientacao; // dada em radianos
	public:
		Robot();
		Robot(Point cor_time, Point cor_id);
		~Robot();
        /*
         * Método:Refresh_Position(Point cor_time, Point cor_id);
         *
         * Descrição: Atualiza a posição e orientação do robô com relação
         *            à imagem adquirida pela câmera do sistema
         *
         * Parâmetros:
         *            1) Point cor_time - Objeto do tipo Point referente ao centro de massa
         *                                da cor do time robô.
         *
         *            2) Point cor_id - Objeto do tipo Point referente ao centro de massa
         *                              da cor de identificação do robô
         *
         * Retorno:
         *        Nenhum
         */
		void Refresh_Position(Point cor_time, Point cor_id);

        int zonamorta_d; // zona morta do motor referente à roda direita
        int zonamorta_e; // zona morta do motor referente à roda esquerda
        double k_lin; // constante de proporcionalidade linear
        double k_ang; // constante de proporcionalidade angular
        double V_max; // velocidade linear máxima
        double W_max; // velocidade angular máxima
        double prop_roda_d;
        double prop_roda_e;

        /*
         * Método: get_center_robot();
         *
         * Descrição: Retorna a coordenada (x,y) referente ao centro do robô
         *
         *
         * Parâmetros:
         *           Nenhum
         *
         * Retorno:
         *        Retorna um objeto do tipo Point que armazena a coordenada(x,y)
         *        da posição do centro do robô         *
         */
		Point get_center_robot();

        /*
         * Método: get_orientation();
         *
         * Descrição: Retorna a orientação do robô em radianos         *
         *
         * Parâmetros:
         *           Nenhum
         *
         * Retorno:
         *        Retorna um valor double referente à orientação do robô em radianos
         */
		double get_orientation();

	private:
        /*
         * Método: calc_orientation();
         *
         * Descrição: Calcula a orientação do robô em radianos.
         *            O valor calculado é armazenado nas variáveis
         *            da classe.
         *
         *
         * Parâmetros:
         *           Nenhum
         *
         * Retorno:
         *        Nenhum
         */
		void calc_orientation();

        /*
         * Método: calc_center_robot();
         *
         * Descrição: Calcula a coordenada(x,y) referente à posição do centro do robô
         *            O valor calculado é armazenado nas variáveis
         *            da classe.
         *
         * Parâmetros:
         *           Nenhum
         *
         * Retorno:
         *        Nenhum
         */
		void calc_center_robot();
};
#endif
