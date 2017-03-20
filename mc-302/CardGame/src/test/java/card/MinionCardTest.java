package card;

import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class MinionCardTest {
	private MinionCard minionCard;

	private int attackBeforeBuff;
	private int healthBeforeBuff;

	@Before
	public void before() {
		this.minionCard = new MinionCard(1, "Test card", 7, 10, 10, 10);
		this.attackBeforeBuff = this.minionCard.getAttack();
		this.healthBeforeBuff = this.minionCard.getCurrentHealth();
	}

	// TODO assert buffed name

	@Test
	public void applyPositiveBuff() {
		int buff = 2;

		this.minionCard.buff(buff);
		Assert.assertEquals(attackBeforeBuff + buff, minionCard.getAttack());
		Assert.assertEquals(healthBeforeBuff + buff, minionCard.getCurrentHealth());
	}

	@Test
	public void applyNegativeAttackBuff() {
		int buff = 2;
		int negative = -2;

		this.minionCard.buff(negative, buff);
		Assert.assertEquals(attackBeforeBuff, minionCard.getAttack());
		Assert.assertEquals(healthBeforeBuff + buff, minionCard.getCurrentHealth());
	}

	@Test
	public void applyNegativeHealthBuff() {
		int buff = 2;
		int negative = -2;

		this.minionCard.buff(buff, negative);
		Assert.assertEquals(healthBeforeBuff, minionCard.getCurrentHealth());
		Assert.assertEquals(attackBeforeBuff + buff, minionCard.getAttack());
	}
}
