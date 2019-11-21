
/* Jogo copter elaborado por Gustavo Melo Poppi da UNICESUMAR, do curso
de An�lise e Desenvolvimento de Sistemas no 2�Semestre. Ano de 2019  

*/

// mudar a cor da letra de digitar o nome, e validar para se n�o colocar nome ele n�o deixa passar
// se apertar ENTER na tela de carregamento ele n�o ir direto para o jogo


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

/* Declara��o das minhas fun��es e/ou m�todos!!*/
void ConfiguracoesIniciais(bool primeiraVez);
int TelaInicialCarregandoJogo();
int TelaMenuInicial();
void IniciarJogo();
int TelaRegras();
int TelaCreditos();
bool EscolhaOpcaoMenuInicial(int opcaoEscolhida);
int SorteioNum(int var);
void RedirecionamentoTeclaDigitada(int tecla);
void Background(int alturaInicia);
void Barreira(bool reniciarBarreira);
void Barreira2(bool reiniciarBarreira);
bool colisao();
void EscritaPontuacaoRecord(bool zerarPontuacao);
void ContagemRegressiva(int posicaoX, int posicaoY, char msg[50], bool contagemRegressiva,int tempoSairDaTela);
void desenhoHelicop(int linha , int coluna);
void EncerrarJogo();
void BotaoEsc(int comprimento, int altura, bool cor, int valorTextColor);
void SalvarRecord(int leitura);


/* Vari�veis globais */
char nomeRecord[50];
int lin = 16, col = 13, record = 0, pontuacao = 0;
int tecla;
int  x, y, w, z, cont;
bool nuncasair = true;
char nome[50];

/* Vari�veis a respeito da barreira */
int velocidadeBarreira = 50, PontuacaoAumentarVelocidade = 630;

/* Vari�veis a respeito do background */
bool zero; // Barreira inicial (Background), onde ela n�o pode ser igual a 0
int sorteio, linhaBaixo;

/* Vari�veis a respeito da tela do carregando jogo */
bool sair; // usei em diversos do e while.


int main(){

    SalvarRecord(0); // 0 ele faz a leitura
    textbackground(9);
    ConfiguracoesIniciais(true); 
    
    do{ 
              
        desenhoHelicop(lin,col); 
        Background(sorteio);
        EscritaPontuacaoRecord(false);             
        
        Barreira(false);
        if (x <= 39 || w < 78)
            Barreira2(false);
            
        Sleep(velocidadeBarreira); 
                            
        // valida��o da colis�o tanto nas barreiras quanto nas linhas de cima ou de baixo. 
        //|| (!(col > sorteio+1) || !(col + 2 < (26-sorteio-linhaBaixo-1))
        if (colisao()==true ){
            Beep(330,500);                
            Sleep(500);
            textbackground(0); // 14 � a cor amarela     
            EscritaPontuacaoRecord(true);    
            SalvarRecord(1); // salva record  
            lin = 16, col = 13, velocidadeBarreira = 50;
            EncerrarJogo();
        }
            
        if (kbhit()){
                     
            if (pontuacao >= PontuacaoAumentarVelocidade && velocidadeBarreira > 2 ){
                velocidadeBarreira = velocidadeBarreira - 2;
                PontuacaoAumentarVelocidade += 390;    
                cont += 3; // para mostrar vel na tela positiva.
           }
           
           if (velocidadeBarreira <= 5)
               velocidadeBarreira = 4;   
                      
           tecla = getch();
           if (tecla == 224){              
              tecla = getch(); //teclas: 72 cima, 80 baixo
              
              if(tecla == 72){ // helic�ptero vai para cima
                 col = col - 1;
              }
              
              if (tecla == 80){
                 col = col + 1; // helic�ptero vai para baixo
              }
           }
        }        
    }while(nuncasair);
}

//----------------------------------------------------------------------
void ConfiguracoesIniciais(bool primeiraVez){

    textbackground(9);  
    setlocale (LC_ALL,"portuguese");
    system("mode 80,25");             
    srand(time(NULL));
    tecla = 0;
    
    if (primeiraVez == true)
        TelaInicialCarregandoJogo();    
        
    TelaMenuInicial();
}

