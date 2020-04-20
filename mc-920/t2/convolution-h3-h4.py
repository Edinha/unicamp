from image import Image
import numpy
from convolution import Convolution

class ConvolutionSquare(Convolution):

    def apply_multiplication(self, h3_result, h4_result):
        h3 = h3_result.get()
        h4 = h4_result.get()

        h3_square = h3 * h3
        h4_square = h4 * h4
        summed = numpy.add(h3_square, h4_square)

        img = numpy.sqrt(summed)
        self.set(img)
        self.set(self.normalize(self.get()))

    def adjust(self, max_value):
        def f(pixel):
            return 255 * (pixel / max_value)

        return f

if __name__ == "__main__":
    import sys
    first = Convolution(sys.argv[1])
    second = Convolution(sys.argv[1])
    first.apply_def('h3')
    second.apply_def('h4')

    i = ConvolutionSquare(sys.argv[1])
    i.apply_multiplication(first, second)
    i.save_to_file("output.png")