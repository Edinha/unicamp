package com.william.card.magic;

import com.william.card.Card;
import com.william.card.Minion;

import java.util.List;
import java.util.UUID;

public class DamageArea extends Damage {

	public DamageArea(UUID id, String name, int manaCost, int damage) {
		super(id, name, manaCost, damage);
	}

	public DamageArea(String name, int manaCost, int damage) {
		super(name, manaCost, damage);
	}

	public void use(List<Card> targets) {
		targets.forEach(this::use);
	}

	@Override
	public String toString() {
		String out = super.toString();
		out += "Dano aplicado em area\n";
		return out;
	}
}
