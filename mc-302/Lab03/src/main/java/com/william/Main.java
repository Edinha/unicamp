package com.william;

import com.william.card.MinionCard;
import com.william.deck.Deck;
import com.william.deck.DeckArray;
import com.william.util.Util;

import java.util.List;

public class Main {

	public static void main(String[] args) {
		Deck deck = new Deck();

		MinionCard darkMagician = new MinionCard(1, "Mago negro", 7, 10, 10, 10);
		MinionCard demonSkullKing = new MinionCard(2, "Rei caveira", 3, 3, 2, 30);
		MinionCard blueEyesWhiteDragon = new MinionCard(3, "Dragão branco de olhos azuis", 9, 5, 6, 20);

		deck.addCard(darkMagician);
		deck.addCard(demonSkullKing);
		deck.addCard(blueEyesWhiteDragon);

		deck.shuffle();

		List<MinionCard> cardList = deck.getDeck();
		System.out.println("\n\nOrdem embaralhada: (" +
			cardList.get(0).getName() +
			", " +
			cardList.get(1).getName() +
			", " +
			cardList.get(2).getName() +
			")");

		DeckArray deckArray = new DeckArray();
		deckArray.addCard(darkMagician);
		deckArray.addCard(demonSkullKing);
		deckArray.addCard(blueEyesWhiteDragon);

		deckArray.shuffle();

		MinionCard[] cardArray = deckArray.getDeck();
		System.out.println("\n\nOrdem embaralhada: (" +
				cardArray[0].getName() +
				", " +
				cardArray[1].getName() +
				", " +
				cardArray[2].getName() +
				")");

		MinionCard pulledCard = deck.pullCard();
		System.out.println("\n\nCarta comprada: " + pulledCard);

		Util.buff(darkMagician, 10);
		Util.buff(demonSkullKing, 2, 2);

		System.out.println("\n\nBuff 1: " + darkMagician);
		System.out.println("\n\nBuff 2: " + demonSkullKing);
	}
}
