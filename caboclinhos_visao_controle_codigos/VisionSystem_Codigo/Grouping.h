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
 * Descrição:    Esse arquivo contém a definição da classe Grouping
 *               que é responsável por realizar um agrupamento de pixels
 *               em uma imagem, onde esses pixels representam uma determinada
 *               cor de identificação dos robôs. Com isso é possível achar
 *               o centro dos robôs.
 *
 *
*/
//-----------------------------------------------------------------------

#ifndef GROUPING_H_
#define GROUPING_H_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <utility>
#include <time.h>
using namespace std;
using namespace cv;
class Grouping
{
private:
	int number;
	int classifier;

	vector<Point>pontos;
	vector<double> posx;
	vector<double> posy;
	vector< vector<Point> > contours;
	vector<Vec4i> hierarchy;
	vector<int> qtd_kmeans;

    /*
     * Método: Classification_FindContours(Mat *segmentacao);
     *
     * Descrição: Esse método busca os pontos de contorno de um corpo
     *            em uma imagem binária. A partir desses pontos é possível
     *            determinar o centro de massa desse corpo. Os dados referentes
     *            aos centros de massa e quantidade de pontos, são guardados
     *            nas variáveis da classe
     *
     *
     * Parâmetros:
     *            1) Mat *segmentacao - ponteiro para a imagem binária
     *
     *
     * Retorno:
     *       Nenhum
     *
     */
	void Classification_FindContours(Mat *segmentacao);

    /*
     * Método: Classification_kmeans(Mat *segmentacao);
     *
     * Descrição: Esse método usa o algoritmo kmeans para fazer o agrupamento
     *            de pontos e logo após encontrar os centros de massa dos corpos
     *            contidos na imagem binária.
     *
     *
     *
     * Parâmetros:
     *            1) Mat *segmentacao - ponteiro para a imagem binária
     *
     *
     * Retorno:
     *       Nenhum
     *
     */
	void Classification_kmeans(Mat *segmentacao);

public:
    /*
     * Método: Grouping(int qtd_group,int classification);
     *
     * Descrição: Método para instanciar o objeto Grouping
     *
     * Parâmetros:
     *            1) int qtd_group - valor inteiro referente a quantidade
     *                               de corpos que serão procurados na imagem
     *
     *            2) in classification - valor inteiro referente a qual classificador
     *                                   será usado, 0- FindContours 1- kmeans
     *
     *
     * Retorno:
     *       Nenhum
     *
     */
	Grouping(int qtd_group,int classification);

    /*
     * Método: Grouping_Result(Mat *binary_image);
     *
     * Descrição: Método para proporcionar o retorno dos centros encontrados
     *            e da quantidade de pontos referentes a cada corpo
     *
     * Parámetros:
     *           1) Mat *segmentacao - ponteiro para a imagem binária
     *
     *
     * Retorno:
     *       vetor do tipo  vector<pair<Point,int> > onde cada elemento do vetor possui um par de valores
     *       onde o primeiro valor corresponde a coordenada (x,y) do centro do corpo com relação à imagem
     *       e o segundo valor informa a quantidade de pontos referente à aquele corpo.     *
     */
     vector<pair<Point,int> > Grouping_Result(Mat *binary_image);
};
#endif
