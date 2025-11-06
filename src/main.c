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

int main(){



    return 0;
}