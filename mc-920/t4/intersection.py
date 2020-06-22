from image import Image
import numpy

class Intersection(Image):

    def intersect(self, another):
        self.set(self.get() & another.get())

if __name__ == "__main__":
    import sys
    i = Intersection(sys.argv[1])
    d = Image(sys.argv[2])

    i.binary_set()
    d.binary_set()
    i.intersect(d)

    i.binary_normalize()
    print("IMG: ", i.get().max(), i.get())
    i.save_to_file("intersect.pbm")
