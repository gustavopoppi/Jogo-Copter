

#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <string.h>
#include <conio.h>
#include <conio.c>
#include <time.h>
#include <ctype.h>
#include <windows.h>

/* Jogo copter elaborado por Gustavo Melo Poppi da UNICESUMAR, do curso
de Análise e Desenvolvimento de Sistemas no 2ºSemestre. Ano de 2019  */


int lin = 16, col = 13, record = 0, pontuacao = 0;
int mapaInicioCima, mapaInicioBaixo;
int  x, y;
int tecla;

void desenhoHelicop(int linha , int coluna){

    textcolor(2);
    textbackground(1);    
    clrscr();
    gotoxy(linha,coluna);   printf("   __________");
    gotoxy(linha,coluna+1); printf("x____.-'-.");
    gotoxy(linha,coluna+2); printf("\"\"___.____)");
}

void sorteiaAltura(){
     
     x = 78;
     y = (rand()%24)+1;
          
}

void barreira(int barreiraX, int barreiraY){
     int col1,col2,col3;
     // acrescentar mais tipos de barreiras e colocar como switch.. case(0),  case(1)
     
     
     gotoxy(x,y);   printf(" _");
     gotoxy(x,y+1); printf("| |");
     gotoxy(x,y+2); printf("|_|");
     
     x = x - 1;
     
     if (x<1){
        sorteiaAltura();
     }         
}


void background(){
     
     
     
}

int main(){
    // X = 80
    // Y = 25   
    //system("mode 80,25");             
    srand(time(NULL));
    tecla = 0;
     
    desenhoHelicop(lin,col); 
    sorteiaAltura();
    
    do{    
        desenhoHelicop(lin,col);  
             
        barreira(x,y);
        Sleep(100);
        // printf("%d\n",x);        
        // printf("%d\n",y);
        
        //tecla = getch();
        // printf("%d\n",tecla);
       
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
