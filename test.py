import numpy as np
import cv2
import urllib
import time

def url_to_image(url):
    resp = urllib.urlopen(url)
    image = np.asarray(bytearray(resp.read()),dtype='uint8')
    image = cv2.imdecode(image,cv2.IMREAD_COLOR)

    return image










t = time.time()
numimages = 0
while(1):
    start = time.time()
    frame = url_to_image('http://192.168.0.6:8080/shot.jpg');
    numimages += 1
    if time.time()- t > 1:
        print 'getting {} fps'.format(numimages)
        t = time.time()
        numimages = 0
    cv2.imshow('frame',frame);
    cv2.waitKey(10);

    

