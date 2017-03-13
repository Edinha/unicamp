package card;

public class MinionCard {

	private int id;
	private String name;
	private int atack;
	private int currentHealth;
	private int totalHealth;
	private int manaCost;
	
	public MinionCard(int id, String name, int atack, int currentHealth, int totalHealth, int manaCost) {
		super();
		this.id = id;
		this.name = name;
		this.atack = atack;
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

	public int getAtack() {
		return atack;
	}

	public void setAtack(int atack) {
		this.atack = atack;
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

	@Override
	public String toString() {
		String out = this.name + " (ID: " + this.id + ")\n";
		out += "Ataque = " + this.atack + "\n";
		out += "Vida Atual = " + this.currentHealth + "\n";
		out += "Vida Maxima = " + this.totalHealth + "\n";
		out += "Custo de Mana = " + this.manaCost + "\n";
		return out;
	}
	
}
