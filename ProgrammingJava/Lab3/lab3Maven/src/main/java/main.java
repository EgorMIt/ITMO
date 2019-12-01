public class main {
    public static void main(String[] args){
        System.out.println();
        HumanAble karlson = new Human("Карлсон");
        karlson.addSkill(new Skills("Летать", null));
        System.out.println();

        HumanAble krister = new Human("Кристер");
        krister.addSkill(new Skills("Доказывать", karlson.toString() +" не существует"));
        System.out.println();

        HumanAble malish = new Human("Малыш");
        malish.addSkill(new Skills("Подойти", null));
        malish.addSkill(new Skills("Чмокнуть", "в полную руку"));
        System.out.println();

        PlaceAble location1 = new Place("Локация1");
        location1.setType(Places.Room);
        malish.addSkill(new Skills("Ждать", karlson.toString()));
        System.out.println();

        PlaceAble location2 = new Place("Локация2");
        location2.setType(Places.Roof);
        malish.addSkill(new Skills("Гулять", location2.getType().toString()));
        karlson.addSkill(new Skills("Гулять", location2.getType().toString()));
        System.out.println();

        Human.kiss(malish.getName().toString());
        Human.away(malish.getName().toString(), karlson.getName().toString(), location1.getType().toString());
        Human.walk(malish.getName().toString(), karlson.getName().toString(), location1.getType().toString());
        Human.think(malish.getName().toString(), krister.getName().toString(), karlson.getName().toString());
    }
}
