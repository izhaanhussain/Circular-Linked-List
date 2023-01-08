#ifndef CIRCULAR_LINKED_LIST_HPP
#define CIRCULAR_LINKED_LIST_HPP

#include <iostream>

#include "node.hpp"

enum class Order { kASC, kDESC };

template <typename T>
class CircularLinkedList {
public:
  CircularLinkedList() = default;
  CircularLinkedList(const CircularLinkedList<T>& source);
  CircularLinkedList<T>& operator=(const CircularLinkedList<T>& source);
  ~CircularLinkedList();

  void InsertInOrder(const T& data);
  void FirstInsert(const T& data);
  void SecondInsert(const T& data);
  void ThirdInsertASC(const T& data);
  void ThirdInsertDES(const T& data);
  void Reverse();

  template <typename U>
  friend std::ostream& operator<<(std::ostream& os,
                                  const CircularLinkedList<U>& cll);

private:
  Node<T>* head_ = nullptr;
  Node<T>* tail_ = nullptr;
  Order node_order_ = Order::kASC;
};

template <typename T>
CircularLinkedList<T>::CircularLinkedList(const CircularLinkedList<T>& source) {
  this -> ~CircularLinkedList();
  node_order_ = source.node_order_;
  if (source.head_ != nullptr) {
    Node<T>* source_curr = source.head_;
    head_ = new Node<T>(source.head_ -> data);
    Node<T>* current = head_;
    while (source_curr -> next != source.head_) {
      current -> next = new Node<T>(source_curr -> next -> data);
      source_curr = source_curr -> next;
      current = current -> next;
    }
    current -> next = head_;
    tail_ = current;
  }
}

template <typename T>
CircularLinkedList<T>& CircularLinkedList<T>::operator=(const CircularLinkedList<T>& source) {
  if (this == &source) {
    return *this;
  }
  if (tail_ != nullptr) {
    tail_ -> next = nullptr;
  }
  Node<T>* tmp = head_;
  while (tmp != nullptr) {
    tmp = head_ -> next;
    delete head_;
    head_ = tmp;
  }
  head_ = nullptr;
  tail_ = nullptr;
  node_order_ = source.node_order_;
  if (source.head_ != nullptr) {
    Node<T>* source_curr = source.head_;
    head_ = new Node<T>(source.head_ -> data);
    Node<T>* current = head_;
    while (source_curr -> next != source.head_) {
      current -> next = new Node<T>(source_curr -> next -> data);
      source_curr = source_curr -> next;
      current = current -> next;
    }
    current -> next = head_;
    tail_ = current;
  }
  return *this;
}

template <typename T>
CircularLinkedList<T>::~CircularLinkedList() {
  if (tail_ != nullptr) {
    tail_ -> next = nullptr;
  }
  Node<T>* tmp = head_;
  while (tmp != nullptr) {
    tmp = head_ -> next;
    delete head_;
    head_ = tmp;
  }
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const CircularLinkedList<T>& cll) {
  Node<T>* iter = cll.head_;
  // empty list condition
  if (iter == nullptr) {
    os << "Empty list";
    return os;
  }
  // non-empty list condition
  do {
    os << iter->data << '\t';
    iter = iter->next;
  } while (iter != cll.head_);
  return os;
}

template <typename T>
void CircularLinkedList<T>::InsertInOrder(const T& data) {
  if (head_ == nullptr) {
    FirstInsert(data);
  } else if (tail_ == head_) {
    SecondInsert(data);
  } else {
    if (node_order_ == Order::kASC) {
      ThirdInsertASC(data);
    } else {
      ThirdInsertDES(data);
    }
  }
}

template <typename T>
void CircularLinkedList<T>::FirstInsert(const T& data) {
  auto tmp = new Node(data);
  head_ = tmp;
  tail_ = head_;
  tail_ -> next = head_;
}

template <typename T>
void CircularLinkedList<T>::SecondInsert(const T& data) {
  if ((data <= head_ -> data && node_order_ == Order::kASC) || (data >= head_ -> data && node_order_ == Order::kDESC)) {
    Node<T>* tmp = new Node(data);
    tail_ = head_;
    head_ = tmp;
    tail_ -> next = head_;
    head_ -> next = tail_;
  } else {
    Node<T>* tmp = new Node(data);
    tail_ = tmp;
    tail_ -> next = head_;
    head_ -> next = tail_;
  }
}

template <typename T>
void CircularLinkedList<T>::ThirdInsertASC(const T& data) {
  Node<T>* add = new Node<T>(data);
  Node<T>* current = head_;
  Node<T>* previous = head_;
  do {
    if (data > current -> data) {
      if (current != tail_) {
        previous = current;
        current = current -> next;
      } else {
        add -> next = tail_ -> next;
        tail_ -> next = add;
        tail_ = add;
        return;
      }
    } else {
      if (current == head_) {
        add -> next = current;
        tail_ -> next = add;
        head_ = add;
        return;
      } else {
        add -> next = current;
        previous -> next = add;
        return;
      }
    }
  } while (head_ != tail_);
}

template <typename T>
void CircularLinkedList<T>::ThirdInsertDES(const T& data) {
  Node<T>* add = new Node<T>(data);
  Node<T>* current = head_;
  Node<T>* previous = head_;
  do {
    if (data < current -> data) {
      if (current != tail_) {
        previous = current;
        current = current -> next;
      } else {
        add -> next = tail_ -> next;
        tail_ -> next = add;
        tail_ = add;
        return;
      }
    } else {
      if (current == head_) {
        add -> next = current;
        tail_ -> next = add;
        head_ = add;
        return;
      } else {
        add -> next = current;
        previous -> next = add;
        return;
      }
    }
  } while (head_ != tail_);
}

template <typename T>
void CircularLinkedList<T>::Reverse() {
  if (head_ != nullptr) {
    Node<T>* previous = head_;
    Node<T>* current = head_ -> next;
    while (current != head_) {
      Node<T>* tmp = current -> next;
      current -> next = previous;
      previous = current;
      current = tmp;
    }
    Node<T>* temp = tail_;
    tail_ = head_;
    head_ = temp;
    tail_ -> next = head_;
  }
  if (node_order_ == Order::kASC) {
    node_order_ = Order::kDESC;
  } else {
    node_order_ = Order::kASC;
  }
}

#endif