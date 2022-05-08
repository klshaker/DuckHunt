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
    im = Image.open('media/duckhunt_various_sheet.png').convert('RGBA')
    pix = im.load()

    width, height = im.size


    print(im.size)
    print(pix[96,88])
    print(im.mode)
    loader      = PackageLoader("scripts", "templates")
    env         = Environment(loader=loader)
    sprite_temp    = env.get_template('sprite.j2') 
    color_temp     = env.get_template('colormap.j2')

    for sprite, coords in SPRITES.items():
        tx, ty, bx, by = coords[0], coords[1], coords[2], coords[3]

        colorcount = defaultdict(lambda: 0)
        for i in range(tx, bx):
            for j in range(ty, by):
                colorcount[pix[i,j]] += 1

        max_colors = sorted([(v, k) for (k, v) in colorcount.items()])[::-1]
        print(colorcount)
        print(max_colors)
        

        out_colors = []
        cm_ind = 1
        for cnt, col in max_colors:
            if col[3] == 0:
                colorcount[col] = 0
            else:
                if cm_ind <= 3:
                    out_colors.append(col)
                colorcount[col] = min(cm_ind, 3)
                cm_ind += 1

        print(out_colors)
        
        # Write out color map
        variables   = dict(id = 1, colors = out_colors)
        output_from_parsed_template = color_temp.render(**variables)
        print(output_from_parsed_template)

        for i in range(tx, bx, 16):
            for j in range(ty, by, 16):
                # Generate hex numbers
                nums = ['0x0' for _ in range(16)] 
                for q in range(j, min(j + 16, by)):
                    num = 0
                    for p in range(i, min(i + 16, bx)):
                        # num = num * 4 + colorcount[pix[p,q]]
                        num ^= (colorcount[pix[p,q]] << (2 * (p - i)))
                    nums[q - j] = str(hex(num))
                    # nums[q - j] = str(hex(rev))

                print(nums)
                
                variables   = dict(id = 1, lines = nums)
                output_from_parsed_template = sprite_temp.render(**variables)
                print(output_from_parsed_template)

