package io;

import base.CardType;
import base.LaMaSerializable;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class Reader {

	private Scanner scanner;

	public Reader(String filename) throws FileNotFoundException {
		this.scanner = new Scanner(new File(filename));
	}

	public String nextAttribute() {
		return this.scanner.nextLine().split(" ")[1];
	}

	public List<LaMaSerializable> readObjects() {
		List<LaMaSerializable> result = new ArrayList<>();

		while (this.scanner.hasNext()) {
			String className = nextAttribute();

			LaMaSerializable serializable = CardType.of(className);
			serializable.readAttributes(this);

			result.add(serializable);
		}

		this.scanner.close();

		return result;
	}
}
