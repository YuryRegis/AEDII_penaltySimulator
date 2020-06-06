/*
Programa para criação de um simulador de cobranças de penalti.

O código irá gerar aleatoriamente valores-base para definir a cobrança: gol, defesa ou chute para fora.

Ao final, será apresentado a posição de cada chute e cada movimento do "goleiro", bem como um cálculo
com estatísticas de acerto e de erro, bem como local médio dos chutes.

- Criar pilha para definir chutes e defesas
- Criar fila para definir acertos
- Criar fila para definir erros
- Criar váriaveis para gerar estatística geral


*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

struct no
{
    int chute_x, chute_y; //coordenadas de chute
    int gol_x, gol_y; // coordenadas de posicionamento do goleiro
    struct no *prox;
};

typedef struct
{
    struct no *topo;
} pilha;

void create(pilha *s);
int pushCobranca(pilha *s, int cx, int cy, int gx, int gy); //cx = coord chute x, cy = coord chute y, gx = coord gol x, gy = coord gol y
int isEmpty (pilha s);
void geraCoordenadas(int *cx, int *cy, int *gx, int *gy);
void mostraPilha (pilha s);
int verifica_cobranca (int cx, int cy, int gx, int gy);


int main ()
{
    int cx, cy, gx, gy;

    pilha cobranca;

    create(&cobranca);

    printf("\n Simulador de cobrancas de penalti\n\n");
    printf("Digite qualquer tecla para comecar: \n\n");
    getch();

    do
    {
        geraCoordenadas(&cx, &cy, &gx, &gy);
        verifica_cobranca (cx, cy, gx, gy);
        pushCobranca(&cobranca, cx, cy, gx, gy);
        printf(" Tecle para parar...\n\n");

        Sleep(1000);

    }while(!kbhit());
    getch();

    printf(" Digite qualquer tecla para sair: \n");
    getch();

    return 0;
    }





//funções
void create(pilha *s)
{
s->topo = NULL;
}

int pushCobranca(pilha *s, int cx, int cy, int gx, int gy)
{
struct no *aux;
    aux =(struct no *)malloc(sizeof(struct no));
    if (aux==NULL)
        return 0;

    aux->chute_x=cx;
    aux->chute_y=cy;
    aux->gol_x=gx;
    aux->gol_y=gy;
    aux->prox= s->topo;
    s->topo=aux;
    printf(" Chute em (%d ; %d)\n", aux->chute_x, aux->chute_y);
    printf(" Goleiro em (%d ; %d)\n\n", aux->gol_x, aux->gol_y);
    return 1;
}
int isEmpty (pilha s)
{

    if (s.topo == NULL)
        return 1;
    return 0;
}

void geraCoordenadas(int *cx, int *cy, int *gx, int *gy)
{
    //srand(time(NULL)); //gerando numeros aleatorios porem com ordem crescente. não funciona.

    *cx = rand()%5;
    *cy = rand()%3;

    *gx = rand()%4;
    if(*gx<1)
        *gx++;
    /*while (*gx<1)
        {
        *gx = rand()%4;
        }*/
    *gy = rand()%2;


}

void mostraPilha (pilha s)
{

}

int verifica_cobranca (int cx, int cy, int gx, int gy)
{

    if (cy == 2)
        printf(" Chute para fora!\n");
    else if (cx<0 || cx>3)
        printf(" Chute para fora!\n");
    else if(cx == gx && cy == gy)
        printf(" Defesa do goleiro!\n");
    else printf(" Gol!\n");

    return 0;
}
