#include "school_structure.h"

// Students functions
void Students::info()const{

    if(!this->name.empty()){
        cout << this->name << "\n" << this->floor << "\n"
        << this->classroom << "\n" << this->place << endl;
    }

}

Students::Students(string students_name, string current_place, int class_floor, int class_number ):name(students_name),
        place(current_place), floor(class_floor), classroom(class_number){
        
    cout << "A new student has been created" << "\n" << "name: " << students_name << "\n" <<"place: "
    << current_place << "\n" << "class number: " << class_number << "\n" << "class floor: " << class_floor << endl;
}

Students::~Students(){cout << "A student to be destroyed" << endl;}

void Students::print_name()const{cout << this->name << endl;}

int Students::get_classroom()const{return this->classroom;}

int Students::get_floor()const{return this->floor;}

void Students::set_place(string place){this->place.assign(place);}

// Teachers functions
void Teachers::info()const{

    if(!this->name.empty()){
        cout << this->name << "\n" << this->floor << "\n"<< this->classroom << "\n";
        if(this->inclass)
            cout << "in class" << endl;
        else 
            cout << "out of class" << endl;
    }
}

Teachers::Teachers(string teachers_name, bool current_status, int class_floor, int class_number): name(teachers_name),
        inclass(current_status), floor(class_floor), classroom(class_number){

    cout << "A new teacher has been created " << "\n" << "name: " << teachers_name << "\n" << "place: " << "out of class"
    << "\n" << "class number: " << class_number << "\n" << "class floor: " << class_floor << endl;
}

Teachers::~Teachers(){cout << "A teacher to be destroyed" << endl;}

int Teachers::get_floor()const{return this->floor;}

int Teachers::get_classroom()const{return this->classroom;}

void Teachers::print_name()const{cout << this->name << endl;}

void Teachers::set_status(bool status){this->inclass = status;}

// classroom functions
Classrooms::Classrooms(int students):teacher(NULL), students(students), class_full(false){

    cout << "A classroom has been created" << endl;

    class_students = new Students*[students];
    for(int i=0; i<students; i++){
        class_students[i] = NULL;
    }
}

Classrooms::~Classrooms(){

    cout << "A classroom to be destroyed" << endl;
    for(int i=0; i<students; i++){
        if(class_students[i] != NULL)
            delete class_students[i];
    }

    delete[] class_students;
    if(teacher != NULL)
        delete teacher;

}

bool Classrooms::place(Teachers* teacher){

    // Aν δεν υπάρχει καθηγητής στην τάξη τότε τον εισάγω και επιστρέφω true
    if(this->teacher == NULL){
        this->teacher = teacher;
        cout << "The teacher is in class: " << teacher->get_classroom() << " of floor: " << teacher->get_floor() << " name: ";
        this->teacher->print_name();
        teacher->set_status(true);
        return true;
    }
    // Αν υπάρχει ήδη τότε επιστρέφω false
    else{
        cout << "There is already a teacher in this class" << endl;
        return false;
    }
}

Teachers* Classrooms::get_teacher()const{return teacher;}

void Classrooms::print()const{

    cout << "The studens are: " << endl;
    for(int i=0; i<students; i++){
        if(class_students[i] != NULL)
            class_students[i]->print_name();
    }
    cout << "The teacher is: " << endl;
    if(teacher != NULL)
        teacher->print_name();
}

void Classrooms::set_classroom_status(bool status){this->class_full = status;}

bool Classrooms::get_classroom_status()const{return this->class_full;}

bool Classrooms::enter_classroom(Students* some_student){

    //Aμα δεν έχει μπει ήδη ο καθηγητής
    if(this->teacher == NULL){
        // και άμα υπάρχει διαθέσιμη θέση στον πίνακα της τάξης
        for(int i=0; i<this->students; i++){
            
            if(class_students[i] == NULL){

                // τοτε κάνω εισαγωγή και επιστρέφω true
                class_students[i] = some_student;
                cout << "Enters class ... ";
                class_students[i]->print_name();
                some_student->set_place("in class");

                return true;
            }
        }
        cout << "class is packed " << endl;
        return false;
    }
    // αλλιως σε κάθε αλλή περίπτωση επιστρέφω false και δεν γίνεται καποια εισαγωγή
    else{
        cout << "There is a teacher in class already" << endl;
        return false;
    }  
}

