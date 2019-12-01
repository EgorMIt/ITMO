package human;

public class Skills {
    private final String name;
    private final String info;

    public Skills(String name, String info){
        this.name = name;
        this.info = info;
    }

    public String getName(){
        return name;
    }

    public String getInfo(){
        if (info == null)
            return "...";
        else
            return info;

    }

}
