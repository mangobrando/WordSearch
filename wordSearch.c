#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
void printPuzzle(char** arr);
void searchPuzzle(char** arr, char* word);
int bSize;
void printMap(int** arr);

int checkPath = 0; 	
int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
        return 2;
    }
    int i, j;
    FILE *fptr;

    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }
    fscanf(fptr, "%d\n", &bSize);
    char **block = (char**)malloc(bSize * sizeof(char*));
    char *word = (char*)malloc(20 * sizeof(char));
    for(i = 0; i < bSize; i++) {
        *(block + i) = (char*)malloc(bSize * sizeof(char));
        for (j = 0; j < bSize - 1; ++j) {
            fscanf(fptr, "%c ", *(block + i) + j);            
        }
        fscanf(fptr, "%c \n", *(block + i) + j);
    }
    fclose(fptr);

    printf("Enter the word to search: ");
    scanf("%s", word);
    printf("\nPrinting puzzle before search:\n");
    printPuzzle(block);
    searchPuzzle(block, word);
    
    return 0;
}

char Lower(char c)
{
    return (c | ' ');
}

void printPuzzle(char** arr) {
    for(int i = 0; i < bSize; i++){
        
        for(int j = 0; j < bSize; j++){

            printf("%c", (*(*(arr+i) + j)));
            printf(" ");
        }
        printf("\n");
    }
    printf("\n");
}

void printPath(int* indexes, char* word){ 

    
        checkPath++;
    int **arr = (int**)malloc(bSize * sizeof(int*));
	for(int i = 0; i < bSize; i++){
		*(arr+i) = (int *)malloc(bSize *sizeof(int));
		for(int j = 0 ; j < bSize; j++){
			*(*(arr+i) + j) = 0;
		}
	}

    for(int k = 0; k < strlen(word); k++){
        int i = *(indexes + k*2);
        int j = *(indexes + k*2 + 1);
        
        if(*(*(arr+i) + j) == 0){
            
            *(*(arr+i) + j) = k+1;
        }
        else{
            int temp = *(*(arr+i) + j);
          
            int count = 0;
            while(temp != 0){
                temp = temp/10;
                count++;
            }
            
            *(*(arr+i) + j) = (k+1)*(pow(10, count)) + *(*(arr+i) + j);
        }
    }

    for(int i = 0; i < bSize; i++){
    
    	for(int j = 0; j < bSize; j++){
    	
    		printf("%d", *(*(arr+i) + j));

            if(*(*(arr+i) + j) == 0 || *(*(arr+i) + j) / 10 == 0){
                printf("    ");
            }
            else{
                int temp = *(*(arr+i) + j);
                int count = 0;
                while(temp != 0){
                    temp = temp / 10;
                    count++;
                }

                for(int i = 0; i < (5 - count); i++){
                    printf(" ");
                }
            }
    	
    	}
    	
    	printf("\n");
    
    }
    
}

int* searchHelper(char** arr, char* word, int a, int b, int count, int* indexes, int indexSize){
    int wordSize = sizeof(word)/sizeof(char);
    if(checkPath == 0){
    if (count < strlen(word)){ 
        
        for(int i = -1; i < 2; i++){


            for(int j = -1; j < 2; j++){
                

                

                
                if(a + i >= 0 && b + j >= 0 && a + i < bSize && b + j < bSize){
                    if(abs(j) + abs(i) != 0){
                        if( Lower(*(*(arr + a + i) + (b + j))) == Lower(*(word+count))){
                            indexes[indexSize+1] = a + i;
                            indexes[indexSize+2] = b + j;
                            searchHelper(arr, word, a+i, j+b, count + 1, indexes, indexSize+2);
                        }


                    }
                
                }
                
                
                    

            }
        }

    }
    
    else if(count == strlen(word)){
        printf("Word Found!");
        printf("\n");
        
        printPath(indexes, word);
        return indexes;
    }

    
    }
}

void searchPuzzle(char** arr, char* word) { 
    bool test;
    int iVal[strlen(word)];
    int jVal[strlen(word)];

    for(int i = 0; i < bSize; i++){
       
        for(int j = 0; j < bSize; j++){
            

            if( Lower(*(*(arr + i ) + j)) == Lower(*(word+0))){ 
                int indexes[bSize*2];
                indexes[0] = i;
                indexes[1] = j;
                searchHelper(arr, word, i, j, 1, indexes, 1); 
                
                
            }
        }
    }

    if(checkPath == 0){
        printf("Word not found! \n");
    }

}


// puzzle1.txt HelLo//
// puzzle2.txt bAnANa//
// puzzle3.txt deTeR // 
// puzzle4.txt color // 