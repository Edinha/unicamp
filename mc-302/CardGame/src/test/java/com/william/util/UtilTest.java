package com.william.util;

import com.william.card.Minion;
import org.junit.Assert;
import org.junit.Before;
import org.junit.Test;

public class UtilTest {

	private Minion minion;
	private int attackBeforeBuff;
	private int healthBeforeBuff;

	@Before
	public void before() {
		this.minion = new Minion("Test card", 7, 10, 10, 10);
		this.attackBeforeBuff = this.minion.getAttack();
		this.healthBeforeBuff = this.minion.getCurrentHealth();
	}

	@Test
	public void applyPositiveBuff() {
		int buff = 2;

		Util.buff(minion, buff);
		Assert.assertEquals(attackBeforeBuff + buff, minion.getAttack());
		Assert.assertEquals(healthBeforeBuff + buff, minion.getTotalHealth());
		Assert.assertEquals(healthBeforeBuff + buff, minion.getCurrentHealth());

		Assert.assertTrue(minion.getName().contains(Minion.getBuffedNameSuffix()));
	}

	@Test
	public void applyNegativeAttackBuff() {
		int buff = 2;
		int negative = -2;

		Util.buff(minion, negative, buff);
		Assert.assertEquals(attackBeforeBuff, minion.getAttack());
		Assert.assertEquals(healthBeforeBuff + buff, minion.getTotalHealth());
		Assert.assertEquals(healthBeforeBuff + buff, minion.getCurrentHealth());

		Assert.assertTrue(minion.getName().contains(Minion.getBuffedNameSuffix()));
	}

	@Test
	public void applyNegativeHealthBuff() {
		int buff = 2;
		int negative = -2;

		Util.buff(minion, buff, negative);
		Assert.assertEquals(healthBeforeBuff, minion.getTotalHealth());
		Assert.assertEquals(healthBeforeBuff, minion.getCurrentHealth());
		Assert.assertEquals(attackBeforeBuff + buff, minion.getAttack());

		Assert.assertTrue(minion.getName().contains(Minion.getBuffedNameSuffix()));
	}

	@Test
	public void applyNegativeBuff() {
		int negative = -2;

		Util.buff(minion, negative);
		Assert.assertEquals(attackBeforeBuff, minion.getAttack());
		Assert.assertEquals(healthBeforeBuff, minion.getTotalHealth());
		Assert.assertEquals(healthBeforeBuff, minion.getCurrentHealth());

		Assert.assertFalse(minion.getName().contains(Minion.getBuffedNameSuffix()));
	}

}
