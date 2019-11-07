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

   Validações:
       - Helicoptero não pode passar por cima da barreira e do background;
       - Barreira não pode sair em cima do background;
       

*/

/* Jogo copter elaborado por Gustavo Melo Poppi da UNICESUMAR, do curso
de Análise e Desenvolvimento de Sistemas no 2ºSemestre. Ano de 2019  */


int lin = 16, col = 13, record = 0, pontuacao = 0;
int mapaInicioCima, mapaInicioBaixo;
int tecla;
int  x, y;


/* Variaveis a respeito da barreira */
int velocidadeBarreira = 2; 


/* Variaveis a respeito do background */
bool zero;
int sorteio, linhaBaixo;



//----------------------------------------------------------------------
int sorteioNum(int var){
    
    sorteio = rand()%var;      
    return sorteio;
}

//----------------------------------------------------------------------
void sorteiaAltura(){
     
     x = 78;
     y = (rand()%24)+1;          
}

//----------------------------------------------------------------------
void background(int alturaInicia){
     bool zero;     
     
     for (int x = 1; x<80; x++){
         
         // linha da cima
         gotoxy(x,alturaInicia); printf("_");
         
         // linha de baixo, onde 25 é a altura máxima
         gotoxy(x,(25-alturaInicia-linhaBaixo)); printf("_");
         
         
         // implementar um novo cenário de fundo, sem ser apenas uma reta
         /*gotoxy(6,5); printf("\\");
         gotoxy(7,5); printf("_/");*/
     }     
}

//----------------------------------------------------------------------
void barreira(int barreiraX, int barreiraY){
     int col1,col2,col3;
     // acrescentar mais tipos de barreiras e colocar como switch.. case(0),  case(1)
     
     if ((y > sorteio) && (y + 2 < (25-sorteio-linhaBaixo))){ // Condições para estar dentro do "mapa"
         gotoxy(x,y);   printf(" _");
         gotoxy(x,y+1); printf("| |");
         gotoxy(x,y+2); printf("|_|");
     }else{
         sorteiaAltura();  
     }

     x = x - velocidadeBarreira;
     
     // Se o valor do X for menor que 0 ele passa fora da tela
     if (x<1){
        sorteiaAltura();
     }         
}

//----------------------------------------------------------------------
bool colisao(){
     
     if (((col+2) >= y) && (col <= (y+2) && ((lin+12) == x)))
         return true;
     else
         return false;
}

//----------------------------------------------------------------------
void desenhoHelicop(int linha , int coluna){

    textcolor(2);
    textbackground(1);    
    clrscr();
    gotoxy(linha,coluna);   printf("   __________");
    gotoxy(linha,coluna+1); printf("x____.-'-.");
    gotoxy(linha,coluna+2); printf("\"\"___.____)");
}

int main(){
    // X = 80
    // Y = 25   
    //system("mode 80,25");             
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
    
    
    do{    
        desenhoHelicop(lin,col);  
        printf("%d",lin);     
        printf("%d",col);         
        printf(" %d",y);         
        printf(" %d",x);
             
        background(sorteio);
        barreira(x,y);
        Sleep(100);
        // printf("%d\n",x);        
        // printf("%d\n",y);
        
        //tecla = getch();
        // printf("%d\n",tecla);
       
        if (colisao()==true){
            printf("GAMEOVER");
            scanf("");
        }
        
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
