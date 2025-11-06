#include <stdlib.h>
#include <stdio.h>

typedef struct no
{
    int valor;
    struct no *esquerdo, *direito;
    int altura;
}No;


int maior(int a, int b){
    return (a > b)? a: b;
}

No* novoNo(int x){
    No *novo = malloc(sizeof(No));

    if(novo){
        novo->valor = x;
        novo->esquerdo = NULL;
        novo->direito = NULL;
        novo->altura = 0;
    }
    else{
        printf("ERRO ao alocar novo no!");
    }

    return novo;
}

int alturaNo(No *no){
    if(no == NULL){
        return -1;
    }
    else{
        return no->altura;
    }
}

int fatorBalanceamento(No *no){
    if(no){
        return (alturaNo(no->esquerdo) - (alturaNo(no->direito)));
    }
    else{
        return 0;
    }
}

No* rotacaoEsquerda(No *r){
    No *y, *f;

    y = r->direito;
    f = y->esquerdo;

    y->esquerdo = r;
    r->direito = f;

    r->altura = maior(alturaNo(r->esquerdo), alturaNo(r->direito) + 1);
    y->altura = maior(alturaNo(y->esquerdo), alturaNo(y->direito) + 1);

    return y;
}

No* rotacaoDireita(No *r){
    No *y, *f;

    y = r->esquerdo;
    f = y->direito;

    y->direito = r;
    r->esquerdo = f;

    r->altura = maior(alturaNo(r->esquerdo), alturaNo(r->direito) + 1);
    y->altura = maior(alturaNo(y->esquerdo), alturaNo(y->direito) + 1);

    return y;
}

No* rotacaoDireitaEsquerda(No *r){
    r->direito = rotacaoDireita(r->direito);
    return rotacaoEsquerda(r);
}

No* rotacaoEsquerdaDireita(No *r){
    r->esquerdo = rotacaoDireita(r->esquerdo);
    return rotacaoDireita(r);
}

No* balancearARV(No *raiz){
    int fb = fatorBalanceamento(raiz);

    if(fb < -1 && fatorBalanceamento(raiz->direito) <= 0){
        raiz = rotacaoEsquerda(raiz);
    }
    else if(fb < -1 && fatorBalanceamento(raiz->direito) > 0){
        raiz = rotacaoDireitaEsquerda(raiz);
    }
    else if(fb > 1 && fatorBalanceamento(raiz->esquerdo) >= 0){
        raiz = rotacaoDireita(raiz);
    }
    else if(fb > 1 && fatorBalanceamento(raiz->esquerdo) < 0){
        raiz = rotacaoEsquerdaDireita(raiz);
    }

    return raiz;
}

No* inserir(No *raiz, int x){
    if(raiz == NULL){
        return novoNo(x);
    }
    else{
        if(x < raiz->valor){
            raiz->esquerdo = inserir(raiz->esquerdo, x);
        }
        else if(x > raiz->valor){
            raiz->direito = raiz->direito = inserir(raiz->direito, x);
        }
        else{
            printf("Inserção não realizada! O elemento %d já existe\n", x);
        }
    }

    raiz->altura = maior(alturaNo(raiz->esquerdo), alturaNo(raiz->direito));

    raiz = balancearARV(raiz);

    return raiz;
}

No* remover(No *raiz, int chave){
    if(raiz == NULL){
        printf("Valor não encontrado");
        return NULL;
    }
    else{
        if(raiz->valor == chave){
            if(raiz->esquerdo == NULL && raiz->direito == NULL){
                free(raiz);
                printf("Elemento folha removido: %d!\n", chave);
                return NULL;
            }
            else{
                if(raiz->esquerdo != NULL && raiz->direito != NULL){
                    No *aux = raiz->esquerdo;
                    while(aux->direito != NULL){
                        aux = aux->direito;
                    }

                    raiz->valor = aux->valor;
                    aux->valor = chave;

                    printf("Elemento trocado: %d!\n", chave);

                    return raiz;                    
                }
                else{
                    No *aux;

                    if(raiz->esquerdo != NULL){
                        aux = raiz->esquerdo;
                    }
                    else{
                        aux = raiz->direito;
                    }

                    free(raiz);
                    printf("Elemento com 1 filho removido: %d!\n", chave);
                    
                    return aux;
                }
            }
        }
        else if(chave < raiz->valor){
                raiz->esquerdo = remover(raiz->esquerdo, chave);
            }
            else{
                raiz->direito = remover(raiz->direito, chave);
            }
        
        raiz->altura = maior(alturaNo(raiz->esquerdo), alturaNo(raiz->direito) + 1);

        raiz = balancearARV(raiz);
    }

    return raiz;

}

void imprimir(No *raiz, int nivel){
    if(raiz){
        imprimir(raiz->direito, nivel + 1);
        printf("\n\n");

        for(int i = 0; i < nivel; i++){
            printf("\t");
        }

        printf("%d", raiz->valor);

        imprimir(raiz->esquerdo, nivel + 1);
    }
}

int main(){

    int opcao, valor;
    No *raiz = NULL;

    do{
        printf("\n\n\n\t0 - Sair\n\t1 - Inserir\n\t2 - Remover\n\t3 - Imprimir\n\n");
        scanf("%d", &opcao);

        switch(opcao){
            case 0:
                system("clear");
                printf("SAINDO!");
                break;
            case 1:
                printf("\tDigite o valor a ser INSERIDO: ");
                scanf("%d", &valor);
                raiz = inserir(raiz, valor);
                system("clear");
                break;
            case 2:
                printf("\tDigite o valor a ser REMOVIDO: ");
                scanf("%d", &valor);
                raiz = remover(raiz, valor);
                system("clear");
                break;
            case 3:
                system("clear");
                imprimir(raiz, 1);
                break;
            default:
                printf("OPÇÃO INVÁLIDA!!!\n");
                system("clear");            
        }
    }while(opcao != 0);

    return 0;
}