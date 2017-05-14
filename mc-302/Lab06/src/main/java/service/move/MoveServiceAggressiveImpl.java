package service.move;

import java.util.Collections;
import java.util.Comparator;
import java.util.List;

import base.Table;
import base.card.Card;
import base.move.Move;

public class MoveServiceAggressiveImpl implements MoveService {

	public MoveServiceAggressiveImpl() {
	}

	@Override
	public List<Move> createMove(Table table, char player) {
		Card attacker = table.getFirstPlayerMinions().iterator().next();
		return Collections.singletonList(new Move(attacker, null, player));
	}

	private class DamageComparator implements Comparator<Card> {

		public DamageComparator() {
		}

		@Override
		public int compare(Card first, Card second) {
			return 0;
		}
	}

	private class MinionComparator implements Comparator<Card> {

		public MinionComparator() {
		}

		@Override
		public int compare(Card first, Card second) {
			return 0;
		}
	}
}
