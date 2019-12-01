package info;

import ru.ifmo.se.pokemon.*;
import info.pockemons.*;
import info.moves.*;

public class Main {
    public static void main(String[] args) {
        Battle b = new Battle();
        Registeel p1 = new Registeel("Круглоголовый",2);
        Mismagius p2 = new Mismagius("Шляпник", 2);;
        Misdreavus p3 = new Misdreavus("Медузич",2);
        Dratini p4 = new Dratini("Драк", 2);;
        Dragonair p6 = new Dragonair("ДракПокруче", 2);
        Dragonite p5 = new Dragonite("ДракКрутой",2);

        b.addAlly(p1);
        b.addAlly(p2);
        b.addAlly(p3);
        b.addFoe(p4);
        b.addFoe(p5);
        b.addFoe(p6);
        b.go();
    }
}
