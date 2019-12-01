import java.util.ArrayList;
import java.util.List;

public class Human extends AbstractHuman {
    private final List<Skills> skills = new ArrayList<Skills>();

    public Human(){
        System.out.println("Обычный человек успешно создан...");
    }

    public Human (String name){
        this.name = name;
        System.out.println("Человек - " + name  + " успешно создан!");
    }

    public List<Skills> getSkills() {
        return skills;
    }

    public boolean addSkill(Skills skill){
        if (skills.add(skill)){
            System.out.println("Объекту - \"" + this.getName() + "\" успешно присвоено умение " + skill.getName()
                    + " (" + skill.getInfo()+ ")");
            return true;
        }
        else{
            System.out.println("При добавлении умения произошла ошибка...");
            return false;
        }
    }

    public static void away(String name1, String name2, String place){
        System.out.println("Затем " + name1 + " пошел в " + place + " ждать " + name2);
    }

    public static void kiss(String name){
        System.out.println(name + " подошел к ней, поцеловал в полную руку и сказал: " + null + " !");
    }

    public static void walk(String name1, String name2, String place){
        System.out.println(name1 + " и " + name2 + " должны были идти на " + place + " вместе");
    }

    public static void think(String name1, String name2, String name3){
        System.out.println(name1 + " не сможет туда попасть, если " + name2 + " окажется прав насчет " + name3);
    }
    @Override
    public int hashCode() {
        return super.hashCode()+this.getName().hashCode();
    }

    @Override
    public boolean equals(Object obj) {
        return obj.hashCode() == this.hashCode();
    }

    @Override
    public String toString() {
        return "Человек по имени " + this.getName();
    }

    @Override
    public String getName() {
        return name;
    }
}