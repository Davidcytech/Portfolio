#define _CRT_SECURE_NO_WARNINGS
#include <string.h>
#include <locale.h>
#include <stdio.h>
#include <math.h>
#define MAX_JOGADORES 20
#define MAX_EQUIPAS 18

typedef struct {
    char esquema[10];
    int coordenadas[11][2];
    char tipos[11][20];
} Formacao;

const Formacao listaFormacoes[] = {
    { "4-4-2",
        {{10, 10}, {30, 10}, {70, 10}, {90, 10}, // Defesa
        {20, 40}, {40, 40}, {60, 40}, {80, 40}, // Medio
        {40, 70}, {60, 70},                    // Ataque
        {50, 5}},                              // Guarda Redes
        {"Defesa", "Defesa", "Defesa", "Defesa",
        "Medio", "Medio", "Medio", "Medio",
        "Avancado", "Avancado",
        "Guarda Redes"} },
    { "4-3-3",
        {{10, 10}, {30, 10}, {70, 10}, {90, 10}, // Defesa
        {30, 40}, {50, 40}, {70, 40},          // Medio
        {20, 70}, {50, 70}, {80, 70},          // Ataque
        {50, 5}},                              // Guarda Redes
        {"Defesa", "Defesa", "Defesa", "Defesa",
        "Medio", "Medio", "Medio",
        "Avancado", "Avancado", "Avancado",
        "Guarda Redes"} },
    { "5-3-2",
        {{10, 10}, {25, 10}, {50, 10}, {75, 10}, {90, 10}, // Defesa
         {30, 40}, {50, 40}, {70, 40},                   // Medio
         {40, 70}, {60, 70},                             // Ataque
         {50, 5}},                                       // Guarda Redes
        {"Defesa", "Defesa", "Defesa", "Defesa", "Defesa",
         "Medio", "Medio", "Medio",
         "Avancado", "Avancado",
         "Guarda Redes"} },
    { "4-5-1",
        {{10, 10}, {30, 10}, {70, 10}, {90, 10}, // Defesa
         {20, 30}, {40, 30}, {60, 30}, {80, 30}, {50, 50}, // Medio
         {50, 70},                                     // Ataque
         {50, 5}},                                    // Guarda Redes
        {"Defesa", "Defesa", "Defesa", "Defesa",
         "Medio", "Medio", "Medio", "Medio", "Medio",
         "Avancado",
         "Guarda Redes"}
    }
};

typedef struct {
    int numero;
    char nomej[70];
    char posicaoDefault[25]; 
    char posicao[25]; 
    int coordenadas[2]; 
    int forca;
    int salario;
    char datai[12];
    char dataf[12];
    int mesesrest;

} Jogador;

typedef struct {
    char abreviacao[5];
    char nomec[100];
    char treinador[200];
    char estadio[200];
    int lugares;
    int socios;
    int income;
    int despesas;
    int torneiosganhos;
    Jogador jogador[MAX_JOGADORES];
    Formacao formacao;
} Equipa;

void leitura(FILE* file, char* stats, int tamanho) {

    int i = 0;
    char x;
    while ((x = fgetc(file)) != '\n' && x != EOF && i < tamanho - 1) { 
        stats[i++] = x;
    }
    stats[i] = '\0';    //após ler a string adiciona um \0 no último membro para declarar o fim dela e para que ela possa ser lida corretamente.

}

