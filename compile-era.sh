#!/usr/bin/sh

if [[ "$1" == "riscv" ]]; then
  source soc_utils/setup_paths.sh
  fpga_host=$FPGA_HOST
  fpga_host_ip=$FPGA_HOST_IP
  fpga_username=$FPGA_USERNAME
  rm -rf XF_riscv_hpvm
  mkdir -p XF_riscv_hpvm/soc_utils
  sed -i 's/scheduler-library-x86/scheduler-library-hpvm/' soc_utils/setup_paths.sh
  sed -i 's/scheduler-library-x86/scheduler-library-hpvm/' soc_utils/config_files/base_me_p2.config
  source soc_utils/setup_paths.sh
  sed -i 's/#define X86/#define RISCV/' src/main.c
  sed -i 's/#define ERA2/#define ERA1/' src/main.c
  sed -i "s/192.168.1.99/$fpga_host/" src/main.c
  make hpvm-epochs -f Makefile
  cp hpvm-test-scheduler-RV-F2VCHo-P1V1F0N1 era1
  sed -i 's/#define ERA1/#define ERA2/' src/main.c
  make hpvm-epochs -f Makefile
  cp hpvm-test-scheduler-RV-F2VCHo-P1V1F0N1 era2
  sed -i 's/#define ERA2/#define ERA1/' src/main.c

  cp era1 era2 XF_riscv_hpvm
  cp graph*.xml XF_riscv_hpvm/
  cp src/*.py XF_riscv_hpvm/
  cp src/*.sh XF_riscv_hpvm/

  #CV binaries and files
  cp sw/umd/out/core/src/runtime/libnvdla_runtime/libnvdla_runtime.so XF_riscv_hpvm/
  cp sw/prebuilt/riscv-linux/nvdla_runtime XF_riscv_hpvm/
  cp hpvm-mod.nvdla XF_riscv_hpvm/
  cp ../hpvm-release/hpvm/test/epoch_dnn/gen_yolo/images/44.jpg XF_riscv_hpvm/atr.jpg

  sed -i "s/127.0.0.1/$fpga_host/" XF_riscv_hpvm/read_bag_1.py
  sed -i "s/127.0.0.1/$fpga_host/" XF_riscv_hpvm/read_bag_2.py
  sed -i "s/127.0.0.1/$fpga_host/" XF_riscv_hpvm/wifi_comm_1.sh
  sed -i "s/127.0.0.1/$fpga_host/" XF_riscv_hpvm/wifi_comm_2.sh
  sed -i "s/127.0.0.1/$fpga_host/" XF_riscv_hpvm/carla_recvr_1.sh
  sed -i "s/127.0.0.1/$fpga_host/" XF_riscv_hpvm/carla_recvr_2.sh

  # cp -r data XF_riscv_hpvm/
  cp -r soc_utils/config_files XF_riscv_hpvm/soc_utils/
  cp -r $SOC_LIB_DIR/sched_library/meta_policies XF_riscv_hpvm/
  cp -r $SOC_LIB_DIR/sched_library/task_policies XF_riscv_hpvm/

  # scp -r XF_riscv_hpvm $fpga_username@$fpga_host_ip:~/XF_riscv_hpvm
  # scp -r data $fpga_username@$fpga_host_ip:~/data
  
elif [[ "$1" == "x86" ]]; then
  x86_host='127.0.0.1'
  export PYTHONPATH=/dccstor/epochs/aporvaa/hetero_era/src/cv/yolo
  rm -rf XF_x86_hpvm
  mkdir -p XF_x86_hpvm/soc_utils
  rm -f hpvm-test-scheduler-F2VCF-P3V0F0N0
  sed -i 's/scheduler-library-hpvm/scheduler-library-x86/' soc_utils/setup_paths.sh
  sed -i 's/scheduler-library-hpvm/scheduler-library-x86/' soc_utils/config_files/base_me_p2.config
  source soc_utils/setup_paths.sh
  sed -i 's/#define RISCV/#define X86/' src/main.c
  sed -i 's/#define ERA2/#define ERA1/' src/main.c
  make hpvm-epochs -f Makefile
  cp hpvm-test-scheduler-F2VCF-P3V0F0N0 era1
  rm -f hpvm-test-scheduler-F2VCF-P3V0F0N0
  sed -i 's/#define ERA1/#define ERA2/' src/main.c
  make hpvm-epochs -f Makefile
  cp hpvm-test-scheduler-F2VCF-P3V0F0N0 era2
  sed -i 's/#define ERA2/#define ERA1/' src/main.c
  cp era1 era2 XF_x86_hpvm/
  cp graph*.xml XF_x86_hpvm/
  cp src/*.py XF_x86_hpvm/
  cp src/*.sh XF_x86_hpvm/

  sed -i 's/192.168.1.99/127.0.0.1/' XF_x86_hpvm/read_bag_1.py
  sed -i 's/192.168.1.99/127.0.0.1/' XF_x86_hpvm/read_bag_2.py
  sed -i 's/192.168.1.99/127.0.0.1/' XF_x86_hpvm/wifi_comm_1.sh
  sed -i 's/192.168.1.99/127.0.0.1/' XF_x86_hpvm/wifi_comm_2.sh
  sed -i 's/192.168.1.99/127.0.0.1/' XF_x86_hpvm/carla_recvr_1.sh
  sed -i 's/192.168.1.99/127.0.0.1/' XF_x86_hpvm/carla_recvr_2.sh

  # cp -r data XF_x86_hpvm/
  cp -r soc_utils/config_files XF_x86_hpvm/soc_utils/
  cp -r $SOC_LIB_DIR/sched_library/meta_policies XF_x86_hpvm/
  cp -r $SOC_LIB_DIR/sched_library/task_policies XF_x86_hpvm/
fi

# scp -r XF/era* aamarnath@erebor.watson.ibm.com:/mnt/seagate_hdd/EPOCHS/hetero_era/XF

