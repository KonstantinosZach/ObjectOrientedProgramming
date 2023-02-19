#include "school.h"
//Οι συναρτήσεις της κλάσης Person
//Δημιουργία του Person
Person::Person(std::string name, int classroom_id, int floor_number, bool in_class, int counter_of_fatigue):
        name(name), classroom_id(classroom_id), floor_number(floor_number), in_class(in_class), counter_of_fatigue(counter_of_fatigue){
}

//Καταστροφή του Person(dummy destructor για να καταφέρουμε να γίνει abstract)
Person::~Person(){}

// Εκτύπωση του Person
//όρισμα(default = "full_info") τότε θα εκτυπωθούν όλα τα στοιχεία του person
//όρισμα το "name" τοτε θα εκτυπωθεί μονο το name του person
void Person::print(std::string type)const{

    if(type.compare("full_info") == 0){
        std::cout << "name: " << name << " " << "classroom_id: " << classroom_id << " " << "floor number: " << floor_number;
        if(in_class)
            std::cout << " in class: true ";
        else
            std::cout << " in class: false ";
        std::cout << "fatigue: " << counter_of_fatigue << std::endl;
    }
    else if(type.compare("name") == 0){
        std::cout << name;
    }
}

int Person::get_classroom_id()const{return classroom_id;}

int Person::get_floor_number()const{return floor_number;}

void Person::set_in_class_state(bool state){in_class = state;}

//Οι συναρτήσεις της κλάσης Student
//Δημιουργία του Student
Student::Student(std::string name, int classroom_id, int floor_number, bool in_class, int counter_of_fatigue):
        Person(name, classroom_id, floor_number, in_class, counter_of_fatigue){
    std::cout << "A new Student is constructed" << std::endl; 
    print();
}

//Καταστροφή του Student
Student::~Student(){
    std::cout << "A Student to be destroyed" << std::endl;
    print();
}

//Οι συναρτήσεις της κλάσης Junior
//Δημιουργία του Junior
Junior::Junior(std::string name, int classroom_id, int floor_number, bool in_class, int counter_of_fatigue):
        Student(name, classroom_id, floor_number, in_class, counter_of_fatigue){
}

//Ο μετρητής της κούρασης των μαθητών αυξάνεται
void Junior::attend(int hours){
    for(int i=0; i<hours; i++)
        counter_of_fatigue += rate_of_fatigue;
}

//Αρχικοποιούμε την static μεταβλητή
int Junior::rate_of_fatigue = 0;

void Junior::set_rate_of_fatigue(int rate){rate_of_fatigue = rate;}

//Οι συναρτήσεις της κλάσης Senior
//Δημιουργία του Senior
Senior::Senior(std::string name, int classroom_id, int floor_number, bool in_class, int counter_of_fatigue):
        Student(name, classroom_id, floor_number, in_class, counter_of_fatigue){
}

void Senior::attend(int hours){
    for(int i=0; i<hours; i++)
        counter_of_fatigue += rate_of_fatigue;
}

//Αρχικοποιούμε την static μεταβλητή
int Senior::rate_of_fatigue = 0;

void Senior::set_rate_of_fatigue(int rate){rate_of_fatigue = rate;}

//Οι συναρτήσεις της κλάσης Teacher
//Δημιουργία του Teacher
Teacher::Teacher(std::string name, int classroom_id, int floor_number, bool in_class, int counter_of_fatigue):
        Person(name, classroom_id, floor_number, in_class, counter_of_fatigue){
    std::cout << "A new Teacher is constructed" << std::endl;
    print();
}

//Καταστροφή του Teacher
Teacher::~Teacher(){
    std::cout << "A Teacher to be destroyed" << std::endl;
    print();
}

//Ο μετρητής της κούρασης των δασκάλων αυξάνεται
void Teacher::teach(int hours){
    for(int i=0; i<hours; i++)
        counter_of_fatigue += rate_of_fatigue;  
}

void Teacher::set_rate_of_fatigue(int rate){rate_of_fatigue = rate;}

//Αρχικοποιούμε την static μεταβλητή
int Teacher::rate_of_fatigue = 0;

//Συναρτήσεις της κλάσης Αrea
//Δημιουργία ενός χώρου
Area::Area():temp_student(NULL){}

