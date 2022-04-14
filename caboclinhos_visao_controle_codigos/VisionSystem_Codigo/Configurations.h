//-------------------------------------------------------------------------
/*
 * Arquivo: Configurations.h
 *
 * Sistema:  VisionSystem
 * Nome do Componente: Configurations
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
 * Descrição:  Esse arquivo contém a definição da classe Configuration
 *             que é responsável por carregar e atribuir ao programa
 *             informações adquiridas a partir do software de calibração
 *
 *             Segue abaixo os dados carregados:
 *
 *             - Limiares das cores dos robôs
 *             - Delimitações do campo
 *             - Constantes de zona morta dos motores
 *             - Configurações da camera(Brilho, Saturação,Exposição,Contraste)
 *             - Resolução da câmera
 *             - Dimensão e posição de corte da imagem adquirida
 *             - Características dos robôs( velocidade máxima linear,
 *               velocidade máxima angular, constantes de proporcionalidade)
 *             - Mascaras
 *
*/
//-----------------------------------------------------------------------
#ifndef CONFIGURATIONS_H_
#define CONFIGURATIONS_H_

#include <iostream>
#include "opencv2/opencv.hpp"
#include <String>
#include <vector>
#include <cstdlib>
#include <Windows.h>

using namespace std;
using namespace cv;

class Configurations
{
	public:

        //Variáveis correspondente às delimitações do campo

        int ftop;
        int fbot;
        int gtopy;
        int gboty;
        int fleftx;
        int frightx;
        int gleft;
        int gright;
        int area_left;
        int area_right;
        int lgoleiro;
        int lzagueiro;
        int area_topy;
        int area_boty;
        int p_area_b;
        int p_area_t;
        int tam_robo;
        int diametro_robo;
        int meio_campo_y;
        int meio_campo_x;

        //Constantes dos robôs

        double rb1[4];    //Constantes Referente ao Robô 1
                          //rb1[0] - Velocidade linear máxima
                          //rb1[1] - Constante de proporcionalidade para a velocidade linear
                          //rb1[2] - Velocidade Angular máxima
                          //rb1[3] - Constante de proporcionalidade para a velocidade angular

        double rb2[4];    //Constantes Referente ao Robô 2
                          //rb2[0] - Velocidade linear máxima
                          //rb2[1] - Constante de proporcionalidade para a velocidade linear
                          //rb2[2] - Velocidade Angular máxima
                          //rb2[3] - Constante de proporcionalidade para a velocidade angular

        double rb3[4];    //Constantes Referente ao Robô 3
                          //rb3[0] - Velocidade linear máxima
                          //rb3[1] - Constante de proporcionalidade para a velocidade linear
                          //rb3[2] - Velocidade Angular máxima
                          //rb3[3] - Constante de proporcionalidade para a velocidade angular

        //Constantes referente a zona morta do motor

        int zonamorta_rb1[2];  //Zona morta referente ao Robô 1
                               //zonamorta_rb1[0] - Zona morta do motor direito
                               //zonamorta_rb1[1] - Zona morta do motor esquerdo

        int zonamorta_rb2[2];  //Zona morta referente ao Robô 2
                               //zonamorta_rb2[0] - Zona morta do motor direito
                               //zonamorta_rb2[1] - Zona morta do motor esquerdo

        int zonamorta_rb3[2];  //Zona morta referente ao Robô 3
                               //zonamorta_rb3[0] - Zona morta do motor direito
                               //zonamorta_rb3[1] - Zona morta do motor esquerdo

        /*
         * Método: Configurations(VideoCapture, String);
         *
         * Descrição: Responsável por instanciar o objeto Configurations.
         *            Durante a instanciação o objeto ja carrega as
         *            informações de um arquivo de texto, armazena as
         *            informações referente aos robôs e configura a câmera
         *            do sistema com as informações referente à câmera.
         *
         *
         *
         * Parâmetros:
         *           1) VideoCapture cap - Objeto do opencv referente ao controle
         *                                 da câmera do sistema.
         *           2) String filename - Objeto do tipo String referente ao nome
         *                                do arquivo de texto do tipo (Arquivo.extensão)
         *
         * Retorno:
         *        Nenhum.
         *
        */
		Configurations(VideoCapture, String);
		~Configurations();
		vector<int> GetSettingsAnyData(String); //"Cut_Frame_Points", Color name("Blue", "Yellow", etc.) or "Morph_Element"


        /*
         * Método: GetCutFramePoints();
         *
         * Descrição: Responsável por carregar as coordenadas do corte retângular
         *            que é feito para a extração do campo na imagem          *
         *
         *
         * Parâmetros:
         *          Nenhum
         * Retorno:
         *        Retorna um Objeto Rect do opencv que armazena essas coordenadas do corte
         *
        */
        Rect GetCutFramePoints();

        /*
         * Método: GetConfigurationsElement(Mat*);
         *
         * Descrição: Responsável por carregar uma mascara para operações morfológicas
         *            de abertura e fechamento em imagem.
         *
         *
         * Parâmetros:
         *          1) Mat *Mascara - Um ponteiro para uma Matriz do tipo Mat que corresponde
         *                            à forma da mascara.
         * Retorno:
         *        Nenhum.
         *
        */
		void GetConfigurationsElement(Mat*);

