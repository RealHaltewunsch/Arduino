# Arduino
Privates Arduino Repository

To-Do
- [ ] Geschwindigkeitsregelung 
- [ ] Code aufräumen und Übersichtlicher machen
- [ ] Start jumper Batterie Gehäuse 
- [ ] Doppeltes anfragen der Sensoren verhindern
- [ ] 12V Buchse mit Sicherung
- [ ] Spannung der Batterie messen und ausgeben, wenn Sollwert 0
- [ ] 575918µS benötigt der µC ohne angeschlossene Sensoren, 15µS min
- [ ] 116177µS max ohne Temperatursensorcheck, 14µS min
- [ ] Stromfehleranzeige
- [ ] Reset Taster hinzufügen 
- [x] Nur Bits neu Anzeigen lassen, Text wird neu geschrieben in der Fehler beseitigen Funktion
- [x] -127C Anzeige 
- [x] Anzeige: Fehler & Zustände, Geschwindigkeit wenn alles ok ist
- [x] alles auf einem Bildschirm ausgeben
- [x] Durchgängigkeit des Minuspols des Motors zum Gehäuse
- [x] Pid disable Funktion?
- [x] Temperaturfunktionen etc müssen regelmäßig aufgerufen werden
- [x] Messwerte vom Pedal nehmen und eingeben
- [x] Über und Untertemperatur in eine Funktion 
- [x] Geschwindigkeit ausgeben
- [x] Gaspedal nicht angeschlossen
- [x] Strombegrenzung implementieren
- [x] niedrige Temperatur Strombegrenzung
- [x] Was ruft pid Regler auf?
- [x] Freigabe Leuchte
- [x] Not-Aus raus, Notbetrieb rein, 10% der Leistung verfügbar 
- [x] Stromregelung fertig machen, mit Bedingungen!!!
- [x] Digital write MOSFET low in startup 


20ms benötigt der analogSensor um 4 Werte auszulesen und über den Seriellen Monitor auszusenden
