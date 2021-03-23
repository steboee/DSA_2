#include <stdio.h>
#include <stdlib.h>



typedef struct node{
    int data;
    struct node* left;
    struct node* right;
    int ht;
}NODE;



int search(){

}


NODE* make_new_node(int data){
    NODE* new = (NODE*)malloc(sizeof(NODE));
    new->data = data;
    new->left = NULL;
    new->right = NULL;
    new->ht = 0;
    return new;


}

int leftside=0;
int rightside=0;
int bf;

int height(NODE *a)
{
    int lh,rh;

    if(a==NULL){
        return(0);
    }

    if(a->left==NULL){
        lh=0;
    }

    else{
        lh=1+a->left->ht;
    }


    if(a->right==NULL)
        rh=0;
    else
        rh=1+a->right->ht;

    if(lh>rh)
        return(lh);

    return(rh);
}

NODE * rotation_right(NODE *x)
{
    NODE *y;
    y=x->left;
    x->left=y->right;
    y->right=x;
    x->ht=height(x);
    y->ht=height(y);
    return(y);
}

NODE * rotation_left(NODE *samp)
{
    NODE *y;
    y=samp->right;
    samp->right=y->left;
    y->left=samp;
    samp->ht=height(samp);
    y->ht=height(y);

    return(y);
}

NODE * RR(NODE *T)
{
    T=rotation_left(T);
    return(T);
}

NODE * LL(NODE *T)
{
    T=rotation_right(T);
    return(T);
}

NODE * LR(NODE *T)
{
    T->left=rotation_left(T->left);
    T=rotation_right(T);

    return(T);
}

NODE * RL(NODE *T)
{
    T->right=rotation_right(T->right);
    T=rotation_left(T);
    return(T);
}

int BF(NODE *T)
{
    int lh,rh;
    if(T==NULL)
        return(0);

    if(T->left==NULL)
        lh=0;
    else
        lh=1+T->left->ht;

    if(T->right==NULL)
        rh=0;
    else
        rh=1+T->right->ht;

    return(lh-rh);
}


/*NODE* rotation_left(NODE**smt){

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
*/

/*int insert(NODE** bunka,int data){
    NODE *A;


    if (*bunka == NULL){            // úplne prvé dáta ...
        *bunka = make_new_node(data);
        return 0;
    }

    A = *bunka;
    if(data > 0){
        if(data>=A->data){
            rightside++;
        }
        else if(data<A->data){
            leftside++;
        }
    }


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


    if(A->ht < -1){
        A = rotation_left(&A);
        *bunka = A;
    }
    else if(A->balance_factor > 1){
        A = rotation_right(&A);
        *bunka = A;
    }



    return 0;
}
*/
NODE * insert(NODE *T,int x)
{
    if(T==NULL)
    {
        T=(NODE*)malloc(sizeof(NODE));
        T->data=x;
        T->left=NULL;
        T->right=NULL;
    }
    else
    if(x > T->data)		// insert in right subtree
    {
        T->right=insert(T->right,x);
        if(BF(T)==-2)
            if(x>T->right->data)
                T=RR(T);
            else
                T=RL(T);
    }
    else
    if(x<T->data)
    {
        T->left=insert(T->left,x);
        if(BF(T)==2)
            if(x < T->left->data)
                T=LL(T);
            else
                T=LR(T);
    }

    T->ht=height(T);

    return(T);
}


int main() {

    NODE* root=NULL;

    insert(&root,200);

    insert(&root,100);
    insert(&root,7);
    insert(&root,10);
    insert(&root,200);



    printf("BF = %d\n",bf);

    return 0;
}
