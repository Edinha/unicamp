package service.move;

import base.Table;
import base.move.Move;

import java.util.List;

public interface MoveService {
	List<Move> createMove(Table table, char player);
}
