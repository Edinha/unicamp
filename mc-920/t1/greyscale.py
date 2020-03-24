from image import Image
import numpy

MAX_GREY_SCALE = 256

class Greyscale(Image):

    def greyscale(self, scale):
        reduced_scale_options = numpy.arange(0, MAX_GREY_SCALE, (MAX_GREY_SCALE // scale))
        self.apply_to_all_pixels(self.apply_greyscale(scale, reduced_scale_options))
        self.astype(numpy.uint8)

    def apply_greyscale(self, scale, reduced_scale_options):
        def f(pixel):
            pos = pixel // (MAX_GREY_SCALE // scale)
            return reduced_scale_options[pos]

        return f

if __name__ == "__main__":
    import sys
    i = Greyscale(sys.argv[1])
    i.greyscale(int(sys.argv[2]))
    i.save_to_file("output.png")