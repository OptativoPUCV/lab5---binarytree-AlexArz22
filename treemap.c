#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "treemap.h"
#include <stdbool.h>
typedef struct TreeNode TreeNode;


struct TreeNode {
    Pair* pair;
    TreeNode * left;
    TreeNode * right;
    TreeNode * parent;
};

struct TreeMap {
    TreeNode * root;
    TreeNode * current;
    int (*lower_than) (void* key1, void* key2);
};

int is_equal(TreeMap* tree, void* key1, void* key2){
    if(tree->lower_than(key1,key2)==0 &&  
        tree->lower_than(key2,key1)==0) return 1;
    else return 0;
}


TreeNode * createTreeNode(void* key, void * value) {
    TreeNode * new = (TreeNode *)malloc(sizeof(TreeNode));
    if (new == NULL) return NULL;
    new->pair = (Pair *)malloc(sizeof(Pair));
    new->pair->key = key;
    new->pair->value = value;
    new->parent = new->left = new->right = NULL;
    return new;
}

TreeMap * createTreeMap(int (*lower_than) (void* key1, void* key2)) {
  
  TreeMap *tree= (TreeMap *) malloc(sizeof(TreeMap));
  if(tree==NULL) return NULL;
  
  tree->lower_than = lower_than;
  return tree;
}


void insertTreeMap(TreeMap * tree, void* key, void * value) {
  Pair *par=(Pair *) malloc(sizeof(Pair));
  par->key=key;
  par->value=value;
  tree->current=tree->root;
  int iguales;
  while(true){
    iguales=is_equal(tree, tree->current->pair->key, key);
    if(iguales==1) return;
      
    else{
      int comparar=tree->lower_than(tree->current->pair->key, key);
      if(comparar==1){
        if(tree->current->right==NULL){
          TreeNode *nodo=malloc(sizeof(TreeNode));
          nodo->pair=par;
          nodo->parent=tree->current;
          tree->current->right=nodo;
          nodo->left=NULL;
          nodo->right=NULL;
          tree->current=tree->current->right;
          return;
        }
        tree->current=tree->current->right;
      }
      if(comparar==0){
        if(tree->current->left==NULL){
          TreeNode *nodo=malloc(sizeof(TreeNode));
          nodo->pair=par;
          nodo->parent=tree->current;
          tree->current->left=nodo;
          nodo->left=NULL;
          nodo->right=NULL;
          tree->current=tree->current->left;
          return;
        }
        tree->current=tree->current->left;
      }
    }
  }
  
}

TreeNode * minimum(TreeNode * x){

  while(true){
    if(x->left==NULL) return x;
    x=x->left;
  }
  
}


void removeNode(TreeMap * tree, TreeNode* node) {

  //No tiene hijos
  if(node->left == NULL && node->right == NULL){
    TreeNode *padre=node->parent;
    padre=NULL;
    return;
  }

  //Solo tiene un hijo
  if((node->left == NULL && node->right != NULL) || (node->left != NULL && node->right == NULL)){
    if(node->left!=NULL){
      node=node->left;
      node->left=NULL;
    }
    else{
      node=node->right;
      node->right=NULL;
    }
  }

  //Tiene 2 hijos
  if(node->left != NULL && node->right != NULL){
    
  }
}

void eraseTreeMap(TreeMap * tree, void* key){
    if (tree == NULL || tree->root == NULL) return;

    if (searchTreeMap(tree, key) == NULL) return;
    TreeNode* node = tree->current;
    removeNode(tree, node);

}


Pair * searchTreeMap(TreeMap * tree, void* key) {

  tree->current=tree->root;
  while(true){
    if(tree->current==NULL) return NULL;
    int iguales=is_equal(tree, tree->current->pair->key, key);
    
    if(iguales==1) return tree->current->pair;
      
    else{
      int comparar=tree->lower_than(tree->current->pair->key, key);
      if(comparar==1){
        tree->current=tree->current->right;
      }
      if(comparar==0){
        tree->current=tree->current->left;
      }
    }
  }
}


Pair * upperBound(TreeMap * tree, void* key) {
    return NULL;
}

Pair * firstTreeMap(TreeMap * tree) {
    return NULL;
}

Pair * nextTreeMap(TreeMap * tree) {
    return NULL;
}
