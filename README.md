Commands run during the kubernetes (k8s) raspberry pi (pi) cluster setup.

This setup guide is based on this medium article: https://medium.com/nycdev/k8s-on-pi-9cc14843d43

### Setup SD card
1. Download *Raspbian Lite* from the [Raspbian download page](https://www.raspberrypi.org/downloads/raspbian/)
1. Download *Balena Etcher* (_etcher_) from either it's [web page](https://www.balena.io/etcher/) or from your package manager of choice (e.g. brew install balenaetcher)
1. Start etcher, select Raspbian Lite as the image to flash. Plug in a target SD card and flash with Raspbian Lite. Repeat for each SD card you want to flash.
1. `touch` a file named `ssh` in the root of the SD card.

    I used windows, and git bash -- here is the snippet I run for each SD card:

    `cd /d/ && touch ssh && ls -la | grep "ssh" && cd /c/`
1. Install the SD cards and wire up your pis (ethernet cable, power).
1. Find the IP address assigned to your pi by your router (via DHCP), perhaps using your router's admin page?

### Initial Setup
1. SSH into pi(s).
1. (optional) Output raspberry pi model and it's RAM count
    ```
    cat /proc/device-tree/model && echo && free -m
    ```
1. (optional) Verify that swap is enabled
    ```
    sudo swapon --summary
    ```
1. Disable swap files:
    ```
    sudo dphys-swapfile swapoff && \
    sudo dphys-swapfile uninstall && \
    sudo update-rc.d dphys-swapfile remove
    ```
1. Edit `/boot/cmdline.txt` to add line `cgroup_enable=cpuset cgroup_memory=1 cgroup_enable=memory`
1. Reboot pi `sudo reboot`
1. Edit `/etc/apt/sources.list.d/kubernetes.list` to add in line `deb http://apt.kubernetes.io/ kubernetes-xenial main`
1. Add `apt-key.gpg` from internet `curl -s https://packages.cloud.google.com/apt/doc/apt-key.gpg | sudo apt-key add -`
1. Run `rpi-update` to update the raspberry pi firmware. This is required for installing weave net.
1. Alias `kubectl` to `k` by editing the `.bashrc` file in the home folder (`~` or `$HOME`) and adding `alias k=kubectl`.
1. Repeatedly disable swap files after any reboots
    ```
    sudo dphys-swapfile swapoff && \
    sudo dphys-swapfile uninstall && \
    sudo update-rc.d dphys-swapfile remove
    ```

