from PIL import Image
from collections import defaultdict
from jinja2 import Environment
from jinja2 import PackageLoader

# Format:
# image_name : [tl x, tl y, br x, br y]
SPRITES = {
        "DUCK_RIGHT_1" : [0, 120, 35, 145],
}

if __name__ == "__main__":
    im = Image.open('media/duckhunt_various_sheet.png').convert('RGB')
    pix = im.load()

    width, height = im.size


    print(im.size)
    print(pix[96,88])
    print(im.mode)

    for sprite, coords in SPRITES.items():
        tx, ty, bx, by = coords[0], coords[1], coords[2], coords[3]

        for i in range(tx, bx, 16):
            for j in range(ty, by, 16):
                block = [[0 for _ in range(16)] for _ in range(16)]

                # find max 3 colors
                colorcount = defaultdict(lambda: 0)
                for p in range(i, min(i + 16, width)):
                    for q in range(j, min(j + 16, height)):
                        colorcount[pix[p,q]] += 1 

                print(colorcount)

                max_colors = sorted([(v, k, ind) for ind, (k, v) in enumerate(colorcount.items())])[::-1]
                print(max_colors)
                # TODO: write out color map

                for cnt, col, ind in max_colors:
                    colorcount[col] = min(ind + 1, 3)

                # Generate hex numbers
                nums = [] 
                for p in range(i, min(i + 16, width)):
                    num = 0
                    for q in range(j, min(j + 16, height)):
                        num = num * 4 + colorcount[pix[p,q]]
                    # print(hex(num))
                    nums.append(str(hex(num)))

                print(nums)
                
                loader      = PackageLoader("scripts", "templates")
                env         = Environment(loader=loader)
                template    = env.get_template('sprite.j2') 
                variables   = dict(id = 1, lines = nums)
                output_from_parsed_template = template.render(**variables)
                print(output_from_parsed_template)

