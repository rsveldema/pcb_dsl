import sys
import os
import pystache
from antlr4 import *
from dslLexer import dslLexer
from dslParser import dslParser
from dslListener import dslListener
from create_model import read_model
from optimizer import optimize_model

def Usage():
    print("USAGE: xxx.edsl");


def parse(fileName):
    print("Reading " + fileName)

    input = FileStream(fileName)
    lexer = dslLexer(input)
    stream = CommonTokenStream(lexer)
    parser = dslParser(stream)
    tree = parser.startRule()
    return tree;

def getBaseName(name):
    ix = name.rfind('/')
    if ix >= 0:
        name = name[ix+1:]
    ix = name.find('.')
    if ix >= 0:
        name = name[0:ix]
    return name


fileName = None
for arg in sys.argv[1:]:
    if arg.endswith(".edsl"):
        fileName = arg;
    else:
        Usage("unknown command line parameter: " + arg)

if fileName == None:
    Usage("missing xxx.edsl file")


tree = parse(fileName)
model = read_model(tree)
model.writeDot("model.dot")
model.writeSVG("model.svg")

clone = model.deepclone()
clone.writeSVG("clone.svg")

time_limit_secs = 5
opt = optimize_model(model, time_limit_secs)
if opt != None:
    opt.writeSVG("final.svg")
else:
    print("optimized failed to create a good model")
