# Cellular Vehicle-to-Everything (C-V2X) Mode 4 Communication Model for ns-3

A ns-3 model for C-V2X Mode 4 communication based on the ns-3 D2D model from [NIST](https://github.com/usnistgov/psc-ns3/tree/d2d-ns-3.22).

![TU Dortmund University](img/tu-dortmund_small.png "TU Dortmund University")
![InVerSiV](img/Inversiv_small.png "InVerSiV")
![SFB 876](img/SFB876_small.png "Collaborative Research Center SFB 876")
![Communication Networks Institute](img/CNI_small.png "Communication Networks Institute")
![EFRE](img/EFRE_small.png "EFRE")
![DFG](img/DFG_small.png "DFG")

The work on this paper has been partially funded by the federal state of Northrhine-Westphalia and the “European Regional Development Fund” (EFRE) 2014-2020 in the course of the InVerSiV project under grant number EFRE-0800422 and by DeutscheForschungsgemeinschaft (DFG) within the Collaborative Research Center SFB 876 project B4.

## Installation

1. Clone or download the source code from this repository
2. Navigate to the root directory of the cloned/downloaded repository
3. Configure the project using the command
```
   ./waf configure
```
4. Build the project using the command
```
   ./waf build
```

For more details regarding the configuration and building of ns-3 projects see [the ns-3 documentation](https://www.nsnam.org/documentation/).

## Usage

A example script for the usage of the C-V2X Mode 4 is located in the *scratch* directory of this repository (*v2x_communication_example.cc*).
To run the example script run:
```
   ./waf --run v2x_communication_example
```

# Cite as

If you use our model in your research, please cite the following paper:

F. Eckermann, M. Kahlert, C. Wietfeld, ["Performance Analysis of C-V2X Mode 4 Communication Introducing an Open-Source C-V2X Simulator"](https://www.kn.e-technik.tu-dortmund.de/.cni-bibliography/publications/cni-publications/Eckermann2019performance.pdf), In 2019 IEEE 90th Vehicular Technology Conference (VTC-Fall), Honolulu, Hawaii, USA, September 2019.

### Bibtex:
    @InProceedings{Eckermann2019performance,
        Author = {Fabian Eckermann and Moritz Kahlert and Christian Wietfeld},
        Title = {Performance Analysis of {C-V2X} Mode 4 Communication Introducing an Open-Source {C-V2X} Simulator},
        Booktitle = {2019 IEEE 90th Vehicular Technology Conference (VTC-Fall)},
        Year = {2019},
        Address = {Honolulu, Hawaii, USA},
        Month = {September},
    }
