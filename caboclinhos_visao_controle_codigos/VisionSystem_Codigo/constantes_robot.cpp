#include "constantes_robot.h"
#include "ui_constantes_robot.h"

Constantes_robot::Constantes_robot(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Constantes_robot)
{
    ui->setupUi(this);
    zona_morta_rb1[0] = 35;
    zona_morta_rb1[1] = 35;

    zona_morta_rb2[0] = 35;
    zona_morta_rb2[1] = 35;

   zona_morta_rb3[0] = 35;
   zona_morta_rb3[1] = 35;

   constantes_rb1[0] = 1; // vmax
   constantes_rb1[1] = 0.002; // klin
   constantes_rb1[2] = -1; // wmax
   constantes_rb1[3] = 0.1; // kang

   constantes_rb2[0] = 1; // vmax
   constantes_rb2[1] = 0.002; // klin
   constantes_rb2[2] = -1; // wmax
   constantes_rb2[3] = 0.1; // kang

   constantes_rb3[0] = 1; // vmax
   constantes_rb3[1] = 0.002; // klin
   constantes_rb3[2] = -1; // wmax
   constantes_rb3[3] = 0.1; // kang

   ui->rb1_vmax->setValue(1);
   ui->rb1_klin->setValue(0.002);
   ui->rb1_wmax->setValue(-1);
   ui->rb1_kang->setValue(0.1);

   ui->rb2_vmax->setValue(1);
   ui->rb2_klin->setValue(0.002);
   ui->rb2_wmax->setValue(-1);
   ui->rb2_kang->setValue(0.1);
   
   ui->rb3_vmax->setValue(1);
   ui->rb3_klin->setValue(0.002);
   ui->rb3_wmax->setValue(-1);
   ui->rb3_kang->setValue(0.1);
   
   
   ui->rb1_zd->setValue(35);
   ui->rb1_ze->setValue(35);

   ui->rb2_zd->setValue(35);
   ui->rb2_ze->setValue(35);

   ui->rb3_zd->setValue(35);
   ui->rb3_ze->setValue(35);
}

Constantes_robot::~Constantes_robot()
{
    delete ui;
}
void Constantes_robot::setar_constantes(double rb1[],int zona1[], double rb2[],int zona2[],double rb3[],int zona3[])
{
    for(int i =0;i<4;i++)
    {
        constantes_rb1[i] = rb1[i];
        constantes_rb2[i] = rb2[i];
        constantes_rb3[i] = rb3[i];
     }
    for(int i=0;i<2;i++)
    {
        zona_morta_rb1[i] = zona1[i];
        zona_morta_rb2[2] = zona2[i];
        zona_morta_rb3[2] = zona3[i];
    }

    ui->rb1_zd->setValue(zona_morta_rb1[0]);
    ui->rb1_ze->setValue(zona_morta_rb1[1]);

    ui->rb1_vmax->setValue(rb1[0]);
    ui->rb1_klin->setValue(rb1[1]);
    ui->rb1_wmax->setValue(rb1[2]);
    ui->rb1_kang->setValue(rb1[3]);

    ui->rb2_zd->setValue(zona_morta_rb2[0]);
    ui->rb2_ze->setValue(zona_morta_rb2[1]);

    ui->rb2_vmax->setValue(rb2[0]);
    ui->rb2_klin->setValue(rb2[1]);
    ui->rb2_wmax->setValue(rb2[2]);
    ui->rb2_kang->setValue(rb2[3]);

    ui->rb2_zd->setValue(zona_morta_rb2[0]);
    ui->rb2_ze->setValue(zona_morta_rb2[1]);

    ui->rb3_vmax->setValue(rb3[0]);
    ui->rb3_klin->setValue(rb3[1]);
    ui->rb3_wmax->setValue(rb3[2]);
    ui->rb3_kang->setValue(rb3[3]);

}
void Constantes_robot::on_pushButton_clicked()
{
     zona_morta_rb1[0] = ui->rb1_zd->value();
     zona_morta_rb1[1] = ui->rb1_ze->value();

     zona_morta_rb2[0] = ui->rb2_zd->value();
     zona_morta_rb2[1] = ui->rb2_ze->value();

     zona_morta_rb3[0] = ui->rb3_zd->value();
     zona_morta_rb3[1] = ui->rb3_ze->value();

     constantes_rb1[0] = ui->rb1_vmax->value(); // vmax
     constantes_rb1[1] = ui->rb1_klin->value(); // klin
     constantes_rb1[2] = ui->rb1_wmax->value(); // wmax
     constantes_rb1[3] = ui->rb1_kang->value(); // kang

     constantes_rb2[0] = ui->rb2_vmax->value(); // vmax
     constantes_rb2[1] = ui->rb2_klin->value(); // klin
     constantes_rb2[2] = ui->rb2_wmax->value(); // wmax
     constantes_rb2[3] = ui->rb2_kang->value(); // kang

     constantes_rb3[0] = ui->rb3_vmax->value(); // vmax
     constantes_rb3[1] = ui->rb3_klin->value(); // klin
     constantes_rb3[2] = ui->rb3_wmax->value(); // wmax
     constantes_rb3[3] = ui->rb3_kang->value(); // kang

}
