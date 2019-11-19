
/* Bibliotecas usadas no projeto */

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <conio.c>
#include <time.h>
#include <ctype.h>
#include <windows.h>

/* Declaração das minhas funções e/ou métodos!!*/

void ConfiguracoesIniciais(bool primeiraVez);
int TelaInicialCarregandoJogo();
int TelaMenuInicial();
int TelaRegras();
int TelaCreditos();
bool EscolhaOpcaoMenuInicial(int opcaoEscolhida);
int SorteioNum(int var);
void RedirecionamentoTelasPelaTeclaDigitada(int tecla);
void SetarCorFundo(int corDeFundo);
void sorteiaAltura();
void Background(int alturaInicia);
void Barreira(bool reniciarBarreira);
void Barreira2(bool reiniciarBarreira);
bool colisao();
int ZerarPontuacao(int pontuacao);
void EscritaPontuacaoRecord(bool zerarPontuacao);
void ContagemRegressiva(int posicaoX, int posicaoY, char msg[50], bool contagemRegressiva,int tempoSairDaTela);
void desenhoHelicop(int linha , int coluna);
void IniciarJogo();
void EncerrarJogo();
void BotaoEsc(int comprimento, int altura, bool cor, int valorTextColor);


/* Jogo copter elaborado por Gustavo Melo Poppi da UNICESUMAR, do curso
de Análise e Desenvolvimento de Sistemas no 2ºSemestre. Ano de 2019  */


// Variáveis globais
int lin = 16, col = 13, record = 500, pontuacao = 0;
int mapaInicioCima, mapaInicioBaixo;
int tecla;
int  x, y, w, z;


/* Variaveis a respeito da barreira */
int velocidadeBarreira = 50; 


/* Variaveis a respeito do background */
bool zero;
int sorteio, linhaBaixo;

/* Variáveis a respeito da tela do carregando jogo */
bool sair;

bool nuncasair = true;
int AumentarVelocidade = 450;


int main(){

    ConfiguracoesIniciais(true); 
    
    do{ 
                
        desenhoHelicop(lin,col); 
        Background(sorteio);
        EscritaPontuacaoRecord(false);             
        
        Barreira(false);
        if (x <= 39 || w < 78)
            Barreira2(false);
        Sleep(velocidadeBarreira);  
        
        //if (contador > 78 && pontuacao > 800){
        if (pontuacao >= AumentarVelocidade){
            velocidadeBarreira = velocidadeBarreira - 4;
            AumentarVelocidade += 450;
        }        
       
        if (colisao()==true){
            Beep(330,500);                
            Sleep(500);
            SetarCorFundo(0); // 14 é a cor amarela     
            EscritaPontuacaoRecord(true);      
            EncerrarJogo();
        }
        
        // Se o helicóptero encostar em alguma das linhas, encerra o jogo
        if (!(col > sorteio) || !(col + 2 < (26-sorteio-linhaBaixo-1))){            
            Beep(330,500); 
            Sleep(500);
            EscritaPontuacaoRecord(true);      
            EncerrarJogo();
        }
            
        if (kbhit()){
           tecla = getch();
           if (tecla == 224){              
              tecla = getch(); //teclas: 72 cima, 80 baixo
              
              if(tecla == 72){ // helicóptero vai para cima
                 col = col - 1;
              }
              
              if (tecla == 80){
                 col = col + 1; // helicóptero vai para baixo
              }
           }
        }        
    }while(nuncasair);
}

//----------------------------------------------------------------------
void ConfiguracoesIniciais(bool primeiraVez){

    SetarCorFundo(9);
    // X = 80
    // Y = 25   
    setlocale (LC_ALL,"portuguese");
    system("mode 80,25");             
    srand(time(NULL));
    tecla = 0;
    
    if (primeiraVez == true)
        TelaInicialCarregandoJogo();    
        
    TelaMenuInicial();
}

//----------------------------------------------------------------------
void IniciarJogo(){    
        
    SetarCorFundo(9);// azul claro
    
    Barreira(true);
    Barreira2(true);    
    // sorteio da altura da Barreira inicial (Background), onde ela não pode ser igual a 0
    do{
        zero = false;
        SorteioNum(4);
        if (sorteio == 0){
            zero = true;
        }        
    }while(zero);    
    linhaBaixo = rand()%2; // só para linha de baixo não ficar igual a de cima.    
    
    desenhoHelicop(lin,col); 
    //sorteiaAltura(); // sortear a altura INICIAL das Barreiras
}

