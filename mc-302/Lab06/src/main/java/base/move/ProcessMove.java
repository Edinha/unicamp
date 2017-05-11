package base.move;

import java.util.List;
import java.util.stream.Collectors;

import base.Table;
import base.card.Card;
import base.card.Minion;
import base.card.MinionAbility;
import base.card.magic.Buff;
import base.card.magic.Damage;
import base.card.magic.DamageArea;

public class ProcessMove {

	public void process(Move move, Table table) {
		List<Card> myMinions;
		List<Card> enemyMinions;

		int enemyHeroicPower;

		Card card = move.getCard();

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

		// Give preference to Taunt minion instead of target
		Card target = enemyMinions.stream().map(x -> (Minion) x).filter(x -> MinionAbility.TAUNT.equals(x.getAbility())).findAny().orElse(
			(Minion) move.getTarget());

		System.out.println("[START] Player move.");
		System.out.println("Move: " + move.toString());

		enemyDetails(enemyMinions, enemyHeroicPower);

		if (target == null) {
			if (card instanceof Buff) {
				return;
			}

			if (card instanceof Damage) {
				enemyHeroicPower -= ((Damage) card).getDamage();
			} else if (card instanceof Minion) {
				Minion minion = (Minion) card;
				if (MinionAbility.EXHAUSTION.equals(minion.getAbility())) {
					minion.setAbility(MinionAbility.CHARGE);
					myMinions.add(minion);
				} else {
					enemyHeroicPower -= minion.getAttack();
				}
			}

		} else {
			if (card instanceof Buff) {
				card.use(target);
			} else if (card instanceof DamageArea) {
				DamageArea damageArea = (DamageArea) card;
				damageArea.use(enemyMinions);
				enemyHeroicPower -= damageArea.getDamage();
			} else if (card instanceof Damage) {
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
		}

		if (move.getAuthor() == 'P') {
			table.setSecondPlayerHeroicPower(enemyHeroicPower);
		} else {
			table.setFirstPlayerHeroicPower(enemyHeroicPower);
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
