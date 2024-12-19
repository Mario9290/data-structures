#include "bst.hpp"
#include <stack>

BST::BST() {
	// Your code here...
	root = nullptr;
	size = 0;
	
}

BST::~BST() {
	// Your code here...
	//Dont need this
	
}

XPost* BST::createPost(float time, string content, int likes) 
{
	// Your code here...
	//newPost pointer pointing to a new instance of class in heap where it will be ready to modify and change all the data of the instance of this pointer 
	XPost* newPost = new XPost();
    newPost->postedTime = time;
    newPost->xContents = content;
    newPost->likes = likes;
    newPost->left = nullptr;
    newPost->right = nullptr;
    return newPost;

}

void BST::insertPost(float time, string content, int likes) 
{
	// Your code here...
	//Create new post pointer pointing to post
	XPost *newPost = createPost(time, content, likes);
	root = insertHelper(root, newPost);

}

XPost* BST::insertHelper(XPost* rt, XPost* pst) 
{
	// Your code here...
	//Check if the subtree is empty 
	if(rt == nullptr)
	{
		//Return the post
		return pst;
	}
	//Recursively call untill we return rt 

	//Check if the post to be inserted time is less 
	else if(pst->postedTime < rt->postedTime)
	{
		//Insert to left subtree
		rt->left = insertHelper(rt->left, pst);
	}
	//Check if posts to be inserted time is greater
	else if(pst->postedTime > rt->postedTime)
	{
		//Insert to the right subtree
		rt->right = insertHelper(rt->right, pst);
	}
	return rt;

}

void BST::displayPosts() 
{
	// Your code here...
	displayHelper(root);	//Passing in the root of the Userpost call 

}

void BST::displayHelper(XPost* rt) // Inorder Traversal
{
	// Your code here...
	//Recursively call until root is nullptr
	if(rt == nullptr)
	{
		return;
	}
	displayHelper(rt->left);
	cout << rt->xContents << endl;
	displayHelper(rt->right);
	
}

//Function return the most liked post in the BST
XPost* BST::mostPopular() 
{
	// Your code here...
	//Set mostLiked pointer of type XPost to nullptr
	XPost *mostLiked = nullptr;
	mostPopularHelper(root, mostLiked);
	return mostLiked;

}

//Pass pointer by reference (modify original memory location)
void BST::mostPopularHelper(XPost* rt, XPost*& mostLiked) 
{
	// Your code here...
	//Traverse the tree recursively until you reach the nullptr
	
	if(rt == nullptr)
	{
		return;
	}

	//Go left
	mostPopularHelper(rt->left, mostLiked);

	if(mostLiked)
	{
		if(rt->likes > mostLiked->likes)
		{
			mostLiked = rt;
		}
		
	}
	
	//Go right
	mostPopularHelper(rt->right, mostLiked);
}
