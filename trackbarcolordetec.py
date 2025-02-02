import cv2
import numpy as np

def callback():
    pass

def init_trackbars():
    #HSV 
    # Bikin Window
    cv2.namedWindow('BGR Trackbar')
    cv2.createTrackbar('LB', 'BGR Trackbar', 0, 255, callback)
    cv2.createTrackbar('LG', 'BGR Trackbar', 0, 255, callback)
    cv2.createTrackbar('LR', 'BGR Trackbar', 0, 255, callback)

    cv2.createTrackbar('UH', 'BGR Trackbar', 255, 255, callback)
    cv2.createTrackbar('US', 'BGR Trackbar', 255, 255, callback)
    cv2.createTrackbar('UV', 'BGR Trackbar', 255, 255, callback)


def get_lower_hsv() :
    lower_hue= cv2.getTrackbarPos('LB', 'BGR Trackbar')
    lower_sat= cv2.getTrackbarPos('LG', 'BGR Trackbar')
    lower_val= cv2.getTrackbarPos('LR', 'BGR Trackbar')

    return (lower_hue, lower_sat, lower_val)

def get_upper_hsv() :
    upper_hue= cv2.getTrackbarPos('UH', 'BGR Trackbar')
    upper_sat= cv2.getTrackbarPos('US', 'BGR Trackbar')
    upper_val= cv2.getTrackbarPos('UV', 'BGR Trackbar')


    return (upper_hue, upper_sat, upper_val)


def main(video) :
    while True :
        ret, frame = video.read()
        hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)

        low = get_lower_hsv()
        high = get_upper_hsv()
        thresh = cv2.inRange(hsv, low, high)
        kernel = cv2.getStructuringElement(cv2.MORPH_ELLIPSE, (5,5))

        lower = np.array([low])
        upper = np.array([high])

        np.save('white_low_npy', lower)
        np.save('white_High_npy', upper)

        thresh = cv2.morphologyEx(thresh, cv2.MORPH_OPEN, kernel)
        contour, _ = cv2.findContours(thresh, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE) 

        if contour :
            largest_contour = max(contour,key=cv2.contourArea)

            x, y, w, h = cv2.boundingRect(largest_contour)

            cv2.rectangle(frame, (x, y), (w+x, h+y), (255, 0, 0), 2)

        cv2.imshow('hsv', hsv)
        cv2.imshow('thres', thresh)
        cv2.imshow('frame', frame)

        if cv2.waitKey(1) & 0xFF == ord('q') :
            break
if __name__ == '__main__' :
    cam = cv2.VideoCapture(0)
    init_trackbars()
    main(cam)