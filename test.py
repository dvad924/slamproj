import numpy as np
import cv2
import urllib
import time

def url_to_image(url):
    resp = urllib.urlopen(url)
    image = np.asarray(bytearray(resp.read()),dtype='uint8')
    image = cv2.imdecode(image,cv2.IMREAD_COLOR)

    return image




cap = cv2.VideoCapture();
cap.open('http://localhost:4747/mjpegfeed?960x720')
cap.set(cv2.cv.CV_CAP_PROP_BUFFERSIZE,3)
while (True):
    ret,frame = cap.read()

    cv2.imshow('frame',frame)

    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()

# while(1):
#     start = time.time()
#     frame = url_to_image('http://localhost:4747/shot.jpg');
#     print 'getting {} fps'.format(1.0/(time.time() - start))
#     cv2.imshow('frame',frame);
#     cv2.waitKey(10);

    

