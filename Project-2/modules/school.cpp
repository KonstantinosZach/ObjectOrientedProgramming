#include "school.h"
#include "LinkedList.h"

// student functions
student::student(std::string name, std::string gender, int classroom_id, int personal_id):
    name(name), gender(gender), classroom_id(classroom_id), personal_id(personal_id), in_sequence(false), rude(false){
        std::cout << "A new student has been created"  << std::endl;
    }

student::~student(){
    std::cout << "A student to be destroyed" << std::endl;
}

void student::print()const{
    std::cout << "name: " << name << " gender: " << gender
    << " classroom_id: " << classroom_id << std::endl;
}

std::string student::get_gender()const{return gender;}

bool student::get_status()const{return in_sequence;}

void student::set_status(bool status){in_sequence=status;}

int student::get_id()const{return personal_id;}

void student::set_rude_status(bool status){rude = status;}

bool student::get_rude_status()const{return rude;}

int student::get_classroom_id()const{return classroom_id;}

// pair functions
pair::pair(Student left_student, Student right_student):
    left_student(left_student), right_student(right_student){
        std::cout << "A pair has been created" << std::endl;
    }

pair::~pair(){
    std::cout << "A pair to be destroyed" << std::endl;
}

void pair::print()const{
    if(left_student != NULL)
        left_student->print();
    
    if(right_student != NULL)
        right_student->print();
}

Student pair::get_student(std::string position)const{
    if(position.compare("right") == 0)
        return right_student;
    else if(position.compare("left") == 0)
        return left_student;
    else
        return NULL;
}

void pair::set_student(std::string position, Student some_student){
    if(position.compare("right") == 0)
        right_student = some_student;
    else if(position.compare("left") == 0)
       left_student = some_student;
    else
        std::cout << "Wrong position" << std::endl;
}

//classroom functions
classroom::classroom(LinkedList<Pair>* sequence, int capacity):disorder_count(0),
                    sequence(sequence),capacity(capacity){
    
    array_of_students = new Student[capacity];
    for(int i=0; i<capacity; i++)
        array_of_students[i] = NULL;
    
    std::cout << "A classroom is created" << std::endl;
   
}

classroom::~classroom(){

    // Kανω επίσης delete τους μαθητές που έβαλε η main στο καθε classroom
    for(int i=0; i<capacity; i++){
        if(array_of_students[i] != NULL)
            delete array_of_students[i];
    }
    delete[] array_of_students;
    delete sequence;
    std::cout << "A classroom to be destroyed" << std::endl;
}

void classroom::print()const{

    std::cout <<"size: " << sequence->get_size() << std::endl;
    std::cout << "The sequence of students is: " << std::endl;
    int size = sequence->get_size();

    for(int i=0; i<size; i++){
        Pair some_pair = sequence->get(i);
        std::cout<<"Pair: " << i << std::endl;
        some_pair->print();
    }
    std::cout << "Disorder level: " << disorder_count << std::endl;
}

// Επιστρέφει true αμα κατάφερε(χώρεσε) να μπει o μαθητης αλλιώς false
bool classroom::enter_student(Student some_student){

    for(int i=0; i<capacity; i++){
        if(array_of_students[i] == NULL){
            array_of_students[i] = some_student;
            return true;
        }
    }
    return false;
}

