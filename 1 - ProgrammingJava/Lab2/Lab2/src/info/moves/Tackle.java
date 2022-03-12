package info.moves;
import ru.ifmo.se.pokemon.*;

public class Tackle extends PhysicalMove{
    public Tackle(){
        super(Type.NORMAL,35,95);
    }
    @Override
    protected String describe(){
        return "толкнул";
    }
}