package deck;

import com.william.card.Card;
import com.william.card.Minion;
import com.william.deck.Deck;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class DeckTest {

	private Deck deck;

	@Before
	public void before() {
		this.deck = new Deck();
	}

	@Test
	public void testPullCardEmptyDeck() throws Exception {
		Card card = this.deck.pullCard();
		Assert.assertNull(card);
	}

	@Test
	public void testPullRecentCardFromDeck() throws Exception {
		Minion top = new Minion("Top", 6, 6, 6, 6);
		Minion below = new Minion("Below", 3, 3, 3, 3);

		this.deck.addCard(below);
		this.deck.addCard(top);

		Minion pullCard = (Minion) this.deck.pullCard();
		Assert.assertNotNull(pullCard);
		Assert.assertEquals(pullCard.getId(), top.getId());
		Assert.assertEquals(pullCard.getName(), top.getName());
		Assert.assertEquals(pullCard.getManaCost(), top.getManaCost());
	}

	@Test
	public void testAddMoreThanMaxCards() throws Exception {
		for (int i = 0; i < 2 * Deck.MAX_CARDS; i++) {
			Minion card = new Minion("Card " + i,  i * 2, i, i, i);
			this.deck.addCard(card);
		}

		Assert.assertEquals(Deck.MAX_CARDS, this.deck.getDeck().size());
	}
}
