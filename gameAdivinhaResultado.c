#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct {
    int dificuldade;
    int valor1;
    int valor2;
    int operacao;
    int resultado;

}Calcular;

int somar(int, Calcular);
int diminuir(int, Calcular);
int multiplicar(int, Calcular);
void jogar();
void mostrarInfo(Calcular calc);

int pontos = 0;

int main() {
    srand(time(NULL));
    
    jogar();

    return 0;
}

void jogar() {
    Calcular calc;
    int dificuldade;


    puts("Informe o nivel de dificuldade desejado [1,2,3 ou 4]:\n");
    scanf("%d", &dificuldade);
    calc.dificuldade = dificuldade;
    calc.operacao = rand() % 3;

    if(calc.dificuldade == 1) {
        //facil
        calc.valor1 = rand() % 11;//0 a 10
        calc.valor2 = rand() % 11;
    }else if(calc.dificuldade == 2) {
        //media
        calc.valor1 = rand() % 101;//0 a 100 
        calc.valor2 = rand() % 101;
    }else if(calc.dificuldade == 3) {
        //dificil
        calc.valor1 = rand() % 1001; // 0 a 1000
        calc.valor2 = rand() % 1001;
    }else if(calc.dificuldade == 4) {
        //insano
        calc.valor1 = rand() % 10001; // 0 a 10000
        calc.valor2 = rand() % 10001;
    }else 
        puts("opção inválida");

        int resposta;
        puts("Informe o resultado para a seguinte operação");

        if(calc.operacao == 0) {
            printf("%d + %d\n", calc.valor1, calc.valor2);
            scanf("%d", &resposta);

            if(somar(resposta, calc)) {
                pontos += 1;
                printf("Voce tem %d ponto(s). \n", pontos);
            }
        }else if(calc.operacao == 1) {
            printf("%d - %d\n", calc.valor1, calc.valor2);
            scanf("%d", &resposta);

            if(diminuir(resposta, calc)) {
                pontos += 1;
                printf("Voce tem %d ponto(s). \n", pontos);
            }

        }else if(calc.operacao == 2) {
            printf("%d * %d\n", calc.valor1, calc.valor2);
            scanf("%d", &resposta);

            if(multiplicar(resposta, calc)) {
                pontos += 1;
                printf("Voce tem %d ponto(s). \n", pontos);
            }
        }else 
            puts("Opção desconhecida\n");

        puts("Deseja continuar jogando ? [1- s, 0- n]\n");
        int continuar;
        scanf("%d", &continuar);
        
        if(continuar == 1)
            jogar();
        else if(continuar == 0) {
            printf("Voce finalizou com %d ponto(s)\n", pontos);
            exit(0);
        }else 
            puts("opção inválida");

}

void showInfo(Calcular calc) {
    char op[25];

    if(calc.operacao == 0) {
        sprintf(op, "Somar");
    }else if(calc.operacao == 1)
        sprintf(op, "Diminuir");    
    else if(calc.operacao == 2)
        sprintf(op,"Multiplicar");
    else 
        sprintf(op, "Operação desconhecida");

    printf("Valor 1: %d\nValor 2: %d\nDificuldade: %d \nOperação %s",
            calc.valor1, calc.valor2, calc.dificuldade, op);
}

int somar(int resposta, Calcular calc) {
    int resultado = calc.valor1 + calc.valor2;
    calc.resultado = resultado;
    int certo = 0;

    if(resposta == calc.resultado) {
        puts("Resposta coreta!\n");
        certo = 1;
    }else {
        puts("Resposta incorreta\n");
        certo = 0;
    }

    printf("%d + %d = %d\n", calc.valor1, calc.valor2, calc.resultado);
    return certo;
}

int diminuir(int resposta, Calcular calc) {
    int resultado = calc.valor1 - calc.valor2;
    calc.resultado = resultado;
    int certo = 0;

    if(resposta == calc.resultado) {
        puts("Resposta coreta!\n");
        certo = 1;
    }else {
        puts("Resposta incorreta\n");
        certo = 0;
    }

    printf("%d - %d = %d\n", calc.valor1, calc.valor2, calc.resultado);
    return certo;

}

int multiplicar(int resposta, Calcular calc) {
    int resultado = calc.valor1 * calc.valor2;
    calc.resultado = resultado;
    int certo = 0;

    if(resposta == calc.resultado) {
        puts("Resposta coreta!\n");
        certo = 1;
    }else {
        puts("Resposta incorreta\n");
        certo = 0;
    }

    printf("%d * %d = %d\n", calc.valor1, calc.valor2, calc.resultado);
    return certo;


}
