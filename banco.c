#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>

typedef struct {
    int codigo;
    char nome[50];
    char email[50];
    char cpf[20];
    char dataNascimento[20];
    char dataCadastro[20];
}Cliente;

typedef struct {
    int numero;
    Cliente cliente;
    float saldo;
    float limite;
    float saldoTotal;
}Conta;

void menu();
void infoCliente(Cliente);
void infoConta(Conta);
void insertConta();
void efetuarSaque();
void efetuarDeposito();
void efetuarTransferencia();
void showContas();
float updateSaldoTotal(Conta conta);
Conta searchConta(int num);
void sacar(Conta conta, float valor);
void depositar(Conta conta, float valor);
void transferir(Conta contaOrigem, Conta contaDestino, float valor);

static Conta contas[50];
static int count_contas = 0;
static int count_clientes = 0;


int main() {
    menu();

    return 0;
}

void menu() {
    int option = 0;
    puts("================================================\n");
    puts("===================== ATM ======================\n");
    puts("=================== Geek Bank ==================\n");
    puts("================================================\n");

    puts("Selecione uma opção no menu\n");
    puts("1- Criar conta\n");
    puts("2- Efetuar saque\n");
    puts("3- Efetuar deposito\n");
    puts("4- Efetuar transferencia\n");
    puts("5- Listar contas\n"); 
    puts("6- Sair do sistema\n");

    scanf("%d", &option);
    getchar();

    switch(option) {
        case 1:
            insertConta();
            break;
        case 2:
            efetuarSaque();
            break;
        case 3:
            efetuarDeposito();
            break;
        case 4:
            efetuarTransferencia();
            break;
        case 5:
            showContas();
            break;
        case 6:
            puts("Até a próxima\n");
            sleep(2);
            exit(0);
        default:
            puts("Opção inválida\n");
            sleep(2);
            menu();
            break;
    }
}

void infoCliente(Cliente cliente) {
   printf("Código: %d \nNome: %s \nData de nascimento: \nE-mail: %s \n%s\nCadastro: %s\n",
           cliente.codigo, strtok(cliente.nome, "\n"), strtok(cliente.dataNascimento, "\n"),
           strtok(cliente.email, "\n") ,strtok(cliente.dataCadastro, "\n"));  
}

void infoConta(Conta conta) {
    printf("Número da conta: %d \nCliente: %s \nData de Nascimento: %s \nData Cadastro: %s \nSaldo Total: %.2f\n", 
            conta.numero, strtok(conta.cliente.nome, "\n"), 
            strtok(conta.cliente.dataNascimento, "\n"), 
            strtok(conta.cliente.dataCadastro, "\n"), conta.saldoTotal);
}

void insertConta() {
    Cliente cliente;

    char dia[3];
    char mes[3];
    char ano[5];
    char dataCadastro[20];
    time_t t = time(NULL);
    struct tm tm = *localtime(&t);

    //formatando data
    if(tm.tm_mday < 10) {
        sprintf(dia, "0%d", tm.tm_mday);
    }else {
        sprintf(mes, "%d", tm.tm_mday );
    }

    if( (tm.tm_mon + 1) < 10) {
        sprintf(mes, "0%d", tm.tm_mon + 1);
    }else {
        sprintf(mes, "%d", tm.tm_mon + 1);
    }

    sprintf(ano, "%d", tm.tm_year + 1900);
    
    //formatando data
    strcpy(dataCadastro, "");
    strcat(dataCadastro, dia);
    strcat(dataCadastro, "/");
    strcat(dataCadastro, mes);
    strcat(dataCadastro, "/");
    strcat(dataCadastro, ano);
    strcat(dataCadastro, "\0");
    strcpy(cliente.dataCadastro, dataCadastro);

    //Inserindo os dados
    puts("Informe os dados do cliente:\n");
    cliente.codigo = count_clientes + 10;

    puts("Nome do cliente: \n");
    fgets(cliente.nome, 50, stdin);

    puts("E-mail do cliente \n");
    fgets(cliente.email, 50, stdin);

    puts("Data de nasciento do cliente");
    fgets(cliente.dataNascimento, 20, stdin);
    
    count_clientes++; 

    //Criando conta
    contas[count_contas].numero = count_contas + 10;
    contas[count_contas].cliente = cliente;
    contas[count_contas].saldo = 0.0;
    contas[count_contas].limite = 0.0;
    contas[count_contas].saldoTotal = updateSaldoTotal(contas[count_contas]);
    
    puts("Conta criada com sucesso!\n");
    puts("Dados da conta criada\n"); 
    infoConta(contas[count_contas]);
    count_contas++;

    sleep(2);
    menu();
}

float updateSaldoTotal(Conta conta) {
    return conta.saldo + conta.limite;
}

Conta searchConta(int num) {
    Conta c;
    if(count_contas > 0) {
        for(int i = 0; i < count_contas; i++) {
            if(contas[i].numero == num)
                c = contas[i];
        }
    }
    return c;
}

