void Schalter () {
  Sport_Modus_auslesen();
  Notbetrieb_auslesen();
  Regenerativbremsen_auslesen();
  Leistungselektronik_auslesen();
  Freigabe_Check();
  if (Gang_wechseln) {   
     if (Gang_wechseln_delay) {        //bei diesem Durchlauf wird die Ausgangssituation hergestellt
      Gang_Wechsel();
      Gang_wechseln_delay = false;
      previousMillis_Inaktiv = currentMillis;
    }
    else {
      SEND(DIR,STOP);
      Gang_wechseln_delay = true;  //beim nächsten Durchlauf wird der Gang gewechselt
    }
  }
}
