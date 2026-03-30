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
int size = 10;
int maxValue = 10;
double seconds = 0.f;
clock_t start;

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

void printDiagram(int* arr, int a, int b){
	printf(CLEAR);
	clock_t step = clock();
	seconds = (double)(step - start)/CLOCKS_PER_SEC;
	printf("Steps: %d\t Swaps: %d\t Time: %.3f s\n", steps, swaps, seconds);
	for (int i = maxValue; i > 0; i--){
                for (int j = 0; j < size; j++){
			if(j == a || j == b){
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
    	sprintf(cmd, "pkill -9 ffplay > /dev/null 2>&1; ffplay -f lavfi -i \"sine=f=%d:d=0.05\" -nodisp -autoexit > /dev/null 2>&1 &", 400 + frequency * 60);
    	system(cmd);
}

int bubbleSort (int* arr){
	int finished = 1;
	for (int i = 0; i < size; i++){
		finished = 1;
		for (int j = 0; j < size-1; j++){
			playSound(arr[j+1]);
			usleep(50000);
			printDiagram(arr, j, j+1);
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

void quickSort(int *arr, int a, int b){
	steps++;
	if (a >= b){		
		return ;
	}
	int r = arr[a];
	int x = a-1;
	int y = b+1;
	while(x < y){
		do{
			x++;
		}while(arr[x] < r);
		
		do{
			y--;	
		}while(arr[y] > r);
		if( x < y){
			playSound(arr[x]);
			usleep(50000);
			swaps++;
			int temp = arr[x];
			arr[x] = arr[y];
			arr[y] = temp;
			printDiagram(arr, x, y);
		}
	}
	quickSort(arr, a, y);
	quickSort(arr, y+1, b);
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
		start = clock();
		printStartDiagram(arr);
		usleep(500000);
		bubbleSort(arr);
	
	}
	if (strcmp(argv[1], "--qs") == 0){
		srand(time(NULL));
		shuffle(arr);
		printf(CLEAR DELETE);
		start = clock();
		printStartDiagram(arr);
		usleep(500000);
		quickSort(arr, 0, size);
		resultPrint(arr);
	
	}
	return 0;
}


