#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 1024

struct FileBlock {
    char data[BLOCK_SIZE];
    struct FileBlock *nextBlock;
};

struct File {
    struct FileBlock *firstBlock;
    struct FileBlock *lastBlock;
};

struct FileBlock *createBlock() {
    struct FileBlock *newBlock = (struct FileBlock *)malloc(sizeof(struct FileBlock));
    if (newBlock == NULL) {
        printf("Memory allocation error!\n");
        exit(1);
    }
    newBlock->nextBlock = NULL;
    return newBlock;
}

void addBlock(struct File *file, struct FileBlock *newBlock) {
    if (file->firstBlock == NULL) {
        file->firstBlock = newBlock;
        file->lastBlock = newBlock;
    } else {
        file->lastBlock->nextBlock = newBlock;
        file->lastBlock = newBlock;
    }
}

void printFile(struct File *file) {
    struct FileBlock *currentBlock = file->firstBlock;

    while (currentBlock != NULL) {
        printf("%s", currentBlock->data);
        currentBlock = currentBlock->nextBlock;
    }

    printf("\n");
}

int main() {
    struct File file;
    struct FileBlock *block1, *block2, *block3;

    block1 = createBlock();
    sprintf(block1->data, "Data for Block 1");
    addBlock(&file, block1);

    block2 = createBlock();
    sprintf(block2->data, "Data for Block 2");
    addBlock(&file, block2);

    block3 = createBlock();
    sprintf(block3->data, "Data for Block 3");
    addBlock(&file, block3);

    printf("File content:\n");
    printFile(&file);

    free(block1);
    free(block2);
    free(block3);

    return 0;
}
