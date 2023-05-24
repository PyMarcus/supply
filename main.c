#include <stdio.h>
#include <string.h>


/*
 * Programa para treinar a manipulação de arquivos em C
 * Receber quantidade de produtos
 * Manipular conforme os comandos passados, esta lista de produtos.
 * */


struct content{
    char text[100];
};



/*obtem a quantidade de linhas do arquivo*/
int getLines(FILE *file)
{

    int count = 0;
    char rows;

    while(fread (&rows, sizeof(char), 1, file))
    {
        if(rows == '\n'){
            count++;
        }
    }
    return count;
}


/* função que le o arquivo determinado.*/
int readFile(char *filePath, int row)
{
    char rows;
    char convert[2];
    int MAX_COLUMNS = 1000;
    char store[MAX_COLUMNS];
    int count = 0;
    FILE *_file_ = fopen(filePath, "r");
    FILE *file = fopen(filePath, "r");
    int lines = getLines(_file_);
    struct content phrases[lines];

    // se o local do arquivo estiver incorreto, retorna mensagem de nao encontrado
    if(file == NULL)
    {
        printf("[-]file not found!\n", stderr);
        return 1;
    }


    // le arquivo:
    while(fread (&rows, sizeof(char), 1, file)) {
        if(rows == '\n') {
            // copia a string formada para cada index do array
            strcpy(phrases[count].text, store);
            // reseta string
            strcpy(store, "");
            count++;
        }
        convert[0] = rows;
        convert[1] = '\0';
        // concatena os caracteres para formar a linha completa
        strcat(store, convert);
    }

    fclose(file);
    return 0;
}


int main(int argc, char *argv[]) {

    readFile("C:\\Users\\Marcu\\CLionProjects\\supply\\input.txt", 1);


    return 0;
}
