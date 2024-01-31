#include "stdio.h"
#include "stdlib.h"
#include "lseneutra.h"

typedef struct elem_se{
    void* carga_util;
    struct elem_se* prox;
} t_elemento_lse;

/**
 * cria um elemento da LSE
*/
t_elemento_lse* criar_elemento_lse(void* carga_util){
    t_elemento_lse* novo = malloc(sizeof(t_elemento_lse));
    novo->carga_util = carga_util;
    novo->prox = NULL;

    //printf("Criando: %p %p %p\n", novo, novo->carga_util, novo->prox);

    return novo;
}

struct lse{
    t_elemento_lse* inicio;
    t_elemento_lse* fim;
    int tamanho;
    t_imprimir_lse impressora;
    t_comparar_lse comparador;
};


t_lse* criar_lse(t_imprimir_lse impressora, t_comparar_lse comparador){ //, t_comparar_lse comparar){
    t_lse *l = malloc(sizeof(t_lse));
    l->inicio = l->fim = NULL;
    l->tamanho = 0;
    l->impressora = impressora;
    l->comparador = comparador;

    return l;
}

void imprimir_lse(t_lse* lse){
    t_elemento_lse* cam = lse->inicio;

    while(cam!=NULL){
        //printf("%p\n", cam->carga_util);
        lse->impressora(cam->carga_util);
        cam = cam->prox;
    }
}


void inserir_lse(t_lse* lse, void* carga_util){
    t_elemento_lse* novo = criar_elemento_lse(carga_util);

    if (lse->inicio == NULL){
        lse->inicio = lse->fim = novo; 
    }else{
        novo->prox = lse->inicio;
        lse->inicio = novo;
    }

    lse->tamanho++;
}

void inserir_final_lse(t_lse* lse, void* carga_util){
    
    t_elemento_lse* novo = criar_elemento_lse(carga_util);

    if (lse->inicio == NULL){
        lse->inicio = lse->fim = novo;
    }else{
       lse->fim->prox = novo;
        lse->fim = novo;
    }
    lse->tamanho++;

}

void* acessar_lse(t_lse* lse, int pos){
    pos = (pos%lse->tamanho);
    pos = (pos == 0?lse->tamanho:pos);

    t_elemento_lse *cam = lse->inicio;
    for(int i=1;i<pos;i++){
        cam = cam->prox;  
    }
    return cam->carga_util;
}

void destruir_lse(t_lse* lse){
    t_elemento_lse* elem = lse->inicio;
    while(elem!=NULL){
        t_elemento_lse* proximo = elem->prox;
        //destruir_elem_lse(elem->carga);
        free(elem->carga_util);
        free(elem);
        elem = proximo;
    } 
}

// void* remover_inicio_lse(t_lse* lse){

// }

// void* remover_final_lse(t_lse* lse){

// }

void* buscar_lse(t_lse *lse, void* buscado){
    t_elemento_lse *cam = lse->inicio;
    short achei = 0; // falso
    while( (cam != NULL) && (!achei) ){
        //printf("%p\n", cam->carga_util);
        if (lse->comparador(cam->carga_util,buscado)==0){
            achei=1; //verdade
        }else{
            cam = cam->prox;
        }
    }
    if (achei)
        return cam->carga_util;
    else
        return NULL;
    
}

void inserir_ordenado_lse(t_lse* lse, void* carga){
    t_elemento_lse *novo = criar_elemento_lse(carga);
    if (lse->inicio == NULL){
        lse->inicio = lse->fim = novo;
    }else{
        t_elemento_lse *ant = NULL; // ANTerior
        t_elemento_lse *cam = lse->inicio; // CAMinhador
        while((cam!=NULL) & (lse->comparador(cam->carga_util, carga)<=0)){
            ant = cam;
            cam = cam->prox;
        }
        if (cam == NULL){ // inserir no final
            lse->fim->prox = novo;
            lse->fim = novo;
        }else if (cam == lse->inicio){ // inserir no inicio
            novo->prox = lse->inicio; 
            lse->inicio = novo;
        }else{
            ant->prox = novo;
            novo->prox = cam;
        }
    }
    lse->tamanho++;
}

void* remover_conteudo_lse(t_lse* lse, void* removivel){
    void* carga = NULL; // referência para a carga_util
    t_elemento_lse *ant = NULL; // ANTerior
    t_elemento_lse *cam = lse->inicio; // CAMinhador
    while((cam!=NULL) & (lse->comparador(cam->carga_util, removivel)!=0)){
        ant = cam;
        cam = cam->prox;
    }
    if (cam != NULL){ // achou
        if (cam == lse->inicio){ // inserir no inicio
            lse->inicio = cam->prox; 
            if (lse->inicio == NULL){ // era o último ?
                lse->fim = NULL;
            }
        }else{
            ant->prox = cam->prox;
            if (lse->fim == cam) // removendo no final?
                lse->fim = ant;
        }
        carga = cam->carga_util;
        free(cam);
        lse->tamanho--;
    }
    return carga;
}
