#include <iostream>
#include <fstream>
#include <math.h>		/* pow */
//#include "cpgplot.h"

using namespace std;

int main ()
{
  //cout << "Hello World";
  int n = 3;			//number of objects
  //float m[] = {1E+9, 50};	//in kg
  float m[] = {10000, 50};
  int steps = 1000;		//number of time steps
  float delta = 0.1;		//seconds per step

  float sf = 1; //gravitational force scaling factor

  float G = sf*6.67E-11;		//m3/kg.s2

  float initialXPos[] = { 0, 30};	//in meters
  float initialYPos[] = { 0, 0};	//should match n, (meters)

  float initialXVel[] = { 0, 0};	//in m/s
  float initialYVel[] = { 0, 20};	//should match n, 

  float r[steps][2][n];
  float v[steps][2][n];

  float rkj;			//distance between two bodies k and j

  ofstream myfile;
  myfile.open ("results.txt");
  
  cout.precision(4); 

  for (int i = 0; i < n; i++)
    {
      r[0][0][i] = initialXPos[i];
      //cout << i;
      //cout << initialXPos[i];
      r[0][1][i] = initialYPos[i];
    }
  
  for (int i = 0; i < n; i++)
    {
      v[0][0][i] = initialXVel[i];
      v[0][1][i] = initialYVel[i];
    }

  for (int i = 0; i < steps; i++)
    {
    myfile << i << "     ";
      for (int j = 0; j < n; j++)
        {
          float Ax = 0;	//x-acceleration of body (j)
          float Ay = 0;
          for (int k = 0; k < n; k++)
            {
              if (k != j)
                {
                  
                  rkj =
                    sqrt (pow ((r[i][0][k] - r[i][0][j]), 2) +
                    pow ((r[i][1][k] - r[i][1][j]), 2));
                  
                  Ax = Ax + G * m[k] * (r[i][0][k] - r[i][0][j]) / rkj;
                  Ay = Ay + G * m[k] * (r[i][1][k] - r[i][1][j]) / rkj;

                }
            }

          v[i + 1][0][j] = v[i][0][j] + Ax * delta;
          v[i + 1][1][j] = v[i][1][j] + Ay * delta;


          r[i + 1][0][j] = r[i][0][j] + v[i + 1][0][j] * delta;
          r[i + 1][1][j] = r[i][1][j] + v[i + 1][1][j] * delta;
             
          //myfile << "Writing this to a file.\n";
          myfile << r[i][0][j] << "     " << r[i][1][j] << "     " ;
        }
    myfile << " \n";
    }

  myfile.close();

  return 0;
}
