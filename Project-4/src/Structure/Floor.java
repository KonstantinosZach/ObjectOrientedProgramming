package Structure;

import java.util.Vector;
import Humans.Student;
import Humans.Teacher;

public class Floor {
    
    private Corridor corridor;
    private Vector<Classroom> classrooms;
    static private int  classroomsPerFloor = 6;

    Floor(int classroomCapacity){
        System.out.println("A Floor has been constructed");
        corridor = new Corridor();
        classrooms = new Vector<Classroom>(classroomsPerFloor);
        for(int i=0; i<classroomsPerFloor; i++){
            classrooms.add(i, new Classroom(classroomCapacity));
        }
    }

    void enter(Student tempStudent){
        System.out.println(tempStudent.getName() + " enters Floor");
        corridor.enter(tempStudent);
        int classroomId = corridor.getStudent().getClassroomId();
        classrooms.get(classroomId).enter(corridor.exit());
    }

    Student exit(int classroomNumber){
        Student toExit = classrooms.get(classroomNumber).exit();
        if(toExit != null){
            corridor.enter(toExit);
            return corridor.exit();
        }
        else{
            return null;
        }
    }

    void teachersOut(){
        for(int i=0; i<classroomsPerFloor; i++){
            classrooms.get(i).teachersOut();
        }
    }

    void enter(Teacher teacher){
        int classroomId = teacher.getClassroomId();
        classrooms.get(classroomId).enter(teacher);
    }

    void operate(int hours){
        for(int i=0; i<classrooms.size(); i++)
            classrooms.get(i).operate(hours);
    }

    void print(){
        for(int i=0; i<classroomsPerFloor; i++){
            System.out.println("The classroom: " + i + " contains:");
            classrooms.get(i).print();
        }
    }

    static public int getClassroomsPerFloor(){ return classroomsPerFloor; }
    

}
