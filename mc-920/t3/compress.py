from fft import FFT
from image import Image
from filter import FilterFFT
import numpy
import math

class Compress(FilterFFT):

    def get_compress_filter(self, max_value):
        img = self.get()
        fft = numpy.log(1 + numpy.abs(self.fft(img)))

        fft[fft < max_value] = 0

        result_img = numpy.zeros_like(img)
        result_img[...] = fft

        self.set(result_img)

        result_img[result_img > 0] = 1
        return result_img

if __name__ == "__main__":
    import sys

    max_value = float(sys.argv[2])

    c = Compress(sys.argv[1])
    d = Compress(sys.argv[1])
    compress_filter = c.get_compress_filter(max_value)

    img = d.get()
    result = numpy.zeros_like(img)
    result[...] = numpy.absolute(d.inverse_fft(compress_filter * d.fft(img)))
    d.set(result)
    d.save_to_file("output.png")

    c.display_normalize()
    c.save_to_file("spectrum.png")