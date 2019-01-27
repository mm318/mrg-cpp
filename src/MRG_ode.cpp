#include <assert.h>
#include <math.h>
#include <thread>

#include "MRG.h"
#include "utils.h"

#include <nvector/nvector_serial.h>
#include <sunmatrix/sunmatrix_dense.h> /* access to dense SUNMatrix            */
#include <sunlinsol/sunlinsol_dense.h> /* access to dense SUNLinearSolver      */
#include <cvode/cvode.h>
#include <cvode/cvode_direct.h>        /* access to CVDls interface            */


constexpr uint64_t REFERENCE_PERIOD = 4;  // don't use the first period as the reference since it
                                          // might not have settled into a repeatable state yet
                                          // since the state at the start of the model could be very
                                          // different from the state at the end of a later period


// wrapper function for ode callback
int odeCVode(realtype t, N_Vector y, N_Vector ydot, void * user_data)
{
  MRG * model = static_cast<MRG *>(user_data);
  return model->odeMcIntyr(t, y, ydot);
}


void MRG::run(MRG_REAL V_fe, MRG_REAL V_applied, MRG_REAL period, MRG_REAL stim_start, MRG_REAL stim_end,
              unsigned int time_steps, bool cache_on)
{
  paracomp(mysaD, mysalength, space_p1, fiberD, c, r, g_p1, nl, mycm, mygm,
           r_mysa, r_pn1, c_mysa, c_mysa_m, g_mysa, g_mysa_m);
  paracomp(flutD, flutlength, space_p2, fiberD, c, r, g_p2, nl, mycm, mygm,
           r_flut, r_pn2, c_flut, c_flut_m, g_flut, g_flut_m);
  paracomp(axonD, interlength, space_i, fiberD, c, r, g_i, nl, mycm, mygm,
           r_inter, r_px, c_inter, c_inter_m, g_inter, g_inter_m);

  g_nap = calcConductance(nodeD, nodelength, g_nap);
  g_k = calcConductance(nodeD, nodelength, g_k);
  g_l = calcConductance(nodeD, nodelength, g_l);
  g_naf = calcConductance(nodeD, nodelength, g_naf);
  r_node = calcResAxial(nodeD, nodelength, r);
  c_node = calcCapacity(nodeD, nodelength, c);
  r_pn0 = calcResPeriax(nodeD, nodelength, space_p1, r);

  Xlr_stim = Xlr * (V_applied / V_fe);
  V_stim *= (V_applied / V_fe);
  m_period = period;
  m_stim_start = stim_start;
  m_stim_end = stim_end;
  int N_nodes = N_inter + 1;

  // index values of the dV vector
  i_node[0] = 0;
  i_node[1] = N_nodes - 1;
  i_para_m[0] = i_node[1] + 1;
  i_para_m[1] = i_node[1] + N_nodes;
  i_para_h[0] = i_para_m[1] + 1;
  i_para_h[1] = i_para_m[1] + N_nodes;
  i_para_p[0] = i_para_h[1] + 1;
  i_para_p[1] = i_para_h[1] + N_nodes;
  i_para_s[0] = i_para_p[1] + 1;
  i_para_s[1] = i_para_p[1] + N_nodes;
  i_mysa[0] = i_para_s[1] + 1;
  i_mysa[1] = i_para_s[1] + N_inter;
  i_mysa[2] = i_para_s[1] + N_inter + 1;
  i_mysa[3] = i_para_s[1] + N_inter * 2;
  i_flut[0] = i_mysa[3] + 1;
  i_flut[1] = i_mysa[3] + N_inter;
  i_flut[2] = i_mysa[3] + N_inter + 1;
  i_flut[3] = i_mysa[3] + N_inter * 2;
  i_para_n[0] = i_flut[3] + 1;
  i_para_n[1] = i_flut[3] + N_inter;
  i_para_n[2] = i_flut[3] + N_inter + 1;
  i_para_n[3] = i_flut[3] + N_inter * 2;
  i_inter[0][0] = i_para_n[3] + 1;
  i_inter[0][1] = i_para_n[3] + N_inter;
  i_inter[1][0] = i_para_n[3] + N_inter + 1;
  i_inter[1][1] = i_para_n[3] + N_inter * 2;
  i_inter[2][0] = i_para_n[3] + (2 * N_inter) + 1;
  i_inter[2][1] = i_para_n[3] + (3 * N_inter);
  i_inter[3][0] = i_para_n[3] + (3 * N_inter) + 1;
  i_inter[3][1] = i_para_n[3] + (4 * N_inter);
  i_inter[4][0] = i_para_n[3] + (4 * N_inter) + 1;
  i_inter[4][1] = i_para_n[3] + (5 * N_inter);
  i_inter[5][0] = i_para_n[3] + (5 * N_inter) + 1;
  i_inter[5][1] = i_para_n[3] + (6 * N_inter);
  i_mysa_b[0] = i_inter[5][1] + 1;
  i_mysa_b[1] = i_inter[5][1] + N_inter;
  i_mysa_b[2] = i_inter[5][1] + N_inter + 1;
  i_mysa_b[3] = i_inter[5][1] + N_inter * 2;
  i_flut_b[0] = i_mysa_b[3] + 1;
  i_flut_b[1] = i_mysa_b[3] + N_inter;
  i_flut_b[2] = i_mysa_b[3] + N_inter + 1;
  i_flut_b[3] = i_mysa_b[3] + N_inter * 2;
  i_inter_b[0][0] = i_flut_b[3] + 1;
  i_inter_b[0][1] = i_flut_b[3] + N_inter;
  i_inter_b[1][0] = i_flut_b[3] + N_inter + 1;
  i_inter_b[1][1] = i_flut_b[3] + N_inter * 2;
  i_inter_b[2][0] = i_flut_b[3] + (2 * N_inter) + 1;
  i_inter_b[2][1] = i_flut_b[3] + (3 * N_inter);
  i_inter_b[3][0] = i_flut_b[3] + (3 * N_inter) + 1;
  i_inter_b[3][1] = i_flut_b[3] + (4 * N_inter);
  i_inter_b[4][0] = i_flut_b[3] + (4 * N_inter) + 1;
  i_inter_b[4][1] = i_flut_b[3] + (5 * N_inter);
  i_inter_b[5][0] = i_flut_b[3] + (5 * N_inter) + 1;
  i_inter_b[5][1] = i_flut_b[3] + (6 * N_inter);

  // create initial conditions
  MRG_MATRIX_REAL initial_voltage(1, 1);
  initial_voltage.fill(vrest);

  MRG_MATRIX_REAL m_alpha, m_beta;
  MRG_MATRIX_REAL h_alpha, h_beta;
  MRG_MATRIX_REAL p_alpha, p_beta;
  MRG_MATRIX_REAL s_alpha, s_beta;
  m_ab(initial_voltage, m_alpha, m_beta);
  h_ab(initial_voltage, h_alpha, h_beta);
  p_ab(initial_voltage, p_alpha, p_beta);
  s_ab(initial_voltage, s_alpha, s_beta);

  MRG_MATRIX_REAL IC(arma::zeros<MRG_MATRIX_REAL>(i_inter_b[5][1] + 1, 1));
  IC.rows(i_node[0], i_node[1]).fill(vrest);
  IC.rows(i_mysa[0], i_flut[3]).fill(vrest);
  IC.rows(i_inter[0][0], i_inter[5][1]).fill(vrest);
  IC.rows(i_para_m[0], i_para_m[1]).fill((m_alpha / (m_alpha + m_beta))[0]);
  IC.rows(i_para_h[0], i_para_h[1]).fill((h_alpha / (h_alpha + h_beta))[0]);
  IC.rows(i_para_p[0], i_para_p[1]).fill((p_alpha / (p_alpha + p_beta))[0]);
  IC.rows(i_para_s[0], i_para_s[1]).fill((s_alpha / (s_alpha + s_beta))[0]);
  assert(IC.is_colvec());

  // debug
  // IC.raw_print("IC =");
  // puts("\n");
  V_stim.raw_print("V_stim =");
  puts("\n");

  N_Vector y0 = N_VNew_Serial(IC.n_rows);
  for (unsigned int i = 0; i < IC.n_rows; ++i) {
    NV_DATA_S(y0)[i] = IC(i, 0);
  }

  void * cv_ode_mem = CVodeCreate(CV_BDF);
  CVodeInit(cv_ode_mem, odeCVode, 0, y0);
  CVodeSStolerances(cv_ode_mem, 1e-3f, 1e-4f);
  CVodeSetUserData(cv_ode_mem, this);
  SUNMatrix A = SUNDenseMatrix(IC.n_rows, IC.n_rows);
  SUNLinearSolver LS = SUNDenseLinearSolver(y0, A);
  int ret = CVDlsSetLinearSolver(cv_ode_mem, LS, A);
  assert(ret == CVLS_SUCCESS);

  Istim.zeros(N_nodes, 1);

  const MRG_REAL dtout = period / time_steps;
  if (cache_on) {
    m_cache.resize(time_steps);
  }
  {
    RingBuffer<MRG_MATRIX_REAL>::pointer Y = m_data_buffer.get_write_pointer();
    Y->set_size(N_nodes, 1);
    *Y = IC(0, 0, size(*Y));
  }

  MRG_REAL tout = dtout;
  for (uint64_t i = 1; true; ++i) {
    realtype t1 = tout;
    N_Vector Y1 = y0;

    const uint64_t period_number = i / time_steps;
    const uint64_t period_location = i % time_steps;
    if (!cache_on || period_number <= REFERENCE_PERIOD) {
      CVode(cv_ode_mem, tout, Y1, &t1, CV_NORMAL);
    }

    // debug
    const MRG_MATRIX_REAL & V_e = get_Ve(t1);
    printf("Timestep %lu: t = %e (%e) ms, V_e = %e mV\n", i, tout, t1, V_e(N_nodes / 2, 0));

    bool use_cache = false;
    if (cache_on) {
      if (period_number == REFERENCE_PERIOD) {
        MRG_MATRIX_REAL & cache = m_cache.at(period_location);
        cache.set_size(N_nodes, 1);
        for (int j = 0; j < N_nodes; ++j) {
          cache(j, 0) = NV_DATA_S(Y1)[j];
        }
      }
      use_cache = (period_number >= REFERENCE_PERIOD);
    }

    RingBuffer<MRG_MATRIX_REAL>::pointer Y = m_data_buffer.get_write_pointer();
    Y->set_size(N_nodes, 1);
    if (use_cache) {
      *Y = m_cache[period_location];
    } else {
      for (int j = 0; j < N_nodes; ++j) {
        (*Y)(j, 0) = NV_DATA_S(Y1)[j];
      }
    }

    tout += dtout;
  }

  CVodeFree(&cv_ode_mem);
  SUNLinSolFree(LS);
  SUNMatDestroy(A);
}


