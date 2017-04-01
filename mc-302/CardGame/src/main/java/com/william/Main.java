package com.william;

import com.william.card.Minion;
import com.william.card.magic.Buff;
import com.william.card.magic.Damage;
import com.william.card.magic.DamageArea;
import com.william.deck.Deck;

public class Main {

	public static void main(String[] args) {
		Deck deck = new Deck();

		Minion darkMagician = new Minion("Mago negro", 7, 10, 10, 10);
		Minion demonSkullKing = new Minion("Rei caveira", 3, 3, 2, 30);
		Minion blueEyesWhiteDragon = new Minion("Dragão branco de olhos azuis", 9, 5, 6, 20);

		Buff blackPendant = new Buff("Pendente negro", 5, 12, 0);
		Buff monsterReborn = new Buff("O monstro que renasce", 20, 0, 20);

		Damage justDeserts = new Damage("Apenas sobremesas", 2, 7);

		DamageArea tremendousFire = new DamageArea("Fogo medonho", 1, 8);

		deck.addCard(darkMagician);
		deck.addCard(demonSkullKing);
		deck.addCard(blueEyesWhiteDragon);

		deck.addCard(blackPendant);
		deck.addCard(justDeserts);
		deck.addCard(tremendousFire);
		deck.addCard(monsterReborn);

		deck.shuffle();
	}
}
