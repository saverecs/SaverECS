@PHONY: test

deps:
	sudo apt-get install -y libboost-all-dev libjson-glib-dev
	sudo npm install -g coffee-script
	cd ODE_visualization && make

CProgramToSMT=../CProgramToSMT

GOODPATH=$(abspath ../CProgramToSMT/llvm/build/bin/)
GOODCLANG=$(echo $(GOODPATH)"clang" | sed 's_/_\\/_g')
GOODOPT=$(echo $(GOODPATH)"opt" | sed 's_/_\\/_g')
GOODLLI=$(echo $(GOODPATH)"lli" | set 's_/_\\/_g')

BADFILE=src/coreSystem/controller_program/controller_parser.cpp

setupSO:
	cd .. && git clone https://github.com/maxvonhippel/CProgramToSMT.git \
	      && cd CProgramToSMT        \
	      && sudo make deps          \
	      && sudo bash setup_llvm.sh \
	      && sudo make build

# The problem is that in 
# src/coreSystem/controller_program/controller_parser.cpp
# they use the commands clang and opt, but it will default to whatever
# the system default is.
# We want it to default to
# ../CProgramToSMT/llvm/build/bin/clang
# and
# ../CProgramToSMT/llvm/build/bin/opt
fix:
	sed -i 's#opt #$(GOODPATH)/opt #g' $(BADFILE)
	sed -i 's#clang #$(GOODPATH)/clang #g' $(BADFILE)
	sed -i 's#lli #$(GOODPATH)/lli #g' $(BADFILE)

build:
	cd src                      \
		&& chmod +x compile-cpp \
		&& chmod +x ODE_visualization/run_websvr.sh \
		&& chmod +x src/bin/dReal                   \
		&& cp ../$(CProgramToSMT)/llvm-pass-moduleTest/src/libTestPass.so lib/. \
		&& LLVM_DIR=../../$(CProgramToSMT)/llvm ./compile-cpp

test:
	cd src && LLVM_DIR=../$(CProgramToSMT)/llvm ./SaVerECS -m 100 \
	                     -t 0.2                                   \
	                     -d 0.001                                 \
	                     -u 10                                    \
	                     -l 5                                     \
	         --time-horizon 3                                     \
	                 --goal "x>=5 & y>=3"                         \
	           --plant-file "benchmarks/thermostat/thermostat.ha" \
	      --controller-file "benchmarks/thermostat/thermostat.c"  \
	                     -o test.smt2