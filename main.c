//Pré processamento

#include <stdio.h>
#include <stdlib.h>

#define TAMANHO_ACERVO 20

// Definição do comando para limpar a tela conforme o sistema operacional
#ifdef _WIN32
    #define LIMPAR_TELA "cls" // Para Windows
#else
    #define LIMPAR_TELA "clear" // Para Mac/Linux
#endif

// Definição da struct livro
struct livro {
    int codigo;
    char titulo[50];
    char autor[30];
    char area[30];
    int ano;
    char editora[30];
};
int total_livros = 0; // Controla quantos livros existem de verdade

// Função auxiliar para limpar buffer no Mac/Linux/Windows
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);//Limpa qualquer coisa que o usuário digitou até encontrar o enter. 
    //Também evita um loop infinito caso o usuário encerre a aplicação com Ctrl+D ou CTRL+C (EOF)
}

// Função para pausar a tela antes de limpar e mostrar o menu novamente
void pausar_tela() {
    int c;
    printf("\nPressione ENTER para continuar...");
    while ((c = getchar()) != '\n' && c != EOF); // Só continua quando o usuário digitar enter
}

void limparTela() {
    system(LIMPAR_TELA);
}
void cadastrarLivro (struct livro acervo[], int tamanhoMaximo); 
void imprimirLivros (struct livro acervo[], int total_livros);
void pesquisarLivro (struct livro acervo[], int total_livros);
void ordenarLivros (struct livro acervo[], int total_livros);
void carregarAcervo (struct livro acervo[]);
void salvarAcervo (struct livro acervo[], int total_livros);

int main() {
    struct livro acervo[TAMANHO_ACERVO];
    int op = 0;
    carregarAcervo(acervo); // Carrega o acervo do arquivo ao iniciar


while (op != 5) {
    limparTela();
    
    printf("=== SISTEMA DE CONTROLE DA BIBLIOTECA ===\n");
    printf("Livros cadastrados: %d/%d\n", total_livros, TAMANHO_ACERVO);
    printf("1 - Cadastrar livros\n");
    printf("2 - Imprimir livros\n");
    printf("3 - Buscar por codigo\n");
    printf("4 - Ordenar por ano\n");
    printf("5 - Sair\n");
    printf("Escolha: ");
    scanf("%d", &op);
    limpar_buffer(); // Limpa o buffer do scanf
    
    switch (op) {
        case 1:
            cadastrarLivro(acervo, TAMANHO_ACERVO);
            break;
        case 2:
            imprimirLivros(acervo, total_livros);
            pausar_tela();  // Espera o usuário ler antes de limpar
            break;
        case 3:
            pesquisarLivro(acervo, total_livros);
            break;
        case 4:
            ordenarLivros(acervo, total_livros);
            break;
        case 5:
            printf("Salvando dados e saindo do sistema...\n");
            salvarAcervo(acervo, total_livros);
            break;
        default:
            printf("Opcao invalida! Tente novamente.\n");
            pausar_tela();
    }


  } 

return 0;
}

//Funções para modularizar o código
void cadastrarLivro (struct livro acervo[], int tamanhoMaximo) {
        if (total_livros >= tamanhoMaximo) {
            printf("Memória cheia!\n");
            pausar_tela(); 
            return;
        }
        
        limparTela();
        printf("Cadastro do livro %d:\n", total_livros + 1);
        
        printf("Digite o codigo: ");
        scanf("%d", &acervo[total_livros].codigo);
        limpar_buffer(); // Remove o \n do buffer

        printf("Titulo: ");
        scanf("%[^\n]", acervo[total_livros].titulo); // O [^\n] lê tudo até o enter.
        limpar_buffer();

        printf("Autor: ");
        scanf("%[^\n]", acervo[total_livros].autor);
        limpar_buffer();

        printf("Area: ");
        scanf("%[^\n]", acervo[total_livros].area);
        limpar_buffer();

        printf("Ano: ");
        scanf("%d", &acervo[total_livros].ano);
        limpar_buffer();

        printf("Editora: ");
        scanf("%[^\n]", acervo[total_livros].editora);
        limpar_buffer();

        total_livros++; // Incrementa o contador real

        printf("\nLivro cadastrado com sucesso!\n");
        pausar_tela();
    
    }

    void imprimirLivros (struct livro acervo[], int total_livros) {
        limparTela();
        if (total_livros == 0) {
            printf("Nenhum livro cadastrado!\n");
        } else {
            for (int i = 0; i < total_livros; i++) { // Percorre só o que existe
                printf("\n--- Livro %d ---\n", i+1);
                printf("Codigo: %d\n", acervo[i].codigo);
                printf("Titulo: %s\n", acervo[i].titulo);
                printf("Ano: %d\n", acervo[i].ano);
                printf("Autor: %s\n", acervo[i].autor);
                printf("Area: %s\n", acervo[i].area);
                printf("Editora: %s\n", acervo[i].editora); 
            }
        }
    }

    void pesquisarLivro (struct livro acervo[], int total_livros) {
        limparTela();
        int codigoBusca;
        int encontrou = 0;
        printf("Digite o codigo para buscar: ");
        scanf("%d", &codigoBusca);
        limpar_buffer(); // Limpa o buffer do scanf do codigo

        for (int i = 0; i < total_livros; i++) {
            if (acervo[i].codigo == codigoBusca) {
                printf("\nENCONTRADO:\n");
                printf("Titulo: %s\n", acervo[i].titulo);
                printf("Autor: %s\n", acervo[i].autor);
                encontrou = 1;
                break; // Para de buscar se achou
            }
        }
        if (!encontrou) 
            printf("Livro nao encontrado!\n");
        pausar_tela();
    }

    void ordenarLivros (struct livro acervo[], int total_livros) {
        // Bubble Sort
        struct livro troca;
        for (int i = 0; i < total_livros - 1; i++) {
            for (int j = i + 1; j < total_livros; j++) {
                if (acervo[i].ano > acervo[j].ano) {
                    troca = acervo[i];
                    acervo[i] = acervo[j];
                    acervo[j] = troca;
                }
            }
        }
        printf("\nLivros ordenados por ano com sucesso!\n");
        pausar_tela();
    }
    
    void salvarAcervo (struct livro acervo[], int total_livros) {
        FILE *arquivo = fopen("acervo.dat", "wb");
        if (arquivo == NULL) {
            printf("Erro ao abrir o arquivo para salvar!\n");
            return;
        }
        fwrite(&total_livros, sizeof(int), 1, arquivo);
        if (total_livros > 0) {
            fwrite(acervo, sizeof(struct livro), total_livros, arquivo);
        }
        fclose(arquivo);
    }

    void carregarAcervo (struct livro acervo[]) {
        FILE *arquivo = fopen("acervo.dat", "rb");
        if (arquivo == NULL) {
            printf("Nenhum arquivo de acervo encontrado. Iniciando com acervo vazio.\n");
            return;
        }
        fread(&total_livros, sizeof(int), 1, arquivo);
        if (total_livros > 0) {
            fread(acervo, sizeof(struct livro), total_livros, arquivo);
        }
        fclose(arquivo);
    }