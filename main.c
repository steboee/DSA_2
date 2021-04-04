
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>



typedef struct person{
    char*name;
    int age;
    struct person* next;
}PERSON;


typedef struct table{
    struct person* data;
}TABLE;



TABLE* table;
int max=100;                   // počitočná veľkosť hashovacej tabulky
int count = 0;                  // počítadlo koľko prvkov už je v tabulke
int count_resize =0;            // pocitadlo kolkokrat sa velkost tabulky zvacsovala



int hash(char*meno){                // hash funckia , dostane string --> vráti index
    int len = (int)strlen(meno);
    int h=0;
    for (int i = 0; i< len;i++){      // prejde celým stringom
        h = (31*h + meno[i] ) % max ;
    }

    return h;

}

void init_table(){                  // funkcia inicializuje hashovaciu tabuľku a nastaví všetko na NULL
    for (int i =0;i< max ;i++){
        (table+i)->data = NULL;
    }
}

int insert(PERSON*p){           // funkcia na vkladanie dát do hashovacej tabulky, vstupom je dátová štruktúra PERSON
    if (p == NULL){
        return 0;
    }
    int index = hash(p->name);      // podľa stringu sa vygeneruje index
    p->next = table[index].data;      // každý bucket ma vlastný LINK-LIST, a pri kolízií nové dáta uložím na prvé miesto v link-liste a ostatné posuniem
    table[index].data = p;
    count++;                    // globalna premenná určuje naplnenosť tabulky
    return 1;
}

void resize_table(){                    // Funkcia mení veľkosť hashovacej tabulky,
    count_resize++;                     // počítadlo koľkokrát tabuľka menila velkost
    TABLE *temp = table;                // temp reprezentuje starú tabulku
    int old_max = max;                  // old_max reprezentuje starú veľkosť tabulky
    count =0;                           // nastavím globálnu premennú počítadla prvkov v tabulke na 0
    max = max*2;                        // doterajsiu velkost tabulky zvacsím 2 - naśobne


    table = (TABLE*)malloc(max*sizeof(TABLE));          // alokujem novú tabulku s 2-nasobnou velkostou
    init_table();                                       // novu tabulku inicializujem
    for (int i =0;i<old_max;i++){                       // musim prejsť každý bucket v starej hashovacej tabulke a prehashovať ich do novej
        PERSON*a = (PERSON*) temp[i].data;
        if (a == NULL){
            continue;
        }
        else{
            while(a != NULL){                           // Prípad ked mám v buckete link list s najmenej 2 dátami
                PERSON*a_t;                             // nasledujúce dáta v link liste
                a_t = a->next;
                insert(a);                              // do novej tabulky insertnem dáta zo starej tabulky
                a = a_t;                                // dalšie dáta z link listu ktoré by sa po zavolani insert(a) v predoslom riadku stratili, preto nové a -> reprezentuje dalše dáta
            }
        }
    }
    free(temp);                                         // uvolním celú predošlu tabulku
    temp = NULL;
}

int load_factor(){                              // funkcia počíta load factor a pri určitej hodnote returne 1 čím sa velkost tabulky zvacsí
    int bucket = max;                           // počet bucketov celkovo
    int data = count;                           // pocet dát v tabulke
    double alpha = (double)data/(double)bucket;
    if (alpha > 0.50){                              // ak je tabulka z polovice naplnená dátami tak zvaČší velkost
        return 1;
    }
    return 0;
}

void print_table(){                                     // pomocná funkcia , inšpirovaná githubom/stackoverflow ,
    printf("Start\n");                                  // použival som ju na vizualizáciu hashovacej tabulky a dokázala aj ukázať kolízie čiže aj dáta v link liste
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

char *randstring(size_t length,int x) {                                 // Funkcia ktorá generuje náhodné stringy, používam ju v každej implementácií aby boli výsledky viac relevantné

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

PERSON * create_data(int i){                                        // funkcia vytvorí nové dáta a meno je na základe funkcie na random generáciu stringu
    PERSON *data = malloc(sizeof(PERSON));
    data->name = randstring(5,i);
    data->age = 20;                                                // vek som nemenil randomne aby sa program zbytočne nezatažoval..
    data->next = NULL;
    return data;
}

PERSON* search(char*name){                      // FUNKCIA na hladanie dát v hashovacej tabulke, ak najde prvok tak vŕati celú štruktúru
    int h = hash(name);                         // podla mena najde index v tabulke
    while (table[h].data != NULL){              // v pripade že tam bude aj link list , pokracuj az kym data na danom indexe v tabulke niesu NULL
        if (strcmp(table[h].data->name,name)==0){       // ak sa rovná meno tak sa nasli dané dáta
            return table[h].data;
        }
        table[h].data = table[h].data->next;    // posun sa v link liste dalej
    }
    return NULL;
}

void delete_table(){                                    // funkcia vymaže celú hashovaciu tabulku a dealokuje všetky alokácie
    int i = 0;
    for (i = 0; i < max; i++)                           // opakuj tolkokrát aká velka je tabulka
    {
        TABLE temp = table[i];                          // pomocná premenná temp ktorá ukladá "bucket"
        PERSON* first = temp.data;                      // premenná first ma v sebe dáta z bucketu
        if (first != NULL)                              // ak nieje prázdny bucket tak ->
        {
            while (first->next != NULL)                 // pokiaľ sú dalsie dáta v link liste -> tak
            {
                PERSON* old = first;                    // pomocná premenná ktorú uvolním
                first = first->next;                    // posuniem sa dalej v link liste
                free(old);
            }
            free(first);                                // ak už nieje další zaznam v link liste a mám posledný , uvolním ho
            first = NULL;
        }

        temp.data = NULL;
    }
    free(table);                                        // nakoniec uvolnim celu tabulku
    table = NULL;
}



/* TESTOVANIE SOM ZAHRNOL DO FUNKCIE MAIN*/


int main(){
    int items = 2000000;                                // pocet dát ktoré chcem vložiť do hashovacej tabulky
    table = malloc(max*sizeof(PERSON));                 // alokujem prvotnú hashovaciu tabulku o velkosti max ( globalńa premenná ) riadok 23
    init_table();                                       // inicializujem tabulku ( nastavim všetky buckety na NULL
    PERSON *u;
    double elapsed=0;

    for (int i =0;i<items;i++){                         // TESTOVAC , vkladá (items) dát do tabulky
        u = create_data(i);                             // za kazdým sa vytvoria nahodné dáta
        clock_t start = clock();
        insert(u);                                      // vkladanie do tabulky
        if(load_factor()){                              // za kazdym vlozenim program skotnroluje load factor
            resize_table();                             // ak je potrebné tak sa tabulka zvačší
        }
        clock_t stop = clock();
        elapsed = elapsed + (double)(stop - start) *1000.0/ (double)CLOCKS_PER_SEC;
    }


    printf("INSERTED %d data\n",items);
    printf("Time elapsed : %.f ms\n", elapsed);
    printf("Number of resizes : %d\n",count_resize);
    int searched_items=0;
    double elapsed2=0;


    for (int i =0;i<items;i++){                         // TESTOVAC , vkladá (items) dát do tabulky
        u = create_data(i);
        clock_t start = clock();
        if(search(u->name)){
            searched_items++;
        }
        clock_t stop = clock();
        elapsed2 = elapsed2 + (double)(stop - start) *1000.0/ (double)CLOCKS_PER_SEC;
    }


    printf("SEARCHED FOR %d random data\n",items);
    printf("Time elapsed : %.f ms\n", elapsed2);
    printf("Number of data found : %d\n",searched_items);

    delete_table();

    return 0;

}