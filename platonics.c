
#include <stdio.h>

#include <stdlib.h>

#include <math.h>

#include <string.h>


static float xs[32];// = (float*)malloc(sizeof(float)*32); //seting arrays

static float ys[32];// = (float*)malloc(sizeof(float)*32);

static float zs[32];// = (float*)malloc(sizeof(float)*32);


//start openscad version


void makePoint(float x, float y, float z, int i)

{

  xs[i]=x;

  ys[i]=y;

  zs[i]=z;

}


void zeroPoints()

{

  int i=0;

  for(i=0;i<32;i+=1)

  {

    xs[i]=0;

    ys[i]=0;

    zs[i]=0;

  }

}


float torad(float i)

{

  return i*3.14159265/180;

}


//start tetrahedron


void otetra(float s,FILE* o)

{

  fprintf(o,"//tetrahedron\r\npolyhedron(points=[[");

    fprintf(o,"%f,0,0],[",s);

    fprintf(o,"0,0,%f],[",pow(2*s*s*(1-cos(torad(120)))-s*s,.5));

    fprintf(o,"%f,%f,0],[",s*cos(torad(120)),s*sin(torad(120)));

    fprintf(o,"%f,%f,0]],",s*cos(torad(240)),s*sin(torad(240)));

    fprintf(o,"faces=[[0,1,2],[3,1,0],[2,1,3],[0,2,3]]);\r\n");

  }


//start cube


  void ocube(float s,FILE* o){fprintf(o,"//cube\r\ncube([%f,%f,%f]);\r\n",s,s,s);}


//start octahedron


  void oocta(float s,FILE* o)

  {

    fprintf(o,"//octaheron\r\npolyhedron(points=[[");

      fprintf(o,"%f,%f,0],[",s*cos(torad(45)),s*sin(torad(45)));

      fprintf(o,"%f,%f,0],[",s*cos(torad(135)),s*sin(torad(135)));

      fprintf(o,"%f,%f,0],[",s*cos(torad(225)),s*sin(torad(225)));

      fprintf(o,"%f,%f,0],[",s*cos(torad(315)),s*sin(torad(315)));

      fprintf(o,"0,0,%f],[",s);

      fprintf(o,"0,0,%f]],",-s);

      fprintf(o,"faces=[[3,4,0],[0,4,1],[1,4,2],[2,4,3],[5,0,1],[5,1,2],[5,2,3],[5,3,0]]);\r\n");

    }


//start dodecahedron


    void ododeca(float s,FILE* o)

    {

  //faces defined as though you had a d12 with face 1 on the table with the 1 pointing to angle 0

      zeroPoints();

      float PL = pow(2*s*s*(1-cos(torad(72))),.5);

      float PH = s+pow(s*s-pow((PL/2),2),.5);

      float angle = acos(pow(5,.5)/-5);

      float Z=sin(angle)*PL+sin(angle)*PH;

      float m=pow(3,.5)/4*(1+pow(5,.5));


      int i=0;

  for(i=4;i>=0;i-=1){makePoint(s*cos(torad(72*i)),s*sin(torad(72*i)),0,4-i); }//make bottom ring, 0-4


  for(i=4;i>=0;i-=1){makePoint(s*cos(torad(72*i+32)),s*sin(torad(72*i+32)),Z,19-i); }//make top ring, 15-19


  for(i=4;i>=0;i-=1){makePoint(xs[4-i]+PL*-cos(angle)*cos(torad(72*i)),ys[4-i]+PL*-cos(angle)*sin(torad(72*i)),PL*sin(angle),9-i);} //make lower crown, 5-9


  for(i=4;i>=0;i-=1){makePoint(xs[19-i]+PL*-cos(angle)*cos(torad(72*i+32)),ys[19-i]+PL*-cos(angle)*sin(torad(72*i+32)),Z-PL*sin(angle),14-i);}//make upper crown, 10-14


    makePoint(0,0,0,20);


  makePoint(0,0,Z,21);


  fprintf(o,"//dodecahedron\r\npolyhedron(points=["); //start printing

    i=0;

  while(i<22)//print point list

  {

    fprintf(o,"[%f,",xs[i]);

      fprintf(o,"%f,",ys[i]);

      fprintf(o,"%f]",zs[i]);

      if(i!=21){fprintf(o,",");}

      else{fprintf(o,"],");}

      i+=1;

    }

    fprintf(o,"faces=[[1,0,20],[2,1,20],[3,2,20],[4,3,20],[0,4,20],[21,15,16],[21,16,17],[21,17,18],[21,18,19],[21,19,15],[0,1,6],[0,6,11],[0,11,5],[1,2,7],[1,7,12],[1,12,6],[2,3,8],[2,8,13],[2,13,7],[3,4,9],[3,9,14],[3,14,8],[4,0,5],[4,5,10],[4,10,9],[11,16,15],[5,11,15],[10,5,15],[12,17,16],[6,12,16],[11,6,16],[13,18,17],[7,13,17],[12,7,17],[14,19,18],[8,14,18],[13,8,18],[10,15,19],[9,10,19],[14,9,19]]);\r\n");

  }


