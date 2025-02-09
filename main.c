#include <stdio.h>
#include <stdlib.h>
#include <string.h>


typedef struct { //registrando o motivo da saida conforme ultimo requisito
    char nome[50];
    char motivo[20];
} RegistroSaida;

typedef struct Animal
{
    char nome[50];
    char tutor[50];
    char servico[50];
    char status[50];
    struct Animal *proximo;
} Animal;
Animal *inicio = NULL;

typedef struct PilhaSaida{
    Animal *animal;
    struct PilhaSaida *proximo;
} PilhaSaida;
PilhaSaida *topo = NULL;

RegistroSaida historico[];
int contadorHistorico = 0;
void registrarNoHistorico(char *nome, char *motivo) {
    strcpy(historico[contadorHistorico].nome, nome);
    strcpy(historico[contadorHistorico].motivo, motivo);
    contadorHistorico++; //contando pra saber qnts iterações no 'for' pra mostrar a lista
}

void encaminharAnimalSaida(Animal *animal)
{
    PilhaSaida *animalFinalizado = (PilhaSaida *)malloc(sizeof(PilhaSaida));
    if (!animalFinalizado)
    {
        printf("Não foi possivel alocar novo espaço de memoria.\n");
        return;
    }
    animalFinalizado->animal = animal;
    animalFinalizado->proximo = topo;
    topo = animalFinalizado;
    registrarNoHistorico(animal->nome, "finalizado");
    printf("'%s' foi pra pilha de finalizados! Aguarde para a saida...\n", animal->nome);
}
Animal *entregarAnimal()
{
    if (!topo)
    {
        printf("Nao ha animais aguardando saida!\n");
        return NULL;
    }
    PilhaSaida *temp = topo;
    Animal *animal = topo->animal;
    topo = topo->proximo;
    free(temp);
    return animal;
}

void listarPilha() //mostrando a formação da pilha pra entrega
{
    if (!topo)
    {
        printf("Pilha de saida vazia.\n");
        return;
    }

    printf("Animais na pilha de saida:\n");
    PilhaSaida *temp = topo;
    while (temp !=NULL)
    {
        printf("- %s\n", temp->animal->nome);
        temp = temp->proximo;
    }
}
int contadorAnimaisNaPilha() //contar pra q a entrega seja liberada a partir de 3
{
    int contador = 0;
    PilhaSaida *temp = topo;
    while (temp != NULL)
    {
        contador++;
        temp = temp->proximo;
    }
    return contador;
}

Animal *alocarMemoriaPonteiro()
{
    Animal *ponteiro = (Animal *)malloc(sizeof(Animal));

    if (!ponteiro)
    {
        printf("Não foi possivel alocar novo espaço de memoria.\n");
        return NULL;
    }
    return ponteiro;
}

Animal *buscarAnimal(const char *nome)
{
    Animal *atual = inicio;
    while (atual != NULL)
    {
        if (strcmp(atual->nome, nome) == 0)
        {
            return atual;
        }
        atual = atual->proximo;
    }
    return NULL;
}

int contadorEmAndamento() //pra limitar a qnt de atendimentos ao msm tempo
{
    int contador = 0;
    Animal *atual = inicio;
    while (atual != NULL)
    {
        if (strcmp(atual->status, "em andamento") == 0)
        {
            contador++;
        }
        atual = atual->proximo;
    }
    return contador;
}

void entradaDadosString(char *buffer, size_t tamanho) //msm funcao da prova
{
    if (fgets(buffer, tamanho, stdin))
    {
        buffer[strcspn(buffer, "\n")] = '\0';
    }
}

void clearinput(){ //encontrada no notion pra tbm tentar tratar os problemas de input
    int c;
    while ((c = getchar()) != '\n' && c != EOF){}
}

char *menuServico()
{
    int opcaoServico = 0;
    static char servicoEscolhido[50];

    do
    {
        printf("\nQual o servico desejado do Pet Shop Mundo Cao?\n");
        printf("--- Escolha uma opcao ---\n");
        printf("1 - Banho.\n");
        printf("2 - Tosa.\n");
        printf("3 - Ambos (banho e tosa).\n");
        printf("Opcao: ");
        scanf("%d", &opcaoServico);


        switch (opcaoServico)
        {
        case 1:
            strcpy(servicoEscolhido, "banho");
            printf("Servico definido como 'banho'.\n");
            opcaoServico = 9;
            break;

        case 2:
            strcpy(servicoEscolhido, "tosa");
            printf("Servico definido como 'tosa'.\n");
            opcaoServico = 9;
            break;

        case 3:
            strcpy(servicoEscolhido, "ambos");
            printf("Servico definido como 'ambos'.\n");
            opcaoServico = 9;
            break;

        default:
            printf("Opcao invalida!\n");
            break;
        }

    } while (opcaoServico != 9);

    return servicoEscolhido;
}

