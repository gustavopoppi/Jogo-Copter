#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <conio.c>
#include <time.h>
#include <ctype.h>
#include <windows.h>

/* Coisas a fazer

   Telas:
         - Tela de entrada ( Jogo Copter -> Desenvolvido por...), fica uns 3 segundos na tela e redireciona para segunda tela
         - Segunda tela é a tela de Menu (Jogar, Como Jogar, Créditos), um extra é deixar escolher a cor do helicóptero
         -      
*/

/* Jogo copter elaborado por Gustavo Melo Poppi da UNICESUMAR, do curso
de Análise e Desenvolvimento de Sistemas no 2ºSemestre. Ano de 2019  */


int lin = 16, col = 13, record = 500, pontuacao = 0;
int mapaInicioCima, mapaInicioBaixo;
int tecla;
int  x, y;


/* Variaveis a respeito da barreira */
int velocidadeBarreira = 50; 


/* Variaveis a respeito do background */
bool zero;
int sorteio, linhaBaixo;

/* Variáveis a respeito da tela do carregando jogo */
bool sair;



//----------------------------------------------------------------------
int TelaInicialCarregandoJogo(){
     
    do{
        fflush(stdin);
        sair = true;
        int x = 14, y = 5;      
        float PorcentagemCarregadoTelaInicial = 1;  
        
        // b = x, c = y
        // b representa linha e c a coluna
        int b = 1, c = 20;
        
        char situacao[14] = "";
        
        for (b = 0; b < 78; b++){
            gotoxy(x,y);printf("         __    ______     ______    ______          \n");
            gotoxy(x,y+1);printf("        |  |  /  __  \\   /  ____|  /   __ \\       \n");
            gotoxy(x,y+2);printf("        |  | |  |  |  | |  |  __  |  |  |  |        \n");
            gotoxy(x,y+3);printf("  .--.  |  | |  |  |  | |  | |_ | |  |  |  |        \n");
            gotoxy(x,y+4);printf("  |  `--'  | |  `--'  | |  |__| | |  `--'  |        \n");
            gotoxy(x,y+5);printf("   \\______/   \\______/   \\______|  \\______/     \n");
            
            gotoxy(x-4,y+6);printf("  ______   ______   .______   .__________. _______ .______   \n");
            gotoxy(x-4,y+7);printf(" /      | /  __  \\  |   _  \\  |          | |   ____||   _  \\  \n");
            gotoxy(x-4,y+8);printf("|  ,----'|  |  |  | |  |_)  | `---|  |---` |  |__   |  |_)  | \n");
            gotoxy(x-4,y+9);printf("|  |     |  |  |  | |   ___/      |  |     |   __|  |      /  \n");
            gotoxy(x-4,y+10);printf("|  `----.|  `--'  | |  |          |  |     |  |____ |  |\\  \\_.\n");
            gotoxy(x-4,y+11);printf(" \\______| \\______/  | _|          |__|     |_______|| _| `.__|\n");
            //gotoxy(x+19,y+13);printf("Carregando...\n");
            
            if (PorcentagemCarregadoTelaInicial < 100)
                strcpy(situacao,"Carregando..."); 
            else
                strcpy(situacao,"Redirecionando...");
            

            gotoxy(x+21,y+13);printf("%s\n",situacao);
            gotoxy(x+25,y+14);printf(" %.0f%% \n",PorcentagemCarregadoTelaInicial);
            
            PorcentagemCarregadoTelaInicial += 1.5;   
            if (PorcentagemCarregadoTelaInicial>=101.5){
                b = 79;
                Sleep(500);
                sair = false;
            }
        
            gotoxy(b,c);   printf("   ________");
            gotoxy(b,c+1); printf("x____.-'-.");
            gotoxy(b,c+2); printf("\"\"___.____)");            
        
            
            if (b > 72)
                c = 19;
            Sleep(90);         
            clrscr();
            tecla = 0;                        
        }
    }while(sair);   
}  

//----------------------------------------------------------------------
bool EscolhaOpcaoMenuInicial(int opcaoEscolhida){

    switch(opcaoEscolhida){
    
        case 12: // volta para o jogo
            return sair = false;
         break;
        case 14: // vai para página de REGRAS
            return 2;
         break;
        case 16: // vai para página de CRÉDITOS
            return 3;
         break;
        default:
        return false;  
    }              
}   
    
//----------------------------------------------------------------------
int TelaMenuInicial(){
    
   
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
    
        gotoxy(11,23);printf("*Desenvolvido Por: Gustavo Melo Poppi, 2º Semestre de ADS\n");
    
    do{           
        if (kbhit()){            
            tecla = getch();    
            //printf("%d",tecla);
            if (tecla == 224){
              tecla = getch(); 
              //printf("%d",tecla);
                                         
              if (tecla == 72){ // 72 é a seta para CIMA
                  if (PosicaoSetaEscolha == 12){ 
                      PosicaoSetaEscolha = 16; // Validação se já estiver no primeiro menu de cima, ele vai direto para o ultimo
                      goto menuInicial;
                  }
                  else{
                      PosicaoSetaEscolha -= 2;
                      goto menuInicial;
                  }
              }
                 
              if (tecla == 80){ // 80 é a seta para BAIXO
                  if (PosicaoSetaEscolha == 16){ 
                      PosicaoSetaEscolha = 12; // Validação se já estiver no ultimo menu de baixo, ele vai direto para o primeiro
                      goto menuInicial;
                  }
                  else{  
                      PosicaoSetaEscolha += 2;
                      goto menuInicial;
                  }
              }   
           }
           
           if (tecla == 13){
               printf("%d",tecla);
               EscolhaOpcaoMenuInicial(PosicaoSetaEscolha);    
           }
        }    
    }while(sair);    
}
                                                                                                               
