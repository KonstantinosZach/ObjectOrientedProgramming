#include <iostream>
#include <algorithm>    // std::random_shuffle
#include <vector>       // std::vector
#include <ctime>        // std::time
#include <cstdlib>      // std::rand, std::srand
#include "school.h"
#include "names.h"
using namespace std;

int main(int argc, char **argv){

    int const C_class = atoi(argv[1]);            // μαθητές ανα τάξη
    int const L_junior = atoi(argv[2]);           // βαθμός κούρασης των junior μαθητών
    int const L_senior = atoi(argv[3]);           // βαθμός κούρασης των senior μαθητών
    int const L_teacher = atoi(argv[4]);          // βαθμός κούρασης των καθηγητών
    SchoolBuilding school_building(C_class,L_junior,L_senior,L_teacher);

    // O αριθμός όλων των μαθητών και των δασκάλων
    int const all_students = C_class*classrooms_per_floor*number_of_floors;
    int const all_teachers = classrooms_per_floor*number_of_floors;

    vector<Student*> vector_of_students;   // To vector στο οπoιο θα εισαχθούν οι μαθητές που θα δημιουργθούν
    vector<Teacher*> vector_of_teachers;   // To vector στο οπoιο θα εισαχθούν οι καθηγητές που θα δημιουργθούν

    // Μεταβλητές που θα μας βοηθήσουν να δημιουργήσουμε τους μαθητές και τους καθηγητές στις παρακάτω for loops
    int index_of_names_students = 0;
    int index_of_names_teachers = 0;

    for(int current_floor=0; current_floor<number_of_floors; current_floor++){
        for(int current_class=0; current_class<classrooms_per_floor; current_class++ ){

            vector_of_teachers.push_back(new Teacher(names_of_teachers[index_of_names_teachers], current_class, current_floor, false, 0));

            index_of_names_teachers++;
            if(index_of_names_teachers > 14) // O πίνακας names_of_teachers είναι μεγέθους 15 οπότε προσέχουμε μην υπερβούμε το όριο
                index_of_names_teachers = 0;

            for(int students=0; students<C_class; students++){

                if(current_class < 3)
                    vector_of_students.push_back(new Junior(names_of_students[index_of_names_students], current_class, current_floor, false, 0));
                else
                    vector_of_students.push_back(new Senior(names_of_students[index_of_names_students], current_class, current_floor, false, 0));

                index_of_names_students++;
                if(index_of_names_students > 35) // O πίνακας names_of_students είναι μεγέθους 36 οπότε προσέχουμε μην υπερβούμε το όριο
                    index_of_names_students = 0;
                
            }
        }

    }

    std::srand(unsigned(std::time(0)));

    std::random_shuffle(vector_of_students.begin(), vector_of_students.end());
    std::random_shuffle(vector_of_teachers.begin(), vector_of_teachers.end());

    for(int i=0; i<all_students; i++)
        school_building.enter(vector_of_students[i]);

    for(int i=0; i<all_teachers; i++)
        school_building.place(vector_of_teachers[i]);

    int const N_hours = atoi(argv[5]);            // Η ώρες λειτουργίας του σχολείου

    school_building.operate(N_hours);
    
    school_building.print();

    return 0;
}