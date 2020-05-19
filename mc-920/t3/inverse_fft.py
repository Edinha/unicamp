from image import Image
import numpy

class InverseFFT(Image):

    def apply(self):
        img = self.get()
        result_img = numpy.zeros_like(img)
        result_img[...] = self.inverse_fft(img)

        result_img *= 255 // result_img.max()
        print("RESUKLT IMG: ", result_img)
        self.set(result_img)

    def inverse_fft(self, channel):
        fft = numpy.fft.ifft2(numpy.fft.ifftshift(channel))
        return numpy.abs(fft)

if __name__ == "__main__":
    import sys
    i = InverseFFT(sys.argv[1])
    i.apply()
    i.save_to_file("inverse.png")