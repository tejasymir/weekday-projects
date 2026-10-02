import qrcode
from pathlib import Path

data = input("Enter the URL: ")

img = qrcode.make(data)

desktop_path = Path.home() / "Desktop"
file_path = desktop_path / "qr.png"

img.save(file_path)

if file_path.exists():
    print("QR Code Generated successfully")
else:
    print("QR Code generation failed")