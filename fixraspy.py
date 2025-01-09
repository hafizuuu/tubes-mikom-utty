import cv2
import pytesseract
from pytesseract import Output
import serial
import time

#komunikasi serial dengan Arduino
arduino = serial.Serial('/dev/ttyUSB0', 9600) 
time.sleep(2)

#buka kamera
cap = cv2.VideoCapture(0)
cap.set(cv2.CAP_PROP_BUFFERSIZE, 1)

while True:
    # Capture frame-by-frame
    ret, frame = cap.read()
    if not ret:
        continue

    #Tesseract untuk membaca teks
    d = pytesseract.image_to_data(frame, output_type=Output.DICT, lang='eng')
    n_boxes = len(d['text'])

    for i in range(n_boxes):
        if int(d['conf'][i]) > 60:  # Confidence threshold
            (text, x, y, w, h) = (
                d['text'][i],
                d['left'][i],
                d['top'][i],
                d['width'][i],
                d['height'][i],
            )
            # Jangan tampilkan teks kosong
            if text and text.strip() != "":
                frame = cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)
                frame = cv2.putText(
                    frame,
                    text,
                    (x, y - 10),
                    cv2.FONT_HERSHEY_SIMPLEX,
                    0.5,
                    (0, 255, 0),
                    2,
                )

                if "D333A" in text:  
                    arduino.write(b'1') 
                    print("Plat nomor terdeteksi:", text)
                else:
                    arduino.write(b'0') 
                    print("Plat nomor tidak terdeteksi")

    cv2.imshow('frame', frame)
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
arduino.close()
