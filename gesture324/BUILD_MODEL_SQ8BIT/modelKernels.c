#include "modelKernels.h"
L1_CL_MEM AT_L1_POINTER model_L1_Memory;
L2_MEM AT_L2_POINTER model_L2_Memory;
AT_HYPERRAM_POINTER model_L3_Memory;
static AT_HYPERRAM_T HyperRam;
static AT_HYPERFLASH_FS_T HyperFlash;
void S1_Op_input_1_formatter(
		unsigned char * __restrict__ In,
		signed char * __restrict__ Out)

{
	/* Shared L1: 47952 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerNormBW_fps_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 7]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 79056 [Tile0, 7:[324x37, 5:324x37, 324x22], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[324x37, 5:324x37, 324x22], 1]
		Tile0: [0, 11988, 11988], Tile1: [11988, 11988, 11988], Tile2; [23976, 11988, 11988]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 7 logical tiles, 7 physical tiles
			Total Size: 79056 [Tile0, 7:[324x37, 5:324x37, 324x22], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 7:[324x37, 5:324x37, 324x22], 1]
		Tile0: [0, 11988, 11988], Tile1: [11988, 11988, 11988], Tile2; [23976, 11988, 11988]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->W = (unsigned short int) (324);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+0), 11988, 0, &DmaR_Evt1);
	_N_In=0;
	_C_Out=0; _SC_Out=11988;
	_SPP_Out=0; _SP_Out=0;
	/*============================= End Read Tiles Prolog ===============================*/
	for (T0Ind=0; T0Ind<7; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
		int T0Ind_Last = (T0Ind==6), T0Ind_NextLast = ((T0Ind+1)==6);
		/*================================= Prepare Tiles ===================================*/
		_SN_In = 0;
		if (!(T0Ind_Last)) {
			_N_In = _N_In + (11988); _SN_In = ((T0Ind_NextLast)?7128:11988); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
		if (_SN_In) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+11988*((T0Ind_Total+1)%2)),
					_SN_In, 0, &DmaR_Evt1);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->In = (unsigned char *__restrict__) (model_L1_Memory+0+11988*((T0Ind_Total)%2));
		KerArg0->Out = (signed char *__restrict__) (model_L1_Memory+23976+11988*((T0Ind_Total)%2));
		KerArg0->H = (unsigned short int) (T0Ind_Last?22:37);
		AT_FORK(gap_ncore(), (void *) CNN_NormBW_offset_fps, (void *) KerArg0);
		__CALL(CNN_NormBW_offset_fps, KerArg0);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
		if (_SP_Out) AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+20664+11988*((T0Ind_Total+-1)%2)),
					_SP_Out, 1, &UchanHR1);
		AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+20664+11988*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+23976+11988*((T0Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SPP_Out = _SP_Out;
		_P_Out = _C_Out;_SP_Out = _SC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		if (!(T0Ind_Last)) {
			_C_Out = _C_Out + (11988); _SC_Out = ((T0Ind_NextLast)?7128:11988); 
		}
		/*============================= End Prepare Tiles ===================================*/
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+20664+11988*((T0Ind_Total+-1)%2)), _SP_Out, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 38436 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerConvLinReduct_SQ8_T S_KerArg2, *KerArg2 = &S_KerArg2;
	KerPool_SQ8_T S_KerArg3, *KerArg3 = &S_KerArg3;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Total=0, D1Ind_Last, D1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 32, Tiled: 2][Tile0 Dim: 60][D0 Dim: Init: 1, Tiled: 1]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 120 logical tiles, 120 physical tiles
			Total Size: 153600 [D1, [1 x 115200, 38400]][Tile0, 60:[80x1, 58:80x1, 80x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 115200, 38400]][Tile0, 60:[80x1, 58:80x1, 80x1], 1]
		Tile0: [0, 1920, 80], Tile1: [80, 1920, 80], Tile2; [160, 1920, 80]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [1 x 96, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 96, 32]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 32 [D1, [1 x 24, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 24, 8]]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 32 [D1, [1 x 24, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 24, 8]]
		Tile0: [0, 32, 32], Tile1: [0, 32, 32], Tile2; [0, 32, 32]
	Ker Arg: Filter, Tiled Space: D1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 120 logical tiles, 2 physical tiles
			Total Size: 288 [D1, [1 x 216, 72]][D0, [0 x 216, 216]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 216, 72]][D0, [0 x 216, 216]]
		Tile0: [0, 216, 9], Tile1: [216, 72, 9], Tile2; [0, 216, 9]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 60 logical tiles, 60 physical tiles
			Total Size: 79056 [D0, [0 x 79056, 79056]][Tile0, 60:[324x5, 58:324x5, 324x5], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 60:[324x5, 58:324x5, 324x5], 1][D0, [0 x 79056, 79056]]
		Tile0: [0, 1620, 1620], Tile1: [1296, 1620, 1620], Tile2; [2592, 1620, 1620]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 120 logical tiles, 1 physical tiles
			Total Size: 2457600 [D1, [1 x 1843200, 614400]][Tile0, 60:[160x2, 58:160x2, 160x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 1843200, 614400]][Tile0, 60:[160x2, 58:160x2, 160x2], 4]
		Tile0: [0, 30720, 1280], Tile1: [0, 30720, 1280], Tile2; [0, 30720, 1280]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 60 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 60:[9x1, 58:9x1, 9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 60:[9x1, 58:9x1, 9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (model_L1_Memory+7704);
	KerArg0->W = (unsigned short int) (160);
	KerArg0->H = (unsigned short int) (2);
	KerArg1->W = (unsigned short int) (324);
	KerArg1->UsedW = (unsigned short int) (321);
	KerArg1->H = (unsigned short int) (5);
	KerArg1->UsedH = (unsigned short int) (5);
	KerArg1->InFeatures = (unsigned short int) (1);
	KerArg1->TotalInFeatures = (unsigned short int) (1);
	KerArg1->Out = (int * __restrict__) (model_L1_Memory+7704);
	KerArg1->Pad = (v4s) 0;
	KerArg2->In = (int *__restrict__) (model_L1_Memory+7704);
	KerArg2->Out = (void *__restrict__) (model_L1_Memory+7704);
	KerArg2->W = (unsigned short int) (160);
	KerArg2->H = (unsigned short int) (2);
	KerArg2->Infos = (signed char *__restrict__) (model_L1_Memory+38424);
	KerArg3->In = (signed char * __restrict__) (model_L1_Memory+7704);
	KerArg3->W = (unsigned short int) (160);
	KerArg3->UsedW = (unsigned short int) (160);
	KerArg3->H = (unsigned short int) (2);
	KerArg3->UsedH = (unsigned short int) (2);
	KerArg3->Pad = (v4s) 0;
	KerArg3->PoolMax = (unsigned char) (1);
	KerArg3->DoScale = (unsigned char) (0);
	KerArg3->Infos = (signed char * __restrict__) (model_L1_Memory+38424);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=1920; _LC_Out=80;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3240), 128, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3368), 32, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3400), 32, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3432+0), 216, 0, &DmaR_Evt4);
	_N_Filter=0;
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+174264+0), 1620, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+1296), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+174264+1620), 1620, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+174264+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+0), 1620, 0, &DmaR_Evt5);
	_NN_In=1296; _SN_In=1620;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+38424), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++, D1Ind_Total++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1);
		/*================================= Prepare Tiles ===================================*/
		_SN_Filter = 0;
		if (!(D1Ind_Last)) {
			_N_Filter = _N_Filter + (216); _SN_Filter = ((1)?72:216); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Filter */
		if (_SN_Filter) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3432+216*((D1Ind_Total+1)%2)),
					_SN_Filter, 0, &DmaR_Evt4);
		}
		/*============================= End Read Tiles ======================================*/
		for (T0Ind=0; T0Ind<60; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==59), T0Ind_NextLast = ((T0Ind+1)==59), T0Ind_NextNextLast = ((T0Ind+2)==59);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->Feat = (unsigned short int) (D1Ind_Last?8:24);
			KerArg0->Bias = (void * __restrict__) (model_L1_Memory+3240+((D1Ind)*96));
			KerArg0->NormBias = (unsigned char) (((char *)(model_L1_Memory+38424))[5]);
			AT_FORK(gap_ncore(), (void *) KerParSetBiasB32_SQ8, (void *) KerArg0);
			__CALL(KerParSetBiasB32_SQ8, KerArg0);
			{ /* Single iteration on D0 */
				int D0Ind_Last = 1, D0Ind_NextLast = 1, D0Ind_NextNextLast = 1;
				/*================================= Prepare Tiles ===================================*/
				_SNN_In = 0;
				if (!(T0Ind_Last)) {
					if (!(T0Ind_NextLast)) {
						_NN_In = _NN_In + (1296); _SNN_In = (1620); 
					} else if (!(D1Ind_Last)) {
						_NN_In = _NN_In + (-76464); _SNN_In = (1620); 
					}
				} else if (!((D1Ind_Last))) {
					_NN_In = _NN_In + (1296); _SNN_In = (1620); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+174264+1620*((D0Ind_Total)%2)),
							_SNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+174264+1620*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+1620*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt5);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (signed char * __restrict__) (model_L1_Memory+0+1620*((D0Ind_Total)%2));
				KerArg1->OutFeatures = (unsigned short int) (D1Ind_Last?8:24);
				KerArg1->Filter = (signed char * __restrict__) (model_L1_Memory+3432+216*((D1Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride2_SQ8, (void *) KerArg1);
				__CALL(KerParConv3x3Stride2_SQ8, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;
				/*============================= End Update Arg Pipeline =============================*/
				D0Ind_Total++;
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Feat = (unsigned short int) (D1Ind_Last?8:24);
			KerArg2->Scale = (unsigned char *__restrict__) (model_L1_Memory+3368+((D1Ind)*24));
			KerArg2->ScaleN = (unsigned char *__restrict__) (model_L1_Memory+3400+((D1Ind)*24));
			AT_FORK(gap_ncore(), (void *) KerParReductIO_CC_SQ8, (void *) KerArg2);
			__CALL(KerParReductIO_CC_SQ8, KerArg2);
			KerArg3->Feat = (unsigned short int) (D1Ind_Last?8:24);
			KerArg3->Out = (signed char * __restrict__) (model_L1_Memory+3864+1920*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParPool2x2Stride2_ReLU_SQ8, (void *) KerArg3);
			__CALL(KerParPool2x2Stride2_ReLU_SQ8, KerArg3);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3864+1920*((T0Ind_Total)%2)),
					_SC_Out, 4800, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (80); _LC_Out = (80); _SC_Out = (((D1Ind_Last)?8:24)*_LC_Out); 
			} else if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (115200)+(-4720); _LC_Out = (80); _SC_Out = (((1)?8:24)*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
		/*================================= Update Arg Pipeline =============================*/
		/*============================= End Update Arg Pipeline =============================*/
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 46412 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerConvLinReduct_SQ8_T S_KerArg2, *KerArg2 = &S_KerArg2;
	KerPool_SQ8_T S_KerArg3, *KerArg3 = &S_KerArg3;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Total=0, D1Ind_Last, D1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast;
	/* User kernel arguments related variables */
	unsigned int _P_Out, _C_Out;
	unsigned int _SPP_Out, _SP_Out, _SC_Out;
	unsigned int _LPP_Out, _LP_Out, _LC_Out;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _LN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 64, Tiled: 2][Tile0 Dim: 29][D0 Dim: Init: 32, Tiled: 4]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -2, Max Pipe Depth: 0
		KerArgItSpace: 58 logical tiles, 58 physical tiles
			Total Size: 72384 [D1, [1 x 36192, 36192]][Tile0, 29:[39x1, 27:39x1, 39x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 36192, 36192]][Tile0, 29:[39x1, 27:39x1, 39x1], 1]
		Tile0: [0, 1248, 39], Tile1: [39, 1248, 39], Tile2; [78, 1248, 39]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 256 [D1, [1 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 128, 128]]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 64 [D1, [1 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 32]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 2 logical tiles, 1 physical tiles
			Total Size: 64 [D1, [1 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 32, 32]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Filter, Tiled Space: D1
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 232 logical tiles, 2 physical tiles
			Total Size: 18432 [D1, [1 x 9216, 9216]][D0, [3 x 2304, 2304]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 9216, 9216]][D0, [3 x 2304, 2304]]
		Tile0: [0, 9216, 288], Tile1: [9216, 9216, 288], Tile2; [0, 9216, 288]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 116 logical tiles, 116 physical tiles
			Total Size: 153600 [D0, [3 x 38400, 38400]][Tile0, 29:[80x4, 27:80x4, 80x4], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 29:[80x4, 27:80x4, 80x4], 1][D0, [3 x 38400, 38400]]
		Tile0: [0, 2560, 320], Tile1: [38400, 2560, 320], Tile2; [76800, 2560, 320]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 58 logical tiles, 1 physical tiles
			Total Size: 1158144 [D1, [1 x 579072, 579072]][Tile0, 29:[78x2, 27:78x2, 78x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [1 x 579072, 579072]][Tile0, 29:[78x2, 27:78x2, 78x2], 4]
		Tile0: [0, 19968, 624], Tile1: [0, 19968, 624], Tile2; [0, 19968, 624]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 29 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 29:[9x1, 27:9x1, 9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 29:[9x1, 27:9x1, 9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (model_L1_Memory+26432);
	KerArg0->W = (unsigned short int) (78);
	KerArg0->H = (unsigned short int) (2);
	KerArg0->Feat = (unsigned short int) (32);
	KerArg1->W = (unsigned short int) (80);
	KerArg1->UsedW = (unsigned short int) (80);
	KerArg1->H = (unsigned short int) (4);
	KerArg1->UsedH = (unsigned short int) (4);
	KerArg1->InFeatures = (unsigned short int) (8);
	KerArg1->OutFeatures = (unsigned short int) (32);
	KerArg1->TotalInFeatures = (unsigned short int) (32);
	KerArg1->Out = (int * __restrict__) (model_L1_Memory+26432);
	KerArg1->Pad = (v4s) 0;
	KerArg2->In = (int *__restrict__) (model_L1_Memory+26432);
	KerArg2->Out = (void *__restrict__) (model_L1_Memory+26432);
	KerArg2->Feat = (unsigned short int) (32);
	KerArg2->W = (unsigned short int) (78);
	KerArg2->H = (unsigned short int) (2);
	KerArg2->Infos = (signed char *__restrict__) (model_L1_Memory+46400);
	KerArg3->In = (signed char * __restrict__) (model_L1_Memory+26432);
	KerArg3->W = (unsigned short int) (78);
	KerArg3->UsedW = (unsigned short int) (78);
	KerArg3->H = (unsigned short int) (2);
	KerArg3->UsedH = (unsigned short int) (2);
	KerArg3->Feat = (unsigned short int) (32);
	KerArg3->Pad = (v4s) 0;
	KerArg3->PoolMax = (unsigned char) (1);
	KerArg3->DoScale = (unsigned char) (0);
	KerArg3->Infos = (signed char * __restrict__) (model_L1_Memory+46400);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=1248; _LC_Out=39;
	_SPP_Out=0; _SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+5120), 256, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+5376), 64, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+5440), 64, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+5504+0), 9216, 0, &DmaR_Evt4);
	_N_Filter=0;
	AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+0), 2560, 4800, 320, 0, &DmaR_Evt5);
	_N_In=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+46400), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<2; D1Ind++, D1Ind_Total++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==1), D1Ind_NextLast = ((D1Ind+1)==1);
		/*================================= Prepare Tiles ===================================*/
		_SN_Filter = 0;
		if (!(D1Ind_Last)) {
			_N_Filter = _N_Filter + (9216); _SN_Filter = (9216); 
		}
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Filter */
		if (_SN_Filter) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+5504+9216*((D1Ind_Total+1)%2)),
					_SN_Filter, 0, &DmaR_Evt4);
		}
		/*============================= End Read Tiles ======================================*/
		for (T0Ind=0; T0Ind<29; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==28), T0Ind_NextLast = ((T0Ind+1)==28);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->Bias = (void * __restrict__) (model_L1_Memory+5120+((D1Ind)*128));
			KerArg0->NormBias = (unsigned char) (((char *)(model_L1_Memory+46400))[5]);
			AT_FORK(gap_ncore(), (void *) KerParSetBiasB32_SQ8, (void *) KerArg0);
			__CALL(KerParSetBiasB32_SQ8, KerArg0);
			for (D0Ind=0; D0Ind<4; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==3), D0Ind_NextLast = ((D0Ind+1)==3);
				/*================================= Prepare Tiles ===================================*/
				_SN_In = 0;
				if (!(D0Ind_Last)) {
					_N_In = _N_In + (38400); _LN_In = (320); _SN_In = (8*_LN_In); 
				} else if (!(T0Ind_Last)) {
					_N_In = _N_In + (160)+(-115200); _LN_In = (320); _SN_In = (8*_LN_In); 
				} else if (!(D1Ind_Last)) {
					_N_In = _N_In + (-4480)+(-115200); _LN_In = (320); _SN_In = (8*_LN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+2560*((D0Ind_Total+1)%2)),
							_SN_In, 4800, _LN_In, 0, &DmaR_Evt5);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (signed char * __restrict__) (model_L1_Memory+0+2560*((D0Ind_Total)%2));
				KerArg1->Filter = (signed char * __restrict__) (model_L1_Memory+5504+((D0Ind)*72)+9216*((D1Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_SQ8, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_SQ8, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->Scale = (unsigned char *__restrict__) (model_L1_Memory+5376+((D1Ind)*32));
			KerArg2->ScaleN = (unsigned char *__restrict__) (model_L1_Memory+5440+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParReductIO_CC_SQ8, (void *) KerArg2);
			__CALL(KerParReductIO_CC_SQ8, KerArg2);
			KerArg3->Out = (signed char * __restrict__) (model_L1_Memory+23936+1248*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParPool2x2Stride2_ReLU_SQ8, (void *) KerArg3);
			__CALL(KerParPool2x2Stride2_ReLU_SQ8, KerArg3);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
			if (_SP_Out) AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+174264+1248*((T0Ind_Total+-1)%2)),
						_SP_Out, 1131, _LP_Out, 1, &UchanHR1);
			AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+174264+1248*((T0Ind_Total)%2)), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+23936+1248*((T0Ind_Total)%2)),
					_SC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SPP_Out = _SP_Out;_LPP_Out = _LP_Out;
			_P_Out = _C_Out;_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (39); _LC_Out = (39); _SC_Out = (32*_LC_Out); 
			} else if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (36192)+(-1092); _LC_Out = (39); _SC_Out = (32*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
		/*================================= Update Arg Pipeline =============================*/
		/*============================= End Update Arg Pipeline =============================*/
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	if (_SPP_Out) AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA write Out */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Out+_P_Out), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+174264+1248*((T0Ind_Total+-1)%2)), _SP_Out, 1131, _LP_Out, 1, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait current uDMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S4_Conv2d_128x64x3x3_MaxPool_2x2_Relu(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 47676 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerConv_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerConvLinReduct_SQ8_T S_KerArg2, *KerArg2 = &S_KerArg2;
	KerPool_SQ8_T S_KerArg3, *KerArg3 = &S_KerArg3;

	/* Iteration space related variables */
	int D1Ind, D1Ind_Last, D1Ind_NextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _LP_Out, _LC_Out;
	unsigned int _N_Filter;
	unsigned int _SN_Filter;
	unsigned int _LN_Filter;
	unsigned int _NN_In;
	unsigned int _SN_In, _SNN_In;
	unsigned int _LN_In, _LNN_In;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D1 Dim: Init: 128, Tiled: 4][Tile0 Dim: 4][D0 Dim: Init: 64, Tiled: 16]
	Ker Arg: Out, Tiled Space: Tile0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 16 logical tiles, 16 physical tiles
			Total Size: 29952 [D1, [3 x 7488, 7488]][Tile0, 4:[18x4, 2:18x4, 18x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 7488, 7488]][Tile0, 4:[18x4, 2:18x4, 18x1], 1]
		Tile0: [0, 2304, 72], Tile1: [72, 2304, 72], Tile2; [144, 2304, 72]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 512 [D1, [3 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 128, 128]]
		Tile0: [0, 512, 512], Tile1: [0, 512, 512], Tile2; [0, 512, 512]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [3 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 32, 32]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 128 [D1, [3 x 32, 32]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 32, 32]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Filter, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 256 logical tiles, 256 physical tiles
			Total Size: 73728 [D1, [3 x 18432, 18432]][D0, [15 x 1152, 1152]]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 18432, 18432]][D0, [15 x 1152, 1152]]
		Tile0: [0, 1152, 36], Tile1: [1152, 1152, 36], Tile2; [2304, 1152, 36]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 64 logical tiles, 64 physical tiles
			Total Size: 72384 [D0, [15 x 4524, 4524]][Tile0, 4:[39x10, 2:39x10, 39x4], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[39x10, 2:39x10, 39x4], 1][D0, [15 x 4524, 4524]]
		Tile0: [0, 1560, 390], Tile1: [4524, 1560, 390], Tile2; [9048, 1560, 390]
	Ker Arg: ConvOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 16 logical tiles, 1 physical tiles
			Total Size: 479232 [D1, [3 x 119808, 119808]][Tile0, 4:[36x8, 2:36x8, 36x2], 4]
		KerArgItSpace (User Kernel Iter Order):
			[D1, [3 x 119808, 119808]][Tile0, 4:[36x8, 2:36x8, 36x2], 4]
		Tile0: [0, 36864, 1152], Tile1: [0, 36864, 1152], Tile2; [0, 36864, 1152]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 4 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 4:[9x1, 2:9x1, 9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 4:[9x1, 2:9x1, 9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (model_L1_Memory+10800);
	KerArg0->W = (unsigned short int) (36);
	KerArg0->Feat = (unsigned short int) (32);
	KerArg1->W = (unsigned short int) (39);
	KerArg1->UsedW = (unsigned short int) (38);
	KerArg1->InFeatures = (unsigned short int) (4);
	KerArg1->OutFeatures = (unsigned short int) (32);
	KerArg1->TotalInFeatures = (unsigned short int) (4);
	KerArg1->Out = (int * __restrict__) (model_L1_Memory+10800);
	KerArg1->Pad = (v4s) 0;
	KerArg2->In = (int *__restrict__) (model_L1_Memory+10800);
	KerArg2->Out = (void *__restrict__) (model_L1_Memory+10800);
	KerArg2->Feat = (unsigned short int) (32);
	KerArg2->W = (unsigned short int) (36);
	KerArg2->Infos = (signed char *__restrict__) (model_L1_Memory+47664);
	KerArg3->In = (signed char * __restrict__) (model_L1_Memory+10800);
	KerArg3->W = (unsigned short int) (36);
	KerArg3->UsedW = (unsigned short int) (36);
	KerArg3->Feat = (unsigned short int) (32);
	KerArg3->Pad = (v4s) 0;
	KerArg3->PoolMax = (unsigned char) (1);
	KerArg3->DoScale = (unsigned char) (0);
	KerArg3->Infos = (signed char * __restrict__) (model_L1_Memory+47664);
	/*================================= Read Tiles Prolog ===============================*/
	_C_Out=0; _SC_Out=2304; _LC_Out=72;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3120), 512, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3632), 128, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3760), 128, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3888+0), 1152, 0, &DmaR_Evt4);
	_N_Filter=0;
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+0), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+50616+0), 1560, 1131, 390, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
	AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+4524), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+50616+1560), 1560, 1131, 390, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+50616+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+0), 1560, 0, &DmaR_Evt5);
	_NN_In=4524; _SN_In=1560;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+47664), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	for (D1Ind=0; D1Ind<4; D1Ind++) { /* Iteration on D1 */
		int D1Ind_Last = (D1Ind==3), D1Ind_NextLast = ((D1Ind+1)==3);
		for (T0Ind=0; T0Ind<4; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==3), T0Ind_NextLast = ((T0Ind+1)==3), T0Ind_NextNextLast = ((T0Ind+2)==3);
			/*====================== Call Kernel LOC_D0_PROLOG =========================*/
			KerArg0->H = (unsigned short int) (T0Ind_Last?2:8);
			KerArg0->Bias = (void * __restrict__) (model_L1_Memory+3120+((D1Ind)*128));
			KerArg0->NormBias = (unsigned char) (((char *)(model_L1_Memory+47664))[5]);
			AT_FORK(gap_ncore(), (void *) KerParSetBiasB32_SQ8, (void *) KerArg0);
			__CALL(KerParSetBiasB32_SQ8, KerArg0);
			for (D0Ind=0; D0Ind<16; D0Ind++, D0Ind_Total++) { /* Iteration on D0 */
				int D0Ind_Last = (D0Ind==15), D0Ind_NextLast = ((D0Ind+1)==15), D0Ind_NextNextLast = ((D0Ind+2)==15);
				/*================================= Prepare Tiles ===================================*/
				_SN_Filter = 0;
				if (!(D0Ind_Last)) {
					_N_Filter = _N_Filter + (1152); _LN_Filter = (36); _SN_Filter = (32*_LN_Filter); 
				} else if (!((T0Ind_Last))) {
					_N_Filter = _N_Filter + (-17280); _LN_Filter = (36); _SN_Filter = (32*_LN_Filter); 
				} else if (!(D1Ind_Last)) {
					_N_Filter = _N_Filter + (18432)+(-17280); _LN_Filter = (36); _SN_Filter = (32*_LN_Filter); 
				}
				_SNN_In = 0;
				if (!(D0Ind_Last)) {
					if (!(D0Ind_NextLast)) {
						_NN_In = _NN_In + (4524); _LNN_In = ((T0Ind_Last)?156:390); _SNN_In = (4*_LNN_In); 
					} else if (!(T0Ind_Last)) {
						_NN_In = _NN_In + (312)+(-67860); _LNN_In = ((T0Ind_NextLast)?156:390); _SNN_In = (4*_LNN_In); 
					} else if (!(D1Ind_Last)) {
						_NN_In = _NN_In + (-936)+(-67860); _LNN_In = (390); _SNN_In = (4*_LNN_In); 
					}
				} else if (!(T0Ind_Last)) {
					_NN_In = _NN_In + (4524); _LNN_In = ((T0Ind_NextLast)?156:390); _SNN_In = (4*_LNN_In); 
				} else if (!((D1Ind_Last))) {
					_NN_In = _NN_In + (4524); _LNN_In = (390); _SNN_In = (4*_LNN_In); 
				}
				/*============================= End Prepare Tiles ===================================*/
				/*================================= Read Tiles ======================================*/
				AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Filter */
				if (_SN_Filter) {
					AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+_N_Filter), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+3888+1152*((D0Ind_Total+1)%2)),
							_SN_Filter, 0, &DmaR_Evt4);
				}
				AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read In */
				if (_SNN_In) {
					AT_HYPERRAM_CL_COPY2D(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) In+_NN_In), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+50616+1560*((D0Ind_Total)%2)),
							_SNN_In, 1131, _LNN_In, 0, &UchanHR1);
				}
				AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read In */
				if (_SN_In) {
					AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+50616+1560*((D0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+1560*((D0Ind_Total+1)%2)),
							_SN_In, 0, &DmaR_Evt5);
				}
				/*============================= End Read Tiles ======================================*/
				/*====================== Call Kernel LOC_D0 =========================*/
				KerArg1->In = (signed char * __restrict__) (model_L1_Memory+0+1560*((D0Ind_Total)%2));
				KerArg1->H = (unsigned short int) (T0Ind_Last?4:10);
				KerArg1->UsedH = (unsigned short int) (T0Ind_Last?4:10);
				KerArg1->Filter = (signed char * __restrict__) (model_L1_Memory+3888+1152*((D0Ind_Total)%2));
				AT_FORK(gap_ncore(), (void *) KerParConv3x3Stride1_SQ8, (void *) KerArg1);
				__CALL(KerParConv3x3Stride1_SQ8, KerArg1);
				/*================================= Update Arg Pipeline =============================*/
				_SN_In = _SNN_In;_LN_In = _LNN_In;
				/*============================= End Update Arg Pipeline =============================*/
			} /* End iteration on D0 */
			/*====================== Call Kernel LOC_D0_EPILOG =========================*/
			KerArg2->H = (unsigned short int) (T0Ind_Last?2:8);
			KerArg2->Scale = (unsigned char *__restrict__) (model_L1_Memory+3632+((D1Ind)*32));
			KerArg2->ScaleN = (unsigned char *__restrict__) (model_L1_Memory+3760+((D1Ind)*32));
			AT_FORK(gap_ncore(), (void *) KerParReductIO_CC_SQ8, (void *) KerArg2);
			__CALL(KerParReductIO_CC_SQ8, KerArg2);
			KerArg3->H = (unsigned short int) (T0Ind_Last?2:8);
			KerArg3->UsedH = (unsigned short int) (T0Ind_Last?2:8);
			KerArg3->Out = (signed char * __restrict__) (model_L1_Memory+6192+2304*((T0Ind_Total)%2));
			AT_FORK(gap_ncore(), (void *) KerParPool2x2Stride2_ReLU_SQ8, (void *) KerArg3);
			__CALL(KerParPool2x2Stride2_ReLU_SQ8, KerArg3);
			/*================================= Write Tiles =====================================*/
			if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
			AT_L2_COPY2D(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+6192+2304*((T0Ind_Total)%2)),
					_SC_Out, 234, _LC_Out, 1, &DmaW_Evt1);
			/*============================= End Write Tiles =====================================*/
			/*================================= Update Arg Pipeline =============================*/
			_SP_Out = _SC_Out;_LP_Out = _LC_Out;
			/*============================= End Update Arg Pipeline =============================*/
			/*================================= Prepare Tiles ===================================*/
			_SC_Out = 0;
			if (!(T0Ind_Last)) {
				_C_Out = _C_Out + (72); _LC_Out = ((T0Ind_NextLast)?18:72); _SC_Out = (32*_LC_Out); 
			} else if (!(D1Ind_Last)) {
				_C_Out = _C_Out + (7488)+(-216); _LC_Out = (72); _SC_Out = (32*_LC_Out); 
			}
			/*============================= End Prepare Tiles ===================================*/
		} /* End iteration on Tile0 */
	} /* End iteration on D1 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S5_Linear_64x13x18x128(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 48748 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	AT_HYPERRAM_CL_EVENT UchanHR1;
	KerSetBias_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;
	KerLinear_SQ8_T S_KerArg1, *KerArg1 = &S_KerArg1;
	KerConvLinReduct_SQ8_T S_KerArg2, *KerArg2 = &S_KerArg2;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Total=0, D0Ind_Last, D0Ind_NextLast, D0Ind_NextNextLast;
	int T0Ind, T0Ind_Total=0, T0Ind_Last, T0Ind_NextLast, T0Ind_NextNextLast;
	/* User kernel arguments related variables */
	unsigned int _N_In;
	unsigned int _SN_In;
	unsigned int _NN_Filter;
	unsigned int _SN_Filter, _SNN_Filter;
	unsigned int _LN_Filter, _LNN_Filter;
	unsigned int _N_Bias;
	unsigned int _SN_Bias;
	unsigned int _C_Out;
	unsigned int _SP_Out, _SC_Out;
	unsigned int _N_Scale;
	unsigned int _SN_Scale;
	unsigned int _N_ScaleN;
	unsigned int _SN_ScaleN;
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 64, Tiled: 1][Tile0 Dim: 82]
	Ker Arg: In, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 82 logical tiles, 82 physical tiles
			Total Size: 29952 [Tile0, 82:[1x366, 80:1x366, 1x306], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 82:[1x366, 80:1x366, 1x306], 1]
		Tile0: [0, 366, 366], Tile1: [366, 366, 366], Tile2; [732, 366, 366]
	Ker Arg: Filter, Tiled Space: Tile0
		Min Pipe Depth: 0, Max Pipe Depth: 2
		KerArgItSpace: 82 logical tiles, 82 physical tiles
			Total Size: 1916928 [D0, [0 x 1916928, 1916928]][Tile0, 82:[1x366, 80:1x366, 1x306], 1]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 1916928, 1916928]][Tile0, 82:[1x366, 80:1x366, 1x306], 1]
		Tile0: [0, 23424, 366], Tile1: [23424, 23424, 366], Tile2; [46848, 23424, 366]
	Ker Arg: Bias, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 256 [D0, [0 x 256, 256]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 256, 256]]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: LinOut, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 256 [D0, [0 x 256, 256]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 256, 256]]
		Tile0: [0, 256, 256], Tile1: [0, 256, 256], Tile2; [0, 256, 256]
	Ker Arg: Out, Tiled Space: D0
		Min Pipe Depth: -1, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [D0, [0 x 64, 64]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 64, 64]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Scale, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [D0, [0 x 64, 64]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 64, 64]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: ScaleN, Tiled Space: D0
		Min Pipe Depth: 0, Max Pipe Depth: 1
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [D0, [0 x 64, 64]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 64, 64]]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 82 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 82:[1x1, 80:1x1, 1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 82:[1x1, 80:1x1, 1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->Out = (int * __restrict__) (model_L1_Memory+48096);
	KerArg0->W = (unsigned short int) (1);
	KerArg0->H = (unsigned short int) (1);
	KerArg0->Feat = (unsigned short int) (64);
	KerArg1->Out = (void * __restrict__) (model_L1_Memory+48096);
	KerArg1->OutDim = (unsigned short int) (64);
	KerArg1->Infos = (signed char *__restrict__) (model_L1_Memory+48736);
	KerArg2->In = (int *__restrict__) (model_L1_Memory+48096);
	KerArg2->Feat = (unsigned short int) (64);
	KerArg2->W = (unsigned short int) (1);
	KerArg2->H = (unsigned short int) (1);
	KerArg2->Infos = (signed char *__restrict__) (model_L1_Memory+48736);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+0), 366, 0, &DmaR_Evt1);
	_N_In=0;
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+0), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+50680+0), 23424, 0, &UchanHR1);
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+23424), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+50680+23424), 23424, 0, &UchanHR1);
	AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+50680+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+736+0), 23424, 0, &DmaR_Evt2);
	_NN_Filter=23424; _SN_Filter=23424;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+47584+0), 256, 0, &DmaR_Evt3);
	_N_Bias=0;
	_C_Out=0; _SC_Out=64;
	_SP_Out=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+48480+0), 64, 0, &DmaR_Evt4);
	_N_Scale=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+48608+0), 64, 0, &DmaR_Evt5);
	_N_ScaleN=0;
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+48736), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1, D0Ind_NextLast = 1, D0Ind_NextNextLast = 1;
		/*================================= Prepare Tiles ===================================*/
		_SN_Bias = 0;
		
		_SN_Scale = 0;
		
		_SN_ScaleN = 0;
		
		/*============================= End Prepare Tiles ===================================*/
		/*================================= Read Tiles ======================================*/
		AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
		if (_SN_Bias) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+_N_Bias), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+47584+256*((D0Ind_Total+1)%2)),
					_SN_Bias, 0, &DmaR_Evt3);
		}
		AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
		if (_SN_Scale) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+_N_Scale), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+48480+64*((D0Ind_Total+1)%2)),
					_SN_Scale, 0, &DmaR_Evt4);
		}
		AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
		if (_SN_ScaleN) {
			AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+_N_ScaleN), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+48608+64*((D0Ind_Total+1)%2)),
					_SN_ScaleN, 0, &DmaR_Evt5);
		}
		/*============================= End Read Tiles ======================================*/
		/*====================== Call Kernel LOC_LOOP_PROLOG =========================*/
		KerArg0->Bias = (void * __restrict__) (model_L1_Memory+47584+256*((D0Ind_Total)%2));
		KerArg0->NormBias = (unsigned char) (((char *)(model_L1_Memory+48736))[5]);
		AT_FORK(gap_ncore(), (void *) KerParSetBiasB32_SQ8, (void *) KerArg0);
		__CALL(KerParSetBiasB32_SQ8, KerArg0);
		for (T0Ind=0; T0Ind<82; T0Ind++, T0Ind_Total++) { /* Iteration on Tile0 */
			int T0Ind_Last = (T0Ind==81), T0Ind_NextLast = ((T0Ind+1)==81), T0Ind_NextNextLast = ((T0Ind+2)==81);
			/*================================= Prepare Tiles ===================================*/
			_SN_In = 0;
			if (!(T0Ind_Last)) {
				_N_In = _N_In + (366); _SN_In = ((T0Ind_NextLast)?306:366); 
			} else if (!(1)) {
				_N_In = _N_In + (-29646); _SN_In = (366); 
			}
			_SNN_Filter = 0;
			if (!(T0Ind_Last)) {
				if (!(T0Ind_NextLast)) {
					_NN_Filter = _NN_Filter + (23424); _LNN_Filter = ((T0Ind_NextNextLast)?306:366); _SNN_Filter = (64*_LNN_Filter); 
				}
			}
			/*============================= End Prepare Tiles ===================================*/
			/*================================= Read Tiles ======================================*/
			AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
			if (_SN_In) {
				AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+_N_In), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0+368*((T0Ind_Total+1)%2)),
						_SN_In, 0, &DmaR_Evt1);
			}
			AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR1); /* Wait previous uDMA read Filter */
			if (_SNN_Filter) {
				AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) Filter+_NN_Filter), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory+50680+23424*((T0Ind_Total)%2)),
						_SNN_Filter, 0, &UchanHR1);
			}
			AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
			if (_SN_Filter) {
				AT_L2_COPY(0, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L2_Memory+50680+23424*((T0Ind_Total+1)%2)), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+736+23424*((T0Ind_Total+1)%2)),
						_SN_Filter, 0, &DmaR_Evt2);
			}
			/*============================= End Read Tiles ======================================*/
			/*====================== Call Kernel LOC_LOOP =========================*/
			KerArg1->In = (signed char * __restrict__) (model_L1_Memory+0+368*((T0Ind_Total)%2));
			KerArg1->Weights = (signed char * __restrict__) (model_L1_Memory+736+23424*((T0Ind_Total)%2));
			KerArg1->InDim = (unsigned short int) (T0Ind_Last?306:366);
			KerArg1->TotalInDim = (unsigned short int) (T0Ind_Last?306:366);
			AT_FORK(gap_ncore(), (void *) KerParLinearLayer_SQ8, (void *) KerArg1);
			__CALL(KerParLinearLayer_SQ8, KerArg1);
			/*================================= Update Arg Pipeline =============================*/
			_SN_Filter = _SNN_Filter;_LN_Filter = _LNN_Filter;
			/*============================= End Update Arg Pipeline =============================*/
		} /* End iteration on Tile0 */
		/*====================== Call Kernel LOC_LOOP_EPILOG =========================*/
		KerArg2->Out = (void *__restrict__) (model_L1_Memory+48352+64*((D0Ind_Total)%2));
		KerArg2->Scale = (unsigned char *__restrict__) (model_L1_Memory+48480+64*((D0Ind_Total)%2));
		KerArg2->ScaleN = (unsigned char *__restrict__) (model_L1_Memory+48608+64*((D0Ind_Total)%2));
		AT_FORK(gap_ncore(), (void *) KerParReduct_CC_SQ8, (void *) KerArg2);
		__CALL(KerParReduct_CC_SQ8, KerArg2);
		/*================================= Write Tiles =====================================*/
		if (_SP_Out) AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
		AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+_C_Out), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+48352+64*((D0Ind_Total)%2)),
				_SC_Out, 1, &DmaW_Evt1);
		/*============================= End Write Tiles =====================================*/
		/*================================= Update Arg Pipeline =============================*/
		_SP_Out = _SC_Out;
		/*============================= End Update Arg Pipeline =============================*/
		/*================================= Prepare Tiles ===================================*/
		_SC_Out = 0;
		
		/*============================= End Prepare Tiles ===================================*/
		D0Ind_Total++;
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait previous DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S6_Linear_2x64(
		signed char * __restrict__ In,
		signed char * __restrict__ Filter,
		int * __restrict__ Bias,
		signed char * __restrict__ Out,
		unsigned char * __restrict__ Scale,
		unsigned char * __restrict__ ScaleN,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 224 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaR_Evt3;
	AT_L2_EVENT DmaR_Evt4;
	AT_L2_EVENT DmaR_Evt5;
	AT_L2_EVENT DmaR_Evt6;
	AT_L2_EVENT DmaW_Evt1;
	KerLinear_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int D0Ind, D0Ind_Last;
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[D0 Dim: Init: 2, Tiled: 1][Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 64 [Tile0, 1:[1x1], 64]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x1], 64]
		Tile0: [0, 64, 64], Tile1: [0, 64, 64], Tile2; [0, 64, 64]
	Ker Arg: Filter, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 128 [D0, [0 x 128, 128]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 128, 128]]
		Tile0: [0, 128, 128], Tile1: [0, 128, 128], Tile2; [0, 128, 128]
	Ker Arg: Bias, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 8 [D0, [0 x 8, 8]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 8, 8]]
		Tile0: [0, 8, 8], Tile1: [0, 8, 8], Tile2; [0, 8, 8]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2 [D0, [0 x 2, 2]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2, 2]]
		Tile0: [0, 2, 2], Tile1: [0, 2, 2], Tile2; [0, 2, 2]
	Ker Arg: Scale, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2 [D0, [0 x 2, 2]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2, 2]]
		Tile0: [0, 2, 2], Tile1: [0, 2, 2], Tile2; [0, 2, 2]
	Ker Arg: ScaleN, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2 [D0, [0 x 2, 2]]
		KerArgItSpace (User Kernel Iter Order):
			[D0, [0 x 2, 2]]
		Tile0: [0, 2, 2], Tile1: [0, 2, 2], Tile2; [0, 2, 2]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 1:[1x1], 9]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x1], 9]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (signed char * __restrict__) (model_L1_Memory+0);
	KerArg0->Weights = (signed char * __restrict__) (model_L1_Memory+64);
	KerArg0->Bias = (void * __restrict__) (model_L1_Memory+192);
	KerArg0->Out = (void * __restrict__) (model_L1_Memory+200);
	KerArg0->InDim = (unsigned short int) (64);
	KerArg0->TotalInDim = (unsigned short int) (64);
	KerArg0->OutDim = (unsigned short int) (2);
	KerArg0->Scale = (unsigned char *__restrict__) (model_L1_Memory+204);
	KerArg0->ScaleN = (unsigned char *__restrict__) (model_L1_Memory+208);
	KerArg0->Infos = (signed char *__restrict__) (model_L1_Memory+212);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0), 64, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Filter+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+64), 128, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Filter */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Bias+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+192), 8, 0, &DmaR_Evt3);
	AT_L2_WAIT(0, &DmaR_Evt3); /* Wait previous DMA read Bias */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Scale+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+204), 2, 0, &DmaR_Evt4);
	AT_L2_WAIT(0, &DmaR_Evt4); /* Wait previous DMA read Scale */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) ScaleN+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+208), 2, 0, &DmaR_Evt5);
	AT_L2_WAIT(0, &DmaR_Evt5); /* Wait previous DMA read ScaleN */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+212), 9, 0, &DmaR_Evt6);
	AT_L2_WAIT(0, &DmaR_Evt6); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on D0 */
		int D0Ind_Last = 1;
		{ /* Single iteration on Tile0 */
			int T0Ind_Last = 1;
			/*====================== Call Kernel LOC_LOOP =========================*/
			AT_FORK(gap_ncore(), (void *) KerParLinearLayerFullFeatB32_SQ8, (void *) KerArg0);
			__CALL(KerParLinearLayerFullFeatB32_SQ8, KerArg0);
		} /* End iteration on Tile0 */
	} /* End iteration on D0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+200), 2, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
void S7_SoftMax(
		signed char * __restrict__ In,
		short int * __restrict__ Out,
		signed char * __restrict__ Infos)

{
	/* Shared L1: 20 bytes, L2 buffer: 0 bytes */
	/* Local variables used by this kernel */
	AT_L2_EVENT DmaR_Evt1;
	AT_L2_EVENT DmaR_Evt2;
	AT_L2_EVENT DmaW_Evt1;
	KerSoftMax_SQ8_T S_KerArg0, *KerArg0 = &S_KerArg0;

	/* Iteration space related variables */
	int T0Ind, T0Ind_Last;
	/* User kernel arguments related variables */
	/*============================= Ker Arg Iter Spaces =========================================
	User Kernel Iteration Space:
		[Tile0 Dim: 1]
	Ker Arg: In, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 2 [Tile0, 1:[1x2], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x2], 1]
		Tile0: [0, 2, 2], Tile1: [0, 2, 2], Tile2; [0, 2, 2]
	Ker Arg: Out, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 4 [Tile0, 1:[1x2], 2]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[1x2], 2]
		Tile0: [0, 4, 4], Tile1: [0, 4, 4], Tile2; [0, 4, 4]
	Ker Arg: Infos, Tiled Space: Buffer
		Min Pipe Depth: 0, Max Pipe Depth: 0
		KerArgItSpace: 1 logical tiles, 1 physical tiles
			Total Size: 9 [Tile0, 1:[9x1], 1]
		KerArgItSpace (User Kernel Iter Order):
			[Tile0, 1:[9x1], 1]
		Tile0: [0, 9, 9], Tile1: [0, 9, 9], Tile2; [0, 9, 9]
	======================== End Ker Arg Iter Spaces =========================================*/
	/*=========================== Call Kernel, Invariant assignment =====================*/
	KerArg0->In = (signed char *__restrict__) (model_L1_Memory+0);
	KerArg0->N = (unsigned short int) (2);
	KerArg0->Out = (short int *__restrict__) (model_L1_Memory+4);
	KerArg0->Infos = (signed char *__restrict__) (model_L1_Memory+8);
	/*================================= Read Tiles Prolog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) In+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+0), 2, 0, &DmaR_Evt1);
	AT_L2_WAIT(0, &DmaR_Evt1); /* Wait previous DMA read In */
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Infos+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+8), 9, 0, &DmaR_Evt2);
	AT_L2_WAIT(0, &DmaR_Evt2); /* Wait previous DMA read Infos */
	/*============================= End Read Tiles Prolog ===============================*/
	{ /* Single iteration on Tile0 */
		int T0Ind_Last = 1;
		/*====================== Call Kernel LOC_LOOP =========================*/
		KerArg0->Norm = (unsigned short int) (((char *)(model_L1_Memory+8))[0]);
		AT_FORK(gap_ncore(), (void *) KerParSoftMax_SQ8, (void *) KerArg0);
		__CALL(KerParSoftMax_SQ8, KerArg0);
	} /* End iteration on Tile0 */
	/*================================ Write Tiles Epilog ===============================*/
	AT_L2_COPY(0, ((AT_L2_EXT_ADDR_TYPE) Out+0), ((AT_L2_INT_ADDR_TYPE) model_L1_Memory+4), 4, 1, &DmaW_Evt1);
	AT_L2_WAIT(0, &DmaW_Evt1); /* Wait DMA write Out */
	/*============================ End Write Tiles Epilog ===============================*/
}
int modelCNN_Construct()

