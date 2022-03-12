import human.Human;
import human.HumanAble;
import human.Skills;
import place.Place;
import place.PlaceAble;
import place.PlaceTypes;
import quality.QualityTypes;
import quality.Quality;
import quality.QualityAble;

public class main {
    public static void main(String[] args){
        StoryEnd.EndOfStory ending = new StoryEnd.EndOfStory();
        try {
            HumanAble karlson = new Human("Карлсон");
            karlson.addSkill(new Skills("Летать", null));
            System.out.println();

            HumanAble mother = new Human("Мама");
            karlson.addSkill(new Skills("Выглядеть мило", null));
            karlson.addSkill(new Skills("Беспокоиться", "за Малыша"));
            System.out.println();

            HumanAble krister = new Human("Кристер");
            krister.addSkill(new Skills("Доказывать", karlson.toString() + " не существует"));
            System.out.println();

            HumanAble malish = new Human("Малыш");
            malish.addSkill(new Skills("Чмокнуть", "в полную руку"));

            QualityAble quality1 = new Quality("Качество1");
            QualityAble quality2 = new Quality("Качество2");
            QualityAble quality3 = new Quality("Качество3");
            QualityAble quality4 = new Quality("Качество4");
            QualityAble quality5 = new Quality("Качество5");
            QualityAble quality6 = new Quality("Качество6");
            QualityAble quality7 = new Quality("Качество7");
            quality1.setType(QualityTypes.Full);
            quality2.setType(QualityTypes.Happy);
            quality3.setType(QualityTypes.Satisfied);
            quality4.setType(QualityTypes.Dangerous);
            quality5.setType(QualityTypes.Anxious);
            quality6.setType(QualityTypes.Grateful);
            quality7.setType(QualityTypes.Hot);
            System.out.println();

            PlaceAble location1 = new Place("Локация1");
            PlaceAble location2 = new Place("Локация2");
            PlaceAble location3 = new Place("Локация3");
            location1.setType(PlaceTypes.Table);
            location2.setType(PlaceTypes.Room);
            location3.setType(PlaceTypes.Roof);

            System.out.println();
            malish.addSkill(new Skills("Ждать", karlson.toString()));
            malish.addSkill(new Skills("Гулять", location3.getTypeName()));
            karlson.addSkill(new Skills("Гулять", location3.getTypeName()));
            System.out.println();

            Human.Actions.eat(malish.getName(), quality6.getType());
            Human.Actions.patch(malish.getName(), mother.getName());
            Human.Actions.pointless(malish.getName(), mother.getName(), karlson.getName());
            Human.Actions.sorry(malish.getName(), mother.getName());
            Human.Actions.words(mother.getName(), karlson.getName(), quality4.getType(), quality5.getType());

            Human.Actions.worry(mother.getName(), karlson.getName(), location3.getTypeName());
            Human.Actions.getup(malish.getName(), quality1.getType(), quality2.getType(),
                    quality3.getType(), location1.getTypeName());
            Human.Actions.description(malish.getName(), mother.getName(), location2.getTypeName());
            Human.Actions.kiss(malish.getName(), mother.getName());
            Human.Actions.away(malish.getName(), karlson.getName(), location2.getTypeName());
            Human.Actions.walk(malish.getName(), karlson.getName(), location3.getTypeName());
            Human.Actions.think(malish.getName(), krister.getName(), karlson.getName());
            Human.Actions.wait(karlson.getName(), malish.getName());

            Human.Actions.when(malish.getName(), karlson.getName());
            Human.Actions.believe(malish.getName(), karlson.getName(), quality2.getType(), quality3.getType(), location2.getTypeName());
            Human.Actions.drink(karlson.getName(), malish.getName(), quality2.getType(), quality7.getType(), location2.getTypeName());
        }
         catch(NamingException ex){
            System.out.println("NamingException catched: " + ex.getMessage());
        }
        catch(PermissionEcxeption ex){
            System.out.println("PermissionException catched: " + ex.getMessage());
        }
        finally {
            ending.PrintInf();
        }
    }
}