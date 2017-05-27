package base;

import java.util.HashMap;
import java.util.Map;

public enum CardType {
	BUFF {
		@Override
		public LaMaSerializable brandNew() {
			return new Buff();
		}
	},
	MINION {
		@Override
		public LaMaSerializable brandNew() {
			return new Minion();
		}
	},
	DAMAGE {
		@Override
		public LaMaSerializable brandNew() {
			return new Damage();
		}
	},
	AREA_DAMAGE {
		@Override
		public LaMaSerializable brandNew() {
			return new DamageArea();
		}
	};

	public abstract LaMaSerializable brandNew();

	static final Map<String, CardType> TYPES = new HashMap<>();
	static {
		TYPES.put(Buff.class.getSimpleName(), BUFF);
		TYPES.put(Minion.class.getSimpleName(), MINION);
		TYPES.put(Damage.class.getSimpleName(), DAMAGE);
		TYPES.put(DamageArea.class.getSimpleName(), AREA_DAMAGE);
	}

	public static LaMaSerializable of(String className) {
		return TYPES.get(className).brandNew();
	}
}
