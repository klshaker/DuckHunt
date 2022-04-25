#!/bin/bash
echo "Mounting boot..."
mount /dev/mmcblk0p1 /mnt
echo "Mounted..."
echo "Copying files to boot..."
cp output_files/soc_system.rbf /mnt
cp soc_system.dtb /mnt
echo "Done copying..."
echo "Syncing..."
sync
echo "Done!"
