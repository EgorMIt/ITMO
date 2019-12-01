package info.pockemons;
import info.moves.*;
import ru.ifmo.se.pokemon.*;

public class Misdreavus extends Pokemon {
    public Misdreavus(String name,int level){
        super(name,level);
        setStats(60,60,60,85,85,85);
        setType(Type.GHOST);
        setMove(new Rest(), new SwordDance(), new Swagger());
    }
}