#pragma once
#include <iostream>
#include "LinkedList.h"

typedef class student* Student;
// Mια class που περιγράφει έναν μαθητή
class student{
    private:
        std::string name;       // Ονομα μαθητή
        std::string gender;     // Γένος μαθητή
        int classroom_id;       // Αριθμός της τάξης του
        int personal_id;        // Αριθμός προσωπικής ταυτότητας
        bool in_sequence;       // Αμα βρίσκεται στην ακολουθία ή όχι
        bool rude;              // Αμα είναι άτακτος ή οχι
    public:
        student(std::string name, std::string gender, int classroom_id, int personal_id);
        ~student();
        void print()const;
        std::string get_gender()const;
        bool get_status()const;             // Επιστρέφει true αν είναι σε ακολουθία και false αν δεν είναι
        void set_status(bool status);       // Θέτει άμα βρισκεται σε ακολουθία ή οχι
        int get_id()const;
        int get_classroom_id()const;
        void set_rude_status(bool status);  // Θέτει άμα είναι άτακτος ή οχι
        bool get_rude_status()const;        // Επιστρέφει true αν είναι άτακτος και false αν δεν είναι
};

typedef class pair* Pair;
// Mια class που περιγράφει έναν ζευγος μαθητών
class pair{
    private:
        Student left_student;       // Ο μαθητής που βρίσκεται αριστερά στην ακολουθίας
        Student right_student;      // Ο μαθητής που βρίσκεται δεξία στην ακολουθίας
    public:
        pair(Student left_student, Student right_student);
        ~pair();
        Student get_student(std::string position)const;                 // Παιρνουμε τον μαθητή στα δεξιά ή στα αριστερά
        void set_student(std::string position, Student some_student);   // Για να βάλουμε ένα μαθητή σε ένα ζευγάρι 
                                                                        // πρέπει να πούμε και αν θα μπει αριστερά ή δεξία
        void print()const;
        
};

typedef class classroom* Classroom;
// Mια class που περιγράφει μια τάξη
class classroom{
    private:
        int disorder_count;             // Ο μετρητής αταξίας
        LinkedList<Pair>* sequence;     // Μια λίστα από ζευγάρια που αποτυπώνει την ακολουθία της τάξης
        int capacity;                   // Η χωρητικότητα της τάξης
        Student* array_of_students;     // Ένας πίνακας που περιέχει τους μαθητές που ανήκουν στην τάξη
    public:
        classroom(LinkedList<Pair>* sequence, int classroom_capacity);
        ~classroom();
        bool enter_student(Student some_student);       // Γίνεται η εισαγωγή του μαθητή στην τάξη
        void make_sequence();                           // Δημιουργείται η ακολουθία από τους μαθητές της τάξης
        LinkedList<Pair>* get_sequence()const;          // Επιστρέφει την ακολουθία
        Student get_student(int student_id)const;       // Επιστρέφει τον μαθητή με το συγκεκριμένο id
        void disorder_modifier(int level);              // Αυξάνει τον μετρητή αταξίας
        int get_disorder_count()const;                  // Επιστρέφει τον μετρητή αταξίας
        void print()const;                              // Εκτυπώνει την τάξη
};

typedef class school* School;
// Mια class που περιγράφει τον παιδικό σταθμό
class school{
    private:
        Classroom* classrooms;              // Ένας πίνακας από τις τάξεις του σχολείου
        LinkedList<Classroom>* sequence;    // Μια λίστα από τις τάξεις του σχολείου
        int number_of_classrooms;           // Ο αριθμός των τάξεων του σχολείου
        int classroom_capacity;             // Η χωριτκότητα των τάξεων του σχολείου
    public:
        school(int number_of_classrooms, int classroom_capacity);
        ~school();
        Classroom get_classroom(int index)const;
        bool enter_classroom(Student some_student, int index);          // Γίνεται η εισαγωγή του μαθητή στην τάξη
        void make_class_sequence(int classroom_index);                  // Δημιουργείται η ακολουθία συγκεκριμένης τάξης
        void make_class_sequence();                                     // Δημιουργούνται όλες οι ακολουθίες του σχολείου
        void make_school_sequence();                                    // Δημιουργείται η κεντρική ακολουθία του σχολείου
        void print_classroom_sequence()const;                           // Εκτυπώνονται όλες οι ακολουθίες του σχολείου
        void print_classroom_sequence(int index)const;                  // Εκτυπώνεται η ακολουθία της συγκεκριμένης τάξης
        void print_school_sequence(float T_quiet, float T_mess)const;   // Εκτυπώνονται όλες οι ακολουθίες του σχολείου μαζί και με τα ποσοστά
        void remove_pair_from_sequence(int classroom_id, int index);    // Διαγράφεται το ζεύγος(index) από την ακολουθία της τάξης(classroom_id)
        void school_transition();                                       // Γίνονται οι κατάληλες αντιμεταθέσεις πριν μετακινηθουν τα παιδια του σχολείου
        void student_transition(Pair some_pair, Student some_student, int classroom_id, int rude_level);
                                                                        // Πραγματοποεί κατάληλη αντιμετάθεση ενός άτακτου μαθητή με καποιον αλλο
        Student is_now_rude(int index);                                 // Μετατρέπει εναν μαθητή σε άτακτο
        void be_quiet();                                                // Μετατρέπει όλους τους άτακτους μαθητές σε ήσυχους
        void decide_transition(int rude_pair_counter,int scattered_rude_pairs, LinkedList<Pair>* some_sequence,
                                int pair_index, int classroom_index, bool last_pair);
                                                                        // Συναρτηση με βαση την οποία θα επιλέγεται σε ποια από τις περιπτώσεις
                                                                        // αντιμεταθέσεων βρισκόμαστε για τα ζευγάρια άτακτων παιδιών

};
