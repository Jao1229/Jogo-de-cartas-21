#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ctype.h>

// Definindo enums
typedef enum {COPAS, OUROS, ESPADAS, PAUS} Naipe;
typedef enum {AS = 1, DOIS, TRES, QUATRO, CINCO, SEIS, SETE, OITO, NOVE, DEZ, VALETE, DAMA, REI} Valor;

// Struct da carta
typedef struct {
    Naipe naipe;
    Valor valor;
} Carta;

// Nodo da lista encadeada
typedef struct Nodo {
    Carta carta;
    struct Nodo* prox;
} Nodo;

// Struct do jogador
typedef struct {
    char nome[50];
    Nodo* mao;
    int pontuacaoRodada;
} Jogador;

// Protótipos
Nodo *CriarBaralho();
int Embaralhar(Nodo **topo);
int RemoverCarta(Nodo **topo, Carta *carta);
int AdicionarCartaNaMao(Jogador *jogador, Carta carta);
int LimparMao(Jogador *jogador);
int ExibirMao(Jogador *jogador);
int SalvarPlacar(const char *vencedor);
int ExibirPlacar();
int JogarRodada(Nodo **baralho, Jogador* j1, Jogador* j2);
int LiberarBaralho(Nodo *topo);

int main() {
    Nodo *baralho = CriarBaralho();
    if(baralho == NULL) {
        printf("Erro ao criar o baralho!\nPrograma encerrado!\n");
        return -1;
    }

    if (Embaralhar(&baralho) != 0) {
        printf("Erro ao embaralhar o baralho!\n");
        return -1;
    }

    Jogador jogador1 = {"Jogador 1", NULL, 0};
    Jogador jogador2 = {"Jogador 2", NULL, 0};

    int opcao;
    do {
        printf("\n==== Menu ====\n");
        printf("1. Jogar nova rodada\n");
        printf("2. Exibir placar\n");
        printf("3. Sair\n");
        printf("Escolha: ");

        if (scanf("%d", &opcao) != 1) {
            printf("Entrada inválida! Digite um número.\n");
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            opcao = -1;
            continue;
        }

        switch(opcao) {
            case 1:
                if (JogarRodada(&baralho, &jogador1, &jogador2) != 0) {
                    printf("Erro ao jogar rodada!\n");
                    return -1;
                }
                break;
            case 2:
                if (ExibirPlacar() != 0) {
                    printf("Erro ao exibir o placar.\n");
                }
                break;
            case 3:
                printf("Encerrando o jogo...\n");
                break;
            default:
                printf("Opção inválida!\n");
        }
    } while (opcao != 3);

    if (LiberarBaralho(baralho) != 0) {
        printf("Erro ao liberar o baralho.\n");
    }
    return 0;
}

// Criar baralho
Nodo *CriarBaralho() {
    Nodo *topo = NULL;
    for (int n = COPAS; n <= PAUS; n++) {
        for (int v = AS; v <= REI; v++) {
            Nodo *novo = (Nodo*)malloc(sizeof(Nodo));
            if (novo == NULL) return NULL;
            novo->carta.naipe = n;
            novo->carta.valor = v;
            novo->prox = topo;
            topo = novo;
        }
    }
    return topo;
}

// Embaralhar baralho
int Embaralhar(Nodo **topo) {
    if (topo == NULL || *topo == NULL) return -1;

    int tamanho = 0;
    Nodo* temp = *topo;
    while (temp) {
        tamanho++;
        temp = temp->prox;
    }
    if (tamanho <= 1) return 0;

    Carta* cartas = (Carta*)malloc(tamanho * sizeof(Carta));
    if (cartas == NULL) return -1;

    temp = *topo;
    for (int i = 0; i < tamanho; i++) {
        cartas[i] = temp->carta;
        temp = temp->prox;
    }

    srand(time(NULL));
    for (int i = 0; i < tamanho; i++) {
        int j = rand() % tamanho;
        Carta tmp = cartas[i];
        cartas[i] = cartas[j];
        cartas[j] = tmp;
    }

    temp = *topo;
    for (int i = 0; i < tamanho; i++) {
        temp->carta = cartas[i];
        temp = temp->prox;
    }
    free(cartas);
    return 0;
}

// Remover carta (com tratamento de erro)
int RemoverCarta(Nodo **topo, Carta *carta) {
    if (topo == NULL || *topo == NULL || carta == NULL) return -1;

    Nodo* temp = *topo;
    *carta = temp->carta;
    *topo = temp->prox;
    free(temp);
    return 0;
}

// Adicionar carta na mão
int AdicionarCartaNaMao(Jogador *jogador, Carta carta) {
    if (jogador == NULL) return -1;

    Nodo* novo = (Nodo*)malloc(sizeof(Nodo));
    if (novo == NULL) {
        printf("Erro ao alocar memória para nova carta na mão!\n");
        return -1;
    }
    novo->carta = carta;
    novo->prox = jogador->mao;
    jogador->mao = novo;

    int valor = carta.valor;
    jogador->pontuacaoRodada += (valor >= 11) ? 10 : valor;
    return 0;
}

