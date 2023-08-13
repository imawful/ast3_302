// Name: Kevin Barrios
// NSHE ID: 2001697903
// Assignment 3 the crane
//  traverse thru a binary tree to test if the tree is balanced 
#include "binaryTreeClasses.h"
#include <iostream>
#include <string>
using namespace std;


binTreeNode* buildTree();
double getObjectsWeight(binTreeNode *);
void deallocateTree(binTreeNode *);
int main()
{
	binTreeNode * root = buildTree();
	if(getObjectsWeight(root) != -1.0)
		cout << "Crane can lift the items\n";
	else 
		cout << "Well this is awkward\n";
	deallocateTree(root);
	return 0;
}

binTreeNode * buildTree()
{
	binTreeNode * daisy;
	string temp;
	cin >> temp;
	
	if(temp.size() == 0)
		return nullptr;//end of input 
	
	// we check if it's a joint or an object 
	
	//if joint 
	if(temp == "Joint")
	{
		// get arm lengths 
		int lArmLen, rArmLen;
		cin >> temp;
		lArmLen = stoi(temp);
		cin >> temp;
		rArmLen = stoi(temp);
		// create new node to store joint 
		daisy = new binTreeNode;
		
		// since this is a node we will recurssive call 
		// to add on additional nodes or leafs
		daisy->setLeft(buildTree());
		daisy->setRight(buildTree());
		// set arm lengths on the two childs
		binTreeNode * daisy_lengths = daisy->getLeft();
		daisy_lengths->setArmLength(lArmLen);
		daisy_lengths = daisy->getRight();
		daisy_lengths->setArmLength(rArmLen);
		// return back our tree 
		return daisy;
	}
	
	
	if(temp == "Goped")
	{
		// goped has wheels, engine, and tank
		double wheels, engine, tank;
		cin >> temp;
		wheels = stod(temp);
		cin >> temp;
		engine = stod(temp);
		cin >> temp;
		tank = stod(temp);
		
		//set our pointer to a new object with found values 
		daisy = new goped(wheels,engine,tank);
		daisy->setLeft(nullptr);
		daisy->setRight(nullptr);
		//leaf so return 
		return daisy;
	}
	
	if(temp == "Bike")
	{
		//we know we hit a leaf...
		// a bike only has its wheel weight and 
		// its frame weight 
		double wheels, frame;
		cin >> temp;
		wheels = stod(temp);
		cin >> temp;
		frame = stod(temp);
		
		// set our pointer to new object with it's values
		daisy = new bike(wheels, frame);
		daisy->setLeft(nullptr);
		daisy->setRight(nullptr);
		
		//because its a leaf we just return back
		return daisy;
	}
	
	if(temp == "Car")
	{
		//a car has wheels, engine, trans, and body
		double wheels, engine, trans, body;
		cin >> temp;
		wheels = stod(temp);
		cin >> temp; 
		engine = stod(temp);
		cin >> temp;
		trans = stod(temp);
		cin >> temp;
		body = stod(temp);
		
		//set our pointer to a new car with it's values 
		daisy = new car(wheels,engine,trans,body);
		daisy->setLeft(nullptr);
		daisy->setRight(nullptr);
		//leaf so return
		return daisy;
	}
	
	
	
	
	return nullptr;
}



double getObjectsWeight(binTreeNode * daisy)
{
	// first we check if the pointer is a joint 
	// if its not a joint we can just return the weight 
	if(daisy->getWeight() == 0.0)
	{
		//we have a joint 
		// we have to get weight on left and get weight on right 
		double leftWeight = getObjectsWeight(daisy->getLeft());
		double rightWeight = getObjectsWeight(daisy->getRight());
		
		// do the torque check 
		// retrieve arm lengths 
		int lArmLen, rArmLen;
		lArmLen = (daisy->getLeft())->getArmLength();
		rArmLen = (daisy->getRight())->getArmLength();
		// get the torques
		double lTorque, rTorque;
		lTorque = leftWeight * lArmLen;
		rTorque = rightWeight * rArmLen;
		
		if(lTorque == rTorque)
			return leftWeight + rightWeight;
		else 
			return -1.0;
	} 
	else 
		return daisy->getWeight();
}

void deallocateTree(binTreeNode * daisy)
{
	//if the pointer does not point to a node 
	//and its null then we return back 
	if(daisy == nullptr)
		return;
	
	// pointer is not null so we keep deallocating further
	// potential subtrees
	deallocateTree(daisy->getLeft());
	deallocateTree(daisy->getRight());
	
	delete daisy;
	
	return;
}
