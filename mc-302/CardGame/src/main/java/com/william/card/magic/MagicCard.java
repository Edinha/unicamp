package com.william.card.magic;

import com.william.card.Card;

import java.util.UUID;

public abstract class MagicCard extends Card {

	public MagicCard(UUID id, String name, int manaCost) {
		super(id, name, manaCost);
	}

	public MagicCard(String name, int manaCost) {
		super(name, manaCost);
	}

}
