//
//  mainmenu.cpp
//  Lab05
//
//  Created by Carson Clark on 2019-10-10.
//  Copyright © 2019 Carson Clark. All rights reserved.
//

#include <stdio.h>
// See comments in MainMenu.h for general details on what each functin does.
#include <iostream>
#include "mainmenu.h"

// output the menu choices to the console.
void displayMainMenu()
{
    std::cout << "\n";
    std::cout << "--- MENU ---\n";
    std::cout << "1) View Employees\n";
    std::cout << "2) Add Employee\n";
    std::cout << "3) Remove Employee\n";
    std::cout << "0) Exit\n";
    std::cout << "-------------\n";
    std::cout << "Select:";
}


// Attempt to read an int from cin.
// Check if there was a failure, if so, return -1.
int getInt() {
    int x;
    std::cin >> x;
    if (std::cin.fail()) {
        std::cin.clear();
        std::cin.ignore(32767, '\n');
        x = -1;
    }
    return x;
}


// if pHead is a nullptr:
//    - print a "empty list" message to the user
// if pHead not a nullptr,
//        - create a pCurr variable to point to pHead,
//        - while pCurr is not a nullptr,
//                - print the id and name out to the console
//                - set pCurr to point to the next node.
void viewEmployees(Employee* pHead) {
    // TODO
    if (pHead == nullptr) {
        std::cout << "\n empty list \n";
    } else {
        Employee* pCurr = pHead;
        while (pCurr != nullptr) {
            std::cout << pCurr->id << pCurr->fname << std::endl;
            pCurr = pCurr->next;
        }
    }
}


// Use a static variable to generate unique employee id's with (initialize it &
// increment it every time this function is called).
// Dynamically allocate memory for an employee struct from the heap.
//         Initialize it with :
//                -the unique id,
//                -the fName passed in as a paramter,
//                -nullptr.
// Return the pointer to the new dynamically allocated Employee.
Employee* createEmployee(const std::string& fName) {
    // TODO
    static int uniqueID = 0;
    uniqueID++;
    Employee* pEmp = new Employee{uniqueID, fName, nullptr};

    return pEmp;
    // replace this, it is only here to allow this to compile
}


// First Create a new employee (by calling createEmployee())
// Insert the new employee at the front of the linked list
//        - point the new employee's next pointer to the existing head.
//        - point the existing head at the new employee
void addNewEmployee(Employee*& pHead, const std::string& fName) {
    // TODO
    Employee* pNewEmp = createEmployee(fName);
    // Inserting new employee at the front of the linked list
    // connect new node to existing node (pointing new next to old)
    // newEmpNext ---> phead
    pNewEmp->next = pHead;
    // connect head to new node by pointing head to new emp
    pHead = pNewEmp;
}


// Search through the linked list for a node whose id matches the id parameter
// Return a NodeInfo struct to tell the calling function details about your findings.
// Start by initializing its members to nullptr.
// Use an Employee* pCurr var to iterate through the linked list (while pCurr->id != id)
//
// If you find a match,
//        set your nodeInfo.node to the node you matched.
//        set your nodeInfo.parent to the parent of the node you matched *.
//        return nodeInfo
// If no match found simply return nodeInfo as is. (The calling function (removeEmployee())
// should interpret the nullptr vars to mean not found)
//
//        (* To track the parent, create a local Employee* pLast, set it to nullptr,
//        then update it to point to pCurr right before you move pCurr to point to the
//    next node. If you find a match, pLast will then be pointing to the parent.)
NodeInfo getNodeInfo(Employee* pHead, int id) {
    // TODO
    NodeInfo newInfoNode;
    newInfoNode.node = nullptr;
    newInfoNode.parent = nullptr;
    
    Employee* pCurr = pHead;
    Employee* pLast = nullptr;
    while (pCurr->id != id) {
        pLast = pCurr;
        pCurr = pCurr->next;
    }
    if (pCurr->id == id) {
        newInfoNode.node = pCurr;
        newInfoNode.parent = pLast;
    return NodeInfo{ newInfoNode.node, newInfoNode.parent };
    }
 
    return NodeInfo{ newInfoNode.node, newInfoNode.parent };    // temporary return value so that the project will compile
}

// If pHead is a nullptr, then there are no employees to remove, output an error message and return
// Try to find a node with the given id (use getNodeInfo()).
// If not found, output an error message and return
// If found:
//        If pHead is the same as the node we found for the id, (it means the node we found is
//    the first one in the list). This is a special case:
//            -Set the pHead to node->next (The first param is a reference so that we can,
//               change the address that pHead points to and have it affect the caller).
//            -Return the memory of the node we want to delete to the heap
//        otherwise
//            (the node we found isn't the first one - it should theoretically have a parent)
//            -If the parent is a nullptr, print an error message (this should never happen, but we should check)
//            -If the parent is not a nullptr
//                -Set the parent's next pointer to the next pointer of the node we want to delete
//                -Output a "removed id: #" message to the console
//                -Deallocate memory from node back to the heap.

void removeEmployee(Employee*& pHead, int id) {
    if (pHead == nullptr) {
        std::cout << "No employee found";
        return;
    }
    Employee* pCurr = pHead;
    Employee* pLast = nullptr;
    
    while (pCurr->id != id) {
        pLast = pCurr;
        pCurr = pCurr->next;
    }

    getNodeInfo(pCurr, id);
    if (pHead == pCurr) {
        pHead = pCurr->next;
        delete pCurr;
    }
    else {
    if (pLast == nullptr) {
        std::cout << "Error";
    }
    else {
        pLast->next = pCurr->next;
        std::cout << "removed id: " << id;
        delete pCurr;
    }
}

}





// This function is called when a user picks a selection from the menu.
// It determines what action to take depending on the menuItemSelected, and calls
// the appropriate function.
// Returns true the selection was a request to exit menu, false otherwise.
bool handleMenuInput(Employee*& pHead, int menuItemSelected)
{
    bool exitRequest{ false };

    switch (menuItemSelected)
    {
    case 1:
        std::cout << ">> View Employees:\n";
        viewEmployees(pHead);
        break;
    case 2:
    {
        std::cout << ">> Add Employee:\n";
        std::cout << "Enter first name:";
        std::string fName;
        std::cin >> fName;
        addNewEmployee(pHead, fName);
    }
    break;
    case 3:
        std::cout << ">> Remove Employee:\n";
        std::cout << "Enter id:";
        int id;
        std::cin >> id;
        removeEmployee(pHead, id);
        break;
    case 0:
        std::cout << "Exiting\n";
        exitRequest = true;
        break;
    default:
        std::cout << "Invalid input.\n";
        break;
    }
    return exitRequest;
}

