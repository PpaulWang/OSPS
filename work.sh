#!/binin/bash
g++ -o OSPS src/OSPS_old.cpp
./OSPS 10 IDW_10.txt data/IDW/x_IDW.txt data/IDW/y_IDW.txt data/IDW/z_IDW.txt
./OSPS 20 IDW_20.txt data/IDW/x_IDW.txt data/IDW/y_IDW.txt data/IDW/z_IDW.txt
./OSPS 30 IDW_30.txt data/IDW/x_IDW.txt data/IDW/y_IDW.txt data/IDW/z_IDW.txt
./OSPS 10 Krig_10.txt data/Krig/x_krig.txt data/Krig/y_krig.txt data/Krig/z_krig.txt
./OSPS 20 Krig_20.txt data/Krig/x_krig.txt data/Krig/y_krig.txt data/Krig/z_krig.txt
./OSPS 30 Krig_30.txt data/Krig/x_krig.txt data/Krig/y_krig.txt data/Krig/z_krig.txt