void statusServico(char *buffer)
{
    int opcaoStatusServico = 0;

    do
    {
        printf("\nQual o status do servico do seu pet?\n");
        printf("Escolha uma opcao:\n");
        printf("1 - Aguardando.\n");
        printf("2 - Em andamento.\n");
        printf("3 - Finalizado.\n");
        printf("Opcao: ");
        scanf("%d", &opcaoStatusServico);
        clearinput();

        switch (opcaoStatusServico)
        {
            case 1:
                strcpy(buffer, "aguardando");
                printf("Servico definido como 'aguardando'.\n");
                return;

            case 2:
                strcpy(buffer, "em andamento");
                printf("Servico definido como 'em andamento'.\n");
                return;

            case 3:
                strcpy(buffer, "finalizado");
                printf("Servico definido como 'finalizado'.\n");
                return;

            default:
                printf("Opcao invalida! Escolha 1, 2 ou 3.\n");
                break;
        }

    } while (1);
}

void cadastrarAnimal()
{
    Animal *novoAnimal = alocarMemoriaPonteiro();
    Animal *auxiliar = inicio;

    if (novoAnimal == NULL)
        return;

    printf("Digite o nome do animal: ");
    clearinput();
    entradaDadosString(novoAnimal->nome, sizeof(novoAnimal->nome));
    printf("Digite o nome do tutor: ");
    entradaDadosString(novoAnimal->tutor, sizeof(novoAnimal->tutor));
    printf("Digite o nome do servico solicitado: ");
    strcpy(novoAnimal->servico, menuServico());
    printf("Escolha o status do servico: ");
    statusServico(novoAnimal->status);
    if (strcmp(novoAnimal->status, "em andamento") == 0 && contadorEmAndamento() >= 3)
    {
        printf("\nJá existem 3 animais sendo atendidos. Não é possível cadastrar agora.\n");
        free(novoAnimal);
        return;
    }
    printf("\nCadastrado:\n Nome: %s, Tutor: %s, Servico: %s, Status: %s\n",
           novoAnimal->nome, novoAnimal->tutor, novoAnimal->servico, novoAnimal->status);
    if (strcmp(novoAnimal->status, "finalizado") == 0)
    {
        encaminharAnimalSaida(novoAnimal);
        return;
    }
    if (inicio == NULL)
    {
        inicio = novoAnimal;
        novoAnimal->proximo = NULL;
    }
    else
    {
        Animal *auxiliar = inicio;
        while (auxiliar->proximo != NULL)
        {
            auxiliar = auxiliar->proximo;
        }
        auxiliar->proximo = novoAnimal;
        novoAnimal->proximo = NULL;
    }
}

void verFilaEspera() //opcao pra ver a fila sendo formada
{
    if (!inicio)
    {
        printf("\nNenhum animal aguardando atendimento! \n");
        return;
    }

    Animal *auxiliar = inicio;
    int flag = 0;

    printf("\nFILA DE ESPERA:\n");
    while (auxiliar != NULL)
    {

        if (strcmp(auxiliar->status, "aguardando") == 0)
        {
            printf("Nome: %s\n", auxiliar->nome);
            printf("Tutor: %s\n", auxiliar->tutor);
            printf("Servico: %s\n", auxiliar->servico);
            printf("-------------------------\n");
            flag = 1;
        }
        auxiliar = auxiliar->proximo;
    }

    if (!flag)
    {
        printf("Nenhum animal aguardando atendimento!\n");
    }
}

