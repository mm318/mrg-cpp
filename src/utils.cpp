#include <assert.h>
#include "utils.h"


const MRG_REAL rtNaN = arma::datum::nan;


#if 1

// taken from http://berenger.eu/blog/c-from-matlab-to-c-some-useful-functions/
/** To inter-pole data */
void MRG_interp1(const MRG_MATRIX_REAL &x, const MRG_MATRIX_REAL &y, const MRG_MATRIX_REAL &xi, MRG_MATRIX_REAL &yi)
{
	// expect that x, y, and xi are all column vectors
	assert(x.is_colvec() && y.is_colvec() && xi.is_colvec());
	assert(x.n_rows >= 2 && y.n_rows >= 2 && xi.n_rows >= 2);
	yi.set_size(xi.n_rows, xi.n_cols);

	// indexes
	int sizex = x.n_rows;
	int sizexi = xi.n_rows;
	int idyi = 0;
	int idx = 0;

	// After computing, to know the current step progress
	double steps = (y[1] - y[0]) / (x[1] - x[0]);
 
	// fill left points
	while(idyi < sizexi - 1 && xi[idyi] < x[0])
	{
		yi[idyi] = y[0] - (steps * (x[0] - xi[idyi]) );
		++idyi;
	}
 
	// fill point in the same interval as the original values
	while(idyi < sizexi && idx < sizex)
	{
		while(idx < sizex && xi[idyi] >= x[idx])
		{
			++idx;
		}

		if(idx != sizex)
		{
			steps = (y[idx] - y[idx-1]) / (x[idx] - x[idx-1]);
			yi[idyi] = y[idx] - (steps * (x[idx] - xi[idyi]) ) ;
			++idyi;
		}
	}
 
	// fill the right points
	if(idyi < sizexi)
	{
		steps = (y[sizex-1] - y[sizex-2]) / (x[sizex-1] - x[sizex-2]);

		while(idyi < sizexi)
		{
			yi[idyi] = y[sizex-1] + (steps * (xi[idyi] - x[sizex-1])) ;
			++idyi;
		}
	}
}

#else

int findNearestNeighbourIndex(MRG_REAL value, const MRG_MATRIX_REAL &x)
{
	MRG_REAL dist = std::numeric_limits<MRG_REAL>::max();

	int idx = -1;
	for(unsigned int i = 0; i < x.n_rows; ++i)
	{
		MRG_REAL newDist = abs(value - x[i]);
		if(newDist < dist)
		{
			dist = newDist;
			idx = i;
		}
	}

	return idx;
}


// taken from http://stackoverflow.com/questions/9394867/c-implementation-of-matlab-interp1-function-linear-interpolation
void MRG_interp1(const MRG_MATRIX_REAL &x, const MRG_MATRIX_REAL &y, const MRG_MATRIX_REAL &xi, MRG_MATRIX_REAL &yi)
{
	// expect that x, y, and xi are all column vectors
	assert(x.is_colvec() && y.is_colvec() && xi.is_colvec());
	assert(x.n_rows >= 2 && y.n_rows >= 2 && xi.n_rows >= 2);
	yi.set_size(xi.n_rows, xi.n_cols);

	int x_tam = x.n_rows;
	int xx_tam = xi.n_rows;

	int i;
	double *dx, *dy, *slope, *intercept;

	dx = (double*) calloc(x_tam, sizeof(double));
	dy = (double*) calloc(x_tam, sizeof(double));
	slope = (double*) calloc(x_tam, sizeof(double));
	intercept = (double*) calloc(x_tam, sizeof(double));

	for(i = 0; i < x_tam; ++i)
	{
		if(i < x_tam-1)
		{
			dx[i] = x[i + 1] - x[i];
			dy[i] = y[i + 1] - y[i];
			slope[i] = dy[i] / dx[i];
			intercept[i] = y[i] - x[i]*slope[i];
		}
		else
		{
			dx[i] = dx[i-1];
			dy[i] = dy[i-1];
			slope[i] = slope[i-1];
			intercept[i] = intercept[i-1];
		}
	}

	for(i = 0; i < xx_tam; i++)
	{
		int idx = findNearestNeighbourIndex(xi[i], x);
		yi[i] = slope[idx] * xi[i] + intercept[idx];
	}
}

#endif


// void MRG_interp1(const MRG_MATRIX_REAL &x, const MRG_MATRIX_REAL &y, const MRG_MATRIX_REAL &xi, MRG_MATRIX_REAL &yi)
// {
// 	// expect that x, y, and xi are all column vectors
// 	assert(x.is_colvec() && y.is_colvec() && xi.is_colvec());
// 	assert(x.n_rows >= 2 && y.n_rows >= 2 && xi.n_rows >= 2);
// 	yi.set_size(xi.n_rows, xi.n_cols);

// 	int outsize_idx_0 = xi.n_rows;
// 	int ixleft = yi.n_rows;
// 	int ixright = outsize_idx_0;
// 	bool exitg1 = false;
// 	MRG_REAL c_r;

// 	for(ixleft = 0; ixleft < ixright; ++ixleft)
// 	{
// 		yi(ixleft, 0) = rtNaN;
// 	}

// 	ixleft = 1;
// 	while(!exitg1)
// 	{
// 		if (ixleft <= 1)
// 		{
// 			if(!arma::arma_isfinite(x(0, 0)))
// 			{
// 				exitg1 = true;
// 			}
// 			else
// 			{
// 				ixleft = 2;
// 			}
// 		}
// 		else
// 		{
// 			bool reverse = x(1, 0) < x(0, 0);
// 			const MRG_MATRIX_REAL &effective_y = reverse ? arma::flipud(y) : y;

// 			for(ixleft = 0; ixleft < outsize_idx_0; ixleft++)
// 			{
// 				if(xi(ixleft, 0) > x(0, 0))
// 				{
// 				}
// 				else if(xi(ixleft, 0) < x(0, 0))
// 				{
// 					c_r = (xi(ixleft, 0) - x(0, 0)) / (x(1, 0) - x(0, 0));
// 					yi(ixleft, 0) = effective_y[0] + c_r * (effective_y[1] - effective_y[0]);
// 				}
// 				else
// 				{
// 					c_r = (xi(ixleft, 0) - x(0, 0)) / (x(1, 0) - x(0, 0));
// 					if(effective_y[0] == effective_y[1])
// 					{
// 						yi(ixleft, 0) = effective_y[0];
// 					}
// 					else
// 					{
// 						yi(ixleft, 0) = (1.0 - c_r) * effective_y[0] + c_r * effective_y[1];
// 					}
// 				}
// 			}

// 			exitg1 = true;
// 		}
// 	}
// }