int lequipas(char* arquivo, Equipa* equipa) {

    char caminho[18];
    strcpy(caminho, "Equipas/"); // caminho da pasta para cada ficheiro
    strcat(caminho, arquivo);

    FILE* fp = fopen(caminho, "r");

    if (fp != NULL) {
        leitura(fp, (*equipa).abreviacao, sizeof((*equipa).abreviacao));
        leitura(fp, (*equipa).nomec, sizeof((*equipa).nomec));
        leitura(fp, (*equipa).estadio, sizeof((*equipa).estadio));
        fscanf(fp, "%d ", &(*equipa).lugares);
        fscanf(fp, "%d ", &(*equipa).socios);
        fscanf(fp, "%d ", &(*equipa).income);
        fscanf(fp, "%d ", &(*equipa).despesas);
        leitura(fp, (*equipa).treinador, sizeof((*equipa).treinador));
        leitura(fp, (*equipa).formacao.esquema, sizeof((*equipa).formacao.esquema)); //Novas

        for (int i = 0; i < MAX_JOGADORES; i++) {
            fscanf(fp, "%d ", &(*equipa).jogador[i].numero);
            leitura(fp, (*equipa).jogador[i].nomej, sizeof((*equipa).jogador[i].nomej));
            leitura(fp, (*equipa).jogador[i].posicaoDefault, sizeof((*equipa).jogador[i].posicaoDefault));
            fscanf(fp, "%d ", &(*equipa).jogador[i].forca);
            fscanf(fp, "%d ", &(*equipa).jogador[i].coordenadas[0]); //Novas
            fscanf(fp, "%d ", &(*equipa).jogador[i].coordenadas[1]); //Novas
            fscanf(fp, "%d ", &(*equipa).jogador[i].salario);
            leitura(fp, (*equipa).jogador[i].datai, sizeof((*equipa).jogador[i].datai));
            leitura(fp, (*equipa).jogador[i].dataf, sizeof((*equipa).jogador[i].dataf));
            fscanf(fp, "%d ", &(*equipa).jogador[i].mesesrest);

        }
        fclose(fp);
        return 1;

    }
    else
    {
        printf("Não foi possivel abrir o ficheiro %s\n", arquivo);
        return 0;
    }
}

