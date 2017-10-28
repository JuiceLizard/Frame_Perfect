//FRAME PERFECT
//Juice Lizard

#include "kitco.h"
#include <EEPROM.h>

byte modeJeu = 0;
#define ECRAN_SCORE 0
#define PARTIE 1

int xBalle = 82;
int xRaquette = 83;
int score = 0;
bool versLaDroite = false;
bool finPartie = false;

void setup() {

  initialiserKitco(1);
  lcdBegin();
  setContrast(60);

}

void loop() {
  switch (modeJeu) {
    case ECRAN_SCORE:
        effacerEcran(BLANC);
        
        ecrireLettre('0'+score%10, 41, 20, NOIR);
        if (score>=10) ecrireLettre('0'+(score/10)%10, 36, 20, NOIR);
        
        rafraichirEcran();
        if (toucheA()) {
          xBalle = 82;
          xRaquette = 83;
          score = 0;
          versLaDroite = false;
          finPartie = false;
          frequenceBuzzer(2000, 100);
          delai(100);
          frequenceBuzzer(1000, 100);
          delai(100);
          frequenceBuzzer(2000, 100);
          delai(100);          
          modeJeu = PARTIE;
        }
        break;
        
    case PARTIE:
        effacerEcran(BLANC);
        ligneEcran(xBalle, 0, xBalle, 48, NOIR);
        if (versLaDroite == true) {
          xBalle = xBalle + 1;
        }
        if (versLaDroite == false) {
          xBalle = xBalle - 1;
          if (xBalle < 1) {
            versLaDroite = true;
          } 
        }
        if ((versLaDroite == true) && (toucheA())) {
          xRaquette = xBalle;
          xBalle = xBalle - 1;
          xRaquette = xRaquette - 1;
          score = score + 1;
          versLaDroite = false;
          frequenceBuzzer(1000, 60);
          delai(60);
        }
        ligneEcran(xRaquette, 0, xRaquette, 48, NOIR);
        rafraichirEcran();
        if (xBalle == 0) {
          frequenceBuzzer(1000, 60);
          delai(60);
        }
        if (((xBalle >= xRaquette) && (versLaDroite == true)) || (xRaquette < 2)) {
          finPartie = true;
        }
        if (finPartie == true) {
          frequenceBuzzer(1000, 100);
          delai(100);
          frequenceBuzzer(1500, 100);
          delai(100);
          frequenceBuzzer(2000, 100);
          delai(100);
          modeJeu = ECRAN_SCORE;
        }
        break; 
  }
}
