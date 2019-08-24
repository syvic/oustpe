/*
    1.- All the controllers are dark. As the players press the squishy trigger their controller lights up white.
    2.- When all the controllers are white (or someone presses Triangle) the controllers will vibrate, then flash red/yellow/green as a "get ready" signal.
    3.- Every controller turns a different colour and the game has begun.
    4.- The aim of the game is to force all the other players to move their controllers too fast, either by hitting the controller, making them flinch, or the other player doing something stupid.
    5.- If your controller is going too fast it'll flicker as a warning.
    6.- If you are knocked out, your controller goes dark and vibrates.
    7.- The last player standing has their controller flash a beautiful rainbow sequence, and all controllers vibrate to indicate the end of the game.
    8.- The game resets, people hand their controllers to other people to play. GOTO 1.


Elementos necesarios:

- Acelerómetro para detectar movimiento [HALL]
- LED RGB para mostrar el estado [PUERTO SERIE]
- Motor vibrador [OPCIONAL]
- Pulsador de ready U(pulsación corta) / start (pulsación larga)

Secuencia:
- Al pulsar el botón de ready el nodo manda un mensaje diciendo que está vivo - El led se pone blanco (ready)
- Cuando alguno pulsa el botón de start se envía un mensaje indicando que empieza la partida - Preparados(ROJO), 
  listos (NARANJA), ya (VERDE)! - Cada nodo se pone de un color
- Si se detecta demasiado movimiento el nodo muere y envía evento a todos los demás indicándolo - El led se apaga 
- 

Mensajes
===================================

JOIN 
  - UUID
  - GROUP

DEAD
  - UUID

START
  - GROUP



*/