const MRG_MATRIX_REAL & MRG::get_Ve(MRG_REAL t) const
{
  static const MRG_MATRIX_REAL V_nostim = arma::zeros<MRG_MATRIX_REAL>(i_inter[5][1] + 1, 1);
  MRG_REAL period_t = fmod(t, m_period);
  return (period_t >= m_stim_start && period_t <= m_stim_end) ? V_stim : V_nostim;
}


const MRG_MATRIX_REAL & MRG::get_Xlr(MRG_REAL t) const
{
  static const MRG_MATRIX_REAL Xlr_nostim = arma::zeros<MRG_MATRIX_REAL>(2, 1);
  MRG_REAL period_t = fmod(t, m_period);
  return (period_t >= m_stim_start && period_t <= m_stim_end) ? Xlr_stim : Xlr_nostim;
}


// should return 0 if successful, a positive value if a recoverable error occurred
// (in which case cvode will attempt to correct), or a negative value if it failed
// unrecoverably (in which case the integration is halted and CV RHSFUNC FAIL is returned).
int MRG::odeMcIntyr(realtype t, N_Vector y, N_Vector ydot) const
{
  assert(NV_DATA_S(y) != NV_DATA_S(ydot));
  assert(NV_LENGTH_S(y) == NV_LENGTH_S(ydot));

  MRG_MATRIX_REAL Y(NV_DATA_S(y), NV_LENGTH_S(y), 1, false);

  const MRG_MATRIX_REAL & V_e = get_Ve(t);
  Xlr = get_Xlr(t);

  MRG_MATRIX_REAL inter(arma::zeros<MRG_MATRIX_REAL>(N_inter, 6));
  MRG_MATRIX_REAL inter_b(arma::zeros<MRG_MATRIX_REAL>(N_inter, 6));
  int N_nodes = N_inter + 1;

  // V^i
  MRG_MATRIX_REAL node(Y.rows(i_node[0], i_node[1]));
  MRG_MATRIX_REAL para_m(Y.rows(i_para_m[0], i_para_m[1]));
  MRG_MATRIX_REAL para_h(Y.rows(i_para_h[0], i_para_h[1]));
  MRG_MATRIX_REAL para_p(Y.rows(i_para_p[0], i_para_p[1]));
  MRG_MATRIX_REAL para_s(Y.rows(i_para_s[0], i_para_s[1]));
  MRG_MATRIX_REAL mysa_l(Y.rows(i_mysa[0], i_mysa[1]));
  MRG_MATRIX_REAL mysa_r(Y.rows(i_mysa[2], i_mysa[3]));
  MRG_MATRIX_REAL flut_l(Y.rows(i_flut[0], i_flut[1]));
  MRG_MATRIX_REAL flut_r(Y.rows(i_flut[2], i_flut[3]));
  // MRG_MATRIX_REAL para_n_l(Y.rows(i_para_n[0], i_para_n[1]));
  // MRG_MATRIX_REAL para_n_r(Y.rows(i_para_n[2], i_para_n[3]));
  inter.col(0) = Y.rows(i_inter[0][0], i_inter[0][1]);
  inter.col(1) = Y.rows(i_inter[1][0], i_inter[1][1]);
  inter.col(2) = Y.rows(i_inter[2][0], i_inter[2][1]);
  inter.col(3) = Y.rows(i_inter[3][0], i_inter[3][1]);
  inter.col(4) = Y.rows(i_inter[4][0], i_inter[4][1]);
  inter.col(5) = Y.rows(i_inter[5][0], i_inter[5][1]);

  // V^p
  MRG_MATRIX_REAL mysa_l_b(Y.rows(i_mysa_b[0], i_mysa_b[1]));
  MRG_MATRIX_REAL mysa_r_b(Y.rows(i_mysa_b[2], i_mysa_b[3]));
  MRG_MATRIX_REAL flut_l_b(Y.rows(i_flut_b[0], i_flut_b[1]));
  MRG_MATRIX_REAL flut_r_b(Y.rows(i_flut_b[2], i_flut_b[3]));
  inter_b.col(0) = Y.rows(i_inter_b[0][0], i_inter_b[0][1]);
  inter_b.col(1) = Y.rows(i_inter_b[1][0], i_inter_b[1][1]);
  inter_b.col(2) = Y.rows(i_inter_b[2][0], i_inter_b[2][1]);
  inter_b.col(3) = Y.rows(i_inter_b[3][0], i_inter_b[3][1]);
  inter_b.col(4) = Y.rows(i_inter_b[4][0], i_inter_b[4][1]);
  inter_b.col(5) = Y.rows(i_inter_b[5][0], i_inter_b[5][1]);

  // if E^e is assumed to be constant d(V^p) equals d(E^p)
  // these variables look like useless copies
  // MRG_MATRIX_REAL mysa_l_b_e(mysa_l_b);
  // MRG_MATRIX_REAL mysa_r_b_e(mysa_r_b);
  // MRG_MATRIX_REAL flut_l_b_e(flut_l_b);
  // MRG_MATRIX_REAL flut_r_b_e(flut_r_b);
  // MRG_MATRIX_REAL inter_b_e(inter_b);
  // MRG_MATRIX_REAL node_e(node);

  // E^i
  MRG_MATRIX_REAL mysa_l_e(mysa_l + mysa_l_b);  // MRG_MATRIX_REAL mysa_l_e(mysa_l + mysa_l_b_e);
  MRG_MATRIX_REAL mysa_r_e(mysa_r + mysa_r_b);  // MRG_MATRIX_REAL mysa_r_e(mysa_r + mysa_r_b_e);
  MRG_MATRIX_REAL flut_l_e(flut_l + flut_l_b);  // MRG_MATRIX_REAL flut_l_e(flut_l + flut_l_b_e);
  MRG_MATRIX_REAL flut_r_e(flut_r + flut_r_b);  // MRG_MATRIX_REAL flut_r_e(flut_r + flut_r_b_e);
  MRG_MATRIX_REAL inter_e(inter + inter_b);     // MRG_MATRIX_REAL inter_e(inter + inter_b_e);

  MRG_MATRIX_REAL dnode, dpara_m, dpara_h, dpara_p, dpara_s;
  // nodeEq(node, para_m, para_h, para_p, para_s, node_e, mysa_l_e, mysa_r_e,
  //        V_e.rows(i_node[0], i_node[1]), V_e.rows(i_mysa[0], i_mysa[1]),
  //        V_e.rows(i_mysa[2],i_mysa[3]), dnode, dpara_m, dpara_h, dpara_p, dpara_s);
  nodeEq(node, para_m, para_h, para_p, para_s, node, mysa_l_e, mysa_r_e,
         V_e.rows(i_node[0], i_node[1]), V_e.rows(i_mysa[0], i_mysa[1]),
         V_e.rows(i_mysa[2], i_mysa[3]), dnode, dpara_m, dpara_h, dpara_p, dpara_s);

  MRG_MATRIX_REAL dmysa_l, dmysa_l_b;
  // mysaEq(mysa_l, mysa_l_b, mysa_l_e, node_e.rows(1, N_nodes-1), flut_l_e,
  //        mysa_l_b_e, 0, flut_l_b_e, V_e.rows(i_mysa[0], i_mysa[1]),
  //        V_e.rows(1, N_nodes-1), V_e.rows(i_flut[0], i_flut[1]),
  //        dmysa_l, dmysa_l_b);
  mysaEq(mysa_l, mysa_l_b, mysa_l_e, node.rows(1, N_nodes - 1), flut_l_e, mysa_l_b,
         arma::zeros<MRG_MATRIX_REAL>(mysa_l_e.n_rows, 1), flut_l_b,
         V_e.rows(i_mysa[0], i_mysa[1]), V_e.rows(1, N_nodes - 1),
         V_e.rows(i_flut[0], i_flut[1]), dmysa_l, dmysa_l_b);

  MRG_MATRIX_REAL dmysa_r, dmysa_r_b;
  // mysaEq(mysa_r, mysa_r_b, mysa_r_e, node_e.rows(0, N_inter-1), flut_r_e,
  //        mysa_r_b_e, 0, flut_r_b_e, V_e.rows(i_mysa[2], i_mysa[3]),
  //        V_e.rows(0, N_inter-1), V_e.rows(i_flut[2], i_flut[3]),
  //        dmysa_r, dmysa_r_b);
  mysaEq(mysa_r, mysa_r_b, mysa_r_e, node.rows(0, N_inter - 1), flut_r_e, mysa_r_b,
         arma::zeros<MRG_MATRIX_REAL>(mysa_r_e.n_rows, 1), flut_r_b,
         V_e.rows(i_mysa[2], i_mysa[3]), V_e.rows(0, N_inter - 1),
         V_e.rows(i_flut[2], i_flut[3]), dmysa_r, dmysa_r_b);

  MRG_MATRIX_REAL dflut_l, dflut_l_b;
  // flutEq(flut_l, flut_l_b, flut_l_e, mysa_l_e, inter_e.col(0), flut_l_b_e, mysa_l_b_e,
  //        inter_b_e.col(0), V_e.rows(i_flut[0], i_flut[1]), V_e.rows(i_mysa[0], i_mysa[1]),
  //        V_e.rows(i_inter[0][0], i_inter[0][1]), dflut_l, dflut_l_b);
  flutEq(flut_l, flut_l_b, flut_l_e, mysa_l_e, inter_e.col(0), flut_l_e, mysa_l_e,
         inter_e.col(0), V_e.rows(i_flut[0], i_flut[1]), V_e.rows(i_mysa[0], i_mysa[1]),
         V_e.rows(i_inter[0][0], i_inter[0][1]), dflut_l, dflut_l_b);

  MRG_MATRIX_REAL dflut_r, dflut_r_b;
  // flutEq(flut_r, flut_r_b, flut_r_e, mysa_r_e, inter_e.col(5), flut_r_b_e, mysa_r_b_e,
  //        inter_b_e.col(6), V_e.rows(i_flut[2], i_flut[3]), V_e.rows(i_mysa[2], i_mysa[3]),
  //        V_e.rows(i_inter[5][0], i_inter[5][1]), dflut_r, dflut_r_b);
  flutEq(flut_r, flut_r_b, flut_r_e, mysa_r_e, inter_e.col(5), flut_r_e, mysa_r_e,
         inter_e.col(5), V_e.rows(i_flut[2], i_flut[3]), V_e.rows(i_mysa[2], i_mysa[3]),
         V_e.rows(i_inter[5][0], i_inter[5][1]), dflut_r, dflut_r_b);

  MRG_MATRIX_REAL dpara_n_l(arma::zeros<MRG_MATRIX_REAL>(N_inter, 1));
  MRG_MATRIX_REAL dpara_n_r(arma::zeros<MRG_MATRIX_REAL>(N_inter, 1));

  MRG_MATRIX_REAL e_inter(arma::zeros<MRG_MATRIX_REAL>(N_inter, 6));
  e_inter.col(0) = V_e.rows(i_inter[0][0], i_inter[0][1]);
  e_inter.col(1) = V_e.rows(i_inter[1][0], i_inter[1][1]);
  e_inter.col(2) = V_e.rows(i_inter[2][0], i_inter[2][1]);
  e_inter.col(3) = V_e.rows(i_inter[3][0], i_inter[3][1]);
  e_inter.col(4) = V_e.rows(i_inter[4][0], i_inter[4][1]);
  e_inter.col(5) = V_e.rows(i_inter[5][0], i_inter[5][1]);

  MRG_MATRIX_REAL dinter, dinter_b;
  // interEq(inter, inter_b, inter_e, flut_l_e, flut_r_e, inter_b_e, flut_l_b_e,
  //         flut_r_b_e, e_inter, V_e.rows(i_flut[0], i_flut[1]), V_e.rows(i_flut[2], i_flut[2]),
  //         dinter, dinter_b);
  interEq(inter, inter_b, inter_e, flut_l_e, flut_r_e, inter_e, flut_l_e, flut_r_e,
          e_inter, V_e.rows(i_flut[0], i_flut[1]), V_e.rows(i_flut[2], i_flut[3]),
          dinter, dinter_b);

  // finally assemble derivatives into an
  MRG_MATRIX_REAL dY(NV_DATA_S(ydot), NV_LENGTH_S(ydot), 1, false);
  dY.rows(i_node[0], i_node[1]) = dnode;
  dY.rows(i_para_m[0], i_para_m[1]) = dpara_m;
  dY.rows(i_para_h[0], i_para_h[1]) = dpara_h;
  dY.rows(i_para_p[0], i_para_p[1]) = dpara_p;
  dY.rows(i_para_s[0], i_para_s[1]) = dpara_s;
  dY.rows(i_mysa[0], i_mysa[1]) = dmysa_l;
  dY.rows(i_mysa[2], i_mysa[3]) = dmysa_r;
  dY.rows(i_flut[0], i_flut[1]) = dflut_l;
  dY.rows(i_flut[2], i_flut[3]) = dflut_r;
  dY.rows(i_para_n[0], i_para_n[1]) = dpara_n_l;
  dY.rows(i_para_n[2], i_para_n[3]) = dpara_n_r;
  dY.rows(i_inter[0][0], i_inter[0][1]) = dinter.col(0);
  dY.rows(i_inter[1][0], i_inter[1][1]) = dinter.col(1);
  dY.rows(i_inter[2][0], i_inter[2][1]) = dinter.col(2);
  dY.rows(i_inter[3][0], i_inter[3][1]) = dinter.col(3);
  dY.rows(i_inter[4][0], i_inter[4][1]) = dinter.col(4);
  dY.rows(i_inter[5][0], i_inter[5][1]) = dinter.col(5);
  dY.rows(i_mysa_b[0], i_mysa_b[1]) = dmysa_l_b;
  dY.rows(i_mysa_b[2], i_mysa_b[3]) = dmysa_r_b;
  dY.rows(i_flut_b[0], i_flut_b[1]) = dflut_l_b;
  dY.rows(i_flut_b[2], i_flut_b[3]) = dflut_r_b;
  dY.rows(i_inter_b[0][0], i_inter_b[0][1]) = dinter_b.col(0);
  dY.rows(i_inter_b[1][0], i_inter_b[1][1]) = dinter_b.col(1);
  dY.rows(i_inter_b[2][0], i_inter_b[2][1]) = dinter_b.col(2);
  dY.rows(i_inter_b[3][0], i_inter_b[3][1]) = dinter_b.col(3);
  dY.rows(i_inter_b[4][0], i_inter_b[4][1]) = dinter_b.col(4);
  dY.rows(i_inter_b[5][0], i_inter_b[5][1]) = dinter_b.col(5);

  // debug
  // if (t > 1) {
  //   printf("At t = %f\n", t);
  //   Y.raw_print("Y =");
  //   dY.raw_print("dY =");
  //   puts("\n");
  // }

  return 0; // successful
}


