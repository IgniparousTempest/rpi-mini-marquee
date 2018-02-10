#!/usr/bin/env bash
trap "exit" INT

# Install prerequisites
sudo apt-get update
sudo apt-get -y install libsdl2-image-dev

# Make executable
rm -rf ./build/
cmake -B./build/ -H.
cd build/
make
cd ..

# Move executable to /usr/bin
sudo rm -f /usr/bin/rpi-mini-marquee
sudo mv ./build/rpi-mini-marquee /usr/bin/

# Copies runcommand scripts
cp runcommand-onstart.sh /opt/retropie/configs/all/
cp runcommand-onend.sh /opt/retropie/configs/all/

# Copies marquees
sudo rm -rf /usr/share/rpi-mini-marquee
sudo mkdir /usr/share/rpi-mini-marquee
sudo cp -R marquees /usr/share/rpi-mini-marquee/.

# Clean up
rm -rf ./build/