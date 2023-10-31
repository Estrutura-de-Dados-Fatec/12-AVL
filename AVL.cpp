#include <iostream>
using namespace std;

// definicao de tipo
struct NO {
	int valor;
	NO* esq;
	NO* dir;
	int altura; // usada para balanceamento
};

NO* raiz = NULL;

// headers
// estrutura principal
void menu();
void inicializar();
void inserir();
void exibir();
void exibirQuantidade();
void buscar();



// funcoes auxiliares Arvore
NO* insereArvore(NO* no, int valor);
NO* criaNO(int valor);
int elementosArvore(NO* no);
void exibirElementosArvore(NO* no, int qtespacos);
void buscarElementoArvore(NO* no, int valor);
//--------------------------

// funcoes auxiliares balaceamento
int alturaNo(NO* no);
int fatorBalanceamento(NO* no);
int max(int a, int b);
NO* girarDireita(NO* no);
NO* girarEsquerda(NO* no);
//--------------------------


int main()
{
	menu();
}

void menu()
{
	int op = 0;
	while (op != 6) {
		system("cls"); // somente no windows
		cout << "Menu Arvore";
		cout << endl << endl;
		cout << "1 - Inicializar Arvore \n";
		cout << "2 - Exibir quantidade de elementos \n";
		cout << "3 - Inserir elemento \n";
		cout << "4 - Exibir elementos \n";
		cout << "5 - Buscar elemento \n";
		cout << "6 - Sair \n";

		cout << "Opcao: ";
		cin >> op;

		switch (op)
		{
		case 1: inicializar();
			break;
		case 2:exibirQuantidade();
			break;
		case 3: inserir();
			break;
		case 4: exibir();
			break;
		case 5: buscar();
			break;
		default:
			break;
		}

		system("pause"); // somente no windows
	}
}

void inicializar()
{
	raiz = NULL;
	cout << "Arvore inicializada \n";
}


void inserir()
{
	int valor;
	cout << "Digite o elemento: ";
	cin >> valor;
	raiz = insereArvore(raiz, valor);
}

void exibirQuantidade() {
	cout << "Quantidade de elementos: " << elementosArvore(raiz) << endl;

}

void exibir() {
	exibirElementosArvore(raiz, 0);
}

void buscar() {
	int valor;
	cout << "Digite o elemento: ";
	cin >> valor;
	buscarElementoArvore(raiz, valor);
}


NO* criaNO(int valor)
{
	NO* novo = (NO*)malloc(sizeof(NO));
	if (novo == NULL)
	{
		return NULL;
	}
	novo->valor = valor;
	novo->esq = NULL;
	novo->dir = NULL;
	novo->altura = 0;
	return novo;
}


int alturaNo(NO* no)
{
	if (no == NULL) {
		return -1;
	}
	else {
		return no->altura;
	}
}

int fatorBalanceamento(NO* no)
{
	if (no == NULL) {
		return 0;
	}
	return alturaNo(no->esq) - alturaNo(no->dir);
}


int max(int a, int b)
{
	if (a > b) {
		return a;
	}
	else {
		return b;
	}
}


NO* insereArvore(NO* no, int valor)
{

	if (no == NULL) {
		// arvore vazia
		return criaNO(valor);
	}
	else if (valor < no->valor) {
		// insere na subarvore esquerda
		no->esq = insereArvore(no->esq, valor);
	}
	else if (valor > no->valor) {
		// insere na subarvore direita
		no->dir = insereArvore(no->dir, valor);
	}
	else {
		// valor ja existe
		return no;
	}

	// atualiza a altura do no (lembre-se que esta é função recursiva)

	no->altura = max(alturaNo(no->esq), alturaNo(no->dir)) + 1;

	// calcula o fator de balanceamento
	int fator = fatorBalanceamento(no);

	// verifica se precisa balancear
	if (fator > 1 && valor < no->esq->valor) {
		return girarDireita(no);
	}
	if (fator < -1 && valor > no->dir->valor) {
		return girarEsquerda(no);
	}
	if (fator > 1 && valor > no->esq->valor) {
		no->esq = girarEsquerda(no->esq);
		return girarDireita(no);
	}
	if (fator < -1 && valor < no->dir->valor) {
		no->dir = girarDireita(no->dir);
		return girarEsquerda(no);
	}
	return no;

}

NO* girarDireita(NO* no)
{
	// sua implementação vai aqui
	NO* aux1 = no->esq;
	NO* aux2 = aux1->dir;

	aux1->dir = no;
	no->esq = aux2;

	no->altura = max(alturaNo(no->esq), alturaNo(no->dir)) + 1;
	aux1->altura = max(alturaNo(no->esq), alturaNo(no->dir)) + 1;

	return aux1;
}

NO* girarEsquerda(NO* no)
{
	// sua implementação vai aqui

	NO* aux1 = no->dir;
	NO* aux2 = aux1->esq;

	aux1->esq = no;
	no->dir = aux2;

	no->altura = max(alturaNo(no->esq), alturaNo(no->dir)) + 1;
	aux1->altura = max(alturaNo(no->esq), alturaNo(no->dir)) + 1;

	return aux1;
}

int elementosArvore(NO* no)
{
	if (no == NULL) {
		return 0;
	}

	return 1 + elementosArvore(no->esq) + elementosArvore(no->dir);
}


// simula a hierarquia da arvore usando espacos e exibe os elementos 
// horizontalmente 
void exibirElementosArvore(NO* no, int qtEspacos)
{
	const int espaco = 4;

	if (no == NULL) {
		return;
	}
	qtEspacos += espaco;

	//exibe a subarvore da direita
	exibirElementosArvore(no->dir, qtEspacos);
	cout << endl;

	for (int i = espaco; i < qtEspacos; i++)
		cout << " ";

	// exibir o no atual
	cout << no->valor << endl;

	//exibe a subarvore da esquerda
	exibirElementosArvore(no->esq, qtEspacos);

}

void buscarElementoArvore(NO* no, int valor)
{
	if (no == NULL) {
		cout << "Elemento nao encontrado \n";
		return;
	}

	if (no->valor == valor) {
		cout << "Elemento encontrado \n";
		return;
	}

	if (valor < no->valor) {
		buscarElementoArvore(no->esq, valor);
	}
	else {
		buscarElementoArvore(no->dir, valor);
	}
}


// versao nao recursiva
NO* buscarElementoArvoreComPai(NO* no, int valor, NO*& pai)
{
	NO* atual = no;
	pai = NULL;
	while (atual != NULL) {
		if (valor == atual->valor) {
			return atual;
		}
		else {
			pai = atual;

			if (valor < atual->valor) {
				atual = atual->esq;
			}
			else {
				atual = atual->dir;
			}
		}
	}
	return NULL;
}








