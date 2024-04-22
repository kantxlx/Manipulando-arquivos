#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
    char nome[50];
    char telefone[15];
    char curso[50];
    double nota1;
    double nota2;
    double notaFinal;
    char situacao[10];
} Aluno;

void calcularNotaFinal(Aluno *aluno) {
    aluno->notaFinal = (aluno->nota1 + aluno->nota2) / 2;

    if (aluno->notaFinal >= 7.0)
        strcpy(aluno->situacao, "APROVADO");
    else
        strcpy(aluno->situacao, "REPROVADO");
}

void imprimirDadosAluno(Aluno aluno) {
    printf("%s, %.2f, %s\n", aluno.nome, aluno.notaFinal, aluno.situacao);
}

void lerDadosAlunoDoTerminal(Aluno *aluno) {
    printf("Digite o nome do aluno: ");
    scanf("%s", aluno->nome);
    printf("Digite o telefone do aluno: ");
    scanf("%s", aluno->telefone);
    printf("Digite o curso do aluno: ");
    scanf("%s", aluno->curso);

    bool nota1_valida = false;
    while (!nota1_valida) {
        printf("Digite a primeira nota do aluno: ");
        if (scanf("%lf", &aluno->nota1) == 1) {
            nota1_valida = true;
        } else {
            printf("Entrada inválida. Por favor, insira um número.\n");
            while (getchar() != '\n');
        }
    }

    bool nota2_valida = false;
    while (!nota2_valida) {
        printf("Digite a segunda nota do aluno: ");
        if (scanf("%lf", &aluno->nota2) == 1) {
            nota2_valida = true;
        } else {
            printf("Entrada inválida. Por favor, insira um número.\n");
            while (getchar() != '\n');
        }
    }
}

void escreverDadosAlunoNoCSV(Aluno aluno, FILE *arquivo) {
    fprintf(arquivo, "%s,%s,%s,%.1f,%.1f\n", aluno.nome, aluno.telefone, aluno.curso, aluno.nota1, aluno.nota2);
}

int main() {
    FILE *arquivoEntrada = fopen("../dados_entrada.csv", "w");

    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada.\n");
        exit(1);
    }

    printf("Por favor, insira os dados dos alunos:\n");

    Aluno aluno;
    char continuar;
    do {
        lerDadosAlunoDoTerminal(&aluno);
        escreverDadosAlunoNoCSV(aluno, arquivoEntrada);

        printf("Deseja adicionar outro aluno? (S/N): ");
        scanf(" %c", &continuar);
    } while (continuar == 'S' || continuar == 's');

    fclose(arquivoEntrada);

    arquivoEntrada = fopen("../dados_entrada.csv", "r");
    if (arquivoEntrada == NULL) {
        printf("Erro ao abrir o arquivo de entrada para leitura.\n");
        exit(1);
    }

    printf("\nResultados:\n");
    while (fscanf(arquivoEntrada, "%[^,],%[^,],%[^,],%lf,%lf\n", aluno.nome, aluno.telefone, aluno.curso, &aluno.nota1, &aluno.nota2) != EOF) {
        calcularNotaFinal(&aluno);
        imprimirDadosAluno(aluno);
        getchar();
    }

    fclose(arquivoEntrada);

    return 0;
}
