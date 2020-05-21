from fft import FFT
from image import Image
from filter import FilterFFT
from low_pass_filter import LowPassFilter
from high_pass_filter import HighPassFilter
import numpy
import math

#class IntervalPassFilter(FilterFFT):
#    pass

if __name__ == "__main__":
    import sys

    low_cut_distance = 100
    high_cut_distance = 30

    l = LowPassFilter(sys.argv[1])
    low_filter = l.get_filter(low_cut_distance)

    m = HighPassFilter(sys.argv[1])
    high_filter = m.get_filter(high_cut_distance)

    applied_filter = low_filter * high_filter

    i = FFT(sys.argv[1])
    i.apply_inverse(applied_filter)
    i.save_to_file("output.png")

    l.apply()
    l.set(applied_filter * l.get())
    l.display_normalize()
    l.save_to_file("spectrum.png")