# Formal Languages
This repository contains C++ library for working with formal languages: 

## Quick Start Ubuntu 
      Install following tools, if you don't have them already: 
      $ sudo apt-get install libboost-all-dev 
      $ sudo apt-get install openssl libssl-dev 
      $ /install_deps.sh python<your python version> 
## Make 
      $ mkdir build 
      $ cd build 
      $ cmake -DCMAKE_BUILD_TYPE=Debug .. 
      $ sudo make -j<num cores + 1> 
      $ cd .. 
## Run main executable code 
      $ cd bin 
      $ ./01-simple-library-bin 
      $ cd .. 
## Check code coverage 
      $ cd build 
      $ sudo make coverage_report 
      Open an appeared in /build .html file - it will display information related to test coverage
