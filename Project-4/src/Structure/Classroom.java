package Structure;

import java.util.Vector;

import Humans.Student;
import Humans.Teacher;

public class Classroom {

    private int numberOfStudents;
    private Vector<Student> students;
    private Teacher teacher;

    Classroom(int numberOfStudents){
        this.numberOfStudents = numberOfStudents;
        students = new Vector<Student>(this.numberOfStudents);
        System.out.println("A classroom has been constructed");
    }

    void enter(Student student){
        if(students.size() < numberOfStudents){
            System.out.println(student.getName() + " enters Classroom");
            students.add(student);
            students.lastElement().setInClass(true);
        }
    }

    //removes the last student of the vector
    Student exit(){
        Student toExit = null;
        //if the vector is empty we return null
        if(!students.isEmpty()){
            toExit = students.lastElement();
            System.out.println(toExit.getName() + " starts exiting");
            students.removeElement(toExit);
            System.out.println(toExit.getName() + " exits classroom");
            toExit.setInClass(false);
        }
        return toExit;
    }

    void teachersOut(){
        System.out.println(teacher.getName() + " teacher is out");
        teacher.setInClass(false);
        teacher = null;
    }

    void enter(Teacher teacher){
        if(this.teacher == null){
            this.teacher = teacher;
            System.out.println(this.teacher.getName() + " is in classroom");
            this.teacher.setInClass(true);
        }
    }

    void operate(int hours){
        for(int i=0; i<students.size(); i++){
            students.get(i).attend(hours);
        }
        teacher.teach(hours);
    }

    void print(){
        System.out.println("Students:");
        for(int i=0; i<students.size(); i++)
            students.get(i).print();
        
        System.out.println("Teacher:");
        if(teacher != null)
            teacher.print();
    }

    int getNumberOfStudents(){ return numberOfStudents; }

}
