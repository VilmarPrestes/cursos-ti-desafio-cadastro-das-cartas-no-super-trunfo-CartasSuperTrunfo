#include <stdio.h>
#include <locale.h>
#include <string.h>

typedef struct {
    char estado;
    char codigo[4];
    char nomeCidade[100];
    unsigned int populacao;
    float area;
    float pib;
    int numPontosTuristicos;
    float densPop;
    float pibPerCapita;
} Carta;

void calcularAtributos(Carta *c) {
    c->densPop = c->populacao / c->area;
    c->pibPerCapita = c->pib / c->populacao;
}

void cadastrarCarta(Carta *c) {
    printf("Digite seu estado (letra de 'A' a 'H'): ");
    scanf(" %c", &c->estado);
    printf("Digite o código da carta (ex: A01, B03): ");
    scanf("%3s", c->codigo);
    getchar(); 
    printf("Digite o nome da cidade: ");
    fgets(c->nomeCidade, sizeof(c->nomeCidade), stdin);
    strtok(c->nomeCidade, "\n");
    printf("Digite a população da cidade: ");
    scanf("%u", &c->populacao);
    printf("Digite a área (em km²) da cidade: ");
    scanf("%f", &c->area);
    printf("Digite o PIB da cidade: ");
    scanf("%f", &c->pib);
    printf("Digite o número de pontos turísticos: ");
    scanf("%d", &c->numPontosTuristicos);
    calcularAtributos(c);
}

void exibirCarta(Carta c) {
    printf("\n===== Carta =====\n");
    printf("Estado: %c\n", c.estado);
    printf("Código: %s\n", c.codigo);
    printf("Nome da Cidade: %s\n", c.nomeCidade);
    printf("População: %u habitantes\n", c.populacao);
    printf("Área: %.2f km²\n", c.area);
    printf("PIB: %.2f\n", c.pib);
    printf("Número de Pontos Turísticos: %d\n", c.numPontosTuristicos);
    printf("Densidade Populacional: %.2f\n", c.densPop);
    printf("PIB per capita: %.2f\n", c.pibPerCapita);
}

int compararAtributos(float atributo1, float atributo2, int inverte) {
    if (inverte) {
        return atributo1 < atributo2 ? 1 : (atributo1 > atributo2 ? 2 : 0);
    } else {
        return atributo1 > atributo2 ? 1 : (atributo1 < atributo2 ? 2 : 0);
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    Carta carta1, carta2;
    int opcao, vencedor1, vencedor2, totalPontos1 = 0, totalPontos2 = 0;
    printf("Cadastro da Carta 1\n");
    cadastrarCarta(&carta1);
    printf("\nCadastro da Carta 2\n");
    cadastrarCarta(&carta2);
    exibirCarta(carta1);
    exibirCarta(carta2);
    printf("\nEscolha dois atributos para comparar:\n");
    printf("1 - População\n");
    printf("2 - Área\n");
    printf("3 - PIB\n");
    printf("4 - Número de Pontos Turísticos\n");
    printf("5 - Densidade Populacional\n");
    printf("6 - PIB per capita\n");

    for (int i = 0; i < 2; i++) {
        printf("\nEscolha o atributo %d: ", i + 1);
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                vencedor1 = compararAtributos(carta1.populacao, carta2.populacao, 0);
                break;
            case 2:
                vencedor1 = compararAtributos(carta1.area, carta2.area, 0);
                break;
            case 3:
                vencedor1 = compararAtributos(carta1.pib, carta2.pib, 0);
                break;
            case 4:
                vencedor1 = compararAtributos(carta1.numPontosTuristicos, carta2.numPontosTuristicos, 0);
                break;
            case 5:
                vencedor1 = compararAtributos(carta1.densPop, carta2.densPop, 1);
                break;
            case 6:
                vencedor1 = compararAtributos(carta1.pibPerCapita, carta2.pibPerCapita, 0);
                break;
            default:
                printf("Opção inválida! Tente novamente.\n");
                i--;
                continue;
        }
        if (vencedor1 == 1) totalPontos1++;
        else if (vencedor1 == 2) totalPontos2++;
    }

    printf("\n===== Resultado Final =====\n");
    if (totalPontos1 > totalPontos2) {
        printf("A Carta 1 (%s) venceu com %d pontos!\n", carta1.nomeCidade, totalPontos1);
    } else if (totalPontos2 > totalPontos1) {
        printf("A Carta 2 (%s) venceu com %d pontos!\n", carta2.nomeCidade, totalPontos2);
    } else {
        printf("Empate! Ambas as cartas têm %d pontos.\n", totalPontos1);
    }

    return 0;
}
