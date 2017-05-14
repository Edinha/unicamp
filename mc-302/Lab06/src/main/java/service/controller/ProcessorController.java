package service.controller;

import base.Table;
import base.move.Move;
import service.processor.ProcessorService;

public class ProcessorController {
	private ProcessorService service;

	public ProcessorController() {
	}

	public ProcessorController(ProcessorService service) {
		this.service = service;
	}

	public boolean process(Move move, Table table) {
		return this.service.process(move, table);
	}
}
