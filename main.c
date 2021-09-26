#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING 40

typedef struct ListaGenRelatorio
{
  char info[MAX_STRING];
  struct ListaGenRelatorio *cabeca;
  struct ListaGenRelatorio *cauda;

} LgRel;

typedef struct _input
{
  int cod;
  char nome[MAX_STRING];
  char ende[MAX_STRING];
  char bairro[MAX_STRING];
  char estado[MAX_STRING];
  char cidade[MAX_STRING];
} input;

#include "txtToBin.h"

void exibe(LgRel *L)
{
  putchar('[');
  while (L != NULL)
  {
    printf("%s", L->info);
    if (L->cabeca != NULL)
    {
      putchar(',');
      //Exibir com espacos pos virgula
      //printf(", "); 
      exibe(L->cabeca);
    }

    L = L->cauda;
    if (L != NULL)
      putchar(',');
      //Exibir com espacos pos virgula
      //printf(", ");
  }
  putchar(']');
}

//  Outra forma de destruir
/*
void destroy(LgRel **L)
{
  if((*L)->cabeca != NULL)
    destroy(&(*L)->cabeca);

  if((*L)->cauda != NULL)
    destroy(&(*L)->cauda);

  free(*L);
  *L = NULL;
}
*/

void destroy(LgRel **L)
{
  if (*L != NULL)
  {
    destroy(&(*L)->cabeca);
    destroy(&(*L)->cauda);
    free(*L);
    *L = NULL;
  }
}

LgRel *Cons(const char *str, LgRel *cabeca, LgRel *cauda)
{
  LgRel *novoNodo = (LgRel *)malloc(sizeof(LgRel));
  strcpy(novoNodo->info, str);
  novoNodo->cabeca = cabeca;
  novoNodo->cauda = cauda;
  return novoNodo;
}

LgRel *contem(LgRel *nodo, const char *str)
{
  while (nodo != NULL && strcmp(str, nodo->info) > 0)
    nodo = nodo->cauda;

  if (nodo != NULL && !strcmp(str, nodo->info))
    return nodo;
  return NULL;
}

LgRel **grava(LgRel **L, const char *str)
{
  LgRel *ant;
  LgRel *aux = contem(*L, str);

  if (aux == NULL)
  {
    aux = *L;

    while (aux != NULL && strcmp(str, aux->info) > 0)
    {
      ant = aux;
      aux = aux->cauda;
    }

    if (aux == *L)
    {
      *L = Cons(str, NULL, aux);
      return &(*L)->cabeca;
    }
    else
      ant->cauda = Cons(str, NULL, aux);
    return &(ant)->cauda->cabeca;
  }
  return &(aux)->cabeca;
}

void gravacao(LgRel **L)
{
  FILE *arq = fopen("relatorio.dat", "rb");
  if (arq != NULL)
  {
    input in;

    LgRel **aux = NULL;
    //LgRel *L = NULL;

    fread(&in, sizeof(input), 1, arq);

    while (!feof(arq))
    {
      //  se variavel declarada nesse escopo
      //  aux = grava(&L, in.estado);

      aux = grava(&*L, in.estado);
      aux = grava(aux, in.cidade);
      aux = grava(aux, in.bairro);
      aux = grava(aux, in.nome);

      fread(&in, sizeof(input), 1, arq);
    }
    //exibe(L);
    //putchar('\n');
    //destroy(&L);
    fclose(arq);
  }
  else
    perror("Erro");
}

void Exe3()
{
  LgRel *L = NULL;
  geraBinario();

  gravacao(&L);

  exibe(L);
  putchar('\n');

  puts("************Comparar Ordenacao com a do Exercicio************");
  destroy(&L);
}

int main(void)
{
  Exe3();
  return 0;
}