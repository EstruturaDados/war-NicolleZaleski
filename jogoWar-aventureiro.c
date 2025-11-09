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

void MostrarMapa(struct Territorio *territorios, int totalTerritorios){
    printf("\n\n---------------------------------------");
    printf("\n      MAPA DO MUNDO - ESTADO ATUAL");
    printf("\n---------------------------------------\n");
    for (int i = 0; i < totalTerritorios; i++){
        printf("\n%d - %s (Exército %s, Tropas: %d)", i+1, territorios[i].nome, territorios[i].cor, territorios[i].tropas);
    }
}

int Dado(){
    return (rand() % 6) + 1;
}

void Ataque(struct Territorio *territorios, int totalTerritorios){
    if (totalTerritorios == 0){
        printf("\nNenhum território disponível para ataque.");
        return;
    }

    while(1){
        int atacante, defensor;
        MostrarMapa(territorios, totalTerritorios);
        
        printf("\n\n----------FASE DE ATAQUE----------");
        printf("\nEscolha o número do território atacante (0 para sair): ");
        scanf("%d", &atacante);
        LimparBuffer();

        if (atacante == 0) return;
        if (atacante < 1|| atacante > totalTerritorios){
            printf("\nNúmero inválido!");
            return;
        }

        printf("\nEscolha o número do território defensor: ");
        scanf("%d", &defensor);
        LimparBuffer();

        if (defensor < 1 || defensor > totalTerritorios || defensor == atacante){
            printf("\nNúmero inválido!");
            return;
        }

        atacante--;
        defensor--;

        if (territorios[atacante].tropas < 2){
            printf("\nO exército %s não tem tropas suficientes para atacar.", territorios[atacante].nome);
            return;
        }
        if (territorios[defensor].tropas <= 0){
            printf("\nO exército %s não tem tropas para defender.", territorios[defensor].nome);
            return;
        }

        printf("\n---BATALHA ENTRE %s e %s---\n",territorios[atacante].nome, territorios[defensor].nome);

        int dadoA = Dado();
        int dadoD = Dado();

        printf("O atacante %s rolou o dado e tirou: %d\n", territorios[atacante].nome, dadoA);
        printf("O defensor %s rolou o dado e tirou: %d\n", territorios[defensor].nome, dadoD);

        if (dadoA > dadoD){
            territorios[defensor].tropas--;
            printf("Ataque bem sucedido! %s perdeu 1 tropa.\n", territorios[defensor].nome);
        } else{
            territorios[atacante].tropas--;
            printf("Defesa bem-sucedida! %s perdeu uma tropa.\n", territorios[atacante].nome);
        }

        if (territorios[defensor].tropas == 0){
            printf("\nCONQUISTA!! O território %s foi dominado pelo Exército %s\n", territorios[defensor].nome, territorios[atacante].cor);
            strcpy(territorios[defensor].cor, territorios[atacante].cor);
            territorios[defensor].tropas = 1;
            territorios[atacante].tropas--; //move uma tropa   
        }
    }
}



int main() {
    srand(time(NULL));

    struct Territorio *territorios = NULL;
    int totalTerritorios;
    
    
    printf("\n\nNúmero total de territórios: ");    //pedindo o número total de territórios 
    scanf("%d",&totalTerritorios);
    LimparBuffer();

    if (totalTerritorios < 3) {
        printf("Escolha no mínimo 3 territórios!\n");
        return 1;
    }

    territorios = (struct Territorio*) calloc(totalTerritorios,sizeof(struct Territorio));      //alocando a quantidade de territorios escolhida

    if(territorios == NULL){
        printf("\n---------------------------");
        printf("\n| Erro ao alocar memória! |");
        printf("\n---------------------------");
        return 1;
    }
           
    for (int i = 0; i < totalTerritorios; i++){     //Cadastrando os territórios de acordo com o número pedido
        printf("\n\n_______________________________________________\n\n");
        printf("        -----Cadastrando Território %d-----\n", i+1);
        printf("Digite o nome do território: ");
        fgets(territorios[i].nome, MAX_STR,stdin);

        printf("Digite qual a cor do território: ");
        fgets(territorios[i].cor, MAX_STR,stdin);

        printf("Digite o número de tropas: ");
        scanf("%d", &territorios[i].tropas);

        LimparBuffer();
        printf("\n");
    }

    Ataque(territorios, totalTerritorios);

    free(territorios);
    printf("Memória liberada com sucesso!!");
    return 0;
}