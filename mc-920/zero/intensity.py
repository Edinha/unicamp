from image import Image
import numpy

class Intensity(Image):

    def negative(self):
        self.apply_to_all_pixels(self.apply_negative)

    def even_reverse(self):
        img = self.get().T
        img[::2] = img[::2][::-1]

        self.set(img.T)

    def horizontal_mirror(self):
        img = self.get()
        half = len(img) // 2
        img[half::] = img[:half:][::-1]

        self.set(img)

    def greyscale(self):
        self.apply_to_all_pixels(self.apply_greyscale)
        self.astype(numpy.uint8)

    @staticmethod
    def apply_negative(pixel):
        return 255 - pixel

    @staticmethod
    def apply_greyscale(pixel):
        return (100 + (100/255) * pixel)

if __name__ == "__main__":
    import sys
    i = Intensity(sys.argv[1])
    getattr(i, sys.argv[2])()
    i.save_to_file("output.png")