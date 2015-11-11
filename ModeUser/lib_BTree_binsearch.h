//BINARY SEARCH AT EACH NODE


#include <iostream>
#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include "header.h"

using namespace std;

typedef struct BtreeNode
{
	//one extra key,value and child_ptr kept for the split-case
	int keys[ORDER];
	int values[ORDER];
	struct BtreeNode *child_ptrs[ORDER+1];
	struct BtreeNode *parent_ptr;
	struct BtreeNode *left_sibling_ptr;
	struct BtreeNode *rt_sibling_ptr;
	int no_of_keys_in_node;
}BtreeNode;

//performs a binary search in a node
int bin_search(int* arr, int key, int start, int end); 

//shifts and inserts keys in the node
void shift_insert_in_pos(BtreeNode *root,int pos,int value,int key);

//initializes a new node
void intitialize_node(BtreeNode *myBtreeNode);

class Btree
{
	private:
		BtreeNode *root;
	public:
		Btree();
		void create_root(BtreeNode *btree);
		int search(BtreeNode *root,int key);	//returns the corresponding value
		static BtreeNode* insert(BtreeNode *root,int key,int value);
		void display_sorted(BtreeNode *root, FILE* fp);
		void display_level(BtreeNode *root, FILE* fp);
};


Btree:: Btree()
{
	root=NULL;
}

void Btree::create_root (BtreeNode *btree)
{
	//initializations done in main
	root=btree;
}


void Btree::display_level(BtreeNode *root, FILE* fp)
{
	int i;
	BtreeNode *temp_root;

	//at each node, we print all the values left to right, following rt_sibling ptrs to the next node
	//till we reach the rt most node in a level
	//then we follow the leftmost child ptr of the leftmost node to move to the next level.
	while(root!=NULL)
	{
		temp_root=root;
		while(1)
		{
			fprintf(fp,"[");
			for(i=0;i<(ORDER-1);i++)
				fprintf(fp,"%d ",temp_root->values[i]);
			fprintf(fp,"]\t");
			temp_root=temp_root->rt_sibling_ptr;
			if(temp_root==NULL)
				break;
		}
		fprintf(fp,"\n");
		root=root->child_ptrs[0];
	}	
}

void Btree::display_sorted(BtreeNode *root, FILE* fp)
{
	int i;
	BtreeNode *temp_root;

	//this is similar to the in-order traversal of a binary tree
	//We follow the leftmost child-ptrs at each node till we reach the leaf
	//We printout all the values at leaf and move up to the parent
	//we print the value just after the child-ptr last followed to move down
	//next we follow the next child-ptrs 
	//this is done recursively.


	if(root->child_ptrs[0]==NULL)	//reached a leaf-node
	{//print all keys
		for(i=0;i<(ORDER-1) && root->keys[i]!=-1;i++)
			fprintf(fp,"%d ",root->values[i]);
		return;
	}

	for(i=0;i<ORDER;i++)
	{
		if(root->child_ptrs[i]!=NULL)	
			display_sorted(root->child_ptrs[i], fp);
		if(root->keys[i]!=-1)
			fprintf(fp,"%d ",root->values[i]);
	}		
}


int Btree::search(BtreeNode *root,int key)
{
	//search root and follow pointers down accordingly
	int i,value=-1;
	int pos;

	if(root==NULL)	//NOT FOUND
	{
		//printf("\nNULL");
		return value;
	}
	
	//We search the child-ptr along which we can move down
	pos=bin_search(root->keys,key,0,root->no_of_keys_in_node); 

	//if we find the key there, we are done!
	if(root->keys[pos]==key)
		return root->values[pos];

	//else if the value is greater than the key or we are at an index with no key, 
	//we move to the child and
	if(root->keys[pos]>key || root->keys[pos]==-1)
	{
		value=search(root->child_ptrs[pos],key);
		return value;
	}
}


