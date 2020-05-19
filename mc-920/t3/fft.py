from image import Image
import numpy

class FFT(Image):

    def apply(self):
        img = self.get()
        result_img = numpy.zeros_like(img)
        result_img[...] = self.fft(img)

        print("RESULT IMG: ", result_img)
        result_img *= 255 // result_img.max()
        print("RESULT IMG: ", result_img)

        self.set(result_img)

    def fft(self, channel):
        fft = numpy.fft.fftshift(numpy.fft.fft2(channel))
        return numpy.log(1 + numpy.absolute(fft))

if __name__ == "__main__":
    import sys
    i = FFT(sys.argv[1])
    i.apply()
    i.save_to_file("output.png")