#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Struct do Produto Registrado
typedef struct Produto {
    int id;
    char nome[50];
    char sabor[50];
    float precoKG;
    float peso;
    float total;
    struct Produto* esq;
    struct Produto* dir;
} Produto;

// Struct de Auxilio a Impressao da Arvore
typedef struct Trunk{
    struct Trunk *prev;
    char *str;
}Trunk; 

// Função para calcular o valor total do produto (Valor kg * peso)
float calctot(float precoKG, float peso) {
    return precoKG * peso;
}


// Função para criar um ID aleatório único para cada produto
int criaId() {
    srand(time(NULL));
    return rand();
}


// Função para criar um novo produto chamando a funcao de criar id pro id e de calcular o total pro total e ponteiros para a esquerda e direita da arvore
Produto* criaProduto(char nome[50], char sabor[50], float precoKG, float peso) {
    Produto* novoProduto = (Produto*)malloc(sizeof(Produto));
    novoProduto->id = criaId();
    strcpy(novoProduto->nome, nome);
    strcpy(novoProduto->sabor, sabor);
    novoProduto->precoKG = precoKG;
    novoProduto->peso = peso;
    novoProduto->total = calctot(precoKG, peso);
    novoProduto->esq = NULL;
    novoProduto->dir = NULL;
    return novoProduto;
}

// Função para inserir um produto na árvore (apenas quando ele achar uma raiz nula vai chamar a funcao cria produto para inserir o produto).
Produto* insereProduto(Produto* raizArvore, char nome[50], char sabor[50], float precoKG, float peso) {
    if (raizArvore == NULL) {
        return criaProduto(nome, sabor, precoKG, peso);
    }

    // Verifica se já existe um produto com o mesmo nome e sabor e impede de registra-lo.  
	// cmp < 0 = produto a ser inserido vem primeiro de forma alfabetica que a raiz e é jogado na esquerda
    // cmp > 0 = produto a ser inserido vem depois de forma alfabetica que a raiz e é jogado na direita
    // cmp == 0 = produto a ser inserido é o mesmo que o da raiz
    
    // cmp do nome recebe o valor comparativo entre o nome do produto a ser inserido e o da raiz. (-1,0,1)
    int cmp = strcmp(nome, raizArvore->nome);
    // cmp do nome = -1, continua procurando na esquerda
    if (cmp < 0) {
        raizArvore->esq = insereProduto(raizArvore->esq, nome, sabor, precoKG, peso);
    // cmp do nome = +1, continua procurando na direita
    } else if (cmp > 0) {
        raizArvore->dir = insereProduto(raizArvore->dir, nome, sabor, precoKG, peso);
    } else {
    // se caiu aqui, cmp do nome = 0 e agora compara o cmp do sabor
        cmp = strcmp(sabor, raizArvore->sabor);
    // se cmp do sabor = 0 entao nome e sabor iguais, impede registro e avisa o usuario
        if (cmp == 0) {
            printf("Já existe um registro com o mesmo nome e sabor.\n");
        } else if (cmp < 0) {
    // cmp do sabor = -1, continua procurando na esquerda
            raizArvore->esq = insereProduto(raizArvore->esq, nome, sabor, precoKG, peso);
	// cmp do sabor = +1, continua procurando na direita
        } else {
            raizArvore->dir = insereProduto(raizArvore->dir, nome, sabor, precoKG, peso);
        }
    }
    return raizArvore;
}


// Função para listar os produtos em ordem alfabetica 
void imprime_em_ordem(Produto* raizArvore) {
	// enquanto a raiz nao for nula
    if (raizArvore != NULL) {
    // imprime a esquerda da arvore
        imprime_em_ordem(raizArvore->esq);
    // imprime a raiz da árvore
        printf("ID: %d, nome: %s, sabor: %s, Valor/Kg: %.2f, peso: %.3f kg, Total: %.2f\n", raizArvore->id, raizArvore->nome, raizArvore->sabor, raizArvore->precoKG, raizArvore->peso, raizArvore->total);
	// imprime a direita da arvore
		imprime_em_ordem(raizArvore->dir);
    }
}


