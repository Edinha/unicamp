from PIL import Image as IMG
import numpy

class Image():

    def __init__(self, path):
        self.path = path
        self.img_input = IMG.open(self.path)
        self.img = numpy.asarray(self.img_input.convert('L'))

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

    def get_channel(self, index):
        return self.img_input.split()[index]

    def binary_set(self):
        self.img = self.img // 255
        self.img = (self.img + 1) % 2

    def binary_normalize(self):
        img = self.get()
        img = (img + 1) % 2
        img *= 255
        self.set(img)

    def save_to_file(self, path):
        if not path:
            path = self.path

        IMG.fromarray(self.img).save(path)

if __name__ == "__main__":
    import sys
    i = Image(sys.argv[1])
    i.binary_set()
    img = i.get()
    print ("TYPE: ", type(img[0][0]))
    print ("LINES: ", len(img))
    print ("COLUMNS: ", len(img[0]))
    print ("SHAPE:   ", img.shape)
    print ("")
    print (i.get())

    i.binary_normalize()
    i.save_to_file("output.png")