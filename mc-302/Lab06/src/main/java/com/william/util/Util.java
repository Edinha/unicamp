package com.william.util;

import com.william.card.Card;
import com.william.card.CardType;
import com.william.card.Minion;

import java.util.Random;

public class Util {
	public static void buff(Minion minion, int attackAndHealthBuff) {
		buff(minion, attackAndHealthBuff, attackAndHealthBuff);
	}

	public static void buff(Minion minion, int attackBuff, int healthBuff) {
		int oldAttack = minion.getAttack();
		int oldHealth = minion.getCurrentHealth();

		if (attackBuff > 0) {
			minion.setAttack(minion.getAttack() + attackBuff);
		}

		if (healthBuff > 0) {
			minion.setTotalHealth(minion.getTotalHealth() + healthBuff);
			minion.setCurrentHealth(minion.getCurrentHealth() + healthBuff);
		}

		if (hasAppliedBuff(oldAttack, minion.getAttack()) || hasAppliedBuff(oldHealth, minion.getCurrentHealth())) {
			buffedName(minion);
		}
	}

	public static void damage(Minion minion, int damage) {
		int healthAfterDamage = minion.getCurrentHealth() - damage;
		minion.setCurrentHealth(healthAfterDamage);
	}

	public static Card generateRandomCard(Random random, int maxMana, int maxAttack, int maxHealth, CardType cardType) {
		int mana = randInt(random, 1, maxMana);
		int attack = randInt(random, 1, maxAttack);
		int health = randInt(random, 1, maxHealth);
		String name = new RandomString(random, 50).nextString();

		if (cardType == null) {
			cardType = CardType.of(random.nextInt(CardType.values().length - 1));
		}

		return cardType.create(name, mana, health, attack);
	}

	private static int randInt(Random random, int min, int max) {
		return random.nextInt((max - min) + 1) + min;
	}

	private static boolean hasAppliedBuff(int oldStat, int newStat) {
		return (oldStat < newStat);
	}

	private static void buffedName(Minion minion) {
		minion.setName(minion.getName() + Minion.getBuffedNameSuffix());
	}
}