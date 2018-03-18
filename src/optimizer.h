#ifndef OPTIMIZER__G__H__
#define OPTIMIZER__G__H__

#include "model.h"

enum class InitialPlacement
  {
    RANDOM,
      CLOSE_TO_ALREADY_PLACED,
  };


Model* optimize_model(Model *model,
		      unsigned time_limit_secs,
		      bool enable_gui,
		      InitialPlacement initial_placement);

#endif