//----------------------------------------------------------------------
int TelaInicialCarregandoJogo(){  
         
    do{
        fflush(stdin);
        sair = true;
        int comprimento = 14, altura = 5;      
        float PorcentagemCarregadoTelaInicial = 1; // var para minha contagem de 0 a 100%     
     
        //x representa linha e y a coluna
        int x = 1, y = 20;
        bool DigitouNome = false, tamanhoNome = false;        
        char situacao[14] = "";
        
        for (x = 0; x < 78; x++){ // la�o de repeti��o para o helic�ptero andar na tela
            textcolor(15);
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
            
            
            do{
                if (!DigitouNome){ // se digitou o nome, n�o entra mais nesses campos, fiz isso pois estou usando o clrscr().
                    textbackground(9);
                    gotoxy(1,1);printf("                                                                                \n");  
                    gotoxy(1,2);printf("                                                                                \n");  
                    
                    gotoxy(comprimento+18,altura+13);printf("Nome do player: \n"); // msg para digitar o nome do player
                    gotoxy(comprimento+21,altura+14);gets(nome);
                    
                    // valida��o do tamanho de caracteres do nome digitado.
                    if (strlen(nome) > 10){
                        gotoxy(comprimento+10,altura+14);printf("                                                                         ");             
                        gotoxy(comprimento+10,altura+14);printf("Nome com 10 caracteres no m�ximo!!\n"); 
                        Sleep(2000);
                        gotoxy(comprimento+10,altura+14);printf("                                                                         "); 
                    } 
                    else{
                        gotoxy(comprimento+21,altura+14);printf("                       ");
                        gotoxy(comprimento+23,altura+14);printf("OK!\n");
                        Sleep(1000);
                        DigitouNome = true;
                        tamanhoNome = true;
                    }
                }                    
            }while(!tamanhoNome);        
            
            if (PorcentagemCarregadoTelaInicial < 100)
                strcpy(situacao,"Carregando..."); 
            else
                strcpy(situacao,"Redirecionando...");            

            gotoxy(comprimento+21,altura+13);printf("%s\n",situacao); // msg carregando ou rediecionando
            gotoxy(comprimento+25,altura+14);printf(" %.0f%% \n",PorcentagemCarregadoTelaInicial); // % carregada atualizada na tela
            
            PorcentagemCarregadoTelaInicial += 1.5;  // aumento da minha % na tela 
            if (PorcentagemCarregadoTelaInicial>=101.5){
                x = 79; // sair do for
                Sleep(500);
                sair = false; // para sair do la�o do e while
            }
        
            /* helic�ptero andando na tela */
            gotoxy(x,y);   printf("   ________");
            gotoxy(x,y+1); printf("x____.-'-.");
            gotoxy(x,y+2); printf("\"\"___.____)");                  
            
            if (y > 72) // para n�o quebrar o helic�ptero na tela
                x = 19;
            Sleep(90);         
            clrscr();tecla = 0; //para se der um ENTER antes da tela de menu n�o acontecer nada.                        
        }
    }while(sair);
    tecla = 0;            
}  
    
//----------------------------------------------------------------------
int TelaMenuInicial(){
    
    textbackground(9); // cor azul claro
    fflush(stdin);
    sair = true;
    
    int tecla = 0, PosicaoSetaEscolha = 12; // 12 � aonde come�ar a minha seta > de escolha 
    //int b = 1, c = 20; 
    //int x = 14, y = 5; 
 
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
        gotoxy(35,16);printf("Cr�ditos\n");
        gotoxy(35,18);printf("Sair\n");
    
        gotoxy(11,23);printf("*Desenvolvido por: Gustavo Melo Poppi, 2� Semestre de ADS\n");
    
    do{           
        if (kbhit()){            
            tecla = getch();    
            if (tecla == 224){
              tecla = getch(); 
                                         
              if (tecla == 72){ // 72 � a seta para CIMA
                  if (PosicaoSetaEscolha == 12){ 
                      PosicaoSetaEscolha = 18; // Valida��o se j� estiver no primeiro menu de cima, ele vai direto para o ultimo
                      goto menuInicial;
                  }
                  else{
                      PosicaoSetaEscolha -= 2;
                      goto menuInicial;
                  }
              }
                 
              if (tecla == 80){ // 80 � a seta para BAIXO
                  if (PosicaoSetaEscolha == 18){ 
                      PosicaoSetaEscolha = 12; // Valida��o se j� estiver no ultimo menu de baixo, ele vai direto para o primeiro
                      goto menuInicial;
                  }
                  else{  
                      PosicaoSetaEscolha += 2;
                      goto menuInicial;
                  }
              }   
           }
           
           if (tecla == 13){ // se der ENTER vai para a fun��o 
               EscolhaOpcaoMenuInicial(PosicaoSetaEscolha); // funcao recebe o valor da posicao da seta e retorna alguma tela ou sair = false  
           }
        }    
    }while(sair);
    IniciarJogo();
}  

