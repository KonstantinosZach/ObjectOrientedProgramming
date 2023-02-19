package Humans;

public class Teacher extends Person {
    
    private static int rateOfFatigue;

    public Teacher(String name, int classroomId, int floorNumber, boolean inClass, int counterOfFatigue){
        super(name, classroomId, floorNumber, inClass, counterOfFatigue);
        System.out.println("A new Teacher has been constructed");
        print();
    }

    public void teach(int hours){
        for(int i=0; i<hours; i++)
            counterOfFatigue += rateOfFatigue;
    }

    static public void setRateOfFatigue(int rate){ rateOfFatigue = rate; }

    static public int getRateOfFatigue(){ return rateOfFatigue; }
}
