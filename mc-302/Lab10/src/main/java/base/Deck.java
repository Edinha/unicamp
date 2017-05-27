package base;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Deck {
	private List<Card> deck;

	public Deck() {
		this.deck = new ArrayList<>();
	}

	private List<Card> getDeck() {
		return deck;
	}

	public Card pullCard() {
		if (this.deck.isEmpty()) {
			return null;
		}

		Card card = this.deck.get(this.deck.size() - 1);
		this.deck.remove(card);
		return card;
	}

	public void fill(List<Card> cards) {
		this.deck.clear();
		this.deck.addAll(cards);
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
