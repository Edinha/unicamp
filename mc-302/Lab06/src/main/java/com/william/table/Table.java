package com.william.table;

import java.util.ArrayList;
import java.util.List;
import java.util.concurrent.ThreadLocalRandom;

import com.william.card.Card;
import com.william.util.Util;

public class Table {
	private List<Card> firstPlayerHand;
	private List<Card> secondPlayerHand;

	private List<Card> firstPlayerMinions;
	private List<Card> secondPlayerMinions;

	private int firstPlayerHeroicPower;
	private int secondPlayerHeroicPower;

	private int firstPlayerMana;
	private int secondPlayerMana;

	public Table() {
		firstPlayerMana = 1;
		firstPlayerHand = new ArrayList<>();
		firstPlayerMinions = new ArrayList<>();
		firstPlayerHeroicPower = Util.HEROIC_POWER;

		secondPlayerMana = 1;
		secondPlayerHand = new ArrayList<>();
		secondPlayerMinions = new ArrayList<>();
		secondPlayerHeroicPower = Util.HEROIC_POWER;

	}

	public Table(List<Card> firstPlayerHand, List<Card> secondPlayerHand, List<Card> firstPlayerMinions, List<Card> secondPlayerMinions,
			int firstPlayerHeroicPower, int secondPlayerHeroicPower, int firstPlayerMana, int secondPlayerMana) {
		this.firstPlayerHand = firstPlayerHand;
		this.secondPlayerHand = secondPlayerHand;
		this.firstPlayerMinions = firstPlayerMinions;
		this.secondPlayerMinions = secondPlayerMinions;
		this.firstPlayerHeroicPower = firstPlayerHeroicPower;
		this.secondPlayerHeroicPower = secondPlayerHeroicPower;
		this.firstPlayerMana = firstPlayerMana;
		this.secondPlayerMana = secondPlayerMana;
	}

	public List<Card> getFirstPlayerHand() {
		return firstPlayerHand;
	}

	public void setFirstPlayerHand(List<Card> firstPlayerHand) {
		this.firstPlayerHand = firstPlayerHand;
	}

	public List<Card> getSecondPlayerHand() {
		return secondPlayerHand;
	}

	public void setSecondPlayerHand(List<Card> secondPlayerHand) {
		this.secondPlayerHand = secondPlayerHand;
	}

	public List<Card> getFirstPlayerMinions() {
		return firstPlayerMinions;
	}

	public void setFirstPlayerMinions(List<Card> firstPlayerMinions) {
		this.firstPlayerMinions = firstPlayerMinions;
	}

	public List<Card> getSecondPlayerMinions() {
		return secondPlayerMinions;
	}

	public void setSecondPlayerMinions(List<Card> secondPlayerMinions) {
		this.secondPlayerMinions = secondPlayerMinions;
	}

	public int getFirstPlayerHeroicPower() {
		return firstPlayerHeroicPower;
	}

	public void setFirstPlayerHeroicPower(int firstPlayerHeroicPower) {
		this.firstPlayerHeroicPower = firstPlayerHeroicPower;
	}

	public int getSecondPlayerHeroicPower() {
		return secondPlayerHeroicPower;
	}

	public void setSecondPlayerHeroicPower(int secondPlayerHeroicPower) {
		this.secondPlayerHeroicPower = secondPlayerHeroicPower;
	}

	public int getFirstPlayerMana() {
		return firstPlayerMana;
	}

	public void setFirstPlayerMana(int firstPlayerMana) {
		this.firstPlayerMana = firstPlayerMana;
	}

	public int getSecondPlayerMana() {
		return secondPlayerMana;
	}

	public void setSecondPlayerMana(int secondPlayerMana) {
		this.secondPlayerMana = secondPlayerMana;
	}

	public void decreaseHeroicPower(int quantity, char player) {
		if (player == 'P') {
			this.firstPlayerHeroicPower = Math.max(0, this.firstPlayerHeroicPower - quantity);
			return;
		}

		this.secondPlayerHeroicPower = Math.max(0, this.secondPlayerHeroicPower - quantity);
	}

	public void decreaseMana(int quantity, char player) {
		if (player == 'P') {
			this.firstPlayerMana = Math.max(0, this.firstPlayerMana - quantity);
			return;
		}

		this.secondPlayerMana = Math.max(0, this.secondPlayerMana - quantity);
	}

	public Card pull(char player) {
		if (player == 'P') {
			int position = ThreadLocalRandom.current().nextInt(0, this.firstPlayerHand.size() - 1);
			Card card = this.firstPlayerHand.get(position);
			this.firstPlayerHand.remove(card);
			return card;
		}

		int position = ThreadLocalRandom.current().nextInt(0, this.secondPlayerHand.size() - 1);
		Card card = this.secondPlayerHand.get(position);
		this.secondPlayerHand.remove(card);
		return card;
	}
}
