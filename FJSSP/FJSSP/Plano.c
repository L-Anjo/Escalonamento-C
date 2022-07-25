/**
*  @file Plano.c
 * @author Luis Anjo
 * @date 2022
 * @brief Plano para Jobs
 *
 * Metodos para manipular um Plano com Arrays
 * @bug No known bugs.
*/

#include "Arvore.h"
#include "listas.h"

#pragma region CriaPlano
/**
 * @brief Inicia Plano
 *
 * @param p - Plano
 * @param codj - Cod Job
 * @param codo - Cod Operacao
 */
bool IniciaPlano(PlanoJob p[][T], int codj, int codo) {

	for (int l = 0; l < M; l++)
		for (int col = 0; col < T; col++) {
			p[l][col].codj = codj;
			p[l][col].codo = codo;
		}
	return true;
}


/**
 * @brief Ocupa varias unidades de tempo.
 *
 * @param p	- Plano
 * @param m	- Maquina
 * @param totTempo	- Tempo a ocupar
 * @param c	- Job e Operacao
 */
bool OcupaVarios(PlanoJob p[][T], int m,int codJ,int totTempo, PlanoJob* c) {
	int aux = T;
	int guarda;
	//Procurar a primeira "casa" livre
	int col = 0;
	while (p[m][col].codj != 0) {
		col++;
	}
	//Ocupa a partir da posicão livre encontrada
	totTempo += col;	

		if(totTempo < aux) // Confirmar se existe unidades tempo para ocupar
		for (; col < totTempo; col++) {
			p[m][col].codj = c->codj;
			p[m][col].codo = c->codo;
		}
		return true;
}

/**
 * @brief Ocupa
 *
 * @param cod - CodOperacao
 */
Ocupa(PlanoJob p[][T],int codJ,int codO, int m, int totTempo) {
	PlanoJob c = { .codj = codJ, .codo = codO };
	OcupaVarios(p, m,codJ, totTempo, &c);


}


/**
 * @brief Ocupa Plano através dos jobs do ficheiro
 *
 * @param Node - arvore
 * @param root
 */
int OcupaPlanoo(Node* root) {
	if (root == NULL) return NULL;
	PlanoJob plano[M][T];
	IniciaPlano(plano, 0, 0);
	ListaOperacoes* aux = root->data.oper;
	Job auxx;


	while (aux != NULL) {
		auxx.op = aux->cod;
		auxx.cod = root->data.dados;
		ListaMaquinaa* maquinas = aux->maquinas;
		
		ListaMaquinaa* novamaq = CalculaMinimoOperPlano(maquinas);
		if(novamaq)
		Ocupa(plano, auxx.cod, auxx.op, novamaq->maquinaa.codm, novamaq->maquinaa.tempo);
		aux = aux->proximo;
	}
	
		/*OcupaPlanoo(root->esquerdo);
		OcupaPlanoo(root->direito);*/
	
	printf("    ");
	for (int col = 0; col < T; col++) {
		printf("     Tempo:%d", col);
	}
	for (int l = 0; l < M; l++) {
		printf("\n");
		printf("Maq:%d |", l);
		for (int col = 0; col < T; col++) {
			printf("Job:%d Op:%d |", plano[l][col].codj, plano[l][col].codo);
		}
	}
}


/**
 * @brief Carrega dados de um ficheiro CSV.
 *
 * @param fileName
 */
Node* CarregarDadosFicheiro(char* fileName) {
	FILE* fp;
	char texto[MAX];
	int a, b, c, d;

	Node* listaJobs = NULL;
	ListaOperacoes auxOper;
	Job aux;
	ListaMaquinaa auxMaq;
	Node* root = NULL;
	//char d[20];

	fp = fopen(fileName, "r");
	if (fp == NULL) return;

	while (!feof(fp)) {
		//fgets
		//fscanf()
		Node* nodo = NULL;
		
		ListaOperacoes* op = NULL;
		ListaOperacoes* mo = NULL;
		Maquinaa* m = NULL;
		ListaMaquinaa* mac = NULL;
		if (fgets(texto, MAX, fp) != NULL)
		{

			sscanf(texto, "%d;%d;%d;%d", &aux.cod, &aux.op, &aux.codm, &aux.tempo);
			printf("LIDO: %d - %d - %d - %d \n", aux.cod, aux.op, aux.codm, aux.tempo);
			
				root = AdicionaNode(root, aux.cod);
				op = CriaOperacao(aux.op);
				root = AdicionaOper(root, op, aux.cod);
				if (aux.op > 0) {
					m = CriaMaquina(aux.codm, aux.tempo, "");
					m = CriaNodoListaMaquinas(m);
					Node* search = ProcuraArvore(root, aux.cod);
					/*ListaOperacoes* proc = ProcuraOperacao(search->data.oper,aux.op);*/
					search->data.oper = InsereMaquinaOperacaoOrd(search->data.oper, m, aux.op);
					//CUIDADO PODE TER ALGUM ERRO INSERIR MAQUINAS ORDENADAS
				}
			}

			
		}
	
	fclose(fp);

	
	return root;
}


#pragma endregion

