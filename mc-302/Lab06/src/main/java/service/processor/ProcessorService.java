package service.processor;

import base.Table;
import base.move.Move;

public interface ProcessorService {
	boolean process(Move move, Table table);
}
