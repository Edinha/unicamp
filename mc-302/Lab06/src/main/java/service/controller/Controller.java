package service.controller;

import java.util.List;

import base.Deck;
import base.Table;
import base.card.CardType;
import base.move.Move;
import service.card.CardService;
import service.card.CardServiceImpl;
import service.move.MoveService;
import service.move.MoveServiceAggressiveImpl;
import service.processor.ProcessorServiceImpl;
import util.Util;

public class Controller {
	private CardService cardService;
	private MoveService moveService;
	private ProcessorController controller;

	private Table table;
	private Deck firstDeck;
	private Deck secondDeck;

	private int maxMana = 10;
	private int maxAttack = 8;
	private int maxHealth = 20;
	private int maxMinions = 6;

	public Controller() {
		this.table = new Table();
		this.firstDeck = new Deck();
		this.secondDeck = new Deck();

		this.cardService = new CardServiceImpl();
		this.moveService = new MoveServiceAggressiveImpl();

		this.controller = new ProcessorController(new ProcessorServiceImpl());
	}

	public void execute() {
		fillDecks();

		organizeTable();

		List<Move> moves = moveService.createMove(table, 'P');

		for (Move move : moves) {
			if (controller.process(move, table)) {
				System.out.println("##### " + move.getAuthor() + " win!");
				break;
			}
		}
	}

	private void fillDecks() {
		this.firstDeck.randomFill(cardService, maxMana, maxAttack, maxHealth);
		this.secondDeck.randomFill(cardService, maxMana, maxAttack, maxHealth);
	}

	private void organizeTable() {
		for (int i = 0; i < maxMinions; i++) {
			table.getFirstPlayerMinions().add(cardService.randomCard(maxMana, maxAttack, maxHealth, CardType.MINION));
			table.getSecondPlayerMinions().add(cardService.randomCard(maxMana, maxAttack, maxHealth, CardType.MINION));
		}

		for (int i = 0; i < Util.INITIAL_HAND_SIZE; i++) {
			table.getFirstPlayerHand().add(firstDeck.pullCard());
			table.getSecondPlayerHand().add(secondDeck.pullCard());
		}

		table.getSecondPlayerHand().add(secondDeck.pullCard());
	}
}

