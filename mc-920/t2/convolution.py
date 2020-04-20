from image import Image
import numpy

class FilterConstants():
    h1 = [[0, 0, -1, 0, 0], [0, -1, -2, -1, 0], [-1, -2, 16, -2, -1], [0, -1, -2, -1, 0], [0, 0, -1, 0, 0]]
    h2 = [[1/256, 4/256, 6/256, 4/256, 1/256], [4/256, 16/256, 24/256, 16/256, 4/256], [6/256, 24/256, 36/256, 24/256, 6/256], [4/256, 16/256, 24/256, 16/256, 4/256], [1/256, 4/256, 6/256, 4/256, 1/256]]

    h3 = [[-1, 0, 1], [-2, 0, 2], [-1, 0, 1]]
    h4 = [[-1, -2, -1], [0, 0, 0], [1, 2, 1]]
    h5 = [[-1, -1, -1], [-1, 8, -1], [-1, -1, -1]]
    h6 = [[1/9, 1/9, 1/9], [1/9, 1/9, 1/9], [1/9, 1/9, 1/9]]
    h7 = [[-1, -1, 2], [-1, 2, -1], [2, -1, -1]]
    h8 = [[2, -1, -1], [-1, 2, -1], [-1, -1, 2]]

    @staticmethod
    def get_filter_matrix(name):
        return numpy.array(getattr(FilterConstants, name))

class Convolution(Image):

    def get_filter(self, filter_name):
        return FilterConstants.get_filter_matrix(filter_name)

    def apply_def(self, filter_name):
        kernel = self.get_filter(filter_name)
        self.apply(kernel)

    def apply(self, kernel):
        img = self.get()
        sub_shape = (len(kernel), len(kernel))
        view_shape = tuple(numpy.subtract(img.shape, sub_shape) + 1) + sub_shape
        strides = img.strides + img.strides

        sub_matrices = numpy.lib.stride_tricks.as_strided(img, view_shape, strides)
        sub_matrices = self.multiply_filter(kernel)(sub_matrices)

        img = numpy.array([[numpy.sum(s) for s in a] for a in sub_matrices])
        self.set(self.normalize(img))

    def multiply_filter(self, kernel):
        def f(pixel):
            return pixel * kernel

        return f

    def normalize(self, img):
        img[img < 0] = 0
        img[img > 255] = 0
        return numpy.uint8(img)

if __name__ == "__main__":
    import sys
    i = Convolution(sys.argv[1])
    i.apply_def(sys.argv[2])
    i.save_to_file("output.png")