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


int readFile(char *filePath, int size) {
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
    return 0;
}


int main(int argc, char *argv[]){
    readFile("C:\\Users\\Marcu\\CLionProjects\\supply\\input.txt", 1);
    return 0;
}