//----------------------------------------------------------------------
int sorteioNum(int var){
    
    sorteio = rand()%var;      
    return sorteio;
}

//----------------------------------------------------------------------
// Sorteia de x (linha) e y (coluna). x = 78, pois é o valor inicio da direita para esquerda
void sorteiaAltura(){
         
     x = 78;
     y = (rand()%24)+1;       
}

//----------------------------------------------------------------------
void background(int alturaInicia){
     bool zero;     
     
     for (int x = 1; x<80; x++){
         
         // linha da cima, o +1 é para nunca começar com a linha tamanho 1, pois se não irá ter conflito com o texto
         gotoxy(x,alturaInicia+1); printf("_");
         
         // linha de baixo, onde 25 é a altura máxima
         gotoxy(x,(25-alturaInicia-linhaBaixo)); printf("_");
         
         
         // implementar um novo cenário de fundo, sem ser apenas uma reta
         /*gotoxy(6,5); printf("\\");
         gotoxy(7,5); printf("_/");*/
     }    
     
}

//----------------------------------------------------------------------
void barreira(){
     int col1,col2,col3;
     // acrescentar mais tipos de barreiras e colocar como switch.. case(0),  case(1)
    
     
     textcolor(15); // cor branca
     
     // Condições para estar dentro do "mapa"
     if ((y > sorteio) && (y + 2 < (25-sorteio-linhaBaixo-1))){ 
         gotoxy(x,y);   printf(" _");
         gotoxy(x,y+1); printf("| |");
         gotoxy(x,y+2); printf("|_|");
         //teste = true;
//         printf("%d",teste);
//         Sleep(1000);
     }else{
           //printf("%d",teste);
//           Sleep(1000);
//           teste=false;
         sorteiaAltura();  
     }
     
     // Faz a barreira andar da direita para a esquerda
     x --;
     
     // Se o valor do X for menor que 0 ele passa fora da tela
     if (x < 1){
        sorteiaAltura();
     }    
}

//----------------------------------------------------------------------
bool colisao(){
     
     // x é o valor sorteado no plano X (comprimento)
     // y é o valor sorteado no plano Y (altura)
     // lin é a linha do helicóptero
     // col é a coluna do helicóptero
     int x, y ;
     if ((x >= lin) && (x <= (lin+9)))
     {
        if (((y >= col) && (y <= (col+2))) || (col >= y && (col) <= y+2))
        {
            return true;
        }    
     else
        return false;
     }   
    // if  ((x >= lin) && (x <= (lin+9)) && (col >= x) && (col <= (y+2)))  
//         return true;
//     else
//         return false;
         // col >= x && col <= y+
         
}

//----------------------------------------------------------------------
void EscritaPontuacaoRecord(){

    gotoxy(1,1); printf("Player:");
    gotoxy(40,1); printf("Pontuação: %d",pontuacao);
    gotoxy(60,1); printf("Record: %d",record);
    
    pontuacao = pontuacao + 3;
    if (pontuacao >= record )
       record = pontuacao;    
    
}

//----------------------------------------------------------------------
void ContagemRegressiva(){

    bool sair = true;
    
    clrscr();
    gotoxy(33,11); printf("Iniciando em:");
    do{
        for (int x = 3 ; x >= 1; x--){
            gotoxy(39,12); printf("%d",x);   
            Sleep(1000);
        } 
        sair = false;
    }while(sair);      
}

//----------------------------------------------------------------------
void desenhoHelicop(int linha , int coluna){

    textbackground(9);// cor azul clara  

    clrscr();// limpa a tela
    gotoxy(linha,coluna);   printf("   ________");
    gotoxy(linha,coluna+1); printf("x____.-'-.");
    gotoxy(linha,coluna+2); printf("\"\"___.____)");
}

//----------------------------------------------------------------------
void encerrarJogo(){
    system("pause");   
}  

int main(){
    // X = 80
    // Y = 25   
    setlocale (LC_ALL,"portuguese");
    system("mode 80,25");             
    srand(time(NULL));
    tecla = 0;
    
    // sorteio da altura da barreira inicial (background), onde ela não pode ser igual a 0
    do{
        zero = false;
        sorteioNum(4);
        if (sorteio == 0){
            zero = true;
        }        
    }while(zero);
    linhaBaixo = rand()%2;
    
    desenhoHelicop(lin,col); 
    sorteiaAltura();
    
    TelaInicialCarregandoJogo();    
    TelaMenuInicial();
    
    //ContagemRegressiva(); // Contagem antes de inicia o jogo
    
    do{ 
                
        desenhoHelicop(lin,col); 
        background(sorteio);
        EscritaPontuacaoRecord();
        
        //printf(" %d ",lin);     
        //printf(" %d ",col);         
        //printf(" %d",x);         
        //printf(" %d",y); 

        //printf(" %d",colisao());
             
        
        barreira();
        Sleep(velocidadeBarreira);
        // printf("%d\n",x);        
        // printf("%d\n",y);
        
        //tecla = getch();
        // printf("%d\n",tecla);
       
        if (colisao()==true){
            encerrarJogo();
        }
        
        // Se o helicóptero encostas em alguma das linhas, encerra o jogo
        if (!(col > sorteio) || !(col + 2 < (26-sorteio-linhaBaixo-1)))
            encerrarJogo();
            
        if (kbhit()){
           tecla = getch();
           if (tecla == 224){
              tecla = getch();
              //teclas: 72 cima, 80 baixo
              
              if(tecla == 72){ // helicóptero vai para cima
                 col = col - 1;
              }
              
              if (tecla == 80){
                 col = col + 1; // helicóptero vai para baixo
              }
           }
        }
        
    }while(tecla!=27); // tecla 27 = ESC
    // system("pause");
    return(0);
}
