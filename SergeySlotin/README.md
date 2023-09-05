https://youtu.be/1RIPMQQRBWk?si=0cc4NbQIJ4EIHGVE

http://sereja.me/
https://github.com/sslotin


https://github.com/sslotin/awesome-algorithms

## steps
install hugo
https://gohugo.io/installation/
```bash

```

I will install it via snap,
### first I will install snap
https://snapcraft.io/docs/installing-snap-on-centos

```bash
sudo yum install snapd
```

Once installed, the systemd unit that manages the main snap communication socket needs to be enabled:
```bash
sudo systemctl enable --now snapd.socket

Created symlink from /etc/systemd/system/sockets.target.wants/snapd.socket to /usr/lib/systemd/system/snapd.socket.
```

To enable classic snap support, enter the following to create a symbolic link between /var/lib/snapd/snap and /snap:
```bash
sudo ln -s /var/lib/snapd/snap /snap
```

### Once we have snap, install hugo
```bash
sudo snap install hugo
```

I haven`t done this:

To enable or revoke access to removable media:
```bash
sudo snap connect hugo:removable-media
sudo snap disconnect hugo:removable-media
```
To enable or revoke access to SSH keys:
```bash
sudo snap connect hugo:ssh-keys
sudo snap disconnect hugo:ssh-keys
```
### hugo serve в корне репозитория
Выполнить hugo serve в корне репозитория 
и зайти на localhost:1313 для английской или localhost:1314 для русской версии (порты могут быть другие).