int MenuInicio(void)
{
    int opcao;

    system("cls");
    printf("=== Menu do Jogo ===\n");
    printf("1. Novo Jogo\n");
    printf("2. Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opcao);

    return opcao;
}

void mostrarEquipas(Equipa *equipas, int total, int filtro) {

    printf("Lista das equipas:\n");
    for (int i = 0; i < total; i++) {
        if (i != filtro)
        {
            printf("\n--- %d - %s ---\n", i + 1, equipas[i].abreviacao);
            printf("Nome: %s\n", equipas[i].nomec);
            printf("Nome do estadio: %s\n", equipas[i].estadio);
            printf("Numero de Lugares: %d\n", equipas[i].lugares);
            printf("Despesas do estadio: %d\n", equipas[i].despesas);
            printf("Numero de socios: %d\n", equipas[i].socios);
            printf("Fundos do clube: %d\n", equipas[i].income);
            printf("Treinador: %s\n", equipas[i].treinador);
        }
    }
}

void mostrarJogadores(Equipa equipa, int total) {

    printf("Jogadores do %s:\n", equipa.nomec);

    for (int i = 0; i < MAX_JOGADORES; i++) {
        if (equipa.jogador[i].numero > 0) {
            printf("  Numero: %d\n", equipa.jogador[i].numero);
            printf("  Nome: %s\n", equipa.jogador[i].nomej);
            printf("  Posicao: %s\n", equipa.jogador[i].posicaoDefault);
            printf("  Forca: %d\n", equipa.jogador[i].forca);
            printf("  Salario: %d$\n", equipa.jogador[i].salario);
            printf("  Data de inicio de contrato: %s\n", equipa.jogador[i].datai);
            printf("  Data do fim de contrato: %s\n\n", equipa.jogador[i].dataf);
        }
    }
}

void mostrarTodosJogadores(Equipa* equipa, int equiEscolhida) {
    printf("Lista dos jogadores disponíveis para compra:\n");

    for (int i = 0; i < MAX_EQUIPAS; i++)
    {
        if (i != equiEscolhida)
        {
            for (int j = 0; j < MAX_JOGADORES; j++)
            {
                mostrarJogadores(equipa[i], MAX_JOGADORES);
            }
        }
    }
}



float calcularForcaPos(Jogador j, char* pos)
{
    float percentPos = 0;

    if (strcmp(j.posicaoDefault, pos) == 0) {
        percentPos = 0.8;
    }
    else if ((strcmp(j.posicaoDefault, "Avancado") == 0 && strcmp(pos, "Medio") == 0) ||
        (strcmp(j.posicaoDefault, "Defesa") == 0 && strcmp(pos, "Medio") == 0) ||
        (strcmp(j.posicaoDefault, "Medio") == 0 && strcmp(pos, "Avancado") == 0) ||
        (strcmp(j.posicaoDefault, "Guarda-Redes") == 0 && strcmp(pos, "Defesa") == 0)) {
        percentPos = 0.5;
    }
    else if ((strcmp(j.posicaoDefault, "Avancado") == 0 && strcmp(pos, "Defesa") == 0) ||
        (strcmp(j.posicaoDefault, "Defesa") == 0 && strcmp(pos, "Guarda-Redes") == 0) ||
        (strcmp(j.posicaoDefault, "Medio") == 0 && strcmp(pos, "Defesa") == 0) ||
        (strcmp(j.posicaoDefault, "Guarda-Redes") == 0 && strcmp(pos, "Medio") == 0)) {
        percentPos = 0.3;
    }
    else if ((strcmp(j.posicaoDefault, "Avancado") == 0 && strcmp(pos, "Guarda-Redes") == 0) ||
        (strcmp(j.posicaoDefault, "Defesa") == 0 && strcmp(pos, "Avancado") == 0) ||
        (strcmp(j.posicaoDefault, "Medio") == 0 && strcmp(pos, "Guarda-Redes") == 0) ||
        (strcmp(j.posicaoDefault, "Guarda-Redes") == 0 && strcmp(pos, "Avancado") == 0)) {
        percentPos = 0.1;
    }

    return j.forca * percentPos;
}

void vePosicao(Equipa* equi)
{
    int defesas = (*equi).formacao.esquema[0] - '0';
    int medios = (*equi).formacao.esquema[2] - '0';
    int avancados = (*equi).formacao.esquema[4] - '0';
    int i;

    for (i = 0; i < MAX_JOGADORES; i++)
    {
        if ((*equi).jogador[i].coordenadas[0] != 0)
        {
            if (strcmp((*equi).jogador[i].posicaoDefault, "Guarda-Redes") == 0)
            {
                strcpy(&(*equi).jogador[i].posicao, "Guarda-Redes");
            }
            else
            {
                if (defesas > 0)
                {
                    strcpy(&(*equi).jogador[i].posicao, "Defesa");
                    defesas -= 1;
                }
                else if (medios > 0)
                {
                    strcpy(&(*equi).jogador[i].posicao, "Medio");
                    medios -= 1;
                }
                else if (avancados > 0)
                {
                    strcpy(&(*equi).jogador[i].posicao, "Avancado");
                    avancados -= 1;
                }
            }
        }
        else
        {
            strcpy(&(*equi).jogador[i].posicao, "Banco");
        }
    }
}

void TrocaJogadores(Jogador *comprado, Jogador *trocado)
{
    Jogador espera;

    if ((*comprado).coordenadas[0] != 0 || (*trocado).coordenadas[0] != 0)
    {
        printf("Um dos jogadores que trocou era titular, e durante a troca trocaram tambem as posicoes\n");
    }

    espera = (*comprado);

    (*comprado).salario = (*comprado).salario * 1.5; //Aumenta o salario do jogador

    int coordenadasComprado[2] = { (*comprado).coordenadas[0], (*comprado).coordenadas[1] };
    int coordenadasTrocado[2] = { (*trocado).coordenadas[0], (*trocado).coordenadas[1] };

    espera.coordenadas[0] = coordenadasTrocado[0];
    (*comprado).coordenadas[1] = coordenadasTrocado[1];

    (*trocado).coordenadas[0] = coordenadasComprado[0];
    (*trocado).coordenadas[1] = coordenadasComprado[1];

    (*comprado) = (*trocado);
    (*trocado) = espera;
}


void sorteio(Equipa equipasSorteio[], Equipa minhaEquipa, Equipa ordemSorteio[]) {
    int repeticoes[18] = { 0 };
    int sorteados = 0;

    printf("\nCalendario de jogos para a equipa %s:\n", minhaEquipa.abreviacao);

    while (sorteados < 34) {
        int random = rand() % 18;

        // Verifica se o nome sorteado é diferente do nome da minha equipa e se o número já não foi repetido mais de 2 vezes
        if (strcmp(equipasSorteio[random].abreviacao, minhaEquipa.abreviacao) != 0 && repeticoes[random] < 2) {
            ordemSorteio[sorteados] = equipasSorteio[random];
            repeticoes[random]++;
            sorteados++;
        }
    }
}


float calcularForcaAtaque(Equipa *equipa) {
    float somaForcaAtaque = 0;

    for (int i = 0; i < MAX_JOGADORES; i++) {
        if (strcmp((*equipa).jogador[i].posicao, "Avancado") == 0 || strcmp((*equipa).jogador[i].posicao, "Medio") == 0) {
            if (strcmp((*equipa).jogador[i].posicao, "Avancado") == 0) {
                somaForcaAtaque += calcularForcaPos((*equipa).jogador[i], "Avancado");
                
            }
            else
            {
                somaForcaAtaque += calcularForcaPos((*equipa).jogador[i], "Medio") * 0.7;
            }
        }
        //printf("%s\n", (*equipa).jogador[i].posicao);
    }

    return somaForcaAtaque;
}

float calcularForcaDefesa(Equipa equipa) {
    float somaForcaDefesa = 0;

    for (int i = 0; i < MAX_JOGADORES; i++) {
        if (strcmp(equipa.jogador[i].posicao, "Defesa") == 0) {
            somaForcaDefesa += calcularForcaPos(equipa.jogador[i], "Defesa");
        }
    }

    return somaForcaDefesa;
}


void selecionarPlantel(Equipa* equipa, int taticaEscolhida) {
    int jogadorPos;
    int conseguiu = 0;

    mostrarJogadores(*equipa, MAX_JOGADORES);

    int defesas = equipa->formacao.esquema[0] - '0';
    int medios = equipa->formacao.esquema[2] - '0';
    int avancados = equipa->formacao.esquema[4] - '0';


    for (int i = 0; i < 11; i++) {
        printf("Que jogador deseja por na posicao [%d; %d] (%s)?\n",
            listaFormacoes[taticaEscolhida - 1].coordenadas[i][0],
            listaFormacoes[taticaEscolhida - 1].coordenadas[i][1],
            listaFormacoes[taticaEscolhida - 1].tipos[i]);

        do {
            scanf("%d", &jogadorPos);


            for (int j = 0; j < MAX_JOGADORES; j++) {
                if (jogadorPos == equipa->jogador[j].numero && equipa->jogador[j].coordenadas[0] == 0) {
                    equipa->jogador[j].coordenadas[0] = listaFormacoes[taticaEscolhida - 1].coordenadas[i][0];
                    equipa->jogador[j].coordenadas[1] = listaFormacoes[taticaEscolhida - 1].coordenadas[i][1];
                    conseguiu = 1;
                    break;
                }
                else if (j == MAX_JOGADORES - 1 && conseguiu == 0) {
                    printf("Esse jogador nao existe ou ja esta noutro lugar\n");
                }
            }
        } while (conseguiu == 0);
        conseguiu = 0;
    }

    
}

int veGolo(Equipa *equipaDefensora, int ataque)
{

    int defesas = (*equipaDefensora).formacao.esquema[0] - '0';

    Jogador guardaRedes;
    float numeroRandom = 0;

    for (int i = 0; i < MAX_JOGADORES; i++)
    {
        if (strcmp((*equipaDefensora).jogador[i].posicao, "Guarda-Redes") == 0)
        {
            guardaRedes = (*equipaDefensora).jogador[i];
        }
    }

    float defesa = guardaRedes.forca / 4;

    while (ataque > defesa)
    {
        ataque -= 5;
        numeroRandom -= 0.5;
    }

    int ale = rand() % ((int)numeroRandom + (int)defesa);

    if (ale > 0 && ale <= 5)
    {
        printf("GOLOOOO!\n");

        return 1;
    }
    else
    {
        printf("Falhou no golo\n");

        return 0;
    }
}

int Ataque(Equipa* ataque, Equipa* defesa, float forca)
{
    int golos = 0;

    int forcaAtaque = (int)forca;

    int ale = 0;

    int forcaJogador;

    for (int i = 0; i < MAX_JOGADORES; i++)
    {

        if (strcmp((*defesa).jogador[i].posicao, "Defesa") == 0 && forcaAtaque > 0)
        {
            forcaJogador = 100 - (int)calcularForcaPos((*defesa).jogador[i], "Defesa");

            ale = rand() % (3 * forcaJogador);

            //Para intervalo 1 - 100

            if (ale >= 0 && ale <= 5)
            {
                forcaAtaque -= 300;
            }
            else if ((ale > 5 && ale <= 15) && forcaAtaque > 0)
            {
                forcaAtaque -= 200;
            }
            else if ((ale > 15 && ale <= 30) && forcaAtaque > 0)
            {
                forcaAtaque -= 100;
            }
            else if ((ale > 30 && ale <= 60) && forcaAtaque > 0)
            {
                forcaAtaque -= 80;
            }
            else if ((ale > 60 && ale <= 75) && forcaAtaque > 0)
            {
                forcaAtaque -= 60;
            }
            else if ((ale > 75 && ale <= 90) && forcaAtaque > 0)
            {
                forcaAtaque -= 50;
            }
            else if ((ale > 90 && ale <= 100) && forcaAtaque > 0)
            {
                forcaAtaque -= 60;
            }
            else if (ale > 100 && forcaAtaque > 0)
            {
                forcaAtaque -= 40;
            }

            if (forcaAtaque <= 0)
            {
                printf("O ataque falhou em [%d; %d]\n", (*defesa).jogador[i].coordenadas[0], (*defesa).jogador[i].coordenadas[1]);
            }
            
        }

    }

    if (forcaAtaque > 0)
    {
        golos += veGolo(&(*defesa), forcaAtaque);
    }

    getch();

    return golos;
}

int main(void) {
    Equipa equipas[MAX_EQUIPAS];
    Equipa equipaEscolhida;
    int totalequipas = 0;
    char* arquivos[MAX_EQUIPAS] = { "AFS.txt", "BFC.txt", "CDN.txt", "CFEA.txt","CPAC.txt", "EP.txt", "FCA.txt", "FCF.txt", "FCP.txt", "GVFC.txt", "MFC.txt", "RAFC.txt", "SCA.txt", "SCB.txt", "SCF.txt", "SCP.txt", "SLB.txt", "VSC.txt" };

    for (int i = 0; i < MAX_EQUIPAS; ++i) {
        if (lequipas(arquivos[i], &equipas[i]) != 1) {
            printf("Erro ao carregar a equipa\n");
        }
    }
    
    int querJogar;
    int opcao;
    char utilizador[50];

    int valor;
    int conseguiu = 0;
    int contadorCompra;
    char abreviacao[3][5] = { "" };
    int opcaoTroca;
    int comprou; //Serve para ver se o jogador já comprou a uma equipa
    int contaAbreviacao;

    querJogar = MenuInicio();

    switch (querJogar) {
    case 1: printf("\nInsira o seu nome de treinador --> ");
        while (getchar() != '\n'); // Limpa o buffer (consome os \n que tão dentro do buffer até não haver mais
        fgets(utilizador, 50 - 1, stdin);
            break;
        case 2:
            printf("\nSaindo do jogo. Ate logo!\n");
            return 0;
            break;
        default:
            printf("\nOpcao invalida. Tente novamente.\n");
            querJogar = 0;
    }

    do {
        if (querJogar == 1)
        {
            do
            {
                system("cls");
                mostrarEquipas(&equipas, MAX_EQUIPAS, -1);
                printf("\nCom que equipa deseja jogar?\nSe quiser ver os jogadores de alguma equipa, pressione 0\n");
                scanf("%d", &querJogar);

                if (querJogar == 0)
                {
                    do {
                        printf("De que equipa quer ver os jogadores? --> ");
                        scanf("%d", &opcao);
                        if (opcao < 1 || opcao > 18)
                        {
                            printf("Introduza uma equipa valida\n");
                        }
                    } while (opcao < 1 || opcao > 18);


                    if (opcao > 0)
                    {
                        system("cls");
                        opcao -= 1;

                        mostrarJogadores(equipas[opcao], MAX_JOGADORES);

                        printf("Carregue numa tecla para voltar a lista das equipas\n");
                        getch(); //Faz com que o programa espere que a pessoa clique numa tecla qq
                    }
                }
                else if (querJogar >= 1 && querJogar <= 18)
                {
                    equipaEscolhida = equipas[querJogar - 1];
                    strcpy(equipaEscolhida.treinador, utilizador);
                }
            } while (querJogar < 1 || querJogar > 18);

            system("cls");




            contadorCompra = 0;
            memset(abreviacao, 0, sizeof(abreviacao));

            do {
                printf("Deseja comprar algum jogador?\n 1 - Sim\n");

                do {
                    scanf("%d", &opcaoTroca);


                    if (opcaoTroca == 1)
                    {
                        mostrarEquipas(&equipas, MAX_EQUIPAS, querJogar - 1);

                        printf("\nDe que equipa quer comprar algum jogador?\n");

                        do {
                            scanf("%d", &opcao);
                            contaAbreviacao = 0;

                            do {
                                comprou = strcmp(abreviacao[contadorCompra], equipas[opcao - 1].abreviacao);
                                contaAbreviacao += 1;
                            } while (comprou != 0 && contaAbreviacao < 3);


                            if ((opcao - 1 != querJogar - 1) && comprou != 0)
                            {
                                system("cls");
                                int jogadorCompra, jogadorTroca;
                                mostrarJogadores(equipas[opcao - 1], MAX_JOGADORES);
                                printf("Que jogador deseja comprar?\n");
                                scanf("%d", &jogadorCompra);

                                for (int i = 0; i < MAX_JOGADORES; i++)
                                {
                                    if (equipas[opcao - 1].jogador[i].numero == jogadorCompra)
                                    {
                                        valor = equipas[opcao - 1].jogador[i].salario * 5 * equipas[opcao - 1].jogador[i].mesesrest;
                                        /*if (equipaEscolhida.income > valor)
                                        {*/
                                        system("cls");
                                        mostrarJogadores(equipaEscolhida, MAX_JOGADORES);
                                        printf("Que jogador deseja trocar pelo %s?\n", equipas[opcao - 1].jogador[i].nomej);
                                        scanf("%d", &jogadorTroca);

                                        for (int j = 0; j < MAX_JOGADORES; j++)
                                        {
                                            if (equipaEscolhida.jogador[j].numero == jogadorTroca)
                                            {
                                                equipaEscolhida.income -= valor;
                                                TrocaJogadores(&equipas[opcao - 1].jogador[i], &equipaEscolhida.jogador[j]);
                                                conseguiu = 1;
                                                contadorCompra += 1;
                                                strcpy(abreviacao[contadorCompra], equipas[opcao - 1].abreviacao);
                                            }
                                            else if (j == MAX_JOGADORES - 1 && conseguiu == 0)
                                            {
                                                printf("Esse jogador nao existe\n");
                                            }
                                        }
                                        conseguiu = 1;
                                        /*}
                                        else
                                        {
                                            printf("A sua equipa nao tem fundos suficientes para comprar esse jogador\n");
                                        }*/
                                    }
                                    else if (i == MAX_JOGADORES - 1 && conseguiu == 0)
                                    {
                                        printf("Esse jogador nao existe\n");
                                    }
                                }
                            }
                            else
                            {
                                printf("Voce ja comprou um jogador a essa equipa ou a equipa e sua\n");
                            }

                        } while ((opcao < 1 && opcao == querJogar) || conseguiu == 0);

                    }
                } while (opcaoTroca == 1);

            } while (opcaoTroca == 1 && contadorCompra < 3);



            system("cls");
            printf("A tatica atual da sua equipa e %s. Deseja muda-la?\n 0 - Nao\t 1 - Sim\n", equipaEscolhida.formacao.esquema);
            do {
                scanf("%d", &opcao);

                if (opcao == 1)
                {
                    for (int i = 0; i < MAX_JOGADORES; i++) //Mete as posicoes dos jogadores todos a 0
                    {
                        equipaEscolhida.jogador[i].coordenadas[0] = 0;
                        equipaEscolhida.jogador[i].coordenadas[1] = 0;
                    }

                    int taticaEscolhida;
                    printf("Escolha uma das seguintes taticas\n");
                    printf("1 / %s\t2 / %s\t3 / %s\t4 / %s\n", listaFormacoes[0].esquema, listaFormacoes[1].esquema, listaFormacoes[2].esquema, listaFormacoes[3].esquema);

                    do {
                        scanf("%d", &taticaEscolhida);

                        equipaEscolhida.formacao = listaFormacoes[taticaEscolhida - 1];

                        if (taticaEscolhida < 1 || taticaEscolhida > 4)
                        {
                            printf("Escolha uma tatica valida\n");
                        }
                    } while (taticaEscolhida < 1 || taticaEscolhida > 4);

                    selecionarPlantel(&equipaEscolhida, taticaEscolhida);
                    vePosicao(&equipaEscolhida);

                }
                else if (opcao != 0)
                {
                    printf("Escolha uma opcao valida\n");
                }
            } while (opcao != 1 && opcao != 0);
        }

        Equipa ordemSorteio[34];
        sorteio(equipas, equipaEscolhida, ordemSorteio);

        int vitorias = 0;
        int derrotas = 0;
        int empates = 0;

        int golosMarcados = 0;
        int golosSofridos = 0;


        for (int i = 0; i < 34; i++)
        {
            Equipa equipaAdversa = ordemSorteio[i];

            vePosicao(&equipaEscolhida);
            vePosicao(&equipaAdversa);

            // Exibe a ordem do sorteios
            for (int j = 0; j < 34; j++) {
                printf("%d ---%s vs %s---\n", j + 1, equipaEscolhida.abreviacao, ordemSorteio[j].abreviacao);
            }

            printf("Pressione uma tecla para iniciar o jogo %d", i + 1);
            getch();

            system("cls");

            int tempo = 0;
            int golos[2] = { 0, 0 };

            float forcaAtaque[2] = { calcularForcaAtaque(&equipaEscolhida), calcularForcaAtaque(&equipaAdversa) };
            float forcaDefesa[2] = { calcularForcaDefesa(equipaEscolhida), calcularForcaDefesa(equipaAdversa) };

            printf("---%s vs %s---\n", equipaEscolhida.abreviacao, equipaAdversa.abreviacao);

            while (tempo <= 90)
            {
                int ale = rand() % 2;

                if (ale == 0)
                {
                    printf("\nAtaque de %s\n", equipaEscolhida.abreviacao);
                    golos[0] += Ataque(&equipaEscolhida, &equipaAdversa, forcaAtaque[0]);
                }
                else
                {
                    printf("\nAtaque de %s\n", equipaAdversa.abreviacao);
                    golos[1] += Ataque(&equipaAdversa, &equipaEscolhida, forcaAtaque[1]);
                }


                tempo += 5;
            }

            printf("--- %d %s vs %s %d ---\n", golos[0], equipaEscolhida.abreviacao, equipaAdversa.abreviacao, golos[1]);

            golosMarcados += golos[0];
            golosSofridos += golos[1];

            if (golos[0] > golos[1])
            {
                vitorias += 1;
            }
            else if (golos[0] < golos[1])
            {
                derrotas += 1;
            }
            else
            {
                empates += 1;
            }
            getch();
        }

        system("cls");
        printf("Jogou 34 jogos\n");
        printf("Ganhou %d jogos\t Perdeu %d jogos\t Empatou em %d jogos\n", vitorias, derrotas, empates);
        printf("Marcou %d golos\t Sofreu %d golos\n", golosMarcados, golosSofridos);
        printf("Desjeja continuar a jogar?\n 1 - Sim");
        scanf("%d", &querJogar);
    } while (querJogar == 1);

    printf("\nSaindo do jogo. Ate logo!\n");

    return 0;
}