bool Classrooms::is_classroom_full(){

    for(int i=0; i<this->students; i++){
        if(this->class_students[i] == NULL)
            return false;
    }

    return true;
}

// corridor functions
Corridors::Corridors(int corr_capacity):max_capacity(corr_capacity){
    cout << "A corridor is been created" << endl;

    array_of_students = new Students*[corr_capacity];

    for(int i=0; i<corr_capacity; i++){
        array_of_students[i] = NULL;
    }
}

Corridors::~Corridors(){
    cout << "A corridor to be destroyed" << endl;

    for(int i=0; i<get_capacity(); i++){
        if(array_of_students[i] != NULL)
            delete array_of_students[i];
    }
    delete[] array_of_students;

}

void Corridors::set_capacity(int corr_capacity){this->max_capacity = corr_capacity;}

int Corridors::get_capacity()const{return this->max_capacity;}

void Corridors::print()const{  
    cout << "People in this corridor: " << endl;

    for(int i=0; i<get_capacity(); i++){

        Students* student = array_of_students[i];
        if(student != NULL)
            student->print_name();           
    }
}

bool Corridors::enter_corridor(Students* some_student){

    for(int i=0; i<this->get_capacity(); i++){
        
        // Aμα βρόυμε κανή θέση στον πίνακα του διαδρόμου τότε γίνεται η εισαγωγή και επιστρέφεται true
        if(array_of_students[i] == NULL){

            array_of_students[i] = some_student;
            cout << "Enters corridor ... ";
            array_of_students[i]->print_name();
            some_student->set_place("in corridors");

            return true;
        }
    }
    // Aλλιως σημαίνει ότι είναι γεμάτος και επιστρέφουμε false
    cout << "Corridor is packed " << endl;
    return false;
   
}

// H exit αφαιρεί έναν μαθητή από τον πίνακα με το συγκεκριμένο index
// Aν o μαθητής αυτου του index έχει ήδη αφαιρεθεί τότε αφαιρεί τον αμέσο επόμενο μαθητή του array
bool Corridors::exit_corridor(int index){

    if(index < get_capacity()){
        while(array_of_students[index] == NULL && index < get_capacity()){
            index++;
        }   
    }
    if(index < get_capacity()){
        cout << "Exits corridor... ";
        array_of_students[index]->print_name();
        array_of_students[index] = NULL;
        return true;
    }
    else{ 
        cout << "all students have passed to their classrooms" << endl;
        return false;
    }  
}

// H get_student επιστρέφει έναν μαθητή από τον πίνακα με το συγκεκριμένο index
// Aν o μαθητής αυτου του index δεν υπάρχει τότε επιστρέφει τον αμέσο επόμενο μαθητή του array
Students* Corridors::get_student(int index)const{
    if(index < get_capacity()){
        while(index < get_capacity() && array_of_students[index] == NULL){
            index++;
        }   
    }
    return (index < get_capacity()) ? array_of_students[index] : NULL;   
}

// Yard functions(οι παρακάτω συναρτήσεις είναι παρόμοιες με αυτές του corridor) 
Yard::Yard(int yard_capacity):max_capacity(yard_capacity){

    cout << "The yard has been created" << endl;

    array_of_students = new Students*[yard_capacity];
    for(int i=0; i<yard_capacity; i++){
        array_of_students[i] = NULL;
    }
}

Yard::~Yard(){
    cout << "A yard to be destroyed" << endl;

    for(int i=0; i<get_capacity(); i++){
        if(array_of_students[i] != NULL)
            delete array_of_students[i];
    }
    delete[] array_of_students;
}

void Yard::set_capacity(int yard_capacity){this->max_capacity = yard_capacity;}

int Yard::get_capacity()const{return this->max_capacity;}

void Yard::print()const{

    cout << "People in schoolyard: " << endl;

    for(int i=0; i<get_capacity(); i++){

        Students* student = array_of_students[i];
        if(student != NULL)
            student->print_name();           
    }
}

bool Yard::enter_yard(Students* some_student){

    for(int i=0; i<this->get_capacity(); i++){
        
        if(array_of_students[i] == NULL){

            array_of_students[i] = some_student;
            cout << "Enters yard ... ";
            array_of_students[i]->print_name();
            some_student->set_place("in yard");

            return true;
        }
    }
    cout << "Yard is packed " << endl;
    return false;

}

