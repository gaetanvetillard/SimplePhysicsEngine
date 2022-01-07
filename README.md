# TP de fin de semestre S1 ESIEA
Réalisé en binôme avec Maëline LEFEUVRE.

## Installation
    git clone https://github.com/gaetanvetillard/SimplePhysicsEngine.git

Sur Linux :

    sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev
    cd .\SimplePhysicsEngine\SimplePhysicsEngine
    make
    ./spe.bin
Sur Windows, le projet vs est déjà prêt.

## Utilisation
**Objectif**
Atteindre le meilleur score en atteignant le maximum d'étoiles grâce à des balles reliées avec des ressorts.

**Explications des balles :**
|Balle | Spécifications |
|--|--|
| 1 - Normale | Jusqu'à 3 ressorts |
| 2 - Girafe | Jusqu'à 3 ressorts et des longs ressorts |
| 3 - Escargot | Jusqu'à 2 ressorts, vitesse faible |
| 4 - Araignée | Jusqu'à 8 ressorts |
| 5 - Suppression | Supprime la balle sélectionnée |


**Touches :**

|Touche|Action  |
|--|--|
| Clic gauche | Pose la balle / fais l'action |
| Clic droit| Déplace la caméra |
| 1 | Balle normale |
| 2 | Balle girafe |
| 3 | Balle escargot |
| 4 | Balle araignée |
| 5 | Suppression |
| Molette haute | Choix de balle vers la droite|
| Molette basse | Choix de balle vers la gauche|
| Echap | Menu pause |
| Entrée | Recommencer |
| Espace | Réinitialiser la vue  |
