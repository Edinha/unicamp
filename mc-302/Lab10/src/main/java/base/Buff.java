package base;

import io.Reader;
import io.Writer;
import util.Util;

import java.io.IOException;
import java.util.UUID;

public class Buff extends Magic implements LaMaSerializable {

	private int attackBuff;
	private int healthBuff;

	Buff() {
		super();
	}

	public Buff(UUID id, String name, int manaCost, int attackBuff, int healthBuff) {
		super(id, name, manaCost);
		this.attackBuff = attackBuff;
		this.healthBuff = healthBuff;
	}

	public Buff(String name, int manaCost, int attackBuff, int healthBuff) {
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

	@Override
	public void readAttributes(Reader reader) {
		readBasicData(reader);
		this.attackBuff = new Integer(reader.nextAttribute());
		this.healthBuff = new Integer(reader.nextAttribute());
	}

	@Override
	public void writeAttributes(Writer writer) throws IOException {
		writeBasicData(writer, this.getClass().getSimpleName());
		writer.writeAttribute("attackBuff", String.valueOf(attackBuff));
		writer.writeAttribute("healthBuff", String.valueOf(healthBuff));
	}
}
