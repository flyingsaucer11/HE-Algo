#include <stdlib.h>
#include <cassert>
#include <codecvt>
#include <iostream>
#include <locale>
#include <string>
#include <vector>

#include "transpiler/data/fhe_data.h"
#include "dungeon_explorer/dungeon_explorer_api_tfhe.h"
#include "dungeon_explorer/dungeon_explorer_client.h"
#include "xls/common/logging/logging.h"

constexpr int kMainMinimumLambda = 120;

Values processMove(int x,int y,char ch, TFHEParameters params, TFHESecretKeySet key){
  char res='e';

  if(ch=='W') x--;
  else if(ch=='S') x++;
  else if(ch=='A') y--;
  else if(ch=='D') y++;
  if(x>=0 && x<5 && y>=0 && y<5){
    // Encrypt the input.
    auto ciphertext1 = FheInt::Encrypt(x, key);
    auto ciphertext2 = FheInt::Encrypt(y, key);
    std::cout << "Encryption done" << std::endl;

    std::cout << "Initial state check by decryption: " << std::endl;
    std::cout << ciphertext1.Decrypt(key) << "\n";
    std::cout << ciphertext2.Decrypt(key) << "\n";
    std::cout << "\n";

    // Make a move.
    FheChar cipher_result(params);

    XLS_CHECK_OK(
        feedback(cipher_result.get(), ciphertext1.get(), ciphertext2.get(), key.cloud()));

    char ans = cipher_result.Decrypt(key);

    res=ans;
  }
  else{
    printScreen(4);
  }
  Values val;
  val.posX=x;
  val.posY=y;
  val.resCh=res;

  return val;
}




void gameLoop(){

	// generate a keyset
	TFHEParameters params(kMainMinimumLambda);

	// generate a random key
	// Note: In real applications, a cryptographically secure seed needs to be
	// used.
	std::array<uint32_t, 3> seed = {314, 1592, 657};
	TFHESecretKeySet key(params, seed);


    int hp=3;
    int tr=0;
    int mn=0;
    int target=3;
    int posX=0;
    int posY=0;
    printScreen(0);
    printScreen(1);
    char ch;
    cin>>ch;
    while(ch!='C'){
      Values val=processMove(posX, posY, ch, params, key);
      if(val.resCh=='e'){
        cin>>ch;
        continue;
      }
      else{
        posX=val.posX;
        posY=val.posY;
        if(val.resCh=='o'){
          printScreen(7);
        }
        else if(val.resCh=='t'){
          printScreen(3);
          tr=tr+1;
        }
        else if(val.resCh=='x'){
          printScreen(2);
          hp--;
        }
      }
      if(tr==target){
        printScreen(5);
        ch='C';
        continue;
      }
      if(hp==0){
        printScreen(6);
        ch='C';
        continue;
      }
      cin>>ch;
    }
  printScreen(8);
}



int main(){
	gameLoop();
}
