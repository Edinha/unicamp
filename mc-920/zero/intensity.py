from image import Image

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

    @staticmethod
    def apply_negative(pixel):
        return 255 - pixel

    @staticmethod
    def even_filter(img):
        return img[::2]

    @staticmethod
    def apply_reverse(row):
        pass

if __name__ == "__main__":
    import sys
    i = Intensity(sys.argv[1])
    i.even_reverse()
    i.save_to_file("output.png")