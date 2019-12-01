package info.moves;
import ru.ifmo.se.pokemon.*;

public class SleepPowder extends SpecialMove {
    public  SleepPowder(){
        super(Type.GRASS,0 ,75);
    }
    @Override
    public void applyOppEffects(Pokemon p) {
        Effect.sleep(p);
    }
    @Override
    protected String describe() {
        return "усыпляет";
    }

}
