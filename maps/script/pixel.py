import sys
from PIL import Image
import ntpath
import os.path

def rgb_to_int(rgb):
    r = rgb[0]
    g = rgb[1]
    b = rgb[2]
    ret = (r << 16) + (g << 8) + b
    return ret

def get_z(n):
    ret = (20/3355443) * n - 50
    ret = round(ret)
    return ret

def get_string(n):
    rgb_int = rgb_to_int(n)
    return str(get_z(rgb_int)) + ',' + hex(rgb_int)

def path_leaf(path):
    head, tail = ntpath.split(path)
    return tail or ntphat.basename(head)

if (len(sys.argv) == 3):
    im = Image.open(sys.argv[1], 'r')
    pix_val = list(im.getdata())
    width, height = im.size
    tmp = width

    arr_name = path_leaf(sys.argv[1]).split('.')
    file_name = arr_name[0].lower() + '.fdf'
    print ("size(width x height):", width, "x", height, file_name)
    path_to_write = sys.argv[2]
    path_to_file = os.path.join(path_to_write, file_name)
    size = width * height
    i = 0
    map_img = []
    while i < size:
        coord = [get_string(x) for x in pix_val[i:i+width]]
        map_img.append(coord)
        i += width
    with open(path_to_file, 'w') as f:
        for i in range(height):
            f.write(" ".join(map_img[i]) + "\n")
else:
    print ("usage: python3 pixel.py [image path] [output path]")
#for file in isopoly_01_01-*.fdf; do mv "$file" "${file#isopoly_01_01-}";done
