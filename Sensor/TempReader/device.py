import os, sys, time, subprocess, glob
os.system('modprobe w1-gpio')
os.system('modprobe w1-therm')


def ready():
    print('start')
    base_dir = '/sys/bus/w1/devices/'
    device_folder = glob.glob(base_dir + '28*')[0]
    device_file = device_folder + '/w1_slave'
    return device_file


def w1(df):
    cat = subprocess.Popen(
        ['cat', df],
        stdout=subprocess.PIPE,
        stderr=subprocess.PIPE)
    out, err = cat.communicate()
    out_decode = out.decode('utf-8')
    lines = out_decode.split('\n')
    equals_pos = lines[1].find('t=')
    if (equals_pos != -1):
        temp_string = lines[1][equals_pos + 2:]
        temp_c = float(temp_string) / 1000.0
        temp = str(temp_c)
        return temp