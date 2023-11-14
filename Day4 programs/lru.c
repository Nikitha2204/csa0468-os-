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

int findLeastRecentlyUsed(int frames[], int counters[], int n) {
    int minIndex = 0;
    int i;
    for (i = 1; i < n; i++) {
        if (counters[i] < counters[minIndex]) {
            minIndex = i;
        }
    }
    return minIndex;
}

int main() {
    int pages[PAGE_SIZE] = {0, 1, 2, 3, 2, 4, 5, 3, 4, 6};
    int frames[FRAME_SIZE];
    int counters[FRAME_SIZE] = {0}; 
    int pageFaults = 0;
	int i,j;
    printf("Page Reference String: ");
    for (i = 0; i < PAGE_SIZE; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n\n");

    for (i = 0; i < FRAME_SIZE; i++) {
        frames[i] = -1;
    }

    for (i = 0; i < PAGE_SIZE; i++) {
        printf("Referencing Page %d:\n", pages[i]);
        printFrames(frames, FRAME_SIZE);

        if (!isInFrames(frames, FRAME_SIZE, pages[i])) {
            pageFaults++;
            if (i < FRAME_SIZE) {
                int emptyIndex = -1;
                for (j = 0; j < FRAME_SIZE; j++) {
                    if (frames[j] == -1) {
                        emptyIndex = j;
                        break;
                    }
                }
                frames[emptyIndex] = pages[i];
                counters[emptyIndex] = i; 
            } else {
                int replaceIndex = findLeastRecentlyUsed(frames, counters, FRAME_SIZE);
                frames[replaceIndex] = pages[i];
                counters[replaceIndex] = i; 
            }
        } else {
            for (j = 0; j < FRAME_SIZE; j++) {
                if (frames[j] == pages[i]) {
                    counters[j] = i; 
                    break;
                }
            }
        }

        printf("\n");
    }

    printf("Total Page Faults: %d\n", pageFaults);

    return 0;
}
