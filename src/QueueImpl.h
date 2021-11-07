//
// Created by shimeng on 2021/11/7.
//

#ifndef UNIT_TEST_QUEUEIMPL_H
#define UNIT_TEST_QUEUEIMPL_H

#include <cstdlib>

// Queue is a simple queue implemented as a singled-linked list.
// The element type must support copy constructor.
template <typename E>  // E is the element type
class Queue;

// Node is a node in a Queue, which consists of an element of
// type E and a pointer to the next node.
template <typename E>
class Node {
    friend class Queue<E>;

public:
    const E& element() const {return element_;}

    // Gets the next node in the queue.
    Node* next() {return next_;}
    const Node* next() const {return next_;}

explicit Node(const E& an_element)
        : element_(an_element), next_(nullptr) {}

private:

    // We disable the default assignment operator and copy c'tor.
    const Node& operator = (const Node&);
    Node(const Node&) {}

    E element_;
    Node* next_;
};

template <typename E>
class Queue {
public:
    Queue() : head_(nullptr), last_(nullptr), size_(0) {}

    ~Queue() { this->clear(); }

    void clear() {
        if (size_ > 0) {
            // 1. Deletes every node.
            Node<E>* node = head_;
            Node<E>* next = node->next();
            for (; ;) {
                delete node;
                node = next;
                if (node == nullptr) break;
                next = node->next();
            }

            // 2. Resets the member variables.
            head_ = last_ = nullptr;
            size_ = 0;
        }
    }

    size_t size() const { return size_; }

    Node<E>* head() { return head_; }
    const Node<E>* head() const { return head_; }

    Node<E>* last() { return last_; }
    const Node<E>* last() const { return last_; }

    // Adds an element to the end of the queue.  A copy of the element is
    // created using the copy constructor, and then stored in the queue.
    // Changes made to the element in the queue doesn't affect the source
    // object, and vice versa.
    void enqueue(const E& element) {
        Node<E>* new_node = new Node<E>(element);

        if (size_ == 0) {
            head_ = last_ = new_node;
            size_ = 1;
        } else {
            last_->next_ = new_node;
            last_ = new_node;
            size_++;
        }
    }

    E* dequeue() {
        if (size_ == 0) {
            return nullptr;
        }

        const Node<E>* const old_head = head_;
        head_ = head_->next_;
        size_--;
        if (size_ == 0) {
            last_ = nullptr;
        }

        E* element = new E(old_head->element());
        delete old_head;

        return element;
    }

    // Applies a function/functor on each element of the queue, and
    // returns the result in a new queue.  The original queue is not
    // affected.
    template <typename F>
    Queue* map(F function) const {
        Queue* new_queue = new Queue();
        for (const Node<E>* node = head_; node != nullptr;
             node = node->next_) {
            new_queue->enqueue(function(node->element()));
        }

        return new_queue;
    }

private:
    Node<E>* head_;
    Node<E>* last_;
    size_t size_;

    // We disallow copying a queue.
    Queue(const Queue&);
    const Queue& operator = (const Queue&);
};

#endif //UNIT_TEST_QUEUEIMPL_H
