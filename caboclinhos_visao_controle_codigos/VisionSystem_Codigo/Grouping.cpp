
#include"Grouping.h"

 bool cmp_pontos(vector<Point>a,vector<Point>b)
{
    return a.size()>b.size();
}
 bool myfunction (int i,int j)
{
    return (i>j);
 }

Grouping::Grouping(int qtd_group,int classification)
{
    classifier = classification;
    number = qtd_group;
}
vector<pair<Point,int> > Grouping::Grouping_Result(Mat *binary_image)
{
    vector<pair<Point,int> >resultado;
    if(classifier == 0)
    {
        Classification_FindContours(binary_image);
        for(int i=0;i<pontos.size();i++)
        {
            resultado.push_back(make_pair(pontos[i],contours[i].size()));
        }
    }
    if(classifier == 1)
    {
        Classification_kmeans(binary_image);
        for(int i=0;i<pontos.size();i++)
        {
            resultado.push_back(make_pair(pontos[i],qtd_kmeans[i]));
        }
    }

    return resultado;
}

void Grouping::Classification_FindContours(Mat *segmentacao)
{


    vector<Point>aux = pontos;
    pontos.clear();
    findContours(*segmentacao,contours,hierarchy,CV_RETR_LIST,CV_CHAIN_APPROX_NONE);
    int soma_x=0;
    int soma_y=0;
    sort(contours.begin(),contours.end(),cmp_pontos);
    int qtd_contornos = number;

    if(number>(int)contours.size())
           qtd_contornos = contours.size();

       int aux_maior=0;
       int aux_id;
       int aux_topo=10000;
       vector<int>id_contours;
       for(int i=0;i<3;i++)
       {
           for(int j=0;j<(int)contours.size();j++)
           {
               if((int)contours[j].size()>30 && (int)contours[j].size()<aux_topo)
                   if((int)contours[j].size()>aux_maior)
                   {
                       aux_maior=contours[j].size();
                       aux_id = j;
                   }
               if(j==(int)contours.size()-1)
               {
                 if(aux_maior != 0)
                 {
                   aux_topo=aux_maior;
                   aux_maior=0;
                   id_contours.push_back(aux_id);
                 }
               }

           }
       }



        for(int i = 0; i < qtd_contornos; i++)
        {

                 for(int j=0;j<(int)contours[i].size();j++)
                 {
                     soma_x+=contours[i][j].x;
                     soma_y+=contours[i][j].y;
                 }
                 pontos.push_back(Point(soma_x/contours[i].size(),soma_y/contours[i].size()));

                 soma_x=0;
                 soma_y=0;



        }


        hierarchy.clear();
        contours.clear();

      if(pontos.size()==0)
          pontos=aux;
      aux.clear();



}
void Grouping::Classification_kmeans(Mat *segmentacao)
{

                vector<Point>aux = pontos;
                pontos.clear();

                int clusterCount = number;// QUANTOS TEM DE VERDADE + 1
                int centro_inicial = clusterCount;
                Mat labels;
                int attempts = 1;
                Mat centers;
                int incremento_centro = 1;



                Mat nonZeroCoordinates;
                findNonZero(*segmentacao, nonZeroCoordinates);
                nonZeroCoordinates.convertTo(nonZeroCoordinates, CV_32F);

          if(nonZeroCoordinates.rows > number){
                // INICIALIZA O KMEANS SEMPRE PROCURANDO APENAS UM CENTRO
                kmeans(nonZeroCoordinates, incremento_centro, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,5, 0.001), attempts, KMEANS_RANDOM_CENTERS, centers);


                // TESTE DE VERIFICAÇÃO DA DISTÂNCIA DOS PONTOS DE UM GRUPO PARA O CENTRO DESTE MESMO GRUPO
                int limiar = 20;
                int distancia = 100;
                int parada = 0;

                while(distancia>limiar){
                    parada++;
                    for (int i = 0; i < nonZeroCoordinates.rows ; i++ ){
                        distancia = sqrt(pow(nonZeroCoordinates.at<float>(i,0) - centers.at<float>(labels.at<int>(i,0),0),2) + pow(nonZeroCoordinates.at<float>(i,1) - centers.at<float>(labels.at<int>(i,0),1),2));

                        if(distancia>limiar){
                            incremento_centro = incremento_centro + 1;

                            kmeans(nonZeroCoordinates , incremento_centro, labels, TermCriteria(CV_TERMCRIT_ITER|CV_TERMCRIT_EPS,5, 0.001), attempts, KMEANS_RANDOM_CENTERS, centers);

                            break;
                        }
                    }
                    if(parada == 5)
                        break;
                }

               vector<double> quantidade_pontos;

                   // SE A QUANTIDADE DE AGRUPAMENTOS FOR MAIOR DO QUE A PEDIDA INICIALMENTE

                        for (int i = 0; i < incremento_centro  ; i++ ){
                            quantidade_pontos.push_back(0);
                            for (int j = 0; j < labels.rows ; j++ ){
                                if(labels.at<int>(j,0) == i ){
                                    quantidade_pontos[i] = quantidade_pontos[i] +1;
                                }
                            }
                        }


            if(centro_inicial <= incremento_centro){
                       vector<double> v2;
                       v2 = quantidade_pontos;
                       sort(quantidade_pontos.begin(), quantidade_pontos.end(), myfunction );
                       vector<cv::Point2f> centros;
                        for (int i = 0; i < centro_inicial ; i++ ){
                            for (int j = 0; j < incremento_centro ; j++ ){
                                 if(quantidade_pontos.size() >0){
                                    if(quantidade_pontos[i] ==v2[j]){
                                        qtd_kmeans.push_back((int)quantidade_pontos[i]);
                                        pontos.push_back(cv::Point(centers.at<float>(j, 0),centers.at<float>(j, 1)));
                                    }
                                 }else{
                                     qtd_kmeans.push_back((int)quantidade_pontos[i]);
                                     pontos.push_back(cv::Point(centers.at<float>(j, 0),centers.at<float>(j, 1)));
                                 }
                            }
                        }

            }else{
                for(int i=0; i<centro_inicial;i++){
                    if(i<incremento_centro){
                        qtd_kmeans.push_back((int)quantidade_pontos[i]);
                        pontos.push_back(cv::Point(centers.at<float>(i, 0),centers.at<float>(i, 1)));
                    }else{
                        pontos.push_back(Point(-1,-1));
                        qtd_kmeans.push_back(0);
                    }
                }

            }
          }

          if(pontos.size()==0)
                  pontos=aux;
              aux.clear();



}
