#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a estrutura de sess�o
typedef struct {
    char filme[50];
    char horario[10];
    int cadeirasDisponiveis;
} Sessao;

// Fun��o para inserir uma nova sess�o
void inserirSessao(Sessao **sessoes, int *numSessoes) {
    *numSessoes += 1;
    *sessoes = (Sessao *) malloc(*numSessoes * sizeof(Sessao));
    //*sessoes = (Sessao*) realloc(*sessoes, (*numSessoes) * sizeof(Sessao));

    printf("Nome do filme: ");
    scanf("%s", (*sessoes)[*numSessoes - 1].filme);

    printf("Horario da sessao: ");
    scanf("%s", (*sessoes)[*numSessoes - 1].horario);

    printf("Quantidade de cadeiras livres: ");
    scanf("%d", &(*sessoes)[*numSessoes - 1].cadeirasDisponiveis);

    printf("Sessao cadastrada com sucesso!\n");
}

// Fun��o para mostrar filmes dispon�veis e respectivas sess�es
void mostrarFilmes(Sessao *sessoes, int numSessoes) {
    printf("\nFilmes disponiveis:\n");
    for (int i = 0; i < numSessoes; i++) {
        printf("%d. %s\n", i + 1, sessoes[i].filme);
    }
}

// Fun��o para buscar por um filme e mostrar hor�rios das sess�es
void buscarFilme(Sessao *sessoes, int numSessoes) {
    char nomeFilme[50];
    printf("Digite o nome do filme: ");
    scanf("%s", nomeFilme);

    for (int i = 0; i < numSessoes; i++) {
        if (strcmp(nomeFilme, sessoes[i].filme) == 0) {
            printf("Horario da sessao: %s\n", sessoes[i].horario);
        }
    }
}

// Fun��o para editar informa��es da sess�o
void editarSessao(Sessao *sessoes, int numSessoes) {
    int numSessao;
    printf("Digite o numero da sessao que deseja editar: ");
    scanf("%d", &numSessao);
    numSessao--;

    if (numSessao >= 0 && numSessao < numSessoes) {
        printf("Novo horario da sessao: ");
        scanf("%s", sessoes[numSessao].horario);

        printf("Nova quantidade de cadeiras livres: ");
        scanf("%d", &sessoes[numSessao].cadeirasDisponiveis);

        printf("Sessao editada com sucesso!\n");
    } else {
        printf("Numero de sessao inv�lido!\n");
    }
}

// Fun��o para remover sess�o
void removerSessao(Sessao **sessoes, int *numSessoes) {
    int numSessao;
    printf("Digite o numero da sessao que deseja remover: ");
    scanf("%d", &numSessao);
    numSessao--;

    if (numSessao >= 0 && numSessao < *numSessoes) {
        for (int i = numSessao; i < *numSessoes - 1; i++) {
            (*sessoes)[i] = (*sessoes)[i + 1];
        }
        *numSessoes -= 1;
        *sessoes = (Sessao*)realloc(*sessoes, (*numSessoes) * sizeof(Sessao));
        printf("Sessao removida com sucesso!\n");
    } else {
        printf("Numero de sessao invalido!\n");
    }
}

// Fun��o para reservar/comprar lugar em uma sess�o espec�fica
void reservarLugar(Sessao *sessoes, int numSessoes) {
    int numSessao;
    printf("Digite o numero da sessao que deseja reservar/comprar lugar: ");
    scanf("%d", &numSessao);
    numSessao--;

    if (numSessao >= 0 && numSessao < numSessoes) {
        if (sessoes[numSessao].cadeirasDisponiveis > 0) {
            sessoes[numSessao].cadeirasDisponiveis--;
            printf("Lugar reservado/comprado com sucesso!\n");
        } else {
            printf("N�o ha cadeiras dispon�veis para esta sessao.\n");
        }
    } else {
        printf("Numero de sessao invalido!\n");
    }
}

// Fun��o principal
int main() {
    Sessao *sessoes = NULL;
    int numSessoes = 0;
    int escolha;

    do {
        printf("\nMenu:\n");
        printf("1. Inserir nova sessao\n");
        printf("2. Mostrar filmes disponiveis\n");
        printf("3. Buscar por um filme\n");
        printf("4. Editar informacoes da sessao\n");
        printf("5. Remover sessao\n");
        printf("6. Reservar/comprar lugar em uma sessao\n");
        printf("0. Sair\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);

        switch (escolha) {
            case 1:
                inserirSessao(&sessoes, &numSessoes);
                break;
            case 2:
                mostrarFilmes(sessoes, numSessoes);
                break;
            case 3:
                buscarFilme(sessoes, numSessoes);
                break;
            case 4:
                editarSessao(sessoes, numSessoes);
                break;
            case 5:
                removerSessao(&sessoes, &numSessoes);
                break;
            case 6:
                reservarLugar(sessoes, numSessoes);
                break;
            case 0:
                printf("Saindo do programa. Obrigado!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    } while (escolha != 0);

    free(sessoes); // Liberando a mem�ria alocada dinamicamente

    return 0;
}

