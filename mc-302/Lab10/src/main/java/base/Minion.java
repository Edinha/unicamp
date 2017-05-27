package base;

import java.io.IOException;

import io.Reader;
import io.Writer;
import util.Util;

public class Minion extends Card implements LaMaSerializable {
	private static final String BUFFED_NAME_SUFFIX = " Buffed";

	private int attack;
	private int totalHealth;
	private int currentHealth;

	private MinionAbility ability;

	Minion() {
	}

	public Minion(String name, int manaCost, int attack, int totalHealth, int currentHealth) {
		super(name, manaCost);
		this.attack = attack;
		this.ability = MinionAbility.EXHAUSTION;
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

	public MinionAbility getAbility() {
		return ability;
	}

	public void setAbility(MinionAbility ability) {
		this.ability = ability;
	}

	public boolean isDestroyed() {
		return (currentHealth <= 0);
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

	@Override
	public void readAttributes(Reader reader) {
		readBasicData(reader);
		this.attack = new Integer(reader.nextAttribute());
		this.ability = MinionAbility.valueOf(reader.nextAttribute());
		this.totalHealth = new Integer(reader.nextAttribute());
		this.currentHealth = new Integer(reader.nextAttribute());
	}

	@Override
	public void writeAttributes(Writer writer) throws IOException {
		writeBasicData(writer, this.getClass().getSimpleName());
		writer.writeAttribute("attack", String.valueOf(attack));
		writer.writeAttribute("ability", ability.name());
		writer.writeAttribute("totalHealth", String.valueOf(totalHealth));
		writer.writeAttribute("currentHealth", String.valueOf(currentHealth));

	}
}
