package service.deck;

import base.card.Card;
import service.card.CardService;

import java.util.List;

public interface DeckService {
	List<Card> randomFill(CardService cardService);
}
