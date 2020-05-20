from fft import FFT
from image import Image
from filter import FilterFFT
import numpy
import math

class HighPassFilter(FilterFFT):

    def get_high_filter(self):
        self.minimum_distance = 50
        return self.get_filter()

    def is_valid_point(self, center, point):
        return self.distance(center, point) > self.minimum_distance

if __name__ == "__main__":
    import sys

    m = HighPassFilter(sys.argv[1])
    applied_filter = m.get_high_filter()

    i = FFT(sys.argv[1])
    i.apply_inverse(applied_filter)
    i.save_to_file("output.png")

    m.apply_spectrum_filter()
    m.display_normalize()
    m.save_to_file("spectrum.png")