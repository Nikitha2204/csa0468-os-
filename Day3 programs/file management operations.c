#include <stdio.h>
#include <stdlib.h>

int main() {
    FILE *file;
    char filename[100];
    char content[100];
    printf("Enter the filename: ");
    scanf("%s", filename);
    file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        exit(1);
    }
    printf("Enter content to write to the file: ");
    scanf("%s", content);
    fprintf(file, "%s", content);
    fclose(file);
    file = fopen(filename, "r");

    if (file == NULL) {
        printf("Error opening file for reading!\n");
        exit(1);
    }
    printf("Content read from the file:\n");
    while (fscanf(file, "%s", content) != EOF) {
        printf("%s ", content);
    }
    fclose(file);

    return 0;
}
