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

For more, see:

- [Benchmarks](BENCHMARKS.md)
- [Command Line Interface](CLI.md)
- [Step-by-step Example](EXAMPLE.md)
- [Input Format](INPUTS.md)
- [How to Run](RUN.md)
- [How to Visualize](VISUALIZE.md)
- [Self-documenting Makefile](Makefile)
