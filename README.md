

A DSL to generate electronics schematics and PCBs.
From the DSL we'll generate eagle CAD sch and brd files.


The vision is to:
  - scrape PDFs for data (sizes, pins, etc.) of components
  - auto place components on a board and auto route connections
    Placement/routing is made under control of constraint rules
    written in the DSL.
  - perform some electrical rule checking
  - output eagle files for import into eagle and circuitmaker/altium
  
This is all work in progress. Currently, it scrapes example datasheet
pdfs already for some tables and can generate SVG files after optimization.



--- installation:

  - yum install boost-devel
  - yum install gcc gcc-c++ make
  - yum install python3 antlr4 libuuid-devel mvn cmake
  - yum install libsigc++-2.0 cairomm-devel gtkmm-devel glibmm-devel
