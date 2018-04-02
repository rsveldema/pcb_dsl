// GENERATED CODE, DO NOT TOUCH
// header comes from opencl/template.opencl.c

struct Component;

struct Point
{
    int x;
    int y;
};

struct Outline
{
  Point p[4];
};

struct Pin
{
  Outline outline;
  Component *parent;
};


struct ComponentInfo
{
  Point *fixed_position;
  const char *name;
  bool is_ground;
  bool is_router;
  bool is_board;
  bool is_rotateable;
};

struct Component
{
  Outline outline;
  ComponentInfo *info;
};

struct ModelInfo
{
  
};

struct Model {
	struct {
		Component base;
	} board;

	struct {
		Component base;
		struct {
			Pin base;
		} DVSS;
		struct {
			Pin base;
		} DVDD;
		struct {
			Pin base;
			Pin *connection_R0_IN;
		} D0;
		struct {
			Pin base;
			Pin *connection_R1_IN;
		} D1;
		struct {
			Pin base;
			Pin *connection_R2_IN;
		} D2;
		struct {
			Pin base;
			Pin *connection_R3_IN;
		} D3;
		struct {
			Pin base;
			Pin *connection_R4_IN;
		} D4;
		struct {
			Pin base;
			Pin *connection_R5_IN;
		} D5;
		struct {
			Pin base;
			Pin *connection_R6_IN;
		} D6;
		struct {
			Pin base;
			Pin *connection_R7_IN;
		} D7;
		struct {
			Pin base;
			Pin *connection_R8_IN;
		} D8;
		struct {
			Pin base;
			Pin *connection_R9_IN;
		} D9;
		struct {
			Pin base;
		} SELECT;
		struct {
			Pin base;
		} CLOCK;
		struct {
			Pin base;
		} SLEEP;
		struct {
			Pin base;
		} INA_I;
		struct {
			Pin base;
			Pin *connection_R5K_2_IN;
		} INB_I;
		struct {
			Pin base;
			Pin *connection_C_01_uF_3_IN;
		} REFT_I;
		struct {
			Pin base;
			Pin *connection_C_01_uF_3_OUT;
		} REFB_I;
		struct {
			Pin base;
		} AVSS;
		struct {
			Pin base;
			Pin *connection_C_01_uF_1_IN;
			Pin *connection_C_10_uF_1_IN;
		} REFSENSE;
		struct {
			Pin base;
			Pin *connection_ADC_REFSENSE;
			Pin *connection_R5K_1_IN;
		} VREF;
		struct {
			Pin base;
		} AVDD;
		struct {
			Pin base;
			Pin *connection_C_01_uF_6_OUT;
		} REFB_Q;
		struct {
			Pin base;
			Pin *connection_C_01_uF_6_IN;
		} REFT_Q;
		struct {
			Pin base;
			Pin *connection_R5K_2_IN;
		} INB_Q;
		struct {
			Pin base;
		} INA_Q;
		struct {
			Pin base;
		} CHIP_SELECT;
	} ADC;

	struct {
		Component base;
		struct {
			Pin base;
			Pin *connection_ADC_INA_I;
		} P0;
		struct {
			Pin base;
			Pin *connection_ADC_INA_Q;
		} P1;
		struct {
			Pin base;
			Pin *connection_router_in;
		} P2;
		struct {
			Pin base;
		} P3;
		struct {
			Pin base;
		} P4;
		struct {
			Pin base;
		} P5;
		struct {
			Pin base;
		} P6;
		struct {
			Pin base;
		} P7;
		struct {
			Pin base;
		} P8;
		struct {
			Pin base;
		} P9;
	} analog_connector;

	struct {
		Component base;
		struct {
			Pin base;
		} GND;
	} AGND;

	struct {
		Component base;
		struct {
			Pin base;
			Pin *connection_router_in;
		} GND;
	} DGND;

