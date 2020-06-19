from image import Image
import numpy
from scipy.ndimage.morphology import binary_dilation

class Dilation(Image):

    def dilate(self, structure):
        img = self.get()
        result = binary_dilation(img, structure=structure)
        self.set(result)
        self.astype(img.dtype)

    def normalize(self):
        img = self.get()
        img = (img + 1) % 2
        img *= 255
        self.set(img)

if __name__ == "__main__":
    import sys
    i = Dilation(sys.argv[1])
    i.binary_set()
    structure = numpy.ones((int(sys.argv[2]), int(sys.argv[3])))
    i.dilate(structure)
    i.normalize()
    print("IMG: ", i.get().max(), i.get())
    i.save_to_file("dilation.pbm")
