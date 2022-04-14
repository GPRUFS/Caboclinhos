#include "Build_Robot.h"

Build_Robot::Build_Robot(int numero_robos)
{
	number_robots = numero_robos;
	gravar_arquivo = false;
    tamanho = 25;

    rb1_linha[0] = Point(0,0);
    rb1_linha[1] = Point(0,0);

    rb2_linha[0] = Point(0,0);
    rb2_linha[1] = Point(0,0);

    rb3_linha[0] = Point(0,0);
    rb3_linha[1] = Point(0,0);
}
void Build_Robot::Change_dist_cores(int i)
{
    tamanho = i;
}
void Build_Robot::Get_Centers(vector<pair<Point,int> >camisa_time,vector<pair<Point,int> >id_camisas[],vector<pair<Point,int> >camisa_adversario)
{
    vector<Point>camisa_marry;
    vector<Point>camisa_adversario_marry;

    for(int i=0;i<(int)camisa_time.size();i++)
    	camisa_marry.push_back(camisa_time[i].first);

    for(int i=0;i<(int)camisa_adversario.size();i++)
        	camisa_adversario_marry.push_back(camisa_adversario[i].first);


    Marriage(camisa_marry,id_camisas,camisa_adversario_marry);

}
void Build_Robot::Marriage(vector<Point>camisa_time,vector<pair<Point,int> >*id_camisa,vector<Point>camisa_adversario)
{
    int dist=0;
    vector<pair<int,Point> > combinacoes[camisa_time.size()];  // 0 - vermelho....1- verde....2- magenta (first)  .....second(indice_
    vector<int> ligacoes(camisa_time.size(),0);

			for(int i=0;i<(int)camisa_time.size();i++)
			{

			     for(int k=0;k<number_robots;k++)
					for(int j=0; j<(int)id_camisa[k].size();j++)
					{
						dist = abs(id_camisa[k][j].first.x-camisa_time[i].x)+ abs(id_camisa[k][j].first.y-camisa_time[i].y);
                        if(dist<=tamanho)
						{
							ligacoes[i]++;
							combinacoes[i].push_back(make_pair(k,id_camisa[k][j].first));
						}

			         }
			}



			bool continuar = true;
				   int flag = 0;

				   while(continuar)
				   {
					   for(int i=0;i<(int)camisa_time.size();i++)
						 for(int j=0;j<(int)camisa_time.size();j++)
						 {
							 if(i!=j && ligacoes[i]==1 && ligacoes[j]>1)
							 {
								 for(int k=0;k<ligacoes[j];k++)
								   if(combinacoes[i][0].first == combinacoes[j][k].first)
								   {
									   combinacoes[j].erase(combinacoes[j].begin()+k);
									   ligacoes[j]--;
									   flag =1;
								   }
							 }

						 }
					   if(flag == 1)
						   flag=0;
					   else
						   continuar = false;

		   }


		   continuar = true;
	flag = 0;
	while(continuar)
	{
	   for(int i=0;i<(int)camisa_time.size();i++)
	   {
	       if(ligacoes[i]>1)
	        {
				 for(int j=0;j<ligacoes[i];j++)
				 {
					 for(int k=0;k<(int)camisa_adversario.size();k++)
					 {
						 dist = abs(combinacoes[i][j].second.x-camisa_adversario[k].x)+ abs(combinacoes[i][j].second.y-camisa_adversario[k].y);
                         if(dist<=tamanho)
						 {
											 combinacoes[i].erase(combinacoes[i].begin()+j);
											 ligacoes[i]--;
											 flag=1;
										 }
									 }
								 }
							 }
							}
							if(flag == 1)
				   flag=0;
				 else
				   continuar = false;
			  }



			  for(int i=0;i<(int)camisa_time.size();i++)
			  {
				  if(ligacoes[i]>1)
				  {
					  Point id;
					  int id_cor;
					  int qtd_pt=0;
					  for(int j=0;j<ligacoes[i];j++)
					  {
							  int qtd_aux=0;
                              for(int k=0;k<(int)id_camisa[i].size();k++)
                              {
                            	    if(id_camisa[i][k].first.x == combinacoes[i][j].second.x && id_camisa[i][k].first.y == combinacoes[i][j].second.y)
                            	    	qtd_aux = id_camisa[i][k].second;
                              }

							  if(qtd_aux>qtd_pt)
							  {
								  id_cor = combinacoes[i][j].first;
								  id = combinacoes[i][j].second;
								  qtd_pt = qtd_aux;

							  }
					  }
						  combinacoes[i][0]=make_pair(id_cor,id);
						  ligacoes[i]=1;
					}

						if(ligacoes[i] == 1 && combinacoes[i][0].first == 0)
						{
							 rb1.Refresh_Position(camisa_time[i],combinacoes[i][0].second);
                             rb1_linha[0] = camisa_time[i];
                             rb1_linha[1] = combinacoes[i][0].second;
							 continue;

						}


						if(ligacoes[i] == 1 && combinacoes[i][0].first == 1)
						{
						 rb2.Refresh_Position(camisa_time[i],combinacoes[i][0].second);
                         rb2_linha[0] = camisa_time[i];
                         rb2_linha[1] = combinacoes[i][0].second;
						 continue;
						}


						if(ligacoes[i] == 1 && combinacoes[i][0].first == 2)
						{
						  rb3.Refresh_Position(camisa_time[i],combinacoes[i][0].second);
                          rb3_linha[0] = camisa_time[i];
                          rb3_linha[1] = combinacoes[i][0].second;
						  continue;
						}

						//CASO TENHA MAIS ROBOS....ACRESCENTAR AQUI
			    }



			if(gravar_arquivo == true)
			{

        				if(arquivo_rb1)  //ESCREVENDO X Y DO RB1
				          arquivo_rb1<<rb1.get_center_robot().x<<" "<<rb1.get_center_robot().y<<" "<<rb1.get_orientation()<<endl;

				        if(arquivo_rb2)
				           arquivo_rb2<<rb2.get_center_robot().x<<" "<<rb2.get_center_robot().y<<" "<<rb2.get_orientation()<<endl;

				        if(arquivo_rb3)
				           arquivo_rb3<<rb3.get_center_robot().x<<" "<<rb3.get_center_robot().y<<" "<<rb3.get_orientation()<<endl;

			}
}


vector<Robot>Build_Robot::Get_robos()
{
    vector<Robot>robos;
    robos.push_back(rb1);
    robos.push_back(rb2);
    robos.push_back(rb3);

   return robos;

}
void Build_Robot::Record_Position(bool p)
{
  gravar_arquivo = p;
  if(p == true)
  {
	   arquivo_rb1.open("Position_Robo1.txt");
	   arquivo_rb2.open("Position_Robo2.txt");
	   arquivo_rb3.open("Position_Robo3.txt");

		if(arquivo_rb2)
	   		arquivo_rb2<<"X "<<"Y "<<"THETA"<<endl;
	   	if(arquivo_rb3)
	   		arquivo_rb3<<"X "<<"Y "<<"THETA"<<endl;
	   	if(arquivo_rb1)
	   		arquivo_rb1<<"X "<<"Y "<<"THETA"<<endl;
  }
  if(p == false)
  {
	  if(arquivo_rb1)
		  arquivo_rb1.close();
	  if(arquivo_rb2)
	 		  arquivo_rb2.close();
	  if(arquivo_rb3)
	 		  arquivo_rb3.close();


  }
}
Build_Robot::~Build_Robot()
{
	arquivo_rb1.close();
	arquivo_rb2.close();
	arquivo_rb3.close();

}
