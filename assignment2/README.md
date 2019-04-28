
1: Open folder and enter make all command

2: To insert module -->  sudo insmod main.ko

3: Verify module---> lsmod

4: For the partition information check using cat /proc/partitions also ls -l /dev/diskonram* or sudo fdisk -l

5: Give permission by typing sudo chmod 777 /dev/diskonram*

6: 2 logical Parititions of the Device : diskonram1 and diskonram2 each of 255.5KB and 256KB

7: Write into file using use cat > /dev/diskonram1 ,to check contents use --> xxd /dev/diskonram1 | less

8: unload module --> sudo rmmod main.ko



