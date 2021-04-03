
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
    struct person* data;
}TABLE;




TABLE* table;
int max=5;
int count = 0;






int hash(char*meno){
    int len = strlen(meno);
    int h=0;
    for (int i = 0; i< len;i++){
        h = (31*h + meno[i] ) % max ;
    }

    return h;

}


void init_table(){
    for (int i =0;i< max ;i++){
        (table+i)->data = NULL;
    }
}
int insert(PERSON*p){
    if (p == NULL){
        return 0;
    }
    int index = hash(p->name);
    p->next = table[index].data;
    table[index].data = p;
    count++;
    return 1;
}

void resize_table(){
    TABLE *temp = table;
    int old_max = max;
    count =0;
    max = max*2;


    table = (TABLE*)malloc(max*sizeof(TABLE));
    init_table();
    for (int i =0;i<old_max;i++){
        PERSON*a = (PERSON*) temp[i].data;
        if (a == NULL){
            continue;
        }
        else{
            while(a != NULL){
                PERSON*a_t;
                a_t = a->next;
                insert(a);
                a = a_t;
            }
        }
    }
    free(temp);
    temp = NULL;
}


int load_factor(){
    int bucket = max;
    int data = count;
    double alpha = (double)data/(double)bucket;
    if (alpha > 0.50){
        return 1;
    }
    return 0;
}





void print_table(){
    printf("Start\n");
    for (int i =0;i<max;i++){
        if (table[i].data == NULL){
            printf("\t%i\t---\n",i);
        }
        else{
            printf("\t%i\t ",i);
            PERSON *temp = table[i].data;
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
    data->next = NULL;
    return data;
}


int main(){
    table = malloc(max*sizeof(PERSON));
    init_table();
    print_table();
    PERSON *u;
    for (int i =0;i<10;i++){
        u = create_data(i);
        insert(u);
        if(load_factor()){
            print_table();
            printf("RESIZE\n");
            resize_table();
            print_table();
        }
    }

    print_table();
}