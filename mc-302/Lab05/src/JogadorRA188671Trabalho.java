import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.stream.Collectors;

public class JogadorRA188671Trabalho extends Jogador {
	private List<CartaLacaio> lacaios;
	private List<CartaLacaio> lacaiosOponente;

	private int manaTurno;

	private List<Carta> retiradas;

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
		this.retiradas = new ArrayList<>();
		ArrayList<Jogada> minhasJogadas = new ArrayList<>();

		// Usar poder heroico para destruir heroi inimigo
		if (vidaOponente == 1 && this.manaTurno >= 2) {
			minhasJogadas.add(new Jogada(TipoJogada.PODER, null, null));
			return minhasJogadas;
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

		// Decide a estrategia depois de verificar se nao tem caso de vitoria certa com a mesa atual
//		 minhasJogadas.addAll(agressivo());
//		minhasJogadas.addAll(controle());
		 minhasJogadas.addAll(curvaMana());

		descarte(this.retiradas);

		return minhasJogadas;
	}

	// Método que realiza a estratégia agressiva
	private List<Jogada> agressivo() {
		List<Jogada> minhasJogadas = new ArrayList<>();
		List<CartaMagia> magias = new ArrayList<>();
		List<CartaLacaio> invocarLacaios = new ArrayList<>();

		Map<CartaMagia, CartaLacaio> buffs = new HashMap<>();

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

				// Marca um mapa de buff por lacaio a ser utilizado
				if (magiaBuff(magia)) {
					Optional<CartaLacaio> lacaio = this.mapearBuff(magia);
					if (lacaio.isPresent()) {
						buffs.put(magia, lacaio.get());
					}
				}
			}
		}

		// Ordena os lacaios pelo ataque, dos de maior ataque para os de menor.
		Collections.sort(invocarLacaios, (first, second) -> Integer.valueOf(first.getAtaque()).compareTo(second.getAtaque()));

		// Ordena as magias pelo dano, das de maior dano para os de menor.
		Collections.sort(magias, (first, second) -> Integer.valueOf(first.getMagiaDano()).compareTo(second.getMagiaDano()));

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

		// Usa buffs nos lacaios marcados
		minhasJogadas.addAll(usarBuffs(buffs));

		// Todos os lacaios atacam diretamente o herói inimigo
		minhasJogadas.addAll(ataqueDiretoHeroi());

		return minhasJogadas;
	}

	// Método que realiza a estratégia de controle
	private List<Jogada> controle() {
		List<Jogada> minhasJogadas = new ArrayList<>();
		List<CartaLacaio> alvos = new ArrayList<>();
		List<CartaLacaio> invocarLacaios = new ArrayList<>();

		// Passa pelos lacaios e decide as jogadas por trocas favoráveis
		this.lacaios.forEach(lacaio -> {
			CartaLacaio alvo = null;
			for (CartaLacaio oponente : this.lacaiosOponente) {
				if (!alvos.contains(oponente) && trocaFavorel(lacaio, oponente)) {
					alvo = oponente;
					break;
				}
			}

			minhasJogadas.add(new Jogada(TipoJogada.ATAQUE, lacaio, alvo));
			if (alvo != null) {
				alvos.add(alvo);
				this.lacaiosOponente.remove(alvo);
			}
		});

		// Usar magias de controle
		for (Carta carta : this.mao) {
			if (carta instanceof CartaLacaio) {
				invocarLacaios.add((CartaLacaio) carta);
			}

			if (carta instanceof CartaMagia && temManaSuficiente(carta)) {
				CartaMagia magia = (CartaMagia) carta;

				// Usa magias em área caso o oponente tenha mais de uma lacaio em campo
				if (magiaArea(magia) && this.lacaiosOponente.size() > 1) {
					minhasJogadas.add(new Jogada(TipoJogada.MAGIA, magia, null));
					atualizarMana(magia);
					retiradas.add(magia);
					
					// Remove os lacaios que sao destruidos pela magia em area
					this.lacaiosOponente.removeAll(lacaiosOponente.stream().filter(x -> x.getVidaAtual() <= magia.getMagiaDano()).collect(
						Collectors.toList()));
				}

				// Usa magias de alvo sem desperdício de mana e tenha destruir lacaio
				if (magiaAlvo(magia)) {
					CartaLacaio destruida = null;
					for (CartaLacaio oponente : this.lacaiosOponente) {
						// TODO calc diference to no waste ?
						if (magia.getMagiaDano() >= oponente.getVidaAtual()) {
							minhasJogadas.add(new Jogada(TipoJogada.MAGIA, magia, oponente));
							atualizarMana(magia);
							retiradas.add(magia);
							destruida = oponente;
							break;
						}
					}

					if (destruida != null) {
						this.lacaiosOponente.remove(destruida);
					}
				}

				// TODO other way of using buffs
			}
		}

		// TODO max of minions in table
		// Invoca quantos lacaios a mana restante permitir
		for (CartaLacaio invocao : invocarLacaios) {
			if (temManaSuficiente(invocao) ) {
				retiradas.add(invocao);
				atualizarMana(invocao);
				minhasJogadas.add(new Jogada(TipoJogada.LACAIO, invocao, null));
			}
		}

		return minhasJogadas;
	}

	// Estrategia de curva de mana
	public List<Jogada> curvaMana() {
		List<Jogada> jogadas = new ArrayList<>();

		Map<CartaMagia, CartaLacaio> buffs = new HashMap<>();

		// Ordena as cartas da mao por maior custo de mana
		Collections.sort(this.mao, (first, second) -> Integer.valueOf(first.getMana()).compareTo(second.getMana()));

		for (Carta carta : this.mao) {
			if (!temManaSuficiente(carta)) {
				continue;
			}

			// Caso seja um lacaio, o invoca
			if (carta instanceof CartaLacaio) {
				jogadas.add(new Jogada(TipoJogada.LACAIO, carta, null));
				this.atualizarMana(carta);
				retiradas.add(carta);
			}

			if (carta instanceof CartaMagia) {
				CartaMagia magia = (CartaMagia) carta;

				// Magia de dano, acertar um alvo que possui mais mana que a carta e o elimina
				if (magiaAlvo(magia)) {
					CartaLacaio destruida = null;

					for (CartaLacaio inimigo : this.lacaiosOponente) {
						if (magia.getMagiaDano() >= inimigo.getVidaAtual() && inimigo.getMana() > magia.getMana()) {
							jogadas.add(new Jogada(TipoJogada.MAGIA, magia, inimigo));
							this.atualizarMana(carta);
							retiradas.add(carta);
							destruida = inimigo;
							break;
						}
					}

					if (destruida != null) {
						this.lacaiosOponente.remove(destruida);
					}
				}

				// Magia de area, calcula a troca custo de mana dos destruidos x custo de mana da magia
				if (magiaArea(magia)) {
					List<CartaLacaio> destruidos = this.lacaiosOponente.stream()
							.filter(inimigo -> magia.getMagiaDano() >= inimigo.getVidaAtual())
							.collect(Collectors.toList());

					// Caso o custo de manda dos destruidos seja maior do que da magia, momento de usar
					int custoDeManaDestruidos = destruidos.stream().mapToInt(Carta::getMana).sum();
					if (custoDeManaDestruidos > magia.getMana()) {
						jogadas.add(new Jogada(TipoJogada.MAGIA, carta, null));
						this.atualizarMana(carta);
						retiradas.add(carta);
						this.lacaiosOponente.removeAll(destruidos);
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
	 * @param buffs mapeamento entre magias de buff e lacaios onde utilizar
	 * @return lista de jogadas de buff
	 */
	private List<Jogada> usarBuffs(Map<CartaMagia, CartaLacaio> buffs) {
		List<Jogada> jogadas = new ArrayList<>();

		for (Map.Entry<CartaMagia, CartaLacaio> buff : buffs.entrySet()) {
			CartaMagia magia = buff.getKey();
			if (temManaSuficiente(magia)) {
				jogadas.add(new Jogada(TipoJogada.MAGIA, magia, buff.getValue()));
				this.atualizarMana(magia);
				retiradas.add(magia);
			}
		}

		return jogadas;
	}

	/**
	 * Busca o lacaio mais forte em campo para se buffar
	 * @param magia buff desejado usar
	 * @return lacaio a ser buffado, optional vazio caso nao exista nenhum
	 */
	private Optional<CartaLacaio> mapearBuff(CartaMagia magia) {
		if (!magiaBuff(magia) || this.lacaios.isEmpty()) {
			return Optional.empty();
		}

		this.lacaios.sort((first, second) -> Integer.valueOf(first.getAtaque()).compareTo(second.getAtaque()));
		return Optional.ofNullable(this.lacaios.iterator().next());
	}

	/**
	 * Retorna uma colecao de jogadas com todos os minions em campo atacando diretamente o heroi
	 * inimigo
	 * 
	 * @return ataques contra o heroi inimigo
	 */
	private List<Jogada> ataqueDiretoHeroi() {
		return this.lacaios.stream().map(lacaio -> new Jogada(TipoJogada.ATAQUE, lacaio, null)).collect(Collectors.toList());
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
	 * Verifica o tipo "Dano" para a carta magia parametrizada
	 * 
	 * @param magia que se deseja usar no turno
	 * @return Verdadeiro caso tipo magia seja ALVO ou AREA, falso caso contrário
	 */
	private boolean magiaDano(CartaMagia magia) {
		return (magiaAlvo(magia) || magiaArea(magia));
	}

	/**
	 * Verifica o tipo area para magia parametrizada
	 * 
	 * @param magia carta
	 * @return Verdadeiro caso seja magia de area, falso caso contrario
	 */
	private boolean magiaArea(CartaMagia magia) {
		return TipoMagia.AREA.equals(magia.getMagiaTipo());
	}

	/**
	 * Verifica o tipo alvo para magia parametrizada
	 * 
	 * @param magia carta
	 * @return Verdadeiro caso seja magia de alvo, falso caso contrario
	 */
	private boolean magiaAlvo(CartaMagia magia) {
		return TipoMagia.ALVO.equals(magia.getMagiaTipo());
	}

	/**
	 * Verifica o tipo buff para magia parametrizada
	 * 
	 * @param magia carta
	 * @return Verdadeiro caso seja magia de buff, falso caso contrario
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
}
