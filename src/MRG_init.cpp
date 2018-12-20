#include <assert.h>
#include <vector>
#include <fstream>

#include "MRG.h"
#include "utils.h"

#include <nvec_ser/nvector_serial.h>
#include <cvode/cvode.h>
#include <cvode/cvode_dense.h>


const MRG_REAL PI = arma::datum::pi;

const MRG_REAL MRG::vrest		= -80;			// mV
const MRG_REAL MRG::mysalength	= 3;			// um  
const MRG_REAL MRG::nodelength	= 1.0;			// um
const MRG_REAL MRG::space_p1	= 0.002;		// um
const MRG_REAL MRG::space_p2	= 0.004;		// um
const MRG_REAL MRG::space_i	= 0.004;		// um
const MRG_REAL MRG::r			= 70;			// Ohm*cm
const MRG_REAL MRG::mycm		= 0.1;			// uF/cm2
const MRG_REAL MRG::mygm		= 0.001;		// S/cm2
const MRG_REAL MRG::c			= 2;			// uF/cm2

// const MRG_REAL MRG::g_nap	= 0.010;		//  sodium channel conductivity [S/cm^2]
// const MRG_REAL MRG::g_naf	= 3;			// S/cm^2
// const MRG_REAL MRG::g_k		= 0.080;		// S/cm^2
const MRG_REAL MRG::g_kf		= 0;			// S/cm^2 (deactivated)
// const MRG_REAL MRG::g_l		= 0.007;		//  leak channel conductivity [S/cm^2] 
const MRG_REAL MRG::e_na 		= 50.0;			// mV
const MRG_REAL MRG::e_k			= -90.0;		// mV
const MRG_REAL MRG::e_l			= -90.0;		// mV

const MRG_REAL MRG::g_p1		= 0.001;		// S/cm^2
const MRG_REAL MRG::g_p2		= 0.0001;		// S/cm^2 
const MRG_REAL MRG::g_i			= MRG::g_p2;	// S/cm^2



MRG::MRG(MRG_REAL fiber_diam) :
	fiberD(fiber_diam),		// um
	g_nap(0.010),			// sodium channel conductivity [S/cm^2]
	g_k(0.080),				// S/cm^2
	g_l(0.007),				// leak channel conductivity [S/cm^2] 
	g_naf(3)				// S/cm^2
{
	assert(fiberD == 10.0 || fiberD == 16.0);

	if(fiberD == 10.0)
	{
		axonD		= 6.9;	// um 
		nodeD		= 3.3;	// um
		mysaD		= 3.3;	// um
		flutD		= 6.9;	// um
		deltax		= 1250;	// um
		flutlength	= 46;	// um
		nl			= 120;	// dimensionless
	}
	else if(fiberD == 16.0)
	{
		axonD		= 12.7;	// um 
		nodeD		= 5.5;	// um
		mysaD		= 5.5;	// um
		flutD		= 12.7;	// um
		deltax		= 1500;	// um
		flutlength	= 60;	// um
		nl			= 150;	// dimensionless
	}

	interlength = (deltax - nodelength - (2*mysalength) - (2*flutlength))/6;

	celsius = 36.0;
	q10_1 = pow(2.2, ((celsius-20.0)/10.0));
	q10_2 = pow(2.9, ((celsius-20.0)/10.0));
	q10_3 = pow(3.0, ((celsius-36.0)/10.0));
}


