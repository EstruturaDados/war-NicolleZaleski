#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define MAX_STR 100

struct Territorio{
    char nome[MAX_STR];
    char cor[MAX_STR];
    int tropas;
};

void LimparBuffer(){
    int c;
    while((c = getchar()) != '\n' && c != EOF);
}

void RemoverEnter(char *str) {
    str[strcspn(str, "\n")] = '\0';
}

int Dado(){
    return (rand() % 6) + 1;
}

void CadastrarTerritorio(struct Territorio *territorios, int totalTerritorios){
    printf("\n\n---------- Cadastro de Território ----------\n\n");

    for (int i = 0; i < totalTerritorios; i++){     //Cadastrando os territórios de acordo com o número pedido
        printf("----- TERRITÓRIO %d-----\n", i+1);
        printf("Nome do território: ");
        fgets(territorios[i].nome, MAX_STR, stdin);
        RemoverEnter(territorios[i].nome);

        printf("Cor do território: ");
        fgets(territorios[i].cor, MAX_STR, stdin);
        RemoverEnter(territorios[i].cor);

        printf("Número de tropas: ");
        scanf("%d", &territorios[i].tropas);

        LimparBuffer();
    }

}

void MostrarMapa(struct Territorio *territorios, int totalTerritorios){
    printf("\n\n------- MAPA DO MUNDO - ESTADO ATUAL -------\n");
    for (int i = 0; i < totalTerritorios; i++){
        printf("\n%d - %s (Exercito %s, Tropas: %d)", i+1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
}

void AtribuirMissao(char *missaoAtual){
    const char *missoes[] = {
        "Conquistar 1 território.",
        "Derrotar uma tropa inimiga.",
        "Defender com sucesso um ataque."
    };

    int totalMissoes = sizeof(missoes) /sizeof(missoes[0]);
    int sorteada = rand() % totalMissoes;
    strcpy(missaoAtual, missoes[sorteada]);
}

void ExibirMissao(char *missaoAtual){
    printf("\n---------- Missão Atual ----------\n");
    printf("%s\n\n",missaoAtual);
}

void MenuOpcoes(struct Territorio *territorios, int totalTerritorios, char *missaoAtual){
    MostrarMapa(territorios, totalTerritorios);
    ExibirMissao(missaoAtual);

    printf("\n\n------ Menu War ------\n")/
    printf("1 - Atacar.\n");
    printf("0 - Sair.");
    printf("\n------------------");
    printf("\nEscolha a opção: ");
}


int Ataque(struct Territorio *territorios, int totalTerritorios, char *missaoAtual){
    if (totalTerritorios == 0){
        printf("\nNenhum território disponível para ataque.");
        return 0;
    }

    while(1){
        int atacante, defensor;

        MostrarMapa(territorios, totalTerritorios);
        
        printf("\n\n----------FASE DE ATAQUE----------");
        printf("\nEscolha o número do território atacante (0 para sair): ");
        scanf("%d", &atacante);
        LimparBuffer();

        if (atacante == 0) return 0;
        if (atacante < 1|| atacante > totalTerritorios){
            printf("\nNúmero inválido!");
            continue;
        }

        printf("\nEscolha o número do território defensor: ");
        scanf("%d", &defensor);
        LimparBuffer();

        if (defensor < 1 || defensor > totalTerritorios || defensor == atacante){
            printf("\nNúmero inválido!");
            continue;
        }

        atacante--;
        defensor--;

        if (territorios[atacante].tropas < 2){
            printf("\nO exército %s não tem tropas suficientes para atacar.", territorios[atacante].nome);
            continue;
        }

        printf("\n---BATALHA ENTRE %s e %s---\n",territorios[atacante].nome, territorios[defensor].nome);

        int dadoA = Dado();
        int dadoD = Dado();

        printf("O atacante %s rolou o dado e tirou: %d\n", territorios[atacante].nome, dadoA);
        printf("O defensor %s rolou o dado e tirou: %d\n", territorios[defensor].nome, dadoD);

        if (dadoA > dadoD){
            territorios[defensor].tropas--;
            printf("CONQUISTA DO ATAQUE! %s perdeu 1 tropa.\n", territorios[defensor].nome);

            if (territorios[defensor].tropas == 0){
                printf("CONQUISTA'! %s foi dominado pelo Exército %s!\n", territorios[defensor].nome, territorios[atacante].cor);
                strcpy(territorios[defensor].cor, territorios[atacante].cor);
                territorios[defensor].tropas = 1;
                territorios[atacante].tropas--;
                
                if (strcmp(missaoAtual, "Conquistar 1 território.") == 0){
                    return 1;
                }  
            } 
        } else{
            territorios[atacante].tropas--;
            printf("CONQUISTA DA DEFESA! %s perdeu uma tropa.\n", territorios[atacante].nome);
            return 0;
        }
    }
    return 0;
}

void liberarMemoria(struct Territorio *territorios){
    free(territorios);
    printf("\nMemória liberada com sucesso!!\n");
}

int main() {
    srand(time(NULL));

    struct Territorio *territorios = NULL;
    int totalTerritorios;
    char missaoAtual[MAX_STR];
    int opcao;

    do{
        printf("\n\nNúmero total de territórios (mínimo 3): ");    //pedindo o número total de territórios 
        scanf("%d",&totalTerritorios);
        LimparBuffer();
    
    } while(totalTerritorios < 3);

    territorios = (struct Territorio*) calloc(totalTerritorios,sizeof(struct Territorio));      //alocando a quantidade de territorios escolhida
    if(territorios == NULL){
        printf("\n----| Erro ao alocar memória! |----\n");
        return 1;
    }

    CadastrarTerritorio(territorios, totalTerritorios);
    AtribuirMissao(missaoAtual);

    do{
        MenuOpcoes(territorios, totalTerritorios, missaoAtual);
        scanf("%d", &opcao);
        LimparBuffer();

        switch (opcao){
            case 1:
                if (Ataque(territorios, totalTerritorios, missaoAtual)){
                    printf("\nParabéns! Você cumpriu sua missão.\n");
                    AtribuirMissao(missaoAtual);
                }
                break;
            case 0:
                printf("\nSaindo do jogo...\n");
                break;
            default:
                printf("\nOpção inválida! Tente novamente.\n");
                printf("Pressione Enter para continuar...\n");
                getchar();
                break;
        }


    } while (opcao != 0);
    
    liberarMemoria(territorios);
    return 0;
}

