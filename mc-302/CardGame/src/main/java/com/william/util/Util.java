package com.william.util;

import com.william.card.MinionCard;

public class Util {
	public static void buff(MinionCard minion, int attackAndHealthBuff) {
		buff(minion, attackAndHealthBuff, attackAndHealthBuff);
	}

	public static void buff(MinionCard minion, int attackBuff, int healthBuff) {
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

	public static void damage(MinionCard minion, int damage) {
		int healthAfterDamage = minion.getCurrentHealth() - damage;
		minion.setCurrentHealth(healthAfterDamage);
	}

	private static boolean hasAppliedBuff(int oldStat, int newStat) {
		return (oldStat < newStat);
	}

	private static void buffedName(MinionCard minion) {
		minion.setName(minion.getName() + MinionCard.getBuffedNameSuffix());
	}
}