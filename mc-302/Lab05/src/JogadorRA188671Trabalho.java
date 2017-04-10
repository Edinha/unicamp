import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.List;
import java.util.stream.Collectors;
import java.util.stream.Stream;

public class JogadorRA188671Trabalho extends Jogador {
	private List<CartaLacaio> lacaios;
	private List<CartaLacaio> lacaiosOponente;

	private int manaTurno;

	/**
	 * O método construtor do JogadorRA188671Trabalho.
	 *
	 * @param maoInicial Contém a mão inicial do jogador. Deve conter o número de cartas correto
	 *        dependendo se esta classe Jogador que está sendo construída é o primeiro ou o segundo
	 *        jogador da partida.
	 * @param primeiro Informa se esta classe Jogador que está sendo construída é o primeiro jogador
	 *        a iniciar nesta jogada (true) ou se é o segundo jogador (false).
	 */
	public JogadorRA188671Trabalho(ArrayList<Carta> maoInicial, boolean primeiro) {
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
		int minhaMana, vidaOponente;

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

		this.setManaTurno(minhaMana);
		ArrayList<Jogada> minhasJogadas = new ArrayList<>();

		// Usar poder heroico para destruir heroi inimigo
		if (vidaOponente == 1 && this.manaTurno >= 2) {
			minhasJogadas.add(new Jogada(TipoJogada.PODER, null, null));
			return minhasJogadas;
		}

		int lacaioSum = this.lacaios.stream().mapToInt(CartaLacaio::getAtaque).sum();

		// Caso todos os lacaios tenham dano para derrotar o heroi
		Stream<Jogada> ataqueDireto = this.lacaios.stream().map(lacaio -> new Jogada(TipoJogada.ATAQUE, lacaio, null));
		if (lacaioSum >= vidaOponente) {
			minhasJogadas.addAll(ataqueDireto.collect(Collectors.toList()));
			return minhasJogadas;
		}

		// Caso todos os lacaios mais o poder heroico consigam ganhar o jogo nessa rodada
		if (lacaioSum + 1 >= vidaOponente && this.manaTurno >= 2) {
			minhasJogadas.add(new Jogada(TipoJogada.PODER, null, null));
			minhasJogadas.addAll(ataqueDireto.collect(Collectors.toList()));
			return minhasJogadas;
		}

		// Decide a estrategia depois de verificar se nao tem caso de vitoria certa com a mesa atual
//		minhasJogadas.addAll(agressivo());
		minhasJogadas.addAll(controle());

		return minhasJogadas;
	}

	// Método que realiza a estratégia agressiva
	private List<Jogada> agressivo() {
		List<Carta> retiradas = new ArrayList<>();
		List<Jogada> minhasJogadas = new ArrayList<>();
		List<CartaMagia> magias = new ArrayList<>();
		List<CartaLacaio> invocarLacaios = new ArrayList<>();

		// Para as cartas da mão, mapeia quais são lacaios e quais são magias de dano
		for (Carta carta : this.mao) {
			if (carta instanceof CartaLacaio) {
				invocarLacaios.add((CartaLacaio) carta);
			}

			if (carta instanceof CartaMagia) {
				CartaMagia magia = (CartaMagia) carta;
				if (magiaDano(magia)) {
					magias.add(magia);
				}

				// TODO maybe buffs ?
			}
		}

		// Ordena os lacaios pelo ataque, dos de maior ataque para os de menor.
		Collections.sort(invocarLacaios, (o1, o2) -> {
			if (o1.getAtaque() > o2.getAtaque()) {
				return -1;
			}

			return 1;
		});

		// Ordena as magias pelo dano, das de maior dano para os de menor.
		Collections.sort(magias, (o1, o2) -> {
			if (o1.getMagiaDano() > o2.getMagiaDano()) {
				return -1;
			}

			return 1;
		});

		// Invoca quantos lacaios a mana atual permirir
		for (CartaLacaio lacaio : invocarLacaios) {
			if (!temManaSuficiente(lacaio)) {
				continue;
			}

			minhasJogadas.add(new Jogada(TipoJogada.LACAIO, lacaio, null));
			atualizarMana(lacaio);
			retiradas.add(lacaio);
		}

		// Usa quantas magias a mana restante permirir
		for (CartaMagia magia : magias) {
			if (!temManaSuficiente(magia)) {
				continue;
			}

			minhasJogadas.add(new Jogada(TipoJogada.MAGIA, magia, null));
			atualizarMana(magia);
			retiradas.add(magia);
		}

		// Todos os lacaios atacam diretamente o herói inimigo
		minhasJogadas.addAll(this.lacaios.stream().map(lacaio -> new Jogada(TipoJogada.ATAQUE, lacaio, null)).collect(Collectors.toList()));

		descarte(retiradas);

		return minhasJogadas;
	}

