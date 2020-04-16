from image import Image
import numpy
from scipy.ndimage import convolve

class FilterConstants():
    h3 = [[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]]
    h4 = [[-1, 2, 1], [0, 0, 0], [1, 2, 1]]
    h5 = [[-1, -1, -1], [-1, 8, -1], [-1, -1, -1]]
    h6 = [[1/9, 1/9, 1/9], [1/9, 1/9, 1/9], [1/9, 1/9, 1/9]]
    h7 = [[-1, -1, 2], [-1, 2, -1], [2, -1, -1]]
    h8 = [[2, -1, -1], [-1, 2, -1], [-1, -1, 2]]


    @staticmethod
    def get_filter_matrix(name):
        return numpy.array(getattr(FilterConstants, name))

class Convolution(Image):

    def apply(self, filter_name):
        kernel = FilterConstants.get_filter_matrix(filter_name)

        img = self.get()
        print("FILTER CHOSEN: ", kernel)
        print("IMAGE STAND: ", img)

        img = convolve(img, kernel, mode='nearest')

        print("NEW IMAGE: ", img)

        self.set(img)


if __name__ == "__main__":
    import sys
    i = Convolution(sys.argv[1])
    i.apply(sys.argv[2])
    i.save_to_file("output.png")