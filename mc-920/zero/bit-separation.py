from image import Image

class BitSeparation(Image):

    def layer(self, n):
        self.apply_to_all_pixels(self.get_layer_function(n))

    def get_layer_function(self, n):
        def f(pixel):
            return (pixel & n) * 255

        return f

if __name__ == "__main__":
    import sys
    for a in range(8):
        n = 1 << (a)
        i = BitSeparation(sys.argv[1])
        i.layer(n)
        i.save_to_file("output-{}.png".format(a))