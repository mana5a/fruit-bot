import cv2
import numpy as np
#import cv2.cv as cv
import time
import serial
ser = serial.Serial('/COM4', 9600)  #replace with actual arduino port

cap = cv2.VideoCapture(1)
while(1):
#Capture a frame
    ret, frame = cap.read()
    (a,b,c)=frame.shape
    midx=b/2
    l_b=midx-30
    r_b=midx+30
#Convert BGR to HSV
    hsv = cv2.cvtColor(frame,cv2.COLOR_BGR2HSV)
#Define range of desired color in HSV
    lower_orange = np.array([0,2,108])
    upper_orange = np.array([87,255,255])



#Threshold the HSV image to get desired color
    mask = cv2.inRange(hsv, lower_orange, upper_orange)
#Bitwise-AND mask and original image
    res = cv2.bitwise_and(frame,frame, mask= mask)
#Morphological operations
    kernel = np.ones((5,5),np.uint8)
    erosion = cv2.erode(mask,kernel,iterations = 1)
    dilation = cv2.dilate(mask,kernel,iterations = 1)
    opening = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
    closing = cv2.morphologyEx(mask, cv2.MORPH_CLOSE, kernel)



# Detect circles using HoughCircles
    circles =cv2.HoughCircles(closing,cv2.HOUGH_GRADIENT,2,120,param1=100,param2=55,minRadius=10,maxRadius=0)

#Draw Circles
    if circles is not None:
        for i in circles[0,:]:
            # If the ball is far, draw it in green
                cv2.circle(frame,(int(round(i[0])),int(round(i[1]))),int(round(i[2])),(255,0,0),4)
                cv2.circle(frame,(int(round(i[0])),int(round(i[1]))),1,(0,255,0),4)
                x=int(round(i[0]))  #pass the difference in the positions to the arduino
                rads=int(round(i[2]))
                #y=midy-int(round(i[0]))
                if(rads<80):
                    rest='f'
                    ser.write(str(rest))
                else:
                    if(l_b<x<r_b and rads>80):
                        rest='s'
                        ser.write(str(rest))
                        ser.sendBreak(duration=4.3)
                    elif(x>r_b):
                        rest='l'
                        ser.write(str(rest))
                    elif(x<l_b):
                        rest='r'
                        ser.write(str(rest))
                print l_b,r_b,"x:",x,"r:",rads,rest
                

    cv2.imshow('tracking',frame)
    cv2.imshow('Original',frame)
    cv2.imshow('Mask',mask)
    cv2.imshow('Result',res)
    k = cv2.waitKey(5) & 0xFF
    if k == 27:
            break
cv2.destroyAllWindows()
cap.release()

