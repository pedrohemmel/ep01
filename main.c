#include <stdlib.h>
//Tipos
typedef struct No {
  int valor;
  struct No *proximo;
} No;

typedef struct Lista {
  int tamanho;
  No *inicio;
} Lista;

//Reserva de memória (Simulação)
No vetor[4096];

//Funções lista ligada
void inserirInicio(Lista *lista, int valor);

void removerItemLista(Lista *lista, int valor);

void imprimirLista(Lista *lista);

void *aloca(size_t size);
void libera(void *ptr);

int main() {
  
    
  //Exemplo de uso
  Lista lista;
  lista.inicio = NULL;
  lista.tamanho = 0;

  inserirInicio(&lista, 10);
  inserirInicio(&lista, 9);
  inserirInicio(&lista, 8);
  inserirInicio(&lista, 7);
  inserirInicio(&lista, 6);
  inserirInicio(&lista, 5);
  inserirInicio(&lista, 4);
  inserirInicio(&lista, 3);
  inserirInicio(&lista, 2);
  inserirInicio(&lista, 1);
  removerItemLista(&lista, 7);

  imprimirLista(&lista);
}


void *aloca(size_t size) {
  for (int i = 0; i < sizeof(vetor); i++) {
    if (vetor[i].valor == 0) {
      if (i + size <= 4096) {
         vetor[i].valor = size;
         return &vetor[i + 1];
      } else {
        printf("Memória insuficiente para guardar tamanho %d", size);
        return NULL;
      }
    }
  }
  printf("Erro: Memória insuficiente.");
  return NULL;
}

void libera(void *ptr) {
  for (int i = 0; i < sizeof(vetor); i++) {
    if(&vetor[i] == ptr) {
      vetor[i].proximo = NULL;
      vetor[i].valor = 0;
      vetor[i - 1].proximo = NULL;
      vetor[i - 1].valor = 0;
    }
  }
}

void imprimirLista(Lista *lista) {
  No *inicio = lista->inicio;
  printf("Tamanho da lista = %d\n", lista->tamanho);
  while (inicio != NULL) {
    printf("%d ", inicio->valor);
    inicio = inicio->proximo;
  }
}

void removerItemLista(Lista *lista, int valor) {
  No *inicio = lista->inicio;
  No *noARemover = NULL;

  if(inicio != NULL && inicio->valor == valor) {
    noARemover = inicio;
    lista->inicio = noARemover->proximo;
  } else {
    while(inicio != NULL && inicio->proximo != NULL && inicio->proximo->valor != valor) {
      inicio = inicio->proximo;
    }
    if(inicio != NULL && inicio->proximo != NULL) {
      noARemover = inicio->proximo;
      inicio->proximo = noARemover->proximo;
    }
  }

  if(noARemover) {
    libera(noARemover);
    lista->tamanho--;
  }        
}

void inserirInicio(Lista *lista, int valor) {
  No *novoNo = (No *)aloca(sizeof(No));
  novoNo->valor = valor;

  if (lista->inicio == NULL) {
    novoNo->proximo = NULL;
    lista->inicio = novoNo;
  } else {
    novoNo->proximo = lista->inicio;
    lista->inicio = novoNo;
  }
  lista->tamanho++;
}
