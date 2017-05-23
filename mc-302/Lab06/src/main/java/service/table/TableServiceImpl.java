package service.table;

import base.Deck;
import base.Table;
import base.card.CardType;
import base.exception.NullTableException;
import service.card.CardService;
import util.Util;

public class TableServiceImpl implements TableService {

	@Override
	public void addMinions(Table table, CardService cardService) throws NullTableException {
		if (table == null) {
			throw new NullTableException("Table is null, cannot add minions");
		}

		for (int i = 0; i < Util.MAX_MINIONS; i++) {
			table.getFirstPlayerMinions().add(cardService.randomCard(CardType.MINION));
			table.getSecondPlayerMinions().add(cardService.randomCard(CardType.MINION));
		}
	}

	@Override
	public void addInitialHand(Table table, Deck first, Deck second) {
		for (int i = 0; i < Util.INITIAL_HAND_SIZE; i++) {
			table.getFirstPlayerHand().add(first.pullCard());
			table.getSecondPlayerHand().add(second.pullCard());
		}

		table.getSecondPlayerHand().add(second.pullCard());
	}
}
