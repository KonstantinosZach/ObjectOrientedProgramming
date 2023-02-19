package Structure;
import Humans.Student;

abstract public class Area {

    protected Student tempStudent;

    void enter(Student tempStudent){
        this.tempStudent = tempStudent;
    }

    Student exit(){
        Student studentToLeave = tempStudent;
        tempStudent = null;
        return studentToLeave;
    }

    Student getStudent(){ return tempStudent; }
}
