package place;

public class Place extends AbstractPlace {
    private PlaceTypes type;

    public Place(String name){
        this.placeName = name;
        System.out.println("Место - " + name  + " успешно создано!");
    }

    public void setType(PlaceTypes type){
        this.type = type;
        typeName = "";
        switch (type){
            case Roof : typeName = "Крыша";
                break;
            case Room : typeName = "Комната";
                break;
            case Table: typeName = "Стол";
                break;
        }
        System.out.println(placeName +" объявлена как " + typeName);
    }

    public String getTypeName() {
        return this.typeName;
    }

    public String getPlace() {
        return placeName == null ? "..." : placeName;
    }
}