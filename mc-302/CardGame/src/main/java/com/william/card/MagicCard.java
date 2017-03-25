package com.william.card;

public class MagicCard {

	private int id;
	private String name;
	private int damage;
	private boolean multiTarget;
	private int manaCost;

	public MagicCard(int id, String name, int damage, boolean multiTarget, int manaCost) {
		super();
		this.id = id;
		this.name = name;
		this.damage = damage;
		this.multiTarget = multiTarget;
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

	public int getDamage() {
		return damage;
	}

	public void setDamage(int damage) {
		this.damage = damage;
	}

	public boolean isMultiTarget() {
		return multiTarget;
	}

	public void setMultiTarget(boolean multiTarget) {
		this.multiTarget = multiTarget;
	}

	public int getManaCost() {
		return manaCost;
	}

	public void setManaCost(int manaCost) {
		this.manaCost = manaCost;
	}

	@Override
	public String toString() {
		String out = this.name + " (ID: " + this.id + ")\n";
		out += "Dano = " + this.damage + "\n";
		out += "Area = " + this.multiTarget + "\n";
		out += "Custo de Mana = " + this.manaCost + "\n";
		return out;
	}
}
