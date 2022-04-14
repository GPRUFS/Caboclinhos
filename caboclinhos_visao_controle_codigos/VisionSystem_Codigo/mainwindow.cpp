#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    cronometro = new QTimer(this);

    /////////////////////////////////// comunicação serial ///////////////////////////////
        int val = inicia_comunicacao_serial();
        if (val == 0) // se a porta não estiver disponível encerre o programa
            int reta = QMessageBox::warning(this, tr("Erro"), "Erro na porta serial!", QMessageBox::Close);

   /////////////////////////////////// comunicação serial ///////////////////////////////

    connect(cronometro,SIGNAL(timeout()),this,SLOT(Refresh_position_robots()));
    cronometro->start(25);
    con = new Constantes_robot();


    con->hide();

    comando = -2;
    comando_atacante = -1;
    comando_goleiro = -1;
    comando_zagueiro = -1;

    cap.open(0);
    set = new Configurations(cap,"Settings.xml");

    roi = set->GetCutFramePoints();
    set->ReadConfigurationsRobots("Constantes.xml");
    con->setar_constantes(set->rb1,set->zonamorta_rb1,set->rb2,set->zonamorta_rb2,set->rb3,set->zonamorta_rb3);

    set->GetConfigurationsElement(Mascaras);
    set->GetThresholdColor(Blue, "Blue");
    set->GetThresholdColor(Red, "Red");
    set->GetThresholdColor(Yellow, "Yellow");
    set->GetThresholdColor(Orange, "Orange");
    set->GetThresholdColor(Mg,"Magenta");
    set->GetThresholdColor(Green,"Green");

     azul= new Segmentation(Blue[0], Blue[1],Mascaras);
     vermelho = new Segmentation(Red[0], Red[1],Mascaras);
     amarelo = new Segmentation(Yellow[0], Yellow[1],Mascaras);
     laranja = new Segmentation(Orange[0], Orange[1],Mascaras);
     magenta = new Segmentation(Mg[0],Mg[1],Mascaras);
     verde = new Segmentation(Green[0],Green[1],Mascaras);

     azul_group = new Grouping(3,0);
     amarelo_group = new Grouping(3,0);
     verde_group =  new Grouping(2,0);
     vermelho_group = new Grouping (2,0);
     magenta_group = new Grouping(2,0);
     laranja_group = new Grouping (1,0);

     Machine_of_Robots = new Build_Robot(3);
     Machine_of_Robots->Record_Position(false);

     Machine_of_Robots->Change_dist_cores(25);//mudar aqui distancia entra a parte azul e a outra cor


     Cerebro = new Strategy();
     Cerebro->Setar_Campo(set);

     vector<string> nome;

     nome = Cerebro->Get_atacantes();

     for(int i=0;i<nome.size();i++)
     ui->combo_atacante->addItem(QString::fromStdString(nome[i]));

     nome = Cerebro->Get_goleiros();

     for(int i=0;i<nome.size();i++)
     ui->combo_goleiro->addItem(QString::fromStdString(nome[i]));

     nome = Cerebro->Get_zagueiros();

     for(int i=0;i<nome.size();i++)
     ui->combo_zagueiro->addItem(QString::fromStdString(nome[i]));

     nome = Cerebro->Get_Estrategias();

     for(int i=0;i<nome.size();i++)
     ui->comboBox->addItem(QString::fromStdString(nome[i]));
     ui->comboBox->setCurrentIndex(-1);
     ui->combo_goleiro->setCurrentIndex(-1);
     ui->combo_zagueiro->setCurrentIndex(-1);
     ui->combo_atacante->setCurrentIndex(-1);



     cap >> input;
     cap >> input;
     cap >> input;

     vector<Robot> robos;
     time = 0;
     pos_bola[0] = Point(-1,-1);
     pos_bola[1] = Point(-1,-1);
     contador = 1;

}

