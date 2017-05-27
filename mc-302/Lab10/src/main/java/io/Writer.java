package io;

import java.io.FileWriter;
import java.io.IOException;

public class Writer {

	private FileWriter writer;

	public Writer(String filename) throws IOException {
		this.writer = new FileWriter(filename);
	}

	public void writeAttribute(String name, String value) throws IOException {
		this.writer.append(name).append(" ").append(value).append("\n");
	}

	public void writeDelimiter(String className) throws IOException {
		this.writer.append("obj ").append(className).append("\n");
	}

	public void end() throws IOException {
		this.writer.close();
	}
}
