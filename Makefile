deps:
	sudo apt-get install -y libboost-all-dev

build:
	cd src && chmod +x compile-cpp && ./compile-cpp