import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.stream.Collectors;

/**
 * Willam Gonçalves da Cruz - RA 188671
 * Jogador de LaMa, descrevendo estratégias
 *
 * Jogada Base:
 *      Essa jogada é comum para as três estratégias implementadas nesse jogador.
 * Nela, são verificadas as possibilidades de acabar com o jogo nessa rodada que está iniciando.
 * Dentre as verificacoes, estão:
 *      - É possivel destruir o herói apenas com o poder heroico
 *      - Destruir o herói atacando com todos os lacaios em campo diretamente
 *      - Destruir o herói atacando com todos os lacaios mais o poder heroico
 *
 * Depois da verificação básica, caso ela falhe em acabar com o jogo nessa rodada, é executado o retorno das estratégias.
 *
 * No meu caso, apenas a estratégia controle é utilizada efetivamente.
 *
 * Acabada a estratégia, tenta utilizar o poder heroico no herói inimigo, caso haja mana.
 *
 * Descrição estratégias...
 *
 * Agressivo:
 *      O jogador agressivo primeiramente separa as cartas da mão entre magias e lacaios.
 * Para os lacaios, estes são ordenados por mana decrescente (do maior custo de mana para o menor).
 * Assim, tenta invocar o maior número de lacaios fortes possível para aquela rodada.
 *
 * Já para as magia de alvo, as ordena em ordem decrescente de dano magia, e novamente tenta utilizar todas as que forem possiveis.
 *
 * Caso haja magia de área, tenta usá-la se houver mana e mais de dois lacaios no campo do oponente.
 * Caso haja algum buff, tenta utilizá-lo no lacaio de maior ataque caso ainda haja mana.
 * Após tudo isso, mira todos os meus lacaios em campo para atacar o herói inimigo diretamente.
 *
 *
 * Controle:
 *      Primeiramente, essa estratégia ordena as cartas as da mão decrescentemente de acordo com a mana. A partir disso, segue
 * segue para a seção onde decide que magia utilizar para controlar o campo. Para a magia de alvo, decide se pode acabar o
 * jogo com ela ou destruir um "bom alvo" lacaio inimigo com ela. Para magias de área, são utilizadas quando 2+ lacaios
 * do oponente podem ser destruidos e magia de buff são utilizadas no meu lacaio de maior ataque.
 *
 * Depois das magia, vem parte de controlar o campo com trocas favoráveis de lacaios. Para todos meus lacaios em campo eh definido
 * um alvo, seja este um lacaio inimigo ou o herói, de acordo com as regras descritas. Emfim, são invocados mais lacaios ao
 * campo com a mana restante do turno.
 *
 *
 * Curva de Mana:
 *      Primeiramente, essa estratégia ordena as cartas as da mão decrescentemente de acordo com a mana. A partir disso,
 * tenta usar o máximo de mana possivel com em uma repetição. Para cartas de magia, passa por algumas validações antes
 * de usar uma carta: Verifica se o custo de mana do(s) lacaio(s) destruido(s) pela magia é maior do que o próprio custo
 * da magia. Para o caso de magias de alvo, verifica se o alvo é um "bom alvo" para lancar a magia também. Para cartas
 * de lacaio, apenas as baixa ao campo na ordem de maior mana.
 *
 * Fora isso, utiliza buffs e ataca diretamente o herói inimigo, igualmente a estratégia agressiva.
 *
 */

public class JogadorRA188671 extends Jogador {
	private List<CartaLacaio> lacaios;
	private List<CartaLacaio> lacaiosOponente;

	private int manaTurno;
	private int contagemLacaios;

	private int vidaOponente;

	private List<Carta> retiradas;

	/**
	 * O método construtor do JogadorRA188671.
	 *
	 * @param maoInicial Contém a mão inicial do jogador. Deve conter o número de cartas correto
	 *        dependendo se esta classe Jogador que está sendo construída é o primeiro ou o segundo
	 *        jogador da partida.
	 * @param primeiro Informa se esta classe Jogador que está sendo construída é o primeiro jogador
	 *        a iniciar nesta jogada (true) ou se é o segundo jogador (false).
	 */
	public JogadorRA188671(ArrayList<Carta> maoInicial, boolean primeiro) {
		primeiroJogador = primeiro;

		mao = maoInicial;
		lacaios = new ArrayList<>();
		lacaiosOponente = new ArrayList<>();
	}

