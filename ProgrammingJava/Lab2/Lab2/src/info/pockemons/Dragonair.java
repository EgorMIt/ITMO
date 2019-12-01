package info.pockemons;
import info.moves.*;
import ru.ifmo.se.pokemon.*;

public class Dragonair extends Pokemon {
    public Dragonair(String name, int level){
        super(name,level);
        setStats(61,84,65,70,70,70);
        setType(Type.DRAGON);
        setMove(new Swagger(), new Facade(), new HammerArm());
    }
}