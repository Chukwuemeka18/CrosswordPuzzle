#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// DO NOT INCLUDE OTHER LIBRARY!

// Declarations of the two functions you will implement
// Feel free to declare any helper functions
void printPuzzle(char** arr, int n);
void searchPuzzle(char** arr, int n, char** list, int listSize);
void lowercasePuzzle(char** arr, char* list, int a);

// Main function, DO NOT MODIFY!!!	
int main(int argc, char **argv) {
    int bSize = 15;
	if (argc != 2) {
		fprintf(stderr, "Usage: %s <puzzle file name>\n", argv[0]);
		return 2;
	}
    int i, j;
    FILE *fptr;
    char **block = (char**)malloc(bSize * sizeof(char*));
	char **words = (char**)malloc(50 * sizeof(char*));

    // Open file for reading puzzle
    fptr = fopen(argv[1], "r");
    if (fptr == NULL) {
        printf("Cannot Open Puzzle File!\n");
        return 0;
    }

	// Read puzzle block into 2D arrays
    for(i=0; i<bSize; i++){
        *(block+i) = (char*)malloc(bSize * sizeof(char));

        fscanf(fptr, "%c %c %c %c %c %c %c %c %c %c %c %c %c %c %c\n", *(block+i), *(block+i)+1, *(block+i)+2, *(block+i)+3, *(block+i)+4, *(block+i)+5, *(block+i)+6, *(block+i)+7, *(block+i)+8, *(block+i)+9, *(block+i)+10, *(block+i)+11, *(block+i)+12, *(block+i)+13, *(block+i)+14 );
    }
	fclose(fptr);

	// Open file for reading word list
	fptr = fopen("states.txt", "r");
	if (fptr == NULL) {
        printf("Cannot Open Words File!\n");
        return 0;
    }
	
	// Save words into arrays
	for(i=0; i<50; i++){
		*(words+i) = (char*)malloc(20 * sizeof(char));
		fgets(*(words+i), 20, fptr);		
	}
	
	// Remove newline characters from each word (except for the last word)
	for(i=0; i<49; i++){
		*(*(words+i) + strlen(*(words+i))-2) = '\0';	
	}
	
	// Print out word list
	printf("Printing list of words:\n");
	for(i=0; i<50; i++){
		printf("%s\n", *(words + i));		
	}
	printf("\n");
	
	// Print out original puzzle grid
    printf("Printing puzzle before search:\n");
    printPuzzle(block, bSize);
	printf("\n");

	// Call searchPuzzle to find all words in the puzzle
	searchPuzzle(block, bSize, words, 50);
	printf("\n");
	
	// Print out final puzzle grid with found words in lower case
    printf("Printing puzzle after search:\n");
    printPuzzle(block, bSize);
	printf("\n");
	
    return 0;
}











void printPuzzle(char** arr, int n){
	// This function will print out the complete puzzle grid (arr). It must produce the output in the SAME format as the samples in the instructions.
	// Your implementation here 
 
   for (int i = 0; i < n; i++){
        for (int j = 0; j < n; j++){
            printf("%c ", *(*(arr + i) + j));
        }
   
        printf("\n");
    }



}














