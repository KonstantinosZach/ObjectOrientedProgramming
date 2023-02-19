// A generic Linked List
#include "LinkedList.h"
#include <iostream>
/////////////////////// The type I will be using ///////////////////
#include "school.h"
template class LinkedList<Pair>;
template class LinkedList<Classroom>;
///////////////////////////////////////////////////////////////////


// declaring linked list class
template<typename T>
LinkedList<T>::LinkedList():head(NULL), last(NULL), size(0){ std::cout << "A list is created" << std::endl;}

template<typename T>
LinkedList<T>::~LinkedList(){

    std::cout << "A list is destroyed" << std::endl;

    node<T>* current_node = head;
    node<T>* next_node;

    // Διαγραφεί των node και των data της λίστας
    while(current_node != NULL){
        next_node = current_node->next;
        delete current_node->data;
        delete current_node;
        current_node = next_node;
    }
}

// Το add γίνεται στο τέλος της λίστας
template<typename T>
void LinkedList<T>::add(T data){
    //Aμα η λίστα είναι άδεια
    if(head == NULL){
        head = new node<T>;
        head->data = data;
        head->next = NULL;
        last = head;
    }
    else{
        // Αμα η λίστα έχει μόνο ένα στοιχείο
        if(head==last){
            last = new node<T>;
            last->data = data;
            last->next = NULL;
            head->next = last;
        }
        else{
            // Αμα η λίστα έχει παραπάνω από ένα στοιχείο
            node<T>* new_node = new node<T>;
            new_node->data = data;
            new_node->next = NULL;
            last->next = new_node;
            last = new_node;    
        }

    }
    size++;
}

// Επιστρέφει το data που βρίσκεται στην θέση index
template<typename T>
T LinkedList<T>::get(int index)const{
    if(index < size && index >= 0){
        int current_index = 0;
        node<T>* current_node = head;

        while(current_index != index){
            current_node= current_node->next;
            current_index++;
        }
        return  current_node->data;
    }
    else{
        return NULL;
    }
}

// Eπιστρέφει το size της λίστας
template<typename T>
int LinkedList<T>::get_size()const{return size;}

//Επιστρέφει το τελευταίο data της λίστας
template<typename T>
T LinkedList<T>::get_last()const{return last->data;}

// Κανει remove το node και delete το data του με βάσει το index
template<typename T>
void LinkedList<T>::remove(int index){

    if(index < size && index >= 0){
        int current_index = 0;
        node<T>* current_node = head;

        // Αν η λίστα έχει μόνο ένα στοιχείο
        if(size == 1){
            
            delete head->data;
            delete head;    // Κανουμε delete το head 
            head = NULL;
            last = NULL;
        }
        else{
            // Αν η λίστα έχει περισσότερα απο ένα στοιχεία
            // και θέλουμε να κανουμε remove το head
            if(index == 0){
                head = current_node->next;
                delete current_node->data;
                delete current_node;
            }
            else{
                while(current_index != (index-1)){
                    current_node= current_node->next;
                    current_index++;
                }
                //και θέλουμε να κανουμε remove το last
                if(index == (get_size()-1)){
                    delete last->data;
                    delete last;
                    current_node->next = NULL;
                    last = current_node;
                }
                //και θέλουμε να κανουμεremove κατι ενδιαμεσα
                else{
                    node<T>* middle_node = current_node->next;
                    current_node->next = middle_node->next;
                    delete middle_node->data;
                    delete middle_node;                      
                }
            }
        }
        size--;

    }
}

