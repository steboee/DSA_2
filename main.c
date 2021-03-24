
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>



typedef struct person{
    char* name;        //indentifikátor záznamu
    int age;
    struct person* left;
    struct person* right;
    int height
}PERSON;

int max(int a, int b){
    if (a > b){
        return a;
    }
    return b;
}

int height_of_tree(PERSON*A,int balance){
    int left_sub_tree=0;
    int right_sub_tree=0;
    if (A == NULL){
        return 0;
    }

    if(A->right == NULL){               //na pravo už niesu žiadne deti
        right_sub_tree = 0;
    }
    if(A->left == NULL){                //na ľavo už niesu žiadne deti
        left_sub_tree = 0;
    }



    if(A->right != NULL){
        right_sub_tree = 1 + A->right->height;
    }
    if(A->left != NULL){
        left_sub_tree = 1 + A->left->height;
    }


    if (balance == 1){
        return (left_sub_tree - right_sub_tree);
    }

    return max(right_sub_tree,left_sub_tree);

}


int balance_factor(PERSON*A){
    return height_of_tree(A,1);
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
    A->height = height_of_tree(A,0);
    rot_tree->height = height_of_tree(rot_tree,0);
    return rot_tree;
}

PERSON* rotation_right(PERSON *A){
    PERSON *rot_tree;
    rot_tree = A->left;
    A->left = rot_tree->right;
    rot_tree->right = A;
    A->height = height_of_tree(A,0);
    rot_tree->height = height_of_tree(rot_tree,0);
    return rot_tree;
}




PERSON* delete(PERSON*A,char*key){
    PERSON*temp;

    if (A == NULL){
        return NULL;
    }

    if(strcmp(key,A->name)>0){                      // idem doprava od rootu
        A->right = delete(A->right,key);            // rekurzia
        if (balance_factor(A) > 1){                 // za každým vnorením skontrolujem BF
            if(balance_factor(A->left)>=0){
                A = rotation_right(A);              //Ak je BF
            }
            else{
                A->left = rotation_left(A->left);
                A = rotation_right(A);
            }
        }
    }
    else if(strcmp(key,A->name)<0){

        A->left = delete(A->left,key);
        if (balance_factor(A) < 1){
            if(balance_factor(A->right)<=0){
                A = rotation_left(A);
            }
            else{
                A->right = rotation_right(A->right);
                A = rotation_left(A);
            }
        }
    }
    else{
        if(A->right !=NULL){
            temp = A->right;
            while (temp->left != NULL){
                temp = temp->left;
            }
            A->name = temp->name;
            A->right = delete(A->right,temp->name);
            if (balance_factor(A) > 1){
                if(balance_factor(A->left)>=0){
                    A = rotation_right(A);
                }
                else{
                    A->left = rotation_left(A->left);
                    A = rotation_right(A);
                }
            }

        }
        else{
            return (A->left);
        }
    }
    A->height = height_of_tree(A,0);
    return (A);
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
        if(strcmp(data,A->name) > 0){               // postupujem doprava
            A->right = insert(A->right,data);       //pravé dieťa rootu. posielam do funkcie insert
            if (balance_factor(A) < -1){            // po rekurzii skontrolujem či je BF v rámci normyx
                if(strcmp(data,A->right->name)>0){      // Prípad RR
                    A = rotation_left(A);
                }
                else{
                    A->right = rotation_right(A->right);
                    A = rotation_left(A);
                }

            }
        }
        else if(strcmp(data,A->name) < 0){
            A->left = insert(A->left,data);
            if(balance_factor(A) > 1){
                if(strcmp(data,A->left->name)<0){
                    A = rotation_right(A);
                }
                else{
                    A->left = rotation_left(A->left);
                    A = rotation_right(A);
                }
            }
        }
    }
    A->height=height_of_tree(A,0);


    return A;
}


int main() {

    PERSON* root=NULL;

    root = insert(root,"A");
    root = insert(root,"B");
    root = insert(root,"C");
    root = insert(root,"D");
    root = insert(root,"E");
    root = insert(root,"F");


    root = delete(root,"");
    if(search(root,"Ctibor")){
        printf("Nasiel sa\n");
    }
    else{
        printf("Nenasiel sa\n");
    }



    return 0;
}
