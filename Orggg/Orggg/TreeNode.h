#pragma once
#include<vector>
using namespace std;

template <typename T>
class TreeNode
{
public:
	T data;
	int rating;

	vector<TreeNode *> children;

	TreeNode(T data,int rating)
	{
		this->data = data;
		
		this->rating = rating;
	}

};


