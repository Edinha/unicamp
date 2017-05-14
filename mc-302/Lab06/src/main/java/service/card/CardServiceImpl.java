package service.card;

import java.util.concurrent.ThreadLocalRandom;

import base.card.Card;
import base.card.CardType;
import util.RandomString;

public class CardServiceImpl implements CardService {
	public CardServiceImpl() {
	}

	@Override
	public Card randomCard(int maxMana, int maxAttack, int maxHealth, CardType cardType) {
		int mana = randomInt(1, maxMana);
		int attack = randomInt(1, maxAttack);
		int health = randomInt(1, maxHealth);
		String name = new RandomString(50).nextString();

		if (cardType == null) {
			cardType = CardType.of(ThreadLocalRandom.current().nextInt(CardType.values().length - 1));
		}

		return cardType.create(name, mana, health, attack);
	}

	@Override
	public int randomInt(int min, int max) {
		return ThreadLocalRandom.current().nextInt(min, max + 1);
	}
}
