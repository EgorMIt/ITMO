package info.moves;
import ru.ifmo.se.pokemon.*;

public class FireBlast extends SpecialMove{
    public FireBlast(){
        super(Type.FIRE, 120,85);
    }
    private boolean flag;
    @Override
    public void applyOppEffects(Pokemon poc) {
        if (Math.random() <= 0.3) {
            flag = true;
            Effect.burn(poc);
        }
    }
    @Override
    protected String describe(){
        if(flag) return "дамажит и поджигает";
        else return "дамажит";
    }
}