void cancelarEspera()
{
    if (inicio == NULL)
    {
        printf("\n Nenhum animal aguardando!\n");
        return;
    }
    char nomeRemover[50];
    printf("\nDigite o nome do animal que deseja remover da fila de espera: ");
    clearinput();
    entradaDadosString(nomeRemover, sizeof(nomeRemover));
    Animal *atual = inicio;
    Animal *anterior = NULL;
    Animal *animalEncontrado = buscarAnimal(nomeRemover);
    if (animalEncontrado == NULL)
    {
        printf("\n '%s' não foi encontrado no sistema\n", nomeRemover);
        return;
    }
    if (strcmp(animalEncontrado->status, "aguardando") != 0)
    {
        printf("\n '%s' não está aguardando, cheque se já foi finalizado!\n", nomeRemover);
        return;
    }
    while (atual != NULL)
    {
        if (atual==animalEncontrado)
        {
            if (anterior == NULL)
            {
                inicio = atual->proximo;
            }
            else
            {
                anterior->proximo = atual->proximo;
            }
            registrarNoHistorico(atual->nome, "cancelado");
            free(atual);
            printf("\n'%s' foi removido(a) da fila de espera !\n", nomeRemover);
            return;
        }
        anterior = atual;
        atual = atual->proximo;
    }
}

void atualizarStatus()
{
    if (inicio == NULL)
    {
        printf("\nNenhum animal cadastrado.\n");
        return;
    }
    char nomeAtualizar[50];
    printf("\nDigite o nome do animal: ");
    clearinput();
    entradaDadosString(nomeAtualizar, sizeof(nomeAtualizar));
    Animal *animal = buscarAnimal(nomeAtualizar);
    if (animal == NULL)
    {
        printf("\n'%s' não encontrado.\n", nomeAtualizar);
        return;
    }
    if (strcmp(animal->status, "em andamento") != 0)
    {
        int qtdEmAndamento= contadorEmAndamento();
        if (qtdEmAndamento >= 3)
        {
            printf("\n3 animais sendo atendidos. Não é possível atender agora.\n");
            return;
        }
    }
    printf("\nNovo status de '%s':\n", animal->nome);
    statusServico(animal->status);
    if (strcmp(animal->status, "finalizado") == 0)//aqui encaminhamos o pet p pilha de saida e chamamos o prox da fila de espera
    {
        encaminharAnimalSaida(animal);

        if (contadorEmAndamento() >= 3) {
            printf("3 animais em atendimento, aguarde.\n");
            return;
        }
        Animal *atual = inicio;
        while (atual != NULL) {
            if (strcmp(atual->status, "aguardando") == 0) {
                strcpy(atual->status, "em andamento");
                printf("'%s' estava na fila de espera e agora foi para atendimento!\n", atual->nome);
                return;
            }
            atual = atual->proximo;
        }
    }
}

void entregaDeAnimais()
{
    int totalNaPilha = contadorAnimaisNaPilha();
    if (totalNaPilha < 3)
    {
        printf("\nNão há 3 animais finalizados. Aguarde para a entrega.\n");
        return;
    }
    printf("\nPets sendo entregues:\n");
    for (int i = 0; i < 3; i++)
    {
        if (topo == NULL)
            break;
        PilhaSaida *animalFinalizado = topo;
        printf("- %s\n", animalFinalizado->animal->nome);
        topo = topo->proximo;
        free(animalFinalizado->animal);
        free(animalFinalizado);
    }
    printf("3 pets foram entregues com sucesso! Voltem sempre :D\n");
}

void listarHistorico() {
    if (contadorHistorico==0) {
        printf("\nNenhum animal registrado no histórico.\n");
        return;
    }
    printf("\nHistórico de Saída:\n");
    for (int i = 0; i < contadorHistorico; i++) {
        printf("Nome: %s - Motivo: %s\n", historico[i].nome, historico[i].motivo);
    }
}

int main()
{
    int opcao;
    do
    {
        printf("\nBem-vindo(a) ao 'Pet Shop Mundo Cao'!\n");
        printf("Escolha uma opcao:\n");
        printf("1 - Cadastrar animal.\n");
        printf("2 - Ver fila de espera.\n");
        printf("3 - Cancelar serviço em espera.\n");
        printf("4 - Atualizar status de um animal.\n");
        printf("5 - Mostrar pilha de saida.\n");
        printf("6 - Entrega de animais.\n");
        printf("7 - Mostrar histórico de saídas/cancelamentos.\n");
        printf("8 - Sair.\n");
        printf("Opcao: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            cadastrarAnimal();
            break;
        case 2:
            verFilaEspera();
            break;
        case 3:
            cancelarEspera();
            break;
        case 4:
            atualizarStatus();
            break;
        case 5:
            listarPilha();
            break;
        case 6:
            entregaDeAnimais();
            break;
        case 7:
            listarHistorico();
            break;
        case 8:
            printf("Sistema encerrado!\n");
            break;

        default:
            printf("Opcao invalida! Escolha uma opcao entre 1 e 8.\n");
            break;
        }
    } while (opcao != 8);
    return 0;
}