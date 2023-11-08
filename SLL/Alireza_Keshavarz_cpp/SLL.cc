#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <cassert>

// Singly Linked List Node
template <typename T>
class SNode {
public:
    T value;
    SNode* next;

    SNode(const T& _value, SNode* next_ptr=nullptr) : value(_value), next(next_ptr) {}
    SNode(SNode *next_ptr = nullptr) : next(next_ptr), value('\0') {}
};


// Linked List implementation
template <typename T>
class SLL {
private:
    SNode<T>* head;
    SNode<T>* tail;
    // `curr` points to the previous node of the "CURRENT" node
    SNode<T>* curr; // access to current node (it's a cursor)
    size_t count;


    /**
    * --------------------------------------------------------
    * | \0 | 01 | 02 | 03 | 04 | 05 | 06 | 07 | 08 | 09 | 10 |
    * --------------------------------------------------------
    *    ^                                                ^
    *   head                                            tail
    *   count = 10;
    *   total size is 11 nodes
    *
    */
    void init() {
        head = tail = curr = new SNode<T>;
        count = 0;
    }

    void removeAll() {  
        while (head != nullptr) {
            curr = head;
            head = head->next;
            delete curr;
        }
    }

public:
    SLL() { init(); }
    ~SLL() { removeAll(); }

    // TODO: implementing an iterator

    void print() const {
        SNode<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
            std::cout << temp->value << "-";
        }
        std::cout << "\n";

    };

    void clear() { removeAll(); init(); }

    void insert(const T& value) {
        curr->next = new SNode<T>(value, curr->next);
        if (tail == curr)
            tail = curr->next;
        count++;
    }
    void insert(const T& value, int index) {
        auto curr_temp_addr = curr;
        this->moveToIndex(index);
        curr->next = new SNode<T>(value, curr->next);
        if (tail == curr)
            tail = curr->next;
        count++;
        curr = curr_temp_addr;
    }

    void append(const T& value) {
        tail = tail->next = new SNode<T>(value, nullptr);
        count++;
    }

    T remove() {
        assert((curr->next != nullptr) && "Nothing");

        T value = curr->next->value;   // hold the value to return
        SNode<T>* temp = curr->next;    // hold to be deleted node
        if (tail == curr->next) {
            tail = curr;               // reset tail
        }

        curr->next = curr->next->next; // remove from list
        delete temp;
        count--;
        return value;
    }

    T remove(int index) {
        auto curr_temp_addr = curr;
        this->moveToIndex(index);
        assert((curr->next != nullptr) && "Nothing");

        T value = curr->next->value; // hold the value to return
        SNode<T>* temp = curr->next;  // hold to be deleted node
        if (tail == curr->next) {
            tail = curr;             // reset tail
        }

        curr->next = curr->next->next;  // remove from list
        delete temp;
        count--;
        curr = curr_temp_addr;
        return value;
    }

    void moveToStart() { curr = head; }
    void moveToEnd()   { curr = tail; }

    void prev() {                 // it's O(n) time complexity
        if (curr == head) return; // already at head
        SNode<T>* temp = head;     // for traversing
        while (temp->next != curr) {
            temp = temp->next;
        }
        curr = temp;
    }

    void next() {                 // it's O(1) time complexity
        if (curr != tail)         // already at tail
            curr = curr->next;
    }

    SNode<T>* getNodePointer() const {
        return curr->next;
    }

    size_t length() const {
        return count;
    }

    size_t currIndex() const {
        SNode<T>* temp = head;
        size_t i;
        for (i=0; curr != temp; ++i) {
            temp = temp->next;
        }
        return i;
    }

    void moveToIndex(int index)  {
        if (index < 0 || index > count) {
            std::cout << "Index out of bounds\n";
            return;
        }
        curr = head;
        for (int i=0; i<index; ++i) {
            curr = curr->next;
        }
    }

    const T& getValue() const {
        if (curr->next == nullptr) {
            assert((curr->next != nullptr) && "Nothing");
        }

        return curr->next->value;
    }
};