	/**
	 * Um método que processa o turno de cada jogador. Este método deve retornar as jogadas do
	 * Jogador decididas para o turno atual (ArrayList de Jogada).
	 *
	 * @param mesa O "estado do jogo" imediatamente antes do início do turno corrente. Este objeto
	 *        de mesa contém todas as informações 'públicas' do jogo (lacaios vivos e suas vidas,
	 *        vida dos heróis, etc).
	 * @param cartaComprada A carta que o Jogador recebeu neste turno (comprada do Baralho). Obs:
	 *        pode ser null se o Baralho estiver vazio ou o Jogador possuir mais de 10 cartas na
	 *        mão.
	 * @param jogadasOponente Um ArrayList de Jogada que foram os movimentos utilizados pelo
	 *        oponente no último turno, em ordem.
	 * @return um ArrayList com as Jogadas decididas
	 */
	public ArrayList<Jogada> processarTurno(Mesa mesa, Carta cartaComprada, ArrayList<Jogada> jogadasOponente) {
		int minhaMana;
		if (cartaComprada != null) {
			mao.add(cartaComprada);
		}

		if (primeiroJogador) {
			minhaMana = mesa.getManaJog1();
			lacaios = mesa.getLacaiosJog1();

			vidaOponente = mesa.getVidaHeroi2();
			lacaiosOponente = mesa.getLacaiosJog2();
		} else {
			minhaMana = mesa.getManaJog2();
			lacaios = mesa.getLacaiosJog2();

			vidaOponente = mesa.getVidaHeroi1();
			lacaiosOponente = mesa.getLacaiosJog1();
		}

		this.setContagemLacaios(this.lacaios.size());
		this.setManaTurno(minhaMana);
		this.retiradas = new ArrayList<>();

		ArrayList<Jogada> minhasJogadas = new ArrayList<>();

		// Usar poder heroico para destruir herói inimigo
		if (vidaOponente == 1) {
			Optional<Jogada> jogada = poderHeroico();
			if (jogada.isPresent()) {
				minhasJogadas.add(jogada.get());
				return minhasJogadas;
			}
		}

		int lacaioSum = this.lacaios.stream().mapToInt(CartaLacaio::getAtaque).sum();

		// Caso todos os lacaios tenham dano para derrotar o heroi
		if (lacaioSum >= vidaOponente) {
			minhasJogadas.addAll(ataqueDiretoHeroi());
			return minhasJogadas;
		}

		// Caso todos os lacaios mais o poder heroico consigam ganhar o jogo nessa rodada
		if (lacaioSum + 1 >= vidaOponente && this.manaTurno >= 2) {
			minhasJogadas.add(new Jogada(TipoJogada.PODER, null, null));
			minhasJogadas.addAll(ataqueDiretoHeroi());
			return minhasJogadas;
		}

		// Decide a estratégia depois de verificar se não há caso de vitória certa com a mesa atual,
		// usando apenas controle no caso da entrega do trabalho
//		 minhasJogadas.addAll(agressivo());
//		 minhasJogadas.addAll(curvaMana());

		minhasJogadas.addAll(controle());

		// Utiliza o poder heroico ao final da jogada
		Optional<Jogada> poder = poderHeroico();
		if (poder.isPresent()) {
			minhasJogadas.add(poder.get());
		}

		descarte(this.retiradas);

		return minhasJogadas;
	}

