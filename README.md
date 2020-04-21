# Pickering ClientBridge/C++ Test program

Here is simple program that uses Pickering ClientBridge C/C++ library.


# Setup

Tested OS: Debian 10/amd64
* Ensure that build environment is installed using this command:
  ```
  sudo apt-get install build-essential
  ```

* Download latest ClientBridge binary, for example:
  ```
  curl -O http://downloads.pickeringtest.info/downloads/drivers/Sys60/Linux/ClientBridge/Debian/ClientBridge-1.20.0.3-amd64.deb
  ```
* install downloaded binary:
  ```
  dpkg -i ClientBridge-1.20.0.3-amd64.deb
  ```
* build this test program:
  ```
  make
  ```

# Running

To run this program you need target LXI device or LXI Simulator.

To test card on Bus=1 Slot=15 and LXI IP Address=192.168.10.38 you can
use this command:
```
./TestCB 192.168.10.38 1 15
```

# Resources

* [ClientBridge/C++ for Debian](http://downloads.pickeringtest.info/downloads/drivers/Sys60/Linux/ClientBridge/Debian)
* [LXI Simulator](http://downloads.pickeringtest.info/downloads/LXI_Simulator/)


