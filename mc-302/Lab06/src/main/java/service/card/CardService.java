package service.card;

import base.card.Card;
import base.card.CardType;

import java.util.Random;

public interface CardService {
	Card randomCard(int maxMana, int maxAttack, int maxHealth, CardType type);
	int randomInt(int min, int max);
}
