
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

struct no
{
    int cont;              // contador de eventos
    int chute_x, chute_y; //coordenadas de chute
    int gol_x, gol_y;     // coordenadas de posicionamento do goleiro
    char resultado[30];   //variavel que recebe o resultado da cobranca - gol, defesa ou chute para fora.
    struct no *prox;
};

typedef struct
{
    struct no *inicio;
    struct no *fim;
} fila;

void create(fila *s); //funcao para criar a fila
int pushCobranca(fila *s, int cx, int cy, int gx, int gy, int cont); //cx = coord chute x, cy = coord chute y, gx = coord gol x, gy = coord gol y
void mostraCobranca(int cx, int cy, int gx, int gy, int cont, int resultado); //exibe os pontos de chute e goleiro. Por fim, exibe qual o resultado.
int isEmpty (fila s); //ver se fila esta vazia
void geraCoordenadas(int *cx, int *cy, int *gx, int *gy); //funcao que gera as coordenadas para o chute e para posicao do goleiro
void mostrafila (fila s); //exibir as filas
int verifica_cobranca (int cx, int cy, int gx, int gy); //determina resultado da cobranca de acordo com as coordenadas e retorna valor
void imprimeGOL(); //exibicao grafica dos pontos de interesse no simulador - VERIFIQUEM AQUI
void exibeEstatisticas(int cont, int contFora, int contDefesa, int contGol); //exibir estatisticas gerais de simulacao
void teclaContinuar(); //pressione qualquer tecla para continuar + getch

int main ()
{
    int cx, cy, gx, gy, opcao;
    int cont=0, contFora = 0, contDefesa = 0, contGol = 0;

    fila cobranca;
    fila fora;
    fila defesa;
    fila gol;

    srand(time(0)); //semente para gerar numeros aleatorios

    create(&cobranca);
    create(&fora);
    create(&defesa);
    create(&gol);

    printf("\n Simulador de cobrancas de penalti\n\n");
    teclaContinuar();
    system("cls"); //funçao do windows para limpar a tela

    do //loop de execuçao do codigo de cobrancas e armazenamento dos dados nas filas
    {
        cont++; //contador de cobrancas
        geraCoordenadas(&cx, &cy, &gx, &gy); //chamada da funcao que gera randomicamente as coordenadas de chute e goleiro

        pushCobranca(&cobranca, cx, cy, gx, gy, cont); //insere os pontos na fila cobranca

        if(verifica_cobranca (cx, cy, gx, gy)==-1) //verifica se foi para fora
        {
            pushCobranca(&fora, cx, cy, gx, gy, cont);
            mostraCobranca(cx, cy, gx, gy, cont, -1);
            contFora++; //contador de chutes fora
        }

        if(verifica_cobranca(cx, cy, gx, gy)==0) //verifica se foi defesa
        {
            pushCobranca(&defesa, cx, cy, gx, gy, cont);
            mostraCobranca(cx, cy, gx, gy, cont, 0);
            contDefesa++; //contador de defesas
        }

        if(verifica_cobranca(cx, cy, gx, gy)==1) //verifica se foi gol
        {
            pushCobranca(&gol, cx, cy, gx, gy, cont);
            mostraCobranca(cx, cy, gx, gy, cont, 1);
            contGol++;  //contador de gols
        }

        printf(" Tecle para parar...\n\n");

        Sleep(1000); //funcao para pausar execucao - no caso, pausa por 1 segundo

    }while(!kbhit()); // kbhit = ler tecla qualquer do teclado. Ou seja, executa o loop enquanto nenhuma tecla for apertada.


    do //loop de execuçao do menu
        {
            system("cls");
            printf("\n Menu de Dados\n");
            printf(" 1 - Explicacao do modo de funcionamento da simulacao\n");
            printf(" 2 - Ver a lista completa de cobrancas\n");
            printf(" 3 - Ver a lista de Acertos\n");
            printf(" 4 - Ver a lista de Defesas\n");
            printf(" 5 - Ver a lista de Erros\n");
            printf(" 6 - Ver as estatisticas gerais\n");
            printf(" 9 - Sair do programa\n");
            printf(" Digite a opcao desejada:");
            scanf("%d", &opcao);
            switch(opcao)
                {
                    case 1:
                        system("cls");
                        imprimeGOL();
                        teclaContinuar();
                        break;
                    case 2:
                        system("cls");
                        mostrafila(cobranca);
                        teclaContinuar();
                        break;
                    case 3:
                        system("cls");
                        mostrafila(gol);
                        teclaContinuar();
                        break;
                    case 4:
                        system("cls");
                        mostrafila(defesa);
                        teclaContinuar();
                        break;
                    case 5:
                        system("cls");
                        mostrafila(fora);
                        teclaContinuar();
                        break;
                    case 6:
                        system("cls");
                        exibeEstatisticas(cont, contFora, contDefesa, contGol);
                        teclaContinuar();
                        break;
                    case 9:
                        printf("\n Saindo...\n");
                        break;
                    default:
                        printf(" Opcao inexistente. retornando ao menu...\n");
                        Sleep(1500);
                        break;
                }
        }while(opcao!=9);

    printf("\n Ate mais!\n");
    Sleep(1500);

    return 0;
    }

