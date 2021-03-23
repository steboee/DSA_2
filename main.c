#include <stdio.h>
#include <stdlib.h>


typedef struct node{
    int data;
    struct node* left;
    struct node* right;
}NODE;



int search(){

}


NODE* make_new_node(int data){
    NODE* new = (NODE*)malloc(sizeof(NODE));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    return new;


}

int leftside=0;
int rightside=0;
int bf;




NODE* rotation_left(NODE**smt){

    NODE *rot_tree;
    NODE *leftside;
    NODE *BASE;
    rot_tree = *smt;
    BASE = *smt;
    leftside = rot_tree->left;

    rot_tree = rot_tree->right;
    rot_tree ->left = BASE;
    BASE->left = leftside;
    BASE->right = NULL;
    leftside =0;
    rightside = 0;
    return rot_tree;
}

NODE* rotation_right(NODE **smt){

    NODE *rot_tree;
    NODE *rightside;
    NODE *BASE;
    rot_tree = *smt;
    BASE = *smt;
    rightside = rot_tree->right;

    rot_tree = rot_tree->left;
    rot_tree ->right = BASE;
    BASE->right = rightside;
    BASE->left = NULL;
    leftside =0;
    rightside = 0;
    return rot_tree;





}


int insert(NODE** bunka,int data){
    NODE *A;


    if (*bunka == NULL){            // úplne prvé dáta ...
        *bunka = make_new_node(data);
        return 0;
    }

    A = *bunka;







    if (abs(data) < A->data && A->left == NULL ){
        A->left = make_new_node(abs(data));
    }

    else if(abs(data) < A->data && A->left != NULL ){
        if (data > 0){
            insert(&A->left,-data);
        }
        else{
            insert(&A->left,data);
        }

    }

    else if(abs(data) >= A->data && A->right == NULL){
        A->right = make_new_node(abs(data));
    }
    else if(abs(data) >= A->data && A->right != NULL){
        if (data > 0){
            insert(&A->left,-data);
        }
        else{
            insert(&A->left,data);
        }
    }
    if(data > 0){
        if(data>=A->data){
            rightside++;
        }
        else if(data<A->data){
            leftside++;
        }
        bf = leftside - rightside;
        if(bf < -1){
            A = rotation_left(&A);
            *bunka = A;
        }
        else if(bf > 1){
            A = rotation_right(&A);
            *bunka = A;
        }
    }




    return 0;



}







int main() {

    NODE* root=NULL;

    insert(&root,200);

    insert(&root,100);
    insert(&root,7);
    insert(&root,10);
    insert(&root,200);
    insert(&root,70);
    insert(&root,2);
    insert(&root,200);
    insert(&root,70);
    insert(&root,2);


    printf("Right = %d\nLeft = %d\n",rightside,leftside);
    printf("BF = %d\n",bf);

    return 0;
}
