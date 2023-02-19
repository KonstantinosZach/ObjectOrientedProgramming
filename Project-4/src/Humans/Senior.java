package Humans;

public class Senior extends Student{

    private static int rateOfFatigue;

    public Senior(String name, int classroomId, int floorNumber, boolean inClass, int counterOfFatigue){
        super(name, classroomId, floorNumber, inClass, counterOfFatigue);
    }

    @Override
    public void attend(int hours) {
        for(int i=0; i<hours; i++)
            counterOfFatigue += rateOfFatigue;     
    }

    static public void setRateOfFatigue(int rate){ rateOfFatigue = rate; }

    static public int getRateOfFatigue(){ return rateOfFatigue; }   
}
