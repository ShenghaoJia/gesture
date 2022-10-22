#ifndef MODEL_GRAPHINFO_H
#define MODEL_GRAPHINFO_H
// Quantized scales can be used round_norm(val * QSCALE, QNORM) giving the real value in Q8

// S0_Op_input_1
#define S0_Op_input_1_OUT_SCALE	1
#define S0_Op_input_1_OUT_QSCALE	0
#define S0_Op_input_1_OUT_QNORM	0
// S1_Op_input_1_formatter
#define S1_Op_input_1_formatter_OUT_SCALE	0.0078125
#define S1_Op_input_1_formatter_OUT_QSCALE	64
#define S1_Op_input_1_formatter_OUT_QNORM	13
// S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu
#define S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu_OUT_SCALE	0.005276143085211515
#define S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu_OUT_QSCALE	86
#define S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu_OUT_QNORM	14
// S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu
#define S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu_OUT_SCALE	0.00419040210545063
#define S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu_OUT_QSCALE	69
#define S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu_OUT_QNORM	14
// S4_Conv2d_128x64x3x3_MaxPool_2x2_Relu
#define S4_Conv2d_128x64x3x3_MaxPool_2x2_Relu_OUT_SCALE	0.007066009100526571
#define S4_Conv2d_128x64x3x3_MaxPool_2x2_Relu_OUT_QSCALE	116
#define S4_Conv2d_128x64x3x3_MaxPool_2x2_Relu_OUT_QNORM	14
// S5_Linear_64x13x18x128
#define S5_Linear_64x13x18x128_OUT_SCALE	0.0168744008988142
#define S5_Linear_64x13x18x128_OUT_QSCALE	69
#define S5_Linear_64x13x18x128_OUT_QNORM	12
// S6_Linear_2x64
#define S6_Linear_2x64_OUT_SCALE	0.125
#define S6_Linear_2x64_OUT_QSCALE	64
#define S6_Linear_2x64_OUT_QNORM	9
// S7_SoftMax
#define S7_SoftMax_OUT_SCALE	3.0517578125e-05
#define S7_SoftMax_OUT_QSCALE	64
#define S7_SoftMax_OUT_QNORM	21
// S8_Op_output_1
#define S8_Op_output_1_OUT_SCALE	3.0517578125e-05
#define S8_Op_output_1_OUT_QSCALE	64
#define S8_Op_output_1_OUT_QNORM	21
#endif //MODEL_GRAPHINFO_H