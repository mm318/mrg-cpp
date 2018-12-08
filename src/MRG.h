#ifndef _MRG_H_
#define _MRG_H_

#include <armadillo>
#include <sundials/sundials_types.h>
#include <sundials/sundials_nvector.h>


typedef realtype 			MRG_REAL;
typedef arma::Mat<MRG_REAL>	MRG_MATRIX_REAL;


class MRG
{
public:
	MRG(MRG_REAL fiber_diam = 16.0);

	void run(MRG_REAL dur, const char *file, MRG_REAL V_fe, MRG_REAL V_applied, MRG_REAL stim_start, MRG_REAL stim_end);

	int odeMcIntyr(realtype t, N_Vector y, N_Vector ydot) const;

	void write_results(const char *file_name);

	void debug_dump(const char *file_name);

private:
	void interpolate(const char *file, MRG_MATRIX_REAL &Ve, int &N, MRG_MATRIX_REAL &Vlr) const;
	
	void calcX(const int N, MRG_MATRIX_REAL &x_n, MRG_MATRIX_REAL &x_m1, MRG_MATRIX_REAL &x_f1, MRG_MATRIX_REAL &x_i1) const;

	// helper functions
	static void paracomp(MRG_REAL diameter, MRG_REAL length, MRG_REAL space, MRG_REAL fiberDia,
		MRG_REAL c, MRG_REAL r, MRG_REAL g, MRG_REAL nl, MRG_REAL xc, MRG_REAL xg,
		MRG_REAL &rax, MRG_REAL &rpx, MRG_REAL &cmem, MRG_REAL &cmy, MRG_REAL &gpas, MRG_REAL &gmy);

	static MRG_REAL calcResAxial(MRG_REAL diameter, MRG_REAL length, MRG_REAL r);
	static MRG_REAL calcResPeriax(MRG_REAL diameter, MRG_REAL length, MRG_REAL space, MRG_REAL r);
	static MRG_REAL calcCapacity(MRG_REAL diameter, MRG_REAL length, MRG_REAL cap);
	static MRG_REAL calcMyelinCap(MRG_REAL fiberDiameter, MRG_REAL length, MRG_REAL xc, MRG_REAL nl);
	static MRG_REAL calcConductance(MRG_REAL diameter, MRG_REAL length, MRG_REAL gi);
	static MRG_REAL calcMyelinCond(MRG_REAL fiberDiameter, MRG_REAL length, MRG_REAL xg, MRG_REAL nl);
	static MRG_REAL calcRes(MRG_REAL area, MRG_REAL length, MRG_REAL r);

	void m_ab(const MRG_MATRIX_REAL &V, MRG_MATRIX_REAL &m_alpha, MRG_MATRIX_REAL &m_beta) const;
	void h_ab(const MRG_MATRIX_REAL &V, MRG_MATRIX_REAL &h_alpha, MRG_MATRIX_REAL &h_beta) const;
	void p_ab(const MRG_MATRIX_REAL &V, MRG_MATRIX_REAL &p_alpha, MRG_MATRIX_REAL &p_beta) const;
	void s_ab(const MRG_MATRIX_REAL &V, MRG_MATRIX_REAL &s_alpha, MRG_MATRIX_REAL &s_beta) const;

	void nodeEq
	(
		const MRG_MATRIX_REAL &V,
		const MRG_MATRIX_REAL &m,
		const MRG_MATRIX_REAL &h,
		const MRG_MATRIX_REAL &p,
		const MRG_MATRIX_REAL &s,
		const MRG_MATRIX_REAL &Ei,
		const MRG_MATRIX_REAL &EiMl,
		const MRG_MATRIX_REAL &EiMr,
		const MRG_MATRIX_REAL &Vex,
		const MRG_MATRIX_REAL &VexMl,
		const MRG_MATRIX_REAL &VexMr,
		MRG_MATRIX_REAL &dV,
		MRG_MATRIX_REAL &dm,
		MRG_MATRIX_REAL &dh,
		MRG_MATRIX_REAL &dp,
		MRG_MATRIX_REAL &ds
	) const;

	void mysaEq
	(
		const MRG_MATRIX_REAL &V,
		const MRG_MATRIX_REAL &Vp,
		const MRG_MATRIX_REAL &Ei,
		const MRG_MATRIX_REAL &EiN,
		const MRG_MATRIX_REAL &EiF,
		const MRG_MATRIX_REAL &Ep,
		const MRG_MATRIX_REAL &EpN,
		const MRG_MATRIX_REAL &EpF,
		const MRG_MATRIX_REAL &Vex,
		const MRG_MATRIX_REAL &VexN,
		const MRG_MATRIX_REAL &VexF,
		MRG_MATRIX_REAL &dV,
		MRG_MATRIX_REAL &dVp
	) const;

	void flutEq
	(
		const MRG_MATRIX_REAL &V,
		const MRG_MATRIX_REAL &Vp,
		const MRG_MATRIX_REAL &Ei,
		const MRG_MATRIX_REAL &EiM,
		const MRG_MATRIX_REAL &EiI,
		const MRG_MATRIX_REAL &Ep,
		const MRG_MATRIX_REAL &EpM,
		const MRG_MATRIX_REAL &EpI,
		const MRG_MATRIX_REAL &Vex,
		const MRG_MATRIX_REAL &VexM,
		const MRG_MATRIX_REAL &VexI,
		MRG_MATRIX_REAL &dV,
		MRG_MATRIX_REAL &dVp
	) const;

