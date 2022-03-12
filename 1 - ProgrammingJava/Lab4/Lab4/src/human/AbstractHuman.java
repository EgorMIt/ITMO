package human;

public abstract class AbstractHuman implements HumanAble {
    public String name;
    public int age;

    public AbstractHuman(){
    }

    public AbstractHuman(String name){
        this.name = name;
    }

    public AbstractHuman(String name, int age){
        this.name = name;
        this.age = age;
    }

    public String getName(){
        return name;
    }
}
