@PHONY: test

deps:
	sudo apt-get install -y libboost-all-dev libjson-glib-dev

CProgramToSMT=../CProgramToSMT

setupSO:
	cd .. && git clone https://github.com/maxvonhippel/CProgramToSMT.git \
	      && cd CProgramToSMT        \
	      && sudo make deps          \
	      && sudo bash setup_llvm.sh \
	      && sudo make build

build:
	cd src                      \
		&& chmod +x compile-cpp \
		&& cp ../$(CProgramToSMT)/llvm-pass-moduleTest/src/libTestPass.so lib/. \
		&& FMSAFE_HOME=${PWD} LLVM_DIR=../$(CProgramToSMT)/llvm ./compile-cpp

test:
	cd src && ./SaVerECS -m 100                                   \
	                     -t 0.2                                   \
	                     -d 0.001                                 \
	                     -u 10                                    \
	                     -l 5                                     \
	         --time-horizon 3                                     \
	                 --goal "x>=5 & y>=3"                         \
	           --plant-file "benchmarks/thermostat/thermostat.ha" \
	      --controller-file "benchmarks/thermostat/thermostat.c"  \
	                     -o test.smt2