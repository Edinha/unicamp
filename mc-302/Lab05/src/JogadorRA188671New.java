import java.util.ArrayList;
import java.util.Collection;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.stream.Collectors;

public class JogadorRA188671New extends Jogador {

	private List<CartaLacaio> lacaios;
	private List<CartaLacaio> lacaiosOponente;

	private int manaTurno;

	/**
	 * O método construtor do JogadorRA188671New.
	 *
	 * @param maoInicial Contém a mão inicial do jogador. Deve conter o número de cartas correto
	 *        dependendo se esta classe Jogador que está sendo construída é o primeiro ou o segundo
	 *        jogador da partida.
	 * @param primeiro Informa se esta classe Jogador que está sendo construída é o primeiro jogador
	 *        a iniciar nesta jogada (true) ou se é o segundo jogador (false).
	 */
	public JogadorRA188671New(ArrayList<Carta> maoInicial, boolean primeiro) {
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
		if (lacaioSum >= vidaOponente) {
			minhasJogadas.addAll(this.lacaios.stream().map(lacaio -> new Jogada(TipoJogada.ATAQUE, lacaio, null)).collect(Collectors.toList()));
			return minhasJogadas;
		}

		// Caso todos os lacaios mais o poder heroico consigam ganhar o jogo nessa rodada
		if (lacaioSum + 1 >= vidaOponente && this.manaTurno >= 2) {
			minhasJogadas.add(new Jogada(TipoJogada.PODER, null, null));
			minhasJogadas.addAll(this.lacaios.stream().map(lacaio -> new Jogada(TipoJogada.ATAQUE, lacaio, null)).collect(Collectors.toList()));
			return minhasJogadas;
		}

		Map<Integer, Integer> atacados = new HashMap<>();
		Map<CartaLacaio, CartaLacaio> ofensiva = new HashMap<>();

		this.lacaios.forEach(lacaio -> {
			CartaLacaio alvo = null;
			for (CartaLacaio oponente : this.lacaiosOponente) {
				if (oponente.getAtaque() >= lacaio.getVidaAtual()) {
					continue;
				}

				if (oponente.getVidaAtual() < lacaio.getAtaque()) {
					if (alvo == null || alvo.getAtaque() <= oponente.getAtaque()) {
						alvo = oponente;
					}
				}
			}

			ofensiva.put(lacaio, alvo);

			if (alvo != null) {
				atacados.put(alvo.getID(), alvo.getVidaAtual());
			}
		});

		for (Map.Entry<CartaLacaio, CartaLacaio> entrada : ofensiva.entrySet()) {
			Carta alvo = entrada.getValue();

			if (alvo == null) {
				minhasJogadas.add(new Jogada(TipoJogada.ATAQUE, entrada.getKey(), alvo));
				continue;
			}

			Integer vidaAlvo = atacados.get(alvo.getID());
			if (vidaAlvo > 0) {
				minhasJogadas.add(new Jogada(TipoJogada.ATAQUE, entrada.getKey(), alvo));
				atacados.put(alvo.getID(), vidaAlvo - entrada.getKey().getAtaque());
			}
		}

		List<Carta> remover = new ArrayList<>();
		for (Carta carta : this.mao) {
			if (carta instanceof CartaLacaio && temManaSuficiente(carta)) {
				minhasJogadas.add(new Jogada(TipoJogada.LACAIO, carta, null));
				this.setManaTurno(this.manaTurno - carta.getMana());
				remover.add(carta);
			}
		}

		Jogada jogadaMagia = usarMagia();
		if (jogadaMagia != null) {
			minhasJogadas.add(jogadaMagia);
		}

		descarte(remover);

		return minhasJogadas;
	}

	/**
	 * Metodo que realiza uma jogada envolvendo apenas uma magia
	 *
	 * @return Uma jogada de uma carta magia, nulo caso nao seja possivel jogar magias com a mao
	 *         atual
	 */
	public Jogada usarMagia() {
		Jogada jogada = null;
		Carta remover = null;

		for (Carta carta : this.mao) {
			if (carta instanceof CartaMagia && temManaSuficiente(carta)) {
				CartaMagia magia = (CartaMagia) carta;

				if (magiaDano(magia)) {
					jogada = new Jogada(TipoJogada.MAGIA, carta, null);
				}

				if (magiaBuff(magia)) {
					for (CartaLacaio lacaio : this.lacaios) {
						jogada = new Jogada(TipoJogada.MAGIA, carta, lacaio);
						break;
					}
				}

				if (jogada != null) {
					this.setManaTurno(this.manaTurno - carta.getMana());
					remover = carta;
					break;
				}
			}
		}

		descarte(remover);

		return jogada;
	}

	/**
	 * Metedo que verifica se existe mana suficiente para baixar a carta
	 *
	 * @param carta que se deseja usar no turno
	 * @return verdadeiro se eh possivel baixar a carta, falso caso contrario
	 */
	private boolean temManaSuficiente(Carta carta) {
		return (carta.getMana() <= this.manaTurno);
	}

	/**
	 * Verifica o tipo "Dano" para a carta magia parametrizada
	 *
	 * @param magia que se deseja usar no turno
	 * @return Verdadeiro caso seja magia de dano
	 */
	private boolean magiaDano(CartaMagia magia) {
		return (magia.getMagiaTipo().equals(TipoMagia.ALVO) || magia.getMagiaTipo().equals(TipoMagia.AREA));
	}

	/**
	 * Verifica o tipo "Buff" para a carta magia
	 *
	 * @param magia que se deseja usar no turno
	 * @return Verdadeiro caso seja um buff, faldo caso contrario
	 */
	private boolean magiaBuff(CartaMagia magia) {
		return magia.getMagiaTipo().equals(TipoMagia.AREA);
	}

	/**
	 * Remove carta da mao passada como parametro
	 *
	 * @param descarte carta a ser retirada da mao
	 */
	private void descarte(Carta descarte) {
		if (descarte != null) {
			this.mao.remove(descarte);
		}
	}

	private void descarte(Collection<Carta> cartas) {
		cartas.forEach(this::descarte);
	}

	public void setManaTurno(int manaTurno) {
		this.manaTurno = manaTurno;
	}

	public int getManaTurno() {
		return manaTurno;
	}
}
