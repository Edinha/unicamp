package base.move;

import base.card.Card;

public class Move {
	private Card card;
	private Card target;
	private char author;

	public Move(Card card, Card target, char author) {
		this.card = card;
		this.target = target;
		this.author = author;
	}

	public Card getCard() {
		return card;
	}

	public void setCard(Card card) {
		this.card = card;
	}

	public Card getTarget() {
		return target;
	}

	public void setTarget(Card target) {
		this.target = target;
	}

	public char getAuthor() {
		return author;
	}

	public void setAuthor(char author) {
		this.author = author;
	}

	@Override
	public String toString() {
		String out = "Author: " + author;
		out += "\nCard played: " + cardString(card) ;
		out += "\nCard targeted: " + cardString(target);
		return out;
	}

	private String cardString(Card card) {
		if (card == null) {
			return "No card";
		}

		return card.toString();
	}
}