// Δημιουργεί την ακολουθία
void classroom::make_sequence(){

    bool empty = false;     // Ενα flag που θα μας δείξει πότε έχουν μπει όλοι οι μαθητές στην ακολουθία
    int stacking = 0;       // Αν είναι ζυγός (male,female) αν ειναι μονός(female, male)
                            // δηλαδη βοηθα στην τοποθετηση των μαθητων στην ακολουθία

    // Οσο υπάρχουν μαθητές που δεν εχουν μπει ακόμα στην ακολουθία
    while(!empty){

        Student male = NULL;
        Student female = NULL;

        //Ψαχνω έναν male μαθητή απο των πίνακα μαθητών της τάξης
        for(int i=0; i<capacity; i++){
            //Αμα ο μαθητης δεν εχει μπει στην ακολουθία και ειναι male τοτε τον επιλέγω           
            if(array_of_students[i]->get_status() == false && array_of_students[i]->get_gender().compare("male") == 0){
                male = array_of_students[i];
                array_of_students[i]->set_status(true);     // Και ενημερώνω οτι μπήκε στην ακολουθία
                break;
            }            
        }

        //Ψαχνω έναν female μαθητή απο των πίνακα μαθητών της τάξης
        for(int i=0; i<capacity; i++){
            //Αμα ο μαθητης δεν εχει μπει στην ακολουθία και ειναι female τοτε τον επιλέγω
            if(array_of_students[i]->get_status() == false && array_of_students[i]->get_gender().compare("female") == 0){
                female = array_of_students[i];
                array_of_students[i]->set_status(true);      // Και ενημερώνω οτι μπήκε στην ακολουθία
                break;
            }
        }

        Pair some_pair;
        // Δημιουργώ καθε φορά το σωστό ζευγάρι
        if(stacking%2 == 0)
            some_pair = new pair(male,female);
        else
            some_pair = new pair(female,male);
        
        stacking++;
        // Και το προσθέτω στην ακολουθία
        sequence->add(some_pair);

        // Και τέλος ελέγχω άμα όλοι οι μαθητές έχουν μπει στην ακολουθία
        empty = true;
        for(int i=0; i<capacity; i++){
            if(array_of_students[i]->get_status() == false)
                empty = false;
        }
    }
}

LinkedList<Pair>* classroom::get_sequence()const{return sequence;}

// Επιστρέφει τον μαθητή(με το συγκεκριμένο id) άμα τον βρει αλλιώς null
Student classroom::get_student(int student_id)const{
    for(int i=0; i<capacity; i++){
        Student some_student = array_of_students[i];
        if (some_student->get_id() == student_id)
            return some_student;
    }
    return NULL;
}

void classroom::disorder_modifier(int level){disorder_count += level;}

int classroom::get_disorder_count()const{return disorder_count;}

// school functions
school::school(int number_of_classrooms, int classroom_capacity)
                :number_of_classrooms(number_of_classrooms), classroom_capacity(classroom_capacity){
  
    classrooms = new Classroom[number_of_classrooms];
    for(int i=0; i<number_of_classrooms; i++)
        classrooms[i] = NULL;

    sequence = new LinkedList<Classroom>();
    std::cout << "A new kindergarder has been created" << std::endl;
}

school::~school(){
    delete[] classrooms;
    delete sequence;
    std::cout << "The kindergarder to be destroyed" << std::endl;
}

Classroom school::get_classroom(int index)const{
    return (index < number_of_classrooms) ? classrooms[index] : NULL;
}

bool school::enter_classroom(Student some_student, int index){
    //Πρώτα ελεγχω άμα το index υπάρχει
    if(index  < number_of_classrooms){

        // Μετά ελέγχω άμα έχει δημιουργεί ή όχι η τάξη με το συγκεκριμένο index
        // Αν όχι τότε την φτιάχνω 
        if(classrooms[index] == NULL){

            LinkedList<Pair>* list = new LinkedList<Pair>();
            Classroom some_classroom = new classroom(list, classroom_capacity);

            classrooms[index] = some_classroom;
            return classrooms[index]->enter_student(some_student);
        }
        // Αν ναι τοτε απλά βάζω τον student
        else{
            return classrooms[index]->enter_student(some_student);
        }
    }
    else
        return false;
}

void school::make_class_sequence(int classroom_index){

    // Eλέχγω άμα το index αντιστοιχεί σε καποια τάξη και μετά καλείται η συνάρτηση
    // για να δημιουργηθεί η ακολουθία
    if(classroom_index < number_of_classrooms){
        Classroom some_classroom = classrooms[classroom_index];
        some_classroom->make_sequence();
    }
    else{
        std::cout << "Classroom does not exist" << std::endl;
    }
}

