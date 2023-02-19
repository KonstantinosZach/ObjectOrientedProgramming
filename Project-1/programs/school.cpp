#include "school_structure.h"
#include "input_data.h"

int const number_of_classrooms = number_of_floors*number_of_classes; // ο αριθμός όλων τον τάξεων στο σχολικό κτήριο
using namespace std;

int main(int argc, char **argv){

    int const C_class = atoi(argv[1]);  // class capacity
    int const C_yard = atoi(argv[2]);   // yard capacity
    int const C_stair = atoi(argv[3]);  // stair capacity
    int const C_Corr = atoi(argv[4]);   // corridor capacity

    SchoolBuilding school_building(C_class,C_stair,C_yard, C_Corr);

    // O αριθμός όλων των μαθητών
    int const all_students = C_class*number_of_classes*number_of_floors;

    Students** array_of_students;   // Ο πίνακας στον οπόιο θα εισαχθούν οι μαθητές που θα δημιουργθούν
    array_of_students = new Students*[all_students];

    Teachers** array_of_teachers;   // Ο πίνακας στον οπόιο θα εισαχθούν οι καθηγητές που θα δημιουργθούν
                                    // άμα δώσουμε σε 2 η περισσότερους καθηγητές την ίδια τάξη τότε το πρόγραμμα έχει undefined behavior
    array_of_teachers = new Teachers*[number_of_classes*number_of_floors];

    // Μεταβλητές που θα μας βοηθήσουν να δημιουργήσουμε τους μαθητές και τους καθηγητές στις παρακάτω for loops
    int index_of_names_students = 0;
    int index_of_names_teachers = 0;
    int current_student = 0;
    int current_teacher = 0;
    for(int current_floor=0; current_floor<number_of_floors; current_floor++){
        for(int current_class=0; current_class<number_of_classes; current_class++ ){

            array_of_teachers[current_teacher] = new Teachers(names_of_teachers[index_of_names_teachers], false, current_floor, current_class);
            current_teacher++;

            index_of_names_teachers++;
            if(index_of_names_teachers > 14) // O πίνακας names_of_teachers είναι μεγέθους 15 οπότε προσέχουμε μην υπερβούμε το όριο
                index_of_names_teachers = 0;

            for(int students=0; students<C_class; students++){

                array_of_students[current_student] = new Students(names_of_students[index_of_names_students], "out of school", current_floor, current_class);
                current_student++;

                index_of_names_students++;
                if(index_of_names_students > 35) // O πίνακας names_of_students είναι μεγέθους 36 οπότε προσέχουμε μην υπερβούμε το όριο
                    index_of_names_students = 0;
                
            }
        }

    }

    srand((unsigned) time(0));

    int students_left = all_students-1;     // το σύνολο από το οποιο θα επιλεγέται τυχαία ο μαθητής
    int student_index = 0;

    // Eδω "ανακατεύεται ο πίνακας των μαθητών που δημιουργήθηκε προηγουμένος"
    // για να επιτεχθεί η  τυχαιότητα που ζητάει η άσκηση
    for(int i=0; i<all_students; i++){

        // Aμα έχει μείνει μόνο ενας μαθητης δεν έχει νόημα η rand()
        if(students_left == 0){
            continue;
        }
        // Αλλιως επιλέγω τυχαία εναν μαθητη
        else{

            Students* student;  // ο μαθητής που θα αλλάξει θέση μέσα στον πίνακα

            // επιλέγω τυχαία έναν μαθητή(index) από το σύνολο την διαθέσιμων μαθητών
            student_index = (rand()%(students_left));

            // Αφου γίνει η επιλογή τότε αλλάζω τις θέσεις
            // μεταξύ αυτού που επιλέχθηκε και του τελευταίου από το διαθέσιμο σύνολο
            student = array_of_students[student_index];
            array_of_students[student_index] = array_of_students[students_left];
            array_of_students[students_left] = student;

            // και μειώνω το διαθέσιμο σύνολο
            students_left--;
        }
    }


    int classroom_full = 0;     // μετρητής που θα δείχνει αν όλες οι τάξεις γέμισαν από μαθητές
    int index_of_teacher = 0;   // μεταβλητή που θα δείχνει ποια θέση δασκάλου έχει επιλεχθεί
    int teachers_left = number_of_classrooms -1;  // μετρητής που θα δείχνει πόσοι καθηγητές έχουν μείνει
    bool stuck = false;         // false->οι μαθητες μπορουν να προχωρήσουν true->oι δεν μαθητες μπορουν να προχωρήσουν
    do{
        
        // Αμα τύχει το 1 τοτε βάζω μαθητές
        if(rand() % 2){

            if(!school_building.enter_school(array_of_students)){   //Aν επιστρέψει false θα διακόψω την διαδικασία καθως
                stuck = true;                                           // οι μαθητές δεν μπορούν να προσωρήσουν πουθενά μέσα στο σχολείο
                continue;
            }

            // Σε αυτό το σημείο ελέγχω άμα όλες οι τάξεις είναι γεμάτες(από το μέρος των μαθητών)
            // Διότι άμα είναι τότε θα πρέπει να διακόψουμε την διαδικασία
            classroom_full=0;
            for(int i=0; i<number_of_floors; i++){

                Floors* floor = school_building.get_floor(i);
                for(int j=0; j<number_of_classes; j++){

                    Classrooms* classroom = floor->get_classroom(j);
                    if(classroom->get_classroom_status()){  // αμα ειναι true->ειναι γεμάτη
                        classroom_full++;
                    }
                }
            }

            // Αμα ισχύει το if τοτε οι τάξεις γεμισαν από μαθητες
            if(classroom_full == number_of_classrooms){
                cout << "The classrooms area full of students" << endl;
                continue;
            }

        }
        // αλλιώς βάζω έναν τυχαίο καθηγητή
        else{

            // Aμα έχει μείνει μόνο ενας καθηγητής δεν έχει νόημα η rand()
            // Εχει γίνει η πρόβλεψη ο τελευταιος καθηγητής να βρίσκεται πάντα στην θεση 0
            Teachers* teacher;
            if(teachers_left == 0){
                teacher = array_of_teachers[0];
            }
            // Αλλιως επιλέγω τυχαία εναν καθηγητή
            else{
                // τυχαία από το σύνολο την διαθέσιμων καθηγητών
                index_of_teacher = (rand()%(teachers_left));

                // Αφου γίνει η επιλογή τότε αλλάζω τις θέσεις
                // μεταξύ αυτού που επιλέχθηκε και του τελευταίου από το διαθέσιμο σύνολο
                teacher = array_of_teachers[index_of_teacher];
                array_of_teachers[index_of_teacher] = array_of_teachers[teachers_left];
                array_of_teachers[teachers_left] = teacher;
            }


            // Ετσι έχω αυτόν που θα βάλω στην αίθουσα στην τελευταία θέση από
            // το σύνολο των διαθέσιμων καθηγητών
            int nfloor = teacher->get_floor();          // παιρνω τον όροφο της τάξης του καθηγητή
            Floors* floor = school_building.get_floor(nfloor);
            
            int nclass = teacher->get_classroom();      //και την ταξη του καθηγητη στον όροφο
            Classrooms* classroom = floor->get_classroom(nclass);

            // Αμα δεν γίνει με επιτυχία το place στην τάξη θα εκτυπωθεί μύνημα λάθους
            classroom->place(teacher);
            array_of_teachers[teachers_left] = NULL;
            // Οι καθηγητής αυτός "αφαιρείται" γιατί ετσι και αλλιως δεν θα μπορέσει ποτέ να μπεί(εχει την ίδια ταξη με κάποιον άλλο)
            teachers_left--;

            // Αμα το παρακάτω if ειναι αληθες τότε έχουν μπει όλοι οι καθηγητές στις τάξεις τους
            // και η διαδικασία πρέπει να διακοπεί
            if(teachers_left < 0){
                cout << "All the teachers are in the classrooms" << endl;
                continue;
            }

        }
    }
    // Το παρακάτω while γίνεται όσο υπάρχουν καθηγητες και όσο οι τάξεις δεν εχουν γεμίσει και όσο
    // οι μαθητές μπορουν να προχωρήσουν μέσα στον χώρο του σχολείου
    while(teachers_left >= 0 && classroom_full != number_of_classrooms && stuck == false);

    //εκτυπωση τελικής κατάστασης
    school_building.print();
    
    // απελευθέρωση του χώρου που δεν έχει μπει στο χωρο school building
    for(int i=0; i<number_of_classrooms; i++){
        if(array_of_teachers[i] != NULL){
            delete array_of_teachers[i];
        }
    }
    delete[] array_of_teachers;

    for(int i=0; i<all_students; i++){
        if(array_of_students[i] != NULL){
            delete array_of_students[i];
        }
    }
    delete[] array_of_students;
    return 0;
}