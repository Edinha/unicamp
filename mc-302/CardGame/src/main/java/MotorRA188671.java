import java.io.PrintWriter;
import java.text.MessageFormat;
import java.util.ArrayList;
import java.util.Collection;
import java.util.EnumMap;
import java.util.EnumSet;
import java.util.HashMap;
import java.util.HashSet;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.Set;
import java.util.stream.Collectors;

/**
 * Trabalho 2
 *
 * RA : 188671 Nome: William Gonçalves da Cruz
 *
 */

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

		FUNCIONALIDADES.addAll(this.funcionalidadesAtivas);
	}

	private static final Set<Funcionalidade> FUNCIONALIDADES = new HashSet<>();

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

		MAGIA_JOGADA_MAPA.put(TipoMagia.BUFF, new BuffJogada());
		MAGIA_JOGADA_MAPA.put(TipoMagia.ALVO, new MagiaAlvoJogada());
		MAGIA_JOGADA_MAPA.put(TipoMagia.AREA, new MagiaAreaJogada());
	}

	@Override
	public int executarPartida() throws LamaException {
		vidaHeroi1 = vidaHeroi2 = 30;
		manaJogador1 = manaJogador2 = 1;
		movimentos = new ArrayList<>();

		Integer turno = 1;

		JogadorInfo primeiroJogador = new JogadorInfo(1, vidaHeroi1, maoJogador1, baralho1, lacaiosMesa1, manaJogador1, jogador1);
		JogadorInfo segundoJogador = new JogadorInfo(2, vidaHeroi2, maoJogador2, baralho2, lacaiosMesa2, manaJogador2, jogador2);

		for (int k = 0; k < 60; k++) {
			imprimir("\n=== TURNO " + turno + " ===\n");

			primeiroJogador.atualizarMana(turno > 10 ? 10 : turno);
			segundoJogador.atualizarMana(turno > 10 ? 10 : (turno == 1 ? 2 : turno));

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

			detalhesJogadores();

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

			// Atualiza as variáveis para o turno do jogador 2
			atacante = segundoJogador;
			defensor = primeiroJogador;

			for (Jogada jogada : movimentos) {
				this.processarJogada(jogada);
			}

			detalhesJogadores();

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
	 * Imprime os detalhes de vida dos jogadores após um turno de jogadas completo
	 */
	private void detalhesJogadores() {
		imprimir(format("Vida {0}: {1} \nVida {2}: {3}", atacante.getNome(), atacante.vida, defensor.getNome(), defensor.vida));
	}

	/**
	 * Realiza uma entrada de turno para o jogador parametrizado
	 * 
	 * @param jogadorInfo quem realiza a jogada do turno
	 * @return verdadeiro se o jogador perdeu em seu próprio turno de ataque e falso caso contrário
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
	 * 
	 * @return O número contrário ao jogador que sofreu fatalidade no turno, 0 caso nenhum tenha
	 *         sofrido fatalidade
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

	/**
	 * Calcula o tempo de uma jogada para o jogador parametrizado
	 * 
	 * @param jogador atacante nessa jogada
	 * @return Tempo utilizado para realizar o método "processar turno"
	 */
	private long calcularTempoJogada(JogadorInfo jogador) {
		long startTime;
		startTime = System.nanoTime();

		ArrayList<Jogada> cloneMovimentos = (ArrayList<Jogada>) UnoptimizedDeepCopy.copy(movimentos);
		movimentos = jogador.referencia.processarTurno(mesa, sacarCarta(jogador), cloneMovimentos);

		return System.nanoTime() - startTime;
	}

	/**
	 * Adiciona uma carta do baralho do jogador a sua mão
	 * 
	 * @param jogador que irá sacar a carta
	 * @return Carta retirada do baralho e colocada na mão, nulo caso o baralho esteja vazio
	 */
	private Carta sacarCarta(JogadorInfo jogador) {
		if (jogador.baralho.getCartas().isEmpty()) {
			jogador.fadiga();
			return null;
		}

		Carta carta = jogador.baralho.comprarCarta();
		jogador.mao.add(carta);
		return (Carta) UnoptimizedDeepCopy.copy(carta);
	}

	/**
	 * Verifica se o tempo permitido para se realizar uma jogada foi excedido
	 * 
	 * @param tempoTotal o tempo total gasto em uma jogada
	 * @return Verdeiro se esse tempo excedeu o máximo permitido, falso caso contrário
	 */
	private boolean estourouTempoPermitido(long tempoTotal) {
		return tempoLimitado != 0 && tempoTotal > 3e8;
	}

	/**
	 * Processa uma jogada parametrizada, aplicando seus efeitos ao jogo
	 * 
	 * @param umaJogada contendo as informações de mudança
	 * @throws LamaException caso seja uma jogada inválida
	 */
	protected void processarJogada(Jogada umaJogada) throws LamaException {
		String mensagem = JOGADA_MAPA.get(umaJogada.getTipo()).processar(umaJogada, atacante, defensor);
		atacante.removerLacaiosDestruidos();
		defensor.removerLacaiosDestruidos();
		imprimir(mensagem);
	}

	/**
	 * Essa classe encapsula as informações de um jogador, mantendo seu estado atualizado com o
	 * decorrer do jogo Ela é usada para validações, e para extrair informações importantes sobre a
	 * mão, baralho, lacaios mesa e o andamento do turno de um jogador
	 */
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

		private Set<Integer> cartasBaixadasTurno = new HashSet<>();
		private Map<Integer, Integer> contagemAtaqueLacaios = new HashMap<>();

		private boolean poderHeroicoUtilizado;

		JogadorInfo(Integer jogador, Integer vida, List<Carta> mao, Baralho baralho, List<Carta> lacaiosMesa, Integer mana,
				Jogador referencia) {
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

		/**
		 * Inicializa os atributos do jogador para um novo turno
		 */
		void comecarTurno() {
			this.poderHeroicoUtilizado = false;
			this.cartasBaixadasTurno.clear();
			this.contagemAtaqueLacaios.clear();
		}

		/**
		 * Aplica o dano de fadiga
		 */
		void fadiga() {
			this.vida -= this.danoFadiga++;
			imprimir("Fadiga: O " + getNome() + " recebeu dano por falta de cartas. (Vida atual: " + this.vida + ")");
		}

		/**
		 * Baixa uma carta da mão do jogador
		 * 
		 * @param carta a ser baixada para a mesa
		 */
		void baixarCarta(Carta carta) {
			this.mana -= carta.getMana();
			this.mao.remove(carta);

			CartaLacaio lacaio = (CartaLacaio) carta;
			this.lacaiosMesa.add(lacaio);

			if (temInvestida() && TipoEfeito.INVESTIDA.equals(lacaio.getEfeito())) {
				return;
			}

			this.cartasBaixadasTurno.add(carta.getID());
		}

		/**
		 * Retorna verdadeiro caso o jogador possua mana suficiente para utilizar poder heróico
		 */
		boolean temManaSuficientePoderHeroico() {
			return (this.mana >= 2);
		}

		/**
		 * Retorna verdadeiro caso o jogador possua mana suficiente para utilizar a carta
		 * parametrizada
		 * 
		 * @param carta a ser avaliada
		 */
		boolean temManaSuficiente(Carta carta) {
			return (this.mana >= carta.getMana());
		}

		boolean sofreuFatalidade() {
			return (vida <= 0);
		}

		String getNome() {
			return "Jogador " + numeroJogador;
		}

		void atualizarMana(Integer mana) {
			this.mana = mana;
		}

		void ataqueDireto(CartaLacaio cartaAlvo) {
			this.vida -= cartaAlvo.getAtaque();
		}

		void sofrerDanoPoderHeroico() {
			this.vida--;
		}

		/**
		 * Remove da mesa os lacaios destruídos do jogador nessa jogada
		 */
		void removerLacaiosDestruidos() {
			List<CartaLacaio> destruidos = lacaiosMesa.stream().filter(l -> l.getVidaAtual() <= 0).collect(Collectors.toList());
			destruidos.forEach(l -> imprimir(format("O lacaio {0} de {1} foi destruído nessa jogada", l.getNome(), getNome())));
			this.lacaiosMesa.removeAll(destruidos);
		}

		void usarPoderHeroico() {
			this.poderHeroicoUtilizado = true;
		}

		void sofrerDanoLacaio(CartaLacaio lacaio) {
			this.vida -= lacaio.getAtaque();
		}

		void sofrerDanoMagia(CartaMagia magia) {
			this.vida -= magia.getMagiaDano();
		}

		boolean possuiNumeroMaximoLacaios() {
			return lacaiosMesa.size() >= 7;
		}
	}

	/**
	 * Esta interface é utlizada para se manter a generalidade com relação ao processamento de uma
	 * jogada. As jogadas de ataque, baixar lacaio, magia, entre outras, cada uma possuirá sua
	 * implementação de "processar" com uma jogada, um atacante e um defensor.
	 *
	 * Todas essas implementações devem retornar uma mensagem de andamento daquele processamento, e
	 * podem lançar exceção em caso de jogada inválida.
	 *
	 * Como todos os processamentos possuem validações e tratamentos iguais uma vez que a jogada é
	 * processada, surgiu a motivação de ter uma interface para o processamento.
	 */
	private interface Processavel {
		String processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException;

		/**
		 * Recupera da mão do atacante a carta jogada, validando suas informações no caminho
		 * @param jogada objeto contendo ações a serem realizadas
		 * @param atacante Jogador
		 * @param defensor Jogador
		 * @return A carta jogada da mão do jogador
		 * @throws LamaException Em caso da carta não existir na mão do jogador ou não possuir mana suficiente para usá-la
		 */
		default Carta recuperarCartaJogada(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException {
			final Carta cartaJogada = jogada.getCartaJogada();
			final Optional<Carta> cartaOptional = atacante.mao.stream().filter(carta -> carta.equals(cartaJogada)).findFirst();
			if (!cartaOptional.isPresent()) {
				String mensagemErro = format(
					"Tentativa de usar carta (id: {0}), porém essa carta não existe na mão do jogador. IDS Cartas da mão: {1}",
					cartaJogada.getID() + "",
					ids(atacante.mao));

				throw new LamaException(1, jogada, mensagemErro, defensor.numeroJogador);
			}

			final Carta carta = cartaOptional.get();
			if (!atacante.temManaSuficiente(carta)) {
				String mensagem = format("Mana insuficiente para jogada de {0} (mana necessária: 2, mana atual: {1})",
					jogada.getTipo().name(),
					atacante.mana.toString());
				throw new LamaException(2, jogada, mensagem, defensor.numeroJogador);
			}

			return carta;
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
				String mensagemErro = format(
					"Tentativa de atacar com lacaio (id: {0}), porém essa carta não está no campo do jogador. IDS Cartas da mesa: {1}",
					id.toString(),
					ids(atacante.lacaiosMesa));

				throw new LamaException(5, jogada, mensagemErro, defensor.numeroJogador);
			}

			if (atacante.cartasBaixadasTurno.contains(id)) {
				String mensagemErro = format("Tentativa de atacar com lacaio (id: {0}) que foi baixado no mesmo turno", id.toString());
				throw new LamaException(6, jogada, mensagemErro, defensor.numeroJogador);
			}

			final CartaLacaio lacaioAtacante = atacanteOptional.get();

			Integer maximoAtaquesTurno = getMaximoAtaquesTurno(lacaioAtacante);
			Integer contagem = atacante.contagemAtaqueLacaios.getOrDefault(id, 0);

			if (contagem >= maximoAtaquesTurno) {
				String mensagemErro = format("Número máximo de ataque excedido para o lacaio (id: {0})", id.toString());
				throw new LamaException(7, jogada, mensagemErro, defensor.numeroJogador);
			}

			atacante.contagemAtaqueLacaios.put(id, contagem + 1);

			final List<Integer> provocativos = defensor.lacaiosMesa.stream()
					.filter(l -> TipoEfeito.PROVOCAR.equals(l.getEfeito()))
					.map(Carta::getID)
					.collect(Collectors.toList());

			if (cartaAlvo == null) {
				if (temProvocar() && !provocativos.isEmpty()) {
					String mensagemErro = format("Ataque direto a herói inimigo quando existe lacaio com provocar no campo. Lacaios com provocar: {0}", provocativos);
					throw new LamaException(13, jogada, mensagemErro, defensor.numeroJogador);
				}

				defensor.ataqueDireto(lacaioAtacante);
				return format("{0} atacou diretamente o herói inimigo com lacaio {1}", atacante.getNome(), lacaioAtacante.getNome());
			}

			if (!defensorOptional.isPresent()) {
				String mensagemErro = format(
					"Tentativa de atacar com lacaio (id: {0}), porém a carta alvo não está no campo do jogador inimigo (alvo_id: {1})",
					id.toString(),
					cartaAlvo.getID() + "");

				throw new LamaException(8, jogada, mensagemErro, defensor.numeroJogador);
			}

			final CartaLacaio lacaioDefensor = defensorOptional.get();
			if (temProvocar() && !provocativos.isEmpty() && !provocativos.contains(lacaioDefensor.getID())) {
				String mensagemErro = format(
						"Ataque a um lacaio quando existe um outro com provocar no campo. Alvo {0}, Lacaios com provocar: {1}",
						lacaioDefensor.getID() + "",
						provocativos);

				throw new LamaException(13, jogada, mensagemErro, defensor.numeroJogador);
			}

			lacaioAtacante.setVidaAtual(lacaioAtacante.getVidaAtual() - lacaioDefensor.getVidaAtual());
			lacaioDefensor.setVidaAtual(lacaioDefensor.getVidaAtual() - lacaioAtacante.getVidaAtual());

			return format("{0} atacou lacaio inimigo {1} com seu lacaio {2}",
				atacante.getNome(),
				lacaioAtacante.getNome(),
				lacaioDefensor.getNome());
		}
	}

	private static class LacaioJogada implements Processavel {
		@Override
		public String processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException {

			final Carta lacaioBaixado = recuperarCartaJogada(jogada, atacante, defensor);
			if (atacante.possuiNumeroMaximoLacaios()) {
				String mensagemErro = format(
					"Tentativa de usar carta (id: {0}, nome: {1}), porém número máximo de lacaios seria ultrapassado.",
					lacaioBaixado.getID() + "",
					lacaioBaixado.getNome());

				throw new LamaException(4, jogada, mensagemErro, defensor.numeroJogador);
			}

			atacante.baixarCarta(lacaioBaixado);
			return format("{0} baixou a carta {1} com custo de mana de {2}",
				atacante.getNome(),
				lacaioBaixado.getNome(),
				lacaioBaixado.getMana() + "");
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
				String mensagem = format("Tentativa de usar poder heróico em alvo inexistente (alvo_id: {0})", cartaAlvo.getID() + "");
				throw new LamaException(12, jogada, mensagem, defensor.numeroJogador);
			}

			final CartaLacaio lacaio = alvo.get();
			defensor.sofrerDanoLacaio(lacaio);
			lacaio.setVidaAtual(lacaio.getVidaAtual() - 1);

			return format("{0} usou poder heróico no lacaio inimigo {1}, recebendo {2} de dano",
				atacante.getNome(),
				lacaio.getNome(),
				lacaio.getAtaque() + "");
		}
	}

	private static class MagiaJogada implements Processavel {
		@Override
		public String processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException {
			final Carta carta = recuperarCartaJogada(jogada, atacante, defensor);
			if (carta instanceof CartaLacaio) {
				String mensagem = format("Tentativa de utilizar a carta lacaio {0} (id: {1}) como uma magia",
					carta.getNome(),
					carta.getID());
				throw new LamaException(9, jogada, mensagem, defensor.numeroJogador);
			}

			final CartaMagia magia = (CartaMagia) carta;
			return MAGIA_JOGADA_MAPA.get(magia.getMagiaTipo()).processar(jogada, atacante, defensor);
		}
	}

	private static class BuffJogada implements Processavel {
		@Override
		public String processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException {
			final Carta alvo = jogada.getCartaAlvo();
			final CartaMagia buff = (CartaMagia) recuperarCartaJogada(jogada, atacante, defensor);

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

	private static class MagiaAlvoJogada implements Processavel {
		@Override
		public String processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException {
			final Carta alvo = jogada.getCartaAlvo();
			final CartaMagia magia = (CartaMagia) recuperarCartaJogada(jogada, atacante, defensor);

			Optional<CartaLacaio> alvoOptional = defensor.lacaiosMesa.stream().filter(l -> l.equals(alvo)).findFirst();
			if (!alvoOptional.isPresent()) {
				defensor.sofrerDanoMagia(magia);
				return format("{0} atacou o herói inimigo com a carta {1}", atacante.getNome(), magia.getNome());
			}

			final CartaLacaio lacaio = alvoOptional.get();
			lacaio.setVidaAtual(lacaio.getVidaAtual() - magia.getMagiaDano());

			return format("{0} atacou o lacaio (id: {1}) com a carta {2}", atacante.getNome(), lacaio.getID(), magia.getNome());
		}
	}

	private static class MagiaAreaJogada implements Processavel {
		@Override
		public String processar(Jogada jogada, JogadorInfo atacante, JogadorInfo defensor) throws LamaException {
			final CartaMagia magia = (CartaMagia) recuperarCartaJogada(jogada, atacante, defensor);

			defensor.lacaiosMesa.forEach(lacaio -> lacaio.setVidaAtual(lacaio.getVidaAtual() - magia.getMagiaDano()));

			return format("{0} usou a magia em área {1}", atacante.getNome(), magia.getNome());
		}
	}

	// Avalia se a funcionalidade Investida está ativa para o jogo
	private static boolean temInvestida() {
		return FUNCIONALIDADES.contains(Funcionalidade.INVESTIDA);
	}

	// Avalia se a funcionalidade Provocar está ativa para o jogo
	private static boolean temProvocar() {
		return FUNCIONALIDADES.contains(Funcionalidade.PROVOCAR);
	}

	/**
	 * Avalia o número máximo de ataques que um lacaio pode realizar em um turno, dado o estado do
	 * motor
	 * 
	 * @param lacaio que deseja realizar um ataque
	 * @return O número de ataque, dado o tipo de efeito do lacaio (ataque duplo) e se a
	 *         funcionalidade está ativa para a partida
	 */
	private static Integer getMaximoAtaquesTurno(CartaLacaio lacaio) {
		if (!FUNCIONALIDADES.contains(Funcionalidade.ATAQUE_DUPLO)) {
			return 1;
		}

		return TipoEfeito.ATAQUE_DUPLO.equals(lacaio.getEfeito()) ? 2 : 1;
	}

	/**
	 * Formata a String com os argumentos parametrizados
	 * 
	 * @param message uma string com interpolação
	 * @param arguments parâmetros a serem evaludados na String
	 * @return Uma mensagem com os valores evaluados
	 */
	private static String format(String message, Object... arguments) {
		return MessageFormat.format(message, arguments);
	}

	/**
	 * Extrai os ids de uma coleção cartas para impressão
	 * 
	 * @param cartas a serem avaliadas
	 * @param <T> Tipo de Carta
	 * @return Uma String com os ids das cartas separados por ','
	 */
	private static <T extends Carta> String ids(Collection<T> cartas) {
		return cartas.stream().map(Carta::getID).collect(Collectors.toList()).toString();
	}
}