void school::make_class_sequence(){
    for(int i=0; i<number_of_classrooms; i++){
        make_class_sequence(i);
    }
}

void school::print_classroom_sequence()const{
    for(int i=0; i<number_of_classrooms; i++){
        std::cout << "Classroom: " << i << std::endl;
        classrooms[i]->print();
    }
}

void school::print_classroom_sequence(int index)const{
    if(index < number_of_classrooms){
        std::cout << "Classroom: " << index << std::endl;
        Classroom some_classroom = get_classroom(index);
        some_classroom->print();
    }
    else{
        std::cout << "Classroom does not exist" << std::endl;
    }
}

void school::make_school_sequence(){

    for(int i=0; i<number_of_classrooms; i++){
        Classroom some_classroom = classrooms[i];
        sequence->add(some_classroom);
    }
}

void school::print_school_sequence(float T_quiet, float T_mess)const{
    int size = sequence->get_size();

    std::cout<<std::endl;
    std::cout << "The school sequence:" << std::endl;
    for(int i=0; i<size; i++){
        Classroom some_classroom = sequence->get(i);
        std::cout << "Classroom id: " << i << std::endl;
        some_classroom->print();
        if(some_classroom->get_disorder_count() > T_mess*classroom_capacity){
            std::cout << "What a mess!" << std::endl;
        }
        else if(some_classroom->get_disorder_count() < T_quiet*classroom_capacity){
            std::cout << "What a quiet class!" << std::endl;
        }
        else{
            std::cout << "Please, be quiet!" << std::endl;
        }
        std::cout<<std::endl;
    }
    std::cout<<std::endl;
}

void school::remove_pair_from_sequence(int classroom_id, int index){
    classrooms[classroom_id]->get_sequence()->remove(index);
}

