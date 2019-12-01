package quality;

public class Quality extends AbstractQuality {
    private QualityTypes type;

    public Quality(String name){
        this.qualityName = name;
        System.out.println("Характеристика - " + name  + " успешно создана!");
    }

    public void setType(QualityTypes type){
        this.type = type;
        typeName = "";
        switch (type){
            case Full : typeName = "Сытый";
                break;
            case Satisfied: typeName = "Доволен жизнью";
                break;
            case Happy: typeName = "Веселый";
                break;
            case Dangerous: typeName = "Опасный";
                break;
            case Anxious: typeName = "Тревожный";
                break;
            case Grateful: typeName = "Благодарный";
                break;
            case Hot: typeName = "Горячий";
                break;
        }
        System.out.println(qualityName +" обозначено как " + typeName);
    }

    public String getType() {
        return this.typeName;
    }

    public String getQuality() {
        return qualityName == null ? "..." : qualityName;
    }
}
