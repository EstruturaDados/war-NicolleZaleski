#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_TERR 5
#define MAX_STR 100

struct Territorio{
    char nome[MAX_STR];
    char cor[MAX_STR];
    int tropas;
};

int main(){
    struct Territorio Territorios[MAX_TERR];
    int totalTerritorios = 5;

    for (int i = 0; i < totalTerritorios; i++){
        printf("\n_______________________________________________\n\n");
        printf("        ---Cadastrando Território %d---\n", i+1);
        printf("Digite o nome do território: ");
        fgets(Territorios[i].nome, MAX_STR,stdin);

        printf("Digite qual a cor do território: ");
        fgets(Territorios[i].cor, MAX_STR,stdin);

        printf("Digite o número de tropas: ");
        scanf("%d", &Territorios[i].tropas);

        while (getchar() != '\n');

        printf("\n\n");
    }

    //RELATORIO COMPLETO
    printf("\n\n_______________________MAPA DO MUNDO______________________\n\n");
    for (int i = 0; i < totalTerritorios; i++){
        printf("---TERRITÓRIO %d---\n", i+1);
        printf("Nome: %s\n", Territorios[i].nome);
        printf("Cor: %s\n", Territorios[i].cor);
        printf("Número de Tropas: %d\n", Territorios[i].tropas);
        printf("\n\n---------------------------------------------------------\n");
    }
}


