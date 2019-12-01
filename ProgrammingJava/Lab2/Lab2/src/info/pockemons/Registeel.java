package info.pockemons;
import  info.moves.*;
import ru.ifmo.se.pokemon.*;

public class Registeel extends Pokemon{
    public Registeel (String name, int lvl){
        super (name, lvl);
        setStats(57,80,91,80,87,75);
        setType(Type.STEEL);
        setMove(new Tackle(), new SleepPowder(),new Rest(), new StunSpore());
    }
}
