import java.util.ArrayList;
import java.util.List;

public class Place extends AbstractPlace {
    private final List<Skills> skills = new ArrayList<Skills>();

    private Places type;

    public Place(String name){
        this.placeName = name;
        System.out.println("Место - " + name  + " успешно создано!");
    }

    public void setType(Places type){
        this.type = type;
        typeName = "";
        switch (type){
            case Roof : typeName = "Крыша";
                break;
            case Room : typeName = "Комната";
                break;
        }
        System.out.println(placeName +" объявлена как " + typeName);
    }

    public Places getType() {
        return this.type;
    }

    public String getPlace() {
        return placeName == null ? "..." : placeName;
    }

    public List<Skills> getSkills() {
        return skills;
    }

}