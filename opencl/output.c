// GENERATED CODE, DO NOT TOUCH
// header comes from opencl/template.opencl.c

typedef char bool;
#define __global
#define __kernel

typedef struct Point
{
    int x;
    int y;
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

// forward declare pins and components:
struct COMPONENT_board;
struct COMPONENT_ADC;
struct PIN_ADC_DVSS;
struct PIN_ADC_DVDD;
struct PIN_ADC_D0;
struct PIN_ADC_D1;
struct PIN_ADC_D2;
struct PIN_ADC_D3;
struct PIN_ADC_D4;
struct PIN_ADC_D5;
struct PIN_ADC_D6;
struct PIN_ADC_D7;
struct PIN_ADC_D8;
struct PIN_ADC_D9;
struct PIN_ADC_SELECT;
struct PIN_ADC_CLOCK;
struct PIN_ADC_SLEEP;
struct PIN_ADC_INA_I;
struct PIN_ADC_INB_I;
struct PIN_ADC_REFT_I;
struct PIN_ADC_REFB_I;
struct PIN_ADC_AVSS;
struct PIN_ADC_REFSENSE;
struct PIN_ADC_VREF;
struct PIN_ADC_AVDD;
struct PIN_ADC_REFB_Q;
struct PIN_ADC_REFT_Q;
struct PIN_ADC_INB_Q;
struct PIN_ADC_INA_Q;
struct PIN_ADC_CHIP_SELECT;
struct COMPONENT_analog_connector;
struct PIN_analog_connector_P0;
struct PIN_analog_connector_P1;
struct PIN_analog_connector_P2;
struct PIN_analog_connector_P3;
struct PIN_analog_connector_P4;
struct PIN_analog_connector_P5;
struct PIN_analog_connector_P6;
struct PIN_analog_connector_P7;
struct PIN_analog_connector_P8;
struct PIN_analog_connector_P9;
struct COMPONENT_AGND;
struct PIN_AGND_GND;
struct COMPONENT_DGND;
struct PIN_DGND_GND;
struct COMPONENT_fpga_connector;
struct PIN_fpga_connector_D9;
struct PIN_fpga_connector_P1;
struct PIN_fpga_connector_D8;
struct PIN_fpga_connector_P3;
struct PIN_fpga_connector_D7;
struct PIN_fpga_connector_P5;
struct PIN_fpga_connector_D6;
struct PIN_fpga_connector_P7;
struct PIN_fpga_connector_D5;
struct PIN_fpga_connector_P9;
struct PIN_fpga_connector_D4;
struct PIN_fpga_connector_GND1;
struct PIN_fpga_connector_D3;
struct PIN_fpga_connector_P11;
struct PIN_fpga_connector_D2;
struct PIN_fpga_connector_P13;
struct PIN_fpga_connector_D1;
struct PIN_fpga_connector_P15;
struct PIN_fpga_connector_D0;
struct PIN_fpga_connector_P19;
struct PIN_fpga_connector_P20;
struct PIN_fpga_connector_P21;
struct PIN_fpga_connector_P22;
struct PIN_fpga_connector_P23;
struct PIN_fpga_connector_P24;
struct PIN_fpga_connector_P25;
struct PIN_fpga_connector_P26;
struct PIN_fpga_connector_P27;
struct PIN_fpga_connector_P28;
struct PIN_fpga_connector_GND2;
struct PIN_fpga_connector_P30;
struct PIN_fpga_connector_P31;
struct PIN_fpga_connector_P32;
struct PIN_fpga_connector_P33;
struct PIN_fpga_connector_P34;
struct PIN_fpga_connector_P35;
struct PIN_fpga_connector_P36;
struct PIN_fpga_connector_P37;
struct PIN_fpga_connector_P38;
struct PIN_fpga_connector_P39;
struct COMPONENT_R0;
struct PIN_R0_IN;
struct PIN_R0_OUT;
struct COMPONENT_R1;
struct PIN_R1_IN;
struct PIN_R1_OUT;
struct COMPONENT_R2;
struct PIN_R2_IN;
struct PIN_R2_OUT;
struct COMPONENT_R3;
struct PIN_R3_IN;
struct PIN_R3_OUT;
struct COMPONENT_R4;
struct PIN_R4_IN;
struct PIN_R4_OUT;
struct COMPONENT_R5;
struct PIN_R5_IN;
struct PIN_R5_OUT;
struct COMPONENT_R6;
struct PIN_R6_IN;
struct PIN_R6_OUT;
struct COMPONENT_R7;
struct PIN_R7_IN;
struct PIN_R7_OUT;
struct COMPONENT_R8;
struct PIN_R8_IN;
struct PIN_R8_OUT;
struct COMPONENT_R9;
struct PIN_R9_IN;
struct PIN_R9_OUT;
struct COMPONENT_R5K_1;
struct PIN_R5K_1_IN;
struct PIN_R5K_1_OUT;
struct COMPONENT_R5K_2;
struct PIN_R5K_2_IN;
struct PIN_R5K_2_OUT;
struct COMPONENT_C_01_uF_1;
struct PIN_C_01_uF_1_IN;
struct PIN_C_01_uF_1_OUT;
struct COMPONENT_C_10_uF_1;
struct PIN_C_10_uF_1_IN;
struct PIN_C_10_uF_1_OUT;
struct COMPONENT_C_01_uF_2;
struct PIN_C_01_uF_2_IN;
struct PIN_C_01_uF_2_OUT;
struct COMPONENT_C_10_uF_2;
struct PIN_C_10_uF_2_IN;
struct PIN_C_10_uF_2_OUT;
struct COMPONENT_C_01_uF_3;
struct PIN_C_01_uF_3_IN;
struct PIN_C_01_uF_3_OUT;
struct COMPONENT_C_10_uF_3;
struct PIN_C_10_uF_3_IN;
struct PIN_C_10_uF_3_OUT;
struct COMPONENT_C_01_uF_4;
struct PIN_C_01_uF_4_IN;
struct PIN_C_01_uF_4_OUT;
struct COMPONENT_C_01_uF_5;
struct PIN_C_01_uF_5_IN;
struct PIN_C_01_uF_5_OUT;
struct COMPONENT_C_01_uF_6;
struct PIN_C_01_uF_6_IN;
struct PIN_C_01_uF_6_OUT;
struct COMPONENT_C_10_uF_7;
struct PIN_C_10_uF_7_IN;
struct PIN_C_10_uF_7_OUT;
struct COMPONENT_C_01_uF_8;
struct PIN_C_01_uF_8_IN;
struct PIN_C_01_uF_8_OUT;
struct COMPONENT_C_01_uF_9;
struct PIN_C_01_uF_9_IN;
struct PIN_C_01_uF_9_OUT;
struct COMPONENT_router_160;
struct PIN_router_160_in;
struct PIN_router_160_out;
struct COMPONENT_router_161;
struct PIN_router_161_in;
struct PIN_router_161_out;
struct COMPONENT_router_162;
struct PIN_router_162_in;
struct PIN_router_162_out;
struct COMPONENT_router_163;
struct PIN_router_163_in;
struct PIN_router_163_out;
struct COMPONENT_router_164;
struct PIN_router_164_in;
struct PIN_router_164_out;
struct COMPONENT_router_165;
struct PIN_router_165_in;
struct PIN_router_165_out;
struct COMPONENT_router_166;
struct PIN_router_166_in;
struct PIN_router_166_out;
struct COMPONENT_router_167;
struct PIN_router_167_in;
struct PIN_router_167_out;
struct COMPONENT_router_168;
struct PIN_router_168_in;
struct PIN_router_168_out;
struct COMPONENT_router_169;
struct PIN_router_169_in;
struct PIN_router_169_out;
struct COMPONENT_router_170;
struct PIN_router_170_in;
struct PIN_router_170_out;
struct COMPONENT_router_171;
struct PIN_router_171_in;
struct PIN_router_171_out;

// declare pins:
struct PIN_ADC_DVSS {
	Outline outline;
	struct COMPONENT_ADC* parent;
};
struct PIN_ADC_DVDD {
	Outline outline;
	struct COMPONENT_ADC* parent;
};
struct PIN_ADC_D0 {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_R0_IN *CONN_R0_IN;
};
struct PIN_ADC_D1 {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_R1_IN *CONN_R1_IN;
};
struct PIN_ADC_D2 {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_R2_IN *CONN_R2_IN;
};
struct PIN_ADC_D3 {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_R3_IN *CONN_R3_IN;
};
struct PIN_ADC_D4 {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_R4_IN *CONN_R4_IN;
};
struct PIN_ADC_D5 {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_R5_IN *CONN_R5_IN;
};
struct PIN_ADC_D6 {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_R6_IN *CONN_R6_IN;
};
struct PIN_ADC_D7 {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_R7_IN *CONN_R7_IN;
};
struct PIN_ADC_D8 {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_R8_IN *CONN_R8_IN;
};
struct PIN_ADC_D9 {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_R9_IN *CONN_R9_IN;
};
struct PIN_ADC_SELECT {
	Outline outline;
	struct COMPONENT_ADC* parent;
};
struct PIN_ADC_CLOCK {
	Outline outline;
	struct COMPONENT_ADC* parent;
};
struct PIN_ADC_SLEEP {
	Outline outline;
	struct COMPONENT_ADC* parent;
};
struct PIN_ADC_INA_I {
	Outline outline;
	struct COMPONENT_ADC* parent;
};
struct PIN_ADC_INB_I {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_R5K_2_IN *CONN_R5K_2_IN;
};
struct PIN_ADC_REFT_I {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_C_01_uF_3_IN *CONN_C_01_uF_3_IN;
};
struct PIN_ADC_REFB_I {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_C_01_uF_3_OUT *CONN_C_01_uF_3_OUT;
};
struct PIN_ADC_AVSS {
	Outline outline;
	struct COMPONENT_ADC* parent;
};
struct PIN_ADC_REFSENSE {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_C_01_uF_1_IN *CONN_C_01_uF_1_IN;
	struct PIN_C_10_uF_1_IN *CONN_C_10_uF_1_IN;
};
struct PIN_ADC_VREF {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_ADC_REFSENSE *CONN_ADC_REFSENSE;
	struct PIN_R5K_1_IN *CONN_R5K_1_IN;
};
struct PIN_ADC_AVDD {
	Outline outline;
	struct COMPONENT_ADC* parent;
};
struct PIN_ADC_REFB_Q {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_C_01_uF_6_OUT *CONN_C_01_uF_6_OUT;
};
struct PIN_ADC_REFT_Q {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_C_01_uF_6_IN *CONN_C_01_uF_6_IN;
};
struct PIN_ADC_INB_Q {
	Outline outline;
	struct COMPONENT_ADC* parent;
	struct PIN_R5K_2_IN *CONN_R5K_2_IN;
};
struct PIN_ADC_INA_Q {
	Outline outline;
	struct COMPONENT_ADC* parent;
};
struct PIN_ADC_CHIP_SELECT {
	Outline outline;
	struct COMPONENT_ADC* parent;
};
struct PIN_analog_connector_P0 {
	Outline outline;
	struct COMPONENT_analog_connector* parent;
	struct PIN_ADC_INA_I *CONN_ADC_INA_I;
};
struct PIN_analog_connector_P1 {
	Outline outline;
	struct COMPONENT_analog_connector* parent;
	struct PIN_ADC_INA_Q *CONN_ADC_INA_Q;
};
struct PIN_analog_connector_P2 {
	Outline outline;
	struct COMPONENT_analog_connector* parent;
	struct PIN_router_162_in *CONN_router_162_in;
};
struct PIN_analog_connector_P3 {
	Outline outline;
	struct COMPONENT_analog_connector* parent;
};
struct PIN_analog_connector_P4 {
	Outline outline;
	struct COMPONENT_analog_connector* parent;
};
struct PIN_analog_connector_P5 {
	Outline outline;
	struct COMPONENT_analog_connector* parent;
};
struct PIN_analog_connector_P6 {
	Outline outline;
	struct COMPONENT_analog_connector* parent;
};
struct PIN_analog_connector_P7 {
	Outline outline;
	struct COMPONENT_analog_connector* parent;
};
struct PIN_analog_connector_P8 {
	Outline outline;
	struct COMPONENT_analog_connector* parent;
};
struct PIN_analog_connector_P9 {
	Outline outline;
	struct COMPONENT_analog_connector* parent;
};
struct PIN_AGND_GND {
	Outline outline;
	struct COMPONENT_AGND* parent;
};
struct PIN_DGND_GND {
	Outline outline;
	struct COMPONENT_DGND* parent;
	struct PIN_router_160_in *CONN_router_160_in;
};
struct PIN_fpga_connector_D9 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P1 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_D8 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P3 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_D7 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P5 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_D6 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P7 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_D5 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P9 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_D4 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_GND1 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
	struct PIN_router_161_in *CONN_router_161_in;
};
struct PIN_fpga_connector_D3 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P11 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_D2 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P13 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_D1 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P15 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_D0 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P19 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P20 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P21 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P22 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P23 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P24 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P25 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P26 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P27 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P28 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_GND2 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P30 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P31 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P32 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P33 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P34 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P35 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P36 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P37 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P38 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_fpga_connector_P39 {
	Outline outline;
	struct COMPONENT_fpga_connector* parent;
};
struct PIN_R0_IN {
	Outline outline;
	struct COMPONENT_R0* parent;
};
struct PIN_R0_OUT {
	Outline outline;
	struct COMPONENT_R0* parent;
	struct PIN_fpga_connector_D0 *CONN_fpga_connector_D0;
};
struct PIN_R1_IN {
	Outline outline;
	struct COMPONENT_R1* parent;
};
struct PIN_R1_OUT {
	Outline outline;
	struct COMPONENT_R1* parent;
	struct PIN_fpga_connector_D1 *CONN_fpga_connector_D1;
};
struct PIN_R2_IN {
	Outline outline;
	struct COMPONENT_R2* parent;
};
struct PIN_R2_OUT {
	Outline outline;
	struct COMPONENT_R2* parent;
	struct PIN_fpga_connector_D2 *CONN_fpga_connector_D2;
};
struct PIN_R3_IN {
	Outline outline;
	struct COMPONENT_R3* parent;
};
struct PIN_R3_OUT {
	Outline outline;
	struct COMPONENT_R3* parent;
	struct PIN_fpga_connector_D3 *CONN_fpga_connector_D3;
};
struct PIN_R4_IN {
	Outline outline;
	struct COMPONENT_R4* parent;
};
struct PIN_R4_OUT {
	Outline outline;
	struct COMPONENT_R4* parent;
	struct PIN_fpga_connector_D4 *CONN_fpga_connector_D4;
};
struct PIN_R5_IN {
	Outline outline;
	struct COMPONENT_R5* parent;
};
struct PIN_R5_OUT {
	Outline outline;
	struct COMPONENT_R5* parent;
	struct PIN_fpga_connector_D5 *CONN_fpga_connector_D5;
};
struct PIN_R6_IN {
	Outline outline;
	struct COMPONENT_R6* parent;
};
struct PIN_R6_OUT {
	Outline outline;
	struct COMPONENT_R6* parent;
	struct PIN_fpga_connector_D6 *CONN_fpga_connector_D6;
};
struct PIN_R7_IN {
	Outline outline;
	struct COMPONENT_R7* parent;
};
struct PIN_R7_OUT {
	Outline outline;
	struct COMPONENT_R7* parent;
	struct PIN_fpga_connector_D7 *CONN_fpga_connector_D7;
};
struct PIN_R8_IN {
	Outline outline;
	struct COMPONENT_R8* parent;
};
struct PIN_R8_OUT {
	Outline outline;
	struct COMPONENT_R8* parent;
	struct PIN_fpga_connector_D8 *CONN_fpga_connector_D8;
};
struct PIN_R9_IN {
	Outline outline;
	struct COMPONENT_R9* parent;
};
struct PIN_R9_OUT {
	Outline outline;
	struct COMPONENT_R9* parent;
	struct PIN_fpga_connector_D9 *CONN_fpga_connector_D9;
};
struct PIN_R5K_1_IN {
	Outline outline;
	struct COMPONENT_R5K_1* parent;
};
struct PIN_R5K_1_OUT {
	Outline outline;
	struct COMPONENT_R5K_1* parent;
	struct PIN_R5K_2_IN *CONN_R5K_2_IN;
};
struct PIN_R5K_2_IN {
	Outline outline;
	struct COMPONENT_R5K_2* parent;
	struct PIN_C_01_uF_2_IN *CONN_C_01_uF_2_IN;
	struct PIN_C_10_uF_2_IN *CONN_C_10_uF_2_IN;
};
struct PIN_R5K_2_OUT {
	Outline outline;
	struct COMPONENT_R5K_2* parent;
	struct PIN_router_165_in *CONN_router_165_in;
};
struct PIN_C_01_uF_1_IN {
	Outline outline;
	struct COMPONENT_C_01_uF_1* parent;
};
struct PIN_C_01_uF_1_OUT {
	Outline outline;
	struct COMPONENT_C_01_uF_1* parent;
	struct PIN_router_163_in *CONN_router_163_in;
};
struct PIN_C_10_uF_1_IN {
	Outline outline;
	struct COMPONENT_C_10_uF_1* parent;
};
struct PIN_C_10_uF_1_OUT {
	Outline outline;
	struct COMPONENT_C_10_uF_1* parent;
	struct PIN_router_164_in *CONN_router_164_in;
};
struct PIN_C_01_uF_2_IN {
	Outline outline;
	struct COMPONENT_C_01_uF_2* parent;
};
struct PIN_C_01_uF_2_OUT {
	Outline outline;
	struct COMPONENT_C_01_uF_2* parent;
	struct PIN_router_166_in *CONN_router_166_in;
};
struct PIN_C_10_uF_2_IN {
	Outline outline;
	struct COMPONENT_C_10_uF_2* parent;
};
struct PIN_C_10_uF_2_OUT {
	Outline outline;
	struct COMPONENT_C_10_uF_2* parent;
	struct PIN_router_167_in *CONN_router_167_in;
};
struct PIN_C_01_uF_3_IN {
	Outline outline;
	struct COMPONENT_C_01_uF_3* parent;
	struct PIN_C_10_uF_3_IN *CONN_C_10_uF_3_IN;
};
struct PIN_C_01_uF_3_OUT {
	Outline outline;
	struct COMPONENT_C_01_uF_3* parent;
	struct PIN_C_10_uF_3_OUT *CONN_C_10_uF_3_OUT;
};
struct PIN_C_10_uF_3_IN {
	Outline outline;
	struct COMPONENT_C_10_uF_3* parent;
	struct PIN_C_01_uF_4_IN *CONN_C_01_uF_4_IN;
};
struct PIN_C_10_uF_3_OUT {
	Outline outline;
	struct COMPONENT_C_10_uF_3* parent;
	struct PIN_C_01_uF_5_IN *CONN_C_01_uF_5_IN;
};
struct PIN_C_01_uF_4_IN {
	Outline outline;
	struct COMPONENT_C_01_uF_4* parent;
};
struct PIN_C_01_uF_4_OUT {
	Outline outline;
	struct COMPONENT_C_01_uF_4* parent;
	struct PIN_router_168_in *CONN_router_168_in;
};
struct PIN_C_01_uF_5_IN {
	Outline outline;
	struct COMPONENT_C_01_uF_5* parent;
};
struct PIN_C_01_uF_5_OUT {
	Outline outline;
	struct COMPONENT_C_01_uF_5* parent;
	struct PIN_router_169_in *CONN_router_169_in;
};
struct PIN_C_01_uF_6_IN {
	Outline outline;
	struct COMPONENT_C_01_uF_6* parent;
	struct PIN_C_10_uF_7_IN *CONN_C_10_uF_7_IN;
};
struct PIN_C_01_uF_6_OUT {
	Outline outline;
	struct COMPONENT_C_01_uF_6* parent;
	struct PIN_C_10_uF_7_OUT *CONN_C_10_uF_7_OUT;
};
struct PIN_C_10_uF_7_IN {
	Outline outline;
	struct COMPONENT_C_10_uF_7* parent;
	struct PIN_C_01_uF_8_IN *CONN_C_01_uF_8_IN;
};
struct PIN_C_10_uF_7_OUT {
	Outline outline;
	struct COMPONENT_C_10_uF_7* parent;
	struct PIN_C_01_uF_9_IN *CONN_C_01_uF_9_IN;
};
struct PIN_C_01_uF_8_IN {
	Outline outline;
	struct COMPONENT_C_01_uF_8* parent;
};
struct PIN_C_01_uF_8_OUT {
	Outline outline;
	struct COMPONENT_C_01_uF_8* parent;
	struct PIN_router_170_in *CONN_router_170_in;
};
struct PIN_C_01_uF_9_IN {
	Outline outline;
	struct COMPONENT_C_01_uF_9* parent;
};
struct PIN_C_01_uF_9_OUT {
	Outline outline;
	struct COMPONENT_C_01_uF_9* parent;
	struct PIN_router_171_in *CONN_router_171_in;
};
struct PIN_router_160_in {
	Outline outline;
	struct COMPONENT_router_160* parent;
};
struct PIN_router_160_out {
	Outline outline;
	struct COMPONENT_router_160* parent;
	struct PIN_AGND_GND *CONN_AGND_GND;
};
struct PIN_router_161_in {
	Outline outline;
	struct COMPONENT_router_161* parent;
};
struct PIN_router_161_out {
	Outline outline;
	struct COMPONENT_router_161* parent;
	struct PIN_DGND_GND *CONN_DGND_GND;
};
struct PIN_router_162_in {
	Outline outline;
	struct COMPONENT_router_162* parent;
};
struct PIN_router_162_out {
	Outline outline;
	struct COMPONENT_router_162* parent;
	struct PIN_AGND_GND *CONN_AGND_GND;
};
struct PIN_router_163_in {
	Outline outline;
	struct COMPONENT_router_163* parent;
};
struct PIN_router_163_out {
	Outline outline;
	struct COMPONENT_router_163* parent;
	struct PIN_AGND_GND *CONN_AGND_GND;
};
struct PIN_router_164_in {
	Outline outline;
	struct COMPONENT_router_164* parent;
};
struct PIN_router_164_out {
	Outline outline;
	struct COMPONENT_router_164* parent;
	struct PIN_AGND_GND *CONN_AGND_GND;
};
struct PIN_router_165_in {
	Outline outline;
	struct COMPONENT_router_165* parent;
};
struct PIN_router_165_out {
	Outline outline;
	struct COMPONENT_router_165* parent;
	struct PIN_AGND_GND *CONN_AGND_GND;
};
struct PIN_router_166_in {
	Outline outline;
	struct COMPONENT_router_166* parent;
};
struct PIN_router_166_out {
	Outline outline;
	struct COMPONENT_router_166* parent;
	struct PIN_AGND_GND *CONN_AGND_GND;
};
struct PIN_router_167_in {
	Outline outline;
	struct COMPONENT_router_167* parent;
};
struct PIN_router_167_out {
	Outline outline;
	struct COMPONENT_router_167* parent;
	struct PIN_AGND_GND *CONN_AGND_GND;
};
struct PIN_router_168_in {
	Outline outline;
	struct COMPONENT_router_168* parent;
};
struct PIN_router_168_out {
	Outline outline;
	struct COMPONENT_router_168* parent;
	struct PIN_AGND_GND *CONN_AGND_GND;
};
struct PIN_router_169_in {
	Outline outline;
	struct COMPONENT_router_169* parent;
};
struct PIN_router_169_out {
	Outline outline;
	struct COMPONENT_router_169* parent;
	struct PIN_AGND_GND *CONN_AGND_GND;
};
struct PIN_router_170_in {
	Outline outline;
	struct COMPONENT_router_170* parent;
};
struct PIN_router_170_out {
	Outline outline;
	struct COMPONENT_router_170* parent;
	struct PIN_AGND_GND *CONN_AGND_GND;
};
struct PIN_router_171_in {
	Outline outline;
	struct COMPONENT_router_171* parent;
};
struct PIN_router_171_out {
	Outline outline;
	struct COMPONENT_router_171* parent;
	struct PIN_AGND_GND *CONN_AGND_GND;
};
// declare component:
struct COMPONENT_board {
	Outline outline;
	Outline bounding_box;
};
struct COMPONENT_ADC {
	Outline outline;
	Outline bounding_box;
	struct PIN_ADC_DVSS ADC_DVSS;
	struct PIN_ADC_DVDD ADC_DVDD;
	struct PIN_ADC_D0 ADC_D0;
	struct PIN_ADC_D1 ADC_D1;
	struct PIN_ADC_D2 ADC_D2;
	struct PIN_ADC_D3 ADC_D3;
	struct PIN_ADC_D4 ADC_D4;
	struct PIN_ADC_D5 ADC_D5;
	struct PIN_ADC_D6 ADC_D6;
	struct PIN_ADC_D7 ADC_D7;
	struct PIN_ADC_D8 ADC_D8;
	struct PIN_ADC_D9 ADC_D9;
	struct PIN_ADC_SELECT ADC_SELECT;
	struct PIN_ADC_CLOCK ADC_CLOCK;
	struct PIN_ADC_SLEEP ADC_SLEEP;
	struct PIN_ADC_INA_I ADC_INA_I;
	struct PIN_ADC_INB_I ADC_INB_I;
	struct PIN_ADC_REFT_I ADC_REFT_I;
	struct PIN_ADC_REFB_I ADC_REFB_I;
	struct PIN_ADC_AVSS ADC_AVSS;
	struct PIN_ADC_REFSENSE ADC_REFSENSE;
	struct PIN_ADC_VREF ADC_VREF;
	struct PIN_ADC_AVDD ADC_AVDD;
	struct PIN_ADC_REFB_Q ADC_REFB_Q;
	struct PIN_ADC_REFT_Q ADC_REFT_Q;
	struct PIN_ADC_INB_Q ADC_INB_Q;
	struct PIN_ADC_INA_Q ADC_INA_Q;
	struct PIN_ADC_CHIP_SELECT ADC_CHIP_SELECT;
};
struct COMPONENT_analog_connector {
	Outline outline;
	Outline bounding_box;
	struct PIN_analog_connector_P0 analog_connector_P0;
	struct PIN_analog_connector_P1 analog_connector_P1;
	struct PIN_analog_connector_P2 analog_connector_P2;
	struct PIN_analog_connector_P3 analog_connector_P3;
	struct PIN_analog_connector_P4 analog_connector_P4;
	struct PIN_analog_connector_P5 analog_connector_P5;
	struct PIN_analog_connector_P6 analog_connector_P6;
	struct PIN_analog_connector_P7 analog_connector_P7;
	struct PIN_analog_connector_P8 analog_connector_P8;
	struct PIN_analog_connector_P9 analog_connector_P9;
};
struct COMPONENT_AGND {
	Outline outline;
	Outline bounding_box;
	struct PIN_AGND_GND AGND_GND;
};
struct COMPONENT_DGND {
	Outline outline;
	Outline bounding_box;
	struct PIN_DGND_GND DGND_GND;
};
struct COMPONENT_fpga_connector {
	Outline outline;
	Outline bounding_box;
	struct PIN_fpga_connector_D9 fpga_connector_D9;
	struct PIN_fpga_connector_P1 fpga_connector_P1;
	struct PIN_fpga_connector_D8 fpga_connector_D8;
	struct PIN_fpga_connector_P3 fpga_connector_P3;
	struct PIN_fpga_connector_D7 fpga_connector_D7;
	struct PIN_fpga_connector_P5 fpga_connector_P5;
	struct PIN_fpga_connector_D6 fpga_connector_D6;
	struct PIN_fpga_connector_P7 fpga_connector_P7;
	struct PIN_fpga_connector_D5 fpga_connector_D5;
	struct PIN_fpga_connector_P9 fpga_connector_P9;
	struct PIN_fpga_connector_D4 fpga_connector_D4;
	struct PIN_fpga_connector_GND1 fpga_connector_GND1;
	struct PIN_fpga_connector_D3 fpga_connector_D3;
	struct PIN_fpga_connector_P11 fpga_connector_P11;
	struct PIN_fpga_connector_D2 fpga_connector_D2;
	struct PIN_fpga_connector_P13 fpga_connector_P13;
	struct PIN_fpga_connector_D1 fpga_connector_D1;
	struct PIN_fpga_connector_P15 fpga_connector_P15;
	struct PIN_fpga_connector_D0 fpga_connector_D0;
	struct PIN_fpga_connector_P19 fpga_connector_P19;
	struct PIN_fpga_connector_P20 fpga_connector_P20;
	struct PIN_fpga_connector_P21 fpga_connector_P21;
	struct PIN_fpga_connector_P22 fpga_connector_P22;
	struct PIN_fpga_connector_P23 fpga_connector_P23;
	struct PIN_fpga_connector_P24 fpga_connector_P24;
	struct PIN_fpga_connector_P25 fpga_connector_P25;
	struct PIN_fpga_connector_P26 fpga_connector_P26;
	struct PIN_fpga_connector_P27 fpga_connector_P27;
	struct PIN_fpga_connector_P28 fpga_connector_P28;
	struct PIN_fpga_connector_GND2 fpga_connector_GND2;
	struct PIN_fpga_connector_P30 fpga_connector_P30;
	struct PIN_fpga_connector_P31 fpga_connector_P31;
	struct PIN_fpga_connector_P32 fpga_connector_P32;
	struct PIN_fpga_connector_P33 fpga_connector_P33;
	struct PIN_fpga_connector_P34 fpga_connector_P34;
	struct PIN_fpga_connector_P35 fpga_connector_P35;
	struct PIN_fpga_connector_P36 fpga_connector_P36;
	struct PIN_fpga_connector_P37 fpga_connector_P37;
	struct PIN_fpga_connector_P38 fpga_connector_P38;
	struct PIN_fpga_connector_P39 fpga_connector_P39;
};
struct COMPONENT_R0 {
	Outline outline;
	Outline bounding_box;
	struct PIN_R0_IN R0_IN;
	struct PIN_R0_OUT R0_OUT;
};
struct COMPONENT_R1 {
	Outline outline;
	Outline bounding_box;
	struct PIN_R1_IN R1_IN;
	struct PIN_R1_OUT R1_OUT;
};
struct COMPONENT_R2 {
	Outline outline;
	Outline bounding_box;
	struct PIN_R2_IN R2_IN;
	struct PIN_R2_OUT R2_OUT;
};
struct COMPONENT_R3 {
	Outline outline;
	Outline bounding_box;
	struct PIN_R3_IN R3_IN;
	struct PIN_R3_OUT R3_OUT;
};
struct COMPONENT_R4 {
	Outline outline;
	Outline bounding_box;
	struct PIN_R4_IN R4_IN;
	struct PIN_R4_OUT R4_OUT;
};
struct COMPONENT_R5 {
	Outline outline;
	Outline bounding_box;
	struct PIN_R5_IN R5_IN;
	struct PIN_R5_OUT R5_OUT;
};
struct COMPONENT_R6 {
	Outline outline;
	Outline bounding_box;
	struct PIN_R6_IN R6_IN;
	struct PIN_R6_OUT R6_OUT;
};
struct COMPONENT_R7 {
	Outline outline;
	Outline bounding_box;
	struct PIN_R7_IN R7_IN;
	struct PIN_R7_OUT R7_OUT;
};
struct COMPONENT_R8 {
	Outline outline;
	Outline bounding_box;
	struct PIN_R8_IN R8_IN;
	struct PIN_R8_OUT R8_OUT;
};
struct COMPONENT_R9 {
	Outline outline;
	Outline bounding_box;
	struct PIN_R9_IN R9_IN;
	struct PIN_R9_OUT R9_OUT;
};
struct COMPONENT_R5K_1 {
	Outline outline;
	Outline bounding_box;
	struct PIN_R5K_1_IN R5K_1_IN;
	struct PIN_R5K_1_OUT R5K_1_OUT;
};
struct COMPONENT_R5K_2 {
	Outline outline;
	Outline bounding_box;
	struct PIN_R5K_2_IN R5K_2_IN;
	struct PIN_R5K_2_OUT R5K_2_OUT;
};
struct COMPONENT_C_01_uF_1 {
	Outline outline;
	Outline bounding_box;
	struct PIN_C_01_uF_1_IN C_01_uF_1_IN;
	struct PIN_C_01_uF_1_OUT C_01_uF_1_OUT;
};
struct COMPONENT_C_10_uF_1 {
	Outline outline;
	Outline bounding_box;
	struct PIN_C_10_uF_1_IN C_10_uF_1_IN;
	struct PIN_C_10_uF_1_OUT C_10_uF_1_OUT;
};
struct COMPONENT_C_01_uF_2 {
	Outline outline;
	Outline bounding_box;
	struct PIN_C_01_uF_2_IN C_01_uF_2_IN;
	struct PIN_C_01_uF_2_OUT C_01_uF_2_OUT;
};
struct COMPONENT_C_10_uF_2 {
	Outline outline;
	Outline bounding_box;
	struct PIN_C_10_uF_2_IN C_10_uF_2_IN;
	struct PIN_C_10_uF_2_OUT C_10_uF_2_OUT;
};
struct COMPONENT_C_01_uF_3 {
	Outline outline;
	Outline bounding_box;
	struct PIN_C_01_uF_3_IN C_01_uF_3_IN;
	struct PIN_C_01_uF_3_OUT C_01_uF_3_OUT;
};
struct COMPONENT_C_10_uF_3 {
	Outline outline;
	Outline bounding_box;
	struct PIN_C_10_uF_3_IN C_10_uF_3_IN;
	struct PIN_C_10_uF_3_OUT C_10_uF_3_OUT;
};
struct COMPONENT_C_01_uF_4 {
	Outline outline;
	Outline bounding_box;
	struct PIN_C_01_uF_4_IN C_01_uF_4_IN;
	struct PIN_C_01_uF_4_OUT C_01_uF_4_OUT;
};
struct COMPONENT_C_01_uF_5 {
	Outline outline;
	Outline bounding_box;
	struct PIN_C_01_uF_5_IN C_01_uF_5_IN;
	struct PIN_C_01_uF_5_OUT C_01_uF_5_OUT;
};
struct COMPONENT_C_01_uF_6 {
	Outline outline;
	Outline bounding_box;
	struct PIN_C_01_uF_6_IN C_01_uF_6_IN;
	struct PIN_C_01_uF_6_OUT C_01_uF_6_OUT;
};
struct COMPONENT_C_10_uF_7 {
	Outline outline;
	Outline bounding_box;
	struct PIN_C_10_uF_7_IN C_10_uF_7_IN;
	struct PIN_C_10_uF_7_OUT C_10_uF_7_OUT;
};
struct COMPONENT_C_01_uF_8 {
	Outline outline;
	Outline bounding_box;
	struct PIN_C_01_uF_8_IN C_01_uF_8_IN;
	struct PIN_C_01_uF_8_OUT C_01_uF_8_OUT;
};
struct COMPONENT_C_01_uF_9 {
	Outline outline;
	Outline bounding_box;
	struct PIN_C_01_uF_9_IN C_01_uF_9_IN;
	struct PIN_C_01_uF_9_OUT C_01_uF_9_OUT;
};
struct COMPONENT_router_160 {
	Outline outline;
	Outline bounding_box;
	struct PIN_router_160_in router_160_in;
	struct PIN_router_160_out router_160_out;
};
struct COMPONENT_router_161 {
	Outline outline;
	Outline bounding_box;
	struct PIN_router_161_in router_161_in;
	struct PIN_router_161_out router_161_out;
};
struct COMPONENT_router_162 {
	Outline outline;
	Outline bounding_box;
	struct PIN_router_162_in router_162_in;
	struct PIN_router_162_out router_162_out;
};
struct COMPONENT_router_163 {
	Outline outline;
	Outline bounding_box;
	struct PIN_router_163_in router_163_in;
	struct PIN_router_163_out router_163_out;
};
struct COMPONENT_router_164 {
	Outline outline;
	Outline bounding_box;
	struct PIN_router_164_in router_164_in;
	struct PIN_router_164_out router_164_out;
};
struct COMPONENT_router_165 {
	Outline outline;
	Outline bounding_box;
	struct PIN_router_165_in router_165_in;
	struct PIN_router_165_out router_165_out;
};
struct COMPONENT_router_166 {
	Outline outline;
	Outline bounding_box;
	struct PIN_router_166_in router_166_in;
	struct PIN_router_166_out router_166_out;
};
struct COMPONENT_router_167 {
	Outline outline;
	Outline bounding_box;
	struct PIN_router_167_in router_167_in;
	struct PIN_router_167_out router_167_out;
};
struct COMPONENT_router_168 {
	Outline outline;
	Outline bounding_box;
	struct PIN_router_168_in router_168_in;
	struct PIN_router_168_out router_168_out;
};
struct COMPONENT_router_169 {
	Outline outline;
	Outline bounding_box;
	struct PIN_router_169_in router_169_in;
	struct PIN_router_169_out router_169_out;
};
struct COMPONENT_router_170 {
	Outline outline;
	Outline bounding_box;
	struct PIN_router_170_in router_170_in;
	struct PIN_router_170_out router_170_out;
};
struct COMPONENT_router_171 {
	Outline outline;
	Outline bounding_box;
	struct PIN_router_171_in router_171_in;
	struct PIN_router_171_out router_171_out;
};

