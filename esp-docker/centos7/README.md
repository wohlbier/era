# Docker files for

# BUILD
```bash
docker build -f <small/full>/Dockerfile -t <name>:<tag> ./
docker build -f small/Dockerfile --build-arg PROXY=${HTTP_PROXY} -t erademo:latest ./
```
# RUN
## Persistent container
```bash
docker run -uespuser -it <name>:<tag> /bin/bash
```
## Non-persistent container
```bash
docker run -uespuser --rm -it <name>:<tag> /bin/bash
```
## Graphical support non-persistent container
```bash
docker run -e DISPLAY --net=host -uespuser --rm -it <name>:<tag> /bin/bash
```
## Unix X11 Forward container
* Make sure ownger and group of .Xauthority file is set to uid:gid = 1000:1000 or
* change in the dockerfile the uid of espuser to your local uid
```bash
# put esp bitstream directories into era/esp-docker/centos7
[jgwohlbier@etc-gpu-09 centos7]$ pwd
/srv/data_local/jgwohlbier/era/esp-docker/centos7
[jgwohlbier@etc-gpu-09 centos7]$ ls -l
total 16
-rw-rw-r--. 1 jgwohlbier domain users 1296 Feb 10 10:45 README.md
drwxrwxr-x. 2 jgwohlbier domain users 4096 Feb  2 16:29 small
drwxr-xr-x. 7 jgwohlbier         1000 4096 Jan  8 22:11 vcu118-epochs1p-c5isr01
drwxr-xr-x. 7 jgwohlbier         1000 4096 Jan  8 22:12 vcu118-epochs1p-c5isr02

cp  ~/.Xauthority .
docker run -e UID=$(id -u) -e DISPLAY --privileged -v$(pwd)/.Xauthority:/home/espuser/.Xauthority -v/tools/Xilinx:/tools/Xilinx -v$(pwd)/vcu118-epochs1p-c5isr01:/home/espuser/esp/socs/vcu118-epochs1p-c5isr01 -v$(pwd)/vcu118-epochs1p-c5isr02:/home/espuser/esp/socs/vcu118-epochs1p-c5isr02  --net=host --rm -it erademo:latest

# for joining an already running container
docker ps
docker exec -it -u espuser <containerid> /bin/bash
```
# Troubleshooting
* If the build fails, try reducing the number of threads used in compilation in the Dockerfile lines 68/72 (default = 4)
