from PIL import Image as IMG
import numpy

class Image():

    def __init__(self, path):
        self.path = path
        self.img = numpy.asarray(IMG.open(self.path).convert('L'))

    def get(self):
        return numpy.copy(self.img)

    def set(self, img):
        self.img = img

    def apply_to_all_pixels(self, f):
        self.img = f(self.img)

    def filter_apply(self, filter, transform):
        self.img = numpy.where(filter, transform, self.img)

    def save_to_file(self, path):
        if not path:
            path = self.path

        IMG.fromarray(self.img).save(path)

if __name__ == "__main__":
    import sys
    i = Image(sys.argv[1])
    print ("TASDADSDASD", i.get())
    i.save_to_file("output.png")