bool Yard::exit_yard(int index){

    if(index < get_capacity()){
        while(array_of_students[index] == NULL && index < get_capacity()){
            index++;
        }   
    }
    if(index < get_capacity()){
        cout << "Exits yard... ";
        array_of_students[index]->print_name();
        array_of_students[index] = NULL;
        return true;
    }
    else{ 
        cout << "all students have passed to the stairs" << endl;
        return false;
    }    
}

Students* Yard::get_student(int index)const{

    if(index < get_capacity()){
        while(index < get_capacity() && array_of_students[index] == NULL){
            index++;
        }   
    }
    return (index < get_capacity()) ? array_of_students[index] : NULL;
}

// Stairs functions(οι παρακάτω συναρτήσεις είναι παρόμοιες με αυτές του corridor)
Stairs::Stairs(int stair_capacity):max_capacity(stair_capacity){

    cout << "A stair has been created" << endl;

    array_of_students = new Students*[stair_capacity];
    for(int i=0; i<stair_capacity; i++){
        array_of_students[i] = NULL;
    }
}

Stairs::~Stairs(){
    cout << "A stair to be destroyed" << endl;

    for(int i=0; i<get_capacity(); i++){
        if(array_of_students[i] != NULL)
            delete array_of_students[i];
    }
    delete[] array_of_students;

}

void Stairs::set_capacity(int stair_capacity){this->max_capacity = stair_capacity;}

int Stairs::get_capacity()const{return this->max_capacity;}

void Stairs::print()const{

    cout << "People in stairs: " << endl;

    for(int i=0; i<get_capacity(); i++){

        Students* student = array_of_students[i];
        if(student != NULL)
            student->print_name();           
    }
}

bool Stairs::enter_stairs(Students* some_student){

    for(int i=0; i<get_capacity(); i++){
        if(array_of_students[i] == NULL){
            cout << "Enters stair... ";
            some_student->print_name();
            some_student->set_place("in stairs");

            array_of_students[i] = some_student;
            return true;
        }    
    }
        
    cout <<"Stair is packed.." << endl;
    return false;    
}

bool Stairs::exit_stairs(int index){

    if(index < get_capacity()){
        while(array_of_students[index] == NULL && index < get_capacity()){
            index++;
        }   
    }
    if(index < get_capacity()){
        cout << "Exits stair... ";
        array_of_students[index]->print_name();
        array_of_students[index] = NULL;
        return true;
    }
    else{ 
        cout << "all students have passed to the corridors" << endl;
        return false;
    }        
}

Students* Stairs::get_student(int index)const{
    if(index < get_capacity()){
        while(index < get_capacity() && array_of_students[index] == NULL){
            index++;
        }   
    }
    return (index < get_capacity()) ? array_of_students[index] : NULL;    
}

// floor classrooms
Floors::Floors(int students, int corridors_capacity){

    cout << "A floor has been created" << endl;
    this->corridor = new Corridors(corridors_capacity);

    floor_classrooms = new Classrooms*[number_of_classes];
    for(int i=0; i<number_of_classes; i++){
        this->floor_classrooms[i] = new Classrooms(students);
    }

}

Classrooms* Floors::get_classroom(int index)const{return this->floor_classrooms[index];}

Corridors* Floors::get_corridor()const{return this->corridor;}

// H enter_floor καλεί την enter_corridor η οπόι κρίνει άμα ο μαθητής θα φύγει από τις
// σκάλες και θα μπει στον διαδρομο του συγκεκριμένου ορόφου
bool Floors::enter_floor(Students* some_student){

    cout << "Enters floor...";
    some_student->print_name();
    if(corridor->enter_corridor(some_student)){
        return true;
    }
    else{
        cout << "Returning to stairs... ";
        some_student->print_name();
        return false;       
    }
}

void Floors::print()const{
    
    corridor->print();
    for(int i=0; i<number_of_classes; i++){

        cout << "People in the class " << i << " are: " << endl;
        floor_classrooms[i]->print();
    }
}

Floors::~Floors(){

    cout << "A floor to be destroyed" << endl;
    delete corridor;
    for(int i=0; i<number_of_classes; i++){
        delete floor_classrooms[i];
    }
    delete[] floor_classrooms;
}

