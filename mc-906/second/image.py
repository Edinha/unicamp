from PIL import Image
from random import randint, uniform

CUBE_DIVIDE = 32

class ImageWrapper:
	img = None
	count = {}
	pixels = []

	def __init__(self, path):
		self.img = Image.open(path).convert('RGB')
		self.pixels = self.img.load()
		self.load_count()

	def get(self, point):
		(x, y) = point
		r, g, b = self.pixels[x,y][:3]
		return ( self.normalize(r), self.normalize(g), self.normalize(b) )

	def normalize(self, value):
		lower = int(CUBE_DIVIDE * (value // CUBE_DIVIDE))
		return int(lower + CUBE_DIVIDE / 2)

	def random_color(self):
		width, height = self.img.size
		return self.get( (randint(0, width - 1), randint(0, height - 1)) )

	def load_count(self):
		width, height = self.img.size
		for x in range(0, width):
			for y in range(0, height):
				color = self.get((x, y))
				self.count[color] = self.count.get(color, 0) + 1

	def percentage(self, color):
		width, height = self.img.size
		return self.count.get(color, 0) / float(width * height)

class ColorPalletProblem:
	img = None
	pallet = []

	def __init__(self, pallet, img):
		self.img = img
		self.pallet = pallet

	def fitness(self):
		return sum([ self.img.percentage(color) * self.grey_scale(color) for color in self.pallet ])

	def grey_scale(self, color):
		r, g, b = color
		return abs(r - g) * abs(g - b) * abs(r - b)

	def crossover_uniform(self, other):
		new_pallet = []

		for i in range(0, len(self.pallet)):
			my_color = self.pallet[i]
			other_color = other.pallet[i]

			my_color_count = self.img.count.get(my_color, 0)
			other_color_count = self.img.count.get(other_color, 0)

			first_chance = (my_color_count / float(my_color_count + other_color_count + 1))

			if uniform(0, 1) < first_chance:
				new_pallet.append(my_color)
			else:
				new_pallet.append(other_color)

		new_pallet = list(set(new_pallet))
		if len(new_pallet) < len(self.pallet):
			return ColorPalletProblem(self.pallet, self.img)

		return ColorPalletProblem(new_pallet, self.img)

	def crossover_single(self, other): ### escolhe um ponto aleatorio do individuo e troca os genes###
		new_pallet = []

		j = randint(1, len(self.pallet) - 1) ### deve ser entre 1 e 5, se 0 nao faz crossover ai nao vale, se 6 copia tudo tambem nao vale ###
		for i in range(0, len(self.pallet)):
			if i < j:
				new_pallet.append(other.pallet[i])
			else:
				new_pallet.append(self.pallet[i])

		new_pallet = list(set(new_pallet))
		if len(new_pallet) < len(self.pallet):
			return ColorPalletProblem(self.pallet, self.img)

		return ColorPalletProblem(new_pallet, self.img)

	def mutate(self):
		position = randint(0, len(self.pallet) - 1)
		new_color = self.pallet[position]

		while new_color in self.pallet:
			new_color = self.img.random_color()

		self.pallet[position] = new_color
