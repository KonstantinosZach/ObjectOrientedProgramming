package App;

import java.util.Collections;
import java.util.Vector;

import Humans.Junior;
import Humans.Senior;
import Humans.Student;
import Humans.Teacher;
import InputData.InputData;
import Structure.Floor;
import Structure.SchoolBuilding;

public class Main {
    public static void main(String[] args) throws Exception {

        int cClass = Integer.parseInt(args[0]);
        int lJunior = Integer.parseInt(args[1]);
        int lSenior = Integer.parseInt(args[2]);
        int lTeacher = Integer.parseInt(args[3]);

        SchoolBuilding schoolBuilding = new SchoolBuilding(cClass, lJunior, lSenior, lTeacher);

        int allStudents = Floor.getClassroomsPerFloor()*SchoolBuilding.getNumberOffloors()*cClass;
        int allTeachers = Floor.getClassroomsPerFloor()*SchoolBuilding.getNumberOffloors();

        Vector<Student> students = new Vector<Student>(allStudents);
        Vector<Teacher> teachers = new Vector<Teacher>(allTeachers);

        int indexOfNamesStudents = 0;
        int indexOfNamesTeachers = 0;

        for(int currentFloor=0; currentFloor<SchoolBuilding.getNumberOffloors(); currentFloor++){
            for(int currentClassroom=0; currentClassroom<Floor.getClassroomsPerFloor(); currentClassroom++){

                teachers.add(new Teacher(InputData.namesOfTeachers[indexOfNamesTeachers],
                currentClassroom, currentFloor, false, 0));

                indexOfNamesTeachers++;
                if(indexOfNamesTeachers >= InputData.namesOfTeachers.length){
                    indexOfNamesTeachers = 0;
                }

                for(int currentStudent=0; currentStudent<cClass; currentStudent++){
                    if(currentClassroom < 3){
                        students.add(new Junior(InputData.namesOfStudents[indexOfNamesStudents],
                        currentClassroom, currentFloor, false, 0));
                    }
                    else{
                        students.add(new Senior(InputData.namesOfStudents[indexOfNamesStudents],
                        currentClassroom, currentFloor, false, 0));
                    }

                    indexOfNamesStudents++;
                    if(indexOfNamesStudents >= InputData.namesOfStudents.length){
                        indexOfNamesStudents = 0;
                    }
                }
            }
        }

        Collections.shuffle(students);
        Collections.shuffle(teachers);

        System.out.println("\nStudents started entering school\n");
        for(int currentStudent=0; currentStudent < allStudents; currentStudent++){
            schoolBuilding.enter(students.get(currentStudent));
        }

        System.out.println("\nTeachers are being placed in Classrooms\n");
        for(int currentTeacher=0; currentTeacher < allTeachers; currentTeacher++){
            schoolBuilding.place(teachers.get(currentTeacher));
        }

        int operateHours = Integer.parseInt(args[4]);
        schoolBuilding.operate(operateHours);
        schoolBuilding.empty();

    }
}
