package base;

import java.io.IOException;
import java.util.UUID;

import io.Reader;
import io.Writer;

public abstract class Card implements LaMaSerializable {
	private UUID id;
	private String name;
	private int manaCost;

	Card() {
		// Reading from file constructor
	}

	Card(UUID id, String name, int manaCost) {
		this.id = id;
		this.name = name;
		this.manaCost = manaCost;
	}

	Card(String name, int manaCost) {
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

	@Override
	public void writeAttributes(Writer writer) throws IOException {
		writer.writeDelimiter(this.getClass().getSimpleName());
		writer.writeAttribute("id", id.toString());
		writer.writeAttribute("mana", String.valueOf(manaCost));
		writer.writeAttribute("name", name);
	}

	@Override
	public void readAttributes(Reader reader) {
		this.id = UUID.fromString(reader.nextAttribute());
		this.manaCost = new Integer(reader.nextAttribute());
		this.name = reader.nextAttribute();
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