// Limpar mão
int LimparMao(Jogador *jogador) {
    if (jogador == NULL) return -1;
    Nodo* temp = jogador->mao;
    while (temp) {
        Nodo* prox = temp->prox;
        free(temp);
        temp = prox;
    }
    jogador->mao = NULL;
    jogador->pontuacaoRodada = 0;
    return 0;
}

// Exibir mão
int ExibirMao(Jogador *jogador) {
    if (jogador == NULL) return -1;
    Nodo* atual = jogador->mao;
    char* nomesNaipe[] = {"Copas", "Ouros", "Espadas", "Paus"};
    char* nomesValor[] = {"", "As", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Valete", "Dama", "Rei"};

    while (atual != NULL) {
        printf("%s de %s\n", nomesValor[atual->carta.valor], nomesNaipe[atual->carta.naipe]);
        atual = atual->prox;
    }
    printf("%s - Pontuação: %d\n", jogador->nome, jogador->pontuacaoRodada);
    return 0;
}

// Salvar placar
int SalvarPlacar(const char *vencedor) {
    FILE* arquivo = fopen("placar.txt", "a");
    if (arquivo == NULL) return -1;
    fprintf(arquivo, "Vencedor da rodada: %s\n", vencedor);
    fclose(arquivo);
    return 0;
}

// Exibir placar
int ExibirPlacar() {
    FILE* arquivo = fopen("placar.txt", "r");
    if (arquivo == NULL) return -1;

    char linha[100];
    printf("==== Placar ====\n");
    while (fgets(linha, sizeof(linha), arquivo)) {
        printf("%s", linha);
    }
    fclose(arquivo);
    return 0;
}

// Jogar rodada (corrigido)
int JogarRodada(Nodo **baralho, Jogador* j1, Jogador* j2) {
    if (baralho == NULL || *baralho == NULL || j1 == NULL || j2 == NULL) return -1;

    if (LimparMao(j1) != 0 || LimparMao(j2) != 0) return -1;

    Carta c;

    for (int i = 0; i < 2; i++) {
        if (RemoverCarta(baralho, &c) != 0) return -1;
        if (AdicionarCartaNaMao(j1, c) != 0) return -1;

        if (RemoverCarta(baralho, &c) != 0) return -1;
        if (AdicionarCartaNaMao(j2, c) != 0) return -1;
    }

    char escolha;

    printf("\n%s - Sua mão atual:\n", j1->nome);
    ExibirMao(j1);

    do {
        printf("%s, deseja pegar mais uma carta? (s/n): ", j1->nome);
        while (getchar() != '\n');
        scanf("%c", &escolha);
        escolha = tolower(escolha);
    } while (escolha != 's' && escolha != 'n');

    if (escolha == 's') {
        if (RemoverCarta(baralho, &c) != 0) return -1;
        if (AdicionarCartaNaMao(j1, c) != 0) return -1;
        printf("Nova mão de %s:\n", j1->nome);
        ExibirMao(j1);
    }

    printf("\n%s - Sua mão atual:\n", j2->nome);
    ExibirMao(j2);

    do {
        printf("%s, deseja pegar mais uma carta? (s/n): ", j2->nome);
        while (getchar() != '\n');
        scanf("%c", &escolha);
        escolha = tolower(escolha);
    } while (escolha != 's' && escolha != 'n');

    if (escolha == 's') {
        if (RemoverCarta(baralho, &c) != 0) return -1;
        if (AdicionarCartaNaMao(j2, c) != 0) return -1;
        printf("Nova mão de %s:\n", j2->nome);
        ExibirMao(j2);
    }

    printf("\n=== Resultado da Rodada ===\n");
    ExibirMao(j1);
    ExibirMao(j2);

    int p1 = j1->pontuacaoRodada;
    int p2 = j2->pontuacaoRodada;

    if (p1 > 21 && p2 > 21) {
        printf("Ambos passaram de 21! Sem vencedor.\n");
        SalvarPlacar("Nenhum");
    } else if (p1 > 21) {
        printf("%s estourou! %s é o vencedor.\n", j1->nome, j2->nome);
        SalvarPlacar(j2->nome);
    } else if (p2 > 21) {
        printf("%s estourou! %s é o vencedor.\n", j2->nome, j1->nome);
        SalvarPlacar(j1->nome);
    } else if (p1 == p2) {
        printf("Empate!\n");
        SalvarPlacar("Empate");
    } else if (p1 > p2) {
        printf("Vencedor: %s\n", j1->nome);
        SalvarPlacar(j1->nome);
    } else {
        printf("Vencedor: %s\n", j2->nome);
        SalvarPlacar(j2->nome);
    }

    Nodo *temp;
    while (j1->mao) {
        temp = j1->mao;
        j1->mao = j1->mao->prox;
        temp->prox = *baralho;
        *baralho = temp;
    }
    while (j2->mao) {
        temp = j2->mao;
        j2->mao = j2->mao->prox;
        temp->prox = *baralho;
        *baralho = temp;
    }

    return Embaralhar(baralho);
}

// Liberar baralho
int LiberarBaralho(Nodo *topo) {
    if (topo == NULL) return -1;
    while (topo) {
        Nodo* temp = topo;
        topo = topo->prox;
        free(temp);
    }
    return 0;
}
