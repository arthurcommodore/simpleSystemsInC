#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

typedef struct {
    int codigo;
    char nome[30];
    float preco;
}Produto;

typedef struct {
    Produto produto;
    int qtd;
}Carrinho;

void infoProduto(Produto); 
void menu();
void insertProduto();
void showProdutos();
void comprarProduto();
void showCarrinho();
Produto getProduto(int);
int * temNoCarrinho(int);
void fecharPedido();

static int count_produto = 0;
static int count_carrinho = 0;
static Carrinho carrinho[50];
static Produto produtos[50];


int main() {
    menu();
    return 0;
}

void infoProduto(Produto prod) {
    printf("Código %d\nNome; %s \nPreço: %.2f\n", prod.codigo, strtok(prod.nome, "\n"), prod.preco);
}

void menu() {
    puts("=========================================================\n");
    puts("====================== Bem vindo(a)======================\n");
    puts("====================== Geek Shop======================\n");
    puts("=========================================================\n");

    puts("Selecione uma opção abaixo");
    puts("1- Cadastrar produto\n");
    puts("2- Listar produtos\n");
    puts("3- Comprar produtos\n");
    puts("4- Visualizar o carrinho \n");
    puts("5- Fechar pedido \n");
    puts("6- Sair do sistema\n");

    int option;
    scanf("%d", &option);
    getchar();

    switch(option) {
        case 1: 
            insertProduto();
            break;
        case 2:
            showProdutos();
            break;
        case 3:
            comprarProduto();
            break;
        case 4:
            showCarrinho();
            break;
        case 5:
            fecharPedido();
            break;
        case 6:
            puts("Volte sempre!");
            sleep(2);
            exit(0);
            break;
        default:
            puts("Opcao invalida");
            menu();
            break;

    }
}

void insertProduto() {
    puts("Cadastro de produo\n");
    puts("=================\n");

    puts("Informe o nome do produto\n");
    fgets(produtos[count_produto].nome, 30, stdin);

    puts("Informe o preço do produto\n");
    scanf("%f", &produtos[count_produto].preco);

    printf("O produto %s foi cadastrado sucesso. \n", strtok(produtos[count_produto].nome, "\n"));

    produtos[count_produto].codigo = (count_produto + 10);
    count_produto++;
    menu();
}

void showProdutos() {
    if(count_produto > 0) {
        puts("Listagem de produtos.\n");
        puts("---------------------\n");
        for(int i = 0; i < count_produto; i++) {
            infoProduto(produtos[i]);
            puts("---------------------\n");
            sleep(1);
            menu();
        }
    }else {
        puts("Não temos produtos cadastrados");
        sleep(2);
        menu();
    }
}

void comprarProduto() {
    if(count_produto > 0) {
        printf("Informe o código do produto que deseja adicionar ao carrinho.\n");

        for(int i = 0; i < count_produto; i++) {
            printf("Produto: %s\n Preco: %.2f\n",produtos[i].nome, produtos[i].preco);
            printf("COD: %d\n", produtos[i].codigo);
        }
        int codigo;
        scanf("%d", &codigo);
        getchar();

        int temMercado = 0;
        for(int i = 0; i < count_produto; i++) {
            if(produtos[i].codigo == codigo) {
                temMercado = 1;

                if(count_carrinho > 0) {
                    int * result = temNoCarrinho(codigo);

                    if(result[0] == 1) {
                        carrinho[result[1]].qtd++;
                        puts("foi aumentado a quantidade do produto já existente no carrinho");
                        infoProduto(carrinho[result[1]].produto);
                        menu();
                    }else {
                        Produto p = getProduto(codigo); 
                        carrinho[count_carrinho].produto = p;
                        carrinho[count_carrinho].qtd = 1;
                        count_carrinho++;
                        printf("O produto %s foi adicionado ao carrinho.\n", strtok(p.nome, "\n"));
                        menu();
                    }

                }else {
                    Produto p = getProduto(codigo); 
                    carrinho[count_carrinho].produto = p;
                    carrinho[count_carrinho].qtd = 1;
                    count_carrinho++;
                    printf("O produto %s foi adicionado ao carrinho.\n", strtok(p.nome, "\n"));
                    menu();
                }
            }        
        }

        if(temMercado < 0) {
           puts("Não foi encontrado o produto com código passado\n"); 
        }
    }else  {
        puts("Ainda não existem produtos para vender\n");
        sleep(2);
        menu();
    }
}

void showCarrinho() {
    if(count_carrinho > 0) {
        puts("Produtos do carrinho!");
        puts("---------------------\n");
        for(int i = 0; i < count_produto; i++) {
            infoProduto(carrinho[i].produto);
            printf("Quantidade: %d\n", carrinho[i].qtd);
            puts("---------------------\n");
            sleep(1);
            menu();
        }
    }else {
        puts("Carrinho vazio");
        menu();
    }
}

Produto getProduto(int codigo) {
    Produto p;
    for(int i = 0; i < count_produto; i++) {
        if(produtos[i].codigo == codigo) {
            p = produtos[i];
        }
    }
    return p;
}

int* temNoCarrinho(int codigo) {
    int static retorno[] = {0,0};
    for(int i = 0; i < count_produto; i++) {
        if(carrinho[i].produto.codigo == codigo) {
            retorno[0] = 1; //tem o produto com este codigo no carrinho
            retorno[1] = i; //omdoce do produto no carrinho
        }
    }
    return retorno;
}

void fecharPedido() {
    if(count_carrinho > 0) {
        float valorTotal = 0.0;
        puts("Produtos do carrinho\n");
        puts("---------------------\n");
        for(int i = 0; i < count_carrinho; i++) {
            Produto p = carrinho[i].produto;
            int qtd = carrinho[i].qtd;
            valorTotal += p.preco * qtd;
            infoProduto(p);
            printf("Quantidade: %d\n", qtd);
            sleep(1);
        }
        printf("Sua fatura: %.2f\n", valorTotal);

        //limpar carrinho
        count_carrinho = 0;
        puts("Obrigado!\n");
        menu();
    }else {
        puts("Vocẽ não tem nenhum produto no carrinho ainda.\n");
        menu();
    }
}
