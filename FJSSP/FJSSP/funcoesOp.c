/**
*  @file funcoesOp.c
 * @author Anjo
 * @date 2022
 * @brief Lista Ligadas Simples (versão 1)
 *
 * Metodos para manipular uma Lista Ligada de Operacoes
 * @bug No known bugs.
*/

#include "listas.h"
#include <stdio.h>

#pragma region Criar
/**
 * @brief Aloca memoria para armazenar a Operacao
 *
 * @param cod - CodOperacao
 */
ListaOperacoes* CriaOperacao(int cod) {
	ListaOperacoes* aux = (ListaOperacoes*)malloc(sizeof(ListaOperacoes));
	if (aux == NULL) return NULL;
	aux->cod = cod;
	aux->maquinas = NULL;
	aux->proximo = NULL;
	return aux;
}
#pragma	endregion

#pragma region InsereLista

/**
 * @brief Insere na lista uma operacao
 *
 * @param ListaOperacoes - Lista de Operacoes Existentes
 * @param ListaOperacoes - Nova Operacão
 */
ListaOperacoes* InsereOperacaoInicio(ListaOperacoes* h, ListaOperacoes* novo) {
	if (novo == NULL) return h;	//Verificar se apontadores são validos
	/*ListaOperacoes* nova = CriaNodoListaOperacoes(novo);*/
	if (h == novo) return h;
	if (h == NULL) h = novo;
	else
	{
		novo->proximo = h;	//aponta para onde "h" esta a apontar
		h = novo;
	}
	return h;
}

/**
 * @brief Insere uma lista de Operacoes Ordenada
 *
 * @param ListaOperacoes - Lista de Operacoes Existentes
 * @param ListaOperacoes - Nova Operacão
 */
ListaOperacoes* InsereOperacaoOrdenada(ListaOperacoes* h, ListaOperacoes* novo) {
	if (novo == NULL) return h;
	/*ListaOperacoes* nova = CriaNodoListaOperacoes(novo);*/
	if (h == NULL) h = novo;
	else
	{
		ListaOperacoes* aux = h;
		ListaOperacoes* auxAnt = NULL;
		while (aux && aux->cod < novo->cod) {
			auxAnt = aux;
			aux = aux->proximo;
		}
		if (auxAnt == NULL) {	//Insere no meio
			novo->proximo = h;
			h = novo;
		}
		else
		{
			auxAnt->proximo = novo;	//Insere no fim
			novo->proximo = aux;
		}
	}
	return h;
}


/**
 * @brief Ordena a lista
 *
 * @param ListaOperacoes - Lista de Operacoes que vai Ordenar
 */
ListaOperacoes* OrdenaListaO(ListaOperacoes* h) {
	if (h == NULL) return NULL;
	ListaOperacoes* listaOrdenada = NULL;
	ListaOperacoes* aux = h;
	ListaOperacoes* novo;
	while (aux) {
		novo = CriaOperacao(aux->cod);
		listaOrdenada = InsereOperacaoOrdenada(listaOrdenada, novo);
		aux = aux->proximo;
	}
	return listaOrdenada;
}


/**
 * @brief Insere Maquinas na lista Operacao
 *
 * @param ListaOperacoes - Aponta Inicio da Lista
 * @param Maquinaa - Maquina que sera introduzida
 * @param nc - Codigo da operacão onde ira ser inserida a maquina
 */
ListaOperacoes* InsereMaquinaOperacao(ListaOperacoes* h, Maquinaa* c, int nc) {
	if (h == NULL) return NULL;	// se lista vazia
	if (c == NULL) return h;	//se maquina não tem informacão

	ListaOperacoes* aux = ProcuraOperacao(h, nc);
	if (aux) {		//se existe essa Operacao
		aux->maquinas = InsereMaquinaListaMaquinas(aux->maquinas, c);
	}
	return h;
}

/**
 * @brief Insere Maquinas na lista Operacao de Forma Ordenada
 *
 * @param ListaOperacoes - Aponta Inicio da Lista
 * @param Maquinaa - Maquina que sera introduzida
 * @param nc - Codigo da operacão onde ira ser inserida a maquina
 */
ListaOperacoes* InsereMaquinaOperacaoOrd(ListaOperacoes* h, Maquinaa* c, int nc) {
	if (h == NULL) return NULL;	// se lista vazia
	if (c == NULL) return h;	//se maquina não tem informacão

	ListaOperacoes* aux = ProcuraOperacao(h, nc);
	if (aux) {		//se existe essa Operacao
		aux->maquinas = InsereMaquinaListaMaquinasOrd(aux->maquinas, c);
	}
	return h;
}

#pragma endregion


#pragma region Procurar
/**
 * @brief Procura Operacão pelo seu codigo
 *
 * @param ListaOperacoes - Lista Operacoes
 * @param nc - Cod Operacão
 */
ListaOperacoes* ProcuraOperacao(ListaOperacoes* inicio, int nc) {
	ListaOperacoes* aux = inicio;
	while (aux) {
		if (aux->cod == nc) return aux;	//se encontrou
		aux = aux->proximo;
	}
	return NULL;			//se não encontrou
}
#pragma endregion

#pragma region Mostrar
/**
 * @brief Mostra Todas as Operacoes Existentes com as suas Maquinas
 *
 * @param ListaOperacoes - Lista Operacoes
 */
void MostraTodasOperacoes(ListaOperacoes* h) {
	ListaOperacoes* aux = h;
	if (h == NULL) return NULL;
		while (aux) {
		printf("OPERACAO N: %d\n", aux->cod);
		listar3(aux->maquinas);
		aux = aux->proximo;
	}
}


