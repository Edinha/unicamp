package com.william.util;

import com.william.card.MinionCard;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class UtilTest {

	private MinionCard minionCard;
	private int attackBeforeBuff;
	private int healthBeforeBuff;

	@Before
	public void before() {
		this.minionCard = new MinionCard("Test card", 7, 10, 10, 10);
		this.attackBeforeBuff = this.minionCard.getAttack();
		this.healthBeforeBuff = this.minionCard.getCurrentHealth();
	}

	@Test
	public void applyPositiveBuff() {
		int buff = 2;

		Util.buff(minionCard, buff);
		Assert.assertEquals(attackBeforeBuff + buff, minionCard.getAttack());
		Assert.assertEquals(healthBeforeBuff + buff, minionCard.getTotalHealth());
		Assert.assertEquals(healthBeforeBuff + buff, minionCard.getCurrentHealth());

		Assert.assertTrue(minionCard.getName().contains(MinionCard.getBuffedNameSuffix()));
	}

	@Test
	public void applyNegativeAttackBuff() {
		int buff = 2;
		int negative = -2;

		Util.buff(minionCard, negative, buff);
		Assert.assertEquals(attackBeforeBuff, minionCard.getAttack());
		Assert.assertEquals(healthBeforeBuff + buff, minionCard.getTotalHealth());
		Assert.assertEquals(healthBeforeBuff + buff, minionCard.getCurrentHealth());

		Assert.assertTrue(minionCard.getName().contains(MinionCard.getBuffedNameSuffix()));
	}

	@Test
	public void applyNegativeHealthBuff() {
		int buff = 2;
		int negative = -2;

		Util.buff(minionCard, buff, negative);
		Assert.assertEquals(healthBeforeBuff, minionCard.getTotalHealth());
		Assert.assertEquals(healthBeforeBuff, minionCard.getCurrentHealth());
		Assert.assertEquals(attackBeforeBuff + buff, minionCard.getAttack());

		Assert.assertTrue(minionCard.getName().contains(MinionCard.getBuffedNameSuffix()));
	}

	@Test
	public void applyNegativeBuff() {
		int negative = -2;

		Util.buff(minionCard, negative);
		Assert.assertEquals(attackBeforeBuff, minionCard.getAttack());
		Assert.assertEquals(healthBeforeBuff, minionCard.getTotalHealth());
		Assert.assertEquals(healthBeforeBuff, minionCard.getCurrentHealth());

		Assert.assertFalse(minionCard.getName().contains(MinionCard.getBuffedNameSuffix()));
	}

}
