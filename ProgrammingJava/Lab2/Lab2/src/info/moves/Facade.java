package info.moves;
import ru.ifmo.se.pokemon.*;

public class Facade extends PhysicalMove {
    public Facade(){
        super(Type.NORMAL, 70, 100);
    }
    private boolean flag;
    @Override
    public void applyOppDamage(Pokemon poc, double damage){
        Status cond = poc.getCondition();
        flag = true;
        if (cond.equals(Status.POISON) || cond.equals(Status.BURN) || cond.equals(Status.PARALYZE)) {
            poc.setMod(Stat.HP, -2*(int)Math.round(damage));
        }
    }
    @Override
    protected String describe(){
        if(flag) return "сильно бьет";
        else return "бьет";
    }
}
