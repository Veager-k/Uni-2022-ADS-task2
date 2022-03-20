// stud id: 2110583
// This program splits n numbers into sets of 3,
// such that each set has the same sum
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>


int input(int* n, int **numbers, int* sum);
int findSet(int sum, int n, int *numbers, char usedNum[]);
int firstUnusedNum(int n, int *numbers, char usedNum[], char* allNumsTaken);

int main(){
    int n, sum = 0;
    int *numbers;

    if(input(&n, &numbers, &sum) == 0){
        return 0;
    }


    char *usedNum = (char*) calloc(sizeof(int), n);

    printf("-----------\n");

    if(findSet(sum, n, numbers, usedNum) == 0){
        printf("Failed to form the sets.\n");
    };
}

int findSet(int sum, int n, int *numbers, char usedNum[]){
    char allNumsTaken = 0;
    int num1 = firstUnusedNum(n, numbers, usedNum, &allNumsTaken);
    int num2;
    int num3;

    if(allNumsTaken){
        return 1; // all sets formed
    }

    for(int i = 0; i < n; ++i){ //searching for num2
        if(usedNum[i] == 0){
            usedNum[i] = 1;
            num2 = numbers[i];

            num3 = sum - num1 - num2; 
            for(int j = 0; j < n; ++j){ // searching for num3
                if(usedNum[j] == 0 && numbers[j] == num3){
                    usedNum[j] = 1;
                    int result = findSet(sum, n, numbers, usedNum);

                    if(result == 1){
                        printf("%d %d %d\n", num1, num2, num3);
                        return 1;
                    } else{
                        usedNum[i] = 0;
                        usedNum[j] = 0;
                        break;
                    }
                }
            }
            usedNum[i] = 0;
        }
    }
    return 0; //failed to find num2 and num3
}

int firstUnusedNum(int n, int *numbers, char usedNum[], char* allNumsTaken){
    for(int i = 0; i < n; ++i){
        if(usedNum[i] == 0){
            usedNum[i] = 1;
            return numbers[i];
        }
    }
    *allNumsTaken = 1;
    return 0;
}

int input(int* n, int **numbers, int* sum){
    printf("Input N.\n");
    scanf("%d", n);
    if(*n % 3 != 0){
        printf("N must be divisible by 3.\n");
        return 0;
    }

    int *inputs = (int*) malloc(sizeof(int)*(*n));

    for(int i = 0; i < *n;){
        char whiteSpace = 'a';
        int temp;
        while(!isspace(whiteSpace) && i < *n){
            scanf("%d", &temp);
            whiteSpace = getchar();
            *sum += temp;
            inputs[i] = temp;
            i++;
        }
    }

    if(*sum % (*n/3) != 0){
        printf("It is not possible to create 3 number sets with equal sums with the given numbers.");
        return 0;
    }
    *sum = *sum / (*n/3);

    *numbers = inputs;

    return 1;
}