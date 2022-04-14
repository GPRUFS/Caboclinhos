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
 *               contem a definição da classe Segmentation, que é
 *               responsável por realizar a segmentação de uma
 *               determinada cor numa imagem, a partir de um intervalo
 *               de limiares que conseguem representar uma determinada
 *               cor em RGB.
 *
*/
//-----------------------------------------------------------------------

#ifndef SEGMENTATION_H_
#define SEGMENTATION_H_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include<algorithm>
#include<vector>

using namespace cv;
using namespace std;

class Segmentation
{
private:
	Scalar rgbmin;
	Scalar rgbmax;
    Mat segmentacao;
    Mat Mascara[2];
    vector< vector<Point> > contours;
    vector<Vec4i> hierarchy;

public:
    /*
     * Método: Segmentation(Scalar min,Scalar max,Mat *Mask);
     *
     * Descrição: Instância um objeto da classe Segmentation
     *            atribuindo características como os intervalos
     *            de limiares e as mascaras para operações
     *            morfológicas de abertura e fechamento
     *
     * Parâmetros:
     *            1) Scalar min - Limiar contendo os valores minimos de Red,Green,Blue
     *
     *            2) Scalar max - Limiar contendo os valores máximo de Red,Green,Blue
     *
     *            3) Mat *Mask - ponteiro para uma matriz do tipo Mat que representa
     *                           a forma da mascara usada para as operações de abertura
     *                           e fechamento.
     *
     * Retorno:
     *        Nenhum
     */
	Segmentation(Scalar min,Scalar max,Mat *Mask);

    /*
     * Metodo:  Segmentation_Result(Mat *frame);
     *
     * Descrição: Responsável pelo retorno da matriz binária resultante
     *            da segmentação, feita a partir dos limiares definidos,
     *            da imagem fornecida.
     *
     * Parametros:
     *            1) Scalar min - Limiar contendo os valores minimos de Red,Green,Blue
     *
     *            2) Scalar max - Limiar contendo os valores máximo de Red,Green,Blue
     *
     *            3) Mat *Mask - ponteiro para uma matriz do tipo Mat que representa
     *                           a forma da mascara usada para as operações de abertura
     *                           e fechamento.
     *
     * Retorno:
     *        Nenhum
     */
	Mat* Segmentation_Result(Mat *frame);





};
#endif
