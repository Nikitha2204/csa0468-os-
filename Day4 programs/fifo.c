#include <stdio.h>

#define FRAME_SIZE 3
#define PAGE_SIZE 10

void printFrames(int frames[], int n) {
    printf("Frames: ");
    int i;
    for (i = 0; i < n; i++) {
        if (frames[i] == -1) {
            printf("[ ] ");
        } else {
            printf("[%d] ", frames[i]);
        }
    }
    printf("\n");
}

int isInFrames(int frames[], int n, int page) {
	int i;
    for (i = 0; i < n; i++) {
        if (frames[i] == page) {
            return 1; 
        }
    }
    return 0; 
}

int findEmptySlot(int frames[], int n) {
	int i;
    for (i = 0; i < n; i++) {
        if (frames[i] == -1) {
            return i;
        }
    }
    return -1; 
}

int main() {
    int pages[PAGE_SIZE] = {0, 1, 2, 3, 2, 4, 5, 3, 4, 6};
    int frames[FRAME_SIZE];
    int pageFaults = 0;
    int frameIndex = 0;
	int i,j;
    for (i = 0; i < FRAME_SIZE; i++) {
        frames[i] = -1;
    }

    printf("Page Reference String: ");
    for (i = 0; i < PAGE_SIZE; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n\n");

    for (i = 0; i < PAGE_SIZE; i++) {
        printf("Referencing Page %d:\n", pages[i]);
        printFrames(frames, FRAME_SIZE);

        if (!isInFrames(frames, FRAME_SIZE, pages[i])) {
            pageFaults++;
            if (frameIndex < FRAME_SIZE) {
                frames[frameIndex] = pages[i];
                frameIndex++;
            } else {
                int oldestIndex = 0;
                for (j = 1; j < FRAME_SIZE; j++) {
                    if (frames[j] < frames[oldestIndex]) {
                        oldestIndex = j;
                    }
                }
                frames[oldestIndex] = pages[i];
            }
        }

        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);

    return 0;
}
