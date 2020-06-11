#define SDL_MAIN_HANDLED
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>
#include <conio.h>
#include <stdbool.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>


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


int main (int argv, char** args)
{
    int cx, cy, gx, gy;
    bool runnig = true;

    SDL_Init(SDL_INIT_VIDEO);
    IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG);

    SDL_Window *window = SDL_CreateWindow("Simulador de Penaltis", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);


    SDL_Surface *image = IMG_Load("images/intro.png");
    SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
    SDL_FreeSurface(image);
    SDL_Rect texture_destination;
    texture_destination.x = 1;
    texture_destination.y = 0;
    texture_destination.w = 623;
    texture_destination.h = 313;

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
    SDL_RenderPresent(renderer);

    Sleep(5000);
    while(runnig)
    {
        SDL_Event event;
        // caso capture algum evento
        if (SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_MOUSEBUTTONDOWN:
                    if(event.button.button == SDL_BUTTON_LEFT)
                    {
                        SDL_Log("Click direito reconhecido!\n Iniciando chutes ao GOL!");

                        //Imagem inicial

                        SDL_Surface *image = IMG_Load("images/penalti.jpg");
                        SDL_Texture *image_texture = SDL_CreateTextureFromSurface(renderer, image);
                        SDL_FreeSurface(image);
                        SDL_Rect texture_destination;

                        texture_destination.x = 1;
                        texture_destination.y = 0;
                        texture_destination.w = 623;
                        texture_destination.h = 313;

                        SDL_RenderClear(renderer);
                        SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
                        SDL_RenderPresent(renderer);

                        Sleep(1500);

                        // Gerando chutes ao gol até reconhecer click do mouse
                        pilha cobranca;
                        srand(time(0));
                        create(&cobranca);

                        while(runnig)
                        {
                            geraCoordenadas(&cx, &cy, &gx, &gy);
                            pushCobranca(&cobranca, cx, cy, gx, gy);
                            SDL_Event event2;

                            // verifica_cobranca retorna 1 (chute fora), 2 (defesa), 3 (gol) e 0 para nenhuma das anteriores.
                            switch (verifica_cobranca (cx, cy, gx, gy))
                            {
                                case 1:
                                    printf("TELA CHUTE PARA FORA");
                                    image = IMG_Load("images/bolafora.png");
                                break;
                                case 2:
                                    printf("TELA DEFESA");
                                    image = IMG_Load("images/defesa.png");
                                break;
                                case 3:
                                    printf("TELA GOL");
                                    image = IMG_Load("images/gool.png");
                                break;
                            } //Fim Switch

                            image_texture = SDL_CreateTextureFromSurface(renderer, image);

                            SDL_RenderClear(renderer);
                            SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
                            SDL_RenderPresent(renderer);

                            // Para execução de chutes ao gol ao detectar click do mouse
                            if(SDL_PollEvent(&event2))
                                if(event2.type == SDL_MOUSEBUTTONDOWN)
                                    if(event.button.button == SDL_BUTTON_LEFT)
                                        runnig = false;

                            Sleep(1500);
                            printf("\n\nAguardando click para PARAR...");
                        }//Fim While

                    } //Fim if
                break;

                case SDL_QUIT:
                    SDL_DestroyTexture(image_texture);
                    IMG_Quit();
                    SDL_DestroyRenderer(renderer);
                    SDL_DestroyWindow(window);
                    SDL_Quit();
                    return 0;
                break;
            } //Fim switch
        } //Fim if 93002874
    } //Fim While

    // Mostrando menu final (modo grafico)
    image = IMG_Load("images/menu.png");
    image_texture = SDL_CreateTextureFromSurface(renderer, image);

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, image_texture, NULL, &texture_destination);
    SDL_RenderPresent(renderer);

    // Mostrando menu final (terminal)
    getch();
} //Fim main()


//======================FUNÇÕES============================

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
    {
        printf(" Chute para fora!\n");
        return 1;
    }
    else if (cx<0 || cx>3)
    {
        printf(" Chute para fora!\n");
        return 1;
    }
    else if(cx == gx && cy == gy)
    {
        printf(" Defesa do goleiro!\n");
        return 2;
    }
    else
    {
        printf(" Gol!\n");
        return 3;
    }
    return 0;
}
