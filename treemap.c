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
  if(x==NULL) return NULL;
  while(true){
    if(x->left==NULL) return x;
    x=x->left;
  }
  
}


void removeNode(TreeMap * tree, TreeNode* node) {

  //No tiene hijos
  TreeNode *padre=malloc(sizeof(TreeNode));
  padre=node->parent;
  if(node->left == NULL && node->right == NULL){
    if(padre->left==node) padre->left=NULL;
    if(padre->right==node) padre->right=NULL;
    free(node);
    return;
  }

  TreeNode *hijo=malloc(sizeof(TreeNode));

  //Solo tiene un hijo
  if((node->left == NULL && node->right != NULL) || (node->left != NULL && node->right == NULL)){

    if(padre->left==node){
      if(node->left!=NULL){
        hijo=node->left;
        padre->left=hijo;
        hijo->parent=padre;
      }
      else{
        hijo=node->right;
        padre->left=hijo;
        hijo->parent=padre;
      }
    }

    if(padre->right==node){
      if(node->left!=NULL){
        hijo=node->left;
        padre->right=hijo;
        hijo->parent=padre;
      }
      else{
        hijo=node->right;
        padre->right=hijo;
        hijo->parent=padre;
      }
    }  
    free(node);
  }

  //Tiene 2 hijos
  TreeNode *menor=malloc(sizeof(TreeNode));
  menor=minimum(node->right);
  if(node->left != NULL && node->right != NULL){
    node->pair=menor->pair;
    removeNode(tree, menor);
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
  tree->current=tree->root;
  tree->current=minimum(tree->current);
  if(tree->current==NULL) return NULL;
  return tree->current->pair;
}

Pair * nextTreeMap(TreeMap * tree) {
  if(tree==NULL || tree->current==NULL) return NULL;
  /*TreeNode *max= tree->root;
  if(max==NULL) return NULL;
  while(true){
    if(max->right!=NULL) max=max->right;
    if(max->right==NULL) break;
  }
  if(max->pair->key==tree->current->pair->key){
    return NULL;
  }
  */
  TreeNode *original=tree->current;
  
  if(tree->current->right!=NULL){
    tree->current=minimum(tree->current->right);
    return tree->current->pair;
  }
  else{
    while(true){
      if(original->pair->key < tree->current->pair->key){
        return tree->current->pair;
      }
      else{
        tree->current=tree->current->parent;
      }
    }
  }
}  

