package service.controller;

import java.util.List;

import base.Deck;
import base.Table;
import base.exception.NullTableException;
import base.move.Move;
import service.card.CardService;
import service.card.CardServiceImpl;
import service.deck.DeckService;
import service.deck.DeckServiceImpl;
import service.move.MoveService;
import service.move.MoveServiceAggressiveImpl;
import service.processor.ProcessorService;
import service.processor.ProcessorServiceImpl;
import service.table.TableService;
import service.table.TableServiceImpl;

public class Controller {
	private CardService cardService;
	private MoveService moveService;
	private DeckService deckService;
	private TableService tableService;
	private ProcessorService processorService;

	private Table table;
	private Deck firstDeck;
	private Deck secondDeck;

	public Controller() {
		this.table = new Table();
		this.firstDeck = new Deck();
		this.secondDeck = new Deck();

		this.cardService = new CardServiceImpl();
		this.deckService = new DeckServiceImpl();
		this.tableService = new TableServiceImpl();
		this.moveService = new MoveServiceAggressiveImpl();
		this.processorService = new ProcessorServiceImpl();
	}

	public void execute() {
		fillDecks();

		organizeTable();

		List<Move> moves = moveService.createMove(table, 'P');

		for (Move move : moves) {
			if (processorService.process(move, table)) {
				System.out.println("##### " + move.getAuthor() + " win!");
				break;
			}
		}
	}

	private void fillDecks() {
		this.firstDeck.fill(deckService.randomFill(cardService));
		this.secondDeck.fill(deckService.randomFill(cardService));
	}

	private void organizeTable() {
		try {
			this.tableService.addMinions(table, cardService);
			this.tableService.addInitialHand(table, firstDeck, secondDeck);
		} catch (NullTableException e) {
			// TODO
//			e.printStackTrace();
		}
	}
}