void searchPuzzle(char** arr, int n, char** list, int listSize){
	// This function checks if arr contains words from list. If a word appears in arr, it will print out that word and then convert that word entry in arr into lower case.
	// Your implementation here
    

//Note to self always debug yor code touyrself line by line with detail on a piece of papaer
  
   for(int e = 0; e < listSize; e++){ 
        for(int f = 0; f < strlen(*(list+e)); f++){
           if(*(*(list + e) + f) >= 'a' &&  *(*(list + e) + f) <= 'z' ){
              *(*(list + e) + f) = *(*(list + e) + f) - ('a' - 'A');
            }
        }
    }  //9
    


    char **block2 = (char**)malloc(n * sizeof(char*));

    for(int i=0; i<n; i++){
       *(block2+i) = (char*)malloc(n * sizeof(char));
        for(int j=0; j<n; j++){
           *(*(block2+i)+j) = *(*(arr+i)+j);
        }
    }


//--------------------------------------------------------------------------------------------------------------------------------



    //vertical down
     int k = 0;
    for(int a = 0; a < listSize; a++){
       for(int b = 0; b < n; b++){
          for(int c = 0; c < n; c++){
               int y = b, z = c;
               if(*(*(list + a) + k) >= 'a' &&  *(*(list + a) + k) <= 'z' ){
                   *(*(list + a) + k) = *(*(list + a) + k) - ('a' - 'A');
                }
               
              if( *(*(list + a) + k) == *(*(arr + c) + b) ){
                 k++;
              }
              else if( *(*(list + a) + k) != *(*(arr + c) + b) ){
                 k = 0;
                 
               }
              if ( k == (strlen(*(list+a))-1) ){
                  printf("Found: ");
                  for(int l = 0; l < strlen(*(list+a)); l++){
                       if( l != 0  &&*(*(list + a) + l) >= 'A' &&  *(*(list + a) + l) <= 'Z' ){
                        *(*(list + a) + l) = *(*(list + a) + l) + ('a' - 'A');
                      }
                       printf("%c", *(*(list + a) + l));
                       //printf("\n");
                  }
                  printf("\n");
                  k = 0;
                  for(int h=0; h<strlen(*(list+a)); h++){
                      if ((z-h+1) < 0){
                         break;
                       }
                     //if( *(*(block2+((z+y)-h+1))+(z-h+1)) >= 'A' &&  *(*(block2+((z+y)-h+1))+(z-h+1)) <= 'Z' ){
                          *(*(block2+(z-h+1))+y) = *(*(block2+(z-h+1))+y) + ('a'-'A');
                       //}
                   }
 
              }
           }
       }

    }  
   

   //vertical up
   int m = 0;
    for(int a = 0; a < listSize; a++){
       for(int b = n-1; b < n-1; b--){
          for(int c = n-1; c < n-1; c--){
               int y = b, z = c;
               if(*(*(list + a) + m) >= 'a' &&  *(*(list + a) + m) <= 'z' ){
                   *(*(list + a) + m) = *(*(list + a) + m) - ('a' - 'A');
                }
               
              if( *(*(list + a) + m) == *(*(arr + b) + c) ){
                 m++;
              }
              else if( *(*(list + a) + m) != *(*(arr + b) + c) ){
                 m = 0;
                 
               }
              if ( m == (strlen(*(list+a))-1) ){
                  printf("Found: ");
                  for(int l = 0; l < strlen(*(list+a)); l++){
                       if( l != 0  &&*(*(list + a) + l) >= 'A' &&  *(*(list + a) + l) <= 'Z' ){
                        *(*(list + a) + l) = *(*(list + a) + l) + ('a' - 'A');
                      }
                       printf("%c", *(*(list + a) + l));
                       //printf("\n");
                  }
                  printf("\n");
                  m = 0;
                  for(int h=0; h<strlen(*(list+a)); h++){
                      if ((z+h-1) >= n){
                         break;
                       }
                     //if( *(*(block2+((z+y)-h+1))+(z-h+1)) >= 'A' &&  *(*(block2+((z+y)-h+1))+(z-h+1)) <= 'Z' ){
                          *(*(block2+(z+h-1))+y) = *(*(block2+(z+h-1))+y) + ('a'-'A');
                       //}
                   }
              }
           }
       }

    }  
    

//----------------------------------------------------------------------------------------------------------------------------
 
   //horizontal right
   int q = 0;
    for(int a = 0; a < listSize; a++){
       for(int b = 0; b < n; b++){
          for(int c = 0; c < n; c++){
               int y = b, z = c;
               if(*(*(list + a) + q) >= 'a' &&  *(*(list + a) + q) <= 'z' ){
                   *(*(list + a) + q) = *(*(list + a) + q) - ('a' - 'A');
                }
               
              if( *(*(list + a) + q) == *(*(arr + b) + c) ){
                 q++;
              }
              else if( *(*(list + a) + q) != *(*(arr + b) + c) ){
                 q = 0;
                 
               }
              if ( q == (strlen(*(list+a))-1) ){
                  printf("Found: ");
                  for(int l = 0; l < strlen(*(list+a)); l++){
                       if( l != 0  &&*(*(list + a) + l) >= 'A' &&  *(*(list + a) + l) <= 'Z' ){
                        *(*(list + a) + l) = *(*(list + a) + l) + ('a' - 'A');
                      }
                       printf("%c", *(*(list + a) + l));
                       //printf("\n");
                  }
                  printf("\n");
                  q = 0;
                  for(int h=0; h<strlen(*(list+a)); h++){
                      if ((z-h+1) < 0){
                         break;
                       }
                     //if( *(*(block2+((z+y)-h+1))+(z-h+1)) >= 'A' &&  *(*(block2+((z+y)-h+1))+(z-h+1)) <= 'Z' ){
                          *(*(block2+y)+(z-h+1)) = *(*(block2+y)+(z-h+1)) + ('a'-'A');
                       //}
                   }
              }
           }
       }

    }  

    //horizontal left
   int p = 0;
    for(int a = 0; a < listSize; a++){
       for(int b = n-1; b > -1; b--){
          for(int c = n-1; c > -1; c--){
               int y = b, z = c;
               if(*(*(list + a) + p) >= 'a' &&  *(*(list + a) + p) <= 'z' ){
                   *(*(list + a) + p) = *(*(list + a) + p) - ('a' - 'A');
                }
               
              if( *(*(list + a) + p) == *(*(arr + b) + c) ){
                 p++;
              }
              else if( *(*(list + a) + p) != *(*(arr + b) + c) ){
                 p = 0;
                 
               }
              if ( p == (strlen(*(list+a))-1) ){
                  printf("Found: ");
                  for(int l = 0; l < strlen(*(list+a)); l++){
                       if( l != 0  &&*(*(list + a) + l) >= 'A' &&  *(*(list + a) + l) <= 'Z' ){
                        *(*(list + a) + l) = *(*(list + a) + l) + ('a' - 'A');
                      }
                       printf("%c", *(*(list + a) + l));
                       //printf("\n");
                  }
                  printf("\n");
                  p = 0;
                  for(int h=0; h<strlen(*(list+a)); h++){
                      if ((z+h-1) >= n){
                         break;
                       }
                     //if( *(*(block2+((z+y)-h+1))+(z-h+1)) >= 'A' &&  *(*(block2+((z+y)-h+1))+(z-h+1)) <= 'Z' ){
                          *(*(block2+y)+(z+h-1)) = *(*(block2+y)+(z+h-1)) + ('a'-'A');
                       //}
                   }
              }
           }
       }

    } 

 

//-----------------------------------------------------------------------------------------------------------------------------------------

 //right diagonal line pointing down MOVING TO THE SOUTH
   int t = 0;
    for(int a = 0; a < listSize; a++){
       for(int b = 0; b < n; b++){
          for(int c = 0; c < n; c++){
               int y = b, z = c;
               if((c + b) >=n){
               break;
             }

               if(*(*(list + a) + t) >= 'a' &&  *(*(list + a) + t) <= 'z' ){
                   *(*(list + a) + t) = *(*(list + a) + t) - ('a' - 'A');
                }
               
              if( *(*(list + a) + t) == *(*(arr + (c + b)) + c) ){
                 t++;
              }
              else if( *(*(list + a) + t) != *(*(arr + (c + b)) + c) ){
                 t = 0;
                 
               }
              if ( t == (strlen(*(list+a))-1) ){
                  printf("Found: ");
                  for(int l = 0; l < strlen(*(list+a)); l++){
                       if( l != 0  &&*(*(list + a) + l) >= 'A' &&  *(*(list + a) + l) <= 'Z' ){
                        *(*(list + a) + l) = *(*(list + a) + l) + ('a' - 'A');
                      }
                       printf("%c", *(*(list + a) + l));
                       //printf("\n");
                  }
                  printf("\n");
                  t = 0;
                  for(int h=0; h<strlen(*(list+a)); h++){
                      if (((z+y)-h+1) < 0){
                         break;
                       }
                       if( *(*(block2+((z+y)-h+1))+(z-h+1)) >= 'A' &&  *(*(block2+((z+y)-h+1))+(z-h+1)) <= 'Z' ){
                          *(*(block2+((z+y)-h+1))+(z-h+1)) = *(*(block2+((z+y)-h+1))+(z-h+1)) + ('a'-'A');
                       }
                   }
              }
           }
       }

    } 


    //left diagonal line pointing up MOVING TO THE NORTH
    int s = 0;
    for(int a = 0; a < listSize; a++){
       for(int b = 0; b < n; b++){
          for(int c = n-1; c > -1; c--){
               int y = b, z = c;
               if((c - b) <0){
               break;
             }

               if(*(*(list + a) + s) >= 'a' &&  *(*(list + a) + s) <= 'z' ){
                   *(*(list + a) + s) = *(*(list + a) + s) - ('a' - 'A');
                }
               
              if( *(*(list + a) + s) == *(*(arr + (c - b)) + c) ){
                 s++;
              }
              else if( *(*(list + a) + s) != *(*(arr + (c - b)) + c) ){
                 s = 0;
                 
               }
              if ( s == (strlen(*(list+a))-1) ){
                  printf("Found: ");
                  for(int l = 0; l < strlen(*(list+a)); l++){
                       if( l != 0  &&*(*(list + a) + l) >= 'A' &&  *(*(list + a) + l) <= 'Z' ){
                        *(*(list + a) + l) = *(*(list + a) + l) + ('a' - 'A');
                      }
                       printf("%c", *(*(list + a) + l));
                       //printf("\n");
                  }
                  printf("\n");
                  s = 0;
                  for(int h=0; h<strlen(*(list+a)); h++){
                      if (((z-y)+h-1) >= n){
                         break;
                       }
                       if( *(*(block2+((z-y)+h-1))+(z+h-1)) >= 'A' &&  *(*(block2+((z-y)+h-1))+(z+h-1)) <= 'Z' ){
                          *(*(block2+((z-y)+h-1))+(z+h-1)) = *(*(block2+((z-y)+h-1))+(z+h-1)) + ('a'-'A');
                       }
                   }
              }
           }
       }

    } 

    
    


//-------------------------------------------------------------------------------------------------------------------------------------------

 //right diagonal line pointing down MOVING TO THE EAST
   int u = 0;
    for(int a = 0; a < listSize; a++){
       for(int b = 0; b < n; b++){
          for(int c = 0; c < n; c++){
               int y = b, z = c;
               if((c + b) >=n){
               break;
             }

               if(*(*(list + a) + u) >= 'a' &&  *(*(list + a) + u) <= 'z' ){
                   *(*(list + a) + u) = *(*(list + a) + u) - ('a' - 'A');
                }
               
              if( *(*(list + a) + u) == *(*(arr + c) + (c + b)) ){
                 u++;
              }
              else if( *(*(list + a) + u) != *(*(arr + c) + (c + b)) ){
                 u = 0;
                 
               }
              if ( u == (strlen(*(list+a))-1) ){
                  printf("Found: ");
                  for(int l = 0; l < strlen(*(list+a)); l++){
                       if( l != 0  &&*(*(list + a) + l) >= 'A' &&  *(*(list + a) + l) <= 'Z' ){
                        *(*(list + a) + l) = *(*(list + a) + l) + ('a' - 'A');
                      }
                       printf("%c", *(*(list + a) + l));
                       //printf("\n");
                  }
                  printf("\n");
                  u = 0;
                  for(int h=0; h<strlen(*(list+a)); h++){
                      if (((z+y)-h+1) < 0){
                         break;
                       }
                       if( *(*(block2+(z-h+1))+((z+y)-h+1)) >= 'A' &&  *(*(block2+(z-h+1))+((z+y)-h+1)) <= 'Z' ){
                          *(*(block2+(z-h+1))+((z+y)-h+1)) = *(*(block2+(z-h+1))+((z+y)-h+1)) + ('a'-'A'); 
                       }
                   }
              }
           }
       }

    } 


    //left diagonal line pointing up MOVING TO THE WEST
    int v = 0;
    for(int a = 0; a < listSize; a++){
       for(int b = 0; b < n; b++){
          for(int c = n-1; c > -1; c--){
               int y = b, z = c;
               if((c - b) < 0){
               break;
             }

               if(*(*(list + a) + v) >= 'a' &&  *(*(list + a) + v) <= 'z' ){
                   *(*(list + a) + v) = *(*(list + a) + v) - ('a' - 'A');
                }
               
              if( *(*(list + a) + v) == *(*(arr + c) + (c - b)) ){
                 v++;
              }
              else if( *(*(list + a) + v) != *(*(arr + c) + (c - b)) ){
                 v = 0;
                 
               }
              if ( v == (strlen(*(list+a))-1) ){
                  printf("Found: ");
                  for(int l = 0; l < strlen(*(list+a)); l++){
                       if( l != 0  &&*(*(list + a) + l) >= 'A' &&  *(*(list + a) + l) <= 'Z' ){
                        *(*(list + a) + l) = *(*(list + a) + l) + ('a' - 'A');
                      }
                       printf("%c", *(*(list + a) + l));
                       //printf("\n");
                  }
                  printf("\n");
                  v = 0;
                  for(int h=0; h<strlen(*(list+a)); h++){
                      if (((z-y)+h-1) >= n){
                         break;
                       }
                       if( *(*(block2+(z+h-1))+((z-y)+h-1)) >= 'A' &&  *(*(block2+(z+h-1))+((z-y)+h-1)) <= 'Z' ){
                          *(*(block2+(z+h-1))+((z-y)+h-1)) = *(*(block2+(z+h-1))+((z-y)+h-1)) + ('a'-'A'); 
                       }
                   }
              }
           }
       }

    } 


//-----------------------------------------------------------------------------------------------------------------------------
   for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
           *(*(arr+i)+j) = *(*(block2+i)+j);
        }
    }
}

//Remeber to debug your code throghly with a piece of paper step by step, use comments for degug, rest so you can code better later, use print staments to debug, poniters parametrs are poniters, use else if, do the algortim the human way first, algorthim simple then more thought out