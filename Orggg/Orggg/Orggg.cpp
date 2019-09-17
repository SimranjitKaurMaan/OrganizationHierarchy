// Orggg.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include "pch.h"
#include "TreeNode.h"
using namespace std;

#include <iostream>
#include<queue>
#include<string>

void top10(TreeNode<string>* root)
{
	int count = 1;
	priority_queue<TreeNode<string>*, vector<TreeNode<string>*>> pq;
	queue<TreeNode<string>*>pendingNodes;
	pendingNodes.push(root);
	pq.push(root);
	while (!pendingNodes.empty())
	{
		TreeNode<string>* front = pendingNodes.front();
		pendingNodes.pop();
		for (int i = 0; i < front->children.size(); i++)
		{
			pendingNodes.push(front->children[i]);
			if (count < 10)
			{
				pq.push(front->children[i]);
				count++;
			}
			else
			{
				if (pq.top()->rating < front->children[i]->rating)
				{
					pq.pop();
					pq.push(front->children[i]);

				}
			}
		}


	}

	//display the 10 elements
	for (int i = 0; i < 10; i++)
	{
		cout << pq.top()->data << " "<< pq.top()->rating<<endl;
		pq.pop();
	}

}

void printLevelWise(TreeNode<string>* root)
{
	
	queue<TreeNode<string>*> pendingNodes;
	pendingNodes.push(root);
	while (!pendingNodes.empty())
	{
		TreeNode<string>* front = pendingNodes.front();
		std::cout << front->data << ":";
		pendingNodes.pop();
		for (int i = 0; i < front->children.size(); i++)
		{
		    cout << front->children[i]->data<<" "<<front->children[i]->rating << ",";
			pendingNodes.push(front->children[i]);
		}

		cout << endl;
	}


}




TreeNode<string>* takeInput()
{

	TreeNode<string>* root = new TreeNode<string>("CEO",5);

	queue<TreeNode<string>*> pendingNodes;
	pendingNodes.push(root);
	int n;
	string name;
	int rating;
	while (!pendingNodes.empty())
	{
		TreeNode<string>* front = pendingNodes.front();
		cout << "Number of subordinates of "<<front->data<<" ? ";
		cin >> n;
		pendingNodes.pop();
		for (int i = 0; i < n; i++)
		{
			cin >> name >> rating;
			TreeNode<string>* node = new TreeNode<string>(name,rating);
			front->children.push_back(node);
			pendingNodes.push(front->children[i]);
			
		}

		cout << endl;
	}

	return root;
}

void findLeaves(TreeNode<string>* root, vector<int>* ratings)
{
	if(root->children.size() == 0)
	{
		//cout << "rating added " << root->rating << endl;
		ratings->push_back(root->rating);
	}

	for (int i = 0; i < root->children.size(); i++)
	{
		findLeaves(root->children[i],ratings);
	}


}

void distributeBonus(string name,TreeNode<string>* root,int bonus)
{
	if (root == NULL)
	{
		return;
	}

	if (root->data == name)
	{
		vector<int>* ratings = new vector<int>();
		findLeaves(root,ratings);
		int totalRatings = 0;
		for (int i = 0; i < ratings->size(); i++)
			totalRatings += ratings->at(i);
		cout << "bonus of lowest children of " << root->data << " ";
		for (int i = 0; i < ratings->size(); i++)
		{
			cout<< (bonus * ratings->at(i)) / totalRatings<<" ";

		}
	}

	for (int i = 0; i < root->children.size(); i++)
	{
		distributeBonus(name, root->children[i], bonus);
	}
}

vector<string>* printHierarchy(string name,TreeNode<string>* root)
{
	if (root==NULL)
	{
         return NULL;
	}

	if (root->data == name)
	{
		vector<string>* path = new vector<string>();
		path->push_back(name);
		return path;
	}

	for (int i = 0; i < root->children.size(); i++)
	{
		vector<string>* smallAns=printHierarchy(name, root->children[i]);
		if (smallAns != NULL)
		{
			smallAns->push_back(root->data);
			return smallAns;
		}
	}

	return NULL;

}
//3 manager1 1 manager2 2 manager3 3 2 employee1 4 employee2 5 2 employee3 6 employee4 7 1 employee5 8 2 employee6 9 employee7 2 1 employee8 1 0 0 0 0 0 0
int main()
{
	TreeNode<string>* root = takeInput();
	printLevelWise(root);
	string findName = "";
	cin >> findName;
	vector<string>* hierarchy = printHierarchy(findName,root);

	for (int i = hierarchy->size()-1; i >=0; i--)
		cout << hierarchy->at(i) << " ";

	distributeBonus(findName, root, 100);
	top10(root);

}