void MainWindow::Refresh_position_robots()
{
    if(!this->isVisible())
        con->close();

    contador++;
    if(!cap.isOpened())
    {
        int ret = QMessageBox::warning(this, tr("Error"), "Câmera não conectada", QMessageBox::Close);
        this->close();
    }

    start = clock();

    if(!cap.read(input))
    {
        int ret = QMessageBox::warning(this, tr("Error"), "Frame não pode ser aberto", QMessageBox::Close);
        this->close();
    }



    input = input(roi);


    // IMAGEM BINARIA DAS SEGMENTACOES DAS CORES

    Mat *binary_img_azul;
    Mat *binary_img_amarelo;
    Mat *binary_img_verde;
    Mat *binary_img_vermelho;
    Mat *binary_img_magenta;
    Mat *binary_img_laranja;

    vector<pair<Point,int> > center_camisa_azul;
    vector<pair<Point,int> > center_camisa_amarelo;
    vector<pair<Point,int> > centers_id_camisa[3];

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            binary_img_azul= azul->Segmentation_Result(&input);
            center_camisa_azul = azul_group->Grouping_Result(binary_img_azul);

        }

        #pragma omp section
        {
            binary_img_amarelo = amarelo->Segmentation_Result(&input);
            center_camisa_amarelo = amarelo_group->Grouping_Result(binary_img_amarelo);

        }
        #pragma omp section
        {
            binary_img_vermelho = vermelho->Segmentation_Result(&input);
            centers_id_camisa[0] = vermelho_group->Grouping_Result(binary_img_vermelho);


        }
        #pragma omp section
        {
            binary_img_verde = verde->Segmentation_Result(&input);
            centers_id_camisa[1] = verde_group->Grouping_Result(binary_img_verde);

        }
        #pragma omp section
        {
            binary_img_magenta = magenta->Segmentation_Result(&input);
            centers_id_camisa[2]= magenta_group->Grouping_Result(binary_img_magenta);

        }
        #pragma omp section
        {
            binary_img_laranja = laranja->Segmentation_Result(&input);
             if(laranja_group->Grouping_Result(binary_img_laranja).size()>0)
                              Bola.Refresh_Position(laranja_group->Grouping_Result(binary_img_laranja)[0].first);

        }


    }
    // RETORNO DOS CENTROS E QUANTIDADE DE PIXEL VINCULADO A CADA CENTRO ... FEITO PELO AGRUPAMENTO
    // O RETORNO É UM VETOR DE PARES ONDE ... "vetor[i].first é o ponto do centro e vetor[i].second é a quantidade de contorno ou pixel vinculado a aquele centro"

    // POS PROCESSAMENTO PARA FORMACAO DE ROBOS...USO DO CASAMENTO...
    vector<Point>adversario;
    if(time == 0){
          Machine_of_Robots->Get_Centers(center_camisa_azul,centers_id_camisa,center_camisa_amarelo);

          for(int i=0;i<center_camisa_amarelo.size();i++)
          {
            adversario.push_back(center_camisa_amarelo[i].first);
          }

        }
        else
          {
            Machine_of_Robots->Get_Centers(center_camisa_amarelo,centers_id_camisa,center_camisa_azul);

            for(int i=0;i<center_camisa_azul.size();i++)
            {
              adversario.push_back(center_camisa_azul[i].first);
            }
          }

    // RETORNO DOS ROBOS JA FORMADOS
    robos = Machine_of_Robots->Get_robos();


    robos[0].zonamorta_d = con->zona_morta_rb1[0];
    robos[0].zonamorta_e = con->zona_morta_rb1[1];

    robos[1].zonamorta_d = con->zona_morta_rb2[0];
    robos[1].zonamorta_e = con->zona_morta_rb2[1];

    robos[2].zonamorta_d = con->zona_morta_rb3[0];
    robos[2].zonamorta_e = con->zona_morta_rb3[1];

    robos[0].V_max = con->constantes_rb1[0];
    robos[0].k_lin = con->constantes_rb1[1];
    robos[0].W_max = con->constantes_rb1[2];
    robos[0].k_ang = con->constantes_rb1[3];

    robos[1].V_max = con->constantes_rb2[0];
    robos[1].k_lin = con->constantes_rb2[1];
    robos[1].W_max = con->constantes_rb2[2];
    robos[1].k_ang = con->constantes_rb2[3];

    robos[2].V_max = con->constantes_rb3[0];
    robos[2].k_lin = con->constantes_rb3[1];
    robos[2].W_max = con->constantes_rb3[2];
    robos[2].k_ang = con->constantes_rb3[3];

    circle(input,robos[0].get_center_robot(),15, Scalar(0,255,255),1,5,0);
    circle(input,robos[1].get_center_robot(),15, Scalar(0,255,255),1,5,0);
    circle(input,robos[2].get_center_robot(),15, Scalar(0,255,255),1,5,0);
    circle(input,Point(Bola.x,Bola.y),6, Scalar(0,255,255),1,5,0);

    line(input,Machine_of_Robots->rb1_linha[0],Machine_of_Robots->rb1_linha[1],Scalar(0,255,255),1);
    line(input,Machine_of_Robots->rb2_linha[0],Machine_of_Robots->rb2_linha[1],Scalar(0,255,255),1);
    line(input,Machine_of_Robots->rb3_linha[0],Machine_of_Robots->rb3_linha[1],Scalar(0,255,255),1);

    cvtColor(input, input, CV_BGR2RGB,3);

    image = QImage((uchar*) input.data, input.cols, input.rows,input.step, QImage::Format_RGB888);
    if(image.width() > 0 && image.height() > 0)
    {
        ui->janela->setFixedWidth(image.width());
        ui->janela->setFixedHeight(image.height());
    }
    ui->janela->setPixmap(QPixmap::fromImage(image));


    // ESTRATÉGIA
     pos_bola[0] = pos_bola[1];
     pos_bola[1] = Point(Bola.x,Bola.y);

      Cerebro->Setar_Variaveis_jogo(robos,Bola,adversario);

      Cerebro->Setar_Atacante(comando_atacante);
      Cerebro->Setar_Goleiro(comando_goleiro);
      Cerebro->Setar_Zagueiro(comando_zagueiro);

      Cerebro->Executar_estrategia(comando);

    if(comando == -2)
        parar(robos);

   // estrategia2(robos, Bola);

    contador++;

    delete binary_img_azul;
    delete binary_img_amarelo;
    delete binary_img_verde;
    delete binary_img_vermelho;
    delete binary_img_magenta;
    delete binary_img_laranja;

    binary_img_azul = 0;
    binary_img_amarelo = 0;
    binary_img_verde = 0;
    binary_img_vermelho = 0;
    binary_img_magenta = 0;
    binary_img_laranja = 0;

    end = clock();
    double aux = 1000*(end-start)/CLOCKS_PER_SEC;
    QString tempo = QString::number(aux);
    ui->milesegundos->setText(tempo);
}

