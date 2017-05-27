package base;

import io.Reader;
import io.Writer;
import util.Util;

import java.io.IOException;
import java.util.UUID;

public class Damage extends Magic implements LaMaSerializable {

	private int damage;

	Damage() {
	}

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

	@Override
	public void readAttributes(Reader reader) {
		super.readAttributes(reader);
		this.damage = new Integer(reader.nextAttribute());
	}

	@Override
	public void writeAttributes(Writer writer) throws IOException {
		super.writeAttributes(writer);
		writer.writeAttribute("damage", String.valueOf(damage));
	}
}
