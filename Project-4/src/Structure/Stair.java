package Structure;
import Humans.Student;

public class Stair extends Area {
    
    Stair(){ System.out.println("A Stair has been constructed"); }

    @Override
    void enter(Student tempStudent){
        System.out.println(tempStudent.getName() + " enters Stair");
        super.enter(tempStudent);
    }

    @Override
    Student exit(){
        System.out.println(tempStudent.getName() + " exits Stair");
        return super.exit();
    }
}
