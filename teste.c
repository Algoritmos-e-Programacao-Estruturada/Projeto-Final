#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Definindo a estrutura de sessao
typedef struct {
    char filme[50];
    char horario[10];
    int cadeirasDisponiveis;
} Sessao;

// Funcao para inserir uma nova sessao
void inserirSessao(Sessao **sessoes, int *numSessoes) {
    *numSessoes += 1;
    *sessoes = (Sessao *)realloc(*sessoes, *numSessoes * sizeof(Sessao));

    printf("Complete os dados da nova sessao:\n");

    printf("Nome do filme: ");
    getchar(); // Consumir o caractere de nova linha pendente no buffer
    fgets((*sessoes)[*numSessoes - 1].filme, sizeof((*sessoes)[*numSessoes - 1].filme), stdin);
    (*sessoes)[*numSessoes - 1].filme[strcspn((*sessoes)[*numSessoes - 1].filme, "\n")] = '\0';

    printf("Horario da sessao: ");
    scanf("%s", (*sessoes)[*numSessoes - 1].horario);

    printf("Quantidade de cadeiras livres: ");
    scanf("%d", &(*sessoes)[*numSessoes - 1].cadeirasDisponiveis);

    printf("Sessao cadastrada com sucesso!\n");
}


// Funcao para mostrar filmes disponiveis e respectivas sessoes
void mostrarFilmes(Sessao *sessoes, int numSessoes) {
    printf("Filmes disponiveis:\n");
    for (int i = 0; i < numSessoes; i++) {
        printf("%d. %s\n", i + 1, sessoes[i].filme);
    }
}

// Funcao para buscar por um filme e mostrar horarios das sessoes
void buscarFilme(Sessao *sessoes, int numSessoes) {
    char nomeFilme[50];
    printf("Digite o nome do filme: ");
    getchar(); // Consumir o caractere de nova linha pendente no buffer
    fgets(nomeFilme, sizeof(nomeFilme), stdin);
    nomeFilme[strcspn(nomeFilme, "\n")] = '\0';

    for (int i = 0; i < numSessoes; i++) {
        if (strcmp(nomeFilme, sessoes[i].filme) == 0) {
            printf("Horario da sessao: %s\n", sessoes[i].horario);
        }
    }
}


// Funcao para editar informacoes da sessao
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
        printf("Numero de sessao invalido!\n");
    }
}

// Funcao para remover sessao
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

// Funcao para reservar/comprar lugar em uma sessao especifica
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
            printf("Nao ha cadeiras disponiveis para esta sessao.\n");
        }
    } else {
        printf("Numero de sessao invalido!\n");
    }
}

// Função para salvar as sessões em um arquivo
void salvarSessoes(Sessao *sessoes, int numSessoes, const char *arquivoSessoes) {
    FILE *arquivo = fopen("arquivoSessoes.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    // Escrever cada sessão no arquivo
    for (int i = 0; i < numSessoes; i++) {
        fprintf(arquivo, "Nome do Filme: %s\n", sessoes[i].filme);
        fprintf(arquivo, "Horario da Sesssao: %s\n", sessoes[i].horario);
        fprintf(arquivo, "Cadeiras Livres: %d\n\n", sessoes[i].cadeirasDisponiveis);
    }

    fclose(arquivo);
}

// Função para carregar as sessões de um arquivo
void carregarSessoes(Sessao **sessoes, int *numSessoes, const char *arquivoSessoes) {
    FILE *arquivo = fopen("arquivoSessoes.txt", "r");

    if (arquivo == NULL) {
        printf("Arquivo de sessoes nao encontrado. Inicializando sem sessoes.\n");
        return;
    }

    // Contar o número de linhas no arquivo para determinar o número de sessões
    int numLinhas = 0;
    char ch;
    while (!feof(arquivo)) {
        ch = fgetc(arquivo);
        if (ch == '\n') {
            numLinhas++;
        }
    }
    fseek(arquivo, 0, SEEK_SET); // Voltar para o início do arquivo

    *numSessoes = numLinhas;
    *sessoes = (Sessao *)malloc(*numSessoes * sizeof(Sessao));

    // Ler cada sessão do arquivo
    for (int i = 0; i < *numSessoes; i++) {
        fscanf(arquivo, "%49[^;];%9[^;];%d\n",
               (*sessoes)[i].filme, (*sessoes)[i].horario, &(*sessoes)[i].cadeirasDisponiveis);
    }

    fclose(arquivo);
}

// Funcao principal
int main() {
    Sessao *sessoes = NULL;
    int numSessoes = 0;
    int escolha;

    const char *arquivoSessoes = "sessoes.txt";

    // Carregar sessões do arquivo (se existir)
    carregarSessoes(&sessoes, &numSessoes, arquivoSessoes);

    do {
        printf("\n\n\nMenu:\n");
        printf("======================================\n");
        printf("1. Inserir nova sessao\n");
        printf("2. Mostrar filmes disponiveis\n");
        printf("3. Buscar por um filme\n");
        printf("4. Editar informacoes da sessao\n");
        printf("5. Remover sessao\n");
        printf("6. Reservar/comprar lugar em uma sessao\n");
        printf("0. Sair\n");
        printf("======================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &escolha);
        printf("\n");

        switch (escolha) {
            case 1:
                inserirSessao(&sessoes, &numSessoes);
                salvarSessoes(sessoes, numSessoes, arquivoSessoes);
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

    free(sessoes); // Liberando a memoria alocada dinamicamente

    return 0;
}