// school building functions
SchoolBuilding::SchoolBuilding(int class_students, int stair_capacity, int yard_capacity, int corridors_capacity){

    cout << " A School Building has been created" << endl;
    school_floors = new Floors*[number_of_floors];
    for(int i=0; i<number_of_floors; i++){
        school_floors[i] = new Floors(class_students, corridors_capacity);
    }

    all_students = class_students*number_of_classes*number_of_floors;

    stair = new Stairs(stair_capacity);
    school_yard = new Yard(yard_capacity);
}

SchoolBuilding::~SchoolBuilding(){

    cout << "School building to be destroyed" << endl;

    for(int i=0; i<number_of_floors; i++){
        delete school_floors[i];
    }
    delete[] school_floors;

    delete stair;
    delete school_yard;

}

void SchoolBuilding::print()const{

    cout << "\n" << "School life consists of: " << endl;

    cout << endl;
    school_yard->print();

    cout<<endl;
    stair->print();

    for(int i=0; i<number_of_floors; i++){
        cout << "\n" << "Floor number: "<< i << " contains: " << endl;
        school_floors[i]->print();
    }

    cout <<"\n" << "The students that are left out: " << endl;
    for(int i=0; i<all_students; i++){
        if(array_of_students[i] != NULL)
            array_of_students[i]->print_name();
    }
    cout << endl;
}

Yard* SchoolBuilding::get_yard()const{return school_yard;}

Stairs* SchoolBuilding::get_stair()const{return stair;}

Floors* SchoolBuilding::get_floor(int index)const{return school_floors[index];}

// H enter_school καλεί την enter_yard η οπoιa κρίνει άμα ο μαθητής θα φύγει από τον κεντρικό πίνακα
// του SchoolBuilding και θα μπει στον χώρο του σχολείου, συγκεκριμένα στο προαύλιο
bool SchoolBuilding::enter_school(Students* some_student){

    cout <<"Enters School...";
    some_student->print_name();

    if(school_yard->enter_yard(some_student)){
        return true;
    }
    else{
        cout << "Returning out of school... ";
        some_student->print_name();
        return false;       
    }
}

