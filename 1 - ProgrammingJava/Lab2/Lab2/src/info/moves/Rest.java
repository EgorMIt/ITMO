package info.moves;
import ru.ifmo.se.pokemon.*;

public class Rest extends StatusMove{

    public Rest(){
        super(Type.NORMAL,0,0);

    }
    @Override
    protected void applySelfEffects(Pokemon att){
        Effect eff = new Effect();
        eff = eff.condition(Status.SLEEP);
        eff = eff.turns(2);
        att.restore();
        att.addEffect(eff);
    }
    protected boolean checkAccuracy(Pokemon att,Pokemon def){
        return true;
    }
    @Override
    protected String describe(){
        return "адыхает";
    }
}