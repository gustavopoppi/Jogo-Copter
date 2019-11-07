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
int velocidadeBarreira = 50; 


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
     
     textcolor(7); // cor branca
     if ((y > sorteio) && (y + 2 < (25-sorteio-linhaBaixo-1))){ // Condições para estar dentro do "mapa"
         gotoxy(x,y);   printf(" _");
         //gotoxy(x,y+1); printf("| |");
         //gotoxy(x,y+2); printf("|_|");
     }else{
         sorteiaAltura();  
     }

     // Faz a barreira andar da direita para a esquerda
     x --;

     
     // Se o valor do X for menor que 0 ele passa fora da tela
     if (x<1){
        sorteiaAltura();
     }         
}

//----------------------------------------------------------------------
bool colisao(){
     
     // lin é a linha do helicóptero
     // col é a coluna do helicóptero
     // x é o valor sorteado no plano X (comprimento)
     // y é o valor sorteado no plano Y (altura)
     
     if ((x >= lin) && (x <= (lin+9)) && (y >= col) && (y <= (col+2)))
         return true;
     else
         return false;

}

//----------------------------------------------------------------------
void desenhoHelicop(int linha , int coluna){

    textbackground(9);// cor azul clara  

    clrscr();// limpa a tela
    gotoxy(linha,coluna);   printf("   ________");
    gotoxy(linha,coluna+1); printf("x____.-'-.");
    gotoxy(linha,coluna+2); printf("\"\"___.____)");
}

// pinta a tela de verde
void telaVerde(int alturaInicia){
    // laço de repetição onde o y vai até ser igual o número inicial da altura
    // e o x eu fiz para percorrer cada valor de linha, onde vai de 1 até 80 (tela 80x25)
    // de cima
    for (int y = 2; y <= alturaInicia; y++){
        for (int x = 1; x <= 80; x++){
            gotoxy(x,y);
            textbackground(2); 
            textcolor(2);
            printf("'");
        }
    }
    for (int x = 1; x<=80; x++){
              gotoxy(x,1);
              textbackground(2); 
              textcolor(2);
              printf("'");
    }

    
    // de baixo
    for (int x = 1; x < 69; x++){
        gotoxy(x,(25-alturaInicia-linhaBaixo));
        textbackground(2); 
        textcolor(2);
        printf("'");
    }
    
    for (int y = 25; y >= (25-alturaInicia-linhaBaixo+1); y--){
        for (int x = 1; x <= 80; x++){
            gotoxy(x,y);
            textbackground(2); 
            textcolor(2);
            printf("'");
       }
    }

}

int main(){
    // X = 80
    // Y = 25   
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
    
    
    do{ 
        desenhoHelicop(lin,col); 
        background(sorteio);

        //telaVerde(sorteio);
        
        //printf("%d",lin);     
        //printf("%d",col);         
        //printf(" %d",y);         
        //printf(" %d",x); 
        //printf(" %d",colisao());
             
        
        barreira(x,y);
        Sleep(velocidadeBarreira);
        // printf("%d\n",x);        
        // printf("%d\n",y);
        
        //tecla = getch();
        // printf("%d\n",tecla);
       
        if (colisao()==true){
            system("pause");
        }
        
        if (kbhit()){
           tecla = getch();
           if (tecla == 224){
              tecla = getch();
              //teclas: 72 cima, 80 baixo
              
              if(tecla == 72){ // helicóptero vai para cima
                 col = col - 1;
                 //system("pause");
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
