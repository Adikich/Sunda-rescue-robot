import cv2
import requests
import time
import os
from ultralytics import YOLO

# Telegram Bot Credentials
BOT_TOKEN = "your_new_bot_token_here"
CHAT_ID = "your_new_chat_id_here"

# Load YOLOv8 Model (pre-trained for object detection)
model = YOLO("yolov8n.pt")  # Uses YOLOv8 nano model (small & fast)

# Function to send a photo to Telegram
def send_photo(image_path):
    url = f"https://api.telegram.org/bot{BOT_TOKEN}/sendPhoto"
    with open(image_path, "rb") as photo:
        requests.post(url, data={"chat_id": CHAT_ID}, files={"photo": photo})

while True:
    time.sleep(15)  # Wait 15 seconds

    # Open Camera & Capture Image
    cap = cv2.VideoCapture(0)
    cap.set(3, 640)  # Set width to 640px
    cap.set(4, 480)  # Set height to 480px
    ret, frame = cap.read()
    cap.release()  # Release camera immediately after capture

    if not ret:
        print("Failed to capture image!")
        continue

    # Run object detection
    results = model(frame)

    # Draw bounding boxes & labels
    detected = False
    for result in results:
        for box in result.boxes:
            if box.conf[0] < 0.5:  # Ignore weak detections (confidence < 50%)
                continue

            x1, y1, x2, y2 = map(int, box.xyxy[0])  # Bounding box
            label = result.names[int(box.cls[0])]  # Object name

            # Draw rectangle and label
            cv2.rectangle(frame, (x1, y1), (x2, y2), (0, 255, 0), 2)
            cv2.putText(frame, label, (x1, y1 - 10), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (0, 255, 0), 2)
            
            if label == "person":  # Check if a human is detected
                detected = True

    # Save image with a unique name
    timestamp = int(time.time())  # Get current timestamp
    image_path = f"detected_photo_{timestamp}.jpg"
    cv2.imwrite(image_path, frame)

    if detected:  # Only send if a human is detected
        send_photo(image_path)
        print(f"Annotated photo sent to Telegram: {image_path}")

    # Delete old images to save space
    for file in os.listdir("."):
        if file.startswith("detected_photo_") and file != image_path:
            os.remove(file)
