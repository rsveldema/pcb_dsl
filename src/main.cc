#include <antlr4-runtime.h>
#include <stdarg.h>
#include <string.h>
#include <iostream>

#include "create_model.hpp"
#include "optimizer.hpp"

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

  InitialPlacement initial_placement = InitialPlacement::CLOSE_TO_ALREADY_PLACED;
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
  static unsigned parse_errors = 0;
  
  class LexerErrorListener : public antlr4::BaseErrorListener {
  public:    
    virtual void syntaxError(antlr4::Recognizer *recognizer,
			     antlr4::Token *offendingSymbol,
			     size_t line, size_t charPositionInLine,
			     const std::string &msg, std::exception_ptr e) override
    {
      parse_errors++;
    }
  };
  
  class ParserErrorListener : public antlr4::BaseErrorListener {
  public:
    
    virtual void syntaxError(antlr4::Recognizer *recognizer,
			     antlr4::Token *offendingSymbol,
			     size_t line, size_t charPositionInLine,
			     const std::string &msg, std::exception_ptr e) override
    {
      parse_errors++;
    }
  };
  
  try {
    LexerErrorListener lexerErrorListener;
    ParserErrorListener parserErrorListener;
    
    std::ifstream stream;
    stream.open(filename);
    antlr4::ANTLRInputStream input(stream);
    dslLexer lexer(&input);
    lexer.addErrorListener(&lexerErrorListener);
    
    antlr4::CommonTokenStream tokens(&lexer);
    dslParser parser(&tokens);
    //parser.removeErrorListeners();
    parser.addErrorListener(&parserErrorListener);
    
    antlr4::tree::ParseTree *tree = parser.startRule();

    if (parse_errors)
      {
	fprintf(stderr, "bailing out due to %d parse errors\n",
		parse_errors);
	abort();
      }
    
    antlr4::tree::ParseTreeWalker::DEFAULT.walk(&listener, tree);
  } catch (antlr4::RuntimeException &e) {
    fprintf(stderr, "caught exception!\n");
    exit(1);
  }

  printf("going to start optimization now\n");
  Model *model = listener.get();

  model->check();
  
  Model *best = optimize_model(model, optimize_secs, enable_gui, initial_placement);
  best->writeSVG("final.svg");
  
  return 0;
}
