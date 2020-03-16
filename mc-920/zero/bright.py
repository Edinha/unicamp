from image import Image
import numpy

class Bright(Image):

    def bright(self, gamma):
        self.apply_to_all_pixels(self.real_interval)
        self.apply_to_all_pixels(self.apply_bright(gamma))
        self.apply_to_all_pixels(self.natural_interval)
        self.astype(numpy.uint8)

    @staticmethod
    def real_interval(pixel):
        return pixel / 255

    @staticmethod
    def natural_interval(pixel):
        return (pixel * 255) // 1

    def apply_bright(self, gamma):
        def f(pixel):
            return pixel ** (1 / gamma)

        return f

if __name__ == "__main__":
    import sys
    gamma = float(sys.argv[2])
    i = Bright(sys.argv[1])
    i.bright(gamma)
    i.save_to_file("output.png")
    #i.save_to_file("output-{}.png".format(gamma))