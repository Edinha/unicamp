from PIL import Image
from random import randint

mask = 0x07
SIGNIFICANT_BITS = 6

class ImageWrapper:
	img = None
	count = {}
	pixels = []

	def __init__(self, path):
		self.img = Image.open(path)
		self.pixels = self.img.load()
		self.load_count()

	def get(self, point):
		(x, y) = point
		r, g, b = self.pixels[x,y][:3]
		return (r & ~mask, g & ~mask, b & ~mask)

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
	pallet = []

	def __init__(self, pallet):
		self.pallet = pallet

	def fitness(self, image):
		return sum([ image.percentage(color) for color in self.pallet ])

	def crossover(self, other):
		crossover_point = randint(1, 2)
		new_pallet = self.pallet[:crossover_point] + other.pallet[crossover_point:]

		new_pallet = list(set(new_pallet))
		if len(new_pallet) < len(self.pallet):
			return ColorPalletProblem(self.pallet)

		return ColorPalletProblem(new_pallet)

	def mutate(self, image):
		position = randint(0, 2)
		self.pallet[position] = image.random_color()
