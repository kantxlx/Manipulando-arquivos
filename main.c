#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

Aluno lerDadosAlunoDoCSV(FILE *arquivo) {
    Aluno aluno;
    char temp[200];

    fgets(temp, sizeof(temp), arquivo);
    sscanf(temp, "%[^,],%[^,],%[^,],%lf,%lf", aluno.nome, aluno.telefone, aluno.curso, &aluno.nota1, &aluno.nota2);

    aluno.telefone[12] = '\0';

    calcularNotaFinal(&aluno);

    return aluno;
}

void escreverDadosAlunoNoCSV(Aluno aluno, FILE *arquivo) {
    fprintf(arquivo, "%s,%.2f,%s\n", aluno.nome, aluno.notaFinal, aluno.situacao);
}

int main() {
    FILE *arquivoEntrada = fopen("C:\\Users\\caua8\\OneDrive\\Documentos\\codigos e projetos\\Algoritmos facul Noturn\\Trabalho estrutura de dados\\DadosEntrada.csv", "r");
    FILE *arquivoSaida = fopen("SituacaoFinal.csv", "w");

    if (arquivoEntrada == NULL || arquivoSaida == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        exit(1);
    }

    Aluno aluno;
    while (fscanf(arquivoEntrada, "%[^,],%[^,],%[^,],%lf,%lf", aluno.nome, aluno.telefone, aluno.curso, &aluno.nota1, &aluno.nota2) != EOF) {
        calcularNotaFinal(&aluno);
        imprimirDadosAluno(aluno);
        escreverDadosAlunoNoCSV(aluno, arquivoSaida);
    }

    fclose(arquivoEntrada);
    fclose(arquivoSaida);

    return 0;
}