bool SchoolBuilding::enter_school(Students** array_of_students){

    this->array_of_students = array_of_students;  
    
    bool move = false;         // false->οι μαθητες δεν μπορουν να προχωρήσουν true->oι μαθητες μπορουν να προχωρήσουν
    
    // Τωρα οι μαθητές μπαίνουν μέσα στον χωρο του σχολείου
    for(int i=0; i<school_yard->get_capacity(); i++){

        // Παίρνω τον μαθητή από τον πίνακα του school_building
        Students* student = get_student(i);
        // Ελέγχω άμα δεν είναι NULL
        if(student != NULL){    

            // Αμα δεν είναι ΝULL τότε κάνω enter τον συγκεκριμένο student στον χώρο(πίνακα) του yard μεσω της enter_school
            // Αμα η enter επιστρέψει true σημαίνει οτι το enter έγινε με επιτυχία
            if(enter_school(student)){
                exit_school(i);                     // οπότε κάνω exit τον μαθητη από τον πίνακα του school_building
                move = true;                      // και ενημερώνω ότι οι μαθητές προχώρησαν
            }
            // Αμα όμως επιστρεψει false σημαινει οτι ο χώρος(πινακας) του yard είναι γεμάτος
            else
                break;    // οπότε δεν μπορεί να μπει καποιος μαθητής και κανουμε break;
        }
        // Αμα είναι NULL σημαίνει ότι ο πίνακας του school_building έχει αδειάσει και όλοι οι μαθητές έχουν
        // περάσει στο yard
        else
            break;  // οπότε φεύγω(break) από τον απο την εξερεύνηση του πίνακα
    }               

    // Τώρα όσοι μαθητές μπορούν έχουν περάσει στον πινακα του yard
    // και θα ξεκινήσει η εισαγωγή τους στον πίνακα του χώρου stair

    // Παίρνω τον χώρο του stair και βάζω όσους μαθητές μπορώ από τον πίνακα το yard
    for(int i=0; i<stair->get_capacity(); i++){

        // Παίρνω τον μαθητή από τον πίνακα του yard και συνεχίζω παρόμοια με πριν
        Students* student = school_yard->get_student(i);
        if(student != NULL){

            if(stair->enter_stairs(student)){
                school_yard->exit_yard(i);
                move = true;
            }
            else
                break;
        }
        else
            break;
    }

    // Τώρα όσοι μαθητές μπορούν έχουν περάσει στον πινακα του stair
    // και θα ξεκινήσει η εισαγωγή τους στον πίνακα του χώρου corridor
    for(int i=0; i<stair->get_capacity(); i++){

        // Παίρνω ένα μαθητή από τον χώρο stair
        Students* student = stair->get_student(i);

        // Kαι ελέγχω άμα είναι ΝULL ή όχι
        if(student != NULL){
            // Τώρα πρέπει να βρω σε ποιον από τους 3 ορόφους θα πάει ο μαθητής
            int nfloor = student->get_floor();      // Παίρνω τον αριθμό του ορόφου

            // Και τώρα τον χώρο του συγκεκριμένου ορόφου
            Floors* floor = get_floor(nfloor);

            // Παρόμοια με πριν άμα η enter επιστρέψει true εγινε με επιτυχία η είσοδος του μαθητή
            // στο floor, δηλαδη στον corridor που ανηκει η ταξη του μαθητη, και μετά θα γίνει η εξοδός του από τον χωρο stair
            if(floor->enter_floor(student)){
                stair->exit_stairs(i);
                move = true;
            }
            else 
                break;
        }
        else
            break;
    }

    // Σε αυτή την φάση θα ελέγξω και τους corridors και στους 3 ορόφους
    for(int i=0; i<number_of_floors; i++){
        // Παίρνω το floor και τον αντίστοιχο corridor
        Floors* floor = get_floor(i); 
        Corridors* corridor = floor->get_corridor();

        // Exω παρει τον χωρο του corridor και θα βάλω όσους μαθητές γίνεται στις τάξεις τους
        for(int j=0; j<corridor->get_capacity(); j++){

            Students* student = corridor->get_student(j);   // Παιρνω τον μαθητή και ελέγχω
            if(student != NULL){

                int nclass = student->get_classroom();      // Παιρνω τον αριθμό της τάξης του
                Classrooms* classroom = floor->get_classroom(nclass);   // Και παιρνω τον χώρο(πίνακα) την τάξης του

                // Πρεπει πρώτα να ελεγξω άμα έχει μπει ήδη ο καθηγητής
                // Αν έχει μπει τότε παιρνάω στον επόμενο μαθητη του διαδρόμου και ο τρέχον μένει εκεί
                // Αν όμως δεν έχει μπει τότε
                if(classroom->get_teacher() == NULL){

                    // Ελέγχω άμα μπορεί να μπει ο μαθητής στην ταξη
                    // (Δηλαδη οτι υπάρχει θεση στον πίνακα των μαθητών της τάξης)
                    if(classroom->enter_classroom(student) == true){
                        move = true;
                        corridor->exit_corridor(j);
                    }
                    // Αμα δεν μπορεί να μπεί σημαίνει ότι η τάξη είναι πλήρης
                    // αλλά δεν κάνουμε break γιατί μπορεί να υπάρχουν τάξεις στον όροφο που να χωράνε μαθητές
                    else{
                        classroom->set_classroom_status(true);  // ενημερώνουμε οτι η τάξης είναι πλήρης
                    }
                }                    
            }
            // άμα δεν βρω μαθητή σημαίνει ότι ο διάδρομος είναι άδειος οπότε
            // κανω break και ελεγχουμε τον επόμενο όροφο
            else{
                break;
            }           
        }
    }

    //Επιστρέφω αν οι μαθητές κατάφεραν να προχωρήσουν ή όχι
    return move;
}

Students* SchoolBuilding::get_student(int index)const{

    if(index < all_students){
        while(index < all_students && array_of_students[index] == NULL){
            index++;
        }   
    }
    return (index < all_students) ? array_of_students[index] : NULL;
}

bool SchoolBuilding::exit_school(int index){

    if(index < all_students){
        while(array_of_students[index] == NULL && index < all_students){
            index++;
        }   
    }
    if(index < all_students){
        array_of_students[index] = NULL;
        return true;
    }
    else{ 
        cout << "all students have passed to the yard" << endl;
        return false;
    }

}
