

A DSL to generate electronics schematics and PCBs.
From the DSL we'll generate eagle CAD sch and brd files.


The vision is to:
  - scrape PDFs for data (sizes, pins, etc.) of components
  - auto place components on a board and auto route connections
    Placement/routing is made under control of constraint rules
    written in the DSL.
  - perform some electrical rule checking
  - output eagle files for import into eagle and circuitmaker/altium
  
This is all work in progress. Currently, it scrapes example datasheet pdfs already for some tables.


installation:

 - install python3
 - pip3 install pystache
 - pip4 install antlr4-python3-runtime