	void interEq
	(
		const MRG_MATRIX_REAL &V,
		const MRG_MATRIX_REAL &Vp,
		const MRG_MATRIX_REAL &Ei,
		const MRG_MATRIX_REAL &EiFl,
		const MRG_MATRIX_REAL &EiFr,
		const MRG_MATRIX_REAL &Ep,
		const MRG_MATRIX_REAL &EpFl,
		const MRG_MATRIX_REAL &EpFr,
		const MRG_MATRIX_REAL &Vex,
		const MRG_MATRIX_REAL &VexFl,
		const MRG_MATRIX_REAL &VexFr,
		MRG_MATRIX_REAL &dV,
		MRG_MATRIX_REAL &dVp
	) const;

	void axialI
	(
		const MRG_MATRIX_REAL &V,
		const MRG_MATRIX_REAL &V1,
		const MRG_MATRIX_REAL &V2,
		const MRG_REAL r,
		const MRG_REAL r1,
		const MRG_REAL r2,
		MRG_MATRIX_REAL &I
	) const;

	void compartment
	(
		const MRG_MATRIX_REAL &V,
		const MRG_MATRIX_REAL &Vp,
		const MRG_MATRIX_REAL &Iaxonal,
		const MRG_MATRIX_REAL &Iperiaxonal,
		const MRG_MATRIX_REAL &Iex,
		const MRG_REAL epas,
		const MRG_REAL cmem,
		const MRG_REAL cmy,
		const MRG_REAL gmem,
		const MRG_REAL gmy,
		MRG_MATRIX_REAL &dV,
		MRG_MATRIX_REAL &dVp
	) const;

	void axnode2
	(
		const MRG_MATRIX_REAL &V,
		const MRG_MATRIX_REAL &m,
		const MRG_MATRIX_REAL &h,
		const MRG_MATRIX_REAL &p,
		const MRG_MATRIX_REAL &s,
		MRG_MATRIX_REAL &I,
		MRG_MATRIX_REAL &dm,
		MRG_MATRIX_REAL &dh,
		MRG_MATRIX_REAL &dp,
		MRG_MATRIX_REAL &ds
	) const;

	void dpdt
	(
		const MRG_MATRIX_REAL &alpha,
		const MRG_MATRIX_REAL &beta,
		const MRG_MATRIX_REAL &para,
		MRG_MATRIX_REAL &dp
	) const;


	static const MRG_REAL vrest;
	static const MRG_REAL mysalength;
	static const MRG_REAL nodelength;
	static const MRG_REAL space_p1;
	static const MRG_REAL space_p2;
	static const MRG_REAL space_i;
	static const MRG_REAL r;
	static const MRG_REAL mycm;
	static const MRG_REAL mygm;
	static const MRG_REAL c;
	// static const MRG_REAL g_nap;
	// static const MRG_REAL g_naf;
	// static const MRG_REAL g_k;
	static const MRG_REAL g_kf;
	// static const MRG_REAL g_l;
	static const MRG_REAL e_na;
	static const MRG_REAL e_k;
	static const MRG_REAL e_l;
	static const MRG_REAL g_p1;
	static const MRG_REAL g_p2;
	static const MRG_REAL g_i;

	MRG_REAL fiberD;
	MRG_REAL axonD;
	MRG_REAL nodeD;
	MRG_REAL mysaD;
	MRG_REAL flutD;
	MRG_REAL deltax;
	MRG_REAL flutlength;
	MRG_REAL nl;
	MRG_REAL interlength;

	MRG_REAL celsius;
	MRG_REAL q10_1;
	MRG_REAL q10_2;
	MRG_REAL q10_3;

	MRG_REAL r_mysa;
	MRG_REAL r_pn1;
	MRG_REAL c_mysa;
	MRG_REAL c_mysa_m;
	MRG_REAL g_mysa;
	MRG_REAL g_mysa_m;

	MRG_REAL r_flut;
	MRG_REAL r_pn2;
	MRG_REAL c_flut;
	MRG_REAL c_flut_m;
	MRG_REAL g_flut;
	MRG_REAL g_flut_m;

	MRG_REAL r_inter;
	MRG_REAL r_px;
	MRG_REAL c_inter;
	MRG_REAL c_inter_m;
	MRG_REAL g_inter;
	MRG_REAL g_inter_m;

	MRG_REAL g_nap;
	MRG_REAL g_k;
	MRG_REAL g_l;
	MRG_REAL g_naf;
	MRG_REAL r_node;
	MRG_REAL c_node;
	MRG_REAL r_pn0;

	int N_inter;
	mutable MRG_MATRIX_REAL Xlr;

	int i_node[2];
	int i_para_m[2];
	int i_para_h[2];
	int i_para_p[2];
	int i_para_s[2];
	int i_mysa[4];
	int i_flut[4];
	int i_para_n[4];
	int i_inter[6][2];
	int i_mysa_b[4];
	int i_flut_b[4];
	int i_inter_b[6][2];

	MRG_REAL m_stim_start;
	MRG_REAL m_stim_end;
	MRG_MATRIX_REAL Xlr_stim;
	MRG_MATRIX_REAL V_stim;
	MRG_MATRIX_REAL Istim;

	std::vector<MRG_REAL> t;
	MRG_MATRIX_REAL Y;
};

#endif

