from image import Image
import numpy

class FilterConstants():
    h3 = [[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]]

    @staticmethod
    def get_filter_matrix(name):
        return numpy.array(getattr(FilterConstants, name))

class Convolution(Image):

    def apply(self, filter_name):
        filter = FilterConstants.get_filter_matrix(filter_name)

        print("FILTER CHOSEN: ", filter)


if __name__ == "__main__":
    import sys
    i = Convolution(sys.argv[1])
    i.apply(sys.argv[2])
    i.save_to_file("output.png")