package com.william.card.magic;

import com.william.card.Card;
import com.william.card.Minion;
import com.william.util.Util;

import java.util.UUID;

public class Damage extends Magic {

	private int damage;

	public Damage(UUID id, String name, int manaCost, int damage) {
		super(id, name, manaCost);
		this.damage = damage;
	}

	public Damage(String name, int manaCost, int damage) {
		super(name, manaCost);
		this.damage = damage;
	}

	public int getDamage() {
		return damage;
	}

	public void setDamage(int damage) {
		this.damage = damage;
	}

	@Override
	public String toString() {
		String out = super.toString();
		out += "Dano = " + this.damage + "\n";
		return out;
	}

	@Override
	public void use(Card target) {
		Util.damage((Minion) target, this.damage);
	}
}
