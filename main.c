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


// visualiza array de produtos, se necessario.
void viewProduct(struct Product product){
        printf("%d\n", product.code);
        printf("%s\n", product.name);
        printf("%d\n", product.amount);
        printf("%.2f\n", product.price);
        printf("%s\n", product.state);
}


void writeFile(struct Product *products, int size, char *fileName) {
    FILE *file;
    char intToString[10];
    char floatToString[10];
    file = fopen(fileName, "w");

    if (file != NULL) {
        for (int seek = 0; seek < size; seek++) {
            fseek(file, 0, SEEK_END); // Move para o final do arquivo

            sprintf(intToString, "%d", products[seek].code);   // converte de int para str
            fputs(intToString, file);
            fputs("\n", file);

            fputs(products[seek].name, file);
            fputs("\n", file);

            sprintf(intToString, "%d", products[seek].amount);   // converte de int para str
            fputs(intToString, file);
            fputs("\n", file);

            sprintf(floatToString, "%.2f", products[seek].price);   // converte de float para str
            fputs(floatToString, file);
            fputs("\n", file);

            fputs(products[seek].state, file);
            fputs("\n", file);
        }

        fclose(file);
    }
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
    //viewProducts(products, size);
}


// pesquisa produto por código
void searchProduct(struct Product *product, int code, int size){
    for(int i = 0; i < size; i++){
        if(product[i].code == code){
            viewProduct(product[i]);
            break;
        }
    }
}


// pesquisa produto que possui a menor quantidade
void searchLeastAmount(struct Product *products, int size){
    struct Product save[1];
    int amount = 9999999;

    for(int i = 0; i < size; i++){
        if(products[i].amount < amount){
            save[0] = products[i];
            amount = products[i].amount;
        }
    }
    viewProduct(*save);
}


// pesquisa produto por estado , em ordem alfabetica
void searchProductByState(struct Product *products, int size, char *state){
    struct Product save[size];
    struct Product aux[1];

    for(int i = 0; i < size; i++) {
        save[i] = products[i];
    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(strcmp(products[j].name, products[j + 1].name) < 0){
                aux[0] = save[j];
                save[j] = save[j + 1];
                save[j + 1] = aux[0];
            }
        }
    }
    for(int i = 0; i < size; i++) {
        if (strcmp(products[i].state, state) == 0) {
            viewProduct(products[i]);
        }
    }
}


// produto de menor quantidade no estoque por estado
void searchLeastAmountProductByState(struct Product *products, int size, char *state){
    struct Product save[size];
    struct Product aux[1];

    for(int i = 0; i < size; i++) {
        save[i] = products[i];
    }

    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            if(products[j].amount < products[j + 1].amount){
                aux[0] = save[j];
                save[j] = save[j + 1];
                save[j + 1] = aux[0];
            }
        }
    }
    for(int i = 0; i < size; i++) {
        if (strcmp(products[i].state, state) == 0) {
            viewProduct(products[i]);
            break;
        }
    }
}


// calcula o preco total com base na quantidade
void totalPrice(struct Product *products, int size){
    int total = 0;
    float sum = 0;

    for(int i = 0; i < size; i++){
        total += products[i].amount;
        sum += (products[i].price * products[i].amount);
    }
    printf("%d\n", total);
    //printf("%.2f\n", sum);
}


// chama a funcao com base na escolha do usuario
void select(struct Product *products, int size,  int option, char *fileName, int code, char *state){
    switch (option) {
        case 1:
            createReport(products, size, fileName);
            break;
        case 2:
            searchProduct(products, code, size);
            break;
        case 3:
            searchLeastAmount(products, size);
            break;
        case 4:
            searchProductByState(products, size, state);
            break;
        case 5:
            searchLeastAmountProductByState(products, size, state);
            break;
        case 6:
            totalPrice(products, size);
            break;
    }
}


// abre e le arquivo
int readFile(char *filePath, int size, int option, char *fileName, int code, char *state) {
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
    select(products, size, option, fileName, code, state);
    return 0;
}


// trata a linha de comandos
void argparser(int argc, char argv[][200], int size){
    if(strcmp(argv[2], "1") == 0) {
        readFile(argv[1], size, 1, argv[3], -1, "MG");
    }
    else if(strcmp(argv[2], "2") == 0){
        readFile(argv[1], size, 2, NULL, atoi(argv[3]), "MG");
    }
    else if(strcmp(argv[2], "3") == 0){
        readFile(argv[1], size, 3, NULL, -1,"MG");
    }
    else if(strcmp(argv[2], "4") == 0){
        readFile(argv[1], size, 4, NULL, -1, argv[3]);
    }
    else if(strcmp(argv[2], "5") == 0){
        readFile(argv[1], size, 5, NULL, -1,argv[3]);
    }
    else if(strcmp(argv[2], "6") == 0){
        readFile(argv[1], size, 6, NULL, -1, "MG");
    }
    else{
        printf("Opcao invalida! %s", argv[2]);
    }
}


#define MAX_WORDS 4
#define MAX_LENGTH 200


int main() {
    int input;
    int arg_count;
    char arg_values[MAX_WORDS][MAX_LENGTH];

    scanf("%d", &input);

    // Limpar o buffer de entrada após scanf
    while (getchar() != '\n');

    fgets(arg_values[0], sizeof(arg_values[0]), stdin);

    // Remover o caractere de nova linha do final da string
    arg_values[0][strcspn(arg_values[0], "\n")] = '\0';

    // Processar a linha para obter as palavras separadas
    char *token = strtok(arg_values[0], " ");
    int i = 0;
    while (token != NULL && i < MAX_WORDS) {
        strcpy(arg_values[i], token);
        token = strtok(NULL, " ");
        i++;
    }

    argparser(arg_count, arg_values, input);

    return 0;
}