void school::school_transition(){
    //Αμα ο αριθμός των μαθητών είναι ζυγός τότε δεν χρειάζεται κάποια αντιμετάθεση 
    if(classroom_capacity%2 == 0){
        std::cout << "No transitions needed" << std::endl;
    }
    else{
        std::cout << "The number of students is odd" << std::endl;
        std::cout << "so we will check if we can make students transitions to the 1st class" << std::endl;
    // αλλίως δαιτρέχουμε τις τάξεις και βλέπουμε τις ακολουθίες με τα pairs
        for(int i=0; i<number_of_classrooms; i++){

            // Παίρνουμε την ακολουθία της πρώτης τάξη
            LinkedList<Pair>* pair_sequence_1 = sequence->get(i)->get_sequence();

            //Αν έχω ενα μόνο μαθητή ως τελευταίο ζευγάρι θα κοιτάξω για αντιμετάθεση
            if(pair_sequence_1->get_last()->get_student("right") == NULL || 
               pair_sequence_1->get_last()->get_student("left") == NULL){

                // Παιρνω αυτό το "μισό" ζευγάρι
                Pair last_pair_1 = pair_sequence_1->get_last();
                // Και βρίσκω τον μαθητή
                Student last_student_1 = last_pair_1->get_student("left");
                if(last_student_1 == NULL)
                    last_student_1 = last_pair_1->get_student("right");

                // Και τώρα θα ψάξω στις άλλες τάξεις για ένα άλλο μαθητή αντίθετου φύλου
                // που είναι και αυτός μόνος του(χωρίς ζευγράρι)
                for(int j=0; j<number_of_classrooms; j++){

                    if(j==i)continue;   // Δεν ψάχνω στην ιδια τάξη για μαθητή

                    // Παίρνω την ακολουθία μιας αλλης τάξης
                    LinkedList<Pair>* pair_sequence_2 = sequence->get(j)->get_sequence();

                    //Αν έχω ενα μόνο μαθητή ως τελευταίο ζευγάρι θα κοιτάξω για αντιμετάθεση
                    if(pair_sequence_2->get_last()->get_student("right") == NULL || 
                    pair_sequence_2->get_last()->get_student("left") == NULL){

                        // Παιρνω αυτό το "μισό" ζευγάρι
                        Pair last_pair_2 = pair_sequence_2->get_last();
                        // Και βρίσκω τον μαθητή
                        Student last_student_2 = last_pair_2->get_student("left");
                        if(last_student_2 == NULL)
                            last_student_2 = last_pair_2->get_student("right");


                        //Άμα είναι αντίθετου φύλου συνεχίζω
                        if(last_student_1->get_gender().compare(last_student_2->get_gender()) != 0){

                            // Βρήκαμε ζευγάρι για μαθητή της 1ης τάξης
                            if(i==0){

                                //Βαζω τον μαθητή που βρήκαμε στην κατάλληλη θέση
                                if(last_pair_1->get_student("left") == NULL)
                                    last_pair_1->set_student("left", last_student_2);
                                else
                                    last_pair_1->set_student("right", last_student_2);
                                
                                //Και τον κάνω remove από την ακολουθία που βρισκόταν
                                pair_sequence_2->remove(pair_sequence_2->get_size()-1);
                                break;  // Και κάνω break για να ασχοληθώ με άλλο τμήμα
                            }
                            // Βρήκαμε 2 μαθητές εκτός της 1ης τάξης που θα μπουν ως επιπλέον ζευγράρι
                            // στην 1η τάξη
                            else{

                                //Παίρνω την ακολουθία της 1ης τάξης γιατί σε αυτή θα μπει το καινούργιο ζευγάρι
                                LinkedList<Pair>* first_sequence = sequence->get(0)->get_sequence();

                                //Παίρνουμε το τελευταίο ζευγάρι γιατι θέλουμε να δούμε
                                //πως είναι στιβαγμένοι οι μαθητές
                                Pair last_pair = first_sequence->get_last();

                                //Αμα στα δεξία ειναι αγόρι
                                Student right_last_student = last_pair->get_student("right");
                                if(right_last_student->get_gender().compare("male") == 0){

                                    //Βλεπουμε αμα και ο last_student_1 ειναι αγόρι
                                    if(last_student_1->get_gender().compare("male") == 0){

                                        //Δημιουργούμε το ζευγάρι έτσι ώστε να είναι δεξία το κορίτσι και
                                        // αριστερά το αγόρι
                                        Pair some_pair = new pair(last_student_1,last_student_2);
                                        first_sequence->add(some_pair);

                                        //Και κάνουμε remove τα ζεγάρια στα οποία ήταν μόνοι τους οι μαθητές
                                        pair_sequence_1->remove(pair_sequence_1->get_size()-1);
                                        pair_sequence_2->remove(pair_sequence_2->get_size()-1);
                                    }
                                    //Εδω ο last_student_1 ειναι κορίτσι οπότε το ζευγάρι θα δημιουργηθεί αντίθετα
                                    else{
                                        Pair some_pair = new pair(last_student_2,last_student_1);
                                        first_sequence->add(some_pair);
                                        pair_sequence_1->remove(pair_sequence_1->get_size()-1);
                                        pair_sequence_2->remove(pair_sequence_2->get_size()-1);
                                    }
                                }
                                //Εδω στα δεξία είναι κορίτσι οπότε προσαρμόζουμε και πάλι
                                //το πως θα δημιουργηθεί το καινουργιο ζευγάρι
                                else{
                                    if(last_student_1->get_gender().compare("female") == 0){
                                        Pair some_pair = new pair(last_student_1,last_student_2);
                                        first_sequence->add(some_pair);
                                        pair_sequence_1->remove(pair_sequence_1->get_size()-1);
                                        pair_sequence_2->remove(pair_sequence_2->get_size()-1);
                                    }
                                    else{
                                        Pair some_pair = new pair(last_student_2,last_student_1);
                                        first_sequence->add(some_pair);
                                        pair_sequence_1->remove(pair_sequence_1->get_size()-1);
                                        pair_sequence_2->remove(pair_sequence_2->get_size()-1);
                                    }                                    
                                }
                                break;// Και κάνω break για να ασχοληθώ με άλλο τμήμα

                            }
                        }
                    }

                }      
            }
        }
    }
}