//----------------------------------------------------------------------
void EncerrarJogo(){
     
    int comprimento = 17, altura = 6; 
     
    clrscr(); 
    textcolor(4);
    gotoxy(comprimento,altura);printf("  _______      ___      .___  ___.  _______ \n");
    gotoxy(comprimento,altura+1);printf(" /  _____|    /   \\     |   \\/   | |   ____|\n");
    gotoxy(comprimento,altura+2);printf("|  |         /     \\    |        | |  |__   \n");
    gotoxy(comprimento,altura+3);printf("|  |  __    /   ^   \\   |  \\  /  | |   __|  \n");
    gotoxy(comprimento,altura+4);printf("|  | |_ |  /   /_\\   \\  |  |\\/|  | |  |____     \n");
    gotoxy(comprimento,altura+5);printf(" \\______| /___/   \\___\\ |__|  |__| |_______|\n");
     
    gotoxy(comprimento,altura+6);printf("  ______   ____    ____  _______ .______\n");
    gotoxy(comprimento,altura+7);printf(" /  __  \\  \\   \\  /   / |   ____||   _  \\ \n");
    gotoxy(comprimento,altura+8);printf("|  |  |  |  \\   \\/   /  |  |__   |  |_)  |\n");
    gotoxy(comprimento,altura+9);printf("|  |  |  |   \\      /   |   __|  |      /  \n");
    gotoxy(comprimento,altura+10);printf("|  `--'  |    \\    /    |  |____ |  |\\  \\_\n");
    gotoxy(comprimento,altura+11);printf(" \\______/      \\__/     |_______|| _| `.__|\n");
    gotoxy(comprimento+18,altura+13);printf(" Aguarde.\n");
    
    Sleep(1000); 
     
    ContagemRegressiva(25, 11,"Redirecionando ao Menu Principal...", false, 1500);    
    
    Barreira(true);
    Barreira2(true);
    TelaMenuInicial(); 
} 


//----------------------------------------------------------------------
int TelaInicialCarregandoJogo(){  
         
    do{
        fflush(stdin);
        sair = true;
        int comprimento = 14, altura = 5;      
        float PorcentagemCarregadoTelaInicial = 1;          
     
        //x representa linha e y a coluna
        int x = 1, y = 20;
        
        char situacao[14] = "";
        
        for (x = 0; x < 78; x++){ // laço de repetição para o helicóptero andar na tela
            gotoxy(comprimento,altura);printf("         __    ______     ______    ______          \n");
            gotoxy(comprimento,altura+1);printf("        |  |  /  __  \\   /  ____|  /   __ \\       \n");
            gotoxy(comprimento,altura+2);printf("        |  | |  |  |  | |  |  __  |  |  |  |        \n");
            gotoxy(comprimento,altura+3);printf("  .--.  |  | |  |  |  | |  | |_ | |  |  |  |        \n");
            gotoxy(comprimento,altura+4);printf("  |  `--'  | |  `--'  | |  |__| | |  `--'  |        \n");
            gotoxy(comprimento,altura+5);printf("   \\______/   \\______/   \\______|  \\______/     \n");
            
            gotoxy(comprimento-4,altura+6);printf("  ______   ______   .______   .__________. _______ .______   \n");
            gotoxy(comprimento-4,altura+7);printf(" /      | /  __  \\  |   _  \\  |          | |   ____||   _  \\  \n");
            gotoxy(comprimento-4,altura+8);printf("|  ,----'|  |  |  | |  |_)  | `---|  |---` |  |__   |  |_)  | \n");
            gotoxy(comprimento-4,altura+9);printf("|  |     |  |  |  | |   ___/      |  |     |   __|  |      /  \n");
            gotoxy(comprimento-4,altura+10);printf("|  `----.|  `--'  | |  |          |  |     |  |____ |  |\\  \\_.\n");
            gotoxy(comprimento-4,altura+11);printf(" \\______| \\______/  | _|          |__|     |_______|| _| `.__|\n");            
            
            if (PorcentagemCarregadoTelaInicial < 100)
                strcpy(situacao,"Carregando..."); 
            else
                strcpy(situacao,"Redirecionando...");            

            gotoxy(comprimento+21,altura+13);printf("%s\n",situacao);
            gotoxy(comprimento+25,altura+14);printf(" %.0f%% \n",PorcentagemCarregadoTelaInicial);
            
            PorcentagemCarregadoTelaInicial += 1.5;   
            if (PorcentagemCarregadoTelaInicial>=101.5){
                x = 79;
                Sleep(500);
                sair = false;
            }
        
            gotoxy(x,y);   printf("   ________");
            gotoxy(x,y+1); printf("x____.-'-.");
            gotoxy(x,y+2); printf("\"\"___.____)");            
        
            
            if (y > 72)
                x = 19;
            Sleep(90);         
            clrscr();
            tecla = 0;                        
        }
    }while(sair);   
}   
    
