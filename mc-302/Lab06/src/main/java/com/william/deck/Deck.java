package com.william.deck;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import com.william.card.Card;

public class Deck {
	public static int MAX_CARDS = 30;

	private List<Card> deck;

	public Deck() {
		this.deck = new ArrayList<>();
	}

	public List<Card> getDeck() {
		return deck;
	}

	public void addCard(Card card) {
		if (this.deck.size() == MAX_CARDS) {
			return;
		}

		this.deck.add(card);
	}

	public Card pullCard() {
		if (this.deck.isEmpty()) {
			return null;
		}

		Card card = this.deck.get(this.deck.size() - 1);
		this.deck.remove(card);
		return card;
	}

	public void shuffle()  {
		Collections.shuffle(this.deck);
		printReverseDeck();
	}

	private void printReverseDeck() {
		for (int i = this.deck.size() - 1; i >= 0; i--) {
			System.out.println(this.deck.get(i));
			System.out.println();
		}
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}

		if (!(obj instanceof Deck)) {
			return false;
		}

		Deck d = (Deck) obj;
		return this.deck.equals(d.getDeck());
	}

	@Override
	public int hashCode() {
		return deck.hashCode();
	}
}
