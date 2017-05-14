package base;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

import base.card.Card;
import service.card.CardService;

public class Deck {
	private static int MAX_CARDS = 30;

	private List<Card> deck;

	public Deck() {
		this.deck = new ArrayList<>();
	}

	private List<Card> getDeck() {
		return deck;
	}

	private void addCard(Card card) {
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

	public void randomFill(CardService cardService, int maxMana, int maxAttack, int maxHealth) {
		this.deck.clear();

		for (int i = 0; i < MAX_CARDS; i++) {
			this.addCard(cardService.randomCard(maxMana, maxAttack, maxHealth, null));
		}

		shuffle();
	}

	private void shuffle() {
		Collections.shuffle(this.deck);
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
