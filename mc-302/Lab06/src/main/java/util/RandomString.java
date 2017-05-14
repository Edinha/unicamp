package util;

import java.util.concurrent.ThreadLocalRandom;

public class RandomString {

	private static final char[] SYMBOLS;

	static {
		StringBuilder tmp = new StringBuilder();
		for (char ch = '0'; ch < '9'; ch++) {
			tmp.append(ch);
		}

		for (char ch = 'a'; ch < 'z'; ch++) {
			tmp.append(ch);
		}

		SYMBOLS = tmp.toString().toCharArray();
	}

	private final char[] buff;

	public RandomString(int length) {
		if (length < 1) {
			throw new IllegalArgumentException("Length < 1: " + length);
		}

		this.buff = new char[length];
	}

	public String nextString() {
		for (int idx = 0; idx < buff.length; idx++) {
			buff[idx] = SYMBOLS[ThreadLocalRandom.current().nextInt(SYMBOLS.length)];
		}

		return new String(buff);
	}
}
