cmd_/home/pi/driver/hello_module_1/modules.order := {   echo /home/pi/driver/hello_module_1/hello.ko; :; } | awk '!x[$$0]++' - > /home/pi/driver/hello_module_1/modules.order