//Καταστροφή ενός χώρου
Area::~Area(){}

// Eίσοδος μαθητή στον χώρο
void Area::enter(Student* temp_student){
    this->temp_student = temp_student;
}

// Έξοδος μαθητή από τον χώρο
Student* Area::exit(){
    Student* student_to_leave = temp_student;
    temp_student = NULL;
    return student_to_leave;
}

//Συναρτήσεις της κλάσης Yard
//Δημιουργία του προαυλίου
Yard::Yard():Area(){std::cout << "A Yard is constructed" << std::endl;}

//Kαταστροφή του προαυλίου
Yard::~Yard(){std::cout << "A Yard to be destroyed" << std::endl;}

// Είσοδος του student στο Yard
void Yard::enter(Student* temp_student){
    temp_student->print("name");
    std::cout << " enters yard" << std::endl;
    Area::enter(temp_student);
}

// Έξοδος του student απο το Yard
Student* Yard::exit(){
    temp_student->print("name");
    std::cout << " exit yard" << std::endl;
    return Area::exit();
}

// Συναρτήσεις της κλάσης Stair
//Δημιουργία του κλιμακοστασίου
Stair::Stair():Area(){std::cout << "A Stair is constructed" << std::endl;}

//Kαταστροφή του κλιμακοστασίου
Stair::~Stair(){std::cout << "A Stair to be destroyed" << std::endl;}

// Είσοδος του student στο Stair
void Stair::enter(Student* temp_student){
    temp_student->print("name");
    std::cout << " enters stair" << std::endl;
    Area::enter(temp_student);
}

// Έξοδος του student απο το Stair
Student* Stair::exit(){
    temp_student->print("name");
    std::cout << " exits stair" << std::endl;
    return Area::exit();
}

// Συναρτήσεις της κλάσης Corridor
// Δημιουργία του corridor
Corridor::Corridor():Area(){std::cout << "A Corridor is constructed" << std::endl;}

// Καταστροφή του corridor
Corridor::~Corridor(){std::cout << "A Corridor to be destroyed" << std::endl;}

// Είσοδος του student στο Corridor
void Corridor::enter(Student* temp_student){
    temp_student->print("name");
    std::cout << " enters corridor" << std::endl;
    Area::enter(temp_student);
}

// Έξοδος του student απο το Corridor
Student* Corridor::exit(){
    temp_student->print("name");
    std::cout << " exits corridor" << std::endl;
    return Area::exit();
}

// Συναρτήσεις της κλάσης Classroom
//Δημιουργία της τάξης
Classroom::Classroom(int number_of_students):number_of_students(number_of_students), teacher(NULL){
   std::cout << "A classroom is constructed" << std::endl;
   students = new Student*[number_of_students];
   for(int i=0; i<number_of_students; i++)
        students[i] = NULL;
}

//Καταστροφή της classroom
Classroom::~Classroom(){
    std::cout << "A classroom to be destroyed" << std::endl;
    for(int i=0; i<number_of_students; i++)
        if(students[i] != NULL)
            delete students[i];
    delete[] students;
    if(teacher != NULL)
        delete teacher;
}

// Εισαγω μαθητή στην τάξη
void Classroom::enter(Student* student){
    for(int i=0; i<number_of_students; i++)
        if(students[i] == NULL){
            students[i] = student;
            students[i]->set_in_class_state(true);
            students[i]->print("name");
            std::cout << " enters classroom" << std::endl;
            return;
        }
}

// Εισαγω καθηγητη στην τάξη
void Classroom::enter(Teacher* teacher){
    if(this->teacher == NULL){
        this->teacher = teacher;
        this->teacher->set_in_class_state(true);
    }
}

// η τάξη λειτουρεί hours ώρες
void Classroom::operate(int hours){
    for(int i=0; i<number_of_students; i++)
        students[i]->attend(hours);
    teacher->teach(hours);
}

// εκτύπωση των μαθητών και του καθηγητή της τάξης
void Classroom::print()const{
    std::cout << "Students:" << std::endl;
    for(int i=0; i<number_of_students; i++){
        if(students[i] != NULL)
            students[i]->print();
    }
    std::cout << "Teacher:" << std::endl;
    if(teacher != NULL)
        teacher->print();
}

