#include <antlr4-runtime.h>
#include <stdarg.h>
#include <iostream>

#include "create_model.h"


void Usage(const char *format, ...)
{
  va_list va;
  va_start(va, format);

  vfprintf(stderr, format, va);

  fprintf(stderr, "USAGE: -pcb <file.edsl>\n");  
  exit(1);  
}

int main(int argc, char **argv)
{
  const char *filename = NULL;
  for (int i=1;i<argc;i++)
    {
      if (strcmp(argv[i], "-pcb") == 0)
	{
	  i++;
	  filename = argv[i];
	}
      else
	{
	  Usage("unrecognized arg: %s\n", argv[i]);
	}
    }

  if (! filename) {
    Usage("missing file name");
  }

  try {
    std::ifstream stream;
    stream.open(filename);
    antlr4::ANTLRInputStream input(stream);
    dslLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    dslParser parser(&tokens);
    
    antlr4::tree::ParseTree *tree = parser.startRule();
    ModelCreatorListener listener;
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
  } catch (antlr4::RuntimeException &e) {
    fprintf(stderr, "caught exception!\n");
  }

  printf("going to start optimization now\n");
  return 0;
}
