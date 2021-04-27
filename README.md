# SaverECS

This code was originally written by:

````
Indian Institute of Technology Kharagpur, India,
Formal Methods Lab,
Project Title: "FMSAFE: A Networked Centre for Formal Methods in Validation and Certification Procedures for Safety Critical ICT Systems"
Funded by IMPRINT, a MHRD supported Pan-IIT + IISc joint initiative for addressing major science and engineering challenges that are relevant in the national context.
Copyright (c) 2018 Formal Methods Lab, Indian Institute of Technology Kharagpur, India.
Developed by Amit Gurung, Jay Thakkar, Sunandan Adhikary, & Antonio Bruto da Costa 
````

This specific *fork* is a refactor by Max von Hippel, built for:
* portability,
* reproducibility, and
* clarity of documentation.

Please note that while the original authors included a documenting website in their repo, my fork does not copy the website.  So you should refer to the original repository for further documentation.

# *Sa*fety *Ver*ification of *E*mbedded *C*ontrol *S*oftware Tool-chain

**SaVerECS** is an SMT-based verification tool to formally guarantee the performance and safety of an embedded control software under the influence of process or measurement noises and timing uncertainties (i.e. delay, jitters), before implementing them in real-time systems. Support for *non-linearities in the controlled plant and the controller software*, *real-valued constraints* and *control software code as input*, make this tool-chain ideal for verifying real-world hybrid systems. Our tool incorporates semantic support for capturing plant specifications, timing and value-based uncertainties (noise, precision errors), and the control software code.

*Evaluated verification benchmarks can be found in [**this repository**](https://github.com/saverecs/Benchmark_SaverECS). The operational details of the designed tool-chain are documented here.*

--

TL;DR: the following commands, in order, will build and run the software for you.  You can learn generally how to run the software, once it is built, by inspecting the `make test` target in the [Makefile](Makefile).
````
# install some dependencies.
# should take a few seconds or minutes.
make deps
# download and compile LLVM7.0.0 with clang
# in debug mode, and CProgramToSMT project.
# Could take hours to complete, even on a modern
# processor.
make setupSO
# Fix some paths in a cpp file which will point to the
# wrong llvm/clang/lli if you don't have 7.0.0 as your /usr/bin
# version -- which, most of us do not.
# Should take milliseconds.
make fix
# build the code.  Should take under a minute.
make build
# test it. Should take seconds.
make test
````

--

For more documentation by the authors, see:

- [Benchmarks](BENCHMARKS.md)
- [Command Line Interface](CLI.md)
- [Step-by-step Example](EXAMPLE.md)
- [Input Format](INPUTS.md)
- [How to Run](RUN.md)
- [How to Visualize](VISUALIZE.md)
- [Self-documenting Makefile](Makefile)
