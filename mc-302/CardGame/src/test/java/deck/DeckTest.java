package deck;

import com.william.card.MinionCard;
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
		MinionCard card = this.deck.pullCard();
		Assert.assertNull(card);
	}

	@Test
	public void testPullRecentCardFromDeck() throws Exception {
		MinionCard top = new MinionCard(1, "Top", 6);
		MinionCard below = new MinionCard(2, "Below", 3);

		this.deck.addCard(below);
		this.deck.addCard(top);

		MinionCard pullCard = this.deck.pullCard();
		Assert.assertNotNull(pullCard);
		Assert.assertEquals(pullCard.getId(), top.getId());
		Assert.assertEquals(pullCard.getName(), top.getName());
		Assert.assertEquals(pullCard.getManaCost(), top.getManaCost());
	}

	@Test
	public void testAddMoreThanMaxCards() throws Exception {
		for (int i = 0; i < 2 * Deck.MAX_CARDS; i++) {
			MinionCard card = new MinionCard(i, "Card " + i,  i * 2);
			this.deck.addCard(card);
		}

		Assert.assertEquals(Deck.MAX_CARDS, this.deck.getDeck().size());
	}
}
