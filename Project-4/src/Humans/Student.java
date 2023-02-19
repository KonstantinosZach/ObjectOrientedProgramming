package Humans;

abstract public class Student extends Person {

    protected Student(String name, int classroomId, int floorNumber, boolean inClass, int counterOfFatigue){
        super(name, classroomId, floorNumber, inClass, counterOfFatigue);
        System.out.println("A new Student has been constructed");
        print();
    }

    abstract public void attend(int hours);
}
