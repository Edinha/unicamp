from image import ImageWrapper

class GeneticAlgorithm:
	image

	def __init__(self, path):
		self.image = ImageWrapper(path)

g = GeneticAlgorithm('rainbow.png')