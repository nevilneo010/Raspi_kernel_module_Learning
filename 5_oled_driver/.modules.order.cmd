cmd_/home/pi/driver/5_oled_driver/modules.order := {   echo /home/pi/driver/5_oled_driver/oleddri.ko; :; } | awk '!x[$$0]++' - > /home/pi/driver/5_oled_driver/modules.order
