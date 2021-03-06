package base.card;

import java.util.UUID;

public abstract class Card {
	private UUID id;
	private String name;
	private int manaCost;

	public Card(UUID id, String name, int manaCost) {
		this.id = id;
		this.name = name;
		this.manaCost = manaCost;
	}

	public Card(String name, int manaCost) {
		this(UUID.randomUUID(), name, manaCost);
	}

	public UUID getId() {
		return id;
	}

	public void setId(UUID id) {
		this.id = id;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public int getManaCost() {
		return manaCost;
	}

	public void setManaCost(int manaCost) {
		this.manaCost = manaCost;
	}

	public static void test() {
	}

	@Override
	public String toString() {
		String out = this.name + " (ID: " + this.id + ")\n";
		out += "Custo de Mana = " + this.manaCost + "\n";
		return out;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj) {
			return true;
		}

		if (!(obj instanceof Card)) {
			return false;
		}

		Card c = (Card) obj;
		return this.id.equals(c.getId());
	}

	@Override
	public int hashCode() {
		return id.hashCode();
	}

	public abstract void use(Card target);
}
