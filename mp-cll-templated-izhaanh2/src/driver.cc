#include <iostream>

#include "circular-linked-list.hpp"

int main() {
    CircularLinkedList<int> list;
    list.InsertInOrder(5);
    list.InsertInOrder(4);
    list.InsertInOrder(2);
    list.InsertInOrder(3);
    list.InsertInOrder(9);

    CircularLinkedList cll = list;

    std::cout << cll << std::endl;
}