{
	AT_HYPERFLASH_FS_FC_EVENT UchanHF1;
	AT_HYPERRAM_FC_EVENT UchanHR2;
	AT_HYPERRAM_CONF_T HyperRamConf;
	AT_HYPERFLASH_FS_CONF_T HyperFlashConf;
	int Error;
	AT_HYPERRAM_CONF_INIT(&HyperRamConf, AT_MEM_L3_HRAM, 0);
	AT_HYPERFLASH_FS_CONF_INIT(&HyperFlashConf, AT_MEM_L3_HFLASH, 0);
	AT_HYPERRAM_OPEN(&HyperRam, &HyperRamConf, &Error);
	if (Error) return 1;
	AT_HYPERFLASH_FS_OPEN(&HyperFlash, &HyperFlashConf, "model_L3_Flash_Const.dat", &Error);
	if (Error) return 1;
	model_L3_Memory = (AT_HYPERRAM_POINTER) AT_HYPERRAM_ALLOC(&HyperRam, 2069712);
	if (model_L3_Memory == 0) return 2;
	model_L2_Memory = (AT_L2_POINTER) AT_L2_ALLOC(0, 177502);
	if (model_L2_Memory == 0) return 3;
	model_L1_Memory = (AT_L1_POINTER) AT_L1_ALLOC(0, 48748);
	if (model_L1_Memory == 0) return 4;
	/* Moving S4_Weights, size 73728 from HyperFlash at 1916928 to (size 73728) HyperRam at 1916928..1990655 */
	{
		int Size = 73728, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 1916928+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L3_Memory + 1916928+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving S5_Weights, size 1916928 from HyperFlash at 0 to (size 1916928) HyperRam at 0..1916927 */
	{
		int Size = 1916928, Base = 0;
		while (Size) {
			int Chunk = Min(Size, 1024);
			AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 0+Base), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 0), Chunk, 0, &UchanHF1);
			AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
			AT_HYPERRAM_FC_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L3_Memory + 0+Base), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory + 0), Chunk, 1, &UchanHR2);
			AT_HYPERRAM_FC_WAIT(&HyperRam, &UchanHR2);
			Base += Chunk;
			Size -= Chunk;
		}
	}
	/* Moving S2_Infos, size 9 from HyperFlash at 2011232 to (size 9) L2 at 20576..20584 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2011232), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20576), 9, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S2_Weights, size 288 from HyperFlash at 2009600 to (size 288) L2 at 18944..19231 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2009600), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 18944), 288, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S2_Biases, size 128 from HyperFlash at 2010400 to (size 128) L2 at 19744..19871 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2010400), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 19744), 128, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S2_Mul_scale, size 32 from HyperFlash at 2011168 to (size 32) L2 at 20512..20543 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2011168), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20512), 32, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S2_Mul_shift, size 32 from HyperFlash at 2011200 to (size 32) L2 at 20544..20575 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2011200), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20544), 32, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S3_Infos, size 9 from HyperFlash at 2011244 to (size 9) L2 at 20588..20596 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2011244), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20588), 9, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S3_Weights, size 18432 from HyperFlash at 1990656 to (size 18432) L2 at 0..18431 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 1990656), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 0), 18432, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S3_Biases, size 256 from HyperFlash at 2009888 to (size 256) L2 at 19232..19487 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2009888), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 19232), 256, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S3_Mul_scale, size 64 from HyperFlash at 2010912 to (size 64) L2 at 20256..20319 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2010912), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20256), 64, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S3_Mul_shift, size 64 from HyperFlash at 2010976 to (size 64) L2 at 20320..20383 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2010976), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20320), 64, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S4_Infos, size 9 from HyperFlash at 2011256 to (size 9) L2 at 20600..20608 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2011256), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20600), 9, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S4_Biases, size 512 from HyperFlash at 2009088 to (size 512) L2 at 18432..18943 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2009088), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 18432), 512, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S4_Mul_scale, size 128 from HyperFlash at 2010528 to (size 128) L2 at 19872..19999 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2010528), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 19872), 128, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S4_Mul_shift, size 128 from HyperFlash at 2010656 to (size 128) L2 at 20000..20127 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2010656), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20000), 128, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S5_Infos, size 9 from HyperFlash at 2011268 to (size 9) L2 at 20612..20620 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2011268), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20612), 9, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S5_Biases, size 256 from HyperFlash at 2010144 to (size 256) L2 at 19488..19743 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2010144), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 19488), 256, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S5_Mul_scale, size 64 from HyperFlash at 2011040 to (size 64) L2 at 20384..20447 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2011040), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20384), 64, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S5_Mul_shift, size 64 from HyperFlash at 2011104 to (size 64) L2 at 20448..20511 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2011104), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20448), 64, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S6_Infos, size 9 from HyperFlash at 2011280 to (size 9) L2 at 20624..20632 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2011280), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20624), 9, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S6_Weights, size 128 from HyperFlash at 2010784 to (size 128) L2 at 20128..20255 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2010784), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20128), 128, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S6_Biases, size 8 from HyperFlash at 2011304 to (size 8) L2 at 20648..20655 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2011304), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20648), 8, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S6_Mul_scale, size 2 from HyperFlash at 2011312 to (size 2) L2 at 20656..20657 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2011312), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20656), 2, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S6_Mul_shift, size 2 from HyperFlash at 2011316 to (size 2) L2 at 20660..20661 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2011316), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20660), 2, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	/* Moving S7_Infos, size 9 from HyperFlash at 2011292 to (size 9) L2 at 20636..20644 */
	AT_HYPERFLASH_FS_FC_COPY(&HyperFlash, ((AT_HYPERFLASH_FS_EXT_ADDR_TYPE) model_L3_Flash + 2011292), ((AT_HYPERFLASH_FS_INT_ADDR_TYPE) model_L2_Memory + 20636), 9, 0, &UchanHF1);
	AT_HYPERFLASH_FS_FC_WAIT(&HyperFlash, &UchanHF1);
	return 0;
}
int modelCNN_Destruct()