MainWindow::~MainWindow()
{
    cap.release();
    /////////////////////////////////// comunicação serial ///////////////////////////////
        encerra_comunicacao_serial();
    /////////////////////////////////// comunicação serial ///////////////////////////////

        set->WriteConfigurationsRobots(con->constantes_rb1,con->constantes_rb2,con->constantes_rb3,con->zona_morta_rb1,con->zona_morta_rb2,con->zona_morta_rb3,"Constantes.xml");
        delete azul;
        delete amarelo;
        delete vermelho;
        delete verde;
        delete magenta;
        delete laranja;

        delete azul_group;
        delete amarelo_group;
        delete verde_group;
        delete vermelho_group;
        delete magenta_group;
        delete laranja_group;

        delete Machine_of_Robots;

        delete set;
        delete con;
        delete cronometro;

        input.release();



    delete ui;
}


void MainWindow::on_actionKmeans_triggered()
{
    con->show();
}




void MainWindow::on_select_azul_triggered()
{
    ui->select_azul->setChecked(true);
    ui->select_amarelo->setChecked(false);
    time = 0;
}

void MainWindow::on_select_amarelo_triggered()
{
    ui->select_azul->setChecked(false);
    ui->select_amarelo->setChecked(true);
    time = 1;
}

void MainWindow::on_actionComandos_triggered()
{

}

void MainWindow::on_pushButton_clicked()
{
    if(ui->comboBox->currentIndex() != -1)
      comando = ui->comboBox->currentIndex();

    if(ui->combo_atacante->currentIndex() != -1)
        comando_atacante = ui->combo_atacante->currentIndex();

    if(ui->combo_goleiro->currentIndex() != -1)
        comando_goleiro = ui->combo_goleiro->currentIndex();

    if(ui->combo_zagueiro->currentIndex()!= -1)
        comando_zagueiro = ui->combo_zagueiro->currentIndex();

}

void MainWindow::on_pushButton_2_clicked()
{
    comando = -2;
}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->combo_goleiro->setCurrentIndex(-1);
    ui->combo_zagueiro->setCurrentIndex(-1);
    ui->combo_atacante->setCurrentIndex(-1);
}

void MainWindow::on_comboBox_activated(int index)
{
    ui->combo_goleiro->setCurrentIndex(-1);
    ui->combo_zagueiro->setCurrentIndex(-1);
    ui->combo_atacante->setCurrentIndex(-1);
}

void MainWindow::on_actionAbrir_Settings_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this,tr("Abrir arquivo"),"C:", tr("All files (*.*);;XML (*.xml)"));
    if(!fileName.isNull())
    {
        filename = fileName.toStdString();
        set = new Configurations(cap,filename);

        set->GetThresholdColor(Blue, "Blue");
        set->GetThresholdColor(Red, "Red");
        set->GetThresholdColor(Yellow, "Yellow");
        set->GetThresholdColor(Orange, "Orange");
        set->GetThresholdColor(Mg,"Magenta");
        set->GetThresholdColor(Green,"Green");

        azul= new Segmentation(Blue[0], Blue[1],Mascaras);
        vermelho = new Segmentation(Red[0], Red[1],Mascaras);
        amarelo = new Segmentation(Yellow[0], Yellow[1],Mascaras);
        laranja = new Segmentation(Orange[0], Orange[1],Mascaras);
        magenta = new Segmentation(Mg[0],Mg[1],Mascaras);
        verde = new Segmentation(Green[0],Green[1],Mascaras);

        azul_group = new Grouping(3,0);
        amarelo_group = new Grouping(3,0);
        verde_group =  new Grouping(2,0);
        vermelho_group = new Grouping (2,0);
        magenta_group = new Grouping(2,0);
        laranja_group = new Grouping (1,0);

        Machine_of_Robots = new Build_Robot(3);
        Machine_of_Robots->Record_Position(false);
        Machine_of_Robots->Change_dist_cores(25);

        Cerebro = new Strategy();
        Cerebro->Setar_Campo(set);

    }
}