//----------------------------------------------------------------------
void IniciarJogo(){    
        
    textbackground(9);// azul claro
    
    Barreira(true);
    Barreira2(true);    
    // sorteio da altura da Barreira inicial (Background), onde ela n�o pode ser igual a 0
    do{
        zero = false;
        SorteioNum(4);
        if (sorteio == 0 || sorteio == 1){
            zero = true;
        }        
    }while(zero);    
    linhaBaixo = rand()%2; // s� para linha de baixo n�o ficar igual a de cima.            
     
    desenhoHelicop(lin,col);
}

//----------------------------------------------------------------------
int TelaRegras(){
    
    textbackground(9); // cor azul claro; 
    
    int tecla = 0, parar = 0;
    bool sair;
    
    do{
        fflush(stdin);
        sair = true;
        int y = 20, cont = 0;
        
        int comprimento = 17, altura = 3; // comprimento e altura do meu texto      
              
            
        for (x = 56; x > 12; x--){ // la�o de repeti��o para o helic�ptero andar na tela   
               
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
            gotoxy(comprimento-3,altura+7);printf("Voc� deve usar as teclas W ou S para desviar das barreias\n");
            gotoxy(comprimento-3,altura+8);printf("e n�o pode enconstar na linha de cima nem na de baixo\n");
            
                     
            gotoxy(12,14); printf("______________________________________________");
            
            // y determinei uma altura para iniciar
            // cont foi para andar na tela de cima para baixo
            gotoxy(20,(y-5)+cont);   printf("   ________");
            gotoxy(20,(y-4)+cont); printf("x____.-'-.");
            gotoxy(20,(y-3)+cont); printf("\"\"___.____)"); 
            
            gotoxy(x,y-3); printf(" _");
            gotoxy(x,y-2); printf("| |");
            gotoxy(x,y-1); printf("| |");
            gotoxy(x,y);   printf("|_|");             
            
            gotoxy(12,24); printf("______________________________________________");            
                                 
            if (cont != 6) // ele conta, hora q chegar em 6 ele ir� parar. Isso � qndo o helic�ptero chegar na posi��o certa na tela ele ficar parado.
                cont += 1;
            
            Sleep(70);
            
            if (kbhit()){            
                tecla = getch();   
                
                if (tecla == 27){ // ENTER
                    x = 11; // para sair do la�o
                    sair = false;     
                }        
            }              
            clrscr();
        }           
        
    }while(sair);  
    
    RedirecionamentoTeclaDigitada(tecla);  
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
    gotoxy(comprimento,altura+4);printf("An�lise e Desenvolvimento de Sistemas.\n");
        
    gotoxy(comprimento,altura+8);printf("Esse projeto foi criado para obten��o parcial da nota\n");
    gotoxy(comprimento,altura+10);printf("do 2� Semestre da mat�ria de Algoritmos e L�gica de Programa��o II, \n");
    gotoxy(comprimento,altura+12);printf("ministrada pelo Professor Edson Moreno na institui��o UNICESUMAR,\n");
    gotoxy(comprimento,altura+14);printf("situada na cidade de Maring� no estado do Paran�.\n");
        
    gotoxy(comprimento,altura+16);printf("Projeto esse que ocorreu no ano de 2019, onde\n");
    gotoxy(comprimento,altura+18);printf("tinhamos que elaborar qualquer jogo em linguagem C.\n");
    gotoxy(comprimento,altura+21);printf("Email: gustavopoppi@hotmail.com\n");
    gotoxy(comprimento,altura+22);printf("Contato: (44)9.9909-0220\n");
    
    
    tecla = getch();
    
    if (tecla == 27)
        RedirecionamentoTeclaDigitada(tecla);    
}

