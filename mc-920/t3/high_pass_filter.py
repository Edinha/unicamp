from image import Image
from filter import FilterFFT
import numpy
import math

class HighPassFilter(FilterFFT):

    def apply_low_filter(self):
        self.minimum_distance = 50
        self.apply_filter()

    def is_valid_point(self, center, point):
        return self.distance(center, point) < self.minimum_distance

if __name__ == "__main__":
    import sys
    i = HighPassFilter(sys.argv[1])
    i.apply_low_filter()
    i.save_to_file("output.png")