  // Método que realiza a estratégia de controle
	private List<Jogada> controle() {
		List<Jogada> minhasJogadas = new ArrayList<>();

		List<CartaLacaio> alvos = new ArrayList<>();

		List<CartaLacaio> invocarLacaios = new ArrayList<>();

		List<Carta> retiradas = new ArrayList<>();

		// Usar magias de controle
		for (Carta carta : this.mao) {
			if (carta instanceof CartaLacaio) {
				invocarLacaios.add((CartaLacaio) carta);
			}

			if (carta instanceof CartaMagia && temManaSuficiente(carta)) {
				CartaMagia magia = (CartaMagia) carta;

				// Usa magias em área caso o oponente tenha mais de uma lacaio em campo
				if (magia.getMagiaTipo().equals(TipoMagia.AREA) && this.lacaiosOponente.size() > 1) {
					minhasJogadas.add(new Jogada(TipoJogada.MAGIA, magia, null));
					atualizarMana(magia);
					retiradas.add(carta);
				}

				// Usa magias de alvo caso não haja desperdício de mana e consiga destruir o lacaio inimigo
				if (magia.getMagiaTipo().equals(TipoMagia.ALVO)) {
					for (CartaLacaio oponente : this.lacaiosOponente) {
						// TODO calc diference to no waste ?
						if (magia.getMagiaDano() >= oponente.getVidaAtual()) {
							minhasJogadas.add(new Jogada(TipoJogada.MAGIA, magia, oponente));
							atualizarMana(magia);
							retiradas.add(carta);
							break;
						}
					}
				}
			}
		}

		// Passa pelos lacais e decide as jogadas por trocas favoráveis
		this.lacaios.forEach(lacaio -> {
			CartaLacaio alvo = null;
			for (CartaLacaio oponente : this.lacaiosOponente) {
				if (alvos.indexOf(oponente) > -1 && trocaFavorel(lacaio, oponente)) {
					alvo = oponente;
					break;
				}
			}

			minhasJogadas.add(new Jogada(TipoJogada.ATAQUE, lacaio, alvo));
			if (alvo != null) {
				alvos.add(alvo);
			}
		});

		// Invoca quantos lacaios a mana restante permitir
		for (CartaLacaio invocao : invocarLacaios) {
			if (temManaSuficiente(invocao)) {
				retiradas.add(invocao);
				atualizarMana(invocao);
				minhasJogadas.add(new Jogada(TipoJogada.LACAIO, invocao, null));
			}
		}

		descarte(retiradas);

		return minhasJogadas;
	}

	/**
	 * Método que verifica se existe troca favorável entre um lacaio atacante e um defensor
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
	 * Método que verifica se existe mana suficiente para baixar a carta
	 * @param carta que se deseja usar no turno
	 * @return verdadeiro se é possível baixar a carta, falso caso contrário
	 */
	private boolean temManaSuficiente(Carta carta) {
		return (carta.getMana() <= this.manaTurno);
	}

	/**
	 * Verifica o tipo "Dano" para a carta magia parametrizada
	 * @param magia que se deseja usar no turno
	 * @return Verdadeiro caso tipo magia seja ALVO ou AREA, falso caso contrário
	 */
	private boolean magiaDano(CartaMagia magia) {
		return (magia.getMagiaTipo().equals(TipoMagia.ALVO) || magia.getMagiaTipo().equals(TipoMagia.AREA));
	}

	/**
	 * Remove uma carta da mão caso ela não for nula
	 * @param remover carta a ser retirada da mão
	 */
	private void descarte(Carta descarte) {
		if (descarte != null) {
			this.mao.remove(descarte);
		}
	}

	/**
	 * Remove uma coleção de cartas da mão
	 * @param cartas a serem retiradas da mão
	 */
	private void descarte(Collection<Carta> cartas) {
		cartas.forEach(this::descarte);
	}

	/**
	 * Atualiza a mana do turno do jogador ao criar uma jogada com respectiva carta
	 * @param carta usada na jogada
	 */
	private void atualizarMana(Carta carta) {
		this.manaTurno -= manaTurno;
	}

	public void setManaTurno(int manaTurno) {
		this.manaTurno = manaTurno;
	}

	public int getManaTurno() {
		return manaTurno;
	}

}
