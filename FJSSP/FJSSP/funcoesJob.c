/**
*  @file funcoesJob.c
 * @author Luis Anjo
 * @date 2022
 * @brief arvore Binaria Gen�rica
 *
 * Metodos para manipular uma arvore Binaria Gen�rica
 * @bug No known bugs.
*/

#include "Arvore.h"
#include "listas.h"
#include <stdio.h>
#include <stdbool.h>


#pragma region Criar
/**
 * @brief Aloca memoria para armazenar Nodo arvpre
 *
 * @param cod - Cod Job
 */
	Node* NewNode(int cod) {
		Node* node = (Node*)malloc(sizeof(Node));
		if (node == NULL) return(NULL);
		node->data.oper = NULL;
		node->direito = NULL;
		node->esquerdo = NULL;
		node->data.dados = cod;
		return node;
	}

/**
 * @brief Adiciona Node a arvore
 *
 * @param Node - Nodo da arvore
 * @param cod - Novo Nodo que sera adicionado
 */

	Node* AdicionaNode(Node* nodo, int cod) {
	if (nodo == NULL) {
		nodo = NewNode(cod);
		return nodo;
	}
		if (nodo->data.dados > cod) {
			nodo->esquerdo = AdicionaNode(nodo->esquerdo, cod);
		}
		if (nodo->data.dados < cod) {
			nodo->direito = AdicionaNode(nodo->direito, cod);
		}
		if (nodo->data.dados == cod) {
			return nodo;
		}
		return nodo;
}

/**
 * @brief Adiciona Operac�o ao Job
 *
 * @param Node - Nodo da arvore
 * @param ListaOperacoes - Operac�o que sera adicionada
 * @param cod - Cod Job
 */
	Node* AdicionaOper(Node* d, ListaOperacoes* h, int cod){ //Adiciona Lista de Operacoes e Maquinas JOb
		if (h == NULL) return d;
	
		
		Node* dados = ProcuraArvore(d, cod);
		if (dados) {
			if (dados->data.oper) {
				ListaOperacoes* exist = ProcuraOperacao(dados->data.oper, h->cod);
				if (exist) return d;
			}
			
			dados->data.oper = InsereOperacaoOrdenada(dados->data.oper, h);
		}
	
		return d;
	}

	/**
	 * @brief Adiciona Operac�o e Maquina ao Job
	 *
	 * @param Node - Nodo da arvore
	 * @param ListaOperacoes - Operac�o que sera adicionada
	 * @param Maquinaa- Maquina que sera adicionada
	 * @param cod - Cod Job
	 * @param codop - Cod Operac�o
	 */
	Node* InsereMaqOpeJob(Node* d, ListaOperacoes* oper,Maquinaa* m,int codj, int codop) {
		if (m == NULL) return d;
		ListaOperacoes* op = ProcuraOperacao(oper, codop);

		if (op) { //Se Existe Operac�o com o respetivo codigo
			op = InsereMaquinaOperacao(op, m, codop);
		}
		else { //Cria Operac�o e Insere Maquina
			ListaOperacoes* operacao;
			operacao = CriaOperacao(codop);
			op = InsereOperacaoInicio(op,oper);
			op = InsereOperacaoOrdenada(oper,operacao);
			ListaOperacoes* proc;
			op = ProcuraOperacao(op, codop);
			op = InsereMaquinaOperacao(op, m, codop);
		}

		Node* no = ProcuraArvore(d, codj);
		if (no == NULL) { //Se arvore n�o Existe Cria e Adiciona Operac�o
			no = AdicionaNode(d, codj);
			no = AdicionaOper(no, op, codj);
		}
		else
		{
			no = AdicionaOper(no, op, codj);;
		}
	
		return d;
	}

#pragma endregion

