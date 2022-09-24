#include <stdio.h>
#include <string.h>
#include <fstream>
using namespace std;


void rec2(int val, int count, int b, FILE *fp) {
    
    if (count <= 1) {
        int i;
        for (i = b - 1; i >= 0; i--) {
            //printf("%d", (val >> i) & 1);
            //write to file
            fprintf(fp, "%d", (val >> i) & 1);
        }
        //printf("\n");
        fprintf(fp, "\n");
    } else {
        
        rec2(val * 2, count - 1, b,fp);
        rec2(val * 2 + 1, count - 1, b, fp);
    }

    
}

void rec(int val, int count, FILE *fp) {
    rec2(val, count, count,fp);
}


int main(int argc, char **argv) {
   
   //-b means bits 
   //-n means number of bits
   //-o means output file

   //-h means help

   if(argc!=7 || strcmp(argv[1],"-h")){
    printf("Usage: ./main -b <number of bits> -n <num of locations> -o <output file>");
    return -1;
   }

   int bits = 0; int num = 0; char *output = NULL;
    for(int i=0; i<argc; i++){
        
        if(strcmp(argv[i],"-b")==0){
            bits = atoi(argv[i+1]);
        }
        else if(strcmp(argv[i],"-n")==0){
            num = atoi(argv[i+1]);
        }
        else if(strcmp(argv[i],"-o")==0){
            output = argv[i+1];
        }
        // else if(strcmp(argv[i],"-h")==0){
        //     printf("Usage: ./main -b <number of bits> -n <num of locations> -o <output file>");
        // }
    }

    if(bits==0 || num==0 || output==NULL){
        printf("Usage: ./main -b <number of bits> -n <num of locations> -o <output file>");
        return -1;
    }

    FILE *fp = fopen(output,"w");
    if(fp==NULL){
     printf("Error opening file %s",output);
        return -1;
    }
    
    rec(0,bits,fp);
    rec(1,bits,fp);

    fclose(fp);
 return 0;   
}
