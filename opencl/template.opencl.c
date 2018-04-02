// GENERATED CODE, DO NOT TOUCH
// header comes from opencl/template.opencl.c

typedef char bool;
#define __global
#define __kernel

typedef struct Point
{
    int x;
    int y;
    int layer;
} Point;

struct Outline
{
  Point p[4];
};

typedef struct Outline Outline;

struct ComponentInfo
{
  Point *fixed_position;
  bool is_ground;
  bool is_router;
  bool is_board;
  bool is_rotateable;
};

{{DATASTRUCTURE}}

typedef struct ModelInfo
{
  {{COMPONENT_INFO_DATASTRUCTURE}}
} ModelInfo;


void get_model_info(__global int *data)
{
  data[0] = sizeof(Model);
  data[1] = sizeof(ModelInfo);
}

void set_model_info(__global ModelInfo *info)
{
  {{MODEL_INFO_CODE}}
}

void link_model(__global Model *model, __global ModelInfo *info)
{
  {{LINK_MODEL}}
}

__kernel
void optimize()
{
}
