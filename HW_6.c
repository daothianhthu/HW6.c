#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct Node{
    int data;
    struct Node *left;
    struct Node *right;

}Node;
Node*create(int value){
    Node *new=(Node*)malloc(sizeof(Node));
    new->data=value;
    new->left =NULL;
    new->right=NULL;

    return new;
}
Node*insert(Node *root,int value,int *comparisons){
    if(root==NULL){
        return create(value);
    }
    (*comparisons)++;
    if(value <root ->data){
        root->left=insert(root->left,value,comparisons);

    }else if(value > root->data){
        root->right=insert(root->right,value,comparisons);
    }
    else{ 
        return root;
    }
    return root;
}
int height(Node* root){
    if(root==NULL){
        return 0;
    
    }
    int leftHeight = height(root->left);
    int rightHeight = height(root->right);
    if(leftHeight > rightHeight){
        return leftHeight + 1;
    }
    return rightHeight + 1;
}

int check(int arr[],int size,int key,int *comparisons){
    for(int i = 0;i<size;i++){
        (*comparisons)++;
        if(arr[i]==key){
            return 1;
        }

    } 
    return 0;
}
typedef struct AVLNode{
    int data;
    int height;
    struct AVLNode *left;
    struct AVLNode *right;

}AVLNode;
AVLNode*createAVLNode(int value){
    AVLNode *new=(AVLNode*)malloc(sizeof(AVLNode));
    new->data=value;
    new->height=1;
    new->left=NULL;
    new->right=NULL;
    return new;
}
int getHeight(AVLNode *node){
    if(node==NULL) return 0;
    return node->height;

}
int getBalance(AVLNode* node){
    if(node==NULL) return 0;
    return getHeight(node->left)-getHeight(node->right);

}
int searchBST(Node *root, int key, int *comparisons)
{
    if (root == NULL)
        return 0;
    (*comparisons)++;

    if (key == root->data)
    {
        return 1;
    }
    if (key < root->data)
    {
        return searchBST(root->left, key, comparisons);
    }
    return searchBST(root->right, key, comparisons);
}

