#!/bin/bash
g++ -o OSPS src/OSPS_time.cpp
./OSPS 30 time1.txt data/IDW/x_IDW.txt data/IDW/y_IDW.txt data/IDW/z_IDW.txt 3
./OSPS 30 time2.txt data/IDW/x_IDW.txt data/IDW/y_IDW.txt data/IDW/z_IDW.txt 2
./OSPS 30 time3.txt data/IDW/x_IDW.txt data/IDW/y_IDW.txt data/IDW/z_IDW.txt 1
./OSPS 30 time4.txt data/IDW/x_IDW.txt data/IDW/y_IDW.txt data/IDW/z_IDW.txt 0

#./OSPS 30 time1.txt data/Krig/x_krig.txt data/Krig/y_krig.txt data/Krig/z_krig.txt 3
#./OSPS 30 time2.txt data/Krig/x_krig.txt data/Krig/y_krig.txt data/Krig/z_krig.txt 2
#./OSPS 30 time3.txt data/Krig/x_krig.txt data/Krig/y_krig.txt data/Krig/z_krig.txt 1
#./OSPS 30 time4.txt data/Krig/x_krig.txt data/Krig/y_krig.txt data/Krig/z_krig.txt 0