Student school::is_now_rude(int id){

    // Ψαχνει τον μαθητή με το συγκεκριμένο id
    for(int i=0; i<number_of_classrooms; i++){
        Classroom some_classroom = classrooms[i];
        Student some_student = some_classroom->get_student(id);

        // Αμα τον βρει τον μετατρέπει σε άτακτο
        if(some_student != NULL){

            // Αμα είναι ηδη εμφανίζει μύνημα
            if(some_student->get_rude_status()){
                std::cout << "Already rude" << std::endl;
                return NULL;
            }
            // Αλλιώς του αλλάξει στο rude_status σε true
            else{
                some_student->set_rude_status(true);
                some_student->print();
                return some_student;                
            }
        }

    }
    return NULL;
}

// Συνάρτηση που κάνει αντιμετάθεση έναν μόνο μαθητή με κάποιον άλλο από καποια ακολουθία
void school::student_transition(Pair some_pair, Student some_student, int classroom_id, int rude_level){
    
    // Πρώτα ελέγχουμε μήπως ο μαθητής δεν είναι πια άτακτος λόγω προηγούμενης αντιμετάθεσης
    // Αν δεν είναι άτακτος εμφανίζουμε το μύνημα και διακόπτουμε την διαδικασία
    if(!some_student->get_rude_status()){
        std::cout <<"This student is already been transitioned: " << std::endl;
        some_student->print();
        return;
    }
    // Αν είναι άτακτος τότε εμφανίζουμε μύνημα και συνεχίζουμε
    else{
        std::cout <<"This student is rude: " << std::endl;
        some_student->print();       
    }

    // Παίρνουμε την ακολουθία στην οποία θέλουμε να κάνουμε την αντιμετάθεση
    LinkedList<Pair>* some_sequence = classrooms[classroom_id]->get_sequence();

    // Αμα υπάρχει μόνο ένα ζευγάρι και σε αυτό το ζευγάρι βρίσκεται ο άτακτος
    // και θέλουμε αντιμετάθεση στην ίδια ακολουθία τότε
    // δεν πραγματοποιείται καποια αντιμετάθεση επειδή δεν υπάρχει διαθέσιμο ζευγάρι
    if(some_sequence->get_size() == 1 && some_sequence->get(0) == some_pair){
        std::cout<<"No avaible pair \n" <<std::endl;
        some_student->set_rude_status(false);
        return;
    }

    // Aν υπάρχουν μόνο 2 ζευγάρια και ο άτακτος βρίσκεται στο πρώτο
    // η μόνο επιλογή είναι το τελευταίο ζευγάρι
    // Εδώ ελέγχεται η περίπτωση το τελευταίο ζευγάρι να αποτελείται από ενα μαθητή αντίθετου φύλου
    // οπότε είναι αδύνατη η αντιμετάθεση
    else if(some_sequence->get_size() == 2 && some_pair == some_sequence->get(0)){

        // Παιρνουμε το τελευταίο ζευγάρι και βλέπουμε αν αποτελείται απο ένα μαθητή
        Pair last_pair = some_sequence->get_last();
        if((last_pair->get_student("right") == NULL) || (last_pair->get_student("left") == NULL)){

            // Αν αποτελείται από ενα μαθητή τοτε ελεγχουμε άμα αυτος ο μαθητής είναι αντίθετου φύλου ή οχι
            // Αν τελικά είναι αντίθετου φύλου τοτέ δεν γίνεται αντιμετάθεση
            // Αν ειναι του ιδιου φύλου τότε συνεχίζουμε παρακάτω
            if((last_pair->get_student("right") != NULL) &&
            (last_pair->get_student("right")->get_gender().compare(some_student->get_gender()) != 0)){
                std::cout<<"No avaible pair for" <<std::endl;
                some_student->print();
                some_student->set_rude_status(false);
                return;
            }
            else if((last_pair->get_student("left") != NULL) &&
            last_pair->get_student("left")->get_gender().compare(some_student->get_gender()) != 0){
                std::cout<<"No avaible pair for" <<std::endl;
                some_student->print();
                some_student->set_rude_status(false);
                return;
            }
        }
    }

    // Αν έχουμε αποφύγει τις προγούμενες περιπτώσεις τότε
    // βρίσκουμε τα διαθέσιμα ζευγάρια από τα οποία θα επιλέξουμε ένα
    // για να γίνει η αντιμετάθεση
    Pair possible_pairs[some_sequence->get_size() - 1];
    int array_index = 0;
    for(int i=0; i<some_sequence->get_size(); i++){
        Pair possible_pair = some_sequence->get(i);

        // Εδω από κάθε ζευγάρι παίρνουμε τον μαθητή του ίδιου φύλου με του άτακτου
        Student possible_student = possible_pair->get_student("right");
        if(possible_student != NULL && possible_student->get_gender().compare(some_student->get_gender()) != 0)
            possible_student = possible_pair->get_student("left");
        
        // Και αυτό γιατί θέλουμε να αποφύγουμε να βάλουμε στον πίνακα με τα πιθανα ζευγάρια προς αντιμετάθεση
        // το ζευγάρι που ανήκει ο άτακτος μαθητής
        // Οπότε όταν βρούμε τον ζευγάρι του το αγνοούμε
        if(possible_student != NULL && possible_student->get_id() != some_student->get_id()){
            possible_pairs[array_index] = possible_pair;
            array_index++;
        }

    }

    // Βρίσκουμε την θέση(left or right) του άτακτου μαθητή
    std::string position_1("right");
    if(some_pair->get_student("left") == some_student)
        position_1.assign("left");

    // Και τώρα επιλέγουμε τυχαία από τον πίνακα το ζευγάρι στο οποίο θα γίνει η αντιμετάθεση
    Pair transition_pair;
    if(array_index == 1)
        transition_pair = possible_pairs[0];
    else{
        array_index = rand()%(array_index-1);
        transition_pair = possible_pairs[array_index];  
    }
 
    // Βρίσκουμε την θέση(left or right) του μαθητή με τον οποίο θα αντικατασταθεί ο άτακτος μαθητής
    Student transition_student = transition_pair->get_student("right");
    std::string position_2("right");
 
    if(transition_student->get_gender().compare(some_student->get_gender()) != 0){
        position_2.assign("left");
        transition_student = transition_pair->get_student("left");
    }
 
    // Κανουμε την αντιμετάθεση
    some_pair->set_student(position_1, transition_student);
    transition_pair->set_student(position_2, some_student);

    // Βγάζουμε την ένδειξη rude 
    some_student->set_rude_status(false);
    // Kαι αυξάνουμε καταλληλα τον βαθμό της φασαρίας στην τάξη
    classrooms[some_student->get_classroom_id()]->disorder_modifier(rude_level);

    // Στην περίπτωση που ο μαθητής που επιλέχθηκε τυχαία ήταν και αυτός άτακτος τότε
    if(transition_student->get_rude_status()){
        //Ενημερώνουμε τον χρήστη με κατάλληλα μυνήματα
        std::cout << "This student is no more rude: " << std::endl;
        transition_student->print();
        std::cout << "Transitioned with: " << std::endl;
        some_student->print();
        // Βγάζουμε την ένδειξη rude 
        transition_student->set_rude_status(false);
        // Και με βάση την αντιμετάθεση του αλλου μαθητή 
        // αυξάνουμε τον βαθμό της φασαρίας της τάξης αυτού του μαθητή
        classrooms[some_student->get_classroom_id()]->disorder_modifier(rude_level);
    }
}