//----------------------------------------------------------------------
int TelaMenuInicial(){
    
    SetarCorFundo(9); // cor azul claro
    fflush(stdin);
    sair = true;
    
    int b = 1, c = 20, tecla = 0, PosicaoSetaEscolha = 12;
    //        int x = 14, y = 5; 
 
    menuInicial:
        clrscr();
        
        textcolor(15);
        gotoxy(10,2);printf("  ______   ______   .______   .__________. _______ .______   \n");
        gotoxy(10,3);printf(" /      | /  __  \\  |   _  \\  |          | |   ____||   _  \\  \n");
        gotoxy(10,4);printf("|  ,----'|  |  |  | |  |_)  | `---|  |---` |  |__   |  |_)  | \n");
        gotoxy(10,5);printf("|  |     |  |  |  | |   ___/      |  |     |   __|  |      /  \n");
        gotoxy(10,6);printf("|  `----.|  `--'  | |  |          |  |     |  |____ |  |\\  \\_.\n");
        gotoxy(10,7);printf(" \\______| \\______/  | _|          |__|     |_______|| _| `.__|\n");
        
        
        gotoxy(33,PosicaoSetaEscolha);printf(">");
        gotoxy(35,12);printf("Jogar\n");
        gotoxy(35,14);printf("Regras\n");
        gotoxy(35,16);printf("Créditos\n");
        gotoxy(35,18);printf("Sair\n");
    
        gotoxy(11,23);printf("*Desenvolvido por: Gustavo Melo Poppi, 2º Semestre de ADS\n");
    
    do{           
        if (kbhit()){            
            tecla = getch();    
            //printf("%d",tecla);
            if (tecla == 224){
              tecla = getch(); 
              //printf("%d",tecla);
                                         
              if (tecla == 72){ // 72 é a seta para CIMA
                  if (PosicaoSetaEscolha == 12){ 
                      PosicaoSetaEscolha = 18; // Validação se já estiver no primeiro menu de cima, ele vai direto para o ultimo
                      goto menuInicial;
                  }
                  else{
                      PosicaoSetaEscolha -= 2;
                      goto menuInicial;
                  }
              }
                 
              if (tecla == 80){ // 80 é a seta para BAIXO
                  if (PosicaoSetaEscolha == 18){ 
                      PosicaoSetaEscolha = 12; // Validação se já estiver no ultimo menu de baixo, ele vai direto para o primeiro
                      goto menuInicial;
                  }
                  else{  
                      PosicaoSetaEscolha += 2;
                      goto menuInicial;
                  }
              }   
           }
           
           if (tecla == 13){ // se der ENTER vai para a função 
               EscolhaOpcaoMenuInicial(PosicaoSetaEscolha);    
           }
        }    
    }while(sair);
    IniciarJogo();
} 