#pragma region MostraArvore
/**
 * @brief Mostra Todos os Jobs
 *
 * @param Node - arvore que sera exibida
 */
	void MostraTodasJobs(Node* root) {
		if (root == NULL) return root;
		printf("JOB: %d\n", root->data.dados);
		MostraTodasJobs(root->esquerdo);
		MostraTodasJobs(root->direito);
	}
	/**
 * @brief Mostra Todos os Jobs com as Operacoes e Maquinas la dentro
 *
 * @param Node - arvore a ser Exibida
 */
	void MostraTodasJobsOperacoes(Node* root) {
		if (root == NULL) return root;
		printf("JOB: %d\n", root->data.dados);
		if (root->data.oper != NULL) {
			MostraTodasOperacoes(root->data.oper);
		}
		else printf("Job Sem Operacoes\n");
		MostraTodasJobsOperacoes(root->esquerdo);
		MostraTodasJobsOperacoes(root->direito);
	}


#pragma endregion

#pragma region ProcuraArvore
/*	
 * @brief Procura um elemento na arvore
 *
 * @param Node - arvore
 * @param cod - Elemento a ser Procurado
 */
	Node* ProcuraArvore(Node* d, int cod) {
		if (d == NULL) return NULL;
		if (d->data.dados == cod) return d;
		else
		{
			if (d->data.dados > cod) return (ProcuraArvore(d->esquerdo,cod));
			else return (ProcuraArvore(d->direito,cod));
		}
	}
	
#pragma endregion

#pragma region MostraOper_Jobs
/**
 * @brief Mostra Operacoes de uma �nica Job
 *
 * @param Node - arvore
 * @param cod - CodOperacao
 */
	void MostraOpeJob(Node* inicio, int cod) { //Mostra Operacao de uma Job
		Node* aux = inicio;
		aux = ProcuraArvore(inicio, cod);
		if (aux) {
			cod = aux->data.dados;
			printf("Job N: %d \n", cod);
			MostraTodasOperacoes(aux->data.oper);
			printf("--------------------\n");
		}
	}
#pragma endregion

#pragma region GuardaArvore
/**
 * @brief Guarda a Job em Ficheiro
 *
 * @param Node - arvore a ser Guardada
 * @param fp - Ficheiro onde ira ser guardada
 */
	bool SaveJob(Node* j, FILE* fp) {
		ListaOperacoes* aux = j->data.oper;
		Job auxx;
		if (aux == NULL) {
			auxx.cod = j->data.dados;
			auxx.op = NULL;
			fwrite(&auxx, sizeof(Job), 1, fp);
		}
		while (aux != NULL) {
			auxx.op = aux->cod;
			auxx.cod = j->data.dados;
			ListaMaquinaa* maquinas = aux->maquinas;
			while (maquinas) {
				auxx.codm = maquinas->maquinaa.codm;
				auxx.tempo = maquinas->maquinaa.tempo;
				strcpy(auxx.tipoM, maquinas->maquinaa.tipo);
				fwrite(&auxx, sizeof(Job), 1, fp);
				maquinas = maquinas->prox;
			}
			aux = aux->proximo;
		}
	}
#pragma endregion

#pragma region TREE
/**
 * @brief Percorre arvore para Guardar
 *
 * @param Node - arvore 
 * @param File - Ficheiro
 */
	bool SaveJobsPreOrder(Node* h, FILE* fp) {
		if (h == NULL) return false;
		//preOrder
		SaveJob(h, fp);
		SaveJobsPreOrder(h->esquerdo, fp);
		SaveJobsPreOrder(h->direito, fp);
		return true;
	}

/**
 * @brief Recebe nome do Ficheiro onde arvore vai ser guardada
 *
 * @param Node - arvore
 * @param filename - Nome Ficheiro
 */
	bool SaveJobs(Node* h, char* fileName) {
		if (h == NULL) return false;
		FILE* fp;
		fp = fopen(fileName, "wb");
		if (fp == NULL) return false;
		SaveJobsPreOrder(h, fp);
		fclose(fp);
		return true;
	}