	// Método que realiza a estratégia agressiva
	private List<Jogada> agressivo() {
		List<Jogada> minhasJogadas = new ArrayList<>();
		List<CartaMagia> magias = new ArrayList<>();
		List<CartaLacaio> invocarLacaios = new ArrayList<>();

		Map<CartaMagia, CartaLacaio> buffs = new HashMap<>();

		CartaMagia area = null;

		// Para as cartas da mão, mapeia quais são lacaios e quais são magias de dano
		for (Carta carta : this.mao) {
			if (carta instanceof CartaLacaio) {
				invocarLacaios.add((CartaLacaio) carta);
			}

			if (carta instanceof CartaMagia) {
				CartaMagia magia = (CartaMagia) carta;
				if (magiaAlvo(magia)) {
					magias.add(magia);
				}

				if (magiaArea(magia)) {
					area = magia;
				}

				// Marca um mapa de buff por lacaio a ser utilizado
				if (magiaBuff(magia)) {
					Optional<CartaLacaio> lacaio = this.mapearBuff(magia);
					if (lacaio.isPresent()) {
						buffs.put(magia, lacaio.get());
					}
				}
			}
		}

		// Ordena os lacaios pela mana, dos de maior mana para os de menor mana
		Collections.sort(invocarLacaios, (first, second) -> Integer.valueOf(second.getMana()).compareTo(first.getMana()));

		// Ordena as magias pelo dano, das de maior dano para os de menor.
		Collections.sort(magias, (first, second) -> Integer.valueOf(second.getMagiaDano()).compareTo(first.getMagiaDano()));

		// Invoca quantos lacaios a mana atual permitir
		for (CartaLacaio lacaio : invocarLacaios) {
			Optional<Jogada> jogada = invocar(lacaio);
			if (jogada.isPresent()) {
				minhasJogadas.add(jogada.get());
			}
		}

		// Usa a magia em área
		if (area != null && this.lacaiosOponente.size() > 1) {
			Optional<Jogada> jogada = baixarMagia(area, null);
			if (jogada.isPresent()) {
				minhasJogadas.add(jogada.get());
			}
		}

		// Usa quantas magias de alvo a mana restante permitir, mirando no herói inimigo
		for (CartaMagia magia : magias) {
			Optional<Jogada> jogada = baixarMagia(magia, null);
			if (jogada.isPresent()) {
				minhasJogadas.add(jogada.get());
			}
		}

		// Usa buffs nos lacaios marcados
		minhasJogadas.addAll(usarBuffs(buffs));

		// Todos os lacaios atacam diretamente o herói inimigo
		minhasJogadas.addAll(ataqueDiretoHeroi());

		return minhasJogadas;
	}

	// Método que realiza a estratégia de controle
	private List<Jogada> controle() {
		List<Jogada> jogadas = new ArrayList<>();

		List<CartaLacaio> invocarLacaios = new ArrayList<>();

		// Ordena lacaios inimigos do maior para o menor ataque
		Collections.sort(this.lacaiosOponente, (first, second) -> Integer.valueOf(second.getAtaque()).compareTo(first.getAtaque()));

		// Ordena a mao pelas cartas de maior mana
		Collections.sort(this.mao, (first, second) -> Integer.valueOf(second.getMana()).compareTo(first.getMana()));

		for (Carta carta : this.mao) {
			if (carta instanceof CartaLacaio) {
				invocarLacaios.add((CartaLacaio) carta);
			}

			if (carta instanceof CartaMagia) {
				CartaMagia magia = (CartaMagia) carta;
				List<CartaLacaio> destruidos = lacaiosOponente.stream()
						.filter(inimigo -> inimigo.getVidaAtual() <= magia.getMagiaDano())
						.collect(Collectors.toList());

				// Magia area, usada se houverem 2+ lacaios inimigos destruidos por ela
				if (magiaArea(magia)) {
					if (destruidos.size() > 1) {
						Optional<Jogada> jogada = baixarMagia(magia, null);
						if (jogada.isPresent()) {
							jogadas.add(jogada.get());
							this.lacaiosOponente.removeAll(destruidos);
						}
					}
				}

				// Magia alvo, decide a mira da jogada
				if (magiaAlvo(magia)) {
					Optional<Jogada> jogada = mirarMagiaAlvo(magia, destruidos);
					if (jogada.isPresent()) {
						jogadas.add(jogada.get());
					}
				}

				// Buffa meu lacaio de maior ataque e atualiza o objeto
				if (magiaBuff(magia)) {
					Optional<CartaLacaio> possivelBuffado = this.mapearBuff(magia);
					if (possivelBuffado.isPresent()) {
						CartaLacaio lacaio = possivelBuffado.get();
						Optional<Jogada> jogada = baixarMagia(magia, lacaio);
						if (jogada.isPresent()) {
							jogadas.add(jogada.get());
							lacaio.setAtaque(lacaio.getAtaque() + magia.getMagiaDano());
							lacaio.setVidaAtual(lacaio.getVidaAtual() + magia.getMagiaDano());
						}
					}
				}
			}
		}

		// Ordena meus lacaios do menor para o maior ataque
		Collections.sort(this.lacaios, (first, second) -> Integer.valueOf(first.getAtaque()).compareTo(second.getAtaque()));

		// Para todos os meus lacaios em campo, decide quem atacar
		for (CartaLacaio lacaio : this.lacaios) {

			// Filtra as trocas favoraveis do lacaio atual para com os inimigos
			List<CartaLacaio> alvos = lacaiosOponente.stream().filter(alvo -> trocaFavorel(lacaio, alvo)).collect(Collectors.toList());

			// Caso nao haja trocas favoraveis, ataca o heroi inimigo
			if (alvos.isEmpty()) {
				jogadas.add(new Jogada(TipoJogada.ATAQUE, lacaio, null));
				continue;
			}

			// Caso haja trocas favoraveis, pega o lacaio inimigo de maior mana para ser o alvo
			Collections.sort(alvos, (first, second) -> Integer.valueOf(second.getMana()).compareTo(first.getMana()));
			CartaLacaio alvo = alvos.iterator().next();
			this.lacaiosOponente.remove(alvo);

			jogadas.add(new Jogada(TipoJogada.ATAQUE, lacaio, alvo));
		}

		// Invoca os lacaios da mao com a mana restante
		for (CartaLacaio carta : invocarLacaios) {
			Optional<Jogada> jogada = invocar(carta);
			if (jogada.isPresent()) {
				jogadas.add(jogada.get());
			}
		}

		return jogadas;
	}