//----------------------------------------------------------------------
bool EscolhaOpcaoMenuInicial(int opcaoEscolhida){

    switch(opcaoEscolhida){
    
        case 12: // 12 valor do X e volta para o jogo
            ContagemRegressiva(33,11,"Iniciando em:",true,0); // Contagem antes de inicia o jogo
            return sair = false;
         break;
        case 14: // vai para p�gina de REGRAS
            return TelaRegras();
         break;
        case 16: // vai para p�gina de CR�DITOS
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
    
    sorteio = rand()%var; // aqui que fa�o o sorteio da altura da linha do campo 
    return sorteio;
}  

//----------------------------------------------------------------------
void RedirecionamentoTeclaDigitada(int tecla){

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
void Background(int alturaInicia){ // cria��o das minhas linhas de cima e de baixo    
     
     for (int x = 1; x<80; x++){
         
         // linha da cima, o +1 � para nunca come�ar com a linha tamanho 1, pois se n�o ir� ter conflito com o texto
         gotoxy(x,alturaInicia+1); printf("_");
         
         // linha de baixo, onde 25 � a altura m�xima
         gotoxy(x,(25-alturaInicia-linhaBaixo)); printf("_");
     }       
}

//----------------------------------------------------------------------
void Barreira(bool reiniciarBarreira){    
     
     textcolor(15); // cor branca
     
     // Condi��es para estar dentro do "mapa", caso contr�rio ele sorteio de novo
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
     // o reniciar barreira � porque tava tendo problema quando batia e reniciava
     if (x < 1 || reiniciarBarreira == true){
        x = 78;
        y = (rand()%24)+1;
     }    
}

//----------------------------------------------------------------------
void Barreira2(bool reiniciarBarreira){   
     
     textcolor(15); // cor branca
     
     // Condi��es para estar dentro do "mapa"
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
     
     // x � o valor sorteado no plano X (comprimento)
     // y � o valor sorteado no plano Y (altura)
     // lin � a linha do helic�ptero
     // col � a coluna do helic�ptero
     
     // +9 pq � o comprimento do helic�ptero
     if ((x >= lin) && (x <= (lin+9)))
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
     
     // verifica��o de colis�o da linha de cima ou de baixo
     if (!(col > sorteio+1) || !(col + 2 < (26-sorteio-linhaBaixo-1)))
        return true;
     else
        return false; 
}

//----------------------------------------------------------------------
void EscritaPontuacaoRecord(bool zerarPontuacao){

    if (zerarPontuacao)
        pontuacao = 0;
        
    gotoxy(2,1); printf("Player: %s",nome);
    gotoxy(2,2); printf("Velocidade: %d",velocidadeBarreira-49+cont);    
    gotoxy(35,1); printf("Pontua��o: %d",pontuacao);
    gotoxy(35,2); printf("Record: %s - %d pontos",nomeRecord,record);
    
    //cont += 1; // var velocidade vai cair de 3 em 3, ent�o somei 6 para na tela aumentar e n�o diminuir o valor
    
    pontuacao = pontuacao + 3;
    if (pontuacao >= record ){
       record = pontuacao;    
       strcpy(nomeRecord,nome);
    }    
}

//----------------------------------------------------------------------
void ContagemRegressiva(int posicaoX, int posicaoY, char msg[50], bool contagemRegressiva,int tempoSairDaTela){

    bool sair = true;
    int x;
    
    clrscr();
    gotoxy(posicaoX,posicaoY); printf("%s",msg);
    
    if (contagemRegressiva){ // caso queira a contagem, caso contr�rio s� ir� apresentar a mensagem
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

    textbackground(9);// cor azul clara  

    clrscr();// limpa a tela

    gotoxy(linha,coluna);   printf("   ________");
    gotoxy(linha,coluna+1); printf("x____.-'-.");
    gotoxy(linha,coluna+2); printf("\"\"___.____)");
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
void BotaoEsc(int comprimento, int altura, bool cor, int valorTextColor){
    
    if (cor)
       textcolor(valorTextColor);
       
    gotoxy(comprimento,altura);printf("  ESC = Voltar\n");
}

//------------------------------------------------------------------
void SalvarRecord(int leitura){ //0 - leitura / 1 - gravacao
FILE *file;
    file = fopen("Record_Copter.txt", "r");     
    if (file == NULL || leitura==1){
       file = fopen("Record_Copter.txt", "w"); 
       fprintf(file,"%d\n",record);  
       fprintf(file,"%s\n",nomeRecord);
    }   
    else
       fscanf(file,"%i",&record);
       fscanf(file,"%s",&nomeRecord);       
    
    fclose(file);
}

