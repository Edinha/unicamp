package com.william.card.magic;

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

	public void use(List<Minion> targets) {
		targets.forEach(this::use);
	}
}
