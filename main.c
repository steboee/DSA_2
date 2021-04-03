
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#define MAX_SIZE 100


typedef struct person{
    char*name;
    int age;
    struct person* next;
}PERSON;


typedef struct table{
    int size;
    int count;
    struct person** data;
}TABLE;


int size;
int max;
int count;





int hash(char*meno){
    int len = strlen(meno);
    int h=0;
    for (int i = 0; i< len;i++){
        h = (31*h + meno[i] ) % MAX_SIZE ;
    }


    return h;

}


void init_table(PERSON**table,TABLE*start){
    for (int i =0;i< start->size ;i++){
        table[i] = NULL;
    }
}

void resize_table(TABLE**old_tab,PERSON**old_pers){
    TABLE*new_tab;
    PERSON* new_pers [(*old_tab)->size*2];
    new_tab = malloc(sizeof(TABLE));
    new_tab->size = (*old_tab)->size*2;
    new_tab->count =0;
    new_tab->data = new_pers;
    init_table(new_pers,new_tab);
    old_tab =  &new_tab;
    old_pers =  new_pers;

}


int load_factor(TABLE*a,PERSON*b){
    int bucket = a->size;
    int data = a->count;
    double alpha = (double)data/(double)bucket;
    if (alpha > 0.50){
        return 1;
    }
    return 0;
}


int insert(PERSON *p,TABLE*start,PERSON**table){
    if (p == NULL){
        return 0;
    }
    int index = hash(p->name);
    p->next = table[index];
    table[index] = p;
    start->count++;

    return 1;
}


void print_table(PERSON **table){
    printf("Start\n");
    for (int i =0;i<MAX_SIZE;i++){
        if (table[i] == NULL){
            printf("\t%i\t---\n",i);
        }
        else{
            printf("\t%i\t ",i);
            PERSON *temp = table[i];
            while (temp != NULL){
                printf("%s - ",temp->name);
                temp = temp->next;
            }
            printf("\n");
        }

    }
    printf("END\n");
}

char *randstring(size_t length,int x) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyz";
    char *randomString = NULL;
    time_t seconds;
    seconds = time(NULL);
    srand(x*seconds);
    if (length) {
        randomString = malloc(sizeof(char) * (length +1));
        if (randomString) {
            for (int n = 0;n < length;n++) {
                int key = rand() % (int)(sizeof(charset) -1);
                randomString[n] = charset[key];
            }
            randomString[length] = '\0';
        }
    }
    return randomString;
}


PERSON * create_data(int i){
    PERSON *data = malloc(sizeof(PERSON));
    data->name = randstring(10,i);
    data->age = 20;
    return data;
}


int main(){
    TABLE *start = malloc(sizeof(TABLE));
    PERSON* s;
    s = (PERSON*)malloc(100*sizeof(PERSON));
    start->size = 100;
    start->count =0;
    start->data = &s;
    init_table(s,start);
    print_table(s);

    PERSON *u;
    for (int i =0;i<60;i++){
        u = create_data(i);
        insert(u, start, (PERSON **) &s);
        if(load_factor(start, s)){
            resize_table(&start,(PERSON **) &s);
        }
    }

    print_table(s);
}