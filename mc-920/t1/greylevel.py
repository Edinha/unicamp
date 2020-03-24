from image import Image
import numpy

MAX_GREY_SCALE = 256

class Greylevel(Image):

    def greylevel(self, greylevel):
        reduced_level_options = numpy.arange(0, MAX_GREY_SCALE, (MAX_GREY_SCALE // greylevel))
        self.apply_to_all_pixels(self.apply_greylevel(greylevel, reduced_level_options))
        self.astype(numpy.uint8)

    def apply_greylevel(self, level, reduced_level_options):
        def f(pixel):
            pos = pixel // (MAX_GREY_SCALE // level)
            return reduced_level_options[pos]

        return f

if __name__ == "__main__":
    import sys
    i = Greylevel(sys.argv[1])
    i.greylevel(int(sys.argv[2]))
    i.save_to_file("output.png")