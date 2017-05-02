package com.william.card;

import com.william.util.Util;

import java.util.UUID;

public class Minion extends Card {
	private static final String BUFFED_NAME_SUFFIX = " Buffed";

	private int attack;
	private int totalHealth;
	private int currentHealth;

	public Minion(UUID id, String name, int manaCost, int attack, int totalHealth, int currentHealth) {
		super(id, name, manaCost);
		this.attack = attack;
		this.totalHealth = totalHealth;
		this.currentHealth = currentHealth;
	}

	public Minion(String name, int manaCost, int attack, int totalHealth, int currentHealth) {
		super(name, manaCost);
		this.attack = attack;
		this.totalHealth = totalHealth;
		this.currentHealth = currentHealth;
	}

	public int getAttack() {
		return attack;
	}

	public void setAttack(int atack) {
		this.attack = atack;
	}

	public int getCurrentHealth() {
		return currentHealth;
	}

	public void setCurrentHealth(int currentHealth) {
		this.currentHealth = currentHealth;
	}

	public int getTotalHealth() {
		return totalHealth;
	}

	public void setTotalHealth(int totalHealth) {
		this.totalHealth = totalHealth;
	}

	public static String getBuffedNameSuffix() {
		return BUFFED_NAME_SUFFIX;
	}

	@Override
	public String toString() {
		String out = super.toString();
		out += "Ataque = " + this.attack + "\n";
		out += "Vida Atual = " + this.currentHealth + "\n";
		out += "Vida Maxima = " + this.totalHealth + "\n";
		return out;
	}

	@Override
	public void use(Card target) {
		Minion minion = (Minion) target;
		Util.damage(minion, this.attack);
		Util.damage(this, minion.getAttack());
	}
}