// Função para consultar um produto por Nome e Sabor
void consultaProduto(Produto* raizArvore, char nome[50], char sabor[50]) {

    //Se raiz for nula, retorna nulo
    if (raizArvore != NULL) {
        
    	//crio cmp pro nome e sabor para comparar ambos os 2 'ids"
    	int cmp_nome = strcmp(nome, raizArvore->nome);
    	int cmp_sabor = strcmp(sabor, raizArvore->sabor);

    	//Se o cmp do nome e sabor passado for = 0, ou seja, iguais, achamos o produto
    	if (cmp_nome == 0 && cmp_sabor == 0) {
        	printf("ID: %d, Nome: %s, Sabor: %s, Valor/Kg: %.2f, peso: %.3f kg, Total: %.2f\n", raizArvore->id, raizArvore->nome, raizArvore->sabor, raizArvore->precoKG, raizArvore->peso, raizArvore->total);
    	}
    	//Se o cmp do nome for -1 ou o nome for 0 (igual) mas o sabor for -1, continuo procurando ele na esquerda pois vem primeiro alfabeticamente
    	if (cmp_nome < 0 || (cmp_nome == 0 && cmp_sabor < 0)) {
        	consultaProduto(raizArvore->esq, nome, sabor);
    	}
    //caso negativo, procuro na direita pois vem posterior alfabeticamente.
    	 	consultaProduto(raizArvore->dir, nome, sabor);
    }
}


// Função para consultar um produto por Nome
void consultaProdutoNome(Produto* raizArvore, char nome[50]) {
    if (raizArvore != NULL) {
        int cmp_nome = strcmp(nome, raizArvore->nome);
        if (cmp_nome == 0) {
            printf("ID: %d, Nome: %s, Sabor: %s, Valor/Kg: %.2f, peso: %.3f kg, Total: %.2f\n", raizArvore->id, raizArvore->nome, raizArvore->sabor, raizArvore->precoKG, raizArvore->peso, raizArvore->total);
        }
        if (cmp_nome <= 0) {
            consultaProdutoNome(raizArvore->esq, nome);
        }
        if (cmp_nome >= 0) {
            consultaProdutoNome(raizArvore->dir, nome);
        }
    }
}


// Função para encontrar o nó mais à direita (o maior Nome e Sabor)
Produto* maiorNo(Produto* raizArvore) {
    //enquanto nao chegar no nulo, ando pra direita
	while (raizArvore->dir != NULL) {
        raizArvore = raizArvore->dir;
    }

    return raizArvore;
}


// Função para consultar produtos acima do preço total calculado
void consultaValorMaiorQue(Produto* raizArvore, float Valor) {
    // enquanto a raiz nao for nula, consulto todos os produtos à esquerda
	if (raizArvore != NULL) {
        consultaValorMaiorQue(raizArvore->esq, Valor);
    // se campo total da raiz que estou for maior que o informado pelo usuário, imprimo todos os elementos da struct do nó em que estou
        if (raizArvore->total > Valor) {
            printf("ID: %d, Nome: %s, Sabor: %s, Valor/Kg: %.2f, peso: %.3f kg, Total: %.2f\n", raizArvore->id, raizArvore->nome, raizArvore->sabor, raizArvore->precoKG, raizArvore->peso, raizArvore->total);
        }
    // enquanto a raiz nao for nula, consulto todos os produtos à direita
        consultaValorMaiorQue(raizArvore->dir, Valor);
    }
}

