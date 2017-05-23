package util;

import base.card.Minion;

public class Util {
	public static final int MAX_CARDS = 30;
	public static final int HEROIC_POWER = 5;
	public static final int INITIAL_HAND_SIZE = 3;

	public static final int MAX_MANA = 7;
	public static final int MAX_ATTACK = 8;
	public static final int MAX_HEALTH = 9;
	public static final int MAX_MINIONS = 10;

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

	private static boolean hasAppliedBuff(int oldStat, int newStat) {
		return (oldStat < newStat);
	}

	private static void buffedName(Minion minion) {
		minion.setName(minion.getName() + Minion.getBuffedNameSuffix());
	}
}