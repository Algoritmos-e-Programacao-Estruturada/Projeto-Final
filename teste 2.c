#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct{
    char filme[50];
    int cadeirasLivres;
    char horario[6];
}sessoes;

void novaSessao(sessoes *sessao, int numSessoes){

    numSessoes += 1;

    sessao = (sessoes *) malloc(numSessoes * sizeof(sessoes));

    printf("Nome do filme: ");
    fgets(sessao->filme, sizeof(sessao->filme), stdin);

    printf("Horario da sessao: ");
    scanf("%s", sessao->horario);

    printf("Cadeiras disponiveis: ");
    scanf("%d", &sessao->cadeirasLivres);

    printf("Sessao cadastrada com sucesso!\n");
}

void mostrarFilmes(sessoes *sessao, int numSessoes){

    printf("Filmes disponiveis: \n");
    for(int i = 0; i < numSessoes; i++){
        printf("%s --> sessoes: ", sessao[i].filme);
    }
}

void buscarFilme(){

}

int main(){
    sessoes *sessao = NULL;
    int numSessoes = 0;
    int escolha;

    do{
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

        switch (escolha){
            case 1:
                novaSessao(&sessao, &numSessoes);
                break;
            case 2:
                mostrarFilmes(sessao, numSessoes);
                break;
            case 3:
                buscarFilme(sessao, numSessoes);
                break;
            case 4:
                editarSessao(sessao, numSessoes);
                break;
            case 5:
                removerSessao(&sessao, &numSessoes);
                break;
            case 6:
                reservarLugar(sessao, numSessoes);
                break;
            case 0:
                printf("Saindo do programa. Obrigado!\n");
                break;
            default:
                printf("Opcao invalida. Tente novamente.\n");
        }
    }while (escolha != 0);

    free(sessao); // Liberando a memória alocada dinamicamente

    return 0;
}
