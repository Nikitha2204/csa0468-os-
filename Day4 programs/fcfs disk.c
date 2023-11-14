#include <stdio.h>
#include <stdlib.h>

#define MAX_REQUESTS 100

void calculateSeekTime(int requests[], int numRequests, int initialHeadPosition) {
    int totalSeekTime = 0;
    int currentHeadPosition = initialHeadPosition;
	int i;
    printf("Seek Sequence: %d", currentHeadPosition);

    for (i = 0; i < numRequests; i++) {
        int seekDistance = abs(currentHeadPosition - requests[i]);
        totalSeekTime += seekDistance;
        currentHeadPosition = requests[i];

        printf(" -> %d", currentHeadPosition);
    }

    printf("\nTotal Seek Time: %d\n", totalSeekTime);
}

int main() {
    int numRequests, initialHeadPosition;
    int requests[MAX_REQUESTS];
    int i;
    printf("Enter the number of disk I/O requests: ");
    scanf("%d", &numRequests);
    printf("Enter the initial head position: ");
    scanf("%d", &initialHeadPosition);
    printf("Enter the disk I/O requests:\n");
    for (i = 0; i < numRequests; i++) {
        printf("Request %d: ", i + 1);
        scanf("%d", &requests[i]);
    }
    calculateSeekTime(requests, numRequests, initialHeadPosition);

    return 0;
}
