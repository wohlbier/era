/*
 * Copyright (c) 2003, 2007-14 Matteo Frigo
 * Copyright (c) 2003, 2007-14 Massachusetts Institute of Technology
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

/* This file was automatically generated --- DO NOT EDIT */
/* Generated on Thu May 24 08:07:58 EDT 2018 */

#include "rdft/codelet-rdft.h"

#if defined(ARCH_PREFERS_FMA) || defined(ISA_EXTENSION_PREFERS_FMA)

/* Generated by: ../../../genfft/gen_hc2cdft.native -fma -compact -variables 4 -pipeline-latency 4 -sign 1 -n 10 -dif -name hc2cbdft_10 -include rdft/scalar/hc2cb.h */

/*
 * This function contains 122 FP additions, 72 FP multiplications,
 * (or, 68 additions, 18 multiplications, 54 fused multiply/add),
 * 91 stack variables, 4 constants, and 40 memory accesses
 */
#include "rdft/scalar/hc2cb.h"

static void hc2cbdft_10(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     DK(KP618033988, +0.618033988749894848204586834365638117720309180);
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     {
	  INT m;
	  for (m = mb, W = W + ((mb - 1) * 18); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 18, MAKE_VOLATILE_STRIDE(40, rs)) {
	       E T3, Tl, Tu, T14, Ti, T13, Ts, Tt, T1p, T23, TZ, T1z, TQ, T1g, TV;
	       E T1l, TT, TU, T1j, T1k, T1c, T1Y, TK, T1u;
	       {
		    E Td, Tp, Tg, Tq, Th, Tr, T6, Tm, T9, Tn, Ta, To, T1, T2;
		    T1 = Rp[0];
		    T2 = Rm[WS(rs, 4)];
		    T3 = T1 + T2;
		    Tl = T1 - T2;
		    {
			 E Tb, Tc, Te, Tf;
			 Tb = Rp[WS(rs, 4)];
			 Tc = Rm[0];
			 Td = Tb + Tc;
			 Tp = Tb - Tc;
			 Te = Rm[WS(rs, 3)];
			 Tf = Rp[WS(rs, 1)];
			 Tg = Te + Tf;
			 Tq = Te - Tf;
		    }
		    Th = Td + Tg;
		    Tr = Tp + Tq;
		    {
			 E T4, T5, T7, T8;
			 T4 = Rp[WS(rs, 2)];
			 T5 = Rm[WS(rs, 2)];
			 T6 = T4 + T5;
			 Tm = T4 - T5;
			 T7 = Rm[WS(rs, 1)];
			 T8 = Rp[WS(rs, 3)];
			 T9 = T7 + T8;
			 Tn = T7 - T8;
		    }
		    Ta = T6 + T9;
		    To = Tm + Tn;
		    Tu = To - Tr;
		    T14 = Ta - Th;
		    Ti = Ta + Th;
		    T13 = FNMS(KP250000000, Ti, T3);
		    Ts = To + Tr;
		    Tt = FNMS(KP250000000, Ts, Tl);
		    {
			 E T1n, T1o, TX, TY;
			 T1n = Td - Tg;
			 T1o = T6 - T9;
			 T1p = FNMS(KP618033988, T1o, T1n);
			 T23 = FMA(KP618033988, T1n, T1o);
			 TX = Tm - Tn;
			 TY = Tp - Tq;
			 TZ = FMA(KP618033988, TY, TX);
			 T1z = FNMS(KP618033988, TX, TY);
		    }
	       }
	       {
		    E TF, T16, TI, T17, TS, T1i, Ty, T19, TB, T1a, TR, T1h, TO, TP;
		    TO = Ip[0];
		    TP = Im[WS(rs, 4)];
		    TQ = TO + TP;
		    T1g = TO - TP;
		    {
			 E TD, TE, TG, TH;
			 TD = Ip[WS(rs, 4)];
			 TE = Im[0];
			 TF = TD + TE;
			 T16 = TD - TE;
			 TG = Im[WS(rs, 3)];
			 TH = Ip[WS(rs, 1)];
			 TI = TG + TH;
			 T17 = TH - TG;
		    }
		    TS = TF - TI;
		    T1i = T16 + T17;
		    {
			 E Tw, Tx, Tz, TA;
			 Tw = Ip[WS(rs, 2)];
			 Tx = Im[WS(rs, 2)];
			 Ty = Tw + Tx;
			 T19 = Tw - Tx;
			 Tz = Im[WS(rs, 1)];
			 TA = Ip[WS(rs, 3)];
			 TB = Tz + TA;
			 T1a = TA - Tz;
		    }
		    TR = Ty - TB;
		    T1h = T19 + T1a;
		    TV = TR - TS;
		    T1l = T1h - T1i;
		    TT = TR + TS;
		    TU = FNMS(KP250000000, TT, TQ);
		    T1j = T1h + T1i;
		    T1k = FNMS(KP250000000, T1j, T1g);
		    {
			 E T18, T1b, TC, TJ;
			 T18 = T16 - T17;
			 T1b = T19 - T1a;
			 T1c = FNMS(KP618033988, T1b, T18);
			 T1Y = FMA(KP618033988, T18, T1b);
			 TC = Ty + TB;
			 TJ = TF + TI;
			 TK = FMA(KP618033988, TJ, TC);
			 T1u = FNMS(KP618033988, TC, TJ);
		    }
	       }
	       {
		    E Tj, T2y, T2a, T1A, T2q, T10, T1Q, T24, T2k, T1q, T1K, T26, T28, T29, T2c;
		    E Tk, TM, TN, T2w, T1M, T1O, T1P, T1S, T1s, T1w, T1x, T1C, T2m, T2o, T2p;
		    E T2s, T12, T1e, T1f, T1E, T1G, T1I, T1J, T1U, T1W, T20, T21, T2e, T2g, T2i;
		    E T2j, T2u, T1y, TW, T22, T2l, T2r;
		    Tj = T3 + Ti;
		    T2y = T1g + T1j;
		    T2a = TQ + TT;
		    T1y = FNMS(KP559016994, TV, TU);
		    T1A = FMA(KP951056516, T1z, T1y);
		    T2q = FNMS(KP951056516, T1z, T1y);
		    TW = FMA(KP559016994, TV, TU);
		    T10 = FMA(KP951056516, TZ, TW);
		    T1Q = FNMS(KP951056516, TZ, TW);
		    T22 = FMA(KP559016994, T1l, T1k);
		    T24 = FNMS(KP951056516, T23, T22);
		    T2k = FMA(KP951056516, T23, T22);
		    {
			 E T1m, T1v, T2n, T1t;
			 T1m = FNMS(KP559016994, T1l, T1k);
			 T1q = FNMS(KP951056516, T1p, T1m);
			 T1K = FMA(KP951056516, T1p, T1m);
			 {
			      E T27, TL, T1N, Tv;
			      T27 = Tl + Ts;
			      T26 = W[9];
			      T28 = T26 * T27;
			      T29 = W[8];
			      T2c = T29 * T27;
			      Tv = FMA(KP559016994, Tu, Tt);
			      TL = FNMS(KP951056516, TK, Tv);
			      T1N = FMA(KP951056516, TK, Tv);
			      Tk = W[1];
			      TM = Tk * TL;
			      TN = W[0];
			      T2w = TN * TL;
			      T1M = W[17];
			      T1O = T1M * T1N;
			      T1P = W[16];
			      T1S = T1P * T1N;
			 }
			 T1t = FNMS(KP559016994, Tu, Tt);
			 T1v = FNMS(KP951056516, T1u, T1t);
			 T2n = FMA(KP951056516, T1u, T1t);
			 T1s = W[5];
			 T1w = T1s * T1v;
			 T1x = W[4];
			 T1C = T1x * T1v;
			 T2m = W[13];
			 T2o = T2m * T2n;
			 T2p = W[12];
			 T2s = T2p * T2n;
			 {
			      E T1d, T1H, T15, T1Z, T2h, T1X;
			      T15 = FNMS(KP559016994, T14, T13);
			      T1d = FMA(KP951056516, T1c, T15);
			      T1H = FNMS(KP951056516, T1c, T15);
			      T12 = W[2];
			      T1e = T12 * T1d;
			      T1f = W[3];
			      T1E = T1f * T1d;
			      T1G = W[14];
			      T1I = T1G * T1H;
			      T1J = W[15];
			      T1U = T1J * T1H;
			      T1X = FMA(KP559016994, T14, T13);
			      T1Z = FMA(KP951056516, T1Y, T1X);
			      T2h = FNMS(KP951056516, T1Y, T1X);
			      T1W = W[6];
			      T20 = T1W * T1Z;
			      T21 = W[7];
			      T2e = T21 * T1Z;
			      T2g = W[10];
			      T2i = T2g * T2h;
			      T2j = W[11];
			      T2u = T2j * T2h;
			 }
		    }
		    {
			 E T11, T2x, T1r, T1B;
			 T11 = FMA(TN, T10, TM);
			 Rp[0] = Tj - T11;
			 Rm[0] = Tj + T11;
			 T2x = FNMS(Tk, T10, T2w);
			 Im[0] = T2x - T2y;
			 Ip[0] = T2x + T2y;
			 T1r = FNMS(T1f, T1q, T1e);
			 T1B = FMA(T1x, T1A, T1w);
			 Rp[WS(rs, 1)] = T1r - T1B;
			 Rm[WS(rs, 1)] = T1B + T1r;
			 {
			      E T1D, T1F, T1L, T1R;
			      T1D = FNMS(T1s, T1A, T1C);
			      T1F = FMA(T12, T1q, T1E);
			      Im[WS(rs, 1)] = T1D - T1F;
			      Ip[WS(rs, 1)] = T1D + T1F;
			      T1L = FNMS(T1J, T1K, T1I);
			      T1R = FMA(T1P, T1Q, T1O);
			      Rp[WS(rs, 4)] = T1L - T1R;
			      Rm[WS(rs, 4)] = T1R + T1L;
			 }
		    }
		    {
			 E T1T, T1V, T2t, T2v;
			 T1T = FNMS(T1M, T1Q, T1S);
			 T1V = FMA(T1G, T1K, T1U);
			 Im[WS(rs, 4)] = T1T - T1V;
			 Ip[WS(rs, 4)] = T1T + T1V;
			 T2t = FNMS(T2m, T2q, T2s);
			 T2v = FMA(T2g, T2k, T2u);
			 Im[WS(rs, 3)] = T2t - T2v;
			 Ip[WS(rs, 3)] = T2t + T2v;
		    }
		    T2l = FNMS(T2j, T2k, T2i);
		    T2r = FMA(T2p, T2q, T2o);
		    Rp[WS(rs, 3)] = T2l - T2r;
		    Rm[WS(rs, 3)] = T2r + T2l;
		    {
			 E T25, T2b, T2d, T2f;
			 T25 = FNMS(T21, T24, T20);
			 T2b = FMA(T29, T2a, T28);
			 Rp[WS(rs, 2)] = T25 - T2b;
			 Rm[WS(rs, 2)] = T2b + T25;
			 T2d = FNMS(T26, T2a, T2c);
			 T2f = FMA(T1W, T24, T2e);
			 Im[WS(rs, 2)] = T2d - T2f;
			 Ip[WS(rs, 2)] = T2d + T2f;
		    }
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 10},
     {TW_NEXT, 1, 0}
};

static const hc2c_desc desc = { 10, "hc2cbdft_10", twinstr, &GENUS, {68, 18, 54, 0} };

void X(codelet_hc2cbdft_10) (planner *p) {
     X(khc2c_register) (p, hc2cbdft_10, &desc, HC2C_VIA_DFT);
}
#else

/* Generated by: ../../../genfft/gen_hc2cdft.native -compact -variables 4 -pipeline-latency 4 -sign 1 -n 10 -dif -name hc2cbdft_10 -include rdft/scalar/hc2cb.h */

/*
 * This function contains 122 FP additions, 60 FP multiplications,
 * (or, 92 additions, 30 multiplications, 30 fused multiply/add),
 * 61 stack variables, 4 constants, and 40 memory accesses
 */
#include "rdft/scalar/hc2cb.h"

static void hc2cbdft_10(R *Rp, R *Ip, R *Rm, R *Im, const R *W, stride rs, INT mb, INT me, INT ms)
{
     DK(KP951056516, +0.951056516295153572116439333379382143405698634);
     DK(KP587785252, +0.587785252292473129168705954639072768597652438);
     DK(KP250000000, +0.250000000000000000000000000000000000000000000);
     DK(KP559016994, +0.559016994374947424102293417182819058860154590);
     {
	  INT m;
	  for (m = mb, W = W + ((mb - 1) * 18); m < me; m = m + 1, Rp = Rp + ms, Ip = Ip + ms, Rm = Rm - ms, Im = Im - ms, W = W + 18, MAKE_VOLATILE_STRIDE(40, rs)) {
	       E T3, TS, TR, T13, Ti, T12, TT, TU, T1g, T1T, Tr, T1s, TJ, T1h, TG;
	       E T1m, TK, TL, T1k, T1l, T1b, T1P, TY, T1w;
	       {
		    E Td, To, Tg, Tp, Th, TQ, T6, Tl, T9, Tm, Ta, TP, T1, T2;
		    T1 = Rp[0];
		    T2 = Rm[WS(rs, 4)];
		    T3 = T1 + T2;
		    TS = T1 - T2;
		    {
			 E Tb, Tc, Te, Tf;
			 Tb = Rp[WS(rs, 4)];
			 Tc = Rm[0];
			 Td = Tb + Tc;
			 To = Tb - Tc;
			 Te = Rm[WS(rs, 3)];
			 Tf = Rp[WS(rs, 1)];
			 Tg = Te + Tf;
			 Tp = Te - Tf;
		    }
		    Th = Td + Tg;
		    TQ = To + Tp;
		    {
			 E T4, T5, T7, T8;
			 T4 = Rp[WS(rs, 2)];
			 T5 = Rm[WS(rs, 2)];
			 T6 = T4 + T5;
			 Tl = T4 - T5;
			 T7 = Rm[WS(rs, 1)];
			 T8 = Rp[WS(rs, 3)];
			 T9 = T7 + T8;
			 Tm = T7 - T8;
		    }
		    Ta = T6 + T9;
		    TP = Tl + Tm;
		    TR = KP559016994 * (TP - TQ);
		    T13 = KP559016994 * (Ta - Th);
		    Ti = Ta + Th;
		    T12 = FNMS(KP250000000, Ti, T3);
		    TT = TP + TQ;
		    TU = FNMS(KP250000000, TT, TS);
		    {
			 E T1e, T1f, Tn, Tq;
			 T1e = T6 - T9;
			 T1f = Td - Tg;
			 T1g = FNMS(KP951056516, T1f, KP587785252 * T1e);
			 T1T = FMA(KP951056516, T1e, KP587785252 * T1f);
			 Tn = Tl - Tm;
			 Tq = To - Tp;
			 Tr = FMA(KP951056516, Tn, KP587785252 * Tq);
			 T1s = FNMS(KP951056516, Tq, KP587785252 * Tn);
		    }
	       }
	       {
		    E TB, T18, TE, T19, TF, T1j, Tu, T15, Tx, T16, Ty, T1i, TH, TI;
		    TH = Ip[0];
		    TI = Im[WS(rs, 4)];
		    TJ = TH + TI;
		    T1h = TH - TI;
		    {
			 E Tz, TA, TC, TD;
			 Tz = Ip[WS(rs, 4)];
			 TA = Im[0];
			 TB = Tz + TA;
			 T18 = Tz - TA;
			 TC = Im[WS(rs, 3)];
			 TD = Ip[WS(rs, 1)];
			 TE = TC + TD;
			 T19 = TD - TC;
		    }
		    TF = TB - TE;
		    T1j = T18 + T19;
		    {
			 E Ts, Tt, Tv, Tw;
			 Ts = Ip[WS(rs, 2)];
			 Tt = Im[WS(rs, 2)];
			 Tu = Ts + Tt;
			 T15 = Ts - Tt;
			 Tv = Im[WS(rs, 1)];
			 Tw = Ip[WS(rs, 3)];
			 Tx = Tv + Tw;
			 T16 = Tw - Tv;
		    }
		    Ty = Tu - Tx;
		    T1i = T15 + T16;
		    TG = KP559016994 * (Ty - TF);
		    T1m = KP559016994 * (T1i - T1j);
		    TK = Ty + TF;
		    TL = FNMS(KP250000000, TK, TJ);
		    T1k = T1i + T1j;
		    T1l = FNMS(KP250000000, T1k, T1h);
		    {
			 E T17, T1a, TW, TX;
			 T17 = T15 - T16;
			 T1a = T18 - T19;
			 T1b = FNMS(KP951056516, T1a, KP587785252 * T17);
			 T1P = FMA(KP951056516, T17, KP587785252 * T1a);
			 TW = Tu + Tx;
			 TX = TB + TE;
			 TY = FMA(KP951056516, TW, KP587785252 * TX);
			 T1w = FNMS(KP951056516, TX, KP587785252 * TW);
		    }
	       }
	       {
		    E Tj, T2g, TN, T1H, T1U, T26, TZ, T1J, T1Q, T24, T1c, T1C, T1t, T29, T1o;
		    E T1E, T1x, T2b, T20, T21, TM, T1S, TV;
		    Tj = T3 + Ti;
		    T2g = T1h + T1k;
		    TM = TG + TL;
		    TN = Tr + TM;
		    T1H = TM - Tr;
		    T1S = T1m + T1l;
		    T1U = T1S - T1T;
		    T26 = T1T + T1S;
		    TV = TR + TU;
		    TZ = TV - TY;
		    T1J = TV + TY;
		    {
			 E T1O, T14, T1r, T1n, T1v;
			 T1O = T13 + T12;
			 T1Q = T1O + T1P;
			 T24 = T1O - T1P;
			 T14 = T12 - T13;
			 T1c = T14 - T1b;
			 T1C = T14 + T1b;
			 T1r = TL - TG;
			 T1t = T1r - T1s;
			 T29 = T1s + T1r;
			 T1n = T1l - T1m;
			 T1o = T1g + T1n;
			 T1E = T1n - T1g;
			 T1v = TU - TR;
			 T1x = T1v + T1w;
			 T2b = T1v - T1w;
			 {
			      E T1X, T1Z, T1W, T1Y;
			      T1X = TS + TT;
			      T1Z = TJ + TK;
			      T1W = W[9];
			      T1Y = W[8];
			      T20 = FMA(T1W, T1X, T1Y * T1Z);
			      T21 = FNMS(T1W, T1Z, T1Y * T1X);
			 }
		    }
		    {
			 E T10, T2f, Tk, TO;
			 Tk = W[0];
			 TO = W[1];
			 T10 = FMA(Tk, TN, TO * TZ);
			 T2f = FNMS(TO, TN, Tk * TZ);
			 Rp[0] = Tj - T10;
			 Ip[0] = T2f + T2g;
			 Rm[0] = Tj + T10;
			 Im[0] = T2f - T2g;
		    }
		    {
			 E T1V, T22, T1N, T1R;
			 T1N = W[6];
			 T1R = W[7];
			 T1V = FNMS(T1R, T1U, T1N * T1Q);
			 T22 = FMA(T1R, T1Q, T1N * T1U);
			 Rp[WS(rs, 2)] = T1V - T20;
			 Ip[WS(rs, 2)] = T21 + T22;
			 Rm[WS(rs, 2)] = T20 + T1V;
			 Im[WS(rs, 2)] = T21 - T22;
		    }
		    {
			 E T1p, T1A, T1y, T1z;
			 {
			      E T11, T1d, T1q, T1u;
			      T11 = W[2];
			      T1d = W[3];
			      T1p = FNMS(T1d, T1o, T11 * T1c);
			      T1A = FMA(T1d, T1c, T11 * T1o);
			      T1q = W[4];
			      T1u = W[5];
			      T1y = FMA(T1q, T1t, T1u * T1x);
			      T1z = FNMS(T1u, T1t, T1q * T1x);
			 }
			 Rp[WS(rs, 1)] = T1p - T1y;
			 Ip[WS(rs, 1)] = T1z + T1A;
			 Rm[WS(rs, 1)] = T1y + T1p;
			 Im[WS(rs, 1)] = T1z - T1A;
		    }
		    {
			 E T1F, T1M, T1K, T1L;
			 {
			      E T1B, T1D, T1G, T1I;
			      T1B = W[14];
			      T1D = W[15];
			      T1F = FNMS(T1D, T1E, T1B * T1C);
			      T1M = FMA(T1D, T1C, T1B * T1E);
			      T1G = W[16];
			      T1I = W[17];
			      T1K = FMA(T1G, T1H, T1I * T1J);
			      T1L = FNMS(T1I, T1H, T1G * T1J);
			 }
			 Rp[WS(rs, 4)] = T1F - T1K;
			 Ip[WS(rs, 4)] = T1L + T1M;
			 Rm[WS(rs, 4)] = T1K + T1F;
			 Im[WS(rs, 4)] = T1L - T1M;
		    }
		    {
			 E T27, T2e, T2c, T2d;
			 {
			      E T23, T25, T28, T2a;
			      T23 = W[10];
			      T25 = W[11];
			      T27 = FNMS(T25, T26, T23 * T24);
			      T2e = FMA(T25, T24, T23 * T26);
			      T28 = W[12];
			      T2a = W[13];
			      T2c = FMA(T28, T29, T2a * T2b);
			      T2d = FNMS(T2a, T29, T28 * T2b);
			 }
			 Rp[WS(rs, 3)] = T27 - T2c;
			 Ip[WS(rs, 3)] = T2d + T2e;
			 Rm[WS(rs, 3)] = T2c + T27;
			 Im[WS(rs, 3)] = T2d - T2e;
		    }
	       }
	  }
     }
}

static const tw_instr twinstr[] = {
     {TW_FULL, 1, 10},
     {TW_NEXT, 1, 0}
};

static const hc2c_desc desc = { 10, "hc2cbdft_10", twinstr, &GENUS, {92, 30, 30, 0} };

void X(codelet_hc2cbdft_10) (planner *p) {
     X(khc2c_register) (p, hc2cbdft_10, &desc, HC2C_VIA_DFT);
}
#endif