        /*
         * Método:GetThresholdColor(Scalar*, String);
         *
         * Descrição: Responsável por extrair de um arquivo os limiares de uma determinada cor
         *            no padrão RGB.
         *
         * Parâmetros:
         *             1) Scalar* Threshold - Um ponteiro para um vetor do tipo Scalar com 2 posições
         *                                    onde a primeira posição receberá o limiar mínimo e na
         *                                    segunda posição o limiar maximo, todos no padrão RGB.
         *                                    Essa variável Treshold fará o papel de retorno da função,
         *                                    pois como ela é um ponteiro a função GetConfigurationsElement(Mat*)
         *                                    modificará o seu valor e portanto os valores finais da parâmetro
         *                                    de entrada Treshold serão os valores de retorno dessa função.
         *
         *              2) String ColorName - Nome da cor referente aos limiares que serão extraídos.
         *
         * Retorno:
         *        Nenhum.
         *
        */
        void GetThresholdColor(Scalar*, String);//Scalar Vector with two positions, Color name("Blue", "Yellow", etc.)

        /*
         * Método:ReadConfigurationsRobots(String);
         *
         * Descrição: Responsável por extrair de um arquivo todas as informações
         *            referente aos robôs. Após a extração esse método armazena essas
         *            informações nas variáveis da classe Configurations
         *
         * Parâmetros:
         *            1) String filename - Nome do arquivo de texto do tipo (Arquivo.extensão)
         *
         * Retorno:
         *        Nenhum.
         *
        */
        void ReadConfigurationsRobots(String);

        /*
         * Método:WriteConfigurationsRobots(double*, double*, double*, int*, int*, int*, String);
         *
         * Descrição: Responsável por salvar em um arquivo de texto
         *            os valores atualizados das informações dos robôs;
         *
         * Parâmetros:
         *            1)double *rb1 - ponteiro para um vetor do tipo double de tamanho 4 de forma que
         *                            possuam valores referentes a características do robô 1 na respectiva
         *                            ordem:
         *                            rb1[0] - Velocidade linear máxima
         *                            rb1[1] - Constante de proporcionalidade para a velocidade linear
         *                            rb1[2] - Velocidade Angular máxima
         *                            rb1[3] - Constante de proporcionalidade para a velocidade angular
         *
         *            2)double *rb2 - ponteiro para um vetor do tipo double de tamanho 4 de forma que
         *                            possuam valores referentes a características do robô 2
         *                            na respectiva ordem:
         *                            rb2[0] - Velocidade linear máxima
         *                            rb2[1] - Constante de proporcionalidade para a velocidade linear
         *                            rb2[2] - Velocidade Angular máxima
         *                            rb2[3] - Constante de proporcionalidade para a velocidade angular
         *
         *            3)double *rb3 - ponteiro para um vetor do tipo double de tamanho 4 de forma que
         *                            possuam valores referentes a características do robô 3
         *                            na respectiva ordem:
         *                            rb3[0] - Velocidade linear máxima
         *                            rb3[1] - Constante de proporcionalidade para a velocidade linear
         *                            rb3[2] - Velocidade Angular máxima
         *                            rb3[3] - Constante de proporcionalidade para a velocidade angular
         *
         *            4)int *zona1 - ponteiro para um vetor de tamanho 2 do tipo int, referente aos
         *                           valores de zona morta dos motores do robô 1 de forma que :
         *                           zona1[0] - Zona morta do motor direito
         *                           zona1[1] - Zona morta do motor esquerdo
         *
         *            5)int *zona2 - ponteiro para um vetor de tamanho 2 do tipo int, referente aos
         *                           valores de zona morta dos motores do robô 2 de forma que :
         *                           zona2[0] - Zona morta do motor direito
         *                           zona2[1] - Zona morta do motor esquerdo
         *
         *            6)int *zona3 - ponteiro para um vetor de tamanho 2 do tipo int, referente aos
         *                           valores de zona morta dos motores do robô 3 de forma que :
         *                           zona3[0] - Zona morta do motor direito
         *                           zona3[1] - Zona morta do motor esquerdo
         *
         *       7)String filename - Nome do arquivo onde os dados serão guardados.
         *
         *
         * Retorno:
         *        Nenhum.
         *
         */
        void WriteConfigurationsRobots(double*, double*, double*, int*, int*, int*, String);

	private:

        /*
         * Método:GetAndSetConfigurationsCamera(VideoCapture);
         *
         * Descrição: Responsável por extrair de um arquivo todas as informações
         *            referente à câmera controlada pelo sistema. Após a extração
         *            esse método configura a câmera
         *
         * Parâmetros:
         *            1) VideoCapture cap - objeto do tipo VideoCapture referente
         *                                  à câmera controlada por esse sistema
         *
         * Retorno:
         *        Nenhum.
         *
        */
		void GetAndSetConfigurationsCamera(VideoCapture);

        /*
         * Método:GetVariaveisCampo();
         *
         * Descrição: Usa o nome do arquivo dito na instância do objeto configurations
         *            para extrair todas as informações referente às delimitações do campo.
         *            Após a extração das informações esse método às guarda nas variáveis
         *            da classe.
         *
         *
         * Parâmetros:
         *            Nenhum.
         * Retorno:
         *        Nenhum.
         *
        */
        void GetVariaveisCampo();

        FileStorage fs, fs2;
};

#endif