// Συναρτηση με βαση την οποία θα επιλέγεται σε ποια από τις περιπτώσεις ατνιμεταθέσεων βρισκόμαστε για τα ζευγάρια άτακτων παιδιών
void school::decide_transition(int rude_pair_counter,int scattered_rude_pairs, LinkedList<Pair>* some_sequence,
                                int pair_index, int classroom_index, bool last_pair){
    int i = classroom_index;
    int j = pair_index;

    // Aν βρισκόμαστε στο τελευταίο ζευγάρι προσθέτουμε +1 στο index γιατι θελουμε να δουλέψουμε
    // και με το τωρινό ζευγάρι
    if(last_pair)
        j = pair_index + 1;

    //Αμα πριν από τον τωρινό μονό άτακτο μαθητή
    //είχα 3 και παραπάνω συνεχόμενα άτακτα ζευγάρια τότε θα κάνω τις αντιμεταθέσεις με παιδιά από τυχαίες τάξεις
    if(rude_pair_counter >= 3){

        //Παιρνω αυτά τα προηγούμενα ζευγάρια και για κάθε έναν μαθητή επιλέγω τυχαία καποια τάξη για αντιμετάθεση
        //Επιπλεον βάζω βαθμό φασαρίας 2 γιατί φεύγει από την ακολουθία της τάξη του ο μαθητης
        for(int k=1; k<=rude_pair_counter; k++){
            student_transition(some_sequence->get(j-k), some_sequence->get(j-k)->get_student("right"), rand()%(number_of_classrooms), 2);
            student_transition(some_sequence->get(j-k), some_sequence->get(j-k)->get_student("left"), rand()%(number_of_classrooms), 2);
        }

    }
    //Αμα πριν από αυτόν το μονό άτακτο μαθητή
    //ειχα 1 άτακτο ζευγάρι και μάλιστα γνωρίζω ότι η ακολουθία έχει γενικά 3 και πάνω διάσπαρτα
    //ατακτα ζευγάρια τότε για τους μαθητές του προηγούμενου άτακτου ζευγαριου επιλέγω
    //την επόμενη τάξη για αντιμετάθεση
    else if(rude_pair_counter == 1 && scattered_rude_pairs >=3){


        //αμα τωρα βρίσκομαι στην τελευταία τάξη επιλέγω την πρώτη για αντιμετάθεση
        //και σε κάθε περίπτωση βάζω βαθμό φασαράις 2
        if(i == number_of_classrooms-1){
            student_transition(some_sequence->get(j-1), some_sequence->get(j-1)->get_student("right"), 0, 2);
            student_transition(some_sequence->get(j-1), some_sequence->get(j-1)->get_student("left"), 0, 2);                        
        }
        else{
            student_transition(some_sequence->get(j-1), some_sequence->get(j-1)->get_student("right"), i+1, 2);
            student_transition(some_sequence->get(j-1), some_sequence->get(j-1)->get_student("left"), i+1, 2);     
        }
    }
    //Αμα πριν από αυτόν το μονό άτακτο μαθητή
    //ειχα 1 ή 2 συνεχόμενα άτακτα ζευγάρια τότε θα κάνω τις αντιμεταθέσεις με παιδιά από την ίδια τάξη
    else if(rude_pair_counter > 0){
        //Παιρνω αυτά τα προηγούμενα ζευγάρια και για κάθε έναν μαθητή επιλέγω την επόμενη τάξη για αντιμετάθεση
        //Επιπλεον βάζω βαθμό φασαρίας 1 γιατί η αντιμετάθεση γίνεται στην ίδια ακολουθία
        for(int k=1; k<=rude_pair_counter; k++){
            student_transition(some_sequence->get(j-k), some_sequence->get(j-k)->get_student("right"), i, 1);
            student_transition(some_sequence->get(j-k), some_sequence->get(j-k)->get_student("left"), i, 1);
        }                    
    }
}