/**
 * @brief Obtem Dados de Ficheiro Binario
 *
 * @param filename - Nome Ficheiro
 */
	Node* GetAll(char* fileName) {
		FILE* fp = fopen(fileName, "rb");
		if (!fp) return NULL;
		Job aux;
		Node* nodo = NULL;
		Node* root = NULL;
		ListaOperacoes* op = NULL;
		ListaOperacoes* mo = NULL;
		Maquinaa* m = NULL;
		ListaMaquinaa* mac = NULL;

		while (fread(&aux, sizeof(Job), 1, fp) /*!= EOF*/) {
			root = AdicionaNode(root, aux.cod);
			op = CriaOperacao(aux.op);
			root = AdicionaOper(root, op, aux.cod);
			if (aux.op > 0) {
				m = CriaMaquina(aux.codm, aux.tempo, &aux.tipoM);
				m = CriaNodoListaMaquinas(m);
				Node* search = ProcuraArvore(root, aux.cod);
				/*ListaOperacoes* proc = ProcuraOperacao(search->data.oper,aux.op);*/
				search->data.oper = InsereMaquinaOperacaoOrd(search->data.oper, m, aux.op);
			//CUIDADO PODE TER ALGUM ERRO INSERIR MAQUINAS ORDENADAS
			}
		}

		return root;
	}

#pragma endregion

#pragma region ApagaNode

/**
* @brief Percorre arvore para Apagar Node
*
* @param Node - arvore
* @param cod - Elemento da arvore
*/
	Node* DeleteNodeTree(Node* root, int cod) {
		//arvore vazia ou enexistente
		if (root == NULL) return NULL;

		if (root->data.dados > cod)
			root->esquerdo = DeleteNodeTree(root->esquerdo, cod);
		else
			if (root->data.dados < cod) {
				root->direito = DeleteNodeTree(root->direito, cod);
			}
			else    
			{
				root = ApagaNode(root);
			}
		return root;

	}

/**
 * @brief Apaga Nodo arvore
 *
 * @param Node - arvore
 */
	Node* ApagaNode(Node* root) {
		Node* aux;
		if (root == NULL) return NULL;	//Nada para apagar!

		if (root->esquerdo == NULL && root->direito == NULL) {	//�nico nodo
			DestroyNode(&root);
			return NULL;
		}
		else
			if (root->esquerdo == NULL) {		//so tem sub-arvore direita...ligar � direita
				aux = root;
				root = root->direito;
				DestroyNode(&aux);
			}
			else
			{
				if (root->direito == NULL) {	//so com sub-arvore esquerda
					aux = root;
					root = root->esquerdo;
					DestroyNode(&aux);
				}
				else       //com sub-arvores esquerda e direita
				{
					//substitui pelo menor da sub-arvore direita
					root->data = FindMin(root->direito)->data;
					//elimina o menor da sub-arvore direita
					root->direito = DeleteNodeTree(root->direito, root->data.dados);
				}
			}
		return root;
	}


	/**
	 * @brief Destroi Da Memoria Node
	 *
	 * @param Node - arvore
	 */
		void DestroyNode(Node** p) {	
		if (*p != NULL) {
			free(*p);
			*p = NULL;
		}
	}
		Node* FindMin(Node* root) {
			if (root->esquerdo == NULL) return root;
			else
				return(FindMin(root->esquerdo));
		}
#pragma endregion

#pragma region ApagaOperacaoJob
/**
 * @brief Remove Operac�o de uma Job
 *
 * @param Node - arvore 
 * @param codop - Codigo da Operac�o a ser Apagada
 * @param codjob - Codigo da Job
 */
		Node* RemoveOperacaoJob(Node* d, int codop, int codjob) { //Adiciona Lista de Operacoes e Maquinas JOb
			if (d == NULL) return NULL;


			Node* dados = ProcuraArvore(d, codjob);
			if (dados) {
				if (dados->data.oper) {
					ListaOperacoes* exist = ProcuraOperacao(dados->data.oper, codop);
					dados->data.oper = ApagaOperacao(dados->data.oper, codop);
					
				}
			}
			return d;
		}

