#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>

double* lorenzDynamics(double dt, double x, double y, double z, double* dSP);

int main() {

    // TIME SPAN
    double tStart = 0;
    double tStop = 100;
    double dt = 0.1;
    int steps = (tStop - tStart)/dt + 1;

    double* tSpan = (double*)malloc(sizeof(double)*steps);

    for(int i = 0; i < steps; i++) {
	tSpan[i] = tStart + dt*i;
    }

    // XYZ DATA
    double* xData = (double*)malloc(sizeof(double)*steps);
    double* yData = (double*)malloc(sizeof(double)*steps);
    double* zData = (double*)malloc(sizeof(double)*steps);

    xData[0] = 1;
    yData[0] = 1;
    zData[0] = 1;

    // Pointer?
    // double dS[2];
    double *dState = (double*)malloc(sizeof(double)*3);

    // OPEN FILE
    remove("lorenzData.txt");
    FILE * fid;
    fid = fopen("lorenzData.txt", "a");

    // GENERATE AND WRITE DATA
    for (int i = 1; i < steps; i++) {

	// GET NEXT STEP
	dState = lorenzDynamics(dt, xData[i-1], yData[i-1], zData[i-1], dState);
	//printf("%f\n", dSP[0]);
	//printf("%f\n", dSP[1]);
	//printf("%f\n", dSP[2]);

	//double dState[0] = *(dSP[0]);
	//double dState[1] = *(dSP[1]);
	//double dState[2] = *(dSP[2]);

	xData[i] = xData[i-1] + dt*dState[0];
	yData[i] = yData[i-1] + dt*dState[1];
	zData[i] = zData[i-1] + dt*dState[2];

	// WRITE DATA
	fprintf(fid, "%f %f %f\n", xData[i], yData[i], zData[i]);
	fflush(fid);
	//usleep(dt*1000000);
    }

    // CLOSE
    free(tSpan);
    free(xData);
    free(yData);
    free(zData);
    free(dState);
    fclose(fid);
    printf("DONE\n");

}

double* lorenzDynamics(double dt, double x, double y, double z, double* dSP) {

    double sigma = 10;
    double rho = 28;
    double beta = 8/3;

    double dState[2];

    dSP[0] = (sigma*(y-x))*dt;
    dSP[1] = (x*(rho-z)-y)*dt;
    dSP[2] = (x*y-beta*z)*dt;

    return dSP;
}
