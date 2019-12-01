package info.pockemons;
import info.moves.*;
import ru.ifmo.se.pokemon.*;

public class Dragonite extends Pokemon {
    public Dragonite(String name, int level){
        super(name,level);
        setStats(91,134,95,100,100,80);
        setType(Type.DRAGON, Type.FLYING);
        setMove(new Swagger(), new Facade(), new HammerArm(), new FireBlast());
    }
}