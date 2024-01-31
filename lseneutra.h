typedef struct lse t_lse;
typedef void(*t_imprimir_lse)(void*);
typedef int(*t_comparar_lse)(void*, void*);

void imprimir_lse(t_lse* lse);
void inserir_lse(t_lse* lse, void* carga_util);
void inserir_final_lse(t_lse* lse, void* carga_util);
void* acessar_lse(t_lse* lse, int pos);
void destruir_lse(t_lse* lse);
void* buscar_lse(t_lse *lse, void* buscado);
t_lse* criar_lse(t_imprimir_lse impressora, t_comparar_lse comparador);