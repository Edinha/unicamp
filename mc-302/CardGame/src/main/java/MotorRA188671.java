import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.EnumMap;
import java.util.EnumSet;
import java.util.HashSet;
import java.util.List;
import java.util.Map;

@SuppressWarnings("unchecked")
public class MotorRA188671 extends Motor {

	public MotorRA188671(Baralho deck1, Baralho deck2, ArrayList<Carta> mao1, ArrayList<Carta> mao2, Jogador jogador1, Jogador jogador2,
			int verbose, int tempoLimitado, PrintWriter saidaArquivo, EnumSet<Funcionalidade> funcionalidadesAtivas) {

		super(deck1, deck2, mao1, mao2, jogador1, jogador2, verbose, tempoLimitado, saidaArquivo, funcionalidadesAtivas);

		imprimir("========================");
		imprimir("*** Classe " + this.getClass().getName() + " inicializada.");
		imprimir("Funcionalidade ativas no Motor:");
		imprimir("INVESTIDA: " + (this.funcionalidadesAtivas.contains(Funcionalidade.INVESTIDA) ? "SIM" : "NAO"));
		imprimir("ATAQUE_DUPLO: " + (this.funcionalidadesAtivas.contains(Funcionalidade.ATAQUE_DUPLO) ? "SIM" : "NAO"));
		imprimir("PROVOCAR: " + (this.funcionalidadesAtivas.contains(Funcionalidade.PROVOCAR) ? "SIM" : "NAO"));
		imprimir("========================");
	}

	private int jogador; // 1 == turno do jogador1, 2 == turno do jogador2.
	private int turno;
	private int nCartasHeroi1;
	private int nCartasHeroi2;

	private Mesa mesa;

	// "Apontadores" - Assim podemos programar genericamente os métodos para funcionar com ambos os
	// jogadores
	private ArrayList<Carta> mao;
	private ArrayList<Carta> lacaios;
	private ArrayList<Carta> lacaiosOponente;

	// "Memória" - Para marcar ações que só podem ser realizadas uma vez por turno.
	private boolean poderHeroicoUsado;
	private HashSet<Integer> lacaiosAtacaramID;

	private List<Jogada> movimentos;

	private JogadorInfo atacante;
	private JogadorInfo defensor;