	struct {
		Component base;
		struct {
			Pin base;
		} D9;
		struct {
			Pin base;
		} P1;
		struct {
			Pin base;
		} D8;
		struct {
			Pin base;
		} P3;
		struct {
			Pin base;
		} D7;
		struct {
			Pin base;
		} P5;
		struct {
			Pin base;
		} D6;
		struct {
			Pin base;
		} P7;
		struct {
			Pin base;
		} D5;
		struct {
			Pin base;
		} P9;
		struct {
			Pin base;
		} D4;
		struct {
			Pin base;
			Pin *connection_router_in;
		} GND1;
		struct {
			Pin base;
		} D3;
		struct {
			Pin base;
		} P11;
		struct {
			Pin base;
		} D2;
		struct {
			Pin base;
		} P13;
		struct {
			Pin base;
		} D1;
		struct {
			Pin base;
		} P15;
		struct {
			Pin base;
		} D0;
		struct {
			Pin base;
		} P19;
		struct {
			Pin base;
		} P20;
		struct {
			Pin base;
		} P21;
		struct {
			Pin base;
		} P22;
		struct {
			Pin base;
		} P23;
		struct {
			Pin base;
		} P24;
		struct {
			Pin base;
		} P25;
		struct {
			Pin base;
		} P26;
		struct {
			Pin base;
		} P27;
		struct {
			Pin base;
		} P28;
		struct {
			Pin base;
		} GND2;
		struct {
			Pin base;
		} P30;
		struct {
			Pin base;
		} P31;
		struct {
			Pin base;
		} P32;
		struct {
			Pin base;
		} P33;
		struct {
			Pin base;
		} P34;
		struct {
			Pin base;
		} P35;
		struct {
			Pin base;
		} P36;
		struct {
			Pin base;
		} P37;
		struct {
			Pin base;
		} P38;
		struct {
			Pin base;
		} P39;
	} fpga_connector;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_fpga_connector_D0;
		} OUT;
	} R0;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_fpga_connector_D1;
		} OUT;
	} R1;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_fpga_connector_D2;
		} OUT;
	} R2;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_fpga_connector_D3;
		} OUT;
	} R3;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_fpga_connector_D4;
		} OUT;
	} R4;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_fpga_connector_D5;
		} OUT;
	} R5;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_fpga_connector_D6;
		} OUT;
	} R6;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_fpga_connector_D7;
		} OUT;
	} R7;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_fpga_connector_D8;
		} OUT;
	} R8;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_fpga_connector_D9;
		} OUT;
	} R9;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_R5K_2_IN;
		} OUT;
	} R5K_1;

	struct {
		Component base;
		struct {
			Pin base;
			Pin *connection_C_01_uF_2_IN;
			Pin *connection_C_10_uF_2_IN;
		} IN;
		struct {
			Pin base;
			Pin *connection_router_in;
		} OUT;
	} R5K_2;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_router_in;
		} OUT;
	} C_01_uF_1;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_router_in;
		} OUT;
	} C_10_uF_1;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_router_in;
		} OUT;
	} C_01_uF_2;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_router_in;
		} OUT;
	} C_10_uF_2;

	struct {
		Component base;
		struct {
			Pin base;
			Pin *connection_C_10_uF_3_IN;
		} IN;
		struct {
			Pin base;
			Pin *connection_C_10_uF_3_OUT;
		} OUT;
	} C_01_uF_3;

	struct {
		Component base;
		struct {
			Pin base;
			Pin *connection_C_01_uF_4_IN;
		} IN;
		struct {
			Pin base;
			Pin *connection_C_01_uF_5_IN;
		} OUT;
	} C_10_uF_3;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_router_in;
		} OUT;
	} C_01_uF_4;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_router_in;
		} OUT;
	} C_01_uF_5;

	struct {
		Component base;
		struct {
			Pin base;
			Pin *connection_C_10_uF_7_IN;
		} IN;
		struct {
			Pin base;
			Pin *connection_C_10_uF_7_OUT;
		} OUT;
	} C_01_uF_6;

	struct {
		Component base;
		struct {
			Pin base;
			Pin *connection_C_01_uF_8_IN;
		} IN;
		struct {
			Pin base;
			Pin *connection_C_01_uF_9_IN;
		} OUT;
	} C_10_uF_7;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_router_in;
		} OUT;
	} C_01_uF_8;

	struct {
		Component base;
		struct {
			Pin base;
		} IN;
		struct {
			Pin base;
			Pin *connection_router_in;
		} OUT;
	} C_01_uF_9;

	struct {
		Component base;
		struct {
			Pin base;
		} in;
		struct {
			Pin base;
			Pin *connection_AGND_GND;
		} out;
	} routeru;

	struct {
		Component base;
		struct {
			Pin base;
		} in;
		struct {
			Pin base;
			Pin *connection_DGND_GND;
		} out;
	} router;

	struct {
		Component base;
		struct {
			Pin base;
		} in;
		struct {
			Pin base;
			Pin *connection_AGND_GND;
		} out;
	} routerc;

	struct {
		Component base;
		struct {
			Pin base;
		} in;
		struct {
			Pin base;
			Pin *connection_AGND_GND;
		} out;
	} router;

	struct {
		Component base;
		struct {
			Pin base;
		} in;
		struct {
			Pin base;
			Pin *connection_AGND_GND;
		} out;
	} routert;

	struct {
		Component base;
		struct {
			Pin base;
		} in;
		struct {
			Pin base;
			Pin *connection_AGND_GND;
		} out;
	} router;

	struct {
		Component base;
		struct {
			Pin base;
		} in;
		struct {
			Pin base;
			Pin *connection_AGND_GND;
		} out;
	} router ;

	struct {
		Component base;
		struct {
			Pin base;
		} in;
		struct {
			Pin base;
			Pin *connection_AGND_GND;
		} out;
	} router;

	struct {
		Component base;
		struct {
			Pin base;
		} in;
		struct {
			Pin base;
			Pin *connection_AGND_GND;
		} out;
	} routers;

	struct {
		Component base;
		struct {
			Pin base;
		} in;
		struct {
			Pin base;
			Pin *connection_AGND_GND;
		} out;
	} router;

	struct {
		Component base;
		struct {
			Pin base;
		} in;
		struct {
			Pin base;
			Pin *connection_AGND_GND;
		} out;
	} routert;

	struct {
		Component base;
		struct {
			Pin base;
		} in;
		struct {
			Pin base;
			Pin *connection_AGND_GND;
		} out;
	} router;

};


void link_model(Model *model, ModelInfo *info)
{
  
}

__kernel
void optimize()
{
}
