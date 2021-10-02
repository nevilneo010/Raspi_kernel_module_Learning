cmd_/home/pi/driver/4_gpio_drive/modules.order := {   echo /home/pi/driver/4_gpio_drive/gpiodri.ko; :; } | awk '!x[$$0]++' - > /home/pi/driver/4_gpio_drive/modules.order
