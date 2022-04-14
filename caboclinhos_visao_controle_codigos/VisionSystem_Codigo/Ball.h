//-------------------------------------------------------------------------
/*
 * Arquivo: Ball.h
 *
 * Sistema:  VisionSystem
 * Nome do Componente: Ball
 * Linguagem: C++
 *
 * (c) Copyright GPRUFS 2015
 * Endereço:
 *    UFS
 *
 * Autor: GPRUFS
 * E-Mail:
 *
 *
 * Descrição:   Esse arquivo contém a definição da classe Ball
 *              que é responsável por guardar as coordenadas
 *              x e y da posição da bola com relação à imagem
 *              do campo.
 *
*/
//-----------------------------------------------------------------------
#ifndef BALL_H_
#define BALL_H_
#include <opencv2/opencv.hpp>
#include <fstream>
using namespace std;
using namespace cv;
class Ball
{
private:

public:
    int x; // Coordenada x da posição da bola
    int y; // Coordenada y da posição da bola

    /*
     * Metodo: Ball()
     * Acesso: public
     * Descrição: Método responsável por instanciar a classe Ball
     * Parametro:
     *         Nenhum
    */
	Ball();

    /*
     * Método: Refresh_Position(Point bola);
     * Acesso: public
     * Descrição: Atualiza a coordenada da posição da bola que é
     *              guardada pela classe Ball.
     * Parâmetro:
     *           1) Point bola - Ponto(x,y) da coordenada da bola.
     *
     * Retorno:
     *       Nenhum.
     *
    */
	void Refresh_Position(Point bola);

    /*
     * Método: Refresh_Position(int xa, int ya);
     * Descrição: Atualiza a coordenada da posição da bola que é
     *              guardada pela classe Ball.
     * Parâmetro:
     *           1) int xa - Valor inteiro referente à coordenada x
     *                       da posição da bola.
     *
     *           2) int ya - Valor inteiro referente à coordenada y
     *                       da posição da bola.
     * Retorno:
     *       Nenhum.
    */
	void Refresh_Position(int xa,int ya);



	~Ball();
};
#endif
