import java.io.PrintWriter;
import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.Collection;
import java.util.EnumMap;
import java.util.EnumSet;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Set;
import java.util.stream.Collectors;

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

	private Mesa mesa;

	private List<Jogada> movimentos;

	private JogadorInfo atacante;
	private JogadorInfo defensor;

	private static final Map<TipoJogada, Processavel> JOGADA_MAPA = new EnumMap<>(TipoJogada.class);
	private static final Map<TipoMagia, Processavel> MAGIA_JOGADA_MAPA = new EnumMap<>(TipoMagia.class);
	static {
		JOGADA_MAPA.put(TipoJogada.MAGIA, new MagiaJogada());
		JOGADA_MAPA.put(TipoJogada.LACAIO, new LacaioJogada());
		JOGADA_MAPA.put(TipoJogada.ATAQUE, new AtaqueJogada());
		JOGADA_MAPA.put(TipoJogada.PODER, new PoderHeroicoJogada());

		MAGIA_JOGADA_MAPA.put(TipoMagia.ALVO, null);
		MAGIA_JOGADA_MAPA.put(TipoMagia.BUFF, new BuffJogada());
		MAGIA_JOGADA_MAPA.put(TipoMagia.AREA, null);
	}

	@Override
	public int executarPartida() throws LamaException {
		vidaHeroi1 = vidaHeroi2 = 30;
		manaJogador1 = manaJogador2 = 1;
		movimentos = new ArrayList<>();

		Integer turno = 1;

		for (int k = 0; k < 60; k++) {
			imprimir("\n=== TURNO " + turno + " ===\n");

			// Atualiza lacaiosMesa (com cópia profunda)

			manaJogador1 = turno > 10 ? 10 : turno;
			manaJogador2 = turno > 10 ? 10 : (turno == 1 ? 2 : turno);

			JogadorInfo primeiroJogador = new JogadorInfo(1, vidaHeroi1, maoJogador1, baralho1, lacaiosMesa1, manaJogador1, jogador1);
			JogadorInfo segundoJogador = new JogadorInfo(2, vidaHeroi2, maoJogador2, baralho2, lacaiosMesa2, manaJogador2, jogador2);

			ArrayList<CartaLacaio> lacaios1clone = (ArrayList<CartaLacaio>) UnoptimizedDeepCopy.copy(primeiroJogador.lacaiosMesa);
			ArrayList<CartaLacaio> lacaios2clone = (ArrayList<CartaLacaio>) UnoptimizedDeepCopy.copy(segundoJogador.lacaiosMesa);

			mesa = new Mesa(lacaios1clone, lacaios2clone, primeiroJogador.vida, segundoJogador.vida, primeiroJogador.mao.size() + 1,
					segundoJogador.mao.size(), primeiroJogador.mana, segundoJogador.mana);

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
					segundoJogador.mao.size(), primeiroJogador.mana, segundoJogador.mana);

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
			imprimir(jogadorInfo.getNome() + " recebeu dano fatal pela fadiga");
		}

		return estourouTempoPermitido(totalTime) || danoFatal;
	}

	/**
	 * Método que avalia a existência de um vencedor para o turno
	 * @return O número contrário ao jogador que sofreu fatalidade no turno, 0 caso nenhum tenha sofrido fatalidade
	 */
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
		imprimir(JOGADA_MAPA.get(umaJogada.getTipo()).processar(umaJogada, atacante, defensor));
	}

	private class JogadorInfo {
		private Integer vida;
		private Integer mana;
		private Integer danoFadiga;

		private List<Carta> mao;

		private Baralho baralho;
		private List<Jogada> jogadas;
		private List<CartaLacaio> lacaiosMesa;

		private Jogador referencia;
		private Integer numeroJogador;

		private Set<Integer> lacaiosUsadosTurno = new HashSet<>();
		private Set<Integer> cartasBaixadasTurno = new HashSet<>();

		private boolean poderHeroicoUtilizado;

		JogadorInfo(Integer jogador, Integer vida, List<Carta> mao, Baralho baralho, List<Carta> lacaiosMesa, Integer mana, Jogador referencia) {
			this.vida = vida;
			this.mana = mana;
			this.baralho = baralho;

			this.mao = (List<Carta>) UnoptimizedDeepCopy.copy(mao);
			this.jogadas = (List<Jogada>) UnoptimizedDeepCopy.copy(jogadas);

			List<Carta> copiaLacaiosMesa = (List<Carta>) UnoptimizedDeepCopy.copy(lacaiosMesa);
			this.lacaiosMesa = copiaLacaiosMesa.stream().map(l -> (CartaLacaio) l).collect(Collectors.toList());

			this.danoFadiga = 1;
			this.referencia = referencia;
			this.numeroJogador = jogador;
		}

		void comecarTurno() {
			this.poderHeroicoUtilizado = false;
			this.lacaiosUsadosTurno.clear();
			this.cartasBaixadasTurno.clear();
		}

		void fadiga() {
			this.vida -= this.danoFadiga++;
			imprimir("Fadiga: O " + getNome() + " recebeu dano por falta de cartas. (Vida atual: " + this.vida + ")");
		}

		void baixarCarta(Carta carta) {
			this.mana -= carta.getMana();
			this.mao.remove(carta);
			this.cartasBaixadasTurno.add(carta.getID());
			this.lacaiosMesa.add((CartaLacaio) carta);
		}

		boolean temManaSuficientePoderHeroico() {
			return (this.mana >= 2);
		}

		boolean temManaSuficiente(Carta carta) {
			return (this.mana >= carta.getMana());
		}

		boolean sofreuFatalidade() {
			return (vida <= 0);
		}

		String getNome() {
			return "Heroi " + numeroJogador;
		}

		void ataqueDireto(CartaLacaio cartaAlvo) {
			this.vida -= cartaAlvo.getAtaque();
		}

		void sofrerDanoPoderHeroico() {
			this.vida--;
		}

		void sofrerDanoLacaio(CartaLacaio lacaio) {
			this.vida -= lacaio.getAtaque();
		}

		void removerLacaiosDestruidos() {
			this.lacaiosMesa = lacaiosMesa.stream().filter(l -> l.getVidaAtual() > 0).collect(Collectors.toList());
		}

		void usarPoderHeroico() {
			this.poderHeroicoUtilizado = true;
		}
	}

	private interface Processavel {
		String processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException;

		default void manaInsuficiente(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException {
			if (!atacante.temManaSuficiente(jogada.getCartaJogada())) {
				String mensagem = format("Mana insuficiente para jogada de {0} (mana necessária: 2, mana atual: {1})",
						jogada.getTipo().name(),
						atacante.mana.toString());
				throw new LamaException(2, jogada, mensagem, defensor.numeroJogador);
			}
		}
	}

	private static class AtaqueJogada implements Processavel {
		@Override
		public String processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException {
			final Carta cartaAlvo = jogada.getCartaAlvo();
			final Carta cartaJogada = jogada.getCartaJogada();

			final Integer id = cartaJogada.getID();

			final Optional<CartaLacaio> defensorOptional = defensor.lacaiosMesa.stream().filter(l -> l.equals(cartaAlvo)).findFirst();
			final Optional<CartaLacaio> atacanteOptional = atacante.lacaiosMesa.stream().filter(l -> l.equals(cartaJogada)).findFirst();

			if (!atacanteOptional.isPresent()) {
				String mensagemErro = format("Tentativa de atacar com lacaio (id: {0}), porém essa carta não está no campo do jogador. IDS Cartas da mesa: {1}",
					id.toString(),
					ids(atacante.lacaiosMesa));
				
				throw new LamaException(5, jogada, mensagemErro, defensor.numeroJogador);
			}

			if (atacante.cartasBaixadasTurno.contains(id)) {
				String mensagemErro = format("Tentativa de atacar com lacaio (id: {0}) que foi baixado no mesmo turno", id.toString());
				throw new LamaException(6, jogada, mensagemErro, defensor.numeroJogador);
			}

			if (atacante.lacaiosUsadosTurno.contains(id)) {
				String mensagemErro = format("Tentativa de atacar com lacaio (id: {0}) duas vezes no mesmo turno", id.toString());
				throw new LamaException(7, jogada, mensagemErro, defensor.numeroJogador);
			}

			atacante.lacaiosUsadosTurno.add(id);
			if (cartaAlvo == null) {
				defensor.ataqueDireto((CartaLacaio) cartaJogada);
				return format("{0} atacou diretamente o herói inimigo com lacaio {1}", atacante.getNome(), cartaJogada.getNome());
			}

			if (!defensorOptional.isPresent()) {
				String mensagemErro = "Tentativa de atacar com lacaio (id: " +
					id +
					"), porém a carta alvo não está no campo do jogador inimigo (alvo_id: " +
					cartaAlvo.getID() +
					")";
				throw new LamaException(8, jogada, mensagemErro, defensor.numeroJogador);
			}

			final CartaLacaio lacaioAtacante = atacanteOptional.get();
			final CartaLacaio lacaioDefensor = defensorOptional.get();
			lacaioAtacante.setVidaAtual(lacaioAtacante.getVidaAtual() - lacaioDefensor.getVidaAtual());
			lacaioDefensor.setVidaAtual(lacaioDefensor.getVidaAtual() - lacaioAtacante.getVidaAtual());

			atacante.removerLacaiosDestruidos();
			defensor.removerLacaiosDestruidos();

			return format("{0} aatacou lacaio inimigo {1} com seu lacaio {2}", atacante.getNome(), cartaJogada.getNome(), cartaAlvo.getNome());
		}
	}

	private static class LacaioJogada implements Processavel {
		@Override
		public String processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException {

			manaInsuficiente(jogada, atacante, defensor);

			final Carta cartaJogada = jogada.getCartaJogada();
			final Optional<Carta> cartaOptional = atacante.mao.stream().filter(carta -> carta.equals(cartaJogada)).findFirst();
			if (!cartaOptional.isPresent()) {
				String mensagemErro = format(
					"Tentativa de usar carta (id: {0}), porém essa carta não existe na mão do jogador. IDS Cartas da mão: {1}",
					cartaJogada.getID() + "",
					ids(atacante.mao));

				throw new LamaException(1, jogada, mensagemErro, defensor.numeroJogador);
			}

			Carta lacaioBaixado = cartaOptional.get();
			atacante.baixarCarta(lacaioBaixado);

			return format("{0} baixou a carta {1} com custo de mana de {2}", atacante.getNome(), cartaJogada.getNome(), cartaJogada.getMana()+"");
		}
	}

	private static class PoderHeroicoJogada implements Processavel {
		@Override
		public String processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException {
			if (atacante.poderHeroicoUtilizado) {
				String mensagem = format("{0} já utilizou poder heróico neste turno.", atacante.getNome());
				throw new LamaException(11, jogada, mensagem, defensor.numeroJogador);
			}

			atacante.usarPoderHeroico();
			if (!atacante.temManaSuficientePoderHeroico()) {
				String mensagem = format("Mana insuficiente para jogada de {0} (mana necessária: 2, mana atual: {1})",
					jogada.getTipo().name(),
					atacante.mana.toString());
				throw new LamaException(2, jogada, mensagem, defensor.numeroJogador);
			}

			final Carta cartaAlvo = jogada.getCartaAlvo();
			if (cartaAlvo == null) {
				defensor.sofrerDanoPoderHeroico();
				return format("{0} usou poder heróico no herói inimigo", atacante.getNome());
			}

			final Optional<CartaLacaio> alvo = defensor.lacaiosMesa.stream().filter(l -> l.equals(cartaAlvo)).findAny();
			if (!alvo.isPresent()) {
				String mensagem = format("Tentativa de usar poder heróico em alvo inexistente (alvo_id: {0})", cartaAlvo.getID()+"");
				throw new LamaException(12, jogada, mensagem, defensor.numeroJogador);
			}

			final CartaLacaio lacaio = alvo.get();
			defensor.sofrerDanoLacaio(lacaio);
			lacaio.setVidaAtual(lacaio.getVidaAtual() - 1);

			defensor.removerLacaiosDestruidos();

			return format("{0} usou poder heróico no lacaio inimigo {1}", atacante.getNome(), cartaAlvo.getNome());
		}
	}

	private static class MagiaJogada implements Processavel {
		@Override
		public String processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException {

			manaInsuficiente(jogada, atacante, defensor);

			final Carta cartaJogada = jogada.getCartaJogada();
			final Optional<Carta> cartaOptional = atacante.mao.stream().filter(carta -> carta.equals(cartaJogada)).findFirst();
			if (!cartaOptional.isPresent()) {
				String mensagemErro = format(
						"Tentativa de usar carta (id: {0}), porém essa carta não existe na mão do jogador. IDS Cartas da mão: {1}",
						cartaJogada.getID() + "",
						ids(atacante.mao));

				throw new LamaException(1, jogada, mensagemErro, defensor.numeroJogador);
			}

			if (cartaJogada instanceof CartaLacaio) {
				String mensagem = format("Tentativa de utilizar a carta lacaio {0} (id: {1}) como uma magia",
					cartaJogada.getNome(),
					cartaJogada.getID());
				throw new LamaException(9, jogada, mensagem, defensor.numeroJogador);
			}

			final CartaMagia magia = (CartaMagia) cartaJogada;
			return MAGIA_JOGADA_MAPA.get(magia.getMagiaTipo()).processar(jogada, atacante, defensor);
		}
	}

	private static class BuffJogada implements Processavel {
		@Override
		public String processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException {
			final Carta alvo = jogada.getCartaAlvo();
			final CartaMagia buff = (CartaMagia) jogada.getCartaJogada();

			Optional<CartaLacaio> alvoOptional = atacante.lacaiosMesa.stream().filter(l -> l.equals(alvo)).findFirst();
			if (!alvoOptional.isPresent()) {
				String mensagem = format("Tentativa de utilizar magia de buff (id: {0}) em uma carta inexistente (id: {1})",
						buff.getID(),
						alvo.getID());
				throw new LamaException(10, jogada, mensagem, defensor.numeroJogador);
			}

			final CartaLacaio lacaio = alvoOptional.get();
			lacaio.setAtaque(lacaio.getAtaque() + buff.getMagiaDano());
			lacaio.setVidaAtual(lacaio.getVidaAtual() + buff.getMagiaDano());

			return format("{0} buffou o lacaio (id: {1}) com a carta {2}", atacante.getNome(), lacaio.getID(), buff.getNome());
		}
	}

	private static String format(String message, Object... arguments) {
		return MessageFormat.format(message, arguments);
	}

	private static <T extends Carta> String ids(Collection<T> cartas) {
		return cartas.stream().map(Carta::getID).collect(Collectors.toList()).toString();
	}
}
