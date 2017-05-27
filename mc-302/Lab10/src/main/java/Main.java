import java.io.FileNotFoundException;
import java.io.IOException;

import base.Buff;
import base.Damage;
import base.DamageArea;
import base.Minion;
import io.Reader;
import io.Writer;

public class Main {

	public static void main(String[] args) {

		Minion minion = new Minion("Minion", 10, 9, 8, 7);
		Damage damage = new Damage("Damage", 6, 5);
		DamageArea area = new DamageArea("Damage area", 4, 3);
		Buff buff = new Buff("Buff", 2, 1, 0);

		try {
			Writer writer = new Writer("test.txt");

			minion.writeAttributes(writer);
			damage.writeAttributes(writer);
			area.writeAttributes(writer);
			buff.writeAttributes(writer);

			writer.end();
		} catch (IOException e) {
			System.err.println("Error while writing in file... ");
			e.printStackTrace();
		}

		try {
			new Reader("test.txt").readObjects().forEach(System.out::println);
		} catch (FileNotFoundException e) {
			System.err.println("Error while reading the file (do not exists)... ");
			e.printStackTrace();
		}

	}

}