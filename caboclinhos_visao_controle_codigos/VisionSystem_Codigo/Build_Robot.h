//-------------------------------------------------------------------------
/*
 * Arquivo: Build_Robot.h
 *
 * Sistema:  VisionSystem
 * Nome do Componente: Build_Robot
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
 * Descrição:    Esse arquivo contém a definição da classe Build Robot
 *               que é responsável por fazer a separação entre os robôs
 *               do time adversário e os robôs controlados por esse
 *               sistema. A distinção dos robôs levou em conta caracteriscas
 *               do padrão de camisa usado pelo time do GPRUFS. Adicionalmente,
 *               essa classe permite a gravação das coordenadas (x,y),
 *               com relação à imagem obtida pela câmera do sistema, de cada
 *               robô em arquivos de texto.
 *
*/
//-----------------------------------------------------------------------
#ifndef BUILD_ROBOT_H_
#define BUILD_ROBOT_H_

#include <iostream>
#include <opencv2/opencv.hpp>
#include <Windows.h>
#include <algorithm>
#include <vector>
#include <utility>
#include <fstream>
#include "Grouping.h"
#include "Robot.h"
using namespace cv;
using namespace std;

class Build_Robot
{
private:
	int number_robots;
    Robot rb1; // Robô 1
    Robot rb2; // Robô 2
    Robot rb3; // Robô 3
    int tamanho; //distância do centro da camisa azul/amarelo até a outra cor
	bool gravar_arquivo;

	ofstream arquivo_rb1;
   	ofstream arquivo_rb2;
   	ofstream arquivo_rb3;



public:
    /*
     * Método: Build_Robot(int numero_robos);
     *
     * Descrição:   Responsável por instanciar um objeto
     *              da classe Build_Robot.
     * Parâmetros:
     *           1) int numero_robos - Valor inteiro referente ao número de
     *                                 robôs contidos no time
     *
     * Retorno:
     *       Nenhum.
    */
	Build_Robot(int numero_robos);
	~Build_Robot();

    /*
     * Metodo: Change_dist_cores(int i);
     * Descrição: Define para classe a distância entre o centro da cor
     *            identificadora do robô e a cor do time
     * Parâmetros:
     *           1) int i - Valor inteiro referente ao à distância entre
     *              o centro da cor identificadora do robô e a cor do
     *              time.
     *
     * Retorno:
     *       Nenhum.
    */
    void Change_dist_cores(int i);

    /*
     * Método: Record_Position(bool i);
     *
     * Descrição: habilita ou desabilita a gravação das coordenadas
     *            de cada robô, do time controlado pelo sistema, em
     *            um arquivo de texto.
     * Parâmetros:
     *           1) bool p - valor lógico onde o valor true, habilita a
     *                       gravação das coordenadas dos robôs em um
     *                       arquivo de texto e o valor false, desabilita
     *                       essa gravação
     *
     * Retorno:
     *       Nenhum.
    */
	void Record_Position(bool p);

    /*
     * Método:Get_Centers(vector<pair<Point,int> >camisa_time,vector<pair<Point,int> >id_camisas[],vector<pair<Point,int> >camisa_adversario);
     *
     * Descrição: Faz a aquisição das coordenadas dos centros da cor
     *            identificadora do robô controlado por esse sistema
     *            e da cor correspondente à camisa do time
     *
     * Parâmetros:
     *          1) vector<pair<Point,int> >camisa_time - Vetor composto por dois valores em cada coluna
     *                                                    onde o primeiro valor, camisa_time[posicao].first,
     *                                                    indica a coordenada do centro da camisa do time e
     *                                                    o segundo valor, camisa_time[posicao].second,indica
     *                                                    a quantidade de pontos do contorno da cor, encontrados
     *                                                    na segmentacao
     *
     *          2)vector<pair<Point,int> >id_camisas[] - Tabela Hash composta por 3 linhas onde cada linha representa
     *                                                   uma cor de identificação do time de robôs controlado por esse
     *                                                   sistema. Por exemplo, linha 0 - vermelho, linha 1 - verde,
     *                                                   linha 2 - magenta. A quantidade de colunas em cada linha é
     *                                                   determinada pela quantidade de centros resultantes pela segmentacao
     *                                                   de uma determinada cor de identificação. Por exemplo, a tabela pode
     *                                                   ter a seguinte forma:
     *                                                                        ______________________________________________________
     *                                                   linha 0 - vermelho  |centro1 vermelho| centro2 vermelho | centro 3 vermelho|
     *                                                                        _____________
     *                                                   linha 1 - verde     |centro1 verde|
     *                                                                        _________________________________
     *                                                   linha 2 - magenta   |centro1 magenta| centro 2 magenta|
     *
     *                                                   Cada elemento dessa tabela é um objeto Pair<Point,int> onde o primeiro
     *                                                   elemento do Pair (Pair.first) é um objeto Point(x,y), que representa
     *                                                   as coordenadas da posição do centro de uma determinada cor com relação
     *                                                   à imagem adquirida pela câmera do sistema. O segundo elemento do Pair
     *                                                   (Pair.second) representa a quantidade de pontos do contorno, da cor de
     *                                                   identificação do robô, encontrados durante a segmentação.
     *
     *          3) vector<pair<Point,int> >camisa_time - Vetor composto por dois valores em cada coluna
     *                                                   onde o primeiro valor, camisa_advesario[posicao].first,
     *                                                   indica a coordenada do centro da cor da camisa do time
     *                                                   adversário e o segundo valor, camisa_adversario[posicao].second
     *                                                   indica a quantidade de pontos do contorno da cor, encontrados
     *                                                   na segmentacao
     *
     * Retorno:
     *       Nenhum.
    */
    void Get_Centers(vector<pair<Point,int> >camisa_time,vector<pair<Point,int> >id_camisas[],vector<pair<Point,int> >camisa_adversario);

