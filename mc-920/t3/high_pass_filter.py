from fft import FFT
from image import Image
from filter import FilterFFT
import numpy
import math

class HighPassFilter(FilterFFT):

    def is_valid_point(self, center, point, cut_distance):
        return self.distance(center, point) > cut_distance

if __name__ == "__main__":
    import sys

    m = HighPassFilter(sys.argv[1])
    applied_filter = m.get_filter(50)

    i = FFT(sys.argv[1])
    i.apply_inverse(applied_filter)
    i.save_to_file("output.png")

    m.apply_spectrum_filter()
    m.display_normalize()
    m.save_to_file("spectrum.png")