void sacar(Conta conta, float valor) {
    if(valor > 0 && conta.saldoTotal >= valor) {
        for(int i = 0; i > count_contas; i++) {
            if(contas[i].numero == conta.numero) {
                if(contas[i].saldo >= valor) {
                    contas[i].saldo = contas[i].saldo - valor;
                    contas[i].saldoTotal = updateSaldoTotal(contas[i]);
                    puts("Saque efetuado com sucesso\n");
                }else {
                    float restante = contas[i].saldo + valor;
                    contas[i].limite = contas[i].limite- valor;
                    contas[i].saldo = 0.0;
                    contas[i].saldoTotal = updateSaldoTotal(contas[i]);
                    puts("Saque efetuado com sucesso!\n");
                }
            }
        } 
    }else {
        puts("Saque n'ao realizado. Tente novamente\n");
    }
}

void depositar(Conta conta, float valor) {
    if(valor > 0) {
        for(int i = 0; i < count_contas; i++) {
            if(contas[i].numero == conta.numero) {
                contas[i].saldo = contas[i].saldo + valor;
                contas[i].saldoTotal = updateSaldoTotal(contas[i]);
                puts("Deposito efetuado com sucesso");
            }
        }
    }else
        puts("Erro ao efetuar deposito\n");
}

void transferir(Conta contaOrigem, Conta contaDestino, float valor) {
    if(valor > 0 && contaOrigem.saldoTotal >= valor) {
        int indiceOrigem = -1, indiceDestino = -1;
        for(int i = 0; i < count_contas; i++) {
            if(contas[i].numero == contaOrigem.numero) {
                indiceOrigem = i;
            }
        }      

        for(int i = 0; i < count_contas; i++) {
            if(contas[i].numero == contaDestino.numero)
                indiceDestino = i;
        }

        if(indiceOrigem >= 0 && indiceDestino >= 0) {
            if(contas[indiceOrigem].saldo >= valor) {
                contas[indiceOrigem].saldo = contas[indiceOrigem].saldo - valor;
                contas[indiceDestino].saldo = contas[indiceDestino].saldo + valor;
                contas[indiceOrigem].saldoTotal = updateSaldoTotal(contas[indiceOrigem]);
                contas[indiceDestino].saldoTotal = updateSaldoTotal(contas[indiceDestino]);
                puts("Transferencia realizada com sucesso");
            }else {
                float restante = contas[indiceOrigem].saldo - valor;
                contas[indiceOrigem].limite = contas[indiceOrigem].limite + restante;
                contas[indiceOrigem].saldo  = 0.0;
                contas[indiceDestino].saldo = contas[indiceDestino].saldo + valor;
                contas[indiceOrigem].saldoTotal = updateSaldoTotal(contas[indiceOrigem]);
                puts("Transferencia realizada com sucesso!\n");
            }
        }else 
            puts("Não foi possível realizar a tranferência\n");
    
    }else 
       puts("Transferência não realizada teste novamente. Tente novamente. \n");

}

void efetuarSaque() {
    if(count_contas > 0) {
        int numero;
        puts("Informe o número da conta: \n");             
        scanf("%d", &numero);

        Conta conta = searchConta(numero);

        if(conta.numero == numero) {
            float valor;
            printf("Informe o valor do saque \n");
            scanf("%f", &valor);

            sacar(conta, valor);
        }
    }else
        puts("Ainda não existem contas para saque\n");

    sleep(2);
    menu();
}

void efetuarDeposito() {
    if(count_contas > 0) {
        int numero;
        puts("Informe o número da conta: \n");             
        scanf("%d", &numero);

        Conta conta = searchConta(numero);

        if(conta.numero == numero) {
            float valor;
            printf("Informe o valor do deposito\n");
            scanf("%f", &valor);

            depositar(conta, valor);
        }
    }else
        puts("Ainda não existem contas para deposito\n");

    sleep(2);
    menu();

}

void efetuarTransferencia() {
    if(count_contas > 0) {
        int numeroDestino, numeroOrigem; 
        puts("Informe o número da sua conta: \n");
        scanf("%d", &numeroOrigem);

        Conta contaOrigem = searchConta(numeroOrigem);
        if(contaOrigem.numero == numeroOrigem) {
            puts("Informe o numero da conta destino\n");
            scanf("%d", &numeroDestino);

            Conta contaDestino = searchConta(numeroDestino);
                        
            if(contaDestino.numero == numeroDestino) {
                float valor;
                puts("Informe o valor para a transferencia: \n");
                scanf("%f", &valor);

                transferir(contaOrigem, contaDestino, valor);
            }else {
                printf("A conta destino com número %d não foi encontrada. \n", numeroDestino);
            }
        }

    }else {
        puts("Ainda não existe contas para transferência.\n");
    } 
    sleep(2);
    menu();
} 

void showContas() {
    if(count_contas > 0) {
        for(int i = 0; i < count_contas; i++) {
            infoConta(contas[i]);
            puts("\n");
            sleep(1);
        }
    }else 
        puts("não existe contas cadastras ainda.\n");

    sleep(2);
    menu();
}