//start icosahedron


  void oicosa(float s,FILE* o)

  {

    zeroPoints();

    float PL = s;

    float PH = pow(s*s-pow((s/2),2),.5);

    float R = pow(s*s/(2-2*cos(torad(72))),.5);

    float h = pow((s*s-R*R),.5);

    float angle = torad(360)-2*acos(pow(5,.5)/-3);

    float Z = 2*h+PH*sin(angle);

    int i = 0;


  makePoint(0,0,0,0); //bottom point in 0

  for(i=4;i>=0;i-=1){makePoint(R*cos(torad(72*i)),R*sin(torad(72*i)),h,5-i);}//make lower crown in 1-5

  makePoint(0,0,Z,6); //top point in 6

  for(i=4;i>=0;i-=1){makePoint(R*cos(torad(72*i+32)),R*sin(torad(72*i+32)),Z-h,11-i);}//make upper crown in 7-11


  fprintf(o,"//icosahedron\r\npolyhedron(points=["); //start printing

    i=0;

  while(i<12)//print point list

  {

    fprintf(o,"[%f,",xs[i]);

      fprintf(o,"%f,",ys[i]);

      fprintf(o,"%f]",zs[i]);

      if(i!=11){fprintf(o,",");}

      else{fprintf(o,"],");}

      i+=1;

    }

  fprintf(o,"faces=[[2,1,0],[3,2,0],[4,3,0],[5,4,0],[1,5,0],[6,7,8],[6,8,9],[6,9,10],[6,10,11],[6,11,7],[7,11,5],[11,10,4],[10,9,3],[9,8,2],[8,7,1],[11,4,5],[10,3,4],[9,2,3],[8,1,2],[7,5,1]]);\r\n");//i

}


//start .stl version


void pT(int a, int b, int c,FILE* o)

{

  fprintf(o," facet normal 0 0 0\r\n  outer loop\r\n   vertex ");

  fprintf(o,"%e %e %e\r\n",xs[a],ys[a],zs[a]);

  fprintf(o,"   vertex ");

  fprintf(o,"%e %e %e\r\n",xs[b],ys[b],zs[b]);

  fprintf(o,"   vertex ");

  fprintf(o,"%e %e %e\r\n",xs[c],ys[c],zs[c]);

  fprintf(o,"  endloop\r\n endfacet\r\n");

}


//start tetrahedron


void stetra(float s,FILE* o)

{

  zeroPoints();

  makePoint(s,0,0,0);

  makePoint(0,0,pow(2*s*s*(1-cos(torad(120)))-s*s,.5),1);

  makePoint(s*cos(torad(120)),s*sin(torad(120)),0,2);

  makePoint(s*cos(torad(240)),s*sin(torad(240)),0,3);

  fprintf(o,"solid tetrahedron\r\n");

  pT(0,1,2,o);

  pT(3,1,0,o);

  pT(2,1,3,o);

  pT(0,2,3,o);

  fprintf(o,"endsolid tetrahedron\r\n");

}


//start cube


void scube(float s,FILE* o)

