package com.william;

import java.util.ArrayList;
import java.util.List;
import java.util.Random;
import java.util.concurrent.ThreadLocalRandom;

import com.william.card.Card;
import com.william.card.CardType;
import com.william.deck.Deck;
import com.william.move.Move;
import com.william.move.ProcessMove;
import com.william.table.Table;
import com.william.util.RandomString;
import com.william.util.Util;

public class Main {

	public static void main(String[] args) {
		// Creating base values for cards
		int mana = ThreadLocalRandom.current().nextInt(1, 10);
		int attack = ThreadLocalRandom.current().nextInt(1, 10);
		int health = ThreadLocalRandom.current().nextInt(1, 10);

		Deck firstDeck = new Deck();
		Deck secondDeck = new Deck();

		// Random fill both decks
		Random random = new Random();
		firstDeck.randomFill(random, 30, mana, attack, health);
		secondDeck.randomFill(random, 30, mana, attack, health);

		Table table = new Table();
		ProcessMove processMove = new ProcessMove();

		List<Card> firstMinions = new ArrayList<>();
		List<Card> secondMinions = new ArrayList<>();

		int minionMaxCount = ThreadLocalRandom.current().nextInt(2, 5);

		// Creating minions for both players
		RandomString randomString = new RandomString(random, ThreadLocalRandom.current().nextInt(20, 30));
		for (int i = 0; i < minionMaxCount; i++) {
			int value = ThreadLocalRandom.current().nextInt(1, 10);
			firstMinions.add(CardType.MINION.create(randomString.nextString(), value, value, value));
		}

		for (int i = 0; i < minionMaxCount; i++) {
			int value = ThreadLocalRandom.current().nextInt(1, 10);
			secondMinions.add(CardType.MINION.create(randomString.nextString(), value, value, value));
		}

		table.setFirstPlayerMinions(firstMinions);
		table.setSecondPlayerMinions(secondMinions);

		// Fill each player hand, with second player receiving four cards
		table.getSecondPlayerHand().add(secondDeck.pullCard());
		for (int i = 0; i < Util.INITIAL_HAND_SIZE; i++) {
			table.getFirstPlayerHand().add(firstDeck.pullCard());
			table.getSecondPlayerHand().add(secondDeck.pullCard());
		}

		Card firstPlayerHandCard = table.getFirstPlayerHand().get(0);
		Card secondPlayerHandCard = table.getFirstPlayerHand().get(0);

		// Attacking other hero with chosen hand cards
		Move firstPlayerHeroAttack = new Move(firstPlayerHandCard, null, 'P');
		Move secondPlayerHeroAttack = new Move(secondPlayerHandCard, null, 'S');

		processMove.process(firstPlayerHeroAttack, table);
		processMove.process(secondPlayerHeroAttack, table);

		// Attacking other player minions
		Card firstPlayerMinion = firstMinions.get(0);
		Card secondPlayerMinion = secondMinions.get(0);

		Move firstPlayerMinionAttack = new Move(firstPlayerMinion, secondMinions.get(1), 'P');
		Move secondPlayerMinionAttack = new Move(secondPlayerMinion, firstMinions.get(1), 'S');

		processMove.process(firstPlayerMinionAttack, table);
		processMove.process(secondPlayerMinionAttack, table);
	}

}