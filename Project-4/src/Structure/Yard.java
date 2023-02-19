package Structure;
import Humans.Student;

public class Yard extends Area {
    
    Yard(){ System.out.println("A Yard has been constructed"); }

    @Override
    void enter(Student tempStudent){
        System.out.println(tempStudent.getName() + " enters Yard");
        super.enter(tempStudent);
    }

    @Override
    Student exit(){
        System.out.println(tempStudent.getName() + " exits Yard");
        return super.exit();
    }
}
