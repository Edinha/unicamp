from image import Image
from filter import FilterFFT
from fft import FFT
import numpy
import math

class LowPassFilter(FilterFFT):

    def get_low_filter(self):
        self.minimum_distance = 50
        return self.get_filter()

    def is_valid_point(self, center, point):
        return self.distance(center, point) < self.minimum_distance

if __name__ == "__main__":
    import sys

    l = LowPassFilter(sys.argv[1])
    applied_filter = l.get_low_filter()

    i = FFT(sys.argv[1])
    i.apply_inverse(applied_filter)
    #i.display_normalize()
    i.save_to_file("output.png")

    l.apply_spectrum_filter()
    l.display_normalize()
    l.save_to_file("spectrum.png")