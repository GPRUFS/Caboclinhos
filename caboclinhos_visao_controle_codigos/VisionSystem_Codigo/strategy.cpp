#include "strategy.h"


//////////////////////////////////////////////////////////////////////////////
////////////////////////ADICIONAR FUNCOES NA INTERFACE////////////////////////
//////////////////////////////////////////////////////////////////////////////

//COLOCAR ("NOME QUE APARECE NA INTERFACE",NOME_FUNCAO_DO_JOGADOR)
//FUNCOES...Adicionar_atacante("Nome",Nome_da_funcao);
//          Adicionar_zagueiro("Nome",Nome_da_funcao);
//          Adicionar_goleiro("Nome",Nome_da_funcao);
//          Adicionar_estrategia("Nome",Nome_da_funcao);

Strategy::Strategy()
{
   V = 0;
   W = 0;

   goalkeeper = 0;
   g[0] = 4;
   g[1] = 5;
   g[2] = 6;

   ataque = 1;
   a[0] = 1;
   a[1] = 2;
   a[2] = 3;

   defensor = 2;
   z[0] = 7;
   z[1] = 8;
   z[2] = 9;

   Alteracao_jogador[0] = -1;
   Alteracao_jogador[1] = -1;
   Alteracao_jogador[2] = -1;


   Adicionar_atacante("atacante",atacante);

   Adicionar_zagueiro("zagueiro",zagueiro);

   Adicionar_goleiro("goleiro",goleiro);

   Adicionar_estrategia("estrategia",estrategia1);

}
void parar(vector<Robot> robos)
{
    comandos resultado;
    unsigned char str[10];
    str[0] = 255;
    for(int i=1;i<10;i++) str[i] = 0;
    envia_comandos_robo(str);
}
///////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////



/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////// FAZ AQUI AS ESTRATEGIAS ////////////////////////////////////////////////////////////////////////////////////////////////
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// VARIAVEIS QUE PODEM SER USADAS
//Objeto robo - variavel q contem centro e orientacao
//robos[0] -- robo vermelho, robos[1]- robo verde, robos[2]- robo magenta
//
// adversarios- SE USAR POR FAVOR TESTE O TAMANHO DELE
// EX.
// if(adversarios.size()>0) faça alguma coisa
// adversarios é um vetor de Point com as posicoes x e y do adversario, o vetor pode variar de 0 a 3 posicoes
//
// bola -  da as coordenadas da bola
// podendo ser usada chamando bola.x ou bola.y
//
//
// *campo - variavel com as componentes do campo...ftop...gboty..gtopy.....
//
// ACONSELHO QUE DIVIDA OS COMPORTAMENTOS DOS ZAGUEIROS, GOLEIROS E ATACANTES EM FUNCOES SEPARADAS
// E USE A FUNCAO DE ESTRATEGIA PARA COORDENAR ESSES COMPORTAMENTOS
// AS FUNCOES PODEM SER CHAMADAS COMO O EXEMPLO A SEGUIR
//
// comando result = Atacantes();
// comando result = Goleiro();
// comando result = Zagueiro();
//
// ESSAS FUNCOES SERÃO DEFINIDAS PELO USUARIO A PARTIR DA INTERFACE
// DEPOIS DE FEITA A FUNCAO... ADICIONE-A NO CONSTRUTOR
// da SEGUINTE FORMA
// Adicionar_Atacante("NOME QUE APARECE NA INTERFACE",NOME_DA_FUNCAO);

//

comandos Strategy::atacante(Robot rb)
{
        comandos resultado;
        ang_err angulo;

        angulo = olhar(rb, bola.x, bola.y);

        W = controle_angular(rb,angulo.fi);

        V = controle_linear(rb, bola.x, bola.y);

        resultado = gera_comandos_vr(rb, V, W);

        return(resultado);
}

comandos Strategy::goleiro(Robot rb)
{
    comandos resultado;
    ang_err angulo;



    W = 60;

    V = 0;

    resultado = gera_comandos_vr(rb, V, W);

    return(resultado);
}

comandos Strategy::zagueiro(Robot rb)
{
    comandos resultado;
    ang_err angulo;

    W = -60;

    V = 0;

    resultado = gera_comandos_vr(rb, V, W);

    return(resultado);
}

