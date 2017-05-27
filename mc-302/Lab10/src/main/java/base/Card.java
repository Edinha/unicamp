package base;

import java.io.IOException;
import java.util.UUID;

import io.Reader;
import io.Writer;

public abstract class Card {
	private UUID id;
	private String name;
	private int manaCost;

	public Card() {
		// Reading from file constructor
	}

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

	void readBasicData(Reader reader) {
		this.id = UUID.fromString(reader.nextAttribute());
		this.manaCost = new Integer(reader.nextAttribute());
		this.name = reader.nextAttribute();
	}

	void writeBasicData(Writer writer, String subClassName) throws IOException {
		writer.writeDelimiter(subClassName);
		writer.writeAttribute("id", id.toString());
		writer.writeAttribute("mana", String.valueOf(manaCost));
		writer.writeAttribute("name", name);
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
