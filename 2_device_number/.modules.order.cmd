cmd_/home/pi/driver/device_number/modules.order := {   echo /home/pi/driver/device_number/device_number.ko; :; } | awk '!x[$$0]++' - > /home/pi/driver/device_number/modules.order
