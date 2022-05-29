#include<stdio.h>
#include<stdlib.h>
#include"tree.h"
#include"generic_vector.h"


tNode* insertNodes(tNode* node, MY_STRING new_key)
{
  /*BST insertion -usual technique , refer to notes */
    if (node == NULL)
        return(createNode(new_key));
 
    if (my_string_compare(new_key, node->key) < 0)
        node->lChild  = insertNodes(node->lChild, new_key);
    else if (my_string_compare(new_key, node->key) > 0)
        node->rChild = insertNodes(node->rChild, new_key);
    else // No duplicates in a BST
        return node;
    
    /* A update height of the node */
    node->nodeHeight = 1 + findmax(getHeight(node->lChild),getHeight(node->rChild));
 
    /* B. calculate balance factor (hLeft-hRigh)*/
    int balance = getBalancefactor(node);
 
    /*IF Node is unbalance, i.e balance is >1 or <-1, then it could be: */
 
    // 1. LEFT LEFT CASE (In this case, just rotate once on the RIGHT)
    if (balance > 1 && my_string_compare(new_key, node->lChild->key) < 0)
        return rightRotation(node);
 
    // 2. RIGHT RIGHT CASE (In this case, just rotate once on the left)
    if (balance < -1 && my_string_compare(new_key, node->rChild->key) > 0)
        return leftRotation(node);
 
    // 3. LEFT - RIGHT CASE ()
    if (balance > 1 && my_string_compare(new_key, node->lChild->key) > 0)
    {
        node->lChild =  leftRotation(node->lChild); //To make it a LEFT LEFT CASE
        return rightRotation(node);
    }
 
    // 4. RIGHT - LEFT CASE
    if (balance < -1 && my_string_compare(new_key, node->rChild->key) < 0) 
    {
        node->rChild = rightRotation(node->rChild);//To make it a RIGHT RIGHT CASE
        return leftRotation(node);
    }
 
    /* return the (unchanged) node pointer */
    return node;
 
}
/* Create a new node with the given key and NULL lChild and rChild pointers. */
tNode* createNode(MY_STRING new_key)
{
    tNode* node = (tNode*) malloc(sizeof(tNode));
    node->key = my_string_init_default();
    my_string_assignment(&node->key, new_key);
    node->lChild   = NULL;
    node->rChild  = NULL;
    node->nodeHeight = 1;//assume that node is added at leaf
    node->words = generic_vector_init_default();

    return(node);
}
// A get method for height of the node.
int getHeight(tNode *node)
{
    if (node == NULL)
        return 0;
    return node->nodeHeight;
}

// Calculates and returns the balance factor
int getBalancefactor(tNode* node)
{
    if (node == NULL)
        return 0;
    return getHeight(node->lChild) - getHeight(node->rChild);
}

// This should show a sorted out tree(recall from last class)
void inorderTraversal(tNode *root, int* largest)
{
  if(root == NULL){
    return;
  }
    
  inorderTraversal(root->lChild, largest);
  if(generic_vector_get_size(root->words) > *largest){
    *largest = generic_vector_get_size(root->words);
  }
  //my_string_insertion(root->key, stdout);
  //printf(" %d\n", generic_vector_get_size(root->words));
  inorderTraversal(root->rChild, largest);
    
}
// This should show tree with root first (recall from last class)
void preorderTraversal(tNode *root, MY_STRING new_key, MY_STRING oriWord)
{
    if(root == NULL){
      return;
    }
    if(my_string_compare(root->key, new_key) == 0){
      generic_vector_push_back(root->words, oriWord);
    }
    preorderTraversal(root->lChild, new_key, oriWord);
    preorderTraversal(root->rChild, new_key, oriWord);    
}

void traverse(tNode *root, int largest, GENERIC_VECTOR hVectorCurr, MY_STRING largestKey){
  if(root == NULL){
    return;
  }
  if(generic_vector_get_size(root->words) == largest){
    generic_vector_assignment(&hVectorCurr, root->words);
    my_string_assignment(&largestKey, root->key);
  }
  traverse(root->lChild, largest, hVectorCurr, largestKey);
  traverse(root->rChild, largest, hVectorCurr, largestKey);
  
}

 
// Rotate Right
tNode *rightRotation(tNode* nodey)
{
    tNode* nodex = nodey->lChild;
    tNode* T2 = nodex->rChild;
 
    // Rotate RIGHT
    nodex->rChild = nodey;
    nodey->lChild = T2;
 
    // Update heights
    nodey->nodeHeight = findmax(getHeight(nodey->lChild), getHeight(nodey->rChild))+1;
    nodex->nodeHeight = findmax(getHeight(nodex->lChild), getHeight(nodex->rChild))+1;
 
    // Return new root
    return nodex;
}
 
// rotate LEFT subtree rooted with a nodex
tNode* leftRotation(tNode* nodex)
{
    tNode* nodey = nodex->rChild;
    tNode* T2 = nodey->lChild;
 
    // Rotate LEFT
    nodey->lChild = nodex;
    nodex->rChild = T2;
 
    //  Update height of nodes
    nodex->nodeHeight = findmax(getHeight(nodex->lChild), getHeight(nodex->rChild))+1;
    nodey->nodeHeight = findmax(getHeight(nodey->lChild), getHeight(nodey->rChild))+1;
 
    // Return new root
    return nodey;
}

void treeDestroy(tNode* root){
  if(root == NULL){
    return;
  }
  treeDestroy(root->lChild);
  treeDestroy(root->rChild);
  generic_vector_destroy(&root->words);
  my_string_destroy(&root->key);
  free(root);
  
  
}
// return the largest value (used for height comparison)
int findmax(int x, int y)
{
    return (x > y)? x : y;
}
