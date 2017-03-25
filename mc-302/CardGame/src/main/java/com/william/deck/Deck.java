package com.william.deck;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import com.william.card.MinionCard;

public class Deck {
	public static int MAX_CARDS = 30;

	private List<MinionCard> deck;

	public Deck() {
		this.deck = new ArrayList<MinionCard>();
	}

	public List<MinionCard> getDeck() {
		return deck;
	}

	public void addCard(MinionCard card) {
		if (this.deck.size() == MAX_CARDS) {
			return;
		}

		this.deck.add(card);
	}

	public MinionCard pullCard() {
		if (this.deck.isEmpty()) {
			return null;
		}

		MinionCard card = this.deck.get(this.deck.size() - 1);
		this.deck.remove(card);
		return card;
	}

	public void shuffle()  {
		Collections.shuffle(this.deck);
		printReverseDeck();
	}

	private void printReverseDeck() {
		for (int i = this.deck.size() - 1; i >= 0; i--) {
			System.out.print(this.deck.get(i));
		}
	}
}
