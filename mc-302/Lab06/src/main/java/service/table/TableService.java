package service.table;

import base.Deck;
import base.Table;
import base.exception.NullTableException;
import service.card.CardService;

public interface TableService {
	void addMinions(Table table, CardService cardService) throws NullTableException;
	void addInitialHand(Table table, Deck first, Deck second);
}
