#!/usr/bin/env bash
trap "exit" INT

# Create binary
sudo cp rpi-mini-marquee.py /usr/bin/rpi-mini-marquee
sudo chmod +x /usr/bin/rpi-mini-marquee

# User files
sudo mkdir /usr/share/rpi-mini-marquee/
sudo cp -R marquees /usr/share/rpi-mini-marquee/

# Add emulationstation runcommand files
#! /bin/bash -
if [[ ! -e /opt/retropie/configs/all/runcommand-onstart.sh ]]; then
    echo -e '#!/bin/bash' > /opt/retropie/configs/all/runcommand-onstart.sh
fi
echo -e '\n# Changes the mini marquee on game start, $1 is the system name' >> /opt/retropie/configs/all/runcommand-onstart.sh
echo -e '/usr/bin/rpi-mini-marquee -f $1' >> /opt/retropie/configs/all/runcommand-onstart.sh

#! /bin/bash -
if [[ ! -e /opt/retropie/configs/all/runcommand-onend.sh ]]; then
    echo -e '#!/bin/bash' > /opt/retropie/configs/all/runcommand-onend.sh
fi
echo -e '\n# Changes the mini marquee on game start' >> /opt/retropie/configs/all/runcommand-onend.sh
echo -e '/usr/bin/rpi-mini-marquee -f retropie' >> /opt/retropie/configs/all/runcommand-onend.sh

# Create service
sudo cp rpimm.sh /etc/init.d/
sudo chmod +x /etc/init.d/rpimm.sh
sudo update-rc.d rpimm.sh defaults