/**
 * @brief Mostra Maquinas inseridas numa so Operacão
 *
 * @param ListaOperacoes - Lista Operacoes
 * @param nc - Cod da Operacão que ira ser mostrada
 */
void MostraMaquinasOperacoes(ListaOperacoes* inicio, int nc) {
	ListaOperacoes* aux = inicio;
	aux = ProcuraOperacao(inicio, nc);
	if (aux) {
		ListaOperacoes* maq = aux->maquinas;
		printf("OPERACAO ENCONTRADA CODIGO: %d\n", aux->cod);
		listar3(maq);
	}
}
#pragma endregion

#pragma region Remover

/**
 * @brief Remove Operacão. Codigo indexado pelo seu codigo (cod)
 * 
 * @param ListaOperacoes - Lista Operacoes
 * @param cod - Cod Operacão que sera Apagada
 */
ListaOperacoes* ApagaOperacao(ListaOperacoes* h, int cod) {
	if (h == NULL) return NULL;			//Lista vazia

	if (h->cod == cod) {		//remove no inicio da lista
		ListaOperacoes* aux = h;
		h = h->proximo;
		free(aux);
	}
	else
	{
		ListaOperacoes* aux = h;
		ListaOperacoes* auxAnt = aux;
		while (aux && aux->cod != cod) {	//procura para remover
			auxAnt = aux;
			aux = aux->proximo;
		}
		if (aux != NULL) {					//se encontrou, remove
			auxAnt->proximo = aux->proximo;
			free(aux);
		}
	}
	return h;
}
#pragma endregion

#pragma region Alterar

/**
 * @brief Altera codigo Operacao
 *
 * @param ListaOperacoes - Lista Operacoes
 * @param cod - CodOperacao
 * @param novocod - Novo Codigo de Operacão
 */
ListaOperacoes* AlteraOperacao(ListaOperacoes* h, int cod, char novocod) {
	ListaOperacoes* aux = ProcuraOperacao(h, cod);
	if (aux != NULL)		//se encontrou operacao
	{
		aux->cod = novocod;
	}
	return h;
}


#pragma endregion 


//Destroi toda a lista
void DestroiLista(ListaOperacoes** h) {
	if (h != NULL) {
		ListaOperacoes* aux;
		while (*h) {
			aux = *h;
			*h = (*h)->proximo;
			free(aux);
		}
	}
}
#pragma endregion

#pragma region CalculaTempo_O
/**
 * @brief Percorre a Lista e Encontra a maquina que demora menos tempo
 *
 * @param ListaMaquinaa - Lista Maquinas
 */ 
int CalculaMinimoOper_T(ListaMaquinaa* h) {
	ListaMaquinaa* aux = h;
	int min;
	if (h == NULL) return(NULL);
	else {
		min = h->maquinaa.tempo;
		while (aux != NULL) {
			//Se o Valor da Lista for menor que o min
			//Entao vai repor com o valor mais pequeno  
			if (min > aux->maquinaa.tempo) {
				min = aux->maquinaa.tempo;
			}
			aux = aux->prox;
		}
		//printf("Valor Minimo na Operacao: % d\n", min);     Valor Minimo em Cada Operacao
	}	
	return min;
}


/**
 * @brief Percorre a Lista e Encontra a maquina que demora mais tempo 
 *
 * @param ListaMaquinaa - Lista Maquinas
 */
int CalculaMaximoOper_T(ListaMaquinaa* h) {
	ListaMaquinaa* aux = h;
	int max;
	if (h == NULL) return(NULL);
	else {
		max = h->maquinaa.tempo;
		while (aux != NULL) {
			//Se o Valor da Lista for maior que o max
			//Entao vai repor com o valor mais pequeno  
			if (max < aux->maquinaa.tempo) {
				max = aux->maquinaa.tempo;
			}
			aux = aux->prox;
		}
		//printf("Valor Maximo da Operacao: %d\n", max);
	}
	return max;
}


/**
 * @brief Percorre a Lista e Faz a Média de tempo de todas as maquinas 
 *
 * @param ListaMaquinaa - Lista Maquinas
 */
float CalculaMediaOper_T(ListaMaquinaa* h) {
	ListaMaquinaa* aux = h;
	int media = 0;
	int cont = 0;
	if (h == NULL) return(0);
	else {
		while (aux != NULL) {
			media += aux->maquinaa.tempo;
			cont++;
			aux = aux->prox;
			}
		media = media / cont;
			/*aux = aux->prox;*/
		
		/*printf("Valor Medio na Operacao: % f\n", media);*/     //Valor Médio em Cada Operacao
	}
	return media;
}


ListaMaquinaa* CalculaMinimoOperPlano(ListaMaquinaa* h) {
	ListaMaquinaa* aux = h;
	ListaMaquinaa* mmin = NULL;
	int min;
	if (h == NULL) return(NULL);
	else {
		min = h->maquinaa.tempo;
		while (aux != NULL) {
			//Se o Valor da Lista for menor que o min
			//Entao vai repor com o valor mais pequeno  
			if (min > aux->maquinaa.tempo) {
				mmin = aux;
			}
			if (min == aux->maquinaa.tempo) {
				mmin = aux;
			}
			aux = aux->prox;
		}
		//printf("Valor Minimo na Operacao: % d\n", min);     Valor Minimo em Cada Operacao
	}
	return mmin;
}
#pragma endregion

