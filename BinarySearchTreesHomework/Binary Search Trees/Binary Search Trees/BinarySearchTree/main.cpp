//
//  main.cpp
//  Binary Search Trees
//
//  Created by Sheefali Tewari on 8/1/13.
//  Copyright (c) 2013 Sheefali Tewari. All rights reserved.
// Collaborated with Paul.

#include <iostream>
#include "bst.h"
using namespace std;

int main()
{
	bstNode<int>* root=NULL;//make an initial root pointer
	int data; //data to be cin by user
    int out;
	char command; //command to be cin by user
	while(true) //we keep letting user do stuff until they hit q
	{ //all our commands (some take 2 cin some take 1)
		
		cout<<"enter i followed by number to insert"<<endl;
		cout<<"enter r followed by number to remove"<<endl;
		cout<<"enter f followed by number to find"<<endl;
		cout<<"enter s to see the size of the tree"<<endl;
		cout<<"enter t to print out values in the tree"<<endl;
        cout<<"enter p to print out the tree"<<endl;
		cout<<"enter q to quit"<<endl;
		cin>>command;
		if (command=='i' || command=='r' || command=='f')
		{
			cin>>data;
		}
		switch(command) //case statement that runs through our commands
		{
                //I gave case i, case f, case t as an example of how we do stuff in main
			case 'i':
                cout << "*** " << command << " " << data << " ***" << endl;
				if (root==NULL) //ALWAYS check the NULL case before dereferencing
					root=new bstNode<int>(data);
				else
                    root->insert(data);
                root->printLevelOrder(root);
				break;
			case 'r':
                cout << "*** " << command << " " << data << " ***" << endl;
                //fill this in
                if (root==NULL)
                {
                    cout << "There are no nodes in the tree to remove!" << endl;
                }
                else if ( (root->size() == 1) && (root->find(data) ) )
                {
                    cout << "the only node in the tree is the root node." << endl;
                    delete root;
                    root = NULL;
                    cout << "Root removed" << endl;
                }
                else if ( !root->find(data) )
                {
                    cout << "We could not find the data you asked to delete!" << endl;
                }
                else if ( root->find(data) )
                {
                    cout << "Found data! Attempting to remove..." << endl;
                    root->remove(data);
                }
                root->printLevelOrder(root);
				break;
			case 'f':
                cout << "*** " << command << " " << data << " ***" << endl;
				if(root->find(data))
				{
					cout << "Found the data we want!" << endl;
				}
				else
				{
					cout<<"Not Found!"<<endl;
				}
				break;
			case 's':
                cout << "*** " << command << " ***" << endl;
                out = root->size();
                cout << "BST total size is: " << out << endl;
				break;
			case 't':
                cout << "*** " << command << " ***" << endl;
				if(root!=NULL)
					root->traverse();
                cout << endl;
				break;
            case 'p':
                cout << "*** " << command << " ***" << endl;
                if (root != NULL)
                {
                    root->printLevelOrder(root);
                }
                break;
			case 'q':
                cout << "end" << endl;
				return 0;
				break;
		}
	}
	return 0;
}