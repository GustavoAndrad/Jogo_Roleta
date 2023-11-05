#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#define T 8 //OS ESTILOS DA ROLETA FUNCIONAM COM ESSE VALOR PREDEFINIDO


struct _Casa_Roleta{
    int valor;
    struct _Casa_Roleta * prox;
};
typedef struct _Casa_Roleta *noPtr;

void preencheRoleta(noPtr * i, int qnt){
    srand(time(NULL));
    for(int j=0;j<qnt;j++){
        noPtr p = (noPtr) malloc(sizeof(struct _Casa_Roleta));
        
        int numeroAleatorio = rand() % 9 + 1;

        p->valor = numeroAleatorio;

        if ((*i)==NULL) {
            p->prox = p;
            *i = p;
        } else {
            p->prox = (*i)->prox;
            (*i)->prox = p;
        }
    }
}

/*a roleta é gerada como uma lista circular, mas é escrita e estlizada com a ajuda de um array*/
void mostraRoleta(noPtr i, int q)
{
    int roleta[q];
    if (i!=NULL)
    {
        for (int j = 0; j < q; j++){
            //printf(" - %d - ", i->valor);
            roleta[j] = i->valor;
            i = i->prox;
        }
        // roleta estilizada
        printf("\n\n======== \U0001F3A1   ROLETA   \U0001F3A1 ========\n");
        printf("\n\t\t\033[1;31m%d\033[0m\t\t\n\t\033[1;32m%d\033[0m\t\t\033[1;32m%d\033[0m\t\n\033[1;33m%d\033[0m\t\t.\t\t\033[1;33m%d\033[0m\t\n\t\033[1;32m%d\033[0m\t\t\033[1;32m%d\033[0m\t\n\t\t\033[1;31m%d\033[0m\n\n",
            roleta[0], roleta[7], roleta[1], roleta[6], roleta[2], roleta[5], roleta[3], roleta[4]);    
        printf("==================================\n");
       }
    else{
        printf("\n\nRoleta Vazia");
    }
}

/* impulso é multiplicado por um número aleatorio (1 - 3) para evitar previsibilidade. e o ponteiro avança -impulso- vezes*/
int rodaRoleta(noPtr i, int impulso){
    srand(time(NULL));
    int numeroAleatorio = rand() % 3 + 1;
    impulso = impulso * numeroAleatorio;

    if (i!=NULL)
    {
        printf("\nRODANDO ");
        for (int j = 0; j < impulso; j++){
            printf("\U0001F528\U0001F529");
            usleep(400000);
            i = i->prox;
        }
        return i->valor;
    }
    else{
        printf("\n\nRoleta vazia!");
    }
    return 0;
}

int main(){
    noPtr topo = NULL;
    int impulso, num_escolha, num_roleta, jogar_denovo;
    preencheRoleta(&topo,T);

    do{
        mostraRoleta(topo,T);
        printf("\U00002B50 \U00002B50 \U00002B50 ESCOLHA UM NÚMERO: ");
        scanf("%d", &num_escolha);

        printf("\U0001F4AA \U0001F4AA \U0001F4AA FORÇA PARA GIRAR A ROLETA: ");
        scanf("%d", &impulso);

        if(impulso>0){
            num_roleta = rodaRoleta(topo, impulso);
            printf("\n\nA roleta caiu em %d !!!\n", num_roleta);
            if(num_roleta==num_escolha){
                printf("\U0001F389\U0001F389\U0001F389 VOCÊ GANHOU \U0001F389\U0001F389\U0001F389");
            } else{
                printf("\U0001F61E\U0001F61E\U0001F61E VOCÊ PERDEU \U0001F61E\U0001F61E\U0001F61E");
            }
        } else{
            printf("\U0001F615 Você precisa girar com mais força...");
        }
            
        printf("\n\n");
        printf("Quer tentar denovo? Aperte 1 para continuar.\nCansou? Aperte em 0 para sair.\n");
        scanf("%d", &jogar_denovo);
    } while(jogar_denovo != 0);

    return 0;
}