#include "school.h"
#include "LinkedList.h"
#include "names.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

int main(int argc, char *argv[]){

    int number_of_classrooms = atoi(argv[1]);       // Ο αριθμός των τάξεων του παιδικού σταθμού
    int L = atoi(argv[2]);                          // Το πόσες φορές θα δημιουργήσουμε άτακτους μαθητές
    float T_quiet = atoi(argv[3])/100.0;            // Το ποσοστό που καθορίζει μια τάξη ήσυχη
    float T_mess = atoi(argv[4])/100.0;             // Το ποσοστό που καθορίζει μια τάξη άτακτη

    int const students_per_classroom = 7;           // Ο αριθμός των μαθητών σε κάθε τάξη στην αρχική φάση
    int index = 0;                                  // Μετρητής που θα μας βοηθήσει στην δημιουργία των μαθητών

    // Δημιουργούμε τον παιδικό σταθμό
    School kindergarden = new school(number_of_classrooms, students_per_classroom);
    // Ο κάθε μαθητής θα έχει και μια προσωπική id(αριθμό ταυτότητας)
    int student_id = 0;
    // Δημιουργούμε τους μαθητές και τους βάζουμε στον παιδικό σταθμό
    for(int i=0; i<number_of_classrooms; i++){
        for(int j=0; j<students_per_classroom; j++){

            // Ο πίνακας names_genders_of_students[] είναι της μορφής = {"name","gender",....,} δηλαδή ={"jack", "male", "maria", "female" , ... ,}
            Student some_student = new student(names_genders_of_students[index], names_genders_of_students[index+1], i, student_id);
            kindergarden->enter_classroom(some_student, i);

            student_id++;

            // προσέχουμε να μην βγούμε έξω από τα όρια του πίνακα
            index = index+2;
            if(index > 54)
                index = 0;
        }
    }

    // Τώρα δημιουργούμε τις ακολουθίες όλων των τάξεων (αν διναμε όρισμα κάποιον αριθμό τάξης θα
    // δημιουργούσαμε την ακολουθία μόνο για την συγκεκριμένη τάξη)
    kindergarden->make_class_sequence();

    // Τώρα δημιουργούμε την κεντρική ακολουθία του σχολείου που αποτελείται
    // από όλες τις ακολουθίες των τάξεων
    kindergarden->make_school_sequence();

    // Και την εκτυπώνουμε
    kindergarden->print_school_sequence(T_quiet, T_mess);

    // Eπειδή πρόκειται να μετακινηθούν τα τμήματα πρέπει
    // άμα υπάρχει περριτός αριθμός μαθητών να ελέγξουμε αν μπορουν να δημιουργηθούν ζευγάρια στην ακολουθία της 1ης τάξης
    kindergarden->school_transition();

    // Άμα θέλουμε μπορούμε να εκτυπώσουμε την καινούργια(κατά πάσα πιθανότητα) ακολουθία
    // kindergarden->print_school_sequence();    

    int number_of_all_students = number_of_classrooms*students_per_classroom;      // Ο αριθμός όλων των μαθητών του παιδικού σταθμού

    // Τωρα θέλοντας να πετύχουμε την τυχαιότητα στην επιλογή των άτακτων μαθητών
    // Δημιουργούμε έναν πίνακα με τα ids των μαθητών από τον οποίο θα επιλέγονται τυχαία οι άτακτοι μαθητές
    // (προφανώς αυτό δουλέυει μόνο όταν τα ids βρίσκονται μέσα στο όριο του αριθμού των μαθητών)
    int array_of_ids[number_of_all_students];
    for(int i=0; i<number_of_all_students; i++){
        array_of_ids[i] = i;
    }
    srand((unsigned) time(0));

    // Σε αυτό το loop επιλέγονται τυχαία οι άτακτοι μαθητές και μετά
    // γίνονται οι αντιμεταθέσεις για να γίνουν πάλι ήσυχοι οι μαθητές
    for(int i=0; i<L; i++){

        int ids_left = number_of_all_students-1;

        // επιλέγεται τυχαία ο αριθμός των άτακτων μαθητών
        int number_of_rude_students = (rand()%(number_of_all_students));
        std::cout << std::endl << "Rude students: " << number_of_rude_students << std::endl;

        // και μετά επιλέγονται τυχαία τόσοι άτακτοι μαθητές οι οποίοι και εκτυπώνονται
        for(int j=0; j<number_of_rude_students; j++){

            // Το id που επιλέγεται πηγαίνει στο τέλος του πίνακα έτσι ώστε να μην επιλεχθεί πάλι τυχαία
            // για αυτο και μειώνω το περιθώριο επιλογής σε κάθε επανάληψη
            int index = (rand()%(ids_left));
            int rude_id =  array_of_ids[index];
            array_of_ids[index] = array_of_ids[ids_left];
            array_of_ids[ids_left] = rude_id;

            // ενημερώνω τον παιδικό σταθμό ότι ο μαθητής με το συγκεκριμένο id είναι άτακτος
            kindergarden->is_now_rude(rude_id);
            ids_left--;
        }
        std::cout << std::endl;

        // Μόλις επιλεχθούν όλοι οι άτακτοι μαθητές κάνω τις ανιμεταθέσεις για να γίνει πάλι ησυχία
        kindergarden->be_quiet();

        // Και εκτυπώνεται η καινούργια ακολουθία των μαθητών του παιδικού σταθμού
        kindergarden->print_school_sequence(T_quiet, T_mess);

        // Ξαναβάζω σε σειρά τα ids των μαθητών
        for(int j=0; j<number_of_all_students; j++){
            array_of_ids[j] = j;
        }
    }

    // Και τέλος κάνω delete τον παιδικό σταθμό
    delete kindergarden;
}