cmd_/home/pi/driver/3_auto_device_file/modules.order := {   echo /home/pi/driver/3_auto_device_file/autodev.ko; :; } | awk '!x[$$0]++' - > /home/pi/driver/3_auto_device_file/modules.order