typedef struct Model {
	struct COMPONENT_board board;
	struct COMPONENT_ADC ADC;
	struct COMPONENT_analog_connector analog_connector;
	struct COMPONENT_AGND AGND;
	struct COMPONENT_DGND DGND;
	struct COMPONENT_fpga_connector fpga_connector;
	struct COMPONENT_R0 R0;
	struct COMPONENT_R1 R1;
	struct COMPONENT_R2 R2;
	struct COMPONENT_R3 R3;
	struct COMPONENT_R4 R4;
	struct COMPONENT_R5 R5;
	struct COMPONENT_R6 R6;
	struct COMPONENT_R7 R7;
	struct COMPONENT_R8 R8;
	struct COMPONENT_R9 R9;
	struct COMPONENT_R5K_1 R5K_1;
	struct COMPONENT_R5K_2 R5K_2;
	struct COMPONENT_C_01_uF_1 C_01_uF_1;
	struct COMPONENT_C_10_uF_1 C_10_uF_1;
	struct COMPONENT_C_01_uF_2 C_01_uF_2;
	struct COMPONENT_C_10_uF_2 C_10_uF_2;
	struct COMPONENT_C_01_uF_3 C_01_uF_3;
	struct COMPONENT_C_10_uF_3 C_10_uF_3;
	struct COMPONENT_C_01_uF_4 C_01_uF_4;
	struct COMPONENT_C_01_uF_5 C_01_uF_5;
	struct COMPONENT_C_01_uF_6 C_01_uF_6;
	struct COMPONENT_C_10_uF_7 C_10_uF_7;
	struct COMPONENT_C_01_uF_8 C_01_uF_8;
	struct COMPONENT_C_01_uF_9 C_01_uF_9;
	struct COMPONENT_router_160 router_160;
	struct COMPONENT_router_161 router_161;
	struct COMPONENT_router_162 router_162;
	struct COMPONENT_router_163 router_163;
	struct COMPONENT_router_164 router_164;
	struct COMPONENT_router_165 router_165;
	struct COMPONENT_router_166 router_166;
	struct COMPONENT_router_167 router_167;
	struct COMPONENT_router_168 router_168;
	struct COMPONENT_router_169 router_169;
	struct COMPONENT_router_170 router_170;
	struct COMPONENT_router_171 router_171;
} Model;


typedef struct ModelInfo
{
  
} ModelInfo;


void get_model_info(__global int *data)
{
  data[0] = sizeof(Model);
  data[1] = sizeof(ModelInfo);
}

void set_model_info(__global ModelInfo *info)
{
  
}

void link_model(__global Model *model, __global ModelInfo *info)
{
  
}

__kernel
void optimize()
{
}
