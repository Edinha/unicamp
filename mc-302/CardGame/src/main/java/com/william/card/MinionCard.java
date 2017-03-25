package com.william.card;

public class MinionCard {
	private static final String BUFFED_NAME_SUFFIX = " Buffed";

	private int id;
	private int attack;
	private int manaCost;
	private int totalHealth;
	private int currentHealth;

	private String name;

	public MinionCard(int id, String name, int manaCost) {
		this.id = id;
		this.name = name;
		this.manaCost = manaCost;
	}

	public MinionCard(MinionCard other) {
		this.id = other.getId();
		this.name = other.getName();
		this.attack = other.getAttack();
		this.manaCost = other.getManaCost();
		this.currentHealth = other.getCurrentHealth();
		this.totalHealth = other.getTotalHealth();
	}

	public MinionCard(int id, String name, int attack, int currentHealth, int totalHealth, int manaCost) {
		this.id = id;
		this.name = name;
		this.attack = attack;
		this.currentHealth = currentHealth;
		this.totalHealth = totalHealth;
		this.manaCost = manaCost;
	}

	public int getId() {
		return id;
	}

	public void setId(int id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
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

	public int getManaCost() {
		return manaCost;
	}

	public void setManaCost(int manaCost) {
		this.manaCost = manaCost;
	}

	public static String getBuffedNameSuffix() {
		return BUFFED_NAME_SUFFIX;
	}

	@Override
	public String toString() {
		String out = this.name + " (ID: " + this.id + ")\n";
		out += "Ataque = " + this.attack + "\n";
		out += "Vida Atual = " + this.currentHealth + "\n";
		out += "Vida Maxima = " + this.totalHealth + "\n";
		out += "Custo de Mana = " + this.manaCost + "\n";
		return out;
	}
}