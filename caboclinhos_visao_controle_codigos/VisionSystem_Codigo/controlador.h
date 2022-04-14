//-------------------------------------------------------------------------
/*
 * Arquivo: controlador.h
 *
 * Sistema:  VisionSystem
 * Nome do Componente: Controle
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
 * Descrição: Esse arquivo contém funções necessárias para o controle
 *            da movimentação do robô.
 *
*/
//-----------------------------------------------------------------------

#ifndef CONTROLADOR_H_
#define CONTROLADOR_H_

#include "Robot.h"


/*
* Objeto responsável por guardar o valor dos sinais ( de 0 a 254)
* que serão enviados às rodas dos robôs
*
*     VrD - sinal de velocidade para a roda direita
*     VrE - sinal de velocidade para a roda esquerda
*/
struct comandos
{
	unsigned char vrD, vrE, logica;
};
/*
 * Objeto responsável por guardar o valor de ângulo em radianos
 * do quando o robô precisa girar para ficar na mesma orientação
 * que um determinado ponto.
 *
 *    fi - valor do ângulo.
 *    flag - direção para com a qual o robô apontará, para flag = -1 o robô apontará com o fundo
 *           para flag = 1 o robô apontará com a frente.
*/
struct ang_err
{
	double fi;
	int flag;
};

    /*
     * Método:limita_velocidade(double, double);
     *
     * Descrição: Responsável por impedir que o sinal de velocidade ultrapasse um valor
     *            denominado valor de saturação. Caso a velocidade ultrapasse o valor de
     *            saturação então velocidade = valor de saturação.
     *
     * Parâmetros:
     *            1) double valor - valor referente à velocidade
     *
     *            2) double sat - valor de saturação
     *
     * Retorno:
     *        retorna um variável do tipo double com o valor da velocidade
     *        limitado até o valor de saturação.
     *
    */
    double limita_velocidade(double, double);

    /*
     * Método: olhar(Robot, double, double)
     *
     * Descrição: Responsável por retornar o quanto o robô precisa girar
     *            para ficar na mesma orientação com um determinado ponto
     *
     * Parâmetros:
     *            1) Robot rb - Objeto robot com todas as informações sobre
     *                          um determinado robô, coordenadas de posição
     *                          orientação e outras características.
     *
     *            2) double px - coordenada x do ponto para o qual o robô
     *                           irá virar.
     *
     *            3) double py - coordenada y do ponto para o qual o robô
     *                           irá virar
     *
     * Retorno:
     *        retorna um objeto do tipo ang_err que informa o módulo do ângulo
     *        e sentido com o qual o robô precisa virar para ficar na mesma
     *        orientação que um determinado ponto.
     *
    */
    ang_err olhar(Robot, double, double);

    /*
     * Método:  controle_angular(Robot rb,double);
     *
     * Descrição: Responsável por gerar um valor de velocidade angular
     *            entre -1 e 1 para o robô girar sobre um determinado
     *            ângulo
     *
     * Parâmetros:
     *            1) Robot rb - Objeto robot com todas as informações sobre
     *                          um determinado robô, coordenadas de posição
     *                          orientação e outras característica.
     *
     *            2) double fi - angulo correspondente ao quanto o robô irá
     *                           girar.
     *
     * Retorno:
     *       retorna um valor de velocidade angular entre -1 e 1
     *
     */
    double controle_angular(Robot rb,double);
    double controle_angular_goleiro(double);

    /*
     * Método:  controle_linear(Robot, double, double);
     *
     * Descrição: Responsável por gerar um valor de velocidade linear
     *            entre -1 e 1 para o robô andar até determinado ponto
     *
     *
     * Parâmetros:
     *            1) Robot rb - Objeto robot com todas as informações sobre
     *                          um determinado robô, coordenadas de posição
     *                          orientação e outras característica.
     *
     *            2) double px - coordenada x do ponto para o qual o robô
     *                           irá andar.
     *
     *            3) double py - coordenada y do ponto para o qual o robô
     *                           irá andar.
     *
     * Retorno:
     *       retorna um valor de velocidade linear entre -1 e 1
     *
     */
    double controle_linear(Robot, double, double);
    double controle_linear_goleiro(Robot, double, double);

    /*
     * Método:  gera_comandos_vr(Robot, double, double);
     *
     * Descrição: Responsável por converter os valores de velocidade angular
     *            e linear em sinais de velocidade para a roda direita e
     *            esquerda do robô.
     *
     *
     * Parâmetros:
     *            1) Robot rb - Objeto robot com todas as informações sobre
     *                          um determinado robô, coordenadas de posição
     *                          orientação e outras característica.
     *
     *            2) double V - Valor de velocidade linear
     *
     *            3) double W - Valor de velocidade angular
     *
     * Retorno:
     *        Retorna um objeto do tipo comando que guarda os valores dos sinais de
     *        velocidade para roda direita e para roda esquerda, esses valores vão de
     *        0 à 254
     *
     */
    comandos gera_comandos_vr(Robot, double, double);

    /*
     * Método:  distancia(Robot, double, double);
     *
     * Descrição: Calcula a distância euclidiana entre o centro do robô
     *            e um determinado ponto.
     *
     *
     * Parâmetros:
     *            1) Robot rb - Objeto robot com todas as informações sobre
     *                          um determinado robô, coordenadas de posição
     *                          orientação e outras caracteristica.
     *
     *            2) double px - Coordenada x de um determinado ponto
     *
     *            3) double py - Coordenada y de um determinado ponto
     *
     * Retorno:
     *        Retorna uma variável do tipo double com o valor da distância euclidiana
     *        entre o robô e o ponto informado.
     *
     */
    double distancia(Robot, double, double);


#endif /* CONTROLADOR_H_ */