int max(int a, int b) 
{ return (a > b) ? a : b; }
AVLNode* rightRotate(AVLNode *y){
    
    AVLNode *x  = y->left;
    AVLNode *T2 = x->right;
    x->right = y;
    y->left  = T2;

    y->height = 1 + max(getHeight(y->left), getHeight(y->right));
    x->height = 1 + max(getHeight(x->left), getHeight(x->right));

    return x;   
}
AVLNode* leftRotate(AVLNode*x){
    AVLNode* y=x->right;
    AVLNode* T2=y->left;

    y->left=x;
    x->right=T2;

    x->height = 1 + max(getHeight(x->left), getHeight(x->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}
AVLNode*insertAVL(AVLNode *root,int value,int *comparisons){
   if(root==NULL)
   return createAVLNode(value);

    (*comparisons)++;

    if (value < root->data)
    {
        root->left = insertAVL(root->left, value, comparisons);
    }
    else if (value > root->data)
    {
        root->right = insertAVL(root->right, value, comparisons);
    }
    else
    { return root;
    }
    root->height = 1 + max(
        getHeight(root->left),
        getHeight(root->right)
    );

    int balance = getBalance(root);

      if (balance > 1 && value < root->left->data)
    {
        return rightRotate(root);
    }
     if (balance < -1 && value > root->right->data)
    {
        return leftRotate(root);
    }
     if (balance > 1 && value > root->left->data)
    {
        root->left = leftRotate(root->left);

        return rightRotate(root);
    }
     if (balance < -1 && value < root->right->data)
    {
        root->right = rightRotate(root->right);

        return leftRotate(root);
    }


    return root;
}
int searchAVL(AVLNode *root, int key, int *comparisons)
{
    if (root == NULL) return 0;
    (*comparisons)++;

    if (key == root->data) return 1;
    if (key < root->data)
    {
        return searchAVL(root->left, key, comparisons);
    }
    return searchAVL(root->right, key, comparisons);
}
void freeBST(Node *r){ if(!r) return; freeBST(r->left); freeBST(r->right); free(r); }
void freeAVL(AVLNode *r){ if(!r) return; freeAVL(r->left); freeAVL(r->right); free(r); }

int main(){

    srand(time(NULL));
    int arr[100];
    int size=0;
    int duplicates=0;
    int arraycomparisons =0;
     Node *root =NULL;
     int bstComparisons = 0;
     int value;
    
     AVLNode *avlroot=NULL;
     int avlComparisons = 0;
     
printf("generated 100 random numbers \n");
for(int i=0;i <100;i++){
    value= rand()%1001;

    printf(" %d ",value);

    int comparisons = 0;
    int found = check(arr,size,value,&comparisons);
    arraycomparisons += comparisons;
if(found==1){
    duplicates++;

}
else{
    arr[size]=value;
    size++;

}
 int bstComp=0;
     root =insert(root,value,&bstComp);
      bstComparisons +=bstComp;

int avlComp = 0;
    avlroot = insertAVL(avlroot, value, &avlComp);
    avlComparisons += avlComp;
}

printf("\n\nStored values : %d\n", size);
printf("Duplicates    : %d\n\n", duplicates);

printf("Construction\n");
printf("Array comparisons : %d\n", arraycomparisons);
printf("BST comparisons   : %d\n", bstComparisons);
printf("AVL comparisons   : %d\n\n", avlComparisons);

printf("Structure\n");
printf("Array length : %d\n", size);
printf("BST height   : %d\n", height(root));
printf("AVL height   : %d\n\n", getHeight(avlroot));
printf("\n==SEARCH 50 KEYS ==\n");
int arraySearchTotal = 0;
int bstSearchTotal = 0;
int avlSearchTotal = 0;
int keys[50];

printf("Generated 50 search keys:\n");
for (int i = 0; i < 50; i++) {
    keys[i] = rand() % 1001;
    printf("%d ", keys[i]);
}
printf("\n\nSearches : 50\n\n");
for (int i = 0; i < 50; i++)
{
    int key = keys[i];                      

    int arrayComp = 0;
    int arrayFound = check(arr, size, key, &arrayComp);

    int bstSearchComp = 0;
    int bstFound = searchBST(root, key, &bstSearchComp);

    int avlSearchComp = 0;
    int avlFound = searchAVL(avlroot, key, &avlSearchComp);

    arraySearchTotal += arrayComp;
    bstSearchTotal += bstSearchComp;
    avlSearchTotal += avlSearchComp;

    printf("Search Key : %d\n\n", key);

    printf("Sequential Search\n");
    printf("Result      : %s\n", arrayFound ? "Found" : "Not Found");
    printf("Comparisons : %d\n\n", arrayComp);

    printf("BST Search\n");
    printf("Result      : %s\n", bstFound ? "Found" : "Not Found");
    printf("Comparisons : %d\n\n", bstSearchComp);

    printf("AVL Search\n");
    printf("Result      : %s\n", avlFound ? "Found" : "Not Found");
    printf("Comparisons : %d\n\n", avlSearchComp);
}
    
printf("Sequential Search\n");
printf("Total comparisons   : %d\n", arraySearchTotal);
printf("Average comparisons : %.2f\n\n", (double)arraySearchTotal / 50);

printf("BST Search\n");
printf("Total comparisons   : %d\n", bstSearchTotal);
printf("Average comparisons : %.2f\n\n", (double)bstSearchTotal / 50);

printf("AVL Search\n");
printf("Total comparisons   : %d\n", avlSearchTotal);
printf("Average comparisons : %.2f\n", (double)avlSearchTotal / 50);
freeBST(root);
freeAVL(avlroot);
return 0;
}
