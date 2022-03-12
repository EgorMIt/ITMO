package info.moves;

import ru.ifmo.se.pokemon.*;

public class SwordDance extends SpecialMove{
    public SwordDance(){
        super(Type.NORMAL,0,95);
    }
    @Override
    public void applySelfEffects(Pokemon p) {
        p.setMod(Stat.ATTACK,+2);
    }

    @Override
    protected String describe(){
        return "усилил атаку";
    }
}
