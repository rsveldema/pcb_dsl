#include <antlr4-runtime.h>
#include <stdarg.h>
#include <string.h>
#include <iostream>

#include "create_model.h"
#include "optimizer.h"

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
  srand(10);

  bool enable_gui = false;
  const char *filename = NULL;
  int optimize_secs = 5;
  
  for (int i=1;i<argc;i++)
    {
      if (strcmp(argv[i], "-gui") == 0)
	{
	  enable_gui = true;
	}
      else if (strcmp(argv[i], "-secs") == 0)
	{
	  i++;	  
	  optimize_secs = atoi(argv[i]);
	}
      else if (strcmp(argv[i], "-pcb") == 0)
	{
	  i++;
	  filename = argv[i];
	}
      else
	{
	  Usage("unrecognized arg: %s\n", argv[i]);
	}
    }

  if (! filename)
    {
      Usage("missing file name");
    }
  if (! file_exists(filename))
    {
      fprintf(stderr, "ERROR: file '%s' not found\n", filename);
      exit(1);
    }
  printf("PARSING: %s\n", filename);


  argc = 1;
  Canvas::init(argc, argv);    

  ModelCreatorListener listener;

  try {
    std::ifstream stream;
    stream.open(filename);
    antlr4::ANTLRInputStream input(stream);
    dslLexer lexer(&input);
    antlr4::CommonTokenStream tokens(&lexer);
    dslParser parser(&tokens);
    
    antlr4::tree::ParseTree *tree = parser.startRule();
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
  } catch (antlr4::RuntimeException &e) {
    fprintf(stderr, "caught exception!\n");
    exit(1);
  }

  printf("going to start optimization now\n");
  Model *model = listener.get();

  model->check();
  Model *best = optimize_model(model, optimize_secs, enable_gui);
  best->writeSVG("final.svg");
  
  return 0;
}
