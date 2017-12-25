#!/usr/bin/env python
# coding: UTF-8

import sys, re, unicodedata

def main():
    while True:
        set_num = raw_input('[0-9]: ')
        if set_num.isdigit():
            break
    f = open('Merger.h', "r")
    lines = f.readlines()
    f.close()
    f2 = open('Merger.h', 'w')
    result_lines = ''
    for line in lines:
        if re.search('InPortNum = [0-9]', line) != None:
            result = re.sub('[0-9]', set_num, line)
            print(result)
            result_lines += result
        else:
            result_lines += line
    f2.write(result_lines)
    f2.close()

if __name__ == '__main__':
    main()