#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    if (argc != 2) return 1;
    FILE* rawfile = fopen(argv[1],"r"); // function opening a file and return pointer
    if (rawfile == NULL) { // if not not open .. the return from the function is null
        return 2; // exit
    }
    FILE* photofile = NULL;
    unsigned char c[512];
    int count = 0;
    while(fread(c,512,1,rawfile)) { // fread: return next 512 bytes from the file - advance the pointer - copy the bytes to c
        if(c[0]==0xff && c[1]==0xd8 && c[2]== 0xff && (c[3]>=0xe0 &&c[3]<=0xef)){ // check first bytes
            // 1. il 7eta de btghz il name bs msh aktr ....
            // 1.1 de btsheel il string name nfso
            char name[15];
            // 1.2 de bt format el string w b3den bt7oto fel array
            sprintf(name, "%03d.jpg", count);
            if (photofile != NULL) {// if I am pointing to a file
                fclose(photofile);
            }
            photofile = fopen(name, "w");
            count++;
        }

        if (photofile != NULL) {
            fwrite(c, 512, 1, photofile);
        }
    }
    if (photofile != NULL)
        fclose(photofile);
    fclose(rawfile);
}