void MRG::nodeEq
(
  const MRG_MATRIX_REAL & V,
  const MRG_MATRIX_REAL & m,
  const MRG_MATRIX_REAL & h,
  const MRG_MATRIX_REAL & p,
  const MRG_MATRIX_REAL & s,
  const MRG_MATRIX_REAL & Ei,
  const MRG_MATRIX_REAL & EiMl,
  const MRG_MATRIX_REAL & EiMr,
  const MRG_MATRIX_REAL & Vex,
  const MRG_MATRIX_REAL & VexMl,
  const MRG_MATRIX_REAL & VexMr,
  MRG_MATRIX_REAL & dV,
  MRG_MATRIX_REAL & dm,
  MRG_MATRIX_REAL & dh,
  MRG_MATRIX_REAL & dp,
  MRG_MATRIX_REAL & ds
) const
{
  MRG_MATRIX_REAL I;
  MRG_MATRIX_REAL V1, V2;
  MRG_MATRIX_REAL Iax, Iex;

  axnode2(V, m, h, p, s, I, dm, dh, dp, ds);

  V1 = EiMl;
  V1.insert_rows(0, 1);
  V1(0, 0) = vrest;
  V2 = EiMr;
  V2.insert_rows(EiMr.n_rows, 1);
  V2(EiMr.n_rows, 0) = vrest;
  axialI(Ei, V1, V2, r_node, r_mysa, r_mysa, Iax);

  V1 = VexMl;
  V1.insert_rows(0, 1);
  V1(0, 0) = Xlr(0, 0);
  V2 = VexMr;
  V2.insert_rows(VexMr.n_rows, 1);
  V2(VexMr.n_rows, 0) = Xlr(1, 0);
  axialI(Vex, V1, V2, r_node, r_mysa, r_mysa, Iex);

  dV = (Istim - I - Iax - Iex) / c_node;
}


