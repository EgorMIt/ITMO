package info.moves;
import ru.ifmo.se.pokemon.*;

public class HammerArm extends PhysicalMove{
    public HammerArm(){
        super(Type.NORMAL, 100, 90);
    }
    @Override
    public void applySelfEffects (Pokemon p){
        p.setMod(Stat.SPEED,-1);
    }
    @Override
    protected String describe(){
        return "кидает молот";
    }
}
