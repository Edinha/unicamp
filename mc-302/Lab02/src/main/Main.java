package main;

import card.MinionCard;

public class Main {

	public static void main(String[] args) {
		MinionCard darkMagician = new MinionCard(1, "Mago negro", 7, 10, 10, 10);
		MinionCard demonSkullKing = new MinionCard(2, "Rei caveira", 3, 3, 2, 30);
		MinionCard blueEyesWhiteDragon = new MinionCard(3, "Dragão branco de olhos azuis", 9, 5, 6, 20);

		// Construtor reduzido, atributos não inicializados pela construção começam em 0
		MinionCard reducedDarkMagician = new MinionCard(darkMagician.getId(), darkMagician.getName(), darkMagician.getManaCost()); 
		System.out.println("Reduzido: " + reducedDarkMagician.toString());
		
		// Mudando o ataque do primeiro lacaio
		darkMagician.setAtack(blueEyesWhiteDragon.getAtack());
		System.out.println("(Depois set) Carta 1: " + darkMagician.toString());
		
		// Não há diferença entre os valores dos atributos do objeto cópia e original
		MinionCard demonSkullKingCopy = new MinionCard(demonSkullKing);
		System.out.println("Original: " + demonSkullKing.toString());
		System.out.println("Cópia: " + demonSkullKingCopy.toString());
		
		/* Alterar a visibilidade do atributo para 'public' permite que ele seja referenciado fora da classe onde está declarado.
		 * Quando restrigimos o acesso para 'private', forçamos que os clientes (utilizadores) da classe conversem com nosso objeto
		 * a partir de getter/setter, podendo assim manter a implementação que altera o objeto agrupada em um só lugar (dentro da classe),
		 * facilitando validações e refatorações no código.
		 */
		
		System.out.println("Acessando atributo public: " + demonSkullKing.name + "\n\n");
		// Acessar atributo private gera erro de compilação devido a sua visilidade, teste: 
		// System.out.println("Acessando atributo private: " + demonSkullKing.attack);

		darkMagician.buff(10);
		System.out.println("Depois do buff (Mago negro) \n\n" + darkMagician.toString());
		
		blueEyesWhiteDragon.buff(3, 6);
		System.out.println("Depois do buff (Dragão branco) \n\n" + blueEyesWhiteDragon.toString());
		
		demonSkullKing.buff(-1);
		System.out.println("Sem aplicar buff (Rei caveira) \n\n" + demonSkullKing.toString());
	}

}
