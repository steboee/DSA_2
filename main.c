
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>


int celkovy_pocet;


typedef struct person{
    char* name;        //indentifikátor záznamu
    int age;
    struct person* left;
    struct person* right;
    int height;
}PERSON;



int height_of_tree(PERSON*A,int balance){
    int lh,rh;
    if(A==NULL)
        return(0);

    if(A->left==NULL)
        lh=0;
    else
        lh=1+A->left->height;

    if(A->right==NULL)
        rh=0;
    else
        rh=1+A->right->height;

    if(lh>rh)
        return(lh);

    return(rh);

}

int balance_factor(PERSON*A){
    int lh,rh;
    if(A==NULL)
        return(0);

    if(A->left==NULL)
        lh=0;
    else
        lh=1+A->left->height;

    if(A->right==NULL)
        rh=0;
    else
        rh=1+A->right->height;

    return(lh-rh);
}

int search(PERSON *A,char*data){
    if (A == NULL){
        return 0;
    }

    if (strcmp(data,A->name)==0){
        return 1;
    }

    if (strcmp(data,A->name)>0){
        search(A->right,data);
    }
    else if(strcmp(data,A->name)<0){
        search(A->left,data);
    }




}

PERSON* rotation_left(PERSON*A){
    PERSON *rot_tree;
    rot_tree = A->right;
    A->right = rot_tree->left;
    rot_tree->left = A;
    rot_tree->height = height_of_tree(rot_tree,0);
    A->height = height_of_tree(A,0);
    return rot_tree;
}

PERSON* rotation_right(PERSON *A){
    PERSON *rot_tree;
    rot_tree = A->left;
    A->left = rot_tree->right;
    rot_tree->right = A;
    rot_tree->height = height_of_tree(rot_tree,0);
    A->height = height_of_tree(A,0);
    return rot_tree;
}

PERSON* delete(PERSON*A,char*key){
    PERSON*temp;

    if (A == NULL){
        return NULL;
    }

    if(strcmp(key,A->name)>0){                      // idem doprava od node
        A->right = delete(A->right,key);            // rekurzia
        if (balance_factor(A) > 1){                 // za každým vnorením skontrolujem BF
            if(balance_factor(A->left) > 1){
                A = rotation_right(A);              //Rotácia LL
            }
            else{
                A->left = rotation_left(A->left);   //Rotácia LR
                A = rotation_right(A);
            }
        }
    }
    else if(strcmp(key,A->name)<0){                     // key je mensí než key v danom node , postupujem dolava

        A->left = delete(A->left,key);                  // reukurzivne volam funkciu delete ale už s ľavým child
        if (balance_factor(A) < -1){                     //
            if(balance_factor(A->right) < -1){
                A = rotation_left(A);               //Prípad RR
            }
            else{
                A->right = rotation_right(A->right);    //Prípad RL
                A = rotation_left(A);
            }
        }
    }


    else {                          // Našiel sa záznam ktorý chcem odtrániť                   // A - > node ktorý chcem odtrániť
        if(A->right!=NULL){

            temp=A->right;
            while(A->left!= NULL){
                temp=temp->left;
            }
            A->name=temp->name;
            A->age = temp->age;
            A->right=delete(A->right,temp->name);

            if(balance_factor(A)==2)
                if(balance_factor(A->left)>=0)
                    A = rotation_right(A);              //Rotácia LL
                else
                    A->left = rotation_left(A->left);   //Rotácia LR
                     A = rotation_right(A);
				}
        else{
            return(A->left);
        }

    A->height=height_of_tree(A,0);
    return(A);
    }
}

PERSON* make_new_node(char* data){
    PERSON* new = (PERSON*)malloc(sizeof(PERSON));
    new->name = data;
    new->left = NULL;
    new->right = NULL;
    new->height = 0;


    time_t seconds;             // náhodný generátor
    seconds = time(NULL);
    srand(seconds);
    new->age = (rand() % (99 + 1 - 1)) + 1;


    return new;


}

PERSON * insert(PERSON* A,char* data){


    if (A == NULL){            // úplne prvé dáta ...
        A = make_new_node(data);
        return A;
    }

    else{
        if(strcmp(data,A->name)>=0){               // postupujem doprava
            A->right = insert(A->right,data);       //pravé dieťa rootu. posielam do funkcie insert
            if (balance_factor(A) == -2){            // po rekurzii skontrolujem či je BF v rámci normyx
                if(strcmp(data,A->right->name)>0){
                    A = rotation_left(A);               // Prípad RR  -> rotácia vľavo
                }
                else{
                    A->right = rotation_right(A->right);    // Prípad RL
                    A = rotation_left(A);
                }

            }
        }
        else if(strcmp(data,A->name)<0){
            A->left = insert(A->left,data);
            if(balance_factor(A) == 2 ){
                if(strcmp(data,A->left->name)<0){
                    A = rotation_right(A);          //Prípad LL
                }
                else{
                    A->left = rotation_left(A->left);       //Prípad LR
                    A = rotation_right(A);
                }
            }
        }

    }
    A->height=height_of_tree(A,0);

    //printf("inserted string : %s\n",A->name);
    return A;
}

char *randstring(size_t length) {

    static char charset[] = "abcdefghijklmnopqrstuvwxyz";
    char *randomString = NULL;

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




char* gen_random(char **s, const int len) {
    static const char alphanum[] =     "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    char*a;
    a=s;

    for (int i = 0; i < len; ++i) {
        *(a+i) = alphanum[rand() % (sizeof(alphanum) - 1)];
    }

    *(a+len) = 0;
    return a;
}




int main() {

    PERSON* root=NULL;
    int i;
    celkovy_pocet = 10000000;
    clock_t start = clock();
    for (i = 0; i<10000000;i++){
        char*data;
        data = gen_random(&data,10);
        if (search(root,data)){
            celkovy_pocet--;
            continue;
        }
        else{
            root = insert(root,data);
        }


    }

    clock_t stop = clock();
    double elapsed = (double)(stop - start) * 1000.0 / CLOCKS_PER_SEC;
    printf("Time elapsed in ms: %f\n", elapsed);
    printf("N: %d\n",celkovy_pocet);
    printf("Height of tree: %d\n", root->height);











    return 0;
}
