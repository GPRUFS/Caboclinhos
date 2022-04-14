//-------------------------------------------------------------------------
/*
 * Arquivo: constantes_robot.h
 *
 * Sistema:  VisionSystem
 * Nome do Componente: Constantes_robot
 * Linguagem C++
 *
 * (c) Copyright GPRUFS 2015
 * Endereço:
 *    UFS
 *
 * Autor: GPRUFS
 * E-Mail:
 *
 * Descrição:  Esse arquivo contém a definição da classe Constantes_robot
 *             que tem o papel de comandar a interface para a atualização
 *             de informações caracteristicas dos robôs, como:
 *
 *             - Zona morta
 *             - Velocidade linear máxima
 *             - Constante de proporcionalidade para a velocidade linear
 *             - Velocidade angular máxima
 *             - Constante de proporcionalidade para a velocidade angular
 *
*/
//-----------------------------------------------------------------------
#ifndef CONSTANTES_ROBOT_H
#define CONSTANTES_ROBOT_H

#include <QWidget>
#include <String>
#include <QString>
#include <iostream>

using namespace std;

namespace Ui {
class Constantes_robot;
}

class Constantes_robot : public QWidget
{
    Q_OBJECT

public:
    explicit Constantes_robot(QWidget *parent = 0);
    ~Constantes_robot();



    int zona_morta_rb1[2];       //Zona morta referente ao Robô 1
                                 //zona_morta_rb1[0] - Zona morta do motor direito
                                 //zona_morta_rb1[1] - Zona morta do motor esquerdo


    int zona_morta_rb2[2];       //Zona morta referente ao Robô 2
                                 //zona_morta_rb2[0] - Zona morta do motor direito
                                 //zona_morta_rb2[1] - Zona morta do motor esquerdo

    int zona_morta_rb3[2];       //Zona morta referente ao Robô 3
                                 //zona_morta_rb3[0] - Zona morta do motor direito
                                 //zona_morta_rb3[1] - Zona morta do motor esquerdo

    double constantes_rb1[4];    //Constantes Referente ao Robô 1
                                 //constantes_rb1[0] - Velocidade linear máxima
                                 //constantes_rb1[1] - Constante de proporcionalidade para a velocidade linear
                                 //constantes_rb1[2] - Velocidade Angular máxima
                                 //constantes_rb1[3] - Constante de proporcionalidade para a velocidade angular

    double constantes_rb2[4];    //Constantes Referente ao Robô 2
                                 //constantes_rb2[0] - Velocidade linear máxima
                                 //constantes_rb2[1] - Constante de proporcionalidade para a velocidade linear
                                 //constantes_rb2[2] - Velocidade Angular máxima
                                 //constantes_rb2[3] - Constante de proporcionalidade para a velocidade angular

    double constantes_rb3[4];    //Constantes Referente ao Robô 3
                                 //constantes_rb3[0] - Velocidade linear máxima
                                 //constantes_rb3[1] - Constante de proporcionalidade para a velocidade linear
                                 //constantes_rb3[2] - Velocidade Angular máxima
                                 //constantes_rb3[3] - Constante de proporcionalidade para a velocidade angular



    /*
     * Método:setar_constantes(double rb1[],int zona1[], double rb2[],int zona2[],double rb3[],int zona3[])
     *
     * Descrição: Responsável por atribuir na tela de interface valores atualizados
     *            das informações dos robôs
     *
     *
     * Parâmetros:
     *           1)double rb1[] - vetor do tipo double de tamanho 4 de forma que possuam valores
     *                            referentes a características do robô 1 na respectiva ordem:
     *
     *                            rb1[0] - Velocidade linear máxima
     *                            rb1[1] - Constante de proporcionalidade para a velocidade linear
     *                            rb1[2] - Velocidade Angular máxima
     *                            rb1[3] - Constante de proporcionalidade para a velocidade angular
     *
     *           2)double rb2[] - vetor do tipo double de tamanho 4 de forma que possuam valores
     *                            referentes a características do robô 2 na respectiva ordem:
     *
     *                            rb2[0] - Velocidade linear máxima
     *                            rb2[1] - Constante de proporcionalidade para a velocidade linear
     *                            rb2[2] - Velocidade Angular máxima
     *                            rb2[3] - Constante de proporcionalidade para a velocidade angular
     *
     *           3)double rb3[] - vetor do tipo double de tamanho 4 de forma que possuam valores
     *                            referentes a características do robô 3 na respectiva ordem:
     *
     *                            rb3[0] - Velocidade linear máxima
     *                            rb3[1] - Constante de proporcionalidade para a velocidade linear
     *                            rb3[2] - Velocidade Angular máxima
     *                            rb3[3] - Constante de proporcionalidade para a velocidade angular
     *
     *            4)int zona1[] - vetor de tamanho 2 do tipo int, referente aos valores de zona morta
     *                            dos motores do robô 1 de forma que :
     *
     *                           zona1[0] - Zona morta do motor direito
     *                           zona1[1] - Zona morta do motor esquerdo
     *
     *           5)int zona2[] - vetor de tamanho 2 do tipo int, referente aos valores de zona morta
     *                           dos motores do robô 2 de forma que :
     *
     *                           zona2[0] - Zona morta do motor direito
     *                           zona2[1] - Zona morta do motor esquerdo
     *
     *           6)int zona3[] - vetor de tamanho 2 do tipo int, referente aos valores de zona morta
     *                           dos motores do robô 3 de forma que :
     *
     *                           zona3[0] - Zona morta do motor direito
     *                           zona3[1] - Zona morta do motor esquerdo
     *
     *
     *
     * Retorno:
     *        Nenhum.
     *
    */
    void setar_constantes(double rb1[],int zona1[], double rb2[],int zona2[],double rb3[],int zona3[]);

private slots:

    /*
     * Método:on_pushButton_clicked();
     *
     * Descrição: Responsável por salvar nas variáveis da classe os
     *            valores que estão na interface.Esse método é chamado
     *            quando o botão 'salvar' é pressionado
     *
     *
     * Parâmetros:
     *           Nenhum.
     *
     * Retorno:
     *        Nenhum.
     *
    */
    void on_pushButton_clicked();

private:
    Ui::Constantes_robot *ui;
};

#endif // CONSTANTES_ROBOT_H
