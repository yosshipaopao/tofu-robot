import cv2
import os
import numpy as np
from itertools import groupby


def convert_16(i: int) -> list[int]:
    ans = []
    ans.append(i >> 8)
    ans.append(i & ((1 << 8) - 1))
    return ans


base_folder = "assets/parts"
save_folder = "data/img"

folders = [""] + [
    f for f in os.listdir(base_folder) if os.path.isdir(os.path.join(base_folder, f))
]

# 0 is not complessed and 1byte color(gray scale)

for fo in folders:
    current_folder = os.path.join(base_folder, fo)
    files = [
        f
        for f in os.listdir(current_folder)
        if os.path.isfile(os.path.join(current_folder, f)) and f.endswith(".bmp")
    ]
    os.makedirs(os.path.join(save_folder, fo), exist_ok=True)
    for f in files:
        file = os.path.join(current_folder, f)
        id = os.path.join(fo, f)[:-4]
        img = cv2.imread(file, cv2.IMREAD_GRAYSCALE)
        h, w = img.shape
        img = [i >> 3 for i in img.ravel()]
        n = len(img)

        rawdata = [0]
        rawdata += convert_16(h)
        rawdata += convert_16(w)
        rawdata += [i for i in img]

        tmp = [[i, len(list(v))] for i, v in groupby(img)]

        conpressed_data = [2] + convert_16(h) + convert_16(w)
        for i, v in tmp:
            while v // 0b100000000 != 0:
                conpressed_data += [i, 0b11111111]
                v -= 256
            if v != 0:
                conpressed_data += [i, v - 1]

        tmp = [[i, len(list(v))] for i, v in groupby(img)]
        easyconpressed_data = [4] + convert_16(h) + convert_16(w)
        for i, v in tmp:
            while v // 8 != 0:
                easyconpressed_data += [(i << 3) + 0b111]
                v -= 8
            if v != 0:
                easyconpressed_data += [(i << 3) + (v - 1)]
        # check

        size = conpressed_data[2] * conpressed_data[4]

        check_comp = conpressed_data[5:]
        data = []
        for i in range(0, len(check_comp), 2):
            data += [check_comp[i]] * (check_comp[i + 1] + 1)
        print(np.all(data == img))

        # check 2

        check_easycomp = easyconpressed_data[5:]
        data = []
        for i in range(len(check_easycomp)):
            data += [check_easycomp[i] >> 3] * ((check_easycomp[i] & 0b111) + 1)
        print(data == [i >> 3 for i in img])

        braw = bytearray(rawdata)
        bcomp = bytearray(conpressed_data)
        becomp = bytearray(easyconpressed_data)

        print(len(braw), len(bcomp), len(becomp))

        with open(os.path.join(save_folder, id), mode="wb") as F:
            if len(braw) > len(bcomp) and len(bcomp) > len(becomp):
                F.write(becomp)
            elif len(braw) > len(bcomp):
                F.write(bcomp)
            else:
                F.write(braw)