// Função para excluir um produto pelo Nome e Sabor
Produto* excluiProduto(Produto* raizArvore, char nome[50], char sabor[50]) {
	// se raiz for nula, nao achei o produto e aviso o usuário que não encontrei.
    if (raizArvore == NULL) {
	printf("Registro não encontrado para exclusao.\n");
        return raizArvore;
    }
	
	//crio cmp pro nome e sabor para comparar ambos os 2 'ids"
    int cmp_nome = strcmp(nome, raizArvore->nome);
    int cmp_sabor = strcmp(sabor, raizArvore->sabor);
	//Se o cmp do nome for -1 ou o nome for 0 (igual) mas o sabor for -1, continuo procurando ele na esquerda pois vem primeiro alfabeticamente
    if (cmp_nome < 0 || (cmp_nome == 0 && cmp_sabor < 0)) {
        raizArvore->esq = excluiProduto(raizArvore->esq, nome, sabor);
    //Se o cmp do nome for +1 ou o nome for 0 (igual) mas o sabor for +1, continuo procurando ele na direita pois vem posterior alfabeticamente
    } else if (cmp_nome > 0 || (cmp_nome == 0 && cmp_sabor > 0)) {
        raizArvore->dir = excluiProduto(raizArvore->dir, nome, sabor);
    } 	else {

    // senao, cmp nome e sabor estão com valores 0, logo, ele encontrou o produto a ser excluído. 
	// informo pro usuario que aquele produto e nome foi excluido
	printf("Registro excluido: Nome: %s, Sabor: %s\n", raizArvore->nome, raizArvore->sabor);
	
	//CASO DE EXCLUSÃO DE PAI COM APENAS 1 FILHO OU SEM FILHOS
	// Se ele não tem filhos a esquerda, ou seja, null, insiro o filho mais a direita no lugar dele e excluo o nó pai
        if (raizArvore->esq == NULL) {
            Produto* temp = raizArvore->dir;
            free(raizArvore);
            return temp;
    // Se ele não tem filhos a direita, ou seja, null, insiro o filho mais a esquerda no lugar dele e excluo o nó pai
        } else if (raizArvore->dir == NULL) {
            Produto* temp = raizArvore->esq;
            free(raizArvore);
            return temp;
        }

	//CASO DE EXCLUSÃO DE PAI COM 2 FILHOS
    // Encontrar o nó mais à direita (pego o maior dos filhos)
        Produto* temp = maiorNo(raizArvore->esq);

    // Copio todos os dados da estrutura do maior filho para o nó pai (filho maior passa a ser o pai também)
        strcpy(raizArvore->nome, temp->nome);
        strcpy(raizArvore->sabor, temp->sabor);
        raizArvore->precoKG = temp->precoKG;
        raizArvore->peso = temp->peso;
        raizArvore->total = temp->total;

    // Excluo o filho maior (uma vez que ele já assumiu o papel de pai e está repetido)
        raizArvore->esq = excluiProduto(raizArvore->esq, temp->nome, temp->sabor);
    }

        return raizArvore;
}


// IMPRIMIR A ARVORE DE FORMA AMIGAVEL NO CMD
  Trunk *cria_trunk(Trunk *prev, char *str){
  Trunk *novo = (Trunk*)malloc(sizeof(Trunk));
  novo->prev = prev;
  novo->str = str;
  return novo;
}

void showTrunks(Trunk *p){
    if (p == NULL)
        return;

    showTrunks(p->prev);

    printf("%s", p->str);
}

void printTree(Produto *root, Trunk *prev, int isLeft){
    if (root == NULL)
        return;
    
    char *prev_str = "    ";
    Trunk *trunk = cria_trunk(prev, prev_str);

    printTree(root->dir, trunk, 1);

    if (!prev)
        trunk->str = "---";
    else if(isLeft)
    {
        trunk->str = ".---";
        prev_str = "   |";
    }
    else
    {
        trunk->str = "`---";
        prev->str = prev_str;
    }

    showTrunks(trunk);
    printf("%s %s (R$%.2f / %.3fKg / R$%.2f)\n", root->nome, root->sabor, root->precoKG, root->peso, root->total); // ** imprime a informacao do nó **

    if(prev)
        prev->str = prev_str;
    trunk->str = "   |";

    printTree(root->esq, trunk, 0);
}