	@Override
	public int executarPartida() throws LamaException {
		vidaHeroi1 = vidaHeroi2 = 30;
		manaJogador1 = manaJogador2 = 1;
		nCartasHeroi1 = cartasIniJogador1;
		nCartasHeroi2 = cartasIniJogador2;
		movimentos = new ArrayList<>();

		int noCardDmgCounter1 = 1;
		int noCardDmgCounter2 = 1;
		turno = 1;

		for (int k = 0; k < 60; k++) {
			imprimir("\n=== TURNO " + turno + " ===\n");

			// Atualiza lacaiosMesa (com cópia profunda)
			ArrayList<CartaLacaio> lacaios1clone = (ArrayList<CartaLacaio>) UnoptimizedDeepCopy.copy(lacaiosMesa1);
			ArrayList<CartaLacaio> lacaios2clone = (ArrayList<CartaLacaio>) UnoptimizedDeepCopy.copy(lacaiosMesa2);

			mesa = new Mesa(lacaios1clone, lacaios2clone, vidaHeroi1, vidaHeroi2, nCartasHeroi1 + 1, nCartasHeroi2, turno > 10 ? 10 : turno,
				turno > 10 ? 10 : (turno == 1 ? 2 : turno));

			JogadorInfo primeiroJogador = new JogadorInfo(1, vidaHeroi1, maoJogador1, baralho1, lacaiosMesa1, mesa.getManaJog1(), jogador1);
			JogadorInfo segundoJogador = new JogadorInfo(2, vidaHeroi2, maoJogador2, baralho2, lacaiosMesa2, mesa.getManaJog2(), jogador2);

			imprimir("\n----------------------- Começo de turno para Jogador 1:");
			boolean danoFatalProprioTUrno = realizarJogadaTurno(primeiroJogador);
			if (danoFatalProprioTUrno) {
				return 2;
			}

			// Atualiza as variáveis para o turno do jogador 1
			atacante = primeiroJogador;
			defensor = segundoJogador;

			for (Jogada jogada : movimentos) {
				this.processarJogada(jogada);
			}


			// Apontadores para jogador1
//			mao = maoJogador1;
//			lacaios = lacaiosMesa1;
//			lacaiosOponente = lacaiosMesa2;
//			jogador = 1;

			// Processa o turno 1 do Jogador1
//			long startTime, endTime, totalTime;

			// Cópia profunda de jogadas realizadas.
//			ArrayList<Jogada> cloneMovimentos1 = (ArrayList<Jogada>) UnoptimizedDeepCopy.copy(movimentos);

//			startTime = System.nanoTime();
//			if (baralho1.getCartas().size() > 0) {
//				if (nCartasHeroi1 >= maxCartasMao) {
//					movimentos = jogador1.processarTurno(mesa, null, cloneMovimentos1);
//					comprarCarta(); // carta descartada
//				} else
//					movimentos = jogador1.processarTurno(mesa, comprarCarta(), cloneMovimentos1);
//			} else {
//				imprimir("Fadiga: O Herói 1 recebeu " +
//					noCardDmgCounter1 +
//					" de dano por falta de cartas no baralho. (Vida restante: " +
//					(vidaHeroi1 - noCardDmgCounter1) +
//					").");
//				vidaHeroi1 -= noCardDmgCounter1++;
//				if (vidaHeroi1 <= 0) {
//					 Jogador 2 venceu
//					imprimir("O jogador 2 venceu porque o jogador 1 recebeu um dano mortal por falta de cartas ! (Dano : " +
//						(noCardDmgCounter1 - 1) +
//						", Vida Herói 1: " +
//						vidaHeroi1 +
//						")");
//					return 2;
//				}
//				movimentos = jogador1.processarTurno(mesa, null, cloneMovimentos1);
//			}
//
//			endTime = System.nanoTime();
//			totalTime = endTime - startTime;
//			if (tempoLimitado != 0 && totalTime > 3e8) { // 300ms
//				 Jogador 2 venceu, Jogador 1 excedeu limite de tempo
//				return 2;
//			} else
//				imprimir("Tempo usado em processarTurno(): " + totalTime / 1e6 + "ms");

//			 Começa a processar jogadas do Jogador 1
			this.poderHeroicoUsado = false;
			this.lacaiosAtacaramID = new HashSet<>();
			for (Jogada movimento : movimentos) {
				processarJogada(movimento);
			}

			if (vidaHeroi2 <= 0) {
				// Jogador 1 venceu
				return 1;
			}

			// Atualiza lacaiosMesa (com cópia profunda)
			ArrayList<CartaLacaio> lacaios1clone2 = (ArrayList<CartaLacaio>) UnoptimizedDeepCopy.copy(lacaiosMesa1);
			ArrayList<CartaLacaio> lacaios2clone2 = (ArrayList<CartaLacaio>) UnoptimizedDeepCopy.copy(lacaiosMesa2);

			mesa = new Mesa(lacaios1clone2, lacaios2clone2, vidaHeroi1, vidaHeroi2, nCartasHeroi1, nCartasHeroi2 + 1, turno > 10 ? 10
				: turno, turno > 10 ? 10 : (turno == 1 ? 2 : turno));

			// Apontadores para jogador2
//			mao = maoJogador2;
//			lacaios = lacaiosMesa2;
//			lacaiosOponente = lacaiosMesa1;
//			jogador = 2;
//
//			 Processa o turno 1 do Jogador2
//			imprimir("\n\n----------------------- Começo de turno para Jogador 2:");
//
//			 Cópia profunda de jogadas realizadas.
//			ArrayList<Jogada> cloneMovimentos2 = (ArrayList<Jogada>) UnoptimizedDeepCopy.copy(movimentos);
//
//			startTime = System.nanoTime();
//
//
//			if (baralho2.getCartas().size() > 0) {
//				if (nCartasHeroi2 >= maxCartasMao) {
//					movimentos = jogador2.processarTurno(mesa, null, cloneMovimentos2);
//					comprarCarta(); // carta descartada
//				} else
//					movimentos = jogador2.processarTurno(mesa, comprarCarta(), cloneMovimentos2);
//			} else {
//				imprimir("Fadiga: O Herói 2 recebeu " +
//					noCardDmgCounter2 +
//					" de dano por falta de cartas no baralho. (Vida restante: " +
//					(vidaHeroi2 - noCardDmgCounter2) +
//					").");
//				vidaHeroi2 -= noCardDmgCounter2++;
//				if (vidaHeroi2 <= 0) {
//					 Vitoria do jogador 1
//					imprimir("O jogador 1 venceu porque o jogador 2 recebeu um dano mortal por falta de cartas ! (Dano : " +
//						(noCardDmgCounter2 - 1) +
//						", Vida Herói 2: " +
//						vidaHeroi2 +
//						")");
//					return 1;
//				}
//				movimentos = jogador2.processarTurno(mesa, null, cloneMovimentos2);
//			}
//
//			endTime = System.nanoTime();
//			totalTime = endTime - startTime;
//			if (tempoLimitado != 0 && totalTime > 3e8) { // 300ms
//				 Limite de tempo pelo jogador 2. Vitoria do jogador 1.
//				return 1;
//			} else
//				imprimir("Tempo usado em processarTurno(): " + totalTime / 1e6 + "ms");
//
			this.poderHeroicoUsado = false;
			this.lacaiosAtacaramID = new HashSet<>();
			for (int i = 0; i < movimentos.size(); i++) {
				processarJogada(movimentos.get(i));
			}
			if (vidaHeroi1 <= 0) {
				// Vitoria do jogador 2
				return 2;
			}

			turno++;
		}

		// Nunca vai chegar aqui dependendo do número de rodadas
		imprimir("Erro: A partida não pode ser determinada em mais de 60 rounds. Provavel BUG.");
		throw new LamaException(-1, null, "Erro desconhecido. Mais de 60 turnos sem termino do jogo.", 0);
	}

