package info.pockemons;
import info.moves.*;
import ru.ifmo.se.pokemon.*;

public class Mismagius extends Pokemon {
    public Mismagius(String name, int level){
        super(name,level);
        setStats(60,60,60,105,105,105);
        setType(Type.GHOST);
        setMove(new Rest(), new SwordDance(), new Swagger(), new IcicleCrash());
    }
}