void MRG::mysaEq
(
  const MRG_MATRIX_REAL & V,
  const MRG_MATRIX_REAL & Vp,
  const MRG_MATRIX_REAL & Ei,
  const MRG_MATRIX_REAL & EiN,
  const MRG_MATRIX_REAL & EiF,
  const MRG_MATRIX_REAL & Ep,
  const MRG_MATRIX_REAL & EpN,
  const MRG_MATRIX_REAL & EpF,
  const MRG_MATRIX_REAL & Vex,
  const MRG_MATRIX_REAL & VexN,
  const MRG_MATRIX_REAL & VexF,
  MRG_MATRIX_REAL & dV,
  MRG_MATRIX_REAL & dVp
) const
{
  MRG_MATRIX_REAL Iax, Ipx, Iex;
  axialI(Ei, EiN, EiF, r_mysa, r_node, r_flut, Iax);
  axialI(Ep, EpN, EpF, r_pn1, r_pn0, r_pn2, Ipx);
  axialI(Vex, VexN, VexF, r_mysa, r_node, r_flut, Iex);
  compartment(V, Vp, Iax, Ipx, Iex, vrest, c_mysa, c_mysa_m, g_mysa, g_mysa_m, dV, dVp);
}


void MRG::flutEq
(
  const MRG_MATRIX_REAL & V,
  const MRG_MATRIX_REAL & Vp,
  const MRG_MATRIX_REAL & Ei,
  const MRG_MATRIX_REAL & EiM,
  const MRG_MATRIX_REAL & EiI,
  const MRG_MATRIX_REAL & Ep,
  const MRG_MATRIX_REAL & EpM,
  const MRG_MATRIX_REAL & EpI,
  const MRG_MATRIX_REAL & Vex,
  const MRG_MATRIX_REAL & VexM,
  const MRG_MATRIX_REAL & VexI,
  MRG_MATRIX_REAL & dV,
  MRG_MATRIX_REAL & dVp
) const
{
  MRG_MATRIX_REAL Iax, Ipx, Iex;
  axialI(Ei, EiM, EiI, r_flut, r_mysa, r_inter, Iax);
  axialI(Ep, EpM, EpI, r_pn2, r_pn1, r_px, Ipx);
  axialI(Vex, VexM, VexI, r_flut, r_mysa, r_inter, Iex);
  compartment(V, Vp, Iax, Ipx, Iex, vrest, c_flut, c_flut_m, g_flut, g_flut_m, dV, dVp);
}