#pragma endregion

#pragma region CalculaMinimo{
 /**
 * @brief Calcula o Minimo tempo para executar o Job
 *
 * @param Node - arvore
 * @param cod - Codigo arvore
 */
		int CalculaMin(Node* h, int cod) {
			if (h == NULL) return NULL;
			int soma = 0;
		
			Node* dados = ProcuraArvore(h, cod);
			ListaOperacoes* aux = dados->data.oper;
				while (aux != NULL) {
					soma += CalculaMinimoOper_T(aux->maquinas);
					aux = aux->proximo;
				}

			return soma;
		}

/**
 * @brief Calcula a M�dia de tempo para executar o Job
 *
 * @param Node - arvore
 * @param cod - Codigo arvore
 */
		float CalculaMed(Node* h, int cod) {
			if (h == NULL) return 0;
			float media = 0;
			int cont = 0;
			Node* dados = ProcuraArvore(h, cod);
			ListaOperacoes* aux = dados->data.oper;
				while (aux != NULL) {
					media += CalculaMediaOper_T(aux->maquinas);
					cont++;
					aux = aux->proximo;
				}
				media = media / cont;

			
			return media;
		}

		/**
		 * @brief Calcula o Maximo tempo para executar o Job
		 *
		 * @param Node - arvore
		 * @param cod - Codigo arvore
		 */
		int CalculaMax(Node* h, int cod) {
			if (h == NULL) return NULL;
			int soma = 0;
			Node* dados = ProcuraArvore(h, cod);
			ListaOperacoes* aux = dados->data.oper;
			
				while (aux != NULL) {
					soma += CalculaMaximoOper_T(aux->maquinas);
					aux = aux->proximo;
				}

			
			return soma;
		}
#pragma endregion

#pragma region GuardaArvoreTXT
		/**
		 * @brief Guarda a Job em Ficheiro TXT
		 *
		 * @param Node - arvore a ser Guardada
		 * @param fp - Ficheiro onde ira ser guardada
		 */
		bool SaveJobb(Node* j, FILE* fp) {
			ListaOperacoes* aux = j->data.oper;
			Job auxx;
			if (aux == NULL) {
				auxx.cod = j->data.dados;
				auxx.op = NULL;
				fprintf(fp, "%d;%d;%d;%d\n", auxx.cod, 0, 0,0);
			}
			while (aux != NULL) {
				auxx.op = aux->cod;
				auxx.cod = j->data.dados;
				ListaMaquinaa* maquinas = aux->maquinas;
				while (maquinas) {
					auxx.codm = maquinas->maquinaa.codm;
					auxx.tempo = maquinas->maquinaa.tempo;
					fprintf(fp, "%d;%d;%d;%d\n", auxx.cod,auxx.op,auxx.codm,auxx.tempo);
					maquinas = maquinas->prox;
				}
				aux = aux->proximo;
			}
		}

		/**
		 * @brief Percorre arvore para Guardar
		 *
		 * @param Node - arvore
		 * @param File - Ficheiro
		 */
		bool SaveJobsPreOrderr(Node* h, FILE* fp) {
			if (h == NULL) return false;
			//preOrder
			SaveJobb(h, fp);
			SaveJobsPreOrderr(h->esquerdo, fp);
			SaveJobsPreOrderr(h->direito, fp);
			return true;
		}

		/**
		 * @brief Recebe nome do Ficheiro onde arvore vai ser guardada
		 *
		 * @param Node - arvore
		 * @param filename - Nome Ficheiro
		 */
		bool SaveJobss(Node* h, char* fileName) {
			if (h == NULL) return false;
			FILE* fp;
			fp = fopen(fileName, "wt");
			SaveJobsPreOrderr(h, fp);
			fclose(fp);
			return true;
		}

#pragma endregion