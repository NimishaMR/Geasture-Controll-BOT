from pywebio.input import *
from pywebio.output import *

import serial
import time
import cv2
import os
import HandTrackingModule as hm
import argparse
from pywebio import start_server

wCam, hCam = 640, 480

cap = cv2.VideoCapture(0, cv2.CAP_DSHOW)
cap.set(3, wCam)
cap.set(4, hCam)

#folderPath = "Images"
#myList = os.listdir(folderPath)
#print(myList)
overlayList = []

#print(len(overlayList))
pTime = 0

detector = hm.handDetector(detectionCon=0.75)

totalFingers_prev=-1
check=0
tipIds = [4, 8, 12, 16, 20]
com=input("ENTER THE COM PORT BLUETOOTH IS CONNECTED")

if __name__=='__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument("-p", "--port", type=int, default=8080)
    args = parser.parse_args()

    start_server(predict, port=args.port)
    ser =serial.Serial(com,9600,timeout=5)
    ser.flush()
    popup(com,'You have chosen'+str(com)+' .Please Ensure that that is the COM Port that your device has assigned as output Port to the Bluetooth Module')
    while True:
        success, img = cap.read()
        img = detector.findHands(img)
        lmList = detector.findPosition(img, draw=False)
        # print(lmList)

        if len(lmList) != 0:
            fingers = []

            # Thumb
            if lmList[tipIds[0]][1] > lmList[tipIds[0] - 1][1]:
                fingers.append(1)
            else:
                fingers.append(0)

            # 4 Fingers
            for id in range(1, 5):
                if lmList[tipIds[id]][2] < lmList[tipIds[id] - 2][2]:
                    fingers.append(1)
                else:
                    fingers.append(0)

            # print(fingers)
            totalFingers = fingers.count(1)
    


        #add delay library 
        

            #cv2.rectangle(img, (20, 225), (170, 425), (255, 255, 255), cv2.FILLED)
            cv2.putText(img, str(totalFingers), (45, 375), cv2.FONT_HERSHEY_PLAIN,10, (0, 0, 0), 25)
            if totalFingers_prev != totalFingers:
                check=check+1
                #time.sleep(0.25)
                print(totalFingers)
                if check>3:
                    ser.write(str(totalFingers).encode('utf-8'))
                    print("Sent the Number :",str(totalFingers))
                    put_text("Sent the Number :",str(totalFingers))
                    totalFingers_prev = totalFingers
                    time.sleep(0.5)
                    check=0
        cTime = time.time()
        fps = 1 / (cTime - pTime)
        pTime = cTime


        cv2.putText(img, f'FPS: {int(fps)}', (400, 70), cv2.FONT_HERSHEY_PLAIN,
                    3, (255, 0, 0), 3)
                    

        footage=cv2.imshow("Image", img)
        footage
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break
        


    cv2.destroyAllWindows()
    cap.release()