void MRG::interEq
(
  const MRG_MATRIX_REAL & V,
  const MRG_MATRIX_REAL & Vp,
  const MRG_MATRIX_REAL & Ei,
  const MRG_MATRIX_REAL & EiFl,
  const MRG_MATRIX_REAL & EiFr,
  const MRG_MATRIX_REAL & Ep,
  const MRG_MATRIX_REAL & EpFl,
  const MRG_MATRIX_REAL & EpFr,
  const MRG_MATRIX_REAL & Vex,
  const MRG_MATRIX_REAL & VexFl,
  const MRG_MATRIX_REAL & VexFr,
  MRG_MATRIX_REAL & dV,
  MRG_MATRIX_REAL & dVp
) const
{
  dV = arma::zeros<MRG_MATRIX_REAL>(N_inter, 6);
  dVp = arma::zeros<MRG_MATRIX_REAL>(N_inter, 6);

  MRG_MATRIX_REAL Iax, Ipx, Iex;
  MRG_MATRIX_REAL dV_result, dVp_result;

  axialI(Ei.col(0), EiFl, Ei.col(1), r_inter, r_flut, r_inter, Iax);
  axialI(Ep.col(0), EpFl, Ep.col(1), r_px, r_pn2, r_px, Ipx);
  axialI(Vex.col(0), VexFl, Vex.col(1), r_inter, r_flut, r_inter, Iex);
  compartment(V.col(0), Vp.col(0), Iax, Ipx, Iex, vrest, c_inter, c_inter_m,
              g_inter, g_inter_m, dV_result, dVp_result);
  dV.col(0) = dV_result;
  dVp.col(0) = dVp_result;

  axialI(Ei.col(5), EiFr, Ei.col(4), r_inter, r_flut, r_inter, Iax);
  axialI(Ep.col(5), EpFr, Ep.col(4), r_px, r_pn2, r_px, Ipx);
  axialI(Vex.col(5), VexFr, Vex.col(4), r_inter, r_flut, r_inter, Iex);
  compartment(V.col(5), Vp.col(5), Iax, Ipx, Iex, vrest, c_inter, c_inter_m,
              g_inter, g_inter_m, dV_result, dVp_result);
  dV.col(5) = dV_result;
  dVp.col(5) = dVp_result;

  for (int j = 1; j <= 4; ++j) {
    axialI(Ei.col(j), Ei.col(j - 1), Ei.col(j + 1), r_inter, r_inter, r_inter, Iax);
    axialI(Ep.col(j), Ep.col(j - 1), Ep.col(j + 1), r_px, r_px, r_px, Ipx);
    axialI(Vex.col(j), Vex.col(j - 1), Vex.col(j + 1), r_inter, r_inter, r_inter, Iex);
    compartment(V.col(j), Vp.col(j), Iax, Ipx, Iex, vrest, c_inter, c_inter_m,
                g_inter, g_inter_m, dV_result, dVp_result);
    dV.col(j) = dV_result;
    dVp.col(j) = dVp_result;
  }
}


