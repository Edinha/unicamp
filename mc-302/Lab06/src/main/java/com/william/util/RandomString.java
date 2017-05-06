package com.william.util;

import java.util.Random;

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
	private final Random random;

	public RandomString(Random random, int length) {
		if (length < 1) {
			throw new IllegalArgumentException("Length < 1: " + length);
		}

		this.buff = new char[length];
		this.random = random;
	}

	public String nextString() {
		for (int idx = 0; idx < buff.length; idx++) {
			buff[idx] = SYMBOLS[random.nextInt(SYMBOLS.length)];
		}

		return new String(buff);
	}
}
