#include <iostream>
#include <stdlib.h>
#include<stdio.h>
//on deletion replace root by smallest node on rt sub-tree

using namespace std;

struct AVLNode
{
	int key;
	int value;
	int balance_factor;
	AVLNode *left;
	AVLNode *right;
};
 
class avltree
{
	private:
		AVLNode *root;
	public:
		avltree();
		void create_root(AVLNode *avl);
		AVLNode* searchtree(AVLNode *root,int key);	
		static AVLNode* insert(AVLNode *root,int key,int value,char *bf_update_reqd);
		void display_inorder(AVLNode *root,FILE* fp);
		void display_postorder(AVLNode *root,FILE* fp);
};


avltree:: avltree()
{
	root=NULL;
}

void avltree::create_root (AVLNode *avl)
{
	root=avl;
}


AVLNode* avltree:: searchtree (AVLNode *root,int key)
{
	AVLNode *temp_node_1,*temp_node_2;
 
	//if NULL ptr encountered, return Not Found
	if(root==NULL)
		return NULL;

	if(root->key==key)
		return root;	

	//if key< root's key,move to left
	if(key<root->key)
	{
		temp_node_1=searchtree(root->left,key);
		return temp_node_1;
	}
 
	//if key> root's key,move to right
	if(key>root->key)
	{
		temp_node_2=searchtree(root->right,key);
		return temp_node_2;
 	}
}


AVLNode* avltree::insert(AVLNode *root,int key,int value,char *bf_update_reqd)
{
	AVLNode *temp_node_1,*temp_node_2;
 
	//if tree empty,just create a new node with the given key and make it the root
	if(root==NULL)
	{
		root=new AVLNode;
		root->key=key;
		root->value=value;
		root->left=NULL;
		root->right=NULL;
		root->balance_factor=0;
		*bf_update_reqd='1';
		return root;
	}

	//if key< root's key,move to left
	if(key<root->key)
	{
		root->left=insert(root->left,key,value,bf_update_reqd);
 
		// now if balance factors need to be updated
		if(*bf_update_reqd=='1')
		{
			//if root's bf is 1, adjustment is required, since key was inserted in its left subtree
			if(root->balance_factor==1)
			{
				temp_node_1=root->left;
				//if insertion took place in root's left-child's left subtree
				if(temp_node_1->balance_factor==1)	//LL rotation
				{
					root->left=temp_node_1->right;
					temp_node_1->right=root;
					root->balance_factor=0;
					root=temp_node_1;
				}

				//if insertion took place in root's left-child's right subtree
				else	//LR rotation
				{
					temp_node_2=temp_node_1->right;
					temp_node_1->right=temp_node_2->left;
					temp_node_2->left=temp_node_1;
					root->left=temp_node_2->right;
					temp_node_2->right=root;
					if(temp_node_2->balance_factor==1)
						root->balance_factor=-1;
					else
						root->balance_factor=0;
					if(temp_node_2->balance_factor==-1)
						temp_node_1->balance_factor=1;
					else
						temp_node_1->balance_factor=0;
					root=temp_node_2;
				}
				//rotation balances the imbalance and root's balance factor is zero now
				root->balance_factor=0;
				*bf_update_reqd='0';
			}
 
			//if root's bf was zero, it becomes 1 due to insertion in left subtree
			else if(root->balance_factor==0)
				root->balance_factor=1;

			//if root's bf was -1, it becomes 0 due to insertion in left subtree
			else if(root->balance_factor==-1)
			{	
				root->balance_factor=0;
				*bf_update_reqd='0';
			}
		}
	}
 
	//if key> root's key,move to right
	if(key>root->key)
	{
		root->right=insert (root->right,key,value,bf_update_reqd);
 
		// now if balance factors need to be updated
		if(*bf_update_reqd=='1')
		{
			//if root's bf is 1, no rotation is required, since key was inserted in its rt subtree
			if(root->balance_factor==1)
			{
				root->balance_factor=0;
				*bf_update_reqd='0';
			}

			else if(root->balance_factor==0)
					root->balance_factor=-1;
			
			else if(root->balance_factor==-1)	
			//adjustment required,balance_factor becomes -2
			{	
				temp_node_1=root->right;
				//if insertion took place in root's rt-child's rt subtree
				if(temp_node_1->balance_factor==-1)	//RR rotation
				{
					root->right=temp_node_1->left;
					temp_node_1->left=root;
					root->balance_factor=0;
					root=temp_node_1;
				}
				else	//RL rotation
				{
					temp_node_2=temp_node_1->left;
					temp_node_1->left=temp_node_2->right;
					temp_node_2->right=temp_node_1;
					root->right=temp_node_2->left;
					temp_node_2->left=root;
					if(temp_node_2->balance_factor==-1)
						root->balance_factor=1;
					else
						root->balance_factor=0;
					if(temp_node_2->balance_factor==1)
						temp_node_1->balance_factor=-1;
					else
						temp_node_1->balance_factor=0;
					root=temp_node_2;
				}
				root->balance_factor=0;
				*bf_update_reqd='0';
			}
		}
	}
	return root;
}


void avltree:: display_inorder (AVLNode* root,FILE* fp)
{

	if(root != NULL)
	{
		display_inorder (root->left,fp);
		fprintf(fp,"%d ",root->value);
		display_inorder (root->right,fp);
	}
}

void avltree:: display_postorder (AVLNode* root,FILE* fp)
{
	if(root != NULL)
	{
		display_postorder (root->left,fp);
		display_postorder (root->right,fp);
		fprintf(fp,"%d ",root->value);
	}
}


