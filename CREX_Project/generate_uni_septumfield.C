#include <iostream>
#include <fstream>
#include <math.h>
using namespace std;

int main(){

  ofstream OUTFILE;
  OUTFILE.open("uni_septumfield.dat");

  float x_min = -40.0; // cm
  float x_max =  40.0; // cm
  float x_step=   2.0; // cm
  int   x_bins= ( x_max - x_min ) / x_step + 1;
  float y_min = - 14.0; // cm
  float y_max =   14.0; // cm
  float y_step=   2.0; // cm
  int   y_bins= ( y_max - y_min ) / y_step + 1;
  float z_min =- 100.0; // cm
  float z_max =  100.0; // cm
  float z_step=   4.0; // cm
  int   z_bins= ( z_max - z_min ) / z_step + 1;

  float q     = 1.602; // C - need 10^-19
  float l     = 1.;   // m
  //float l     = 0.16;   // m
  float p     = 2200000000.; // eV
  float pi    = 3.14159265358979;
  float theta1= 4.0 * pi / 180.0;
  float theta2=12.5 * pi / 180.0;
  float delta = theta2 - theta1;
  float eps0  = 8.854187817 * 0.000000000001;
  float gauss = sqrt( 4 * pi * eps0);
  float rho   = 2 * l / ( cos( theta1 ) + cos( theta2 ) ) / sqrt( 2 - 2 * cos( delta / 2 ) );

  OUTFILE << "           169          39         101           1" << endl
       << " 1 x [LENGU]" << endl
       << " 2 y [LENGU]" << endl 
       << " 3 z [LENGU]" << endl
       << " 4 bx [FLUXU]" << endl
       << " 5 by [FLUXU]" << endl
       << " 6 bz [FLUXU]" << endl
       << " 0     x        y        z        Bx        By        Bz" << endl;

  for ( int i = 0; i < x_bins; i++ ) {
    for ( int j = 0; j < y_bins; j++ ) {
      for ( int k = 0; k < z_bins; k++ ) {
	float B = 0.;
	//B = p / l / sin( delta ) * ( ( 1 - cos( delta ) ) * ( sin( theta1 ) * cos( delta ) - sin( theta2 ) ) - cos( theta1 ) * sin( delta ) * sin( delta ) ) / 10000. / 2.;
	//cout << B << " ";
	//B = - p / 299.8 / .0017 / delta * 1000.0 / 1000000000. / 5 / l; // Vanderbilt: B in T, r in m, E in GeV, constant is 10 / 2.998, there is a factor of beta, but it is 1
	B = - p / 2.998 / rho / 10000.; // Vanderbilt: B in T, r in m, E in GeV, constant is 10 / 2.998, there is a factor of beta, but it is 1
	//cout << B << " ";
	//B = -p * ( sin( theta2 ) - sin( theta1 ) ) / l / 10000.;
	//cout << B << " ";
	//B = p * ( cos( theta2 ) - cos( theta1 ) * cos( delta ) ) / sin( delta ) / l / 10000.0 / 2.;
	//cout << B << " ";
	//B = p * delta / l / 10000. ; // must divide by 10,000 to change units from Telsa to Gauss
	//cout << B << endl;
	//OUTFILE << x_min + i * x_step << " " << y_min + j * y_step << " " << z_min + k * z_step << " " << 0.0 << " " << 0.0 << " " << 0.0 << endl;
	//if( z_min + k * z_step < 50.){
	//if( z_min + k * z_step < l * 100. ){
	if(  fabs( x_min + i * x_step ) >  8.4 && fabs( x_min + i * x_step ) < 38.8 &&
	     fabs( y_min + j * y_step ) < 12.2 && fabs( z_min + k * z_step ) < 37.0  ){
	  //OUTFILE << x_min + i * x_step << " " << y_min + j * y_step << " " << z_min + k * z_step << " " << 0.0 << " " << -B << " " << 0.0 << endl;
	  OUTFILE << x_min + i * x_step << " " << y_min + j * y_step << " " << z_min + k * z_step << " " << 0.0 << " " << -0.485 << " " << 0.0 << endl;
	}else{
	  OUTFILE << x_min + i * x_step << " " << y_min + j * y_step << " " << z_min + k * z_step << " " << 0.0 << " " << 0 << " " << 0.0 << endl;
	}
      }
    }
  }

  OUTFILE.close();
  return 0;

}