	// estratégia de curva de mana
	private List<Jogada> curvaMana() {
		List<Jogada> jogadas = new ArrayList<>();

		Map<CartaMagia, CartaLacaio> buffs = new HashMap<>();

		// Ordena as cartas da mao por maior custo de mana
		Collections.sort(this.mao, (first, second) -> Integer.valueOf(second.getMana()).compareTo(first.getMana()));

		for (Carta carta : this.mao) {
			if (!temManaSuficiente(carta)) {
				continue;
			}

			// Caso seja um lacaio, o invoca
			if (carta instanceof CartaLacaio) {
				Optional<Jogada> jogada = invocar((CartaLacaio) carta);
				if (jogada.isPresent()) {
					jogadas.add(jogada.get());
				}
			}

			if (carta instanceof CartaMagia) {
				CartaMagia magia = (CartaMagia) carta;

				// Magia de dano, acertar um alvo que possui mais mana que a carta e o elimina
				if (magiaAlvo(magia)) {
					CartaLacaio destruida = null;

					for (CartaLacaio inimigo : this.lacaiosOponente) {

						// Caso o lacaio inimigo seja um bom alvo e tenha maior custo de mana
						// que a magia, procede em usar a carta
						if (bomAlvo(magia, inimigo) && inimigo.getMana() > magia.getMana()) {
							Optional<Jogada> jogada = baixarMagia(magia, inimigo);
							if (jogada.isPresent()) {
								jogadas.add(jogada.get());
								destruida = inimigo;
								break;
							}
						}
					}

					if (destruida != null) {
						this.lacaiosOponente.remove(destruida);
					}
				}

				// Magia de area, troca custo de mana dos destruidos x custo de mana da magia
				if (magiaArea(magia)) {
					List<CartaLacaio> destruidos = this.lacaiosOponente.stream()
							.filter(inimigo -> magia.getMagiaDano() >= inimigo.getVidaAtual())
							.collect(Collectors.toList());

					// Caso o custo de mana dos destruidos seja maior, usar magia
					int custoDeManaDestruidos = destruidos.stream().mapToInt(Carta::getMana).sum();
					if (custoDeManaDestruidos > magia.getMana()) {
						Optional<Jogada> jogada = baixarMagia(magia, null);
						if (jogada.isPresent()) {
							jogadas.add(jogada.get());
							this.lacaiosOponente.removeAll(destruidos);
						}
					}
				}

				if (magiaBuff(magia)) {
					Optional<CartaLacaio> lacaio = this.mapearBuff(magia);
					if (lacaio.isPresent()) {
						buffs.put(magia, lacaio.get());
					}
				}
			}
		}

		jogadas.addAll(usarBuffs(buffs));
		jogadas.addAll(ataqueDiretoHeroi());

		return jogadas;
	}