//funções

void create(fila *s)
{
s->inicio = NULL;
s->fim = NULL;
}

int pushCobranca(fila *s, int cx, int cy, int gx, int gy, int cont)
{
struct no *aux;
    aux =(struct no *)malloc(sizeof(struct no));
    if (aux==NULL)
        return 0;

    aux->cont = cont;
    aux->chute_x=cx;
    aux->chute_y=cy;
    aux->gol_x=gx;
    aux->gol_y=gy;
    //aux->prox= s->topo;
    //s->topo=aux;
    if(verifica_cobranca (cx, cy, gx, gy)==-1) //usa funcao verifica_cobranca para determinar o resultado e copiar a string referente a variavel de resultado na fila.
        strcpy(aux->resultado, "Chute pra fora");
    else if(verifica_cobranca (cx, cy, gx, gy)==0)
        strcpy(aux->resultado, "Defesa do goleiro");
    else
        strcpy(aux->resultado, "Gol!");


     aux->prox=NULL;
    if (s->inicio==NULL)
        s->inicio=aux;
    if (s->fim!=NULL)
        s->fim->prox=aux;
    s->fim = aux;

    return 1;
}
int isEmpty (fila s)
{

    if (s.inicio == NULL)
        return 1;
    return 0;
}

void geraCoordenadas(int *cx, int *cy, int *gx, int *gy) //gera valores aleatorios dentro dos limites estabelecidos para execuçao do simulador
{


    *cx = rand()%5;
    *cy = rand()%3;

    *gx = rand()%4;
    if(*gx<1) //if usado caso o valor gerado para goleiro x seja melhor que 1, oq e impossivel visto que goleiro deve estar entre 1 e 3 do eixo x.
        *gx++;

    *gy = rand()%2;


}

void mostrafila (fila s)
{
    struct no *aux;
    aux = s.inicio;

    if (aux == NULL)
        printf(" Sem dados a exibir.\n");
    else
    {
        while(aux != NULL)
        {
            printf(" Cobranca No. %d:\n Chute em:  (%d;%d)\n", aux->cont, aux->chute_x, aux->chute_y);
            printf(" Goleiro em (%d;%d)\n", aux->gol_x, aux->gol_y);
            printf(" Resultado: %s!\n\n", aux->resultado);
            aux = aux->prox;

        }
    }
}

int verifica_cobranca (int cx, int cy, int gx, int gy) //verifica o resultado da cobranca de acordo com posicao do chute e do goleiro
{

    if (cy == 2)
    {
        //Chute para fora;
        return -1;
    }
    else if (cx<0 || cx>3)
    {
        //Chute para fora
        return -1;
    }
    else if(cx == gx && cy == gy)
    {
        //Defesa do goleiro
        return 0;
    }

    else //Gol

    return 1;
}

void mostraCobranca(int cx, int cy, int gx, int gy, int cont, int resultado) //exibe o resultado da cobranca
{
    printf(" Cobranca No. %d\n", cont);
    printf(" Chute em   (%d ; %d)\n", cx, cy);
    printf(" Goleiro em (%d ; %d)\n", gx,gy);
    if(resultado == -1)
        printf(" Resultado: Chute pra Fora!\n");
    else if (resultado == 0)
        printf(" Resultado: Defesa do Goleiro!\n");
    else
        printf(" Resultado: Gol!\n");

}

void imprimeGOL() //exibe o funcionamento das coordenadas do simulador. **OLHEM ISSO**
{
    printf(R"EOF(
 Eis a determinacao do posicionamento no gol:

 (0;2) (1;2)(2;2)(3;2) (4;2)
       ---------------
 (0;1)|(1;1)(2;1)(3;1)|(4;1)
 (0;0)|(1;0)(2;0)(3;0)|(4;0)

)EOF");
}

void exibeEstatisticas(int cont, int contFora, int contDefesa, int contGol) //gera os dados das estatisticas do simulador. calculos feitos direto nos printf para economizar variaveis
{
    float contFloat; //usar conversao para variavel float pra nao ter erro na divisao entre inteiros
    contFloat = cont;

    printf("\n Estatisticas gerais de simulacao\n\n");
    printf(" Total de Cobrancas: %d\n Gols Feitos: %d\n Defesas: %d\n Chutes Fora: %d\n",cont, contGol, contDefesa, contFora);
    printf(" Porcentagem de acertos: %.2f%%\n", (contGol/contFloat)*100);
    printf(" Porcentagem de Defesas: %.2f%%\n", (contDefesa/contFloat)*100);
    printf(" Porcentagem de Chutes para Fora: %.2f%%\n\n", (contFora/contFloat)*100);
}

void teclaContinuar() //mensagem de execuçao em todo fim de tarefa.
{
    printf(" Digite qualquer tecla para continuar: ");
    _getch();
}
