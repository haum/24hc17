24HC17 --
=========

Matériel
--------

- 13 laumii + adaptateurs
- 13 câbles micro usb

Concepts
--------

- Entrée en matière minimale (juste un Laumio branché au secteur)
- Passage en Wifi à partir d'un certain stade
- Fil rouge (une question finale avec indices)
- Retour en arrière ("Quelle est la réponse à la question 4 ?")
- Les forcer à prendre des notes
- Tocken à aller jouer sur une autre lampe pour récupérer son propre token

Archi & Co
==========

Embedded
--------

- Token:
	- checksum (4 bits)
	- anim (5 bits)
	- color (5 bits)
	- ID (16 bits)
	- faults (4 bits)
	- msg (5 bits)
	- riddle

Serveur
-------

- Django
	- Team (nom demandé par Nero au premier token)
	- TeamMember (pseudo IRC)
	- Challenges
	- Attempts
	- Animations
	- Messages
	- RiddleTreeEdge

- Nero Talkback (via query)

Nero Bot
--------

- communication via le chan public
- hooké dans l'ORM
- SCUD-based AI (markov chain)

Délire(s) & Pénalités
=====================

- Question Fort Boyard (Quiiiiiiii suiiiis-je ?, message codé à déchiffrer)
- Si mauvais token (celui d'une autre équipe) passage en mode punition pendant 15 minutes

Questions
=========

1Q. 004032 LAIRES BSU

   Le Laumio affiche 004032 LAIRES BSU en Morse.
   La question s'arrête quand un caractère est envoyé sur la liaison série

1R. Welcome in the game.
    Please connect to #24hc17laumii @ freenode (IRC network) and authenticate in Nero
    system with the following message :

      Nero: <token>

    (Le laumio affiche un prompt pour le token suivant)



2. Ave Cesar


    AVE IMPERATOR, NVNTIVS VENIT.
    Gvzr unf pbzr gb cebir lbhe jbegu. Va gur arkg 24u (be yrff) lbh jvyy unir gb nafjre
    dhrfgvbaf, fbyir ceboyrzf, ravtznf naq znlor zbir lbhe nff bhg bs lbhe punve.
    Areb jvyy fgnl ol lbhe fvqr nf gur tbbq zragbe ur vf. Cyrnfr xrrc fraqvat uvz lbhe
    thrffrf, ur funyy gura tvir lbh gur xrlf gb zbir sbejneq.

    Areb vf snve ohg ungrf ybbfref. Rnpu gvzr lbh snvy, lbhe punapr bs orvat chavfurq vapernfrf.

    Cebir lbh'ir qrpbqrq guvf zrffntr naq fnl nir gb gur Ynhzvb.

Transcription

    Time has come to prove your worth. In the next 24h (or less) you will have to answer
    questions, solve problems, enigmas and maybe move your ass out of your chair.
    Nero will stay by your side as the good mentor he is. Please keep sending him your
    guesses, he shall then give you the keys to move forward.

    Nero is fair but hates loosers. Each time you fail, your chance of being punished increases.

    Prove you've decoded this message and say ave to the Laumio.

3. On verra.






Idées
-----

3x4
"""

Calcul simple en lettres style "five times two in numbers ?"
=> utilise ta tête

We are alone
""""""""""""

L'appareil annonce "We are alone" et attend une entrée utilisateur (pour qu'ils lisent ce message... ou pas).
Puis diffuse une palanquée de caractères (100k ?) dont seuls les caractères du token sont uniques.

I am alone
""""""""""

L'appareil annonce "I am alone" et attend une entrée utilisateur (pour qu'ils lisent ce message... ou pas).
Puis diffuse une palanquée de mots (suite de caractères séparés par  dont un seul est unique, il s'agit du token.

Markers
"""""""

One small with 3 wards per side cannot escape
=> Trouver les caractère en minuscule entre 3 majuscules exactement

We are legion
"""""""""""""

65535x65537
=> Ce n'est pas -1

Quick computation
"""""""""""""""""

L'appareil pose des questions de calcul style "32 x 45"
Et dit "Too late" au bout d'un timeout court.

Linked list
"""""""""""

L'appareil annonce "Next is XXXXX" "Next ?"
XXXXX change à chaque fois => longue chaine pour forcer à utiliser un programme pour parcourir le chemin
=> un petit message de moquerie si jamais on arrive à voir que c'est fait à la main

Déplacements aveugles
"""""""""""""""""""""

But: sortir d'un hyper-mini labyrinthe avec north/south/east/west
On ne sait pas où est le mobile au début, il faut le déplacer et ouvrir quand on est certains qu'il est à un endroit précis.

Dichotomie retardée
"""""""""""""""""""

Trouve le nombre auquel je pense... mais je te dis "plus" ou "moins" avec une question de retard

Labyrinthe
""""""""""

Découvrir un graphe cyclique et trouver le plus long chemin entre deux points

Quelle est ma raison
""""""""""""""""""""

L'appareil donne une série, il faut trouver sa raisoin

Simon
"""""

Le laumio joue une séquence de couleur rouge, vert, bleu, et jaune. Les joueurs doivent donner la séquence complète sans erreur.

La couleur manquante (simon forgets)
""""""""""""""""""""""""""""""""""""

Le laumio joue une séquence de couleur rouge, vert, bleu et jaune une première fois, puis rejoue la séquence une seconde fois avec des blancs (symbolisés par une led blanche) que les joueurs devront remplir.

