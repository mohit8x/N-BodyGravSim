#include <iostream>
#include <fstream>
#include <cstdlib>    
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//#include "cpgplot.h"

using namespace std;

    int main ()
        {
            int n;
            cout << "Please enter the number of bodies \n";
            cin >> n;
            int TimeStep = 5000;
            float delta = 0.001;
            float G = 1; //6.67E-11; Gravitational Constant
 
            // Array for positon of a body in the x direction
            float XPosition[n]; 
            // Array for positon of a body in the y direction
            float YPosition[n]; 
            // Array for positon of a body in the z direction
            float ZPosition[n]; 
            // Array for velocity of a body in the x direction
            float XVelocity[n]; 
            // Array for velocity of a body in the y direction
            float YVelocity[n]; 
            // Array for velocity of a body in the y direction
            float ZVelocity[n]; 
            // Array for mass values of each body
            float mass[n]; // 1E+9; 
        
            //Opens a text file to print results
            ofstream myfile;
            myfile.open ("results.txt");
            cout.precision(4); 
            
            srand((unsigned) time(0));

            int CaseNumber;
            std::cout << "Please indicate the initial state of the system\n";
            std::cout << "1 for manual entries for the initial state\n";
            std::cout << "2 for automated random entries for the initial state\n";
            std::cin >> CaseNumber;

            switch (CaseNumber)
                {
                    case 1:
                        //For loop to allow user to allocate number of bodies and their respective properties
                      for (int i = 0; i < n; i++)
                            {
                                cout << "Please enter the mass of body #" << i+1 << "\n";
                                cin >> mass[i];
                                cout << "Please enter the XPosition of body #" << i+1 << "\n";
                                cin >> XPosition[i];
                                cout << "Please enter the YPosition of body #" << i+1 << "\n";
                                cin >> YPosition[i];
                                cout << "Please enter the ZPosition of body #" << i+1 << "\n";
                                cin >> ZPosition[i];
                                cout << "Please enter the XVelocity of body #" << i+1 << "\n";
                                cin >> XVelocity[i];
                                cout << "Please enter the YVelocity of body #" << i+1 << "\n";
                                cin >> YVelocity[i];
                                cout << "Please enter the ZVelocity of body #" << i+1 << "\n";
                                cin >> ZVelocity[i];
                            }
                        break;
  
                    case 2:
                        for (int i = 0; i < n; i++)
                            {
                                mass[i] = (1 + (rand()));
                                XPosition[i] = (1 + (rand() % 100));
                                YPosition[i] = (1 + (rand() % 100));
                                ZPosition[i] = (1 + (rand() % 100));
                                XVelocity[i] = ((rand() % 1));
                                YVelocity[i] = ((rand() % 1));
                                ZVelocity[i] = ((rand() % 1));
                            }
                    break;
  
                    default:
                    std::cout << CaseNumber << " is not an allowed choice\n";
                }
            

            //Position array        
            float Pos[TimeStep][3][n];
            //Velocity array        
            float Vel[TimeStep][3][n];
            // Distance between two bodies
            float DistTwoBodies;

            //Input positions assigned to a position array
            for (int i = 0; i < n; i++)
                {
                    //Assigning position in the x direction at initial time
                    Pos[0][0][i] = XPosition[i];
                    //Assigning position in the y direction at initial time
                    Pos[0][1][i] = YPosition[i];
                    //Assigning position in the z direction at initial time
                    Pos[0][2][i] = ZPosition[i];
                }
                
            //Input velocities assigned to velocity array
            for (int i = 0; i < n; i++)
                {
                    //assigning velocity in x direction at initial time
                    Vel[0][0][i] = XVelocity[i];
                    //assigning velocity in y direction at initial time
                    Vel[0][1][i] = YVelocity[i];
                    //assigning velocity in z direction at initial time
                    Vel[0][2][i] = ZVelocity[i];
                }

            //Calculations for positions and velocities for all bodies
            for (int i = 0; i < TimeStep; i++)
                {
                    myfile << i << "     ";
     
                    //Calculations of individual bodies
                    for (int j = 0; j < n; j++)
                        {
                            //Acceleration
                            float AccXDirec = 0;
                            float AccYDirec = 0;
                            float AccZDirec = 0;
          
                            //Gravitaional affects of other bodies
                            for (int k = 0; k < n; k++)
                                {
                                    if (k != j)
                                        {
                                            DistTwoBodies = sqrt (pow ((Pos[i][0][k] - Pos[i][0][j]), 2) + pow ((Pos[i][1][k] - Pos[i][1][j]), 2) + pow ((Pos[i][2][k] - Pos[i][2][j]), 2));
                                            AccXDirec = AccXDirec + G * mass[k] * (Pos[i][0][k] - Pos[i][0][j]) / DistTwoBodies;
                                            AccYDirec = AccYDirec + G * mass[k] * (Pos[i][1][k] - Pos[i][1][j]) / DistTwoBodies;
                                            AccZDirec = AccZDirec + G * mass[k] * (Pos[i][2][k] - Pos[i][2][j]) / DistTwoBodies;
                                        }
                                }
                                
                            //Based on leap frog integration)
                            //Predicted velocity in x Direction
                            Vel[i + 1][0][j] = Vel[i][0][j] + AccXDirec * delta;
                            //Predicted velocity in y Direction
                            Vel[i + 1][1][j] = Vel[i][1][j] + AccYDirec * delta;
                            //Predicted velocity in z Direction
                            Vel[i + 1][2][j] = Vel[i][2][j] + AccZDirec * delta;

                            //(leap frog integration)
                            //Predicted Position in x direction
                            Pos[i + 1][0][j] = Pos[i][0][j] + Vel[i + 1][0][j] * delta;
                            //Predicted Position in y direction
                            Pos[i + 1][1][j] = Pos[i][1][j] + Vel[i + 1][1][j] * delta;
                            //Predicted Position in z direction
                            Pos[i + 1][2][j] = Pos[i][2][j] + Vel[i + 1][2][j] * delta;
             
                            //myfile << "Writing this to a file.\n";
                            myfile << Pos[i][0][j] << "  ,   " << Pos[i][1][j] << "  ,   " << Pos[i][2][j] << "     " ;
                        
                        }
                    myfile << " \n";
                }

            myfile.close();
    
            return 0;
        }