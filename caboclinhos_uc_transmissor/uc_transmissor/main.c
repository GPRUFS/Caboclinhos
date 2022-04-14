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
#use rs232(baud=9600,parity=N,xmit=PIN_C6,rcv=PIN_C7,bits=8,stream=PORT1)

#include <NRF24L01P.c>

//variaveis


//programa principal
void main(){

   setup_adc_ports(NO_ANALOGS);
   setup_adc(ADC_OFF);
   setup_spi(SPI_SS_DISABLED);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_1);
   setup_timer_1(T1_DISABLED);
   setup_timer_2(T2_DISABLED,0,1);
   setup_comparator(NC_NC_NC_NC);
   setup_vref(FALSE);
   
   //seta o canal em CANAL_NUM : 0 ou 1
   if (input(PIN_B7))
   {
      CANAL_NUM = 1;
   }
   else
   {
      CANAL_NUM = 0;
   }
   
   //inicia e configura modulo
   config_nrf24();
    
 
   while(true)
   {   
//     output_high(pin_A0);
//      Delay_ms(1);
//      output_low(pin_A0);
//      Delay_ms(1);
      
      if (kbhit())
      {
         ENVIA[0] = getc(); // palavra de confirmação de início 255 - não usar 255 em outro byte
         if (ENVIA[0] == 255)
         {
            ENVIA[1] = getc(); // lógica do robô 0
            ENVIA[2] = getc(); // velocidade roda 1 : robô 0
            ENVIA[3] = getc(); // velocidade roda 2 : robô 0 
            ENVIA[4] = getc(); // lógica do robô 1 
            ENVIA[5] = getc(); // velocidade roda 1 : robô 1 
            ENVIA[6] = getc(); // velocidade roda 2 : robô 1 
            ENVIA[7] = getc(); // lógica do robô 2
            ENVIA[8] = getc(); // velocidade roda 1 : robô 2 
            ENVIA[9] = getc(); // velocidade roda 2 : robô 2
         }         
      }
      ACK=envia_dados();
   }
}

