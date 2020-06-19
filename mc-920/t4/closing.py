from image import Image
import numpy
from erosion import Erosion
from dilation import Dilation

class Closing(Erosion, Dilation):

    def close(self, structure):
        self.dilate(structure)
        self.erode(structure)

if __name__ == "__main__":
    import sys
    i = Closing(sys.argv[1])
    i.binary_set()
    structure = numpy.ones((int(sys.argv[2]), int(sys.argv[3])))
    i.close(structure)
    i.binary_normalize()
    print("IMG: ", i.get().max(), i.get())
    i.save_to_file("closing.pbm")
