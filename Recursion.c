#include <stdio.h>
#include <string.h>

#define max_n 10
#define maxLengthName 20

int n;
// n amount of people at the movie
int p;
// p amount of people who wont sit next to one another
char names[max_n][maxLengthName];
int popcorn[max_n];
int validOrderings;
int noPartnerSeat[max_n][max_n];

int permutationValid(int perm[]) {
    for (int i = 0; i < n; i++) {
        if (popcorn[perm[i]] == 0) {
            int left = (i > 0) ? perm[i - 1] : -1;
            int right = (i < n - 1) ? perm[i + 1] : -1;
            if (popcorn[left] == 0 && popcorn[right] == 0) {
                return 0;
            }
            if (noPartnerSeat[perm[i]][left] || noPartnerSeat[perm[i]][right]) {
                return 0;
                // seating violated
            }
            // popcorn  violated
        }
    
    }
    return 1;
}
// permutation check
void generatePermutations(int perm[], int used[], int k) {
    if (k == n) {
        if (permutationValid(perm)) {
            validOrderings++;
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (!used[i]) {
                used[i] = 1;
                perm[k] = i;
                generatePermutations(perm, used, k + 1);
                used[i] = 0;
            }
        }
    }
}
// recursive to show validity
int main(void) {
    scanf("%d %d", &n, &p);

    
    for (int i = 0; i < n; i++) {
        scanf("%s %d", names[i], &popcorn[i]);
    }
    // popcorn and name count
    memset(noPartnerSeat, 0, sizeof(noPartnerSeat));
    for (int i = 0; i < p; i++) {
        char name1[maxLengthName], name2[maxLengthName];
        scanf("%s %s", name1, name2);
        int idx1 = -1, idx2 = -1;
        for (int j = 0; j < n; j++) {
            if (strcmp(names[j], name1) == 0) idx1 = j;
            if (strcmp(names[j], name2) == 0) idx2 = j;
        }
        noPartnerSeat[idx1][idx2] = noPartnerSeat[idx2][idx1] = 1;
    }
// seating chart
    int perm[max_n];
    int used[max_n] = {0};
    validOrderings = 0;

    generatePermutations(perm, used, 0);

    printf("%d\n", validOrderings);

    return 0;
}
