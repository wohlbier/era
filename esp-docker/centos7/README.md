# Docker files for

# BUILD
```bash
docker build -f <small/full>/Dockerfile -t <name>:<tag> ./
docker build -f small/Dockerfile --build-arg LOCAL_UID=$(id -u $USER) --build-arg LOCAL_GID=$(id -g $USER) --build-arg PROXY=${HTTP_PROXY} -t erademo:<moniker> ./
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
cp  ~/.Xauthority .
docker run -e DISPLAY -v $(pwd)/.Xauthority:/home/espuser/.Xauthority -v/bigdisk/packages/Xilinx:/bigdisk/packages/Xilinx --net=host -uespuser --rm -it erademo:<moniker> /bin/bash
docker run -e DISPLAY --net=host -uespuser --rm -it erademo:v0 /bin/bash
```
# Troubleshooting
* If the build fails, try reducing the number of threads used in compilation in the Dockerfile lines 68/72 (default = 4)