    /*
     * Método: Marriage(vector<Point>camisa_time,vector< pair<Point,int> >id_camisa[], vector<Point>camisa_adversario);
     *
     * Descrição: Esse metodo faz a distinção de cada robô controlado por
     *            esse sistema, para evitar possíveis ambiguidades que ocorrem
     *            quando vários robôs se juntam ou colidem.
     *
     * Parâmetros:
     *                     1) vector<Point>camisa_time - Vetor onde cada elemento é um objeto Point(x,y)
     *                                                   que indica a coordenada da posição do centro da camisa
     *                                                   do time na imagem adquirida pela câmera do sistema
     *
     *
     *          2)vector<pair<Point,int> >id_camisas[] - Tabela Hash composta por 3 linhas onde cada linha representa
     *                                                   uma cor de identificação do time de robôs controlado por esse
     *                                                   sistema. Por exemplo, linha 0 - vermelho, linha 1 - verde,
     *                                                   linha 2 - magenta. A quantidade de colunas em cada linha é
     *                                                   determinada pela quantidade de centros resultantes pela segmentacao
     *                                                   de uma determinada cor de identificação. Por exemplo, a tabela pode
     *                                                   ter a seguinte forma:
     *                                                                        ______________________________________________________
     *                                                   linha 0 - vermelho  |centro1 vermelho| centro2 vermelho | centro 3 vermelho|
     *                                                                        _____________
     *                                                   linha 1 - verde     |centro1 verde|
     *                                                                        _________________________________
     *                                                   linha 2 - magenta   |centro1 magenta| centro 2 magenta|
     *
     *                                                   Cada elemento dessa tabela é um objeto Pair<Point,int> onde o primeiro
     *                                                   elemento do Pair (Pair.first) é um objeto Point(x,y), que representa
     *                                                   as coordenadas da posição do centro de uma determinada cor com relação
     *                                                   à imagem adquirida pela câmera do sistema. O segundo elemento do Pair
     *                                                   (Pair.second) representa a quantidade de pontos do contorno, da cor de
     *                                                   identificação do robô, encontrados durante a segmentação.
     *
     *
     *               3) vector<Point>camisa_adversario - Vetor onde cada elemento é um objeto Point(x,y)
     *                                                   que indica a coordenada da posição do centro da camisa
     *                                                   do time adversário na imagem adquirida pela câmera do
     *                                                   sistema
     *
     *
     *
     * Retorno:
     *       Nenhum.
    */
	void Marriage(vector<Point>camisa_time,vector< pair<Point,int> >id_camisa[], vector<Point>camisa_adversario);
    /*
     * Método: ector<Robot> Get_robos()
     *
     * Descrição: Responsável por retornar todas as características
     *            dos robôs armazenados por essa classe
     *
     * Parâmetros:
     *           Nenhum.
     *
     * Retorno:
     *       retorna um vetor do tipo vector<Robo> onde cada
     *       elemento do vetor é um objeto Robo que armazena
     *       características como, Coordenadas da posição,
     *       orientação, zona morta do motor, e constantes específicas.
     *       Nessa versão do sistema são retornados 3 objetos
     *       Robô dentro dentro do vetor, onde a posição 0
     *       corresponde ao robô vermelho, a posição 1 corresponde
     *       ao robô verde e a posição 2 corresponde ao robô
     *       magenta.
     *
    */
	vector<Robot> Get_robos();


    Point rb1_linha[2];
    Point rb2_linha[2];
    Point rb3_linha[2];
};

#endif
