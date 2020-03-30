from image import Image
import numpy
import math

MAX_GREY_SCALE = 256

class Greyscale(Image):

    def log(self, _):
        c = self.get_log_transform_constant()
        self.apply_to_all_pixels(self.apply_log(c))
        self.astype(numpy.uint8)

    def apply_log(self, c):
        def g(pixel):
            return c * numpy.log(pixel + 1)

        return g

    def exp(self, e):
        e = float(e)
        c = self.get_exp_transform_constant()
        self.apply_to_all_pixels(self.transform_scale)
        self.apply_to_all_pixels(self.apply_exp(c, e))
        self.apply_to_all_pixels(self.return_scale)
        self.apply_to_all_pixels(self.normalize)

    def apply_exp(self, c, e):
        def g(pixel):
            return c * (e ** pixel)

        return g

    def square(self, _):
        c = self.get_square_constant()
        self.apply_to_all_pixels(self.transform_scale)
        self.apply_to_all_pixels(self.apply_square(c))
        self.apply_to_all_pixels(self.return_scale)
        self.apply_to_all_pixels(self.normalize)

    def apply_square(self, c):
        def g(pixel):
            return c * pixel * pixel

        return g

    def sqrt(self, _):
        c = self.get_sqrt_constant()
        self.apply_to_all_pixels(self.apply_sqrt(c))
        self.apply_to_all_pixels(self.normalize)

    def apply_sqrt(self, c):
        def g(pixel):
            return c * numpy.sqrt(pixel)

        return g

    def transform_scale(self, pixel):
        return pixel / 255.0

    def return_scale(self, pixel):
        return numpy.uint8(pixel * 255)

    def normalize(self, img):
        img[img < 0] = 0
        img[img > 255] = 255
        return numpy.uint8(img)

    def get_log_transform_constant(self):
        img = self.get()
        return MAX_GREY_SCALE / (numpy.log(1 + numpy.amax(img)))

    def get_exp_transform_constant(self):
        return 20.2

    def get_square_constant(self):
        return 1

    def get_sqrt_constant(self):
        return 10

if __name__ == "__main__":
    import sys
    i = Greyscale(sys.argv[1])
    l = len(sys.argv) - 1
    getattr(i, sys.argv[2])(sys.argv[min(3, l)])
    i.save_to_file("output.png")