	/**
	 * Realiza um entrada de turno para o jogador parametrizado
	 * @param jogadorInfo quem realiza a jogada do turno
	 * @return verdadeiro se o jogador perdeu seu proprio turno de ataque e falso c.c.
	 */
	private boolean realizarJogadaTurno(JogadorInfo jogadorInfo) {
		long totalTime = calcularTempoJogada(jogadorInfo);
		imprimir("Tempo usado em processarTurno(): " + totalTime / 1e6 + "ms");

		boolean danoFatal = jogadorInfo.sofreuFatalidade();
		if (danoFatal) {
			imprimir(jogadorInfo.getName() + " recebeu dano fatal pela fadiga");
		}

		return estourouTempoPermitido(totalTime) || danoFatal;
	}

	private long calcularTempoJogada(JogadorInfo jogador) {
		long startTime;
		startTime = System.nanoTime();

		ArrayList<Jogada> cloneMovimentos = (ArrayList<Jogada>) UnoptimizedDeepCopy.copy(movimentos);
		movimentos = jogador.referencia.processarTurno(mesa, sacarCarta(jogador), cloneMovimentos);

		return startTime - System.nanoTime();
	}

	private Carta sacarCarta(JogadorInfo jogador) {
		if (jogador.baralho.getCartas().isEmpty()) {
			jogador.fadiga();
			return null;
		}

		Carta carta = jogador.baralho.comprarCarta();
		this.mao.add(carta);
		return (Carta) UnoptimizedDeepCopy.copy(carta);
	}

	private boolean estourouTempoPermitido(long tempoTotal) {
		return tempoLimitado != 0 && tempoTotal > 3e8;
	}

	protected void processarJogada(Jogada umaJogada) throws LamaException {
		MAP.get(umaJogada.getTipo()).processar(umaJogada, atacante, defensor);

//		switch (umaJogada.getTipo()) {
//			case ATAQUE:
//				// TODO: Um ataque foi realizado... quem atacou? quem foi atacado? qual o dano? o
//				// alvo sofreuFatalidade ou ficou com quanto de vida? Trate o caso do herói como alvo também.
//				break;
//			case LACAIO:
//				int lacaioID = umaJogada.getCartaJogada().getID();
//				imprimir("JOGADA: O lacaio_id=" + lacaioID + " foi baixado para a lacaiosMesa.");
//				if (mao.contains(umaJogada.getCartaJogada())) {
//					Carta lacaioBaixado = mao.get(mao.indexOf(umaJogada.getCartaJogada()));
//					lacaios.add(lacaioBaixado); // lacaio adicionado à lacaiosMesa
//					mao.remove(umaJogada.getCartaJogada()); // lacaio retirado da mão
//				} else {
//					String erroMensagem = "Erro: Tentou-se usar a carta_id=" +
//						lacaioID +
//						", porém esta carta não existe na mao. IDs de cartas na mao: ";
//					for (Carta card : mao) {
//						erroMensagem += card.getID() + ", ";
//					}
//					imprimir(erroMensagem);
//					// Dispara uma LamaException passando o código do erro, uma mensagem descritiva
//					// correspondente e qual jogador deve vencer a partida.
//					throw new LamaException(1, umaJogada, erroMensagem, jogador == 1 ? 2 : 1);
//				}
//				// Obs: repare que este código funcionará tanto quando trata-se do turno do jogador1
//				// ou do jogador2.
//				break;
//			case MAGIA:
//				// TODO: Uma magia foi usada... é de área, alvo ou buff? Se de alvo ou buff, qual o
//				// lacaio receberá o dano/buff ?
//				break;
//			case PODER:
//				// TODO: O poder heroico foi usado. Qual o alvo ?
//				break;
//			default:
//				break;
//		}
	}

