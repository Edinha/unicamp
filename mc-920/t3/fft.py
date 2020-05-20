from image import Image
import numpy

class FFT(Image):

    def apply(self):
        img = self.get()
        result_img = numpy.zeros_like(img)
        result_img[...] = numpy.log(1 + numpy.absolute(self.fft(img)))

        self.set(result_img)

    def fft(self, channel):
        return numpy.fft.fftshift(numpy.fft.fft2(channel))

    def apply_inverse(self, applied_filter):
        img = self.get()
        fft_original = applied_filter * self.fft(img)

        result_img = numpy.zeros_like(img)
        result_img[...] =  numpy.absolute(self.inverse_fft(fft_original))

        self.set(result_img)

    def inverse_fft(self, channel):
        return numpy.fft.ifft2(numpy.fft.ifftshift(channel))

    def display_normalize(self):
        img = self.get()
        img *= 255 // img.max()
        self.set(img)

if __name__ == "__main__":
    import sys
    i = FFT(sys.argv[1])
    i.apply()
    i.display_normalize()
    i.save_to_file("spectrum.png")