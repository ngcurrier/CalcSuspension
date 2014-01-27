#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define pi 3.141592654

/*Function for calculating camber inherent in a-arm geometry*/
/*Does not consider camber acquired from caster*/
/*All variables passed directly without pointers*/

/*hub_height -> distance between hub attachment points*/
/*uc_length -> upper control arm length*/
/*lc_length -> lower control arm length*/
/*lc_ang -> starting angle from horiz*/
/*uc_ang -> starting angle from horiz*/
/*delta -> vertical displacement input into suspension*/
/*new_*.* -> the new positions after vertical movement h*/
/*new_hub_ang -> overall camber from input h*/
/*delta_hub_angle -> overall change in camber*/
/*uc_lc_offset -> assumed lca offset towards centerline as positive*/
/*towards centerline is positive in all cases*/

void builtin_camber(double hub_height, double uc_length, double lc_length,
     double uc_ang, double lc_ang, double uc_lc_offset, double delta, double new_hub_ang,
     double delta_hub_ang){

   double eff_uc_dist;
   double eff_lc_dist;
   double old_hub_ang;
   double new_lc_ang;
   double new_uc_ang;
   double vert_lc_disp;      /*displacement @ hub in vertical plane*/
   double vert_uc_disp;      /*displacement @ hub in vertical plane*/
   double new_vert_lc_disp;
   double new_vert_uc_disp;


   eff_uc_dist = cos(uc_ang)*uc_length;   /*calculates UCA distance from chassis*/
   eff_lc_dist = cos(lc_ang)*lc_length;   /*calculates LCA distance from chassis*/

   old_hub_ang = asin((eff_lc_dist-eff_uc_dist-uc_lc_offset)/hub_height);

   vert_lc_disp = sin(lc_ang)*lc_length;
   vert_uc_disp = sin(uc_ang)*uc_length;

   new_vert_lc_disp = vert_lc_disp + delta;
   new_vert_uc_disp = vert_uc_disp + delta;

   /*Todo: fix abs value iterations, function research needed*/
   /*use: make odd functions even for consistency -> results in variance*/
   /*when delta is equal to zero*/
   
   /*new_vert_lc_disp = abs(new_vert_lc_disp);*/
   /*new_vert_uc_disp = abs(new_vert_uc_disp);*/

   new_lc_ang = asin(new_vert_lc_disp/lc_length);
   new_uc_ang = asin(new_vert_uc_disp/uc_length);

   eff_uc_dist = cos(new_uc_ang)*uc_length;
   eff_lc_dist = cos(new_lc_ang)*lc_length;

   new_hub_ang = asin((eff_lc_dist-eff_uc_dist-uc_lc_offset)/hub_height);

   delta_hub_ang = new_hub_ang-old_hub_ang;

   if ((vert_lc_disp+delta) < 0.0) {
      new_lc_ang = -1.0 * new_lc_ang;
      }

   if ((vert_uc_disp+delta) < 0.0) {
      new_uc_ang = -1.0 * new_uc_ang;
      }
   new_uc_ang = (new_uc_ang * (180/pi));
   new_lc_ang = (new_lc_ang * (180/pi));
   old_hub_ang = (old_hub_ang * (180/pi));
   delta_hub_ang = (delta_hub_ang *(180/pi));
   
   
   printf("%.4f      %.4f            %.4f            %.4f               %.4f\n", delta, new_uc_ang, new_lc_ang, old_hub_ang, delta_hub_ang);



}



int main()
{
  double hub_height;
  double uc_length;
  double lc_length;
  double uc_ang;
  double lc_ang;
  double uc_lc_offset;
  double deltamain; /*eventually input matrix*/
  double new_hub_ang;
  double delta_hub_ang;

  printf("Welcome to the TTU FSAE suspension analysis software system!\n\n");
  
  printf("Written by : Nick Currier                  nicholas.currier.com\n");
  printf("Technical Support: Brent Frounfelker       frounfelker@gmail.com\n\n");
  
  printf("Proprietary software not for redistribution!!!\n");
  printf("For technical support please contact either of above!\n\n");
  
  printf("Please enter overall hub height from attachment points:\n");
  scanf("%lf", &hub_height);
  printf("Please enter overall upper control arm length:\n");
  scanf("%lf", &uc_length);
  printf("Please enter overall lower control arm length:\n");
  scanf("%lf", &lc_length);
  printf("Please enter starting upper control arm angle from static ride height\n");
  printf("Angles measured from horizontal and input in degrees\n");
  scanf("%lf", &uc_ang);
  printf("Please enter starting lower control arm angle from static ride height\n");
  printf("Angles measured from horizontal and input in degrees\n");
  scanf("%lf", &lc_ang);
  printf("Please enter interior upper to lower control arm offset:\n");
  printf("Positive offset toward centerline of vehicle\n");
  printf("Assumed longer lower control arm.  If not the case input a negative value.\n");
  scanf("%lf", &uc_lc_offset);
  
  
  uc_ang = (uc_ang * (pi / 180.0));      /*changes degrees to rads for calculations*/
  lc_ang = (lc_ang * (pi / 180.0));      /*changes degrees to rads for calculations*/
  
  printf("\n");
  printf("Jounce:    New UC angle:    New LC angle:    Old hub angle:     Delta hub angle:\n\n");  

  deltamain = -2.0;
  int j;
  
  for (j=0; j<40; j++)  {
      builtin_camber(hub_height,uc_length,lc_length,uc_ang,lc_ang,
      uc_lc_offset,deltamain,new_hub_ang,delta_hub_ang);
      deltamain = deltamain + 0.1;
  }
  
  
  system("PAUSE");


  return 0;
}
