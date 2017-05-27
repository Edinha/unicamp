package base;

import java.util.UUID;

public abstract class Magic extends Card {

	public Magic() {
		// Reading from file constructor
	}

	public Magic(UUID id, String name, int manaCost) {
		super(id, name, manaCost);
	}

	public Magic(String name, int manaCost) {
		super(name, manaCost);
	}
}