//----------------------------------------------------------------------
int TelaRegras(){
    
    SetarCorFundo(9); // cor azul claro; 
    
    int tecla = 0, parar = 0;
    bool sair;
    
    do{
        fflush(stdin);
        sair = true;
        int y = 20, cont = 0;
        
        int comprimento = 17, altura = 3;         
              
            
        for (x = 56; x > 12; x--){ // laço de repetição para o helicóptero andar na tela   
               
            BotaoEsc(65,1,true,2);      
            
            textcolor(15);             
            gotoxy(comprimento-10,altura+1);printf("Teclas:\n");
            
            gotoxy(comprimento-2,altura);printf(" ____\n");
            gotoxy(comprimento-2,altura+1);printf("||W ||\n");
            gotoxy(comprimento-2,altura+2);printf("||__||\n");
            gotoxy(comprimento-2,altura+3);printf("|/__\\|\n");
            
            gotoxy(comprimento+5,altura+2);printf(" ou \n");
            
            gotoxy(comprimento+10,altura);printf(" ____\n");
            gotoxy(comprimento+10,altura+1);printf("||S ||\n");
            gotoxy(comprimento+10,altura+2);printf("||__||\n");
            gotoxy(comprimento+10,altura+3);printf("|/__\\|\n");
            
            gotoxy(comprimento-10,altura+6);printf("Regras:\n");
            gotoxy(comprimento-3,altura+7);printf("Você deve usar as teclas W ou S para desviar das barreias\n");
            gotoxy(comprimento-3,altura+8);printf("e não pode enconstar na linha de cima nem na de baixo\n");
            
                     
            gotoxy(12,14); printf("______________________________________________");
            
            gotoxy(20,y-5+cont);   printf("   ________");
            gotoxy(20,y-4+cont); printf("x____.-'-.");
            gotoxy(20,y-3+cont); printf("\"\"___.____)"); 
            
            gotoxy(x,y-3); printf(" _");
            gotoxy(x,y-2); printf("| |");
            gotoxy(x,y-1); printf("| |");
            gotoxy(x,y);   printf("|_|");             
            
            gotoxy(12,24); printf("______________________________________________");            
                                 
            if (cont != 6) // ele contar, hora q chegar em 5 ele irá parar. Isso é qndo o helicóptero chegar na posição certa na tela ele ficar parado.
                cont += 1;
            
            Sleep(70);
            
            if (kbhit()){            
                tecla = getch();   
                
                if (tecla == 13 || tecla == 27){
                    x = 11; // para sair do laço
                    sair = false;     
                }        
            }              
            clrscr();
        }           
        
    }while(sair);  
    
    RedirecionamentoTelasPelaTeclaDigitada(tecla);  
} 

//----------------------------------------------------------------------
int TelaCreditos(){

    int comprimento = 8, altura = 3, tecla = 0;  
    bool sair = true;    
    
    clrscr();
    
    BotaoEsc(65,1,true,2); 
    
    textcolor(15);
    gotoxy(comprimento,altura);  printf("Esse jogo foi baseado no Classic Copter Game para Android.\n");
    gotoxy(comprimento,altura+2);printf("Jogo criado pelo aluno Gustavo Melo Poppi, do curso de  \n");
    gotoxy(comprimento,altura+4);printf("Análise e Desenvolvimento de Sistemas.\n");
        
    gotoxy(comprimento,altura+8);printf("Esse projeto foi criado para obtenção parcial da nota\n");
    gotoxy(comprimento,altura+10);printf("do 2º Semestre da matéria de Algoritmos e Lógica de Programação II, \n");
    gotoxy(comprimento,altura+12);printf("ministrada pelo Professor Edson Moreno na instituição UNICESUMAR,\n");
    gotoxy(comprimento,altura+14);printf("situada na cidade de Maringá no estado do Paraná.\n");
        
    gotoxy(comprimento,altura+18);printf("Projeto esse que ocorreu no ano de 2019, onde\n");
    gotoxy(comprimento,altura+20);printf("tinhamos que elaborar qualquer jogo em linguagem C.\n");
    
    tecla = getch();
    
    if (tecla == 27)
        RedirecionamentoTelasPelaTeclaDigitada(tecla);    
}

//----------------------------------------------------------------------
bool EscolhaOpcaoMenuInicial(int opcaoEscolhida){

    switch(opcaoEscolhida){
    
        case 12: // 12 valor do X e volta para o jogo
            ContagemRegressiva(33,11,"Iniciando em:",true,0); // Contagem antes de inicia o jogo
            return sair = false;
         break;
        case 14: // vai para página de REGRAS
            return TelaRegras();
         break;
        case 16: // vai para página de CRÉDITOS
            return TelaCreditos();
         break;
         case 18: // fecha o jogo
            exit(0); 
         break;
        default:
        return false;  
    }              
}
                                                                                                               
//----------------------------------------------------------------------
int SorteioNum(int var){
    
    sorteio = rand()%var;      
    return sorteio;
}  

//----------------------------------------------------------------------
void RedirecionamentoTelasPelaTeclaDigitada(int tecla){

    switch(tecla){
        //case 13: // ENTER
            //IniciarJogo();
            //break;
        case 27: // ESC
            TelaMenuInicial();
            break; 
        default:
            break; 
    }       
}

//----------------------------------------------------------------------
void SetarCorFundo(int corDeFundo){
    textbackground(corDeFundo);
}

