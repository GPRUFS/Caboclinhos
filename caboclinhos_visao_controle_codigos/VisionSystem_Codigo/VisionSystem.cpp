#include "Configurations.h"
#include "Robot.h"
#include "Build_Robot.h"
#include "Segmentation.h"
#include "Grouping.h"
#include "Ball.h"
#include "controlador.h"
#include "serialcomm.h"
#include "estrategia.h"
#include <omp.h>

// incluido por lucas - FIM

using namespace std;
using namespace cv;

int main()
{


	/////////////////////////////////// comunicação serial ///////////////////////////////
	int val = inicia_comunicacao_serial();
	if (val == 0) // se a porta não estiver disponível encerre o programa
	{
		Sleep(2000);
		return(0);
	}
	/////////////////////////////////// comunicação serial ///////////////////////////////


	VideoCapture cap(0);
	Mat input;
    clock_t end,start;

    String filename = "Settings.xml";
    Configurations set(cap, filename);

    Rect roi = set.GetCutFramePoints();

    Mat Mascaras[2];
    set.GetConfigurationsElement(Mascaras);


    Scalar Blue[2];
    Scalar Red[2];
    Scalar Yellow[2];
    Scalar Orange[2];
    Scalar Mg[2];
    Scalar Green[2];



    // PEGAR LIMIARES DO ARQUIVO
    set.GetThresholdColor(Blue, "Blue");
    set.GetThresholdColor(Red, "Red");
    set.GetThresholdColor(Yellow, "Yellow");
    set.GetThresholdColor(Orange, "Orange");
    set.GetThresholdColor(Mg,"Magenta");
    set.GetThresholdColor(Green,"Green");

    // CONFIGURAR SEGMENTACAO
    Segmentation azul(Blue[0],Blue[1],Mascaras);
    Segmentation amarelo(Yellow[0],Yellow[1],Mascaras);
    Segmentation vermelho(Red[0],Red[1],Mascaras);
    Segmentation verde(Green[0],Green[1],Mascaras);
    Segmentation magenta(Mg[0],Mg[1],Mascaras);
    Segmentation laranja(Orange[0],Orange[1],Mascaras);

    // CONFIGURAR AGRUPAMENTO
    Grouping azul_group(3,0);
    Grouping amarelo_group(3,0);
    Grouping verde_group(2,0);
    Grouping vermelho_group(2,0);
    Grouping magenta_group(2,0);
    Grouping laranja_group(1,0);

    //CONFIGURAR FABRICAO DE ROBOS
    Build_Robot Machine_of_Robots(3);
    Ball Bola;

    Machine_of_Robots.Record_Position(true);
    Bola.Record_Position(true);

   	cap >> input;
   	cap >> input;
   	cap >> input;

   	vector<Robot> robos;


   	while(1)
    {
   		if(!cap.isOpened())
   		{
   			cout<<" Camera não pode ser aberta"<<endl;
   			Sleep(2000);
   			return 0;
   		}

   		start = clock();

     	if(!cap.read(input))
     	{
     		cout<<"Não foi possivel capturar um frame"<<endl;
     		Sleep(2000);
     		return 0;
     	}
     	input = input(roi);

        // IMAGEM BINARIA DAS SEGMENTACOES DAS CORES
       
        Mat *binary_img_azul;
        Mat *binary_img_amarelo;
        Mat *binary_img_verde;
        Mat *binary_img_vermelho;
        Mat *binary_img_magenta;
        Mat *binary_img_laranja;

        vector<pair<Point,int> > center_camisa_time;
        vector<pair<Point,int> > center_camisa_adversario;
        vector<pair<Point,int> > centers_id_camisa[3];

		#pragma omp parallel sections
		{
			#pragma omp section
			{
				binary_img_azul= azul.Segmentation_Result(&input);
			    center_camisa_time = azul_group.Grouping_Result(binary_img_azul);
				//printf ("id = %d, \n", omp_get_thread_num());
			}

			#pragma omp section
			{
				binary_img_amarelo = amarelo.Segmentation_Result(&input);
			    center_camisa_adversario = amarelo_group.Grouping_Result(binary_img_amarelo);

			}
			#pragma omp section
			{
				binary_img_vermelho = vermelho.Segmentation_Result(&input);
			    centers_id_camisa[0] = vermelho_group.Grouping_Result(binary_img_vermelho);


			}
			#pragma omp section
			{
				binary_img_verde = verde.Segmentation_Result(&input);
			    centers_id_camisa[1] = verde_group.Grouping_Result(binary_img_verde);

			}
			#pragma omp section
			{
				binary_img_magenta = magenta.Segmentation_Result(&input);
				centers_id_camisa[2]= magenta_group.Grouping_Result(binary_img_magenta);

			}
			#pragma omp section
			{
				binary_img_laranja = laranja.Segmentation_Result(&input);
				 if(laranja_group.Grouping_Result(binary_img_laranja).size()>0)
						          Bola.Refresh_Position(laranja_group.Grouping_Result(binary_img_laranja)[0].first);

			}


		}
        // RETORNO DOS CENTROS E QUANTIDADE DE PIXEL VINCULADO A CADA CENTRO ... FEITO PELO AGRUPAMENTO
        // O RETORNO É UM VETOR DE PARES ONDE ... "vetor[i].first é o ponto do centro e vetor[i].second é a quantidade de contorno ou pixel vinculado a aquele centro"

        // POS PROCESSAMENTO PARA FORMACAO DE ROBOS...USO DO CASAMENTO...
        Machine_of_Robots.Get_Centers(center_camisa_time,centers_id_camisa,center_camisa_adversario);

        // RETORNO DOS ROBOS JA FORMADOS
        robos = Machine_of_Robots.Get_robos();


       	robos[0].zonamorta_d = 35;
       	robos[0].zonamorta_e = 35;
       	robos[1].zonamorta_d = 35;
       	robos[1].zonamorta_e = 35;
       	robos[2].zonamorta_d = 35;
       	robos[2].zonamorta_e = 35;

        circle(input,robos[0].get_center_robot(),15, Scalar(0,255,255),1,5,0);
        circle(input,robos[1].get_center_robot(),15, Scalar(0,255,255),1,5,0);
        circle(input,robos[2].get_center_robot(),15, Scalar(0,255,255),1,5,0);
        circle(input,Point(Bola.x,Bola.y),6, Scalar(0,255,255),1,5,0);
        
        

        imshow("winName", input);
        input.release();


        // ESTRATÉGIA
        estrategia1(robos, Bola);

        end = clock();
        double aux = 1000*(end-start)/CLOCKS_PER_SEC;
        cout<< "tempo gasto "<<aux<<" ms\n\n";

        char c ='a';
         c = cvWaitKey(1);
        if(c == 27)
        {
        	break;
        }
        /*while(c != 'p')
        {
        	 c = cvWaitKey(33);
        	Sleep(1);
        }*/

    }
   	/////////////////////////////////// comunicação serial ///////////////////////////////
   	encerra_comunicacao_serial();
   	/////////////////////////////////// comunicação serial ///////////////////////////////
    return 0;
}
