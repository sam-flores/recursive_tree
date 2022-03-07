#include "FPToolkit.c"
#include "M3d_matrix_tools.c"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int width = 600, height = 600;
double len = 150;
double d_theta = M_PI/10;

int branch(double len, double x, double y, double theta, double sign){

  /*

    this program takes the previous x,y and
    creates the next pair by adding len and rotating the point
    either left or right depending on the branch of recursion

  */

  double x1 = x, y1 = y;
  double x2 = x1 + sign*len*cos(theta + M_PI/2),
          y2 = y1 + sign*len*sin(theta + M_PI/2);
  G_line(x1, y1, x2, y2);

  len = len*.67;
  theta += d_theta;
  if(len > 4){ // recurse case
    branch(len, x2, y2, theta, 1); // left branch
    branch(len, x2, y2, theta, -1); // right branch
  }else{ //else exit
    return 0;
  }
}

int main(){

  G_init_graphics(width, height); // init graphics
  G_rgb(0,0,0);
  G_clear(); // clear background in black
  int q = 0;


  while(q != 'q'){
    G_rgb(1, .55, 1); // set color to pink
    branch(len, width/2, 0, 0, 1); // begin tree
    branch(len, width/2, height, 0, -1); // begin tree
    branch(len, 0, height/2, M_PI/2, -1); // begin tree
    branch(len, width, height/2, -M_PI/2, -1); // begin tree

    q = G_wait_key(); // check wait key

    if(q == 65362){
      d_theta += M_PI/25; // increase angle of twist
    }else if(q== 65364){
      d_theta -= M_PI/25; // decrease angle of twist
    }else if(q == 65363){
      len += 5;
    }else if(q == 65361){
      len -= 5;
    }

    G_rgb(0,0,0); // clear background for next run through
    G_clear();
}
}