	/**
	 * Método que verifica se existe troca favorável entre um lacaio atacante e um defensor
	 *
	 * @param atacante carta que realiza o ataque nesse turno
	 * @param defensor carta que recebe o ataque nesse turno
	 * @return Verdadeiro se existe troca favorável entre as duas cartas, falso caso contrário
	 */
	private boolean trocaFavorel(CartaLacaio atacante, CartaLacaio defensor) {
		// O atacante consegue destruir o defensor
		if (atacante.getAtaque() >= defensor.getVidaAtual()) {

			// Atacante sobrevive a troca, favorável
			if (atacante.getVidaAtual() > defensor.getAtaque()) {
				return true;
			}

			// Ataca e morre no processo, temos dois casos
			if (atacante.getVidaAtual() <= defensor.getAtaque()) {

				// Se tirou um inimigo com custo de mana maior, favorável
				if (atacante.getMana() < defensor.getMana()) {
					return true;
				}

				// Caso a vida do atacante esteja danificada e seja menor do que o defensor
				if (atacante.getVidaAtual() < defensor.getVidaAtual()) {
					return true;
				}
			}
		}

		// Se nenhum caso se aplica, troca desfavorável
		return false;
	}

	/**
	 * Realiza as jogadas de buffs da rodada
	 *
	 * @param buffs mapeamento entre magias de buff e lacaios onde utilizar
	 * @return lista de jogadas de buff
	 */
	private List<Jogada> usarBuffs(Map<CartaMagia, CartaLacaio> buffs) {
		List<Jogada> jogadas = new ArrayList<>();

		for (Map.Entry<CartaMagia, CartaLacaio> buff : buffs.entrySet()) {
			CartaMagia magia = buff.getKey();
			CartaLacaio lacaio = buff.getValue();

			Optional<Jogada> jogada = baixarMagia(magia, lacaio);
			if (jogada.isPresent()) {
				jogadas.add(jogada.get());
				lacaio.setAtaque(lacaio.getAtaque() + magia.getMagiaDano());
				lacaio.setVidaAtual(lacaio.getVidaAtual() + magia.getMagiaDano());
			}
		}

		return jogadas;
	}

	/**
	 * Busca o lacaio mais forte em campo para se buffar
	 *
	 * @param magia buff desejado usar
	 * @return lacaio a ser buffado, optional vazio caso nao exista nenhum
	 */
	private Optional<CartaLacaio> mapearBuff(CartaMagia magia) {
		if (!magiaBuff(magia) || this.lacaios.isEmpty()) {
			return Optional.empty();
		}

		this.lacaios.sort((first, second) -> Integer.valueOf(second.getAtaque()).compareTo(first.getAtaque()));
		return Optional.ofNullable(this.lacaios.iterator().next());
	}

	/**
	 * Retorna um opcional para a invocacao do lacaio parametrizado
	 *
	 * @param lacaio que se deseja invocar na mesa
	 * @return Opcional com uma jogada caso a invocacao seja sucedidade, opcional vazio caso
	 *         contrário
	 */
	private Optional<Jogada> invocar(CartaLacaio lacaio) {
		if (!temManaSuficiente(lacaio) || this.contagemLacaios >= 7) {
			return Optional.empty();
		}

		this.contagemLacaios++;
		this.atualizarMana(lacaio);
		this.retiradas.add(lacaio);

		return Optional.of(new Jogada(TipoJogada.LACAIO, lacaio, null));
	}

	/**
	 * Metodo que avalia onde mirar uma magia de alvo. Caso possa destruir o heroi inimigo,
	 * mira nele, senao, mira no primero lacaio inimigo (bom alvo) da lista parametrizada
	 * @param magia de alvo a ser utiizada
	 * @param destruidos lacaios destruidos pela magia
	 * @return Opcional com uma jogada caso tenha sido realizada, vazio caso contrário
	 */
	private Optional<Jogada> mirarMagiaAlvo(CartaMagia magia, List<CartaLacaio> destruidos) {
		if (vidaOponente <= magia.getMagiaDano()) {
			return baixarMagia(magia, null);
		}

		if (destruidos.isEmpty()) {
			return Optional.empty();
		}

		// Encontra um bom alvo na lista de destruidos pela magia
		Optional<CartaLacaio> possivelAlvo = destruidos.stream().filter(destruido -> bomAlvo(magia, destruido)).findFirst();

		Optional<Jogada> jogada = Optional.empty();

		if (possivelAlvo.isPresent()) {
			CartaLacaio alvo = possivelAlvo.get();
			jogada = baixarMagia(magia, alvo);
			if (jogada.isPresent()) {
				this.lacaiosOponente.remove(alvo);
			}
		}

		return jogada;
	}

