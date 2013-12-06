#include <cstddef>
#include <iostream>
#include <queue>
#ifndef BST_H
#define BST_H
using namespace std;

template<class Item>
class bstNode
{
public:
	//constructor
	bstNode(const Item& init_data, bstNode* init_left=NULL, bstNode* init_right= NULL)
    {
        data_field = init_data;
        left_field = init_left;
        right_field = init_right;
    }
	//helper functions if you need them ..
	//I think I haven't used any of them so far
	//Item& get_data() {return data_field;}
	void set_data(Item& target) {data_field=target;}
    void set_left(bstNode* target) {left_field=target;}
    void set_right(bstNode* target) {right_field=target;}
	bstNode*& get_left() {return left_field;}
	bstNode*& get_right() {return right_field;}
    Item& get_data() {return data_field;}
	
	//FUNCTIONS YOU IMPLEMENT BELOW
	bool find(Item& targetData);
	void insert(Item& targetData);
	void remove(Item& targetData);
	int size();
	void traverse();
    void printLevelOrder(bstNode* root);
    bstNode<Item>* find_pointer(Item& targetData);
    bstNode<Item>* findParent(Item& targetData);
	
	//our private variables (we just have 3)
private:
    Item data_field; //our data
    bstNode* left_field; //pointer to left child
    bstNode* right_field; //pointer to right child
};
//ALL OUR IMPLEMENTATIONS GO IN HERE-- NO .CPP FILE FOR BSTNODE BECUASE IT'S A TEMPLATE CLASS
template<class Item>
bool bstNode<Item>::find(Item& targetData)
{
    if (data_field == targetData)
    {
        return true;
    }
    if(left_field == NULL && right_field == NULL)
    {
        return false;
    }
    if(left_field != NULL)
    {
        if(left_field -> find(targetData) == true)
        {
            return true;
        }
    }
    if(right_field != NULL)
    {
        if(right_field -> find(targetData) == true)
        {
            return true;
        }
    }
    return false;
    //check my self, check my children... if I find targetData I return true, else false
    
}

template<class Item>
bstNode<Item>* bstNode<Item>::find_pointer(Item& targetData)
{
    bstNode* tempPointer;
    if ( data_field == targetData)
    {
        return this;
    }
    if ( !(left_field == NULL) )
    {
        tempPointer = left_field->find_pointer(targetData);
        if ( tempPointer != NULL )
        {
            return tempPointer;
        }
    }
    if ( !(right_field == NULL) )
    {
        tempPointer = right_field->find_pointer(targetData);
        if ( tempPointer != NULL )
        {
            return tempPointer;
        }
    }
    return NULL;
}

template<class Item>
bstNode<Item>* bstNode<Item>::findParent(Item& targetData)
{
    bstNode* tempPointer;
    if ( !(left_field == NULL) )
    {
        if ( this->left_field->get_data() == targetData)
        {
            return this;
        }
        tempPointer = left_field->findParent(targetData);
        if ( tempPointer != NULL )
        {
            return tempPointer;
        }
    }
    if ( (right_field != NULL) )
    {
        if ( this->right_field->get_data() == targetData)
        {
            return this;
        }
        tempPointer = right_field->findParent(targetData);
        if ( tempPointer != NULL )
        {
            return tempPointer;
        }
    }
    return NULL;
}

template<class Item>
void bstNode<Item>::insert(Item& targetData)
{
    if(targetData < data_field)
    {
        if(left_field == NULL){
            left_field = new bstNode<Item>(targetData);
        }
        else
        {
            left_field->insert(targetData);
        }
    }
    else if(targetData > data_field)
    {
        if(right_field == NULL)
        {
            right_field = new bstNode<Item>(targetData);
        }
        else
        {
            right_field->insert(targetData);
        }
    }
    else
    {
        return;
    }
}
//go through and find the correct place to insert a new node
//with this data, remember that you print out the tree in
//that specific format after you insert!

template<class Item>
void bstNode<Item>::traverse()
{
    if(left_field != NULL){
        left_field->traverse();
	}
    cout << data_field << " ";
	if(right_field !=NULL){
		right_field->traverse();
	}
}

template<class Item>
void bstNode<Item>::remove(Item& targetData)
{
    bstNode* targetPointer = find_pointer(targetData);
    bstNode* parent;
    bstNode* cursor = targetPointer;
    int nodeCount = 0;
    bool check = true;
    if (cursor->get_left() != NULL)
    {
        cursor = cursor->get_left();
        check = true;
        while (check)
        {
            if (cursor->get_right() != NULL)
            {
                cursor = cursor->get_right();
                nodeCount++;
            }
            else if (nodeCount > 0)
            {
                parent = findParent(cursor->get_data());
                targetPointer->set_data(cursor->get_data());
                parent->set_right(cursor->get_left());
                check = false;
            }
            else
            {
                parent = findParent(cursor->get_data());
                if (parent->get_data() != targetPointer->get_data())
                {
                    targetPointer->set_data(cursor->get_data());
                    parent->set_left(cursor->get_left());
                    parent->set_right(cursor->get_right());
                }
                else
                {
                    targetPointer->set_data(cursor->get_data());
                    targetPointer->set_left(cursor->get_left());
                }
                check = false;
            }
        }
        
    }
    else if (cursor->get_right() != NULL)
    {
        cursor = cursor->get_right();
        targetPointer->set_data(cursor->get_data());
        targetPointer->set_left(cursor->get_left());
        targetPointer->set_right(cursor->get_right());
    }
    else
    {
        parent = findParent(targetData);
        if (parent->get_left() != NULL)
        {
            if (parent->get_left()->get_data() == targetData)
            {
                parent->set_left(NULL);
            }
        }
        if (parent->get_right() != NULL)
        {
            if (parent->get_right()->get_data() == targetData)
            {
                parent->set_right(NULL);
            }
        }
    }
    delete cursor;
    cursor = NULL;
}

template<class Item>
int bstNode<Item>::size()
{
    int i=1;
    if(left_field == NULL && right_field == NULL)
    {
        return 1;
    }
    if(left_field != NULL)
    {
        i += left_field -> size();
    }
    if (right_field != NULL)
    {
        
        i += right_field -> size();
    }
    return i;
	//go through and count the number of nodes in this
}

template<class Item>
void bstNode<Item>::printLevelOrder(bstNode* root)
{
    if (!root)
    {
        return;
    }
    int counter = 0;
    cout << "R" << counter << endl;
    queue<bstNode*> currentLevel, nextLevel;
    currentLevel.push(root);
    while (!currentLevel.empty())
    {
        bstNode* currNode = currentLevel.front();
        currentLevel.pop();
        if (currNode)
        {
            cout << currNode->data_field << endl;
            nextLevel.push(currNode->left_field);
            nextLevel.push(currNode->right_field);
        }
        if (currentLevel.empty() && (nextLevel.size() != 0) )
        {
            cout << "------" << endl;
            if (!nextLevel.empty()  && ( (nextLevel.front() != 0) || (nextLevel.back() != 0) ) )
            {
                counter++;
                cout << "R" << counter << endl;
            }
            swap(currentLevel, nextLevel);
        }
    }
}
#endif