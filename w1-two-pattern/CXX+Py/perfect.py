# -*- coding: utf-8 -*-
import os, sys, time, subprocess, glob

def ready():
    os.system('modprobe w1-gpio')
    os.system('modprobe w1-therm')
    base_dir = '/sys/bus/w1/devices/'
    device_folder = glob.glob(base_dir + '28*')[0]
    device_file = device_folder + '/w1_slave'
    return device_file

def w1(device_file):
    catdata = subprocess.Popen(['cat', device_file], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    out, err = catdata.communicate()
    out_decode = out.decode('utf-8')
    lines = out_decode.split('\n')
    while lines[0].strip()[-3:] != 'YES':
	time.sleep(1)
	lines = read_temp_raw()
    equals_pos = lines[1].find('t=')
    if (equals_pos != -1):
	temp_string = lines[1][equals_pos + 2:]
	temp_c = float(temp_string) / 1000.0
	return temp_c
	    
if __name__ == '__main__':
    data = ready()
    while True:
        res = w1(data)
        print(res)