void load_data(const char *filename, MRG_MATRIX_REAL &data)
{
	std::vector<MRG_REAL> x;
	std::vector<MRG_REAL> y;
	std::vector<MRG_REAL> z;
	std::vector<MRG_REAL> Ve_pulse;

	// optional reserving, for performance
	x.reserve(500);
	y.reserve(500);
	z.reserve(500);
	Ve_pulse.reserve(500);
	
	std::ifstream in_file(filename);
	assert(in_file.is_open());
	
	int num_data = 0;
	std::string line;
	float curr_x, curr_y, curr_z, curr_Ve_pulse;
	while(in_file.good())
	{
		getline(in_file, line);
		if(line.find_first_not_of("\t\n ") == std::string::npos)
		{
			continue;
		}

		sscanf(line.c_str(), "%f\t%f\t%f\t%f", &curr_x, &curr_y, &curr_z, &curr_Ve_pulse);
		
		x.push_back(curr_x);
		y.push_back(curr_y);
		z.push_back(curr_z);
		Ve_pulse.push_back(curr_Ve_pulse);
		
		++num_data;
	}
	in_file.close();
	assert(num_data > 0);

	std::vector<MRG_REAL>::const_iterator iter_x = x.begin();
	std::vector<MRG_REAL>::const_iterator iter_x_end = x.end();
	std::vector<MRG_REAL>::const_iterator iter_y = y.begin();
	std::vector<MRG_REAL>::const_iterator iter_y_end = y.end();
	std::vector<MRG_REAL>::const_iterator iter_z = z.begin();
	std::vector<MRG_REAL>::const_iterator iter_z_end = z.end();
	std::vector<MRG_REAL>::const_iterator iter_Ve = Ve_pulse.begin();
	std::vector<MRG_REAL>::const_iterator iter_Ve_end = Ve_pulse.end();
	data.set_size(num_data, 4);
	for(int i = 0; i < num_data; ++i)
	{
		data(i, 0) = *iter_x;
		data(i, 1) = *iter_y;
		data(i, 2) = *iter_z;
		data(i, 3) = *iter_Ve;

		if(iter_x == iter_x_end || iter_y == iter_y_end || iter_z == iter_z_end || iter_Ve == iter_Ve_end)
		{
			break;
		}

		++iter_x;
		++iter_y;
		++iter_z;
		++iter_Ve;
	}
	assert(iter_x == iter_x_end && iter_y == iter_y_end && iter_z == iter_z_end && iter_Ve == iter_Ve_end);

	// debug
	// data.raw_print("data =");
	// puts("\n");
}


