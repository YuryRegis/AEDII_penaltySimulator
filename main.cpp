
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
    char resultado[30];
    struct no *prox;
};

typedef struct
{
    struct no *inicio;
    struct no *fim;
} fila;

void create(fila *s);
int pushCobranca(fila *s, int cx, int cy, int gx, int gy, int cont); //cx = coord chute x, cy = coord chute y, gx = coord gol x, gy = coord gol y
void mostraCobranca(int cx, int cy, int gx, int gy, int cont, int resultado);
int isEmpty (fila s);
void geraCoordenadas(int *cx, int *cy, int *gx, int *gy);
void mostrafila (fila s);
int verifica_cobranca (int cx, int cy, int gx, int gy);
void imprimeGOL();


int main ()
{
    int cx, cy, gx, gy, cont=0, opcao;

    fila cobranca;
    fila fora;
    fila defesa;
    fila gol;

    srand(time(0));

    create(&cobranca);
    create(&fora);
    create(&defesa);
    create(&gol);

    printf("\n Simulador de cobrancas de penalti\n\n");
    imprimeGOL();
    printf(" Digite qualquer tecla para comecar: \n\n");
    _getch();

    do
    {
        cont++;
        geraCoordenadas(&cx, &cy, &gx, &gy);
        pushCobranca(&cobranca, cx, cy, gx, gy, cont);

        if(verifica_cobranca (cx, cy, gx, gy)==-1)
        {
            pushCobranca(&fora, cx, cy, gx, gy, cont);
            mostraCobranca(cx, cy, gx, gy, cont, -1);
        }

        if(verifica_cobranca(cx, cy, gx, gy)==0)
        {
            pushCobranca(&defesa, cx, cy, gx, gy, cont);
            mostraCobranca(cx, cy, gx, gy, cont, 0);
        }

        if(verifica_cobranca(cx, cy, gx, gy)==1)
        {
            pushCobranca(&gol, cx, cy, gx, gy, cont);
            mostraCobranca(cx, cy, gx, gy, cont, 1);
        }

        printf(" Tecle para parar...\n\n");

        Sleep(1000);

    }while(!kbhit());


    do
        {
            system("cls");
            printf("\n Menu de Dados\n");
            printf(" 1 - Ver a lista completa de cobrancas\n");
            printf(" 2 - Ver a lista de Erros\n");
            printf(" 3 - Ver a lista de Acertos\n");
            printf(" 4 - Ver a lista de Defesas\n");
            printf(" 5 - Ver as estatisticas completas\n");
            printf(" 9 - Sair do programa\n");
            printf(" Digite a opcao desejada: \n");
            scanf("%d", &opcao);
            switch(opcao)
                {
                    case 1:
                        mostrafila(cobranca);
                        system("pause");
                        break;
                    case 2:
                        mostrafila(fora);
                        system("pause");
                        break;
                    case 3:
                        mostrafila(gol);
                        system("pause");
                        break;
                    case 4:
                        mostrafila(defesa);
                        system("pause");
                        break;
                    case 5:
                        printf("Ainda nao fiz.\n");
                        system("pause");
                        break;
                    case 9:
                        printf(" Saindo...\n");
                        break;
                    default:
                        printf(" Opcao inexistente. Saindo...\n");
                        break;
                }
        }while(opcao!=9);

    printf("\nAte mais!\n");
    Sleep(3000);

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
    if(verifica_cobranca (cx, cy, gx, gy)==-1)
        strcpy(aux->resultado, "Chute pra fora");
    else if(verifica_cobranca (cx, cy, gx, gy)==0)
        strcpy(aux->resultado, "Defesa do goleiro");
    else
        strcpy(aux->resultado, "Gol!");

    //printf(" Cobranca No. %d\n", aux->cont);
    //printf(" Chute em (%d ; %d)\n", aux->chute_x, aux->chute_y);
    //printf(" Goleiro em (%d ; %d)\n", aux->gol_x, aux->gol_y);
    //printf(" Resultado: %s!\n", aux->resultado);

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

void geraCoordenadas(int *cx, int *cy, int *gx, int *gy)
{


    *cx = rand()%5;
    *cy = rand()%3;

    *gx = rand()%4;
    if(*gx<1)
        *gx++;

    *gy = rand()%2;


}

void mostrafila (fila s)
{
    struct no *aux;
    aux = s.inicio;

    if (aux == NULL)
        printf("Sem dados a exibir.\n");
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

int verifica_cobranca (int cx, int cy, int gx, int gy)
{

    if (cy == 2)
    {
        //printf(" Chute para fora!\n");
        return -1;
    }
    else if (cx<0 || cx>3)
    {
        //printf(" Chute para fora!\n");
        return -1;
    }
    else if(cx == gx && cy == gy)
    {
        //printf(" Defesa do goleiro!\n");
        return 0;
    }

    else //printf(" Gol!\n");

    return 1;
}

void mostraCobranca(int cx, int cy, int gx, int gy, int cont, int resultado)
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




void imprimeGOL()
{
    printf(R"EOF(
 Eis a determinacao do posicionamento no gol:

 (0;2) (1;2)(2;2)(3;2) (4;2)
       ---------------
 (0;1)|(1;1)(2;1)(3;1)|(4;1)
 (0;0)|(1;0)(2;0)(3;0)|(4;0)

)EOF");
}
