package service.card;

import base.card.Card;
import base.card.CardType;

public interface CardService {
	Card randomCard(CardType type);
	int randomInt(int min, int max);
}
