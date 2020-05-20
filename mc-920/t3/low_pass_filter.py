from image import Image
from fft import FFT
import numpy
import math

class LowPassFilter(FFT):

    def apply_filter(self):
        self.apply()

        entry_distance = 10

        img = self.get()
        (w, h) = img.shape
        center = (w // 2, h // 2)

        for x in range(w):
            for y in range(h):
                if self.distance(center, (y, x)) > entry_distance:
                    img[y,x] = 0

        self.set(img)

    def distance(self, a, b):
        return math.sqrt( (a[0] - b[0])**2 + (a[1] - b[1])**2 )

if __name__ == "__main__":
    import sys
    i = LowPassFilter(sys.argv[1])
    i.apply_filter()
    i.save_to_file("output.png")