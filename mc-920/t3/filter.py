from image import Image
from fft import FFT
import numpy
import math

class FilterFFT(FFT):

    def apply_spectrum_filter(self):
        self.apply()
        self.set(self.get_filter() * self.get())

    def get_filter(self):
        img = self.get()
        (w, h) = img.shape
        center = (w // 2, h // 2)

        img = numpy.zeros_like(img)
        for x in range(w):
            for y in range(h):
                if self.is_valid_point(center, (y, x)):
                    img[y,x] = 1

        return img

    def distance(self, a, b):
        return math.sqrt( (a[0] - b[0])**2 + (a[1] - b[1])**2 )
