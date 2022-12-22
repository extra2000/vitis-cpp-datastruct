# vitis-cpp-datastruct

| License | Versioning |
| ------- | ---------- |
| [![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT) | [![semantic-release](https://img.shields.io/badge/%20%20%F0%9F%93%A6%F0%9F%9A%80-semantic--release-e10079.svg)](https://github.com/semantic-release/semantic-release) |

C++ Data Structure with Vitis.


## Preprequisites

* Host: GNU/Linux only
* Container: Podman `3.4.7` and above. Make sure to configure for rootless.
* Target board: `digilentinc.com:arty-z7-20:part0:1.1`.
* Vivado 2022.1 and above installed via Flatpak.
* [petalinux-builder v1.2.0](https://github.com/extra2000/petalinux-builder).


## Getting Started

Clone this project and `cd` into the project root:
```
git clone https://github.com/extra2000/vitis-cpp-datastruct.git
cd vitis-cpp-datastruct
```


## Creating Vivado Project

From the project root directory, execute the following command:
```
cd vivado/run/
flatpak run com.github.corna.Vivado -mode batch -source ../script/create_prj.tcl -notrace -tclargs --project_name cpp-datastruct
```

Then, load the Vivado project:
```
flatpak run com.github.corna.Vivado -mode gui ./cpp-datastruct/cpp-datastruct.xpr
```

Generate XSA file required by Vitis and PetaLinux.


## Build PetaLinux

Fix permission issues:
```
chcon -R -v -t container_file_t ./petalinux ./vivado/run/cpp-datastruct
podman unshare chown -R 1000:1000 ./petalinux
```

Create project:
```
podman run -it --rm -v ${PWD}/petalinux:${PWD}/petalinux:rw --workdir ${PWD}/petalinux --security-opt label=type:petalinux_builder.process localhost/extra2000/petalinux-builder:latest
petalinux-create --type project --template zynq --name arty-z7-20
chmod -R og+rw ./arty-z7-20/.petalinux/
exit
```

Initialize project:
```
podman run -it --rm -v ${PWD}/vivado:${PWD}/vivado:ro -v ${PWD}/petalinux:${PWD}/petalinux:rw --workdir ${PWD}/petalinux/arty-z7-20 --security-opt label=type:petalinux_builder.process localhost/extra2000/petalinux-builder:latest
petalinux-config --get-hw-description ../../vivado/run/cpp-datastruct/
```

Choose `EXT4` file system:
* `Image Packaging Configuration` > `Root filesystem type` > `EXT4`.

Execute the following command:
```
petalinux-config -c rootfs
```

Then, set the following configurations:
* All packages in `Filesystem Packages` > `libs` > `boost`
* `Filesystem Packages` > `misc` > `gcc-runtime` > `libstdc++`
* `Filesystem Packages` > `misc` > `packagegroup-core-tools-profile` > `packagegroup-core-tools-profile`
* `Filesystem Packages` > `misc` > `packagegroup-core-tools-profile` > `packagegroup-core-tools-profile-dbg`
* Disable `Filesystem Packages` > `misc` > `packagegroup-core-ssh-dropbear` > `packagegroup-core-ssh-dropbear`
* Disable `Image Features` > `ssh-server-dropbear`
* Enable `Image Features` > `ssh-server-openssh`
* Enable `Image Features` > `package-management`
* Disable `Image Features` > `package-management` > `package-feed-uris`
* Disable `Image Features` > `package-management` > `package-feed-archs`
* Set `Image Features` > `Init-manager` > `systemd`

Build project:
```
petalinux-build
petalinux-build --sdk
petalinux-package --sysroot
petalinux-package --boot --fsbl ./images/linux/zynq_fsbl.elf --fpga ./images/linux/system.bit --u-boot
```

Build for QEMU (optional but may be useful for testing and development):
```
petalinux-package --wic
petalinux-package --prebuilt --fpga ./images/linux/system.bit -a images/linux/image.ub:images/image.ub
chmod og+rw ./pre-built/linux/images/petalinux-sdimage.wic
```

NOTE: If the following `sudo` file has permission denied during the `petalinux-package --prebuilt` command, try fix the permission by executing the following command from host:
```
sudo chmod u+rw,og+r ./petalinux/arty-z7-20/images/linux/sdk/sysroots/cortexa9t2hf-neon-xilinx-linux-gnueabi/usr/bin/sudo
```

Exit from the container:
```
exit
```

Create SD card image.


## Running with QEMU

Spawn a Petalinux container with `host` networking:
```
podman run -it --rm --network host -v ${PWD}/vivado:${PWD}/vivado:ro -v ${PWD}/petalinux:${PWD}/petalinux:rw --workdir ${PWD}/petalinux/arty-z7-20 --security-opt label=type:petalinux_builder.process localhost/extra2000/petalinux-builder
```

Start QEMU which binds TCF Agent port `1534` for Vitis development in later Section:
```
petalinux-boot --qemu --prebuilt 3 --qemu-args "-net nic,netdev=eth0 -netdev user,id=eth0,hostfwd=tcp:127.0.0.1:1534-:1534 -net nic"
```

Later, Vitis will expect a directory `/run/media/mmcblk0p1` to be existed in PetaLinux. For unknown reason, TCF Agent doesn't automatically create `/run/media/mmcblk0p1` in PetaLinux 2022.1. To fix this issue, execute the following commands on PetaLinux:
```
sudo mkdir -pv /run/media/mmcblk0p1
```

NOTE: The default SSH username for Petalinux is `petalinux`.

To shutdown QEMU, execute the following command:
```
poweroff
```

After QEMU has halted, terminate QEMU console with `CTRL + A` and then type `X`.


## Building Application

Ensure host has full access to applications:
```
podman unshare chown -R 0:0 ./petalinux/arty-z7-20/project-spec/meta-user/recipes-apps
podman unshare chown -R 0:0 ./petalinux/arty-z7-20/project-spec/meta-user/conf/user-rootfsconfig
```

Clone applications:
```
git clone https://github.com/extra2000/datastruct-cpp.git ./petalinux/arty-z7-20/project-spec/meta-user/recipes-apps/helloworld
```

Build the application into RPM files:
```
petalinux-build -c datastruct-cpp
```

Upload the RPM files `petalinux/arty-z7-20/build/tmp/deploy/rpm/cortexa9t2hf_neon/datastruct-cpp-*.rpm` to the board and then install the application using `dnf` command:
```
sudo dnf install ./datastruct-cpp-*.rpm
```

To uninstall the application:
```
sudo dnf remove datastruct-cpp{,-dbg,-dev,-lic,-src}
```


## Creating Vitis Project

Restore host's ownership for Petalinux images files. This is required for Vitis to create project:
```
podman unshare chown -R 0:0 ./petalinux/arty-z7-20/images
```

From the project root directory, `cd` into `petalinux/arty-z7-20/project-spec/meta-user/recipes-apps/datastruct-cpp/files`:
```
cd ./petalinux/arty-z7-20/project-spec/meta-user/recipes-apps/datastruct-cpp/files
```

Generate platform:
```
flatpak run --command=xsct com.github.corna.Vivado ./scripts/arty-z7-20.tcl
```

From the project root directory, `cd` into `./workspace`:
```
cd ./workspace
```

Launch Vitis:
```
flatpak run --command=vitis com.github.corna.Vivado -workspace .
```

Then, `Import Projects` > `Eclipse workspace or zip file`:
* Select root directory: `/path/to/vitis-cpp-datastruct/petalinux/arty-z7-20/project-spec/meta-user/recipes-apps/datastruct-cpp`.
* Check all projects.
* Options:
    * Do not copy projects into workspace.

Uploading shared library by executing `xsct` command from this project root directory (*Warning: May conflict with `datastruct-cpp-1.0-r0.0.cortexa9t2hf_neon.rpm`*):
```
flatpak run --command=xsct com.github.corna.Vivado
connect -host 127.0.0.1 -port 1534
tfile copy -from-host ./vitis/logger/Debug/liblogger.so /usr/lib/liblogger.so
disconnect
exit
```


## Known Issues

* **Microsoft Windows 11 with Ubuntu 22.04 LTS WSL2**: Building with Vitis doesn't work. We don't know how to prevent Vitis from creating paths that mixed with forward ("`/`") and backward ("`\`") slash.
