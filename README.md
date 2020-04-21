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
  sudo dpkg -i ClientBridge-1.20.0.3-amd64.deb
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
Example output from above command:
```
OK: Connected to '192.168.10.38:1024', SESSION=1587630255
OK: OpenSpecifiedCard at Bus=1, Slot=15. CardNum=1
OK: Card on Bus=1, Slot=15 has CardId='40-160-001,1000000,1.01'
```

# Resources

* [ClientBridge/C++ for Debian](http://downloads.pickeringtest.info/downloads/drivers/Sys60/Linux/ClientBridge/Debian)
* [LXI Simulator](http://downloads.pickeringtest.info/downloads/LXI_Simulator/)


