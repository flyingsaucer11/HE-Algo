#include "dungeon_explorer_client.h"


void printScreen(int update){
  std::vector<string> v1;
  v1.push_back("Welcome to the dungeon..");
  v1.push_back("#Use WASD for navigation #Use C for abort#");
  v1.push_back("Clashed with the monster!");
  v1.push_back("Found a treasure!");
  v1.push_back("Reached the edge of the map...");
  v1.push_back("Found enough treasures, Mission Successfull.");
  v1.push_back("Fought with too many monters, Game Over!");
  v1.push_back("Exploring the dungeon...");
  v1.push_back("Dungeon Explorer 1.0");
  
  std::cout<<v1[update]<<endl;
}