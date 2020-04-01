from PIL import Image as IMG
import numpy

class Image():

    def __init__(self, path):
        self.path = path
        self.img = numpy.asarray(IMG.open(self.path).convert('L'))

    def get(self):
        return numpy.copy(self.img)

    def set(self, img):
        self.img = numpy.copy(img)

    def apply_to_all_pixels(self, f):
        self.img = f(self.img)

    def filter_apply(self, f, transform):
        self.img = numpy.where(f, self.img, transform)

    def astype(self, t):
        self.img = self.img.astype(t)

    def save_to_file(self, path):
        if not path:
            path = self.path

        IMG.fromarray(self.img).save(path)

if __name__ == "__main__":
    import sys
    i = Image(sys.argv[1])
    img = i.get()
    img[:100] = numpy.zeros((100, 512))
    i.set(img)
    print ("TYPE: ", type(img[0][0]))
    print ("LINES: ", len(img))
    print ("COLUMNS: ", len(img[0]))
    print ("SHAPE:   ", img.shape)
    print ("")
    print (i.get())

    i.save_to_file("output.png")