# Hello World Example
#
# Welcome to the MaixPy IDE!
# 1. Conenct board to computer
# 2. Select board at the top of MaixPy IDE: `tools->Select Board`
# 3. Click the connect buttion below to connect board
# 4. Click on the green run arrow button below to run the script!


import sensor, image, time, lcd ,math
import KPU as kpu
from fpioa_manager import fm
from machine import UART
from board import board_info

lcd.init(freq=15000000)
sensor.reset()                      # Reset and initialize the sensor. It will
                                    # run automatically, call sensor.run(0) to stop
sensor.set_pixformat(sensor.RGB565) # Set pixel format to RGB565 (or GRAYSCALE)
sensor.set_framesize(sensor.QVGA)   # Set frame size to QVGA (320x240)
sensor.set_hmirror(1)#设置水平镜像
sensor.set_vflip(1)#设置垂直翻转
sensor.skip_frames(time = 2000)     # Wait for settings take effect.

clock = time.clock()                # Create a clock object to track the FPS.

#定义串口引脚
fm.register(24,fm.fpioa.UART2_TX)
fm.register(25,fm.fpioa.UART2_RX)
uart = UART(UART.UART2,115200,8,0,0,timeout=1000,read_buf_len=1)

white_threshold=(13, 52, 10, 44, -3, 24)
white_roi=(0,29,223,53)
right_roi=(29,0,58,240)
left_roi=(201,0,58,240)
pull_down_roi1=(0,193,321,35)
pull_down_roi2=(0,67,321,35)


milk_roi=(2,89,320,53)
milk_left_roi=(0,0,61,99)
milk_right_roi=(254,0,61,99)
milk_stop_roi=(0,47,320,48)

reg_roi=(0,108,320,53)
line_mid=0#直走巡线值
right_line_mid=0#右走巡线值
left_line_mid=0#左走巡线值


cross_flag=0
flag_temp1=0
flag_temp2=0
flag_temp3=0



#串口发送函数
def uart_send():
    global line_mid,right_line_mid,left_line_mid,cross_flag

    uart.write('a')#帧头
    time.sleep_ms(1)
    uart.write(line_mid.to_bytes(1, 'little'))
    time.sleep_ms(1)
    uart.write(right_line_mid.to_bytes(1, 'little'))
    time.sleep_ms(1)
    uart.write(left_line_mid.to_bytes(1, 'little'))
    time.sleep_ms(1)
    uart.write(cross_flag.to_bytes(1, 'little'))
    time.sleep_ms(1)
    uart.write('z')#帧尾
    print('line_mid:',line_mid,'right_line_mid',right_line_mid,'left_line_mid',left_line_mid,'cross_flag',cross_flag)


#寻找最大色块函数定义
def find_max(blobs):
    max_size=0
    for blob in blobs:
        if blob[2]*blob[3] > max_size:
            max_blob=blob
            max_size = blob[2]*blob[3]
    return max_blob

#放下箱子时的巡线函数
def go_line():
    global line_mid,right_line_mid,left_line_mid,cross_flag
    while(True):
        flag1=0
        flag2=0
        flag3=0
        cross_flag=0
        left_line_mid=0
        img = sensor.snapshot()         # Take a picture and return the image.
        line = img.get_regression([(13, 52, 10, 44, -3, 24)], robust = True,roi=reg_roi)
        if line:
            img.draw_line(line.line(),(255,0,0))
            line_mid=line.theta()
            if line.theta()>90:
                line_mid = line.theta()-180
            else:
                line_mid = line.theta()
            line_mid=line_mid+180
        blobs = img.find_blobs([white_threshold],roi=milk_roi,invert=False,x_stride=20,y_stride=20,pixel_threshold=20)
        if blobs:
            max_blob = find_max(blobs)#调用函数，返回最大色块
            #tmp=img.draw_rectangle(max_blob[0:4])
            flag1=1
            right_line_mid=max_blob.cx()#右走巡线值

        blobs = img.find_blobs([white_threshold],roi=milk_left_roi,invert=False,x_stride=20,y_stride=20,pixel_threshold=20)
        if blobs:
            max_blob = find_max(blobs)#调用函数，返回最大色块
            tmp=img.draw_rectangle(max_blob[0:4])
            flag2=1


        blobs = img.find_blobs([white_threshold],roi=milk_right_roi,invert=False,x_stride=20,y_stride=20,pixel_threshold=20)
        if blobs:
            max_blob = find_max(blobs)#调用函数，返回最大色块
            tmp=img.draw_rectangle(max_blob[0:4])
            flag3=1

        blobs = img.find_blobs([white_threshold],roi=milk_stop_roi,invert=False,x_stride=2,y_stride=2,pixel_threshold=20)
        if blobs:
            max_blob = find_max(blobs)#调用函数，返回最大色块
            left_line_mid=1
            tmp=img.draw_rectangle(max_blob[0:4])

        if flag1 and flag2 and flag3:
            cross_flag=1
        uart_send()



        if left_line_mid==0:#结束后标志位置1,退出循环
            break




#go_line()

while(True):

    temp1_cx=0
    temp2_cx=0
    temp3_cx=0
    temp_cy=0

    flag_temp1=0
    flag_temp2=0
    flag_temp3=0
    cross_flag=0

    img = sensor.snapshot()         # Take a picture and return the image.
    blobs = img.find_blobs([white_threshold],roi=white_roi,invert=False,x_stride=20,y_stride=20,pixel_threshold=20)
    if blobs:
        flag_temp1=1
        max_blob = find_max(blobs)#调用函数，返回最大色块
        tmp=img.draw_rectangle(max_blob[0:4])
        line_mid=max_blob.cx()#巡线值
        temp1_cx=max_blob.cx()
        temp_cy=max_blob.cy()
        #print(line_mid,temp_cy)


    blobs = img.find_blobs([white_threshold],roi=right_roi,invert=False,x_stride=20,y_stride=20,pixel_threshold=20)
    if blobs:
        flag_temp2=1
        max_blob = find_max(blobs)#调用函数，返回最大色块
        tmp=img.draw_rectangle(max_blob[0:4])
        right_line_mid=max_blob.cy()#右走巡线值
        temp2_cx=max_blob.cx()



    blobs = img.find_blobs([white_threshold],roi=left_roi,invert=False,x_stride=20,y_stride=20,pixel_threshold=20)
    if blobs:
        flag_temp3=1
        max_blob = find_max(blobs)#调用函数，返回最大色块
        tmp=img.draw_rectangle(max_blob[0:4])
        left_line_mid=max_blob.cy()#左走巡线值
        temp3_cx=max_blob.cx()



    if flag_temp1 and flag_temp2 and flag_temp3 and temp3_cx>temp1_cx and temp1_cx>temp2_cx and abs(temp3_cx-temp1_cx)>=5 and abs(temp2_cx-temp1_cx)>=5  and abs(temp_cy-right_line_mid)>5 and abs(temp_cy-left_line_mid)>5:
        cross_flag=1
    else:
        cross_flag=0
    uart_send()
    lcd.display(img)


    uart_get=uart.read(1)#stm32发送一个'z',进入放箱子流程,找到位置后退出
    print(uart_get)
    if uart_get==b'z':
        go_line()