	private Carta comprarCarta() {
		if (this.jogador == 1) {
			if (baralho1.getCartas().size() <= 0) {
				throw new RuntimeException("Erro: Não há mais cartas no baralho para serem compradas.");
			}

			Carta nova = baralho1.comprarCarta();
			mao.add(nova);
			nCartasHeroi1++;
			return (Carta) UnoptimizedDeepCopy.copy(nova);
		} else {
			if (baralho2.getCartas().size() <= 0) {
				throw new RuntimeException("Erro: Não há mais cartas no baralho para serem compradas.");
			}

			Carta nova = baralho2.comprarCarta();
			mao.add(nova);
			nCartasHeroi2++;
			return (Carta) UnoptimizedDeepCopy.copy(nova);
		}
	}

	private class JogadorInfo {
		private Integer vida;
		private Integer mana;
		private Integer danoFadiga;

		private List<Carta> mao;

		private Baralho baralho;
		private List<Jogada> jogadas;
		private List<Carta> lacaiosMesa;

		private Jogador referencia;
		private Integer numeroJogador;

		JogadorInfo(Integer jogador, Integer vida, List<Carta> mao, Baralho baralho, List<Carta> lacaiosMesa, Integer mana, Jogador referencia) {
			this.vida = vida;
			this.mana = mana;
			this.baralho = baralho;

			this.mao = (List<Carta>) UnoptimizedDeepCopy.copy(mao);
			this.jogadas = (List<Jogada>) UnoptimizedDeepCopy.copy(jogadas);
			this.lacaiosMesa = (List<Carta>) UnoptimizedDeepCopy.copy(lacaiosMesa);

			this.danoFadiga = 1;
			this.referencia = referencia;
			this.numeroJogador = jogador;
		}

		void fadiga() {
			this.vida -= this.danoFadiga++;
			imprimir("Fadiga: O " + getName() + " recebeu dano por falta de cartas. (Vida atual: " + this.vida + ")");
		}

		void baixarCarta(Carta carta) {
			this.mana -= carta.getMana();
		}

		boolean temManaSuficiente(Carta carta) {
			return (this.mana >= carta.getMana());
		}

		boolean sofreuFatalidade() {
			return (vida <= 0);
		}

		String getName() {
			return "Heroi " + numeroJogador;
		}
	}

	private interface Processavel {
		void processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException;
	}

	private static class AtaqueJogada implements Processavel {
		@Override
		public void processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException {
			final List<Carta> lacaiosMesa = atacante.lacaiosMesa;
			final Carta cartaJogada = jogada.getCartaJogada();

			int id = cartaJogada.getID();
			if (!lacaiosMesa.contains(cartaJogada)) {
				String mensagemErro = "Tentativa de atacar com lacaio (id: " + id +
						"), porém essa carta não está no campo do jogador. IDS Cartas da mesa: " +
						lacaiosMesa.toString();

				throw new LamaException(5, jogada, mensagemErro, defensor.numeroJogador);
			}

			Carta cartaAlvo = jogada.getCartaAlvo();

//			Carta lacaioBaixado = lacaiosMesa.get(lacaiosMesa.indexOf(cartaJogada));
//			atacante.lacaiosMesa.add(lacaioBaixado);
//			lacaiosMesa.remove(cartaJogada);
		}
	}

	private static class LacaioJogada implements Processavel {
		@Override
		public void processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException {
			final List<Carta> mao = atacante.mao;
			final Carta cartaJogada = jogada.getCartaJogada();

			int id = cartaJogada.getID();
			if (!mao.contains(cartaJogada)) {
				String mensagemErro = "Tentativa de usar carta (id: " + id +
						"), porém essa carta não existe na mão do jogador. IDS Cartas da mao: " +
						mao.toString();

				throw new LamaException(1, jogada, mensagemErro, defensor.numeroJogador);
			}

			Carta lacaioBaixado = mao.get(mao.indexOf(cartaJogada));
			atacante.lacaiosMesa.add(lacaioBaixado);
			mao.remove(cartaJogada);
		}
	}

	private static final Map<TipoJogada, Processavel> MAP = new EnumMap<>(TipoJogada.class);
	static {
		MAP.put(TipoJogada.ATAQUE, new AtaqueJogada());
		MAP.put(TipoJogada.LACAIO, new LacaioJogada());
	}
}
