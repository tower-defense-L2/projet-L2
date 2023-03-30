# projet-L2
## Contributeurs
| Nom            | Github                                  |
|----------------|-----------------------------------------|
| Antoine SAINTY | [enimaloc](https://github.com/enimaloc) |
| Meven PUREN    | [meo-pill](https://github.com/meo-pill) |
| Nathan DUVAl   | [Foakynda](https://github.com/foakynda) |

## Description
Ce projet dans le cadre de notre formation de L2 informatique à l'Université Du Mans a pour but de créer un jeu de type "Tower Defense" en utilisant la librairie graphique SDL2. <br>
Le but étant pour le joueur, de placer des "Tours" sur une carte donnée afin de passer des vagues d'ennemies passant sur un chemin défini. <br>
Le jeu va donc avoir plusieurs perspectives :
- stratégique, dû au placement des tours
- gestion, suite au système de ressources
La Documentation est disponible [ici](https://tower-defense-l2.github.io/projet-L2/).

## Planification
Le diagramme de Gantt est disponible [ici](https://docs.google.com/spreadsheets/d/1WgdX5Zml3Ks-bE99PTovAkDHtlANthjp1Kes8xw4FFY).

## avancement
![](https://img.shields.io/badge/State-In_production-brightgreen?style=for-the-badge)

![](https://img.shields.io/github/issues/tower-defense-L2/projet-L2?style=for-the-badge)

![](https://img.shields.io/github/issues-pr/tower-defense-L2/projet-L2?style=for-the-badge)

## Convention de nommage
### Commit
Les commits doivent suivre [ConventionnalCommits](https://www.conventionalcommits.org/en/v1.0.0/) et doivent être écrits en minuscule et en utilisant la convention suivante:
```
<type>([<scope>]): <description>
```
Les types de commit sont les suivants :
- feat: Ajout d'une nouvelle fonctionnalité
- fix: Correction d'un bug
- docs: Modification de la documentation
- style: Modification du style du code
- refactor: Modification du code sans changer son comportement
- perf: Modification du code pour améliorer les performances
- test: Ajout de tests ou modification des tests existants
- chore: Modification du build system ou des dépendances
- ci: Modification des fichiers de configuration du CI
- revert: Revert d'un commit précédent
- wip: Work in progress
- merge: Merge d'une branche
- release: Release d'une version
- hotfix: Correction d'un bug critique
- other: Autre
- init: Initialisation du projet

### Normes C
Nous suivons la norme C11 pour le code C. <br>

## Compilation

### nécessité
- GCC 4.7 ou supérieur

### Commandes make

|  Commande   |    Description     |
|-------------|--------------------|
| build       | compile le projet  |
| test        | compile les tests  |
| doc         | génere la doc      |
| run         | lance le projet    |
| clean       | nettoie le projet  |
| reomve      | supprime le projet |
| clean-doc   | suprime la doc     |
| install_sdl | installe sdl2      |
| all         | build+test+doc+sdl |
| archive     | génere une archive |