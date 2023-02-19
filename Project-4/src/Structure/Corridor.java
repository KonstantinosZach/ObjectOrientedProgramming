package Structure;
import Humans.Student;

public class Corridor extends Area {

    Corridor(){ System.out.println("A Corridor has been constructed"); }

    @Override
    void enter(Student tempStudent){
        System.out.println(tempStudent.getName() + " enters Corridor");
        super.enter(tempStudent);
    }

    @Override
    Student exit(){
        System.out.println(tempStudent.getName() + " exits Corridor");
        return super.exit();
    }  
}