// Συνάρτηση που μτατρέπει όλους τους άτακτους μαθητές σε ήσυχους
void school::be_quiet(){

    // Θα διασχίσουμε όλες τις τάξεις
    for(int i=0; i<number_of_classrooms; i++){
        Classroom some_classroom = classrooms[i];
        // Παιρνουμε την ακολουθία της τάξης
        LinkedList<Pair>* some_sequence = some_classroom->get_sequence();

        //Μετρητής άτακτων ζευγαριών(συνεχόμενων)
        int rude_pair_counter = 0;

        //Ψαχνω να βρω αν έχω από 3 και πάνω διάσπαρτα άτακτα ζευγάρια στην ακολουθία
        //Μετρητής διασπαρτων άτακτων ζευγαριών
        int scattered_rude_pairs = 0;
        for(int j=0; j<some_sequence->get_size(); j++){

            Pair some_pair = some_sequence->get(j);

            Student right_student = some_pair->get_student("right");
            Student left_student = some_pair->get_student("left");

            //Αν βρήκα άτακτο ζευγάρι
            if((right_student != NULL && right_student->get_rude_status()) && (left_student != NULL && left_student->get_rude_status())){
                //Αυξάνω τον μετρητή άτακτων ζευγαριών
                rude_pair_counter++;
                //Αν βρίσκομαι στο τέλος και είναι μόνο του το άτακτο ζευγάρι τότε αυξάνω το μετρητή διάσπαρτων άτακτων ζευγαριών
                if(j == some_sequence->get_size()-1 && rude_pair_counter == 1){
                    scattered_rude_pairs++;
                }
            }
            //Αν δεν είναι άτακτο
            else{
                //Ελεγχω άμα έχω βρει μέχρι στιγμής ένα άτακτο ζευγάρι για να αυξησω τον μετρητή
                if(rude_pair_counter == 1){
                    scattered_rude_pairs++;
                }
                //μηδενιζω τον μετρητή άτακτων ζευγαριών
                rude_pair_counter = 0;
            }
        }

        rude_pair_counter = 0;
        //Διασχίζω την ακολουθία της τάξης
        std::cout << "Classroom: " << i << std::endl;
        for(int j=0; j<some_sequence->get_size(); j++){

            // Παίρνω ένα ζευγάρι
            Pair some_pair = some_sequence->get(j);

            // Παιρνω τους δύο μαθητες
            Student right_student = some_pair->get_student("right");
            Student left_student = some_pair->get_student("left");

            //Πρώτη περίπτωση όταν μόνο ένα παιδί κάνει φασαρία(ο μαθητής στα δεξιά ή μαθητής στα αριστερά)
            if(((right_student != NULL && right_student->get_rude_status()) && ((left_student != NULL && !left_student->get_rude_status()) || left_student == NULL)) ||
                ((left_student != NULL && left_student->get_rude_status()) && ((right_student != NULL && !right_student->get_rude_status()) || right_student == NULL))){

                // αυτη η συνάρτηση κανει αντιμετάθεση τα προηγούμενα άτακτα ζευγάρια(αν υπήρχαν)
                decide_transition(rude_pair_counter,scattered_rude_pairs, some_sequence, j, i, false);

                //μηδενίζω τον μετρητή συνεχόμενων άτακτων ζευγαριών
                rude_pair_counter = 0;  

                //και τελός κάνω αντιμετάθεση αυτόν τον μονό άτακτο μαθητή
                if(right_student != NULL && right_student->get_rude_status())
                    student_transition(some_pair, right_student, i, 1);
                else
                    student_transition(some_pair, left_student, i, 1);
    
            }
            
            //Δεύτερη περίπτωση βρήκαμε άτακτο ζευγάρι
            else if((right_student != NULL && right_student->get_rude_status()) && (left_student != NULL && left_student->get_rude_status())){

                std::cout << "Rude pair" << std::endl;

                //Αν είναι το τελευταίο ζευγάρι πρέπει να κάνω τώρα τις αντιμεταθέσεις γιατί
                //θα αλλάξει η τάξη στο επόμενο loop
                rude_pair_counter++;
                if(j == some_sequence->get_size() - 1){
                    decide_transition(rude_pair_counter,scattered_rude_pairs, some_sequence, j, i, true);
                }

            }
            //Αλλιως είναι ήσυχο ζευγάρι
            else{
                std::cout << "Pair is calm" << std::endl;

                if(rude_pair_counter > 0)
                    decide_transition(rude_pair_counter,scattered_rude_pairs, some_sequence, j, i, false);

                rude_pair_counter = 0;
            }

        }
    }
}

