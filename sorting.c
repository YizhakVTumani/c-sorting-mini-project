#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define GREEN "\033[32m"
#define RESET "\033[0m"
#define CLEAR "\033[H"
#define DELETE "\033[J"
int steps = 0;
int swaps = 0;
int size = 50;
int maxValue = 10;

void shuffle (int* arr){
	for (int i = 0; i < size; i++){
                arr[i] = rand() % maxValue;
                printf("%d\t", arr[i]);
        }
	printf("\n");
}

void resultPrint(int* arr){
	printf("\n");
        for(int i = 0; i < size; i++){
                printf("%d\t", arr[i]); 
        }
	printf("\n");
}

void printDiagram(int* arr, int a){
	printf(CLEAR);
	printf("Steps: %d\t Swaps: %d\n", steps, swaps);
	for (int i = maxValue; i > 0; i--){
                for (int j = 0; j < size; j++){
			if(j == a || j == a+1){
				if(i <= arr[j]){
                                        printf(GREEN "\u2588" RESET);
                                }
                                else{
                                         printf(" ");
                                }

			}
			else{
                        	if(i <= arr[j]){
                               		printf("\u2588");
                        	}	
                        	else{
                               		 printf(" ");
                        	}
			}
                }
                printf("\n");
        }
	fflush(stdout);
	usleep(150000);
}

void playSound(int frequency){
	char cmd[150];
    	sprintf(cmd, "ffplay -f lavfi -i \"sine=f=%d:d=0.05\" -nodisp -autoexit > /dev/null 2>&1 &", 300 + frequency * 100);
    	system(cmd);
}

int bubbleSort (int* arr){
	int finished = 1;
	for (int i = 0; i < size; i++){
		finished = 1;
		for (int j = 0; j < size-1; j++){
			playSound(arr[j+1]);
			usleep(20000);
			printDiagram(arr, j);
			steps++;
			if (arr[j] > arr[j+1]){
				swaps++;
				finished = 0;
				int temp = arr[j];
				arr[j] = arr[j+1];
				arr[j+1] = temp;
			}
		}
		if(finished == 1){
			resultPrint(arr);
			return -1;
		}	
	}
	resultPrint(arr);
}

void printStartDiagram(int* arr){
	for (int i = maxValue; i > 0; i--){
		for (int j = 0; j < size; j++){
			if(i <= arr[j]){
				printf("\u2588");
			}
			else{
				printf(" ");
			}
		}
		printf("\n");
	}
}



int main(int argc, char *argv[]){
	int steps = 0;
	size = atoi(argv[2]);
	int arr[size];
	if (strcmp(argv[1], "--bl") == 0){
		srand(time(NULL));
		shuffle(arr);
		printf(CLEAR DELETE);
		printStartDiagram(arr);
		usleep(500000);
		bubbleSort(arr);
	
	}
	return 0;
}


