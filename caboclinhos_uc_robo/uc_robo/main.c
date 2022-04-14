#include <16F873A.h>            //PIC 8bits
#FUSES NOWDT                    //No Watch Dog Timer
#FUSES HS                       //Crystal osc <= 4mhz for PCM/PCH , 3mhz to 10 mhz for PCD
#FUSES PUT                      //Power Up Timer
#FUSES NOPROTECT                //Code not protected from reading
#FUSES NODEBUG                  //No Debug mode for ICD
#FUSES NOBROWNOUT               //No brownout reset
#FUSES NOLVP                    //No low voltage prgming, B3(PIC16) or B5(PIC18) used for I/O
#FUSES NOCPD                    //No EE protection
#FUSES NOWRT                    //Program memory not write protected
#use delay(clock=20000000)       //Clock de 4MHZ externo


#include <NRF24L01P.c>

//variaveis
int8 robo_ID;
int16 velocidade[2];
int8 logica;


//programa principal
void main(){

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_2(T2_DIV_BY_16,255,1);      //819 us overflow, 819 us interrupt
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   
   //seta o canal em CANAL_NUM : 0 ou 1
   if (input(PIN_A2))
   {
      CANAL_NUM = 1;
   }
   else
   {
      CANAL_NUM = 0;
   }
   
   //define o ID do robô : 0, 1 ou 2
   if (!input(PIN_A3))
   {
      if (!input(PIN_A4))
      {
         robo_ID = 0;
      }
      else
      {
         robo_ID = 1;
      }
   }
   else
   {
      robo_ID = 2;
   }
 
   //inicia e configura modulo
   config_nrf24();
   
   // inicializa os PWMs
   //set_pwm1_duty(0);      ->>>> PWM duty 0%
   //set_pwm1_duty(1023);   ->>>> PWM duty 100%
   setup_ccp1(CCP_PWM);
   setup_ccp2(CCP_PWM);

   // velocidade de teste
   velocidade[0] = 1023;
   velocidade[1] = 1023;
   
   // espera parado por 2 segundos
   output_low(PIN_B1);
   output_low(PIN_B2);
   output_low(PIN_B3);
   output_low(PIN_B4);
   set_pwm1_duty(velocidade[0]);
   set_pwm2_duty(velocidade[1]);   
   delay_ms(2000);
   
   // gira em torno do próprio eixo por 1 segundo
   output_low(PIN_B1);
   output_high(PIN_B2);
   output_low(PIN_B3);
   output_high(PIN_B4);   
   delay_ms(1000);
   
   // para
   output_low(PIN_B1);
   output_low(PIN_B2);
   output_low(PIN_B3);
   output_low(PIN_B4);
    
   // começa o loop
   while(true)
   {   
      if (RECEBE[0] == 255) // palavra de confirmação de pacote correto é 255
      {
         // só continua o código se passar no teste de confirmação, do contrário não faz nada.
         if (robo_ID == 0) // aqui vai ler o buffer do robô 0
         {
            logica = RECEBE[1];
            velocidade[0] = (int16)4*RECEBE[2];
            velocidade[1] = (int16)4*RECEBE[3];
         }
         if (robo_ID == 1) // aqui vai ler o buffer do robô 1
         {
            logica = RECEBE[4];
            velocidade[0] = (int16)4*RECEBE[5];
            velocidade[1] = (int16)4*RECEBE[6];
         }
         if (robo_ID == 2) // aqui vai ler o buffer do robô 2
         {
            logica = RECEBE[7];
            velocidade[0] = (int16)4*RECEBE[8];
            velocidade[1] = (int16)4*RECEBE[9];
         }
         
         // manda a velocidade desejada para os motores
         set_pwm1_duty(velocidade[0]);
         set_pwm2_duty(velocidade[1]);
         // 
         output_bit(pin_b4,bit_test(logica,4));
         output_bit(pin_b3,bit_test(logica,3));
         output_bit(pin_b2,bit_test(logica,2));
         output_bit(pin_b1,bit_test(logica,1));      
      }
   }
}
