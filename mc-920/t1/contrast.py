from image import Image
import numpy

class Contrast(Image):

    def constrast(self, x_start, x_end, y_start, y_end):
        alpha = y_start / x_start
        beta = (y_end - y_start) / (x_end - x_start)
        gamma = (255 - y_end) / (255 - x_end)

        img = self.get()
        img = numpy.where(img < x_start, img, img * alpha)
        img = numpy.where(img > x_start, img, numpy.where(img < x_end, img, img * beta))
        img = numpy.where(img > x_end, img, img * gamma)

        self.set(img)
        self.apply_to_all_pixels(self.normalize)
        self.astype(numpy.uint8)

    def normalize(self, img):
        img[img < 0] = 0
        img[img > 255] = 255
        return numpy.uint8(img)

if __name__ == "__main__":
    import sys
    r = Contrast(sys.argv[1])
    r.constrast(int(sys.argv[2]), int(sys.argv[3]), int(sys.argv[4]), int(sys.argv[5]))
    r.save_to_file("output.png")