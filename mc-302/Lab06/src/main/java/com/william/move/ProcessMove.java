package com.william.move;

import java.util.List;
import java.util.stream.Collectors;

import com.william.card.Card;
import com.william.card.Minion;
import com.william.card.MinionAbility;
import com.william.card.magic.Buff;
import com.william.card.magic.Damage;
import com.william.card.magic.DamageArea;
import com.william.table.Table;

public class ProcessMove {

	public void process(Move move, Table table) {
		List<Card> myMinions;
		List<Card> enemyMinions;

		int enemyHeroicPower;

		Card card = move.getCard();
		Card target = move.getTarget();

		if (move.getAuthor() == 'P') {
			myMinions = table.getFirstPlayerMinions();
			enemyMinions = table.getSecondPlayerMinions();
			table.setFirstPlayerMana(table.getFirstPlayerMana() - card.getManaCost());
			enemyHeroicPower = table.getSecondPlayerHeroicPower();
		} else {
			myMinions = table.getSecondPlayerMinions();
			enemyMinions = table.getFirstPlayerMinions();
			table.setSecondPlayerMana(table.getSecondPlayerMana() - card.getManaCost());
			enemyHeroicPower = table.getFirstPlayerHeroicPower();
		}

		System.out.println("[START] Player move.");
		System.out.println("Move: " + move.toString());

		enemyDetails(enemyMinions, enemyHeroicPower);

		if (target == null) {
			// TODO attack hero
			return;
		}

		if (card instanceof Buff && target instanceof Minion) {
			card.use(target);
		} else if (card instanceof DamageArea) {
			DamageArea damageArea = (DamageArea) card;
			damageArea.use(enemyMinions);
		} else if (card instanceof Damage && target instanceof Minion) {
			card.use(target);
		} else if (card instanceof Minion) {
			Minion minion = (Minion) card;
			if (MinionAbility.EXHAUSTION.equals(minion.getAbility())) {
				minion.setAbility(MinionAbility.CHARGE);
				myMinions.add(minion);
			} else {
				minion.use(target);
			}

			if (minion.isDestroyed()) {
				myMinions.remove(minion);
			}
		}

		List<Card> deadMinions = enemyMinions.stream().filter(e -> ((Minion) e).isDestroyed()).collect(Collectors.toList());
		enemyMinions.removeAll(deadMinions);

		System.out.println("[END] Player move.");
		enemyDetails(enemyMinions, enemyHeroicPower);
	}

	private void enemyDetails(List<Card> enemyMinions, int enemyHeroicPower) {
		System.out.println("Enemy minions count: " + enemyMinions.size());
		System.out.println("Enemy minions: ");
		enemyMinions.forEach(e -> System.out.println(e.toString()));

		System.out.println("Enemy heroic power: " + enemyHeroicPower);
	}
}
