package info.moves;
import ru.ifmo.se.pokemon.*;

public class Swagger extends SpecialMove{
    public Swagger(){
        super(Type.NORMAL,0,90);
    }
    @Override
    protected String describe(){
        return "флексит";
    }
    @Override
    protected void applyOppEffects(Pokemon opp){
        opp.confuse();
        opp.setMod(Stat.ATTACK,2);
    }
}