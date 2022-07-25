/**
 * @file arvore.h
 * @author Anjo
 * @date 2022
 * @brief Definicoes Globais para arvore Binaria Genérica
 *
 * Structs, Constantes e Assinaturas de Funcoes para arvore Binaria
*/
#include <stdio.h>
#include <stdbool.h>
#include "listas.h"
#include  <locale.h>

#pragma warning( disable : 4996 ) //evita MSG ERROS: _CRT_SECURE_NO_WARNINGS
#define M 5		//Número de Maquinas
#define T 10	//Número de Tempos
#define MAX 100
#pragma once 

/**
 * @brief Dados Node arvore
 */
typedef struct Data{
	int dados; /**< Codigo do Nodo da arvore*/
	struct ListaOperacoes* oper; /**< Ligacão as Operacoes */
}Data;

/**
 * @brief arvore
 */
typedef struct Node {
	Data data; /**< Dados da arvore*/
	struct Node* direito; /**< Ligacão lado direto da arvore*/
	struct Node* esquerdo; /**< Ligacão lado esquerdo da arvore*/
}Node, *PtrNode;

/**
 * @brief Estrutura Auxiliar para preservar dados em ficheiro
 */
typedef struct Job {
	int cod; /**< Codigo da Job*/
	int op; /**< Codigo da Operacão*/
	int codm; /**< Codigo da Maquina*/
	char tipoM[N]; /**< Tipo de Maquina*/
	int tempo; /**< Tempo da Maquina */
}Job;

/**
 * @brief Estrutura para o Planeamento
 */
typedef struct PlanoJob {
	int codj;
	int codo;
}PlanoJob;


/**
 * @brief Prototipos
 */
Node* AdicionaNode(Node* nodo, int cod);
Node* AdicionaOper(Node* d, ListaOperacoes* h, int cod);
void MostraTodasJobs(Node* root);
Node* ProcuraArvore(Node* d, int cod);
void MostraOpeJob(Node* inicio, int cod);
Node* InsereMaqOpeJob(Node* d, ListaOperacoes* oper, Maquinaa* m, int codj, int codop);
bool SaveJob(Node* j, FILE* fp);
bool SaveJobsPreOrder(Node* h, FILE* fp);
bool SaveJobs(Node* h, char* fileName);
Node* GetAll(char* fileName);
Node* NewNode(int cod);
void MostraTodasJobsOperacoes(Node* root);
Node* DeleteNodeTree(Node* root, int cod);
Node* ApagaNode(Node* root);
void DestroyNode(Node** p);
Node* FindMin(Node* root);
Node* RemoveOperacaoJob(Node* d, int codop, int codjob);
int CalculaMin(Node* h, int cod);
float CalculaMed(Node* h, int cod);
int CalculaMax(Node* h, int cod);
bool IniciaPlano(PlanoJob p[][T], int codj, int codo);
bool OcupaVarios(PlanoJob p[][T], int m,int codJ, int totTempo, PlanoJob* c);
Ocupa(PlanoJob p[][T], int codJ, int codO, int m, int totTempo);
int OcupaPlanoo(Node* root);
Node* CarregarDadosFicheiro(char* fileName); //TXT
bool SaveJobss(Node* h, char* fileName);