void Strategy::estrategia1()
{
    comandos resultado;
    unsigned char str[10];
    str[0] = 255;
    for(int i=1;i<10;i++) str[i] = 0;

    //DEFINIR JOGADORES DEFAULT
   Atacante = base_Atacantes[0];
   Goleiro  = base_Goleiros [0];
   Zagueiro = base_Zagueiros[0];

   Permitir_alteracao_usuario();

   //CHAMAR A FUNCAO DE ATACANTE DESSA FORMA
  // (this->*Atacante)();

  int aux;
  if( robos[defensor].get_center_robot().y < campo->gtopy && robos[defensor].get_center_robot().y > campo->gboty &&
      robos[defensor].get_center_robot().x < robos[goalkeeper].get_center_robot().x)
  {
      aux = defensor;
      defensor = goalkeeper;
      goalkeeper = aux;
  }
  //1
  //2
  //3

  //4
  //5
  //6

  //7
  //8
  //9

   resultado = (this->*Zagueiro)(robos[defensor]); // robô 2

   str[z[0]] = resultado.logica; //lógica
   str[z[1]] = resultado.vrD; // velocidade da roda direita (magnitude)
   str[z[2]] = resultado.vrE; // velocidade da roda esquerda (magnitude)

   resultado = (this->*Goleiro)(robos[goalkeeper]); //robo 0

   str[g[0]] = resultado.logica; //lógica
   str[g[1]] = resultado.vrD; // velocidade da roda direita (magnitude)
   str[g[2]] = resultado.vrE; // velocidade da roda esquerda (magnitude)

   resultado = (this->*Atacante)(robos[ataque]); // robo 1

   str[a[0]] = resultado.logica; //lógica
   str[a[1]] = resultado.vrD; // velocidade da roda direita (magnitude)
   str[a[2]] = resultado.vrE; // velocidade da roda esquerda (magnitude)

      envia_comandos_robo(str);
}

void Strategy::Setar_Campo(Configurations *c)
{
    campo = c;
}

void Strategy::Setar_Variaveis_jogo(Vector<Robot> r, Ball b, Vector<Point> a)
{
    robos = r;
    bola = b;
    adversarios = a;
}

vector<string> Strategy::Get_atacantes()
{
    return Nome_atacante;
}

vector<string>Strategy::Get_goleiros()
{
    return Nome_goleiro;
}

vector<string>Strategy::Get_zagueiros()
{
    return Nome_zagueiro;
}

vector<string>Strategy::Get_Estrategias()
{
    return Nome_Estrategias;
}

void Strategy::Adicionar_atacante(String nome, Func atacante)
{
    Nome_atacante.push_back(nome);
    base_Atacantes.push_back(atacante);
}

void Strategy::Adicionar_goleiro(String nome, Func goleiro)
{
    Nome_goleiro.push_back(nome);
    base_Goleiros.push_back(goleiro);
}

void Strategy::Adicionar_estrategia(String nome, cerebro Est)
{
    Nome_Estrategias.push_back(nome);
    Estrategias.push_back(Est);
}

void Strategy::Adicionar_zagueiro(String nome, Func zagueiro)
{
    Nome_zagueiro.push_back(nome);
    base_Zagueiros.push_back(zagueiro);
}

void Strategy::Executar_estrategia(int i)
{
    if(i != -1 && i != -2)
     (this->*Estrategias[i])();

}

void Strategy::Setar_Atacante(int i)
{

      Alteracao_jogador[0] = i;
}

void Strategy::Setar_Goleiro(int i)
{
    Alteracao_jogador[1] = i;
}

void Strategy::Setar_Zagueiro(int i)
{
    Alteracao_jogador[2] = i;
}

void Strategy::Permitir_alteracao_usuario()
{
    if(Alteracao_jogador[0] != -1)
      Atacante = base_Atacantes[Alteracao_jogador[0]];

    if(Alteracao_jogador[1] != -1)
      Goleiro = base_Goleiros[Alteracao_jogador[1]];

    if(Alteracao_jogador[2] != -1)
        Zagueiro = base_Zagueiros[Alteracao_jogador[2]];
}

Strategy::~Strategy()
{
    delete campo;
}