{

  zeroPoints();

  makePoint(s/2,s/2,0,0);

  makePoint(s/2,-s/2,0,1);

  makePoint(-s/2,-s/2,0,2);

  makePoint(-s/2,s/2,0,3);

  makePoint(s/2,s/2,s,4);

  makePoint(s/2,-s/2,s,5);

  makePoint(-s/2,-s/2,s,6);

  makePoint(-s/2,s/2,s,7);

  fprintf(o,"solid cube\r\n");

  pT(0,1,3,o);

  pT(1,2,3,o);

  pT(0,1,4,o);

  pT(1,5,4,o);

  pT(1,2,5,o);

  pT(2,6,5,o);

  pT(2,3,6,o);

  pT(3,7,6,o);

  pT(3,0,7,o);

  pT(0,4,7,o);

  fprintf(o,"endsolid cube\r\n");

}


//start octahedron


void socta(float s,FILE* o)

{

  zeroPoints();

  makePoint(s*cos(torad(45)),s*sin(torad(45)),0,0);

  makePoint(s*cos(torad(135)),s*sin(torad(135)),0,1);

  makePoint(s*cos(torad(225)),s*sin(torad(225)),0,2);

  makePoint(s*cos(torad(315)),s*sin(torad(315)),0,3);

  makePoint(0,0,s,4);

  makePoint(0,0,-s,5);

  fprintf(o,"solid octahedron\r\n");

  pT(3,4,0,o);

  pT(0,4,1,o);

  pT(1,4,2,o);

  pT(2,4,3,o);

  pT(5,0,1,o);

  pT(5,1,2,o);

  pT(5,2,3,o);

  pT(5,3,0,o);

  fprintf(o,"endsolid octahedron\r\n");

}


//start dodecahedron


void sdodeca(float s,FILE* o)

{

  //faces defined as though you had a d12 with face 1 on the table with the 1 pointing to angle 0

  zeroPoints();

  float PL = pow(2*s*s*(1-cos(torad(72))),.5);

  float PH = s+pow(s*s-pow((PL/2),2),.5);

  float angle = acos(pow(5,.5)/-5);

  float Z=sin(angle)*PL+sin(angle)*PH;

  float m=pow(3,.5)/4*(1+pow(5,.5));


  int i=0;

  for(i=4;i>=0;i-=1){makePoint(s*cos(torad(72*i)),s*sin(torad(72*i)),0,4-i); }//make bottom ring, 0-4


  for(i=4;i>=0;i-=1){makePoint(s*cos(torad(72*i+32)),s*sin(torad(72*i+32)),Z,19-i); }//make top ring, 15-19


  for(i=4;i>=0;i-=1){makePoint(xs[4-i]+PL*-cos(angle)*cos(torad(72*i)),ys[4-i]+PL*-cos(angle)*sin(torad(72*i)),PL*sin(angle),9-i);} //make lower crown, 5-9


  for(i=4;i>=0;i-=1){makePoint(xs[19-i]+PL*-cos(angle)*cos(torad(72*i+32)),ys[19-i]+PL*-cos(angle)*sin(torad(72*i+32)),Z-PL*sin(angle),14-i);}//make upper crown, 10-14


    makePoint(0,0,0,20);


  makePoint(0,0,Z,21);


  fprintf(o,"solid dodecahedron\r\n");

  pT(1,0,20,o);

  pT(2,1,20,o);

  pT(3,2,20,o);

  pT(4,3,20,o);

  pT(0,4,20,o);

  pT(21,15,16,o);

  pT(21,16,17,o);

  pT(21,17,18,o);

  pT(21,18,19,o);

  pT(21,19,15,o);

  pT(0,1,6,o);

  pT(0,6,11,o);

  pT(0,11,5,o);

  pT(1,2,7,o);

  pT(1,7,12,o);

  pT(1,12,6,o);

  pT(2,3,8,o);

  pT(2,8,13,o);

  pT(2,13,7,o);

  pT(3,4,9,o);

  pT(3,9,14,o);

  pT(3,14,8,o);

  pT(4,0,5,o);

  pT(4,5,10,o);

  pT(4,10,9,o);

  pT(11,16,15,o);

  pT(5,11,15,o);

  pT(10,5,15,o);

  pT(12,17,16,o);

  pT(6,12,16,o);

  pT(11,6,16,o);

  pT(13,18,17,o);

  pT(7,13,17,o);

  pT(12,7,17,o);

  pT(14,19,18,o);

  pT(8,14,18,o);

  pT(13,8,18,o);

  pT(10,15,19,o);

  pT(9,10,19,o);

  pT(14,9,19,o);

  fprintf(o,"endsolid dodecahedron\r\n");

}


