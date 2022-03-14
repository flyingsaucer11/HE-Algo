#include "dungeon_explorer_api.h"


#pragma hls_top
char feedback(int x,int y){
  int mx=5;
  int ind=x*mx+y;
  char arr[25]=
  {
  'o','o','o','x','t',
  'o','o','t','o','o',
  'x','x','o','o','o',
  'o','x','t','o','o',
  'o','t','o','o','x'
  };
  return arr[ind]; 
}