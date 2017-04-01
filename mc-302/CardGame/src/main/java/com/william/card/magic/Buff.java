package com.william.card.magic;

import com.william.card.Card;
import com.william.card.Minion;
import com.william.util.Util;

import java.util.UUID;

public class Buff extends Magic {

	private int attackBuff;
	private int healthBuff;

	public Buff(UUID id, String name, int manaCost, int damage, boolean multiTarget, int attackBuff, int healthBuff) {
		super(id, name, manaCost);
		this.attackBuff = attackBuff;
		this.healthBuff = healthBuff;
	}

	public Buff(String name, int manaCost, int damage, boolean multiTarget, int attackBuff, int healthBuff) {
		super(name, manaCost);
		this.attackBuff = attackBuff;
		this.healthBuff = healthBuff;
	}

	public int getAttackBuff() {
		return attackBuff;
	}

	public void setAttackBuff(int attackBuff) {
		this.attackBuff = attackBuff;
	}

	public int getHealthBuff() {
		return healthBuff;
	}

	public void setHealthBuff(int healthBuff) {
		this.healthBuff = healthBuff;
	}

	@Override
	public String toString() {
		String out = super.toString();
		out += "Buff Vida = " + this.healthBuff + "\n";
		out += "Buff Ataque  = " + this.attackBuff + "\n";
		return out;
	}

	@Override
	public void use(Card target) {
		Minion minion = (Minion) target;
		Util.buff(minion, this.attackBuff, this.healthBuff);
	}
}