// Função de Alteração de Item
void alteraProduto(Produto* raizArvore, char nome[50], char sabor[50]) {
    
	if (raizArvore != NULL) {
        float novoPreco, novoPeso;
    	//crio cmp pro nome e sabor para comparar ambos os 2 'ids"
    	int cmp_nome = strcmp(nome, raizArvore->nome);
    	int cmp_sabor = strcmp(sabor, raizArvore->sabor);

    	//Se o cmp do nome e sabor passado for = 0, ou seja, iguais, achamos o produto
    	if (cmp_nome == 0 && cmp_sabor == 0) {
        	printf("Informe o novo preço por kg: ");
        	scanf("%f", &novoPreco);
        	printf("Informe o novo peso em kg: ");
        	scanf("%f", &novoPeso);
        	raizArvore->precoKG = novoPreco;
        	raizArvore->peso = novoPeso;
        	raizArvore->total = calctot(novoPreco, novoPeso);
        	printf("Registro atualizado com sucesso!\n");    
    	}
    	//Se o cmp do nome for -1 ou o nome for 0 (igual) mas o sabor for -1, continuo procurando ele na esquerda pois vem primeiro alfabeticamente
    	if (cmp_nome < 0 || (cmp_nome == 0 && cmp_sabor < 0)) {
        	alteraProduto(raizArvore->esq, nome, sabor);
        } else if (cmp_nome > 0 || (cmp_nome == 0 && cmp_sabor > 0)){
        	alteraProduto(raizArvore->dir, nome, sabor);
		}
	}else {
		printf("Registro nao encontrado.\n");
	}
}
    


