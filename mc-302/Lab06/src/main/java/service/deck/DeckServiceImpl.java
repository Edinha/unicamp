package service.deck;

import java.util.ArrayList;
import java.util.List;

import base.card.Card;
import base.exception.EmptyDeckException;
import service.card.CardService;
import util.Util;

public class DeckServiceImpl implements DeckService {

	@Override
	public List<Card> randomFill(CardService cardService) {
		List<Card> cards = new ArrayList<>();

		for (int i = 0; i < Util.MAX_CARDS; i++) {
			cards.add(cardService.randomCard(null));
		}

		if (cards.isEmpty()) {
			throw new EmptyDeckException("Empty deck cannot be returned");
		}

		return cards;
	}
}
