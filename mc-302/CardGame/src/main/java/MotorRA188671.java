import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.EnumMap;
import java.util.EnumSet;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Set;

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

	private Integer turno;

	private Mesa mesa;

	private List<Jogada> movimentos;

	private JogadorInfo atacante;
	private JogadorInfo defensor;

	@Override
	public int executarPartida() throws LamaException {
		vidaHeroi1 = vidaHeroi2 = 30;
		manaJogador1 = manaJogador2 = 1;
		movimentos = new ArrayList<>();

		turno = 1;

		for (int k = 0; k < 60; k++) {
			imprimir("\n=== TURNO " + turno + " ===\n");

			// Atualiza lacaiosMesa (com cópia profunda)
			JogadorInfo primeiroJogador = new JogadorInfo(1, vidaHeroi1, maoJogador1, baralho1, lacaiosMesa1, mesa.getManaJog1(), jogador1);
			JogadorInfo segundoJogador = new JogadorInfo(2, vidaHeroi2, maoJogador2, baralho2, lacaiosMesa2, mesa.getManaJog2(), jogador2);

			ArrayList<CartaLacaio> lacaios1clone = (ArrayList<CartaLacaio>) UnoptimizedDeepCopy.copy(primeiroJogador.lacaiosMesa);
			ArrayList<CartaLacaio> lacaios2clone = (ArrayList<CartaLacaio>) UnoptimizedDeepCopy.copy(segundoJogador.lacaiosMesa);

			mesa = new Mesa(lacaios1clone, lacaios2clone, primeiroJogador.vida, segundoJogador.vida, primeiroJogador.mao.size() + 1,
				segundoJogador.mao.size(), turno > 10 ? 10 : turno, turno > 10 ? 10 : (turno == 1 ? 2 : turno));

			primeiroJogador.comecarTurno();
			segundoJogador.comecarTurno();

			imprimir("\n----------------------- Começo de turno para Jogador 1:");
			boolean danoFatalProprioTurno = realizarJogadaTurno(primeiroJogador);
			if (danoFatalProprioTurno) {
				return segundoJogador.numeroJogador;
			}

			// Atualiza as variáveis para o turno do jogador 1
			atacante = primeiroJogador;
			defensor = segundoJogador;

			for (Jogada jogada : movimentos) {
				this.processarJogada(jogada);
			}

			Integer vencedorAposTurno = vencedorAposTurno();
			if (vencedorAposTurno != 0) {
				return vencedorAposTurno;
			}

			lacaios1clone = (ArrayList<CartaLacaio>) UnoptimizedDeepCopy.copy(primeiroJogador.lacaiosMesa);
			lacaios2clone = (ArrayList<CartaLacaio>) UnoptimizedDeepCopy.copy(segundoJogador.lacaiosMesa);

			mesa = new Mesa(lacaios1clone, lacaios2clone, primeiroJogador.vida, segundoJogador.vida, primeiroJogador.mao.size() + 1,
					segundoJogador.mao.size(), turno > 10 ? 10 : turno, turno > 10 ? 10 : (turno == 1 ? 2 : turno));

			imprimir("\n----------------------- Começo de turno para Jogador 2:");
			danoFatalProprioTurno = realizarJogadaTurno(segundoJogador);
			if (danoFatalProprioTurno) {
				return primeiroJogador.numeroJogador;
			}

			// Atualiza as variáveis para o turno do jogador 1
			atacante = segundoJogador;
			defensor = primeiroJogador;

			for (Jogada jogada : movimentos) {
				this.processarJogada(jogada);
			}

			vencedorAposTurno = vencedorAposTurno();
			if (vencedorAposTurno != 0) {
				return vencedorAposTurno;
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

	private Integer vencedorAposTurno() {
		if (atacante.sofreuFatalidade()) {
			return defensor.numeroJogador;
		}

		if (defensor.sofreuFatalidade()) {
			return atacante.numeroJogador;
		}

		return 0;
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
		jogador.mao.add(carta);
		return (Carta) UnoptimizedDeepCopy.copy(carta);
	}

	private boolean estourouTempoPermitido(long tempoTotal) {
		return tempoLimitado != 0 && tempoTotal > 3e8;
	}

	protected void processarJogada(Jogada umaJogada) throws LamaException {
		JOGADA_MAPA.get(umaJogada.getTipo()).processar(umaJogada, atacante, defensor);
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

		private Set<Integer> lacaiosUsadosTurno = new HashSet<>();
		private Set<Integer> cartasBaixadasTurno = new HashSet<>();

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

		void comecarTurno() {
			this.lacaiosUsadosTurno.clear();
			this.cartasBaixadasTurno.clear();
		}

		void fadiga() {
			this.vida -= this.danoFadiga++;
			imprimir("Fadiga: O " + getName() + " recebeu dano por falta de cartas. (Vida atual: " + this.vida + ")");
		}

		void baixarCarta(Carta carta) {
			this.mana -= carta.getMana();
			this.mao.remove(carta);
			this.cartasBaixadasTurno.add(carta.getID());
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

		void ataqueDireto(CartaLacaio cartaAlvo) {
			this.vida -= cartaAlvo.getAtaque();
		}
	}

	private interface Processavel {
		void processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException;
	}

	private static class AtaqueJogada implements Processavel {
		@Override
		public void processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException {
			final Carta cartaAlvo = jogada.getCartaAlvo();
			final Carta cartaJogada = jogada.getCartaJogada();
			final List<Carta> lacaiosAtacanteMesa = atacante.lacaiosMesa;

			final Integer id = cartaJogada.getID();
			if (!lacaiosAtacanteMesa.contains(cartaJogada)) {
				String mensagemErro = "Tentativa de atacar com lacaio (id: " + id + "), porém essa carta não está no campo do jogador. IDS Cartas da mesa: " + lacaiosAtacanteMesa.toString();
				throw new LamaException(5, jogada, mensagemErro, defensor.numeroJogador);
			}

			if (atacante.cartasBaixadasTurno.contains(id)) {
				String mensagemErro = "Tentativa de atacar com lacaio (id: " + id + ") que foi baixado no mesmo turno";
				throw new LamaException(6, jogada, mensagemErro, defensor.numeroJogador);
			}

			if (atacante.lacaiosUsadosTurno.contains(id)) {
				String mensagemErro = "Tentativa de atacar com lacaio (id: " + id + ") duas vezes no mesmo turno";
				throw new LamaException(7, jogada, mensagemErro, defensor.numeroJogador);
			}

			if (!defensor.lacaiosMesa.contains(cartaAlvo)) {
				String mensagemErro = "Tentativa de atacar com lacaio (id: " + id + "), porém a carta alvo não está no campo do jogador inimigo (alvo_id: " + cartaAlvo.getID() + ")";
				throw new LamaException(8, jogada, mensagemErro, defensor.numeroJogador);
			}

			atacante.lacaiosUsadosTurno.add(id);
			if (cartaAlvo == null) {
				defensor.ataqueDireto((CartaLacaio) cartaJogada);
				return;
			}

			final CartaLacaio lacaioAtacante = (CartaLacaio) atacante.lacaiosMesa.get(atacante.lacaiosMesa.indexOf(cartaJogada));
			final CartaLacaio lacaioDefensor = (CartaLacaio) defensor.lacaiosMesa.get(defensor.lacaiosMesa.indexOf(cartaAlvo));

			lacaioAtacante.setVidaAtual(lacaioAtacante.getVidaAtual() - lacaioDefensor.getVidaAtual());
			lacaioDefensor.setVidaAtual(lacaioDefensor.getVidaAtual() - lacaioAtacante.getVidaAtual());
			if (lacaioAtacante.getVidaAtual() <= 0) {
				atacante.lacaiosMesa.remove(lacaioAtacante);
			}

			if (lacaioDefensor.getVidaAtual() <= 0) {
				defensor.lacaiosMesa.remove(lacaioDefensor);
			}
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
			atacante.baixarCarta(lacaioBaixado);
			atacante.lacaiosMesa.add(lacaioBaixado);
		}
	}

	private static final Map<TipoJogada, Processavel> JOGADA_MAPA = new EnumMap<>(TipoJogada.class);
	static {
		JOGADA_MAPA.put(TipoJogada.LACAIO, new LacaioJogada());
		JOGADA_MAPA.put(TipoJogada.ATAQUE, new AtaqueJogada());
	}

}
