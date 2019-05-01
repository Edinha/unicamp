from PIL import Image

class ImageWrapper:
	pixels = []

	def __init__(self, path):
		img = Image.open(path)
		self.pixels = img.load()

	def get(self, point):
		(x, y) = point
		return self.pixels[x,y]