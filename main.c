
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#define MAX_SIZE 500


typedef struct data{
    char* name;
    int key;
}DATA;




int hash(char*meno){
    int len = strlen(meno);
    int h=0;
    for (int i = 0; i< len;i++){
        if(h>=500){
            h = h/500;
        }
        else{
            h = 31*h + meno[i];
        }
    }
    if(h>=500){
        h = h/500;
    }
    return h;

}



void insert(char** A,char*s){
    DATA* new;
    new = (DATA*)malloc(sizeof(DATA));
    new->name = s;
    new->key = hash(s);
    printf("%s %d\n",s,new->key);

}



int main(){



    char* POLE[MAX_SIZE];

    insert(&POLE,"Ctibor");
    insert(&POLE,"Patricia");
    insert(&POLE,"Matej");
    insert(&POLE,"Eliska");

    printf("Hello world\n");
}