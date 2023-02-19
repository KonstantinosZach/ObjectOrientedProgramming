#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

int const number_of_floors = 3;
int const number_of_classes = 6; // per floor

// Μια κλάση που αναπαριστά έναν μαθητή
class Students{
    string name;
    string place;               // Μια ένδειξη για το σε ποιο χώρο βρίσκεται ο μαθητής
    int floor;                  // Ο αριθμός του floor που βρίσκεται η τάξη του μαθητή
    int classroom;              // Ο αριθμός της τάξης του μαθητή

    public:
    Students(string students_name, string current_place, int class_floor, int class_number );
    ~Students();
    void info()const;               // Εκτυπώνει τις πληροφορίες του μαθητή
    void print_name()const;         // Εκτυπώνει μόνο το όνομα του μαθητή
    int get_classroom()const;       // Παίρνει τον αριθμό της τάξης
    int get_floor()const;           // Παιρνει τον αριθμό του floor που βρίσκεται η τάξη
    void set_place(string place);   // Αλλάζει την ένδειξη για το που βρίσκεται ο μαθητής
};

// Μια κλάση που αναπαριστά έναν καθηγητή
class Teachers{
    string name;
    bool inclass;       // Μια ένδειξη για το αν βρίσκεται στην αίθουσα ο καθηγητής
    int floor;          // Ο αριθμός του floor που βρίσκεται η τάξη του καθηγητή
    int classroom;      // Ο αριθμός της τάξης του καθηγητη

    public:
    Teachers(string teachers_name, bool current_status, int class_floor, int class_number);
    ~Teachers();
    void info()const;
    void print_name()const;
    int get_classroom()const;
    int get_floor()const;
    void set_status(bool status);   // Επιστρέφει την ένδειξη για το αν βρίσκεται στην αίθουσα ο καθηγητής
};

// Μια κλάση που αναπαριστά μια τάξη
class Classrooms{
    Students** class_students;      // Ένας πίνακας που θα αποθηκεύει τους μαθητές της τάξης
    Teachers* teacher;              // Ο καθητής της τάξης
    int students;                   // Ο αριθμός των μαθητών που χωράει η τάξη
    bool class_full;                // Μια ένδειξη για το αν η τάξη είναι γεμάτη ή οχι από μαθητές
    public:
        Classrooms(int students);
        ~Classrooms();
        bool enter_classroom(Students* some_student);   // Συνάρτηση που βάζει έναν μαθητή στον πίνακα με τους μαθητές
        void set_classroom_status(bool status);         // Θέτει την ένδειξη για το αν είναι η τάξη γεμάτη ή οχι
        bool get_classroom_status()const;               // Επιστρέφει την ένδειξη για το αν είναι η τάξη γεμάτη ή οχι
        bool is_classroom_full();                       // Ελέγχει άμα η τάξη είναι γεμάτη ή όχι
        bool place(Teachers* teacher);                  // Τοποθετεί τον καθηγητή στην τάξη
        Teachers* get_teacher()const;                   // Επιστρέφει τον καθηγητή της τάξης
        void print()const;                              // Εκτυπώνει μαθητές και καθηγητές της τάξης
};

// Μια κλάση που αναπαριστά εναν διαδρομο
class Corridors{
    int max_capacity;                           // Η χωρητικότητα του διαδρόμου
    Students** array_of_students;               // Ο πίνακας με τους μαθητές που βρίσκονται στον διαδρομο
    public:
        Corridors(int corr_capacity);
        ~Corridors();
        void set_capacity(int corr_capacity);           // Οριζει την χωρητικότητα
        int get_capacity()const;                        // Επιστρέφει την χωρητικότητα
        bool enter_corridor(Students* some_student);    // Βάζει έναν μαθητή στον διαδρομο αν γίνεται
        bool exit_corridor(int index=0);                // Βγάζει εναν μαθητη από τον διαδρομο αν γίνεται
        Students* get_student(int index=0)const;        // Επιστρέφει έναν μαθητή με το index να αντιστοιχεί στην θέση του στον πίνακα
        void print()const;                              // Εκτυπώνει τους μαθητές του διαδρόμου
};

// Μια κλάση που αναπαριστά το προαύλιο
class Yard{
    int max_capacity;                   // Η χωρητικότητα του προαυλίου
    Students** array_of_students;       // Ο πίνακας με τους μαθητές που βρίσκονται στο προαύλιο

    public:
        Yard(int yard_capacity);
        ~Yard();
        void set_capacity(int yard_capacity);
        int get_capacity()const;
        bool enter_yard(Students* some_student);
        bool exit_yard(int index=0);
        Students* get_student(int index=0)const;
        void print()const;
};

// Μια κλάση που αναπαριστά το κλιμακοστάσιο
class Stairs{
    int max_capacity;               // Η χωρητικότητα του κλιμακοστασίου
    Students** array_of_students;   // Ο πίνακας με τους μαθητές που βρίσκονται στο κλιμακοστάσιο
    public:
        Stairs(int stair_capacity);
        ~Stairs();
        void set_capacity(int stair_capacity);
        int get_capacity()const;
        bool enter_stairs(Students* some_student);
        bool exit_stairs(int index=0);
        Students* get_student(int index=0)const;
        void print()const;
};

// Μια κλάση που αναπαριστά εναν όροφο
class Floors{
    Classrooms** floor_classrooms;      // Ένας πίνακας με τις τάξεις που έχει ο όροφος
    Corridors* corridor;                // Ο διαδρομος που έχει ο όροφος
    public:
        Floors(int students, int corridors_capacity);
        ~Floors();
        Classrooms* get_classroom(int index)const;      // Επιστρέφει την τάξη από τον πίνακα 
        Corridors* get_corridor()const;                 // Επιστρέφει τον διαδρομο του ορόφου
        bool enter_floor(Students* some_student);       // Εισάγει έναν μαθητή στον διάδρομο του ορόφου αν χωράει
        void print()const;                              // Εκτυπώνει τους μαθητές του ορόφου
    
};

// Μια κλάση που αναπαριστά όλο το σχολειο
class SchoolBuilding {

    Floors** school_floors;             // Ένας πινακας με όλους τους ορόφους του σχολείου
    Stairs* stair;                      // Το κλιμακοστάσιο του σχολείου
    Yard* school_yard;                  // Το προαύλιο του σχολείου
    int all_students;                   // Ο αριθμός όλων των μαθητών του σχολείου
    Students** array_of_students;       // Ένας πίνακας με όλους τους μαθητές του σχολείου

    public:
        SchoolBuilding(int class_students, int stair_capacity, int yard_capacity, int corridor_capacity);
        ~SchoolBuilding();
        void print()const;
        Yard* get_yard()const;
        Stairs* get_stair()const;
        Floors* get_floor(int index)const;
        bool enter_school(Students* some_student);         // Εισάγει έναν μαθητή στο προαύλιο του σχολείου αν χωράει
        bool enter_school(Students** array_of_students);   // Εισάγει όσους μεθητές μπορεί μέχρι και τις τάξεις τους 
        bool exit_school(int index=0);                     // Αφαιρεί μαθητη από τον πίνακα όλων των μαθητών το οποίο δηλώνει οτι έχει μπει στο χώρο του σχολείου
        Students* get_student(int index=0)const;           // Επιστρέφει έναν μαθητή με το index να αντιστοιχεί στην θέση του στον πίνακα
};