void MRG::axialI
(
  const MRG_MATRIX_REAL & V,
  const MRG_MATRIX_REAL & V1,
  const MRG_MATRIX_REAL & V2,
  const MRG_REAL r,
  const MRG_REAL r1,
  const MRG_REAL r2,
  MRG_MATRIX_REAL & I
) const
{
  I = (V - V1) / (r / 2 + r1 / 2) + (V - V2) / (r / 2 + r2 / 2);
}


void MRG::compartment
(
  const MRG_MATRIX_REAL & V,
  const MRG_MATRIX_REAL & Vp,
  const MRG_MATRIX_REAL & Iaxonal,
  const MRG_MATRIX_REAL & Iperiaxonal,
  const MRG_MATRIX_REAL & Iex,
  const MRG_REAL epas,
  const MRG_REAL cmem,
  const MRG_REAL cmy,
  const MRG_REAL gmem,
  const MRG_REAL gmy,
  MRG_MATRIX_REAL & dV,
  MRG_MATRIX_REAL & dVp
) const
{
  MRG_MATRIX_REAL IPas = gmem * (V - epas);
  MRG_MATRIX_REAL Imyelin = gmy * Vp;
  MRG_MATRIX_REAL ICmem = -IPas - Iaxonal - Iex;
  MRG_MATRIX_REAL ICmyelin = -Imyelin - Iperiaxonal - Iaxonal - Iex;

  dV = ICmem / cmem;
  dVp = ICmyelin / cmy;
}


