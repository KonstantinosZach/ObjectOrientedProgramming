package Structure;

import java.util.Vector;

import Humans.Junior;
import Humans.Senior;
import Humans.Student;
import Humans.Teacher;

public class SchoolBuilding{

    private static int numberOfFloors;
    private Yard yard;
    private Stair stair;
    private Vector<Floor> floor;

    static{
        numberOfFloors = 3;
    }

    public SchoolBuilding(int studentsPerClassroom, int juniorRate, int seniorRate, int teacherRate){
        System.out.println("A new SchoolBuilding has been constructed");
        yard = new Yard();
        stair = new Stair();
        floor = new Vector<Floor>(numberOfFloors);
        setRateOfFatigue(juniorRate, seniorRate, teacherRate);
        for(int i=0; i<numberOfFloors; i++){
            floor.add(i, new Floor(studentsPerClassroom));
        }

    }

    public void enter(Student tempStudent){
        System.out.println(tempStudent.getName() + " enters School");

        yard.enter(tempStudent);
        stair.enter(yard.exit());

        int floorNumber = stair.getStudent().getFloorNumber();
        floor.get(floorNumber).enter(stair.exit());

    }

    public void empty(){
        System.out.println("\nStudents start exiting\n");
        for(int i=0; i<numberOfFloors; i++){
            for(int j=0; j<Floor.getClassroomsPerFloor(); j++){
                Student toExit = floor.get(i).exit(j);
                //remove all the student of the current classroom
                //if we get null it means that the classroom in now empty
                while(toExit != null){
                    stair.enter(toExit);
                    yard.enter(stair.exit());
                    yard.exit();
                    toExit = floor.get(i).exit(j);
                }
            }
        }

        System.out.println("\nTeachers start exiting\n");
        for(int i=0; i<numberOfFloors; i++){
            floor.get(i).teachersOut();
        }

    }

    public void place(Teacher teacher){
        int floorNumber = teacher.getFloorNumber();
        floor.get(floorNumber).enter(teacher);
    }

    public void print(){
        System.out.println("School life consists of:");
        for(int i=0; i<numberOfFloors; i++){
            System.out.println("Floor: " + i);
            floor.get(i).print();
        }
    }

    public void operate(int hours){
        System.out.println("\nThe school will operate for " + hours + " hours");
        for(int i=0; i<numberOfFloors; i++){
            floor.get(i).operate(hours);
        }
    }

    static public void setRateOfFatigue(int juniorRate, int seniorRate, int teacherRate){
        Junior.setRateOfFatigue(juniorRate);
        Senior.setRateOfFatigue(seniorRate);
        Teacher.setRateOfFatigue(teacherRate);
    }

    static public int getNumberOffloors(){ return numberOfFloors; }
}
