package base;

import io.Reader;
import io.Writer;

import java.io.IOException;

public interface LaMaSerializable {
	void readAttributes(Reader reader);
	void writeAttributes(Writer writer) throws IOException;
}