BtreeNode* Btree::insert(BtreeNode *root,int key,int value)
{
	int i,j,pos,split_key,split_value;
	BtreeNode *left_new,*rt_new,*parent,*root_new,*temp_root;
	
	temp_root=root;

	if(temp_root->child_ptrs[0]!=NULL)		//haven't reached a leaf node, follow ptrs down to a leaf node
	{
		//search for the correct position 	
		//binary search
		while(temp_root->child_ptrs[0]!=NULL)	//move to leaf node
		{
			pos=bin_search(temp_root->keys,key,0,(temp_root->no_of_keys_in_node-1));
			if(temp_root->keys[pos]<key && temp_root->no_of_keys_in_node>0)
				pos++;
			temp_root=temp_root->child_ptrs[pos];
			
			//Moved down to a node 
		}
	}

	//reached a leaf node, insert the pair

	//search for the correct position 	
	//binary search
	pos=bin_search(temp_root->keys,key,0,(temp_root->no_of_keys_in_node-1));
	if(temp_root->keys[pos]<key && temp_root->no_of_keys_in_node>0)
		pos++;

	//this is the insertion in a leaf node- all child-ptrs NULL, so no adjustment reqd 
	shift_insert_in_pos(temp_root,pos,value,key);	
	temp_root->no_of_keys_in_node++;


	//if the node has exceeded its capacity, split it and move up the tree following parent pointers
	if(temp_root->no_of_keys_in_node==ORDER) 
	{
		while(1)
		{
			//split the node and form the left_new and rt_new nodes
			BtreeNode* left_new=new BtreeNode;
			intitialize_node(left_new);

			BtreeNode* rt_new=new BtreeNode;
			intitialize_node(rt_new);

			//Node is being split
			
			//keys copied
			for(i=0;i<(int)(floor(ORDER/2));i++)
			{
				left_new->keys[i]=temp_root->keys[i];
				left_new->values[i]=temp_root->values[i];
			}
			left_new->no_of_keys_in_node=(int)(floor(ORDER/2));

			split_key=temp_root->keys[(int)(floor(ORDER/2))];
			split_value=temp_root->values[(int)(floor(ORDER/2))];	

			for(i=(int)(floor(ORDER/2))+1;i<=ORDER-1;i++)
			{
				rt_new->keys[i-((int)(floor(ORDER/2))+1)]=temp_root->keys[i];
				rt_new->values[i-((int)(floor(ORDER/2))+1)]=temp_root->values[i];
			}
			rt_new->no_of_keys_in_node=(int)(floor((ORDER-1)/2));			
	
			//child ptrs copied as well, child's parent ptrs should also be updated
			for(i=0;i<=(int)(floor(ORDER/2));i++)
			{
				left_new->child_ptrs[i]=temp_root->child_ptrs[i];
				if(temp_root->child_ptrs[i]!=NULL)
					temp_root->child_ptrs[i]->parent_ptr=left_new;
			}
			for(i=(int)(floor(ORDER/2))+1;i<=ORDER;i++)
			{
				rt_new->child_ptrs[i-((int)(floor(ORDER/2))+1)]=temp_root->child_ptrs[i];
				if(temp_root->child_ptrs[i]!=NULL)
					temp_root->child_ptrs[i]->parent_ptr=rt_new;
			}
			
			//sibling ptrs being updated
			if(temp_root->left_sibling_ptr!=NULL)
				temp_root->left_sibling_ptr->rt_sibling_ptr=left_new;
			if(temp_root->rt_sibling_ptr!=NULL)
				temp_root->rt_sibling_ptr->left_sibling_ptr=rt_new;			
			left_new->left_sibling_ptr=temp_root->left_sibling_ptr;
			rt_new->rt_sibling_ptr=temp_root->rt_sibling_ptr;
			left_new->rt_sibling_ptr=rt_new;			
			rt_new->left_sibling_ptr=left_new;
			

			parent=temp_root->parent_ptr;

			if(parent==NULL)	// we are in root
			{
				//create new root with split_key and split_value and set the ptrs
				BtreeNode* root_new=new BtreeNode;
				intitialize_node(root_new);

				//split key copied
				root_new->keys[0]=split_key;
				root_new->values[0]=split_value;
	
				//child ptrs updates
				root_new->child_ptrs[0]=left_new;
				root_new->child_ptrs[1]=rt_new;	

				root_new->no_of_keys_in_node=1;
				
				//parent ptr updates
				left_new->parent_ptr=root_new;
				rt_new->parent_ptr=root_new;


				//sibling ptr updates
				//NULL- already initialized

				//************root UPDATED***********
				root=root_new;
		
				//DONE
				break;
			}

			else		//there is a non-null parent
			{
				//find position to insert the split-key
				pos=bin_search(parent->keys,split_key,0,(parent->no_of_keys_in_node-1));
				if(parent->keys[pos]<key && parent->no_of_keys_in_node>0)
					pos++;
				shift_insert_in_pos(parent,pos,split_value,split_key);	

				//insert the child ptrs to the newly created nodes
				parent->child_ptrs[pos]=left_new;
				parent->child_ptrs[pos+1]=rt_new;

				//update parent_ptrs
				left_new->parent_ptr=parent;
				rt_new->parent_ptr=parent;
				
				parent->no_of_keys_in_node++;
				
			}
			

			if(parent->no_of_keys_in_node<=(ORDER-1))		//adjustments successful, no further splits required
			{
				//DONE
				break;
			}
			else
			{
				//We move up
				temp_root=parent;
			}
		}
	}	

	return root;
}



void shift_insert_in_pos(BtreeNode *root,int pos,int value,int key)
{
	int i,j;
	char flag='0';

	//if the pos is vacant, we simply insert there
	if(root->keys[pos]==-1)
	{
		root->keys[pos]=key;
		root->values[pos]=value;
		//j=pos;	
	}

	else
	{
		//shift elements and insert
		for(i=ORDER-2;i>=pos;i--)
		{
			root->keys[i+1]=root->keys[i];
			root->values[i+1]=root->values[i];

		}	
		root->keys[pos]=key;
		root->values[pos]=value;
	}

	//shift child-pointers on the rt of pos to make space for left_new and rt_new
	for(i=ORDER-1;i>pos;i--)
		root->child_ptrs[i+1]=root->child_ptrs[i];	//child_ptr[pos] is no more
							
}


int bin_search(int* arr, int key, int start, int end)
{

	//recursive binary search 
	int i=start+(end-start)/2;
	int pos;

	if(end<=start)
		return (start);	

	//printf(" [nodes scanned in bin_search ");
	if(arr[i]==key)
		return i;
	
	if(key<arr[i])
		pos=bin_search(arr,key,start,(i-1));

	if(key>arr[i])
		pos=bin_search(arr,key,(i+1),end);

	//printf("]");

	return pos;
}
	

void intitialize_node(BtreeNode *myBtreeNode)
{
	int i;

	//initiation
	for(i=0;i<ORDER;i++)
	{	
		myBtreeNode->keys[i]=-1;
		myBtreeNode->values[i]=-1;
		myBtreeNode->child_ptrs[i]=NULL;
	}
	myBtreeNode->no_of_keys_in_node=0;	
	myBtreeNode->parent_ptr=NULL;
	myBtreeNode->left_sibling_ptr=NULL;
	myBtreeNode->rt_sibling_ptr=NULL;
	myBtreeNode->child_ptrs[i]=NULL;
}

