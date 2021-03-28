
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>
#define MAX_SIZE 500


typedef struct data{
    char* name;
    int key;
}DATA;

typedef struct table{
    DATA** datab;
    int size;
    int count;
}TABLE;




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

TABLE* create_table(int size) {
    // Creates a new HashTable
    TABLE* table = (TABLE*) malloc (sizeof(TABLE));
    table->size = size;
    table->count = 0;
    table->datab = (DATA**) calloc (table->size, sizeof(DATA*));
    for (int i=0; i<table->size; i++)
        table->datab[i] = NULL;

    return table;
}


int main(){
    create_table(500);


    insert(&POLE,"Ctibor");
    insert(&POLE,"Patricia");
    insert(&POLE,"Matej");
    insert(&POLE,"Eliska");

    printf("Hello world\n");
}