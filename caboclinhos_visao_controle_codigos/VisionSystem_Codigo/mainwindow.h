//-------------------------------------------------------------------------
/*
 * Arquivo: mainwindow.h
 *
 * Sistema:  VisionSystem
 * Nome do Componente: MainWindow
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
 * Descrição:    Esse arquivo contém a definição da classe MainWindows
 *               que corresponde à janela principal do programa e tem
 *               a função de instanciar e juntar todos os módulos descritos
 *               para esse programa.
 *
 *
 *
*/
//-----------------------------------------------------------------------
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTimer>
#include <QImage>
#include <QFileDialog>
#include <iostream>
#include "opencv2/opencv.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <string>
#include <time.h>
#include <vector>

#include "Configurations.h"
#include "Robot.h"
#include "Build_Robot.h"
#include "Segmentation.h"
#include "Grouping.h"
#include "Ball.h"
#include "controlador.h"
#include "serialcomm.h"

#include "constantes_robot.h"
#include <omp.h>
#include "strategy.h"

// incluido por lucas - INICIO
#include <math.h>
#include <cstdlib>
#include <stdlib.h>
#include <stdio.h>
#include <Windows.h>
#include <assert.h>
#include <commctrl.h>
#include "serialcomm.h"
#include "comandos.h"



namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    int classificador; //0-Find Contours...//1- Kameans
    QTimer *cronometro;
    Configurations *set;
    VideoCapture cap;
    Mat input;
    double dist;
    string filename = "Settings.xml";

    vector<Point>azul_pt;       // Vetor de coordenadas(x,y) da posição do centro dos corpos azuis.
    vector<Point>vermelho_pt;   // Vetor de coordenadas(x,y) da posição do centro dos corpos vermelho.
    vector<Point>amarelo_pt;    // Vetor de coordenadas(x,y) da posição do centro dos corpos amarelo.
    vector<Point>laranja_pt;    // Vetor de coordenadas(x,y) da posição do centro dos corpos laranja.
    vector<Point>Magenta_pt;    // Vetor de coordenadas(x,y) da posição do centro dos corpos Magenta.
    vector<Point>Green_pt;      // Vetor de coordenadas(x,y) da posição do centro dos corpos verde.

    Scalar Blue[2];             // vetor com o intervalo de limiares para a cor azul. Blue[0]-limiar minimo Blue[1]-limiar máximo
    Scalar Red[2];              // vetor com o intervalo de limiares para a cor vermelho. Red[0]-limiar minimo Red[1]-limiar máximo
    Scalar Yellow[2];           // vetor com o intervalo de limiares para a cor amarelo. yellow[0]-limiar minimo yellow[1]-limiar máximo
    Scalar Orange[2];           // vetor com o intervalo de limiares para a cor laranja. orange[0]-limiar minimo orange[1]-limiar máximo
    Scalar Mg[2];               // vetor com o intervalo de limiares para a cor magenta. Mg[0]-limiar minimo Mg[1]-limiar máximo
    Scalar Green[2];            // vetor com o intervalo de limiares para a cor verde. Green[0]-limiar minimo Green[1]-limiar máximo

    Mat Mascaras[2];            //vetor com as mascaras usadas para operações de abertura e fechamento.
    Rect roi;                   // retângulo usado para fazer a retirada da imagem do campo

    Segmentation *azul;         // Objeto responsável pela segmentação dos corpos de cor azul
    Segmentation *amarelo;      // Objeto responsável pela segmentação dos corpos de cor amarelo
    Segmentation *vermelho;     // Objeto responsável pela segmentação dos corpos de cor vermelo
    Segmentation *verde;        // Objeto responsável pela segmentação dos corpos de cor verde
    Segmentation *magenta;      // Objeto responsável pela segmentação dos corpos de cor magenta
    Segmentation *laranja;      // Objeto responsável pela segmentação dos corpos de cor laranja

    Grouping *azul_group;       // Objeto responsável por identificar o centro de massa dos corpos de cor azul
    Grouping *amarelo_group;    // Objeto responsável por identificar o centro de massa dos corpos de cor amarelo
    Grouping *verde_group;      // Objeto responsável por identificar o centro de massa dos corpos de cor verde
    Grouping *vermelho_group;   // Objeto responsável por identificar o centro de massa dos corpos de cor vermelho
    Grouping *magenta_group;    // Objeto responsável por identificar o centro de massa dos corpos de cor magenta
    Grouping *laranja_group;    // Objeto responsável por identificar o centro de massa dos corpos de cor laranja

    Constantes_robot *con;      // Objeto responsável pelas contantes características de cada robô
    Strategy *Cerebro;          // Objeto responsável pelos comportamentos e coordenação dos robôs
    int comando;
    int comando_atacante;
    int comando_zagueiro;
    int comando_goleiro;

    Build_Robot *Machine_of_Robots; // Objeto responsável por evitar ambiguidades durante colisões ou junção de robôs
    Ball Bola;                  // Objeto responsável por guardar as coordenadas(x,y) da posição da bola

    clock_t end,start;
    vector<Robot> robos;        // Objeto responsável por guardar todas informações necessárias sobre cada robô
    QImage image;

    Robot rb1;
    Robot rb2;
    Robot rb3;

    int time; //0 - TIME AZUL, 1- TIME AMARELO
    int contador;
    Point pos_bola[2];
    int aux;

private slots:

    /*
     * Método:Refresh_position_robots();
     *
     * Descrição: Metodo responsável por fazer a captura e todo o processamento
     *            da imagem do campo.
     * Parâmetro:
     *           Nenhum.
     * Retorno:
     *       Nenhum.
    */
     void Refresh_position_robots();

     void on_actionKmeans_triggered();

     /*
      * Método:on_select_azul_triggered();
      *
      * Descrição: Método responsável por selecionar a cor do time para azul
      *
      * Parâmetro:
      *           Nenhum.
      * Retorno:
      *       Nenhum.
     */
     void on_select_azul_triggered();

     /*
      * Método:on_select_amarelo_triggered();
      *
      * Descrição: Método responsável por selecionar a cor do time para amarelo
      *
      * Parâmetro:
      *           Nenhum.
      * Retorno:
      *       Nenhum.
     */
     void on_select_amarelo_triggered();

     void on_actionComandos_triggered();

     /*
      * Método:on_pushButton_clicked();
      *
      * Descrição: Método responsável por setar a estrategia e comportamentos para os robôs
      *            que foram selecionados pelo usuário.
      *
      * Parâmetro:
      *           Nenhum.
      * Retorno:
      *       Nenhum.
     */
     void on_pushButton_clicked();


     /*
      * Método:on_pushButton_2_clicked();

      *
      * Descrição: Método responsável por para todos os robôs
      *
      * Parâmetro:
      *           Nenhum.
      * Retorno:
      *       Nenhum.
     */
     void on_pushButton_2_clicked();

     void on_comboBox_currentIndexChanged(int index);

     void on_comboBox_activated(int index);

     /*
      * Método:on_actionAbrir_Settings_triggered();
      *
      * Descrição: Método resposável por carregar dados de um determinado arquivo de texto
      *            Segue a lista de dados que são carregados:
      *            - Limiares
      *            - Configurações do campo
      *            - Configurações da camera
      *            - Constantes dos Robôs
      *
      * Parâmetro:
      *           Nenhum.
      * Retorno:
      *       Nenhum.
     */
     void on_actionAbrir_Settings_triggered();

signals:
     void Robos(Robot rb1,Robot rb2,Robot rb3);


};

#endif // MAINWINDOW_H