//start icosahedron


void sicosa(float s,FILE* o)

{

  zeroPoints();

  float PL = s;

  float PH = pow(s*s-pow((s/2),2),.5);

  float R = pow(s*s/(2-2*cos(torad(72))),.5);

  float h = pow((s*s-R*R),.5);

  float angle = torad(360)-2*acos(pow(5,.5)/-3);

  float Z = 2*h+PH*sin(angle);

  int i = 0;


  makePoint(0,0,0,0); //bottom point in 0

  for(i=4;i>=0;i-=1){makePoint(R*cos(torad(72*i)),R*sin(torad(72*i)),h,5-i);}//make lower crown in 1-5

  makePoint(0,0,Z,6); //top point in 6

  for(i=4;i>=0;i-=1){makePoint(R*cos(torad(72*i+32)),R*sin(torad(72*i+32)),Z-h,11-i);}//make upper crown in 7-11

    fprintf(o,"solid icosahedron\r\n");

  pT(0,1,2,o);

  pT(0,2,3,o);

  pT(0,3,4,o);

  pT(0,4,5,o);

  pT(0,5,1,o);

  pT(6,7,8,o);

  pT(6,8,9,o);

  pT(6,9,10,o);

  pT(6,10,11,o);

  pT(6,11,7,o);

  pT(7,11,5,o);

  pT(11,10,4,o);

  pT(10,9,3,o);

  pT(9,8,2,o);

  pT(8,7,1,o);

  pT(11,4,5,o);

  pT(10,3,4,o);

  pT(9,2,3,o);

  pT(8,1,2,o);

  pT(7,5,1,o);

  fprintf(o,"endsolid icosahedron\r\n");

}


void main()

{

  char *intxt = (char*)malloc(sizeof(char)*32);

  int mode = 0;

  do

  {

    printf("Do you want to generate a .stl? Y/N\n");

    scanf("%s",intxt);

    if(strcmp(intxt,"Y")==0){mode=1;}

    memset(intxt,0,strlen(intxt));

    if(mode!=1)

    {

      printf("Do you want to generate a .txt with code for Openscad? Y/N\n");

      scanf("%s",intxt);

      if(strcmp(intxt,"Y")==0){mode=2;}

      memset(intxt,0,strlen(intxt));

    }

  } while(mode==0);

  FILE* out;

  if(mode==1){out=fopen("platonic.stl","w");}

  else{out=fopen("platonic.txt","w");}

  int op1=1;

  float op2=0;

  while(op1!=0)

  {

    printf("Type in the amount of faces of the platonic solid you want to construct (4,6,8,12,20) or 0 to quit\n");

    scanf("%s",intxt);

    op1=atoi(intxt);

    memset(intxt,0,strlen(intxt));

    if(op1==4||op1==6||op1==8||op1==12||op1==20)

    {

      printf("Type in a floating point scaling to your solid\nNote for 6,20 this is the length of a side\nFor 8 this is the distance from the center to a vertex\nFor 4,12 this is the length from the center of a face to a vertex on that face.\n");

      scanf("%s",intxt);

      op2=atof(intxt);

      memset(intxt,0,strlen(intxt));

    }

    if(op1 == 4)

    {

      if(mode==2){otetra(op2,out);}

      else{stetra(op2,out);}

    }

    if(op1 == 6)

    {

      if(mode==2){ocube(op2,out);}

      else{scube(op2,out);}

    }

    if(op1 == 8)

    {

      if(mode==2){oocta(op2,out);}

      else{socta(op2,out);}

    }

    if(op1 == 12)

    {

      if(mode==2){ododeca(op2,out);}

      else{sdodeca(op2,out);}

    }

    if(op1 == 20)

    {

      if(mode==2){oicosa(op2,out);}

      else{sicosa(op2,out);}

    }

  }

  //free(xs);

  //free(ys);

  //free(zs);

  free(intxt);

  fclose(out);

}



