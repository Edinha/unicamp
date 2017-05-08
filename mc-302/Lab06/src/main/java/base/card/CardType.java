package base.card;

import base.card.magic.Buff;
import base.card.magic.Damage;
import base.card.magic.DamageArea;

import java.util.HashMap;
import java.util.Map;

public enum CardType {
	BUFF {
		@Override
		public Card create(String name, int mana, int health, int attack) {
			return new Buff(name, mana, attack, attack);
		}
	},
	MINION {
		@Override
		public Card create(String name, int mana, int health, int attack) {
			return new Minion(name, mana, attack, health, health);
		}
	},
	DAMAGE {
		@Override
		public Card create(String name, int mana, int health, int attack) {
			return new Damage(name, mana, attack);
		}
	},
	AREA_DAMAGE {
		@Override
		public Card create(String name, int mana, int health, int attack) {
			return new DamageArea(name, mana, attack);
		}
	};

	public abstract Card create(String name, int mana, int health, int attack);

	static final Map<Integer, CardType> TYPES = new HashMap<>();

	static {
		TYPES.put(0, BUFF);
		TYPES.put(1, MINION);
		TYPES.put(2, DAMAGE);
		TYPES.put(3, AREA_DAMAGE);
	}

	public static CardType of(int number) {
		return TYPES.get(number);
	}
}
