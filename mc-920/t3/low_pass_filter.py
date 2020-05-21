from fft import FFT
from image import Image
from filter import FilterFFT
import numpy
import math

class LowPassFilter(FilterFFT):

    def is_valid_point(self, center, point, cut_distance):
        return self.distance(center, point) < cut_distance

if __name__ == "__main__":
    import sys

    cut_distance = 50

    l = LowPassFilter(sys.argv[1])
    applied_filter = l.get_filter(cut_distance)

    i = FFT(sys.argv[1])
    i.apply_inverse(applied_filter)
    i.save_to_file("output.png")

    l.apply_spectrum_filter(cut_distance)
    l.display_normalize()
    l.save_to_file("spectrum.png")