	/**
	 * Baixa uma magia a mesa
	 *
	 * @param magia carta a ser jogada
	 * @param alvo quem recebe a magia
	 * @return Opcional com jogada caso seja possivel baixar a magia, vazio caso contrário
	 */
	private Optional<Jogada> baixarMagia(CartaMagia magia, Carta alvo) {
		if (!temManaSuficiente(magia)) {
			return Optional.empty();
		}

		this.atualizarMana(magia);
		this.retiradas.add(magia);

		return Optional.of(new Jogada(TipoJogada.MAGIA, magia, alvo));
	}

	/**
	 * Realiza a jogada de um poder heroico
	 *
	 * @return Opcional com jogada de poder caso tenha mana para jogar, vazio caso contrário
	 */
	private Optional<Jogada> poderHeroico() {
		if (this.manaTurno < 2) {
			return Optional.empty();
		}

		this.manaTurno -= 2;
		return Optional.of(new Jogada(TipoJogada.PODER, null, null));
	}

	/**
	 * Retorna colecao de jogadas com todos os lacaios atacando diretamente o herói inimigo
	 *
	 * @return ataques contra o heroi inimigo
	 */
	private List<Jogada> ataqueDiretoHeroi() {
		return this.lacaios.stream().map(lacaio -> new Jogada(TipoJogada.ATAQUE, lacaio, null)).collect(Collectors.toList());
	}

	/**
	 * Decide se o lacaio eh um bom alvo para a magia
	 *
	 * @param magia que se deseja utilizar
	 * @param alvo mirado
	 * @return Verdadeiro caso magia destrua o alvo e haja pouco desperdicio, falso caso contrário
	 */
	private boolean bomAlvo(CartaMagia magia, CartaLacaio alvo) {
		if (magia.getMagiaDano() < alvo.getVidaAtual()) {
			return false;
		}

		int diferencaDano = Math.abs(magia.getMagiaDano() - alvo.getVidaAtual());
		return (diferencaDano <= 2);
	}

	/**
	 * Método que verifica se existe mana suficiente para baixar a carta
	 *
	 * @param carta que se deseja usar no turno
	 * @return verdadeiro se é possível baixar a carta, falso caso contrário
	 */
	private boolean temManaSuficiente(Carta carta) {
		return (carta.getMana() <= this.manaTurno);
	}

	/**
	 * Verifica o tipo área para magia parametrizada
	 *
	 * @param magia carta
	 * @return Verdadeiro caso seja magia de area, falso caso contrário
	 */
	private boolean magiaArea(CartaMagia magia) {
		return TipoMagia.AREA.equals(magia.getMagiaTipo());
	}

	/**
	 * Verifica o tipo alvo para magia parametrizada
	 *
	 * @param magia carta
	 * @return Verdadeiro caso seja magia de alvo, falso caso contrário
	 */
	private boolean magiaAlvo(CartaMagia magia) {
		return TipoMagia.ALVO.equals(magia.getMagiaTipo());
	}

	/**
	 * Verifica o tipo buff para magia parametrizada
	 *
	 * @param magia carta
	 * @return Verdadeiro caso seja magia de buff, falso caso contrário
	 */
	private boolean magiaBuff(CartaMagia magia) {
		return TipoMagia.BUFF.equals(magia.getMagiaTipo());
	}

	/**
	 * Remove uma coleção de cartas da mão
	 *
	 * @param cartas a serem retiradas da mão
	 */
	private void descarte(Collection<Carta> cartas) {
		this.mao.removeAll(cartas);
	}

	/**
	 * Atualiza a mana do turno do jogador ao criar uma jogada com respectiva carta
	 *
	 * @param carta usada na jogada
	 */
	private void atualizarMana(Carta carta) {
		this.manaTurno -= carta.getMana();
	}

	private void setManaTurno(int manaTurno) {
		this.manaTurno = manaTurno;
	}

	private void setContagemLacaios(int contagemLacaios) {
		this.contagemLacaios = contagemLacaios;
	}
}
