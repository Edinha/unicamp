package com.william;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Comparator;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;
import java.util.concurrent.ThreadLocalRandom;
import java.util.concurrent.TimeUnit;
import java.util.stream.Collectors;

import com.william.card.Card;
import com.william.card.Minion;
import com.william.card.magic.Buff;
import com.william.card.magic.Damage;
import com.william.card.magic.DamageArea;

public class Main {

	public static void main(String[] args) {
		int min = 1;
		int max = 4;

		Set<Card> hashSet = new HashSet<>();
		Set<Card> treeSet = new TreeSet<>(Comparator.comparing(Card::getId));
		List<Card> arrayList = new ArrayList<>();
		List<Card> linkedList = new LinkedList<>();

		for (int i = 0; i < 10000; i++) {
			int random = ThreadLocalRandom.current().nextInt(min, max + 1);

			Card card = CardInstanceType.from(random).getCard();
			treeSet.add(card);
			hashSet.add(card);
			arrayList.add(card);
			linkedList.add(card);
		}

		System.out.println("Start counting time (get ArrayList)...");
		measureGetTime(arrayList);

		System.out.println("Start counting time (get LinkedList)...");
		measureGetTime(linkedList);

		System.out.println("Start counting time (ArrayList contains LinkedList)...");
		measureContainsTime(arrayList, linkedList);

		System.out.println("Start counting time (LinkedList contains ArrayList)...");
		measureContainsTime(linkedList, arrayList);

		// As colecoes de lista aceitam cartas repetidas

		System.out.println("Start counting time (HashSet contains ArrayList)...");
		measureContainsTime(hashSet, arrayList);

		System.out.println("Start counting time (TreeSet contains ArrayList)...");
		measureContainsTime(treeSet, arrayList);

		// As colecoes de set nao aceitam cartas repetidas

		Set<Minion> minions = arrayList.stream().filter(f -> f instanceof Minion).map(m -> (Minion) m).collect(Collectors.toSet());

		Minion strongest = minions.stream().sorted(Comparator.comparing(Minion::getAttack, Comparator.reverseOrder())).findFirst().orElse(null);

		int sumMinionAttacks = minions.stream().mapToInt(Minion::getAttack).sum();

		Set<Minion> sortedByCurrentHealth = minions.stream().sorted(Comparator.comparing(Minion::getCurrentHealth)).collect(Collectors.toSet());

		System.out.println("Strongest minion : " + strongest);
		System.out.println("Sum of attacks : " + sumMinionAttacks);
		System.out.println("Sorted by current health (first) : " + sortedByCurrentHealth.iterator().next());
	}

	private static void measureContainsTime(Collection<Card> base, Collection<Card> contained) {
		long start = System.nanoTime();
		contained.forEach(base::contains);
		System.out.println("Finished (time: " + TimeUnit.NANOSECONDS.toMillis(System.nanoTime() - start) + " ms)");
	}

	private static void measureGetTime(List<Card> cards) {
		long start = System.nanoTime();
		for (int i = 0; i < cards.size(); i++) {
			cards.get(i);
		}

		System.out.println("Finished (time: " + TimeUnit.NANOSECONDS.toMillis(System.nanoTime() - start) + " ms)");
	}
}


enum CardInstanceType {
	MINION(1) {
		@Override
		public Card getCard() {
			return new Minion("Minion", 0, 0, 0, 0);
		}
	},
	DAMAGE(2) {
		@Override
		public Card getCard() {
			return new Damage("Damage", 0, 0);
		}
	},
	AREA(3) {
		@Override
		public Card getCard() {
			return new DamageArea("Damage area", 0, 0);
		}
	},
	BUFF(4) {
		@Override
		public Card getCard() {
			return new Buff("Buff", 0, 0, 0);
		}
	};

	private Integer type;

	CardInstanceType(Integer type) {
		this.type = type;
	}

	public Integer getType() {
		return type;
	}

	public static CardInstanceType from(Integer type) {
		for (CardInstanceType c : CardInstanceType.values()) {
			if (c.getType().equals(type)) {
				return c;
			}
		}

		return CardInstanceType.MINION;
	}

	public abstract Card getCard();
}
