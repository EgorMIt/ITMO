package human;

import javax.naming.NamingException;
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

    public static class Actions{
        public static void away(String name1, String name2, String place){
            System.out.println("Затем " + name1 + " пошел в " + place + " ждать " + name2);
        }

        public static void kiss(String name1, String name2){
            System.out.println(name1 + " подошел к " + name2 + " , поцеловал в полную руку и сказал: " + null + " !");
        }

        public static void walk(String name1, String name2, String place){
            System.out.println(name1 + " и " + name2 + " должны были идти на " + place + " вместе");
        }

        public static void think(String name1, String name2, String name3){
            System.out.println(name1 + " не сможет туда попасть, если " + name2 + " окажется прав насчет " + name3);
        }

        public static void worry(String name1, String name2, String place){
            System.out.println(name1 + " вряд ли была спокойна, если бы поняла, что " + name2 + " живет на " + place);
        }

        public static void getup(String name1, String quality1, String quality2, String quality3, String place){
            System.out.println("Вставая из-за " + place + " , " + name1 + " чувствовал, что он " + quality1 + " " +
                    quality2 +" " +quality3);
        }

        public static void description(String name1, String name2, String place){
            System.out.println(name1 + " чувствовал вкус плюшек, солнце светило в " + place + " ,и "
                    + name2 + " вглядела милой");
        }

        public static void wait(String name1, String name2){
            System.out.println(name1 + " сказал, что прилетит за " + name2 + " не раньше 6");
        }

        public static void eat(String name1, String quality1){
            System.out.println(quality1 + " " + name1 + " откусил кусочек");
        }

        public static void patch(String name1, String name2){
            System.out.println("Пока " + name1 + " жевал, " + name2 + " залипила шишку пластырем");
            System.out.println(name2 + " поцеловала больное место и спросила: " + null);
        }

        public static void pointless(String name1, String name2, String name3){
            System.out.println("Когда " + name1 + " оторавал глааза от чашки и посмотрел на нее, " + name2 +
                    " ничего не ответила, так как было бессмысленно разуверять малыша в существовании " + name3);
        }

        public static void sorry(String name1, String name2){
            System.out.println(name1 + " пожалел, что начал говорить с " + name2 + " о таких вещах");
        }

        public static void words(String name1, String name2, String quality1, String quality2){
            System.out.println("Но эти слова не показались " + name1 + " " + quality1 + " и " + quality2 +
                    " по сравнению с тем, что он рассказывал о " + name2);
        }

        public static  void when(String name1, String name2){
            System.out.println(name1 + " толокм не понял, когда прилетит " + name2 + " и переспросил его");
            System.out.println(name2 + " сказал, что не раньше 6, не позже 7, то есть примероно к 9");
        }

        public static void believe(String name1, String name2, String quality1, String quality2, String place1){
            System.out.println(name1 + " прождал челую вечность, и ему начало казаться, что " +
                    name2 + " действительно не существует");
            System.out.println("Когда " + name1 + " уже готов был поверить, " + quality1 + " и "
            + quality2 + " " + name2 + " влетел в " + place1);
        }

        public static void drink(String name1, String name2, String quality1, String quality2, String place1){
            System.out.println(name1 + " подлетел к аквариуму в " + place1 + ", где плавали "
                    + quality1 + " рыбки, и стал пить воду");
            System.out.println(name2 + " не заметил, что его лоб " + quality2);
        }

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