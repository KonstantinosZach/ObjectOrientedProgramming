#pragma once
#include <iostream>
#include <cstring>

const int number_of_floors = 3;         //ο αριθμός των ορόφων του σχολείου
const int classrooms_per_floor = 6;     //ο αριθμός των τάξεων σε κάθε όροφο

// Μια κλάση η οποία περιέχει τα χαρακτηριστικά ενός ανθρώπου του σχολείου
//(κοινά χαρακτηριστικά και λειτουργίες των μαθητών και των δασκάλων)
// Είναι abstract καθώς έχει τον ρόλο της base class για την δημιουργία των Students
class Person{
    private:
        std::string name;
        int classroom_id;
        int floor_number;
        bool in_class;
    protected:
        Person(std::string name, int classroom_id, int floor_number, bool in_class, int counter_of_fatigue);
        virtual ~Person() = 0;      //Tην κάνουμε abstract
        int counter_of_fatigue;
    public:
        void print(std::string type = "full_info")const;
        int get_classroom_id()const;
        int get_floor_number()const;
        void set_in_class_state(bool state);
};

// Μια κλάση η οποία περιγράφει τον μαθητή του σχολείου
//(κοινές λειτουργίες μεταξύ των Juniors και Seniors students)
//Είναι και αυτή abstract γιατί δεν θέλουμε απλά αντικείμενα Students (θελουμε juniors ή seniors)
class Student: public Person{
    public:
        Student(std::string name, int classroom_id, int floor_number, bool in_class, int counter_of_fatigue);
        virtual ~Student()=0;        //Tην κάνουμε abstract
        virtual void attend(int hours)=0;
};

class Teacher: public Person{
    private:
        static int rate_of_fatigue;
    public:
        Teacher(std::string name, int classroom_id, int floor_number, bool in_class, int fatigue);
        ~Teacher();
        void teach(int hours);
        static void set_rate_of_fatigue(int rate);
};


class Junior: public Student{
    private:
        static int rate_of_fatigue;
    public:
        Junior(std::string name, int classroom_id, int floor_number, bool in_class, int counter_of_fatigue);
        void attend(int hours);
        static void set_rate_of_fatigue(int rate);

};

class Senior: public Student{
    private:
        static int rate_of_fatigue;
    public:
        Senior(std::string name, int classroom_id, int floor_number, bool in_class, int counter_of_fatigue);
        void attend(int hours);
        static void set_rate_of_fatigue(int rate);
};

// Μια κλάση η οποία περιέχει τα χαρακτηριστικά ενός χώρου του σχολείου
//(κοινά χαρακτηριστικά και λειτουργίες μεταξύ των yard,stairs και corridor)
// Είναι abstract καθώς έχει τον ρόλο της base class για την δημιουργία των yard,stairs και corridor
class Area{
    protected:
        Student* temp_student;
        Area();
        virtual ~Area() = 0;     //Tην κάνουμε abstract
        virtual void enter(Student* temp_student);
        virtual Student* exit();
};

class Yard: public Area{
    friend class SchoolBuilding;    //Στις λειτουργίες της έχει πρόσβαση μόνο η κλάση SchoolBuilding
    private:
        Yard();
        ~Yard();
        void enter(Student* temp_student);
        Student* exit();
};

class Stair: public Area{
    friend class SchoolBuilding;
    private:
        Stair();
        ~Stair();
        void enter(Student* temp_student);
        Student* exit();
};

class Corridor: public Area{
    friend class Floor;
    private:
        Corridor();
        ~Corridor();
        void enter(Student* temp_student);
        Student* exit();
};

// Μια κλάση η οποία περιέχει τα χαρακτηριστικά μιας τάξης του σχολείου
// Αποτελεί container(μαθητές και καθηγητή) και οχι κλάση που χρειάζεται inheritance
// Θέλουμε να αποφύγουμε την δημιουργία αντικειμένων Classroom στην main οπότε
// την κάνουμε friend με την Floor και κρατάμε privite όλα τα στοιχεία της
class Classroom{
    friend class Floor;         //Στις λειτουργίες της έχει πρόσβαση μόνο η κλάση Floor
    private:
        int number_of_students;
        Student** students;
        Teacher* teacher;
        Classroom(int number_of_students);
        ~Classroom();
        void enter(Student* student);
        void enter(Teacher* teacher);
        void operate(int hours);
        void print()const;
};

// Μια κλάση η οποία περιέχει τα χαρακτηριστικά του ορόφου του σχολείου
// Αποτελεί container(διάδρομος και τάξεων) και οχι κλάση που χρειάζεται inheritance
// Θέλουμε να αποφύγουμε την δημιουργία αντικειμένων Floor στην main οπότε
// την κάνουμε friend με την SchoolBuilding και κρατάμε privite όλα τα στοιχεία της
class Floor{
    friend class SchoolBuilding;
    private:
        Corridor* corridor;
        Classroom** classrooms;
        Floor(int classroom_capacity);
        ~Floor();
        void enter(Student* temp_student);
        void enter(Teacher* teacher);
        void operate(int hours);
        void print()const;
};

// Mια κλάση που περιγράφει το σχολικό κτήριο
// Αποτελεί container(προαύλιο, σκάλες και όροφοι) και οχι κλάση που χρειάζεται inheritance
class SchoolBuilding{
    private:
        Yard* school_yard;
        Stair* school_stair;
        Floor** school_floor;
    public:
        SchoolBuilding(int students_per_classroom,int junior_rate, int senior_rate, int teacher_rate);
        ~SchoolBuilding();
        void enter(Student* temp_student);
        void place(Teacher* teacher);
        void print()const;
        void operate(int hours);
        static void set_rates_of_fatigue(int junior_rate, int senior_rate, int teacher_rate);
};
