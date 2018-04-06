import picamera
import time

with picamera.PiCamera() as camera:
    dataname = 'frametimes.dat'
    filelength = 15 #seconds
    datafile = open(dataname, 'a+')
    datafile.write('Starting\n')
    datafile.close()
    camera.annotate_foreground = picamera.Color(y=1, u=0, v=0)
    camera.annotate_background = picamera.Color(y=0, u=0, v=0)
    camera.annotate_frame_num = True
    camera.resolution = (1640, 1232)
    camera.framerate = 30
    numfiles = 60*60//filelength #Record for 60 minutes
    datatime = filelength-1/80
    waittime = 1/160
    for filename in camera.record_sequence(('video%04d.h264' %i for i in range(1, numfiles)), 'h264'):
        start = time.time()
        data = ''
        print 'Starting ', filename
        while (time.time()-start) < datatime:
            frame = camera.frame
            num = frame.index
            frame_time_start = frame.timestamp
            data = data + filename + ',' + str(num) + ',' + str(frame_time_start) + '\n'
            camera.wait_recording(waittime)
        datafile = open(dataname, 'a+')
        datafile.write(data)
        datafile.close()
    camera.close()
