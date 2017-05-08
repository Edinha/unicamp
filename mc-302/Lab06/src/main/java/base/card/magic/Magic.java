package base.card.magic;

import base.card.Card;

import java.util.UUID;

public abstract class Magic extends Card {

	public Magic(UUID id, String name, int manaCost) {
		super(id, name, manaCost);
	}

	public Magic(String name, int manaCost) {
		super(name, manaCost);
	}

}