int main() {

	//Inicio as variaveis e a raiz como nulla e mostro o Menu de Escolhas
    Produto* raizArvore = NULL;
    int opcao, subopcao, id, voltamenu, altera;
    char nome[50], sabor[50];
    float precoKG, peso, Valor;
	
	
	
    while (1) {
        printf("\nMenu da Confeitaria:\n");
        printf("1. Incluir Produto\n");  // Marcos
        printf("2. Listar Produtos\n"); // Natthy
        printf("3. Consultar Produto\n"); // Hugo 
        printf("4. Consultar Produtos acima do total informado\n"); // Hugo
        printf("5. Alterar Produto\n"); // Marcos
		printf("6. Excluir Produto\n"); // Glicerio
        printf("7. Imprimir de Forma Amigavel a Arvore\n"); // Natthy
        printf("8. Inserir Lista Pre Definida\n"); // Marcos
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        

        switch (opcao) {
            case 1:
            	system("cls");
                printf("Informe o Nome do Produto: ");
                scanf("%s", &nome);
                printf("Informe o Sabor do Produto: ");
                scanf("%s", &sabor);
                printf("Informe o Preco por kg do Produto: ");
                scanf("%f", &precoKG);
                printf("Informe o Peso em KG do Produto: ");
                scanf("%f", &peso);
                raizArvore = insereProduto(raizArvore, nome, sabor, precoKG, peso);
				system("cls");
				break;

            case 2:
            	system("cls");
                printf("Registros:\n");
                imprime_em_ordem(raizArvore);
                getch();
				system("cls");
				break;

            case 3:
            	system("cls");
                printf("1. Consultar por Nome (ignorando o Sabor)\n");
                printf("2. Consultar por Nome e Sabor\n");
                printf("Escolha uma opcao: ");
                int subopcao;
                scanf("%d", &subopcao);
                
                if (subopcao == 1) {
                    printf("Informe o nome para consultar: ");
                    scanf("%s", nome);
                    consultaProdutoNome(raizArvore,nome);
				} else if (subopcao == 2) {
                	printf("Informe o Nome do Produto: ");
                	scanf("%s", &nome);
                	printf("Informe o Sabor do Produto: ");
                	scanf("%s", &sabor);
                	consultaProduto(raizArvore,nome,sabor);
                } else {
                    printf("Opcao invalida.\n");
                }
                break;
                getch();
				system("cls");
				break;

            case 4:
                system("cls");
				printf("Informe o preco minimo do Produto: ");
                scanf("%f", &Valor);
                printf("Itens acima de %.2f:\n", Valor);
                consultaValorMaiorQue(raizArvore, Valor);
                getch();
				system("cls");
				break;

            case 5:
				system("cls");
                printf("Registros:\n");
                imprime_em_ordem(raizArvore);
                printf("Qual o Nome do Produto que voce deseja alterar?: \n");
                scanf("%s", &nome);
                printf("Qual o Sabor do Produto que voce deseja alterar?: \n");
                scanf("%s", &sabor);
                alteraProduto(raizArvore, nome, sabor);
                getch();
                system("cls");
                break;

            case 6:
            	system("cls");
                printf("Informe o Nome do Produto: ");
                scanf("%s", &nome);
                printf("Informe o Sabor do Produto: ");
                scanf("%s", &sabor);
                raizArvore = excluiProduto(raizArvore, nome, sabor);
                getch();
				system("cls");
				break;
				
			case 7:
            	system("cls");
            	printTree(raizArvore, NULL , 0); 
            	getch();
				system("cls");
				break;
			               
            case 8:
            	system("cls");
                printf("Lista Pre Definida Inserida...\n");
                raizArvore = insereProduto(raizArvore,"Palha","Italiana",59.99,0.440);		//Palha Italiana
                raizArvore = insereProduto(raizArvore,"Pudim","Leite",29.99,0.330);		//Pudim Leite
                raizArvore = insereProduto(raizArvore,"Pudim","Pao",24.99,0.360);			//Pudim Pao
                raizArvore = insereProduto(raizArvore,"Torta","Alema",59.99,0.630);		//Torta Alema
                raizArvore = insereProduto(raizArvore,"Torta","Holandesa",59.99,0.640);		//Torta Holandesa
                raizArvore = insereProduto(raizArvore,"Docinho","Casadinho",39.99,0.420);		//Docinho Casadinho
                raizArvore = insereProduto(raizArvore,"Docinho","Brigadeiro",39.99,0.540);	//Docinho Brigadeiro
                raizArvore = insereProduto(raizArvore,"Docinho","Beijinho",39.99,0.610);		//Docinho Beijinho
                raizArvore = insereProduto(raizArvore,"Torta","Morango",59.99,0.650);		//Torta Morango
                raizArvore = insereProduto(raizArvore,"Brownie","Chocolate",89.99,0.340);		//Brownie Chocolate
                raizArvore = insereProduto(raizArvore,"Brownie","DoceLeite",89.99,0.370);		//Brownie DoceLeite
                raizArvore = insereProduto(raizArvore,"Cupcake","Festa",9.90,1);			//CupCake Festa
                raizArvore = insereProduto(raizArvore,"Bolo","Aipim",29.99,0.470);		//Bolo Aipim
                raizArvore = insereProduto(raizArvore,"Bolo","Chocolate",29.99,0.570);		//Bolo Chocolate
                raizArvore = insereProduto(raizArvore,"Bolo","Laranja",29.99,0.470);		//Bolo Laranja
                raizArvore = insereProduto(raizArvore,"Bolo","Fuba",29.99,0.530);			//Bolo Fuba
                raizArvore = insereProduto(raizArvore,"Torta","Chocolate",59.99,1);		//Torta Chocolate
                raizArvore = insereProduto(raizArvore,"Bolo","Cenoura",29.99,0.880);		//Bolo Cenoura
                getch();
				system("cls");
				break;
             
			case 0:
                printf("Saindo do programa...\n");
                exit(0);   
            
			default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }

return 0;
}