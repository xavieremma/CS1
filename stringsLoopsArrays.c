#include <stdio.h>
#include <string.h>


int main(void) {
   
    char original[100001];
    char newMessage[100001];
    // arrays to store original and new message
    
    fgets(original, sizeof(original), stdin);
    // gets original message from user

    fgets(newMessage, sizeof(newMessage), stdin);
    // gets new message from user
    
    int originalCount[26] = {0};
    int newCount[26] = {0};
    // counts letters from each message (note: 26 = alphabet)

    for (int i = 0; original[i] != '\0'; i++) {
        if (original[i] >= 'A' && original[i] <= 'Z') {
            originalCount[original[i] - 'A']++;
        }
    }
    // number of letters in original message

    for (int i = 0; newMessage[i] != '\0'; i++) {
        if (newMessage[i] >= 'A' && newMessage[i] <= 'Z') {
            newCount[newMessage[i] - 'A']++;
        }
    }
    // number of letters in newMessage
    
    int newLetters_needed = 0;
   
    for (int i = 0; i < 26; i++) {
        if (newCount[i] > originalCount[i]) {
            newLetters_needed += (newCount[i] - originalCount[i]);
        }
    }
    // new letters needed
    
    printf("%d\n", newLetters_needed);

    return 0;
}

