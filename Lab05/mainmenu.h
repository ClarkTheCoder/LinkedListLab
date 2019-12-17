//
//  mainmenu.h
//  Lab05
//
//  Created by Carson Clark on 2019-10-10.
//  Copyright © 2019 Carson Clark. All rights reserved.
//

#ifndef mainmenu_h
#define mainmenu_h
// The MainMenu (.h & .cpp) file contains the function declarations used to
// present a main menu which allows a user to view, add, and remove employees.
// The list of employees is implemented with a linked list, and most of the
// processing functions get passed a pointer to the first element of the
// list (Employee* pHead).
#include <string>

// a struct to represent an Employee (each instance forms a node of a linked list
// used to store employees.
struct Employee {
    int id;
    std::string fname;
    Employee* next;
};

// A struct used to return multiple return values from the getNodeInfo() function.
struct NodeInfo {
    Employee* node;    // a pointer to an employee node.
    Employee* parent;    // a pointer to the node prior to the employee node (nullptr if node is at the front)
};

// display the main menu
void displayMainMenu();

// fetch and return an integer from user input
int getInt();

// output a list of all employees to the console
void viewEmployees(Employee* pHead);

// creates a new employee by allocating one from the heap and returning a pointer to it.
Employee* createEmployee(const std::string& fName);

// responsible for creating a new employee node, and adding it to the list
void addNewEmployee(Employee*& pHead, const std::string& fName);

// Searches through the list for a node with the given id.  Returns a nodeInfo struct pointing to the node and its parent.
NodeInfo getNodeInfo(Employee* pHead, int id);

// Removes an employee node with the given id from the list.
void removeEmployee(Employee*& pHead, int id);

// Given an int representing a menu choice, this will determine what should be done for each choice.
bool handleMenuInput(Employee*& pHead, int menuItemSelected);


#endif /* mainmenu_h */
