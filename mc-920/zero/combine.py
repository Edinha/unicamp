from image import Image
import numpy

class Combine:

    def __init__(self, path_first, path_second):
        self.first = Image(path_first)
        self.second = Image(path_second)

    def result(self):
        return self.first

    def combine(self, percentage_first, percentage_second):
        self.first.apply_to_all_pixels(self.apply_percentage(percentage_first))
        self.second.apply_to_all_pixels(self.apply_percentage(percentage_second))
        self.first.apply_to_all_pixels(self.apply_combine(self.second.get()))
        self.first.astype(numpy.uint8)

    @staticmethod
    def apply_combine(img_second):
        def f(img_first):
            return img_first + img_second

        return f

    @staticmethod
    def apply_percentage(p):
        def f(pixel):
            return pixel * p

        return f

if __name__ == "__main__":
    import sys

    first = float(sys.argv[3])
    second = 1 - first
    test = Combine(sys.argv[1], sys.argv[2])
    test.combine(first, second)
    test.result().save_to_file("output.png")