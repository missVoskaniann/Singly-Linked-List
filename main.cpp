#include "sll.h"
#include <iostream>
#include <cstddef>
#include <stdexcept>

int main() {
    SinglyLinkedList<int> list1;
    list1.push_back(1);
    list1.push_back(3);
    list1.push_back(5);
    list1.push_back(7);

    SinglyLinkedList<int> list2;
    list2.push_back(2);
    list2.push_back(4);
    list2.push_back(6);

    std::cout << "List 1: ";
    list1.printList();
    std::cout << "List 2: ";
    list2.printList();

    SinglyLinkedList<int> mergedList;
    mergedList.mergeTwoSortedLinkedLists(list1, list2);
    std::cout << "Merged List: ";
    mergedList.printList();
    mergedList.reverse();
    std::cout << "Reversed Merged List: ";
    mergedList.printList();

    std::cout << "Reversed Merged List has cycle: " << (mergedList.hasCycle() ? "true" : "false") << std::endl;

    int middleValue = mergedList.getMiddleNode();
    std::cout << "Middle Node Value: " << middleValue << std::endl;

    try {
        int startPointValue = mergedList.getStartPoint();
        std::cout << "Start Point Value of the Cycle: " << startPointValue << std::endl;
    } catch (const std::exception& e) {
        std::cerr << e.what() << std::endl;
    }

    SinglyLinkedList<int> additionalList;
    additionalList.push_back(10);
    additionalList.push_back(20);
    additionalList.push_back(30);

    mergedList.insert(2, additionalList);
    std::cout << "Updated Merged List (insert list(10,20,30) in 2 pos): ";
    mergedList.printList();

    mergedList.deleteItem(4);
    std::cout << "Updated Merged List (delete 4): ";
    mergedList.printList();

    return 0;
}