void MRG::axnode2
(
  const MRG_MATRIX_REAL & V,
  const MRG_MATRIX_REAL & m,
  const MRG_MATRIX_REAL & h,
  const MRG_MATRIX_REAL & p,
  const MRG_MATRIX_REAL & s,
  MRG_MATRIX_REAL & I,
  MRG_MATRIX_REAL & dm,
  MRG_MATRIX_REAL & dh,
  MRG_MATRIX_REAL & dp,
  MRG_MATRIX_REAL & ds
) const
{
  MRG_MATRIX_REAL m_alpha, m_beta;
  MRG_MATRIX_REAL h_alpha, h_beta;
  MRG_MATRIX_REAL p_alpha, p_beta;
  MRG_MATRIX_REAL s_alpha, s_beta;
  m_ab(V, m_alpha, m_beta);
  h_ab(V, h_alpha, h_beta);
  p_ab(V, p_alpha, p_beta);
  s_ab(V, s_alpha, s_beta);

  // first derivatives of m, h, p, s
  dpdt(m_alpha, m_beta, m, dm);
  dpdt(h_alpha, h_beta, h, dh);
  dpdt(p_alpha, p_beta, p, dp);
  dpdt(s_alpha, s_beta, s, ds);

  MRG_MATRIX_REAL I_Naf = g_naf * (m % m % m) % h % (V - e_na); // Fast Sodium current
  MRG_MATRIX_REAL I_Nap = g_nap * (p % p % p) % (V - e_na);     // Persistent Sodium current
  MRG_MATRIX_REAL I_Ks = g_k * s % (V - e_k);                   // Slow Potassium current
  MRG_MATRIX_REAL I_Lk = g_l * (V - e_l);                       // Leakage current
  I = I_Naf + I_Nap + I_Ks + I_Lk;                              // Sum of all nodal currents
}


// dpdt: calculates the derivative of the of the parameter according to
//       alpha, beta and the previous value
void MRG::dpdt
(
  const MRG_MATRIX_REAL & alpha,
  const MRG_MATRIX_REAL & beta,
  const MRG_MATRIX_REAL & para,
  MRG_MATRIX_REAL & dp
) const
{
  dp = alpha % (1 - para) - beta % para;
}
