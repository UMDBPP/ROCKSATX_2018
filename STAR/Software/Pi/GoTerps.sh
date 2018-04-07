sudo mount /dev/sda1 USBDRIVE
cd USBDRIVE
n=0
while ! mkdir dir$n
do
	n=$((n+1))
done
cp ../RecordVideo.py "dir$n"
cd "dir$n"
sudo python RecordVideo.py