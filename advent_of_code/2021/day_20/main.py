from math import inf
BORDERS_SZ = 1

def read_in():
    mask = [x == '#' for x in input()]
    assert input() == ''
    image = set()
    try:
        i = 0
        while True:
            line = input()
            for j, c in enumerate(line):
                if c == '#':
                    image.add((i, j))
            i+= 1
    except EOFError:
        pass
    return mask, Image(image)

def adj_cells(r, c):
    for new_r in range(r - 1, r + 2):
        for new_c in range(c - 1, c + 2):
            yield new_r, new_c

class Image:
    def __init__(self, image, background_color=False):
        self.image: set = image
        rs = [x for x, _ in self.image]
        cs = [x for _, x in self.image]
        self.min_r = min(rs)
        self.min_c = min(cs)
        self.max_r = max(rs)
        self.max_c = max(cs)
        self.background_color = background_color

    def is_lit_at(self, r, c):
        if self.min_r <= r <= self.max_r and \
           self.min_c <= c <= self.max_c:
            return (r, c) in self.image
        return self.background_color

    def get_mask_idx_at(self, r, c):
        s = 0
        for new_r, new_c in adj_cells(r, c):
            s = s*2 + int(self.is_lit_at(new_r, new_c))
        return s

    def simulate_step(self, mask):
        # this is an approximation of the step since it's impossible
        # to account for the infinite image changing together
        # and only the borders of the image and the inside are updated according
        # to the mask. It is assumed that BORDERS_SZ is large enough to avoid
        # issues with border effects
        new_image = set()
        for r in range(self.min_r - BORDERS_SZ, self.max_r + 1 + BORDERS_SZ):
            for c in range(self.min_c - BORDERS_SZ, self.max_c + 1 + BORDERS_SZ):
                if mask[self.get_mask_idx_at(r, c)]:
                    new_image.add((r, c))

        background_color = self.background_color
        if background_color and not mask[(2**9) - 1]:
            # switch back to background_color dim
            background_color = False
        elif not background_color and mask[0]:
            # switch to background_color lit
            background_color = True
        return Image(new_image, background_color=background_color)

    def lit_pixels_count(self):
        if self.background_color:
            # all of the infinite image outside the border is lit
            return inf
        return len(self.image)


def simulate(mask, image, steps):
    for _ in range(steps):
        image = image.simulate_step(mask)
    return image

def part_1(mask, image):
    image = simulate(mask, image, 2)
    return image.lit_pixels_count()

def part_2(mask, image):
    image = simulate(mask, image, 50)
    return image.lit_pixels_count()

def main():
    mask, image = read_in()
    print("part_1:", part_1(mask, image))
    print("part_2:", part_2(mask, image))

if __name__ == '__main__':
    main()