void MRG::interpolate(const char *file, MRG_MATRIX_REAL &Ve, int &N, MRG_MATRIX_REAL &Vlr) const
{
	MRG_MATRIX_REAL data;
	load_data(file, data);

	MRG_MATRIX_REAL Ve_pulse(data.col(3));
	Ve_pulse *= 1000.0f;	// convert to mV

	data.col(0) *= 100.0f;	// convert to cm
	data.col(1) *= 100.0f;	// convert to cm
	data.col(2) *= 100.0f;	// convert to cm

	MRG_MATRIX_REAL s(data.n_rows, 1);
	s(0, 0) = 0.0f;
	for(unsigned int i = 1; i < data.n_rows; ++i)
	{
		MRG_MATRIX_REAL::const_row_iterator xyz_iter1 = data.begin_row(i-1);
		MRG_REAL x1 = *xyz_iter1;
		MRG_REAL y1 = *(++xyz_iter1);
		MRG_REAL z1 = *(++xyz_iter1);

		MRG_MATRIX_REAL::const_row_iterator xyz_iter2 = data.begin_row(i);
		MRG_REAL x2 = *xyz_iter2;
		MRG_REAL y2 = *(++xyz_iter2);
		MRG_REAL z2 = *(++xyz_iter2);

		s(i, 0) = s(i-1, 0) + sqrt((x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) + (z2-z1)*(z2-z1));
	}

	int n = (int) (s[data.n_rows-2]/(1e-4f*deltax)) + 16;
	N = n + 1;

	MRG_MATRIX_REAL x_n, x_m, x_f, x_i;
	const int half = 0;
	if(half == 0)
	{
		calcX(N, x_n, x_m, x_f, x_i);
		
		x_n -= 8.0f * (deltax+1) * 1e-4f;
		x_m -= 8.0f * (deltax+1) * 1e-4f;
		x_f -= 8.0f * (deltax+1) * 1e-4f;
		x_i -= 8.0f * (deltax+1) * 1e-4f;
	}
	else if(half == 1)
	{
		calcX(N/2, x_n, x_m, x_f, x_i);

		N /= 2;
		n = N - 1;
		x_n += N * (deltax+1) * 1e-4f;
		x_m += N * (deltax+1) * 1e-4f;
		x_f += N * (deltax+1) * 1e-4f;
		x_i += N * (deltax+1) * 1e-4f;
	}
	else if(half == 2)
	{
		calcX(N/2, x_n, x_m, x_f, x_i);
		N /= 2;
		n = N - 1;
	}
	
	MRG_MATRIX_REAL::fixed<2, 1> xlr;
	xlr(0, 0) = x_n(0, 0) - 2e-4f;
	xlr(1, 0) = x_n(N-1, 0) + 2e-4f;

	x_n -= 1e-4f * deltax / 10.0f;
	x_m -= 1e-4f * deltax / 10.0f;
	x_f -= 1e-4f * deltax / 10.0f;
	x_i -= 1e-4f * deltax / 10.0f;
	xlr -= 1e-4f * deltax / 10.0f;

	MRG_MATRIX_REAL Ve_n;
	MRG_MATRIX_REAL Ve_m_1, Ve_m_2;
	MRG_MATRIX_REAL Ve_f_1, Ve_f_2;
	MRG_MATRIX_REAL Ve_i_1, Ve_i_2, Ve_i_3, Ve_i_4, Ve_i_5, Ve_i_6;

	interp1(s, Ve_pulse, xlr, Vlr);
	interp1(s, Ve_pulse, x_n, Ve_n);
	interp1(s, Ve_pulse, x_m.col(0), Ve_m_1);
	interp1(s, Ve_pulse, x_m.col(1), Ve_m_2);
	interp1(s, Ve_pulse, x_f.col(0), Ve_f_1);
	interp1(s, Ve_pulse, x_f.col(1), Ve_f_2);
	interp1(s, Ve_pulse, x_i.col(0), Ve_i_1);
	interp1(s, Ve_pulse, x_i.col(1), Ve_i_2);
	interp1(s, Ve_pulse, x_i.col(2), Ve_i_3);
	interp1(s, Ve_pulse, x_i.col(3), Ve_i_4);
	interp1(s, Ve_pulse, x_i.col(4), Ve_i_5);
	interp1(s, Ve_pulse, x_i.col(5), Ve_i_6);

	Ve = Ve_n;
	Ve.insert_rows(Ve.n_rows, arma::zeros<MRG_MATRIX_REAL>(4*N, 1));
	Ve.insert_rows(Ve.n_rows, Ve_m_1);
	Ve.insert_rows(Ve.n_rows, Ve_m_2);
	Ve.insert_rows(Ve.n_rows, Ve_f_1);
	Ve.insert_rows(Ve.n_rows, Ve_f_2);
	Ve.insert_rows(Ve.n_rows, arma::zeros<MRG_MATRIX_REAL>(2*(N-1), 1));
	Ve.insert_rows(Ve.n_rows, Ve_i_1);
	Ve.insert_rows(Ve.n_rows, Ve_i_2);
	Ve.insert_rows(Ve.n_rows, Ve_i_3);
	Ve.insert_rows(Ve.n_rows, Ve_i_4);
	Ve.insert_rows(Ve.n_rows, Ve_i_5);
	Ve.insert_rows(Ve.n_rows, Ve_i_6);

	// debug
	// Ve_pulse.raw_print("Ve_pulse =");
	// puts("\n");
	// s.raw_print("s =");
	// puts("\n");
	// x_n.raw_print("x_n =");
	// puts("\n");
	// x_m.raw_print("x_m =");
	// puts("\n");
	// x_f.raw_print("x_f =");
	// puts("\n");
	// x_i.raw_print("x_i =");
	// puts("\n");
	// xlr.raw_print("xlr =");
	// puts("\n");
	// Vlr.raw_print("Vlr =");
	// puts("\n");
	// Ve.raw_print("Ve =");
	// puts("\n");
}


