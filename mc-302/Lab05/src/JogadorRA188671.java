import java.util.ArrayList;
import java.util.stream.Collectors;

/**
* Esta classe representa um Jogador aleatório (realiza jogadas de maneira aleatória) para o jogo LaMa (Lacaios & Magias).
* @see Object
* @author William Cruz - 188671
*/
public class JogadorRA188671 extends Jogador {
	private ArrayList<CartaLacaio> lacaios;
	private ArrayList<CartaLacaio> lacaiosOponente;

	private int manaTurno;

	/**
	  * O método construtor do JogadorAleatorio.
	  *
	  * @param maoInicial Contém a mão inicial do jogador. Deve conter o número de cartas correto dependendo se esta classe Jogador que está sendo construída é o primeiro ou o segundo jogador da partida.
	  * @param primeiro   Informa se esta classe Jogador que está sendo construída é o primeiro jogador a iniciar nesta jogada (true) ou se é o segundo jogador (false).
	  */
	public JogadorRA188671(ArrayList<Carta> maoInicial, boolean primeiro){
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
		int minhaMana, minhaVida;
		if (cartaComprada != null) {
			mao.add(cartaComprada);
		}

		if(primeiroJogador){
			minhaMana = mesa.getManaJog1();
			minhaVida = mesa.getVidaHeroi1();
			lacaios = mesa.getLacaiosJog1();
			lacaiosOponente = mesa.getLacaiosJog2();
			//System.out.println("--------------------------------- Começo de turno pro jogador1");
		}
		else{
			minhaMana = mesa.getManaJog2();
			minhaVida = mesa.getVidaHeroi2();
			lacaios = mesa.getLacaiosJog2();
			lacaiosOponente = mesa.getLacaiosJog1();
			//System.out.println("--------------------------------- Começo de turno pro jogador2");
		}

		this.setManaTurno(minhaMana);

		ArrayList<Jogada> minhasJogadas = new ArrayList<Jogada>();

		Jogada jogadaMagia = usarMagia();
		if (jogadaMagia != null) {
			minhasJogadas.add(jogadaMagia);
		}

		Carta remover = null;
		for (Carta carta : this.mao) {
			if (carta instanceof CartaLacaio && temManaSuficiente(carta)) {
				minhasJogadas.add(new Jogada(TipoJogada.LACAIO, carta, null));
				this.setManaTurno(this.manaTurno - carta.getMana());
				remover = carta;
				break;
			}
		}

		descarte(remover);

		// O laço abaixo cria jogas de baixar lacaios da mão para a mesa se houver mana disponível.
		minhasJogadas.addAll(this.lacaios.stream().map(lacaio -> new Jogada(TipoJogada.ATAQUE, lacaio, null)).collect(Collectors.toList()));

		return minhasJogadas;
	}

	/**
	 * Metodo que realiza uma jogada envolvendo apenas uma magia
	 * @return Uma jogada de uma carta magia, nulo caso nao seja possivel jogar magias com a mao atual
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
	 * @param carta que se deseja usar no turno
	 * @return verdadeiro se eh possivel baixar a carta, falso caso contrario
	 */
	private boolean temManaSuficiente(Carta carta) {
		return (carta.getMana() <= this.manaTurno);
	}

	/**
	 * Verifica o tipo "Dano" para a carta magia parametrizada
	 * @param magia que se deseja usar no turno
	 * @return Verdadeiro caso seja magia de dano
	 */
	private boolean magiaDano(CartaMagia magia) {
		return (magia.getMagiaTipo().equals(TipoMagia.ALVO) || magia.getMagiaTipo().equals(TipoMagia.AREA));
	}

	/**
	 * Verifica o tipo "Buff" para a carta magia
	 * @param magia que se deseja usar no turno
	 * @return Verdadeiro caso seja um buff, faldo caso contrario
	 */
	private boolean magiaBuff(CartaMagia magia) {
		return magia.getMagiaTipo().equals(TipoMagia.AREA);
	}

	/**
	 * Remove uma carta da mao caso ela nao for nula
	 * @param remover carta a ser retirada da mao
	 */
	private void descarte(Carta remover) {
		if (remover != null) {
			this.mao.remove(remover);
		}
	}

	public void setManaTurno(int manaTurno) {
		this.manaTurno = manaTurno;
	}

	public int getManaTurno() {
		return manaTurno;
	}
}