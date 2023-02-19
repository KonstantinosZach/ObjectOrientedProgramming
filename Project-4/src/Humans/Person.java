package Humans;

abstract public class Person {

    final private String name;      //we set as final these variables cause we dont want them to change
    final private int classroomId;
    final private int floorNumber;
    private boolean inClass;
    protected int counterOfFatigue;

    protected Person(String name, int classroomId, int floorNumber, boolean inClass, int counterOfFatigue){
        this.name = name;
        this.classroomId = classroomId;
        this.floorNumber = floorNumber;
        this.inClass = inClass;
        this.counterOfFatigue = counterOfFatigue;
        
    }

    public void print(){
        System.out.println("name: " + name + " classroom id: " + classroomId + 
        " floor number: " + floorNumber + " in class: " + inClass + " fatigue: " + counterOfFatigue);
    }

    public String getName(){ return name; }

    public int getClassroomId(){ return classroomId; }

    public int getFloorNumber(){ return floorNumber; }

    public boolean getInClass(){ return inClass; }

    public void setInClass(boolean state){ inClass = state; }

    public int getCounterOfFatigue(){ return counterOfFatigue; }

}

