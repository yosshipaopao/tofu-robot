import cv2
import os
import numpy as np

def convert_16(i:int)->list[int]:
    ans = []
    ans.append(i>>8)
    ans.append(i&((1<<8)-1))
    return ans

base_folder = "assets/parts"
save_folder = "data/img"

folders = [""] + [
    f for f in os.listdir(base_folder) if os.path.isdir(os.path.join(base_folder, f))
]

for fo in folders:
    current_folder = os.path.join(base_folder, fo)
    files = [
        f
        for f in os.listdir(current_folder)
        if os.path.isfile(os.path.join(current_folder, f)) and f.endswith(".bmp")
    ]
    os.makedirs(os.path.join(save_folder,fo), exist_ok=True)
    for f in files:
        file = os.path.join(current_folder, f)
        id = os.path.join(fo, f)[:-4]
        data = []
        img = cv2.imread(file, cv2.IMREAD_GRAYSCALE)
        h,w = img.shape
        data += convert_16(h)
        data += convert_16(w)
        img = img.ravel()
        data += [i for i in img]
        print(w,h)
        with open(os.path.join(save_folder,id),mode="wb") as F:
           F.write(bytes(data))
        
