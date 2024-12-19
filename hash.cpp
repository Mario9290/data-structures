// CPP program to implement hashing with chaining
#include<iostream>
#include<sstream>
#include "hash.hpp"
using namespace std;

HashTable::HashTable()
{
	//  Your code here

	this->tableSize = M;
    table = new XUser*[M];

	for (int i = 0; i < this->tableSize ; i++) {
        table[i] = nullptr;
    }
    numCollision = 0;
}

//Returns an instance of a new XUser struct
XUser* HashTable::createUser(string username, string userBio)
{
	//  Your code here
	//newUser pointer pointing to a new instance of class XUser in heap where it will be ready to modify and change all the data of the instance of this pointer 
    XUser* newUser = new XUser();
    newUser->username = username;
    newUser->userBio = userBio;
    newUser->postCount = 0;
    newUser->next = nullptr;
    newUser->bst = new BST(); //
    return newUser;

}

//'unsigned int' = integer that can never be negative
unsigned int HashTable::hashFunction(string username)
{
	//  Your code here
	//Variable to store the username ascii value
	int sum = 0;

	//Loop through username and add it to the variable 
	for(int i = 0; i<username.length(); i++)
    {
        sum = sum + username[i];
    }
    return sum % tableSize;
}



//function to insert a new user into hash table (posts inserted separately)
XUser* HashTable::insertUser(string username, string userBio)
{
	//  Your code here
	//Call searchUser function to check if user already exists
	//Pointer to that node
	XUser *Insert = searchUser(username);
	int index = hashFunction(username);
	XUser *creation = createUser(username, userBio);

	if(!Insert)
	{
		XUser *head = table[index];
		
		if(head)
		{
			numCollision++;
		}
		creation->next = table[index];
		table[index] = creation;
	}
	return creation;

}
	


XUser* HashTable::searchUser(string username)
{
	//  Your code here
	//Call hash function to get the bucket index of username 
	int userKey = hashFunction(username);

			//Set current to the head of the linked list 
			XUser* current = table[userKey];

			//Traverse through whole linked list
			while(current != nullptr)
			{
				//Check if the username matches
				if(current->username == username)
				{
					return current;
				}
					current = current->next;
			}
			return NULL;	//User does not exist

}

void HashTable::printUsers()
{
	//  Your code here
	XUser *temp;
	//Traverse through the hash table
	for(int i = 0; i < tableSize; i++ )	
	{
		temp = table[i];
		cout << i << "|" ;
		//Traverse the linked list until reaching the end 
		while(temp != nullptr)	
		{
			cout << temp->username << "--> ";
			temp = temp->next;
		}
		cout << "NULL"<< endl ; 
	}
}

void HashTable::printAllPostByUser(string username) 
{
	//  Your code here
	XUser *current = searchUser(username);
	//Traverse the hash table 
	if(current == nullptr)
	{
		cout << "User does not exist, try again..."  << endl;
		return;
	}
	else
	{
		cout << current->username << ":" << endl;
		cout << "| userBio: " << current->userBio << endl;
		cout << "| postCount: " << current->postCount << endl;
		cout << "| Posts: " << endl;
		current->bst->displayPosts();
	}

}

void HashTable::printMostLikedPost() 
{
	//  Your code here
	//Define two objects to access both classes and their data 
	XPost *mostLiked = nullptr;
	XUser *mostUser = nullptr;
	//Set counter to account for the most liked post
	int highestLike = 0;

	//Loop through the hash table 
	for(int i = 0; i < tableSize; i++)
	{
		//Start at the first index/bucket of the hash table and go into the linked list
		while(table[i])
		{
			//Check if the likes are higher
			if(table[i]->bst->mostPopular()->likes > highestLike)
			{
				//Update the variables 
				mostLiked = table[i]->bst->mostPopular();
				mostUser = table[i];
				highestLike = table[i]->bst->mostPopular()->likes;
			}
			table[i] = table[i]->next;
		}
	}
		// Print the most liked post if found
    if (mostLiked != nullptr) {
        cout << "Most liked post by: " << mostUser->username << endl;
        cout << "| userBio: " << mostUser->userBio << endl;
        cout << "| postCount: " << mostUser->postCount << endl;
        cout << "| Post:" << endl;
        cout << mostLiked->postedTime << ":" << endl;
        cout << "  __| likes: " << mostLiked->likes << endl;
        cout << "  __| " << mostLiked->xContents << endl;
    } else {
        // Print a message if no posts were found in the hash table
        cout << "No posts found in the hash table." << endl;
    }
}

int HashTable::longestChain() 
{
	//  Your code here
	//XUser pointer to point to XUser objects
	XUser *currentUser = nullptr;
	//Variable to hold the value of the bigget length of chain
	int biggestLength = 0;

	//Traverse through each bucket of the hash table 
	for(int i=0; i < tableSize; i++)
	{
		//Variable to hold the value of the bigget length of chain
		int bigLength = 0;
		//Set the currentUser to the bucket
		currentUser = table[i];	
		//Traverse through the linked list chain 
		while(currentUser != nullptr)
		{
			//Increment the counter 
			bigLength ++;	
			//Move to the next XUser post
			currentUser = currentUser->next;
		}
		//Check and update the biggestLength counter if the current chain is longer
		if(bigLength > biggestLength)
		{
			biggestLength = bigLength;
		}
	}
	return biggestLength;

}
    