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



int insert(NODE** bunka,int data){
    if (*bunka == NULL){
        *bunka = make_new_node(data);
    }


}







int main() {
    printf("Hello, World!\n");

    NODE* root=NULL;

    insert(&root,50);

    return 0;
}
