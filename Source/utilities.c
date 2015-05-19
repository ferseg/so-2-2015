#include "../Headers/utilities.h"


int getRandomNumber(int pMinNum, int pMaxNum){
	srand ( time(NULL) );
    return (rand() % (pMaxNum - pMinNum + 1)) + pMinNum;
}

void clearString(char *str, int len) {
	str = malloc(sizeof(char)*len);
	while(--len > -1) {
		str[len] = 0;
	}
}