{
	AT_HYPERRAM_FREE(&HyperRam, model_L3_Memory, 2069712);
	AT_L2_FREE(0, model_L2_Memory, 177502);
	AT_L1_FREE(0, model_L1_Memory, 48748);
	AT_HYPERRAM_CLOSE(&HyperRam);
	AT_HYPERFLASH_FS_CLOSE(&HyperFlash);
	return 0;
}
unsigned int AT_GraphPerf[7];
unsigned int AT_GraphOperInfosNames[7] = {
	79056,
	6297600,
	83748288,
	69159168,
	1916928,
	128,
	2,
};
char *AT_GraphNodeNames[7] = {
	"S1_Op_input_1_formatter",
	"S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu",
	"S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu",
	"S4_Conv2d_128x64x3x3_MaxPool_2x2_Relu",
	"S5_Linear_64x13x18x128",
	"S6_Linear_2x64",
	"S7_SoftMax",
};
int modelCNN(
		unsigned char * __restrict__ Input_1,
		signed short * __restrict__ Output_1)

{
	AT_HYPERRAM_CL_EVENT UchanHR0;
	AT_GraphPerf[0] = gap_cl_readhwtimer();
	S1_Op_input_1_formatter(
		((unsigned char * __restrict__) Input_1), /* In */
		((signed char * __restrict__) (model_L3_Memory+1990656)) /* Out */
	);
	AT_GraphPerf[0] = gap_cl_readhwtimer() - AT_GraphPerf[0];
	AT_GraphPerf[1] = gap_cl_readhwtimer();
	S2_Conv2d_32x1x3x3_MaxPool_2x2_Relu(
		((signed char * __restrict__) (model_L3_Memory+1990656)), /* In */
		((signed char * __restrict__) (model_L2_Memory+18944)), /* Filter */
		((signed int * __restrict__) (model_L2_Memory+19744)), /* Bias */
		((signed char * __restrict__) (model_L2_Memory+20664)), /* Out */
		((unsigned char * __restrict__) (model_L2_Memory+20512)), /* Scale */
		((signed char * __restrict__) (model_L2_Memory+20544)), /* ScaleN */
		((signed char * __restrict__) (model_L2_Memory+20576)) /* Infos */
	);
	AT_GraphPerf[1] = gap_cl_readhwtimer() - AT_GraphPerf[1];
	AT_GraphPerf[2] = gap_cl_readhwtimer();
	S3_Conv2d_64x32x3x3_MaxPool_2x2_Relu(
		((signed char * __restrict__) (model_L2_Memory+20664)), /* In */
		((signed char * __restrict__) (model_L2_Memory+0)), /* Filter */
		((signed int * __restrict__) (model_L2_Memory+19232)), /* Bias */
		((signed char * __restrict__) (model_L3_Memory+1990656)), /* Out */
		((unsigned char * __restrict__) (model_L2_Memory+20256)), /* Scale */
		((signed char * __restrict__) (model_L2_Memory+20320)), /* ScaleN */
		((signed char * __restrict__) (model_L2_Memory+20588)) /* Infos */
	);
	AT_GraphPerf[2] = gap_cl_readhwtimer() - AT_GraphPerf[2];
	/* Moving S4_Weights, size 73728 from HyperRam at 1916928 to (size 73728) L2 at 53736 using event 0 */
	AT_HYPERRAM_CL_COPY(&HyperRam, ((AT_HYPERRAM_EXT_ADDR_TYPE) model_L3_Memory + 1916928), ((AT_HYPERRAM_INT_ADDR_TYPE) model_L2_Memory + 53736), 73728, 0, &UchanHR0);
	/* Waiting completion of transfer of S4_Weights using event 0 */
	AT_HYPERRAM_CL_WAIT(&HyperRam, &UchanHR0);
	AT_GraphPerf[3] = gap_cl_readhwtimer();
	S4_Conv2d_128x64x3x3_MaxPool_2x2_Relu(
		((signed char * __restrict__) (model_L3_Memory+1990656)), /* In */
		((signed char * __restrict__) (model_L2_Memory+53736)), /* Filter */
		((signed int * __restrict__) (model_L2_Memory+18432)), /* Bias */
		((signed char * __restrict__) (model_L2_Memory+20664)), /* Out */
		((unsigned char * __restrict__) (model_L2_Memory+19872)), /* Scale */
		((signed char * __restrict__) (model_L2_Memory+20000)), /* ScaleN */
		((signed char * __restrict__) (model_L2_Memory+20600)) /* Infos */
	);
	AT_GraphPerf[3] = gap_cl_readhwtimer() - AT_GraphPerf[3];
	AT_GraphPerf[4] = gap_cl_readhwtimer();
	S5_Linear_64x13x18x128(
		((signed char * __restrict__) (model_L2_Memory+20664)), /* In */
		((signed char * __restrict__) (model_L3_Memory+0)), /* Filter */
		((signed int * __restrict__) (model_L2_Memory+19488)), /* Bias */
		((signed char * __restrict__) (model_L2_Memory+50616)), /* Out */
		((unsigned char * __restrict__) (model_L2_Memory+20384)), /* Scale */
		((signed char * __restrict__) (model_L2_Memory+20448)), /* ScaleN */
		((signed char * __restrict__) (model_L2_Memory+20612)) /* Infos */
	);
	AT_GraphPerf[4] = gap_cl_readhwtimer() - AT_GraphPerf[4];
	AT_GraphPerf[5] = gap_cl_readhwtimer();
	S6_Linear_2x64(
		((signed char * __restrict__) (model_L2_Memory+50616)), /* In */
		((signed char * __restrict__) (model_L2_Memory+20128)), /* Filter */
		((signed int * __restrict__) (model_L2_Memory+20648)), /* Bias */
		((signed char * __restrict__) (model_L2_Memory+20664)), /* Out */
		((unsigned char * __restrict__) (model_L2_Memory+20656)), /* Scale */
		((signed char * __restrict__) (model_L2_Memory+20660)), /* ScaleN */
		((signed char * __restrict__) (model_L2_Memory+20624)) /* Infos */
	);
	AT_GraphPerf[5] = gap_cl_readhwtimer() - AT_GraphPerf[5];
	AT_GraphPerf[6] = gap_cl_readhwtimer();
	S7_SoftMax(
		((signed char * __restrict__) (model_L2_Memory+20664)), /* In */
		((signed short * __restrict__) Output_1), /* Out */
		((signed char * __restrict__) (model_L2_Memory+20636)) /* Infos */
	);
	AT_GraphPerf[6] = gap_cl_readhwtimer() - AT_GraphPerf[6];
	return 0;
}
