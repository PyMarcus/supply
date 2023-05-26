#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Product {
    int code;
    int amount;
    float price;
    char name[200];
    char state[2];
};


// visualiza array de produtos, se necessario.
void viewProducts(struct Product *products, int size){
    for (int j = 0; j < size; j++) {
        printf("Dados %d:\n", j + 1);
        printf("Codigo: %d\n", products[j].code);
        printf("Nome: %s\n", products[j].name);
        printf("Quantidade: %d\n", products[j].amount);
        printf("Preco: %.2f\n", products[j].price);
        printf("Estado: %s\n", products[j].state);
        printf("\n");
    }
}


void writeFile(struct Product *products, int size, char *fileName){
    FILE *file;
    char intToString[10];
    char floatToString[10];
    file = fopen(fileName, "w");
    for(int seek = 0; seek < size; seek++){
        sprintf(intToString, "%d", products[seek].code);   // converte de int para str
        sprintf(floatToString, "%f", products[seek].code);   // converte de float para str
        fprintf(file , intToString);
        fprintf(file , "\n");
        fprintf(file, products[seek].name);
        fprintf(file , "\n");
        sprintf(intToString, "%d", products[seek].amount);   // converte de int para str
        fprintf(file, intToString);
        fprintf(file , "\n");
        fprintf(file, floatToString);
        fprintf(file , "\n");
        fprintf(file, products[seek].state);
        fprintf(file , "\n");
    }
    fclose(file);
}


// gera um relatorio, com os nomes em ordem alfabetica
void createReport(struct Product *products, int size, char *fileName){
    for(int product = 0; product < size - 1; product++){
        for(int _product = 0; _product < size - 1; _product++){
            // se a ordem lexicografica de x > x+1, entao substitui x por x+1
            if(strcmp(products[_product].name, products[_product + 1].name) > 0){
                struct Product aux = products[_product];
                products[_product] = products[_product + 1];
                products[_product + 1] = aux;
            }
        }
    }
    writeFile(products, size, fileName);
    viewProducts(products, size);
}


// chama a funcao com base na escolha do usuario
void select(struct Product *products, int size,  int option, char *fileName){
    switch (option) {
        case 1:
            createReport(products, size, fileName);
            break;
    }
}


// abre e le arquivo
int readFile(char *filePath, int size, int option, char *fileName) {
    FILE *file;
    char lines[200];
    struct Product products[5 * size];
    int index = 0;
    int counter = 0;

    // abre arquivo, em caso de erro, termina execucao
    file = fopen(filePath, "r");
    if (file == NULL) {
        printf("ERRO ao abrir arquivo.Possivelmente, caminho incorreto\n");
        return 1;
    }

    // le arquivo e salva os dados na estrutura products
    while (fgets(lines, 200, file) != NULL) {
        // Remover o caractere de nova linha (\n) do final da linha
        lines[strcspn(lines, "\n")] = '\0';

        switch (counter % 5) {
            case 0:
                products[index].code = atoi(lines);
                break;
            case 1:
                strcpy(products[index].name, lines);
                break;
            case 2:
                products[index].amount = atoi(lines);
                break;
            case 3:
                products[index].price = atof(lines);
                break;
            case 4:
                strcpy(products[index].state, lines);
                index++;
                break;
        }

        counter++;
    }

    fclose(file);
    select(products, size, option, fileName);
    return 0;
}


// trata a linha de comandos
void argparser(int argc, char *argv[], int size){
    if(strcmp(argv[2], "1") == 0) {
        readFile(argv[1], size, 1, argv[3]);
    }
    else if(strcmp(argv[2], "2") == 0){
        readFile(argv[1], size, 2, NULL);
    }
    else if(strcmp(argv[2], "3") == 0){
        readFile(argv[1], size, 3, NULL);
    }
    else if(strcmp(argv[2], "4") == 0){
        readFile(argv[1], size, 4, NULL);
    }
    else if(strcmp(argv[2], "5") == 0){
        readFile(argv[1], size, 5, NULL);
    }
    else if(strcmp(argv[2], "6") == 0){
        readFile(argv[1], size, 6, NULL);
    }
    else{
        printf("Opcao invalida! %s", argv[2]);
    }
}


int main(int argc, char *argv[]){

    /*
     *
     * O objetivo deste trabalho é fazer
     * a gestão simples de um mercado
     *
     * A entrada de dados é baseada em
     * arquivo e deve-se usar uma estrutura para
     * manipular os produtos conforme solicitado
     * pelo professor.
     *
     * */
    int input;
    scanf("%d", &input);
    if(argc > 1){
        argparser(argc, argv, input);
    }else{
        printf("Use .\\main.c [opcoes]");
        printf("Opcoes:\n");
        printf("1. Gerar relatorio de estoque\n"
               "2. Pesquisar por produto pelo codigo\n"
               "3. Listar dados do produto com menor quantidade em estoque\n"
               "4. Listar produtos por estado\n"
               "5. Encontrar produto com menor quantidade em estoque do estado\n"
               "6. Calcular a quantidade total de itens no estoque ");
    }

    return 0;
}