// Συναρτήσεις της κλάσης του floor
//Δημιουργία του ορόφου
Floor::Floor(int classroom_capacity){
    std::cout << "A Floor is constructed" << std::endl;
    corridor = new Corridor;
    classrooms = new Classroom*[classrooms_per_floor];
    for(int i=0 ; i<classrooms_per_floor; i++)
        classrooms[i] = new Classroom(classroom_capacity);
}

//Καταστροφή του ορόφου
Floor::~Floor(){
    std::cout << "A Floor to be destroyed" << std::endl;
    delete corridor;
    for(int i=0; i<classrooms_per_floor; i++)
        delete classrooms[i];
    delete[] classrooms;

}

//Εισοδος του μαθητή στον όροφο, δηλαδή στον διαδρομο και μετά στην τάξη του
void Floor::enter(Student* temp_student){

    temp_student->print("name");
    std::cout << " enters floor" << std::endl;

    corridor->enter(temp_student);
    int classroom_id = temp_student->get_classroom_id();
    classrooms[classroom_id]->enter(corridor->exit());
}

//Εισοδος του καθηγητή στην τάξη του
void Floor::enter(Teacher* teacher){
    int classroom_id = teacher->get_classroom_id();
    classrooms[classroom_id]->enter(teacher);
}

void Floor::operate(int hours){
    for(int i=0; i<classrooms_per_floor; i++)
        classrooms[i]->operate(hours);
}

void Floor::print()const{
    for(int i=0; i<classrooms_per_floor; i++){
        std::cout <<"The classroom: " << i << " contains:" << std::endl;
        classrooms[i]->print();
    }
}

//Συναρτήσεις της κλάσης SchoolBuilding
// Δημιουργία του SchoolBuilding
SchoolBuilding::SchoolBuilding(int students_per_classroom,int junior_rate, int senior_rate, int teacher_rate){
    std::cout << "A school building is constructed" << std::endl;
    school_yard = new Yard;
    school_stair = new Stair;
    school_floor = new Floor*[number_of_floors];
    set_rates_of_fatigue(junior_rate, senior_rate, teacher_rate);   //καθορίζω τους βαθμούς αύξησης της κούρασης
    for(int i=0; i<number_of_floors; i++){
        school_floor[i] = new Floor(students_per_classroom);
    }
}

// Kαταστροφή του SchoolBuilding
SchoolBuilding::~SchoolBuilding(){
    std::cout << "A school building to be destroyed" << std::endl;
    delete school_yard;
    delete school_stair;
    for(int i=0; i<number_of_floors; i++)
        delete school_floor[i];
    delete[] school_floor;
}

// Πραγματοποιείται η διαδρομή του μαθητή από το προαύλιο μέχρι την τάξη του
void SchoolBuilding::enter(Student* temp_student){

    temp_student->print("name");
    std::cout << " enters School!" << std::endl;

    school_yard->enter(temp_student);
    school_stair->enter(school_yard->exit());

    int number_of_floor = temp_student->get_floor_number();
    school_floor[number_of_floor]->enter(school_stair->exit());

}

//Toποθέτηση του καθηγητή στην τάξη του
void SchoolBuilding::place(Teacher* teacher){
    int floor_number = teacher->get_floor_number();
    school_floor[floor_number]->enter(teacher);
}

//Εκτύπωση της κατάστασης των σχολικών τάξεων
void SchoolBuilding::print()const{
    std::cout << "School life consists of:" << std::endl;
    for(int i=0; i<number_of_floors; i++){
        std::cout << "The floor number: " << i << " contains:" << std::endl;
        school_floor[i]->print();
    }
}

void SchoolBuilding::operate(int hours){
    for(int i=0; i<number_of_floors; i++)
        school_floor[i]->operate(hours);
}

void SchoolBuilding::set_rates_of_fatigue(int junior_rate, int senior_rate, int teacher_rate){
    Junior::set_rate_of_fatigue(junior_rate);   // βαθμός κούρασης των junior μαθητών
    Senior::set_rate_of_fatigue(senior_rate);   // βαθμός κούρασης των senior μαθητών
    Teacher::set_rate_of_fatigue(teacher_rate); // βαθμός κούρασης των καθηγητών
}