//----------------------------------------------------------------------
void Background(int alturaInicia){
     bool zero;     
     
     for (int x = 1; x<80; x++){
         
         // linha da cima, o +1 é para nunca começar com a linha tamanho 1, pois se não irá ter conflito com o texto
         gotoxy(x,alturaInicia+1); printf("_");
         
         // linha de baixo, onde 25 é a altura máxima
         gotoxy(x,(25-alturaInicia-linhaBaixo)); printf("_");
     }    
     
}

//----------------------------------------------------------------------
void Barreira(bool reiniciarBarreira){    
     
     textcolor(15); // cor branca
     
     // Condições para estar dentro do "mapa"
     if ((y > sorteio) && (y + 3 < (25-sorteio-linhaBaixo-1))){ 
         gotoxy(x,y);   printf(" _");
         gotoxy(x,y+1); printf("| |");
         gotoxy(x,y+2); printf("| |");
         gotoxy(x,y+3); printf("|_|");
         
     }
     else
         y = (rand()%24)+1;  
     
     // Faz a Barreira andar da direita para a esquerda
     x --;
     
     // Se o valor do X for menor que 0 ele passa fora da tela
     if (x < 1 || reiniciarBarreira == true){
        x = 78;
        y = (rand()%24)+1;
     }    
}

//----------------------------------------------------------------------
void Barreira2(bool reiniciarBarreira){   
     
     textcolor(15); // cor branca
     
     // Condições para estar dentro do "mapa"
     if ((z > sorteio) && (z + 3 < (25-sorteio-linhaBaixo-1))){ 
         gotoxy(w,z);   printf(" _");
         gotoxy(w,z+1); printf("| |");
         gotoxy(w,z+2); printf("| |");
         gotoxy(w,z+3); printf("|_|");
     }else{
         z = (rand()%24)+1;  
     }
     
     // Faz a Barreira andar da direita para a esquerda
     w --;
     
     // Se o valor do X for menor que 0 ele passa fora da tela
     if (w < 1 || reiniciarBarreira == true){
        w = 78;
        z = (rand()%24)+1;
     }    
}

//----------------------------------------------------------------------
bool colisao(){
     
     // x é o valor sorteado no plano X (comprimento)
     // y é o valor sorteado no plano Y (altura)
     // lin é a linha do helicóptero
     // col é a coluna do helicóptero
     
     if ((x >= lin) && (x <= (lin+9))) // +9 pq é o comprimento do helicóptero
     {
        if (((y >= col) && (y <= (col+2))) || (col >= y && (col) <= y+3))       
           return true;           
        else
           return false;
     }  
     
     if ((w >= lin) && (w <= (lin+9)))
     {
        if (((z >= col) && (z <= (col+2))) || (col >= z && (col) <= z+3))       
           return true;           
        else
           return false;
     }          
}

//----------------------------------------------------------------------
void EscritaPontuacaoRecord(bool zerarPontuacao){

    if (zerarPontuacao)
        pontuacao = 0;
        
    gotoxy(1,1); printf("Player:");
    gotoxy(40,1); printf("Pontuação: %d",pontuacao);
    gotoxy(60,1); printf("Record: %d",record);
    
    pontuacao = pontuacao + 3;
    if (pontuacao >= record )
       record = pontuacao;        
}

//----------------------------------------------------------------------
void ContagemRegressiva(int posicaoX, int posicaoY, char msg[50], bool contagemRegressiva,int tempoSairDaTela){

    bool sair = true;
    int x;
    
    clrscr();
    gotoxy(posicaoX,posicaoY); printf("%s",msg);
    
    if (contagemRegressiva){ // caso queira a contagem, caso contrário só irá apresentar a mensagem
        do{
            for (int x = 3 ; x >= 1; x--){
                gotoxy(39,12); printf("%d",x);   
                Sleep(1000);
            } 
            sair = false;
        }while(sair);    
    }  
    Sleep(tempoSairDaTela);
}

//----------------------------------------------------------------------
void desenhoHelicop(int linha , int coluna){

    SetarCorFundo(9);// cor azul clara  

    clrscr();// limpa a tela
    gotoxy(linha,coluna);   printf("   ________");
    gotoxy(linha,coluna+1); printf("x____.-'-.");
    gotoxy(linha,coluna+2); printf("\"\"___.____)");
}

//----------------------------------------------------------------------
void BotaoEsc(int comprimento, int altura, bool cor, int valorTextColor){
    
    if (cor)
       textcolor(valorTextColor);
    gotoxy(comprimento,altura);printf("  ESC = Voltar\n");
}

