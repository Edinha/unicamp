package main;

import card.MagicCard;
import card.MinionCard;

public class Main {

	public static void main(String[] args) {
		MinionCard darkMagician = new MinionCard(1, "Mago negro", 7, 10, 10, 10);
		MinionCard blueEyesWhiteDragon = new MinionCard(2, "Dragão branco de olhos azuis", 9, 5, 6, 20);

		MagicCard monsterReborn = new MagicCard(3, "Monstro que renasce", 0, false, 5);
		MagicCard mirrorForce = new MagicCard(5, "Força espelho", 0, true, 3);

		System.out.println("Carta primeira " + darkMagician.toString());
		System.out.println("Carta segunda " + blueEyesWhiteDragon.toString());
		System.out.println("Carta terceira " + monsterReborn.toString());
		System.out.println("Carta quarta " + mirrorForce.toString());
	}

}
