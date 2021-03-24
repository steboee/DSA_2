#include <stdio.h>
#include <stdlib.h>



typedef struct node{
    int data;
    struct node* left;
    struct node* right;
    int left_subtree;
    int right_subtree;
    int balance_factor;
}NODE;



int search(){

}


NODE* make_new_node(int data){
    NODE* new = (NODE*)malloc(sizeof(NODE));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    new->right_subtree=0;
    new->left_subtree=0;
    new->balance_factor = 0;
    return new;


}



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
    BASE->balance_factor=0;


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
    BASE->balance_factor=0;

    return rot_tree;





}


int insert(NODE** bunka,int data){
    NODE *A;

    if (*bunka == NULL){            // úplne prvé dáta ...
        *bunka = make_new_node(data);
        return 0;
    }


    A = *bunka;
    if (A == NULL){
        A = make_new_node(data)
    }



    if(data >= A->data){
        A->right_subtree++;
        A->balance_factor = A->left_subtree - A->right_subtree;
    }
    else if(data<A->data){
        A->left_subtree++;
        A->balance_factor = A->left_subtree-A->right_subtree;
    }

    if(data < A->data && A->left != NULL ){
        insert(&A->left,data);
    }
    else if(data >= A->data && A->right != NULL){
        insert(&A->left,data);
    }



    if (data < A->data){
        A->left = make_new_node(data);
        if(A->balance_factor > 1){
            A = rotation_right(&A);
        }
        else if (A->balance_factor < -1){
            A = rotation_left(&A);
        }
    }


    if(data >= A->data){
        A->right = make_new_node(abs(data));
        if(A->balance_factor > 1){
            A = rotation_right(&A);
        }
        else if (A->balance_factor < -1){
            A = rotation_left(&A);
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
    insert(&root,300);




    return 0;
}
