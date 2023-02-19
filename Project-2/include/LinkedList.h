// A generic Linked List
#pragma once
// declaring node struct
template<typename T>
struct node {
    node<T>* next;
    T data;
};

// declaring linked list class
template<typename T>
class LinkedList{
    private:
        node<T>* head;
        node<T>* last;
        int size;
    public:
        LinkedList<T>();
        ~LinkedList();
        void add(T data);
        void remove(int index);
        T get(int index)const;
        T get_last()const;
        int get_size()const;
};