## Kubernetes Cluster run on a Swarm of Raspberry Pis
This project configures a swarm of raspberry pis to run a kubernetes cluster.

### Technologies
* Ansible (playbooks, galaxy, roles)
* Raspbian (Debian fork (aka "a Linux Operating System"))
* Linux tools & linux system configuration (woo!)
* BSD configuration (...aka "I used tools on OSX, which is a fork of BSD, therefore it counts as "more linux" lol")

### Setup SD card
---
* Download *Raspbian Lite* from the [Raspbian download page](https://www.raspberrypi.org/downloads/raspbian/) to a folder on your file system

    _Note: I downloaded my copy of the image into a folder in this repo, then `.gitignore`d it when I realized VCSing a large file isn't very cool. Feel free to download and extract your copy of raspbian lite to `./ansible/files`_

* From the following snippet, update the image path (if applicable) and then execute.

    ```bash
    RASPIAN_FILEPATH="$(pwd)/ansible/files/2019-09-26-raspbian-buster-lite.img"

    ansible-playbook ./ansible/playbooks/setup-sd-card.yml -K -e "{\"image_file_location\": \"$RASPIAN_FILEPATH\", \"remove_taint_file\": \"no\"}"
    ```

    _Note: Update `remove_taint_file` from `"no"` to `"yes"` if you are reflashing an SD card you have already flashed._ This feature was added because I wound up reflashing SD cards a few times ^^

### Initial Setup of Pi
---
* Insert SD cards into your PIs
* Connect ethernet cables to your PIs
* Modify and execute below snippet:

  ```bash
  TARGET_SSID=''
  TARGET_PSK=''

  ansible-playbook ./ansible/playbooks/initial-pi-configuration.yml -e "{\"network_ssid\": \"$TARGET_SSID\", \"network_psk\": \"$TARGET_PSK\"}" --ask-pass
  ```
* (optional) If you have a raspberry pi with a touchscreen installed, you can run this playbook to configure the touchscreen. This can be done over the network cables or over wifi.
  ```bash
  ansible-playbook ./ansible/playbooks/setup-pi-touchscreens.yml
  ```
* Disconnect the ethernet cables

### Setup Kubernetes
* Execute playbook...

    ``` bash
    ansible-playbook ./ansible/playbooks/setup-k3s.yml -vv
    ```
* The server needs to point at the IP address of a master node
* The node token will be in `~/.k8s-pi-cluster` directory

    ``` bash
    cat ~/.k8s-pi-cluster/192.168.8.200-node-token | pbcopy
    ```
* Test connection with k8s cluster by running...
    ``` bash
    KUBECONFIG="${HOME}/.k8s-pi-cluster/192.168.8.200-kubeconfig.yml" kubectl get pods --all-namespaces
    ```


### Tips
* Find the `MAC address` of your raspberry pi (intentionally ambiguous instruction). Once you have each pi's `MAC address`, go into your WIFI router's admin portal (intentionally ambiguous instruction), and reserve an `IP address` for each `MAC address` (intentionally ambiguous instruction).

    Now you know what IP address when your PI is configured on when your Raspberry PIs are on _that_ network!
* Each network interface has it's own MAC address (violating the "1 device, 1 mac address" simplification). `wlan0` (read: the WIFI network interface) MAC address != `eth0` (read: the physical ethernet connection network interface). Use `ifconfig` (or `ip` tool) and search `ether ` to find MAC addresses for each network interface.
* CAPS LOCK IS CRUISE CONTROL FOR COOL. This isn't applicable advice for this project but it is something to know.

### Resources
* Manual setup inspired by this medium article: https://medium.com/nycdev/k8s-on-pi-9cc14843d43
* Jeff Geerling's [How to build your own Raspberry Pi Cluster](https://www.jeffgeerling.com/blog/2017/how-build-your-own-raspberry-pi-cluster) series. (I wish I saw this earlier!)
* Jeff Geerling's [Raspberry Pi Dramble](https://github.com/geerlingguy/raspberry-pi-dramble) (link to the [pidramble](http://www.pidramble.com/) website) (Again, I wish I saw this earlier! I'll use the code for inspiration, especially since I recognize this github username from working with _Ansible_)

## Legacy Instructions
Manual SD card setup
1. Download *Raspbian Lite* from the [Raspbian download page](https://www.raspberrypi.org/downloads/raspbian/)
1. Download *Balena Etcher* (_etcher_) from either it's [web page](https://www.balena.io/etcher/) or from your package manager of choice (e.g. brew install balenaetcher)
1. Start etcher, select Raspbian Lite as the image to flash. Plug in a target SD card and flash with Raspbian Lite. Repeat for each SD card you want to flash.
1. `touch` a file named `ssh` in the root of the SD card.

    I used windows, and git bash -- here is the snippet I run for each SD card:

    `cd /d/ && touch ssh && ls -la | grep "ssh" && cd /c/`
1. Install the SD cards and wire up your pis (ethernet cable, power).
1. Find the IP address assigned to your pi by your router (via DHCP), perhaps using your router's admin page?

