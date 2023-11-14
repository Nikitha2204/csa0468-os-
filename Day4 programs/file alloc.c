#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 1024
#define FILE_SIZE 5

struct IndexBlock {
    int pointers[FILE_SIZE];
};

struct DataBlock {
    char data[BLOCK_SIZE];
};

int main() {
    FILE *file;
    struct IndexBlock indexBlock;
    struct DataBlock dataBlocks[FILE_SIZE];
	int i;
    for (i = 0; i < FILE_SIZE; i++) {
        sprintf(dataBlocks[i].data, "Data for Block %d", i + 1);
    }

    for (i = 0; i < FILE_SIZE; i++) {
        indexBlock.pointers[i] = i;
    }

    file = fopen("indexed_file.bin", "wb");
    if (file == NULL) {
        printf("Error opening file for writing!\n");
        exit(1);
    }

    fwrite(&indexBlock, sizeof(struct IndexBlock), 1, file);

    for (i = 0; i < FILE_SIZE; i++) {
        fwrite(&dataBlocks[i], sizeof(struct DataBlock), 1, file);
    }

    fclose(file);
    file = fopen("indexed_file.bin", "rb");
    if (file == NULL) {
        printf("Error opening file for reading!\n");
        exit(1);
    }

    fread(&indexBlock, sizeof(struct IndexBlock), 1, file);

    printf("Reading Data Blocks:\n\n");
    for (i = 0; i < FILE_SIZE; i++) {
        fseek(file, indexBlock.pointers[i] * sizeof(struct DataBlock), SEEK_SET);
        fread(&dataBlocks[i], sizeof(struct DataBlock), 1, file);
        printf("Data from Block %d: %s\n", i + 1, dataBlocks[i].data);
    }

    fclose(file);

    return 0;
}
