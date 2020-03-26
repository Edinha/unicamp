from image import Image
import numpy
import math

MAX_GREY_SCALE = 256

class Greyscale(Image):

    def log(self, c, _):
        self.apply_to_all_pixels(self.apply_log(c))
        self.apply_to_all_pixels(self.normalize)

    def apply_log(self, c):
        def g(pixel):
            return c * numpy.log(pixel + 1)

        return g

    def exp(self, c, e):
        self.apply_to_all_pixels(self.apply_exp(c, e))
        self.apply_to_all_pixels(self.normalize)

    def apply_exp(self, c, e):
        def g(pixel):
            return c * (e ** pixel)

        return g

    def square(self, c, _):
        self.apply_to_all_pixels(self.apply_square(c))
        self.apply_to_all_pixels(self.normalize)

    def apply_square(self, c):
        def g(pixel):
            return c * pixel * pixel

        return g

    def sqrt(self, c, _):
        self.apply_to_all_pixels(self.apply_sqrt(c))
        self.apply_to_all_pixels(self.normalize)

    def apply_sqrt(self, c):
        def g(pixel):
            return c * numpy.sqrt(pixel)

        return g

    def normalize(self, pixel):
        return numpy.uint8(pixel % MAX_GREY_SCALE)

if __name__ == "__main__":
    import sys
    i = Greyscale(sys.argv[1])
    getattr(i, sys.argv[2])(int(sys.argv[3]), float(sys.argv[4]))
    i.save_to_file("output.png")