void MRG::calcX(const int N, MRG_MATRIX_REAL &x_n, MRG_MATRIX_REAL &x_m1, MRG_MATRIX_REAL &x_f1, MRG_MATRIX_REAL &x_i1) const
{
	x_n.set_size(N, 1);
	x_m1.set_size(N-1, 2);
	x_f1.set_size(N-1, 2);
	x_i1.set_size(N-1, 6);

	x_n(0, 0) = 0.5f * 1e-4f;
	x_m1(0, 0) = x_n(0, 0) + 0.5f*1e-4f + mysalength/2.0f*1e-4f;
	x_m1(0, 1) = x_n(0, 0) + (1+deltax)*1e-4f - mysalength/2.0f*1e-4f;
	x_f1(0, 0) = x_m1(0, 0) + flutlength/2.0f*1e-4f + mysalength/2.0f*1e-4f;
	x_f1(0, 1) = x_m1(0, 1) - flutlength*1e-4f - mysalength/2.0f*1e-4f;

	x_i1(0, 0) = x_f1(0, 0) + flutlength/2.0f*1e-4f + interlength/2.0f*1e-4f;
	for(int i = 1; i < 6; ++i)
	{
		// this looks like it gets overwritten further down, so what's the point?
		x_i1(0, i) = x_i1(0, 0) + i*interlength*1e-4f;
	}

	for(int i = 1; i < N; ++i)
	{
		x_n(i, 0) = x_n(i-1, 0) + deltax*1e-4f + 1e-4f;
	}

	for(int i = 1; i < N-1; ++i)
	{
		x_m1(i, 0) = x_m1(i-1, 0) + (1 + deltax)*1e-4f;
		x_m1(i, 1) = x_m1(i-1, 1) + (1 + deltax)*1e-4f;
		x_f1(i, 0) = x_f1(i-1, 0) + (1 + deltax)*1e-4f;
		x_f1(i, 1) = x_f1(i-1, 1) + (1 + deltax)*1e-4f;
		for(int j = 0; j < 6; ++j)
		{
			x_i1(i, j) = x_i1(i-1, j) + (1 + deltax)*1e-4f;
		}
	}

	x_m1.swap_cols(0, 1);
	x_f1.swap_cols(0, 1);
	for(int i = 0; i < 6/2; ++i)
	{
		x_i1.swap_cols(i, 6-1-i);
	}
}


void MRG::write_results(const char *file_name)
{
	unsigned int N_nodes = N_inter + 1;
	assert(!t.empty() && N_nodes > 0);

	FILE *out_file = fopen(file_name, "wb");

	fprintf(out_file, "t");
	for(unsigned int i = 0; i < N_nodes; ++i)
	{
		fprintf(out_file, ",Node_%04d", i+1);
	}
	fprintf(out_file, "\n");

	for(unsigned int i = 0; i < t.size(); ++i)
	{
		fprintf(out_file, "%0.8e", t[i]);
		for(unsigned int j = 0; j < N_nodes; ++j)
		{
			fprintf(out_file, ",%0.8e", Y(j, i));
		}
		fprintf(out_file, "\n");
	}

	fclose(out_file);
}


void MRG::debug_dump(const char *file_name)
{
	assert(!t.empty() && Y.n_rows > 0);

	FILE *out_file = fopen(file_name, "wb");
	for(unsigned int i = 0; i < t.size(); ++i)
	{
		fprintf(out_file, "%f", t[i]);
		for(unsigned int j = 0; j < Y.n_rows; ++j)
		{
			fprintf(out_file, ",%f", Y(j, i));
		}
		fprintf(out_file, "\n");
	}
	fclose(out_file);
}


void MRG::m_ab(const MRG_MATRIX_REAL &V, MRG_MATRIX_REAL &m_alpha, MRG_MATRIX_REAL &m_beta) const
{
	assert(V.is_colvec());
	assert(V.n_rows >= 1);
	m_alpha = ((V + 21.4)*1.86)/(1 - exp(-(V + 21.4)/10.3)) * q10_1;
	m_beta = (-(V + 25.7)*0.086)/(1 - exp((V + 25.7)/9.16)) * q10_1;
}


void MRG::h_ab(const MRG_MATRIX_REAL &V, MRG_MATRIX_REAL &h_alpha, MRG_MATRIX_REAL &h_beta) const
{
	assert(V.is_colvec());
	assert(V.n_rows >= 1);
	h_alpha = (-(V + 114)*0.062)/(1 - exp((V + 114)/11)) * q10_2;
	h_beta = 2.3/(1 + exp(-(V + 31.8)/13.4)) * q10_2;
}


void MRG::p_ab(const MRG_MATRIX_REAL &V, MRG_MATRIX_REAL &p_alpha, MRG_MATRIX_REAL &p_beta) const
{
	assert(V.is_colvec());
	assert(V.n_rows >= 1);
	p_alpha = ((V + 27)*0.01)/(1 - exp(-(V + 27)/10.2)) * q10_1;
	p_beta = (-(V + 34)*0.00025)/(1 - exp((V + 34)/10)) * q10_1;
}


void MRG::s_ab(const MRG_MATRIX_REAL &V, MRG_MATRIX_REAL &s_alpha, MRG_MATRIX_REAL &s_beta) const
{
	assert(V.is_colvec());
	assert(V.n_rows >= 1);
	s_alpha = 0.3/(1 + exp((V + 53)/-5)) * q10_3;
	s_beta = 0.03/(1 + exp((V + 90)/-1)) * q10_3;
}


void MRG::paracomp(MRG_REAL diameter, MRG_REAL length, MRG_REAL space, MRG_REAL fiberDia,
	MRG_REAL c, MRG_REAL r, MRG_REAL g, MRG_REAL nl, MRG_REAL xc, MRG_REAL xg,
	MRG_REAL &rax, MRG_REAL &rpx, MRG_REAL &cmem, MRG_REAL &cmy, MRG_REAL &gpas, MRG_REAL &gmy)
{
	// args must be in um, ohm*cm and uF respectively
	rax = calcResAxial(diameter, length, r);
	rpx = calcResPeriax(diameter, length, space, r);
	cmem = calcCapacity(diameter, length, c);
	cmy = calcMyelinCap(fiberDia, length, xc, nl);
	gpas = calcConductance(diameter, length, g);
	gmy = calcMyelinCond(fiberDia, length, xg, nl);
}


MRG_REAL MRG::calcResAxial(MRG_REAL diameter, MRG_REAL length, MRG_REAL r)
{
	// um and Ohm*cm
	MRG_REAL a = PI * (diameter*diameter);
	MRG_REAL rax = calcRes(a, length, r);
	return rax;
}


MRG_REAL MRG::calcResPeriax(MRG_REAL diameter, MRG_REAL length, MRG_REAL space, MRG_REAL r)
{
	// um and Ohm*cm
	MRG_REAL a = PI * ((diameter + (2*space))*(diameter + (2*space)) - diameter*diameter);
	MRG_REAL rpx = calcRes(a, length, r);
	return rpx;
}


MRG_REAL MRG::calcCapacity(MRG_REAL diameter, MRG_REAL length, MRG_REAL cap)
{
	// um and uF/cm^2
	cap = cap*1e-2;				// pF/um^2
	MRG_REAL c = cap*diameter*length*PI;	// c is in uF
	return c;
}


MRG_REAL MRG::calcMyelinCap(MRG_REAL fiberDiameter, MRG_REAL length, MRG_REAL xc, MRG_REAL nl)
{
	xc = xc/(nl*2);
	MRG_REAL c = calcCapacity(fiberDiameter, length, xc);	// c is in uF
	return c;
}


MRG_REAL MRG::calcConductance(MRG_REAL diameter, MRG_REAL length, MRG_REAL gi)
{
	// in S/cm^2 and um
	gi = gi*1e1;	// nS/um^2
	MRG_REAL g = gi*diameter*length*PI;
	return g;
}


MRG_REAL MRG::calcMyelinCond(MRG_REAL fiberDiameter, MRG_REAL length, MRG_REAL xg, MRG_REAL nl)
{
	xg = xg/(nl*2);
	MRG_REAL gmy = calcConductance(fiberDiameter, length, xg);
	return gmy;
}


MRG_REAL MRG::calcRes(MRG_REAL area, MRG_REAL length, MRG_REAL r)
{
	MRG_REAL ra = r*1e-5;	// GOhm*um
	MRG_REAL res = (4*length*ra)/area;
	return res;
}
