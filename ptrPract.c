#include <stdio.h>
#include <stdlib.h>

int main()  {

    FILE *fPointer;
    fPointer = fopen("life.txt", "r");
    
    char singleLine[150];
    
    while(!feof(fPointer))  {
        fgets(singleLine, 150, fPointer);
        printf("%s", singleLine);
        singleLine[0] = '\0';
    
    }
    
    
    
    fclose(fPointer);
    
    return 0;


}
