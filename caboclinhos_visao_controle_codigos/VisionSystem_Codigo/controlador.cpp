#include "controlador.h"
#include <cmath>


double limita_velocidade(double valor, double sat)
{
      if (valor > sat) {valor = sat;}
      if (valor < -sat) {valor = -sat;}
      return(valor);
}

ang_err olhar(Robot rb, double px, double py)   // função testada - ok!
{
      double r = rb.get_orientation(); // orientação do robô de -180 a 180
      ang_err angulo;

      angulo.flag = 1;
      angulo.fi = atan2((py - rb.get_center_robot().y) , (px - rb.get_center_robot().x))*180/M_PI;  //ângulo entre -180 e 180

      if (r < 0)  {r = r + 360;}          //muda para 0 a 360
      if (angulo.fi < 0)   {angulo.fi = angulo.fi + 360;}      //muda para 0 a 360

      angulo.fi = angulo.fi - r;  //erro de orientação a ser corrigido

      if (angulo.fi > 180) {angulo.fi = angulo.fi - 360;}  // limita entre -180 e 180
      if (angulo.fi < -180) {angulo.fi = angulo.fi + 360;} // limita entre -180 e 180

      if (angulo.fi > 90) // se for mais fácil, olhar com o fundo...
      {
          angulo.fi = angulo.fi - 180;
          angulo.flag = -1;
      }
      if (angulo.fi < -90) // se for mais fácil, olhar com o fundo...
      {
          angulo.fi = 180 + angulo.fi;
          angulo.flag = -1;
      }

      // angulo.fi é o ângulo a ser corrigido na convenção do sistema de visão. valores entre -90 e 90.
      // angulo.flag é o sinal a ser aplicado na velocidade linear
      return(angulo);
}

double controle_angular(Robot rb, double fi) // função testada. lembrete : (sinal de w) = -(sinal de fi)
{
    double W_max = rb.W_max,    // constante limitante da tangente hiperbólica : deve ser negativa
           k_ang = rb.k_ang,  // constante de contração da tangente hiperbólica

           W = 0;

    fi = fi/90; // coloca o erro entre -1 e 1

    W = W_max*tanh(k_ang*fi); // não linear

    return(W); //deve tetornar um valor entre -1 e 1
}

double controle_angular_goleiro(double fi) // função testada. lembrete : (sinal de w) = -(sinal de fi)
{
    double W_max = -1,    // constante limitante da tangente hiperbólica : deve ser negativa
           k_ang = 0.6,  // constante de contração da tangente hiperbólica

           W = 0;

    fi = fi/90; // coloca o erro entre -1 e 1

    W = W_max*tanh(k_ang*fi); // não linear


    W = limita_velocidade(W,0.2); //satura em -1 a 1
    return(W); //deve tetornar um valor entre -1 e 1
}

double controle_linear(Robot rb, double px, double py)
{
    double  V = 0,
            k_lin = rb.k_lin,   //constante de contração da tangente hiperbólica
            V_max = rb.V_max,       //constante limitante da tangente hiperbólica
            v_min = 0.03,  	 //módulo da velocidade linear mínima permitida
            ang_grande = 30, //para ângulos maiores que esse valor o sistema da prioridade ao W, reduzindo o V
            dist = distancia(rb, px, py);

    ang_err angulo = olhar(rb, px, py);

    V = V_max*tanh(k_lin*dist*angulo.flag);  //controle não linear de V


    V = V*cos(angulo.fi*M_PI/180);  // controle de prioridade reduzindo V quando "ang_err" for grande

    return(V);
}

double controle_linear_goleiro(Robot rb, double px, double py)
{
    double  V = 0,
            k_lin = rb.k_lin,   //constante de contração da tangente hiperbólica
            V_max = rb.V_max,       //constante limitante da tangente hiperbólica
            v_min = 0.03,  	 //módulo da velocidade linear mínima permitida
            ang_grande = 30, //para ângulos maiores que esse valor o sistema da prioridade ao W, reduzindo o V
            dist = distancia(rb, px, py);

    ang_err angulo = olhar(rb, px, py);

    V = V_max*1/dist;  //controle proporcional

}


comandos gera_comandos_vr(Robot rb, double V, double W)
{
    double vre_, vrd_;
    comandos final;
    int VR_max = 254;


    vrd_ = rb.prop_roda_d*(V + W)*(VR_max - rb.zonamorta_d);

    vre_ = rb.prop_roda_e*(V - W)*(VR_max - rb.zonamorta_e);

    if (vrd_ >= 0)
    {
        vrd_ = vrd_ + rb.zonamorta_d;
    }
    else
    {
        vrd_ = vrd_ - rb.zonamorta_d;
    }
    vrd_ = limita_velocidade(vrd_, 254); // limita velocidade da roda direita


    if (vre_ >= 0)
    {
        vre_ = vre_ + rb.zonamorta_e;
    }
    else
    {
        vre_ = vre_ - rb.zonamorta_e;
    }
    vre_ = limita_velocidade(vre_, 254);  // limita velocidade da roda esquerda

    final.vrD = rint(abs(vrd_));
    final.vrE = rint(abs(vre_));


    // atribuindo as direções à palavra logica
    final.logica = 0;
    if(vrd_ > 0) final.logica = final.logica | 8;
    if(vrd_ < 0) final.logica = final.logica | 16;
    if(vre_ > 0) final.logica = final.logica | 4;
    if(vre_ < 0) final.logica = final.logica | 2;


    return(final);
}

double distancia(Robot rb, double px, double py)
{
      double dist = sqrt( pow((rb.get_center_robot().x-px),2) + pow((rb.get_center_robot().y-py),2) );
      return(dist);
}



