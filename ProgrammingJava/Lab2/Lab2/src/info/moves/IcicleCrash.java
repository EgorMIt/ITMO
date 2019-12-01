package info.moves;

import ru.ifmo.se.pokemon.*;

public class IcicleCrash extends PhysicalMove{
    public IcicleCrash(){
        super(Type.NORMAL, 85,90);
    }
    @Override
    public void applyOppEffects(Pokemon p) {
        if (Math.random() <= 0.3){
            Effect.flinch(p);
        }
    }
    @Override
    protected String describe(){
        return "морозит";
    }
}