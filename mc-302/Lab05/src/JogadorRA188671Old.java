import java.util.ArrayList;
import java.util.stream.Collectors;

/**
* Esta classe representa um Jogador aleatório (realiza jogadas de maneira aleatória) para o jogo LaMa (Lacaios & Magias).
* @see Object
* @author William Cruz - 188671
*/
public class JogadorRA188671Old extends Jogador {
	private ArrayList<CartaLacaio> lacaios;
	private ArrayList<CartaLacaio> lacaiosOponente;

	private int manaTurno;

	/**
	  * O método construtor do JogadorAleatorio.
	  *
	  * @param maoInicial Contém a mão inicial do jogador. Deve conter o número de cartas correto dependendo se esta classe Jogador que está sendo construída é o primeiro ou o segundo jogador da partida.
	  * @param primeiro   Informa se esta classe Jogador que está sendo construída é o primeiro jogador a iniciar nesta jogada (true) ou se é o segundo jogador (false).
	  */
	public JogadorRA188671Old(ArrayList<Carta> maoInicial, boolean primeiro){
		primeiroJogador = primeiro;

		mao = maoInicial;
		lacaios = new ArrayList<>();
		lacaiosOponente = new ArrayList<>();

		// Mensagens de depuração:
		System.out.println("*Classe JogadorRA188671* Sou o " + (primeiro?"primeiro":"segundo") + " jogador (classe: JogadorRA188671)");
		System.out.println("Mao inicial:");
		for(int i = 0; i < mao.size(); i++)
			System.out.println("ID " + mao.get(i).getID() + ": " + mao.get(i));
	}

	/**
	  * Um método que processa o turno de cada jogador. Este método deve retornar as jogadas do Jogador decididas para o turno atual (ArrayList de Jogada).
	  *
	  * @param mesa   O "estado do jogo" imediatamente antes do início do turno corrente. Este objeto de mesa contém todas as informações 'públicas' do jogo (lacaios vivos e suas vidas, vida dos heróis, etc).
	  * @param cartaComprada   A carta que o Jogador recebeu neste turno (comprada do Baralho). Obs: pode ser null se o Baralho estiver vazio ou o Jogador possuir mais de 10 cartas na mão.
	  * @param jogadasOponente   Um ArrayList de Jogada que foram os movimentos utilizados pelo oponente no último turno, em ordem.
	  * @return            um ArrayList com as Jogadas decididas
	  */
	public ArrayList<Jogada> processarTurno (Mesa mesa, Carta cartaComprada, ArrayList<Jogada> jogadasOponente){
		int minhaMana;
		if (cartaComprada != null) {
			mao.add(cartaComprada);
		}

		if (primeiroJogador){
			minhaMana = mesa.getManaJog1();
			lacaios = mesa.getLacaiosJog1();
			lacaiosOponente = mesa.getLacaiosJog2();
		} else {
			minhaMana = mesa.getManaJog2();
			lacaios = mesa.getLacaiosJog2();
			lacaiosOponente = mesa.getLacaiosJog1();
		}

		this.setManaTurno(minhaMana);

		ArrayList<Jogada> minhasJogadas = new ArrayList<>();

		Jogada jogadaMagia = usarMagia();
		if (jogadaMagia != null) {
			minhasJogadas.add(jogadaMagia);
		}

		// Itera nas minhas cartas procurando um lacaio para ser invocado
		Carta remover = null;
		for (Carta carta : this.mao) {
			if (carta instanceof CartaLacaio && temManaSuficiente(carta)) {
				minhasJogadas.add(new Jogada(TipoJogada.LACAIO, carta, null));
				atualizarMana(carta);
				remover = carta;
				break;
			}
		}

		descarte(remover);

		// O laço abaixo cria jogadas de lacaios atacando o heroi inimigo
		minhasJogadas.addAll(this.lacaios.stream().map(lacaio -> new Jogada(TipoJogada.ATAQUE, lacaio, null)).collect(Collectors.toList()));

		return minhasJogadas;
	}

	/**
	 * Metodo que realiza uma jogada envolvendo apenas uma magia
	 * @return Jogada de uma magia, nulo caso não seja possível jogar magias com a mão atual
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
					// Buffa o primeiro lacaio que encontrar
					for (CartaLacaio lacaio : this.lacaios) {
						jogada = new Jogada(TipoJogada.MAGIA, carta, lacaio);
						break;
					}
				}

				// Caso uma jogada tenha sido instanciada, usa a carta magia atual e para de procurar na mao
				if (jogada != null) {
					atualizarMana(carta);
					remover = carta;
					break;
				}
			}
		}

		descarte(remover);

		return jogada;
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
	 * Verifica o tipo "Buff" para a carta magia
	 * @param magia que se deseja usar no turno
	 * @return Verdadeiro caso tipo magia seja BUFF, faldo caso contrario
	 */
	private boolean magiaBuff(CartaMagia magia) {
		return magia.getMagiaTipo().equals(TipoMagia.BUFF);
	}

	/**
	 * Remove uma carta da mão caso ela não for nula
	 * @param remover carta a ser retirada da mão
	 */
	private void descarte(Carta remover) {
		if (remover != null) {
			this.mao.remove(remover);
		}
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