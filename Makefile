# Variables
# Nom du programme
NOM = tower-defence

# Nom du compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic

# Options de l'editeur de liens
LDFLAGS = -lm

# dossier des fichiers sources
SDIR = src

# Liste des fichiers sources
SRC = $(SDIR)/$(wildcard *.c)

# dossier des fichiers objets
ODIR = obj
# Liste des fichiers objets
OBJ = $(ODIR)/$(SRC:.c=.o)

# dossier des fichiers headers
HDIR = lib

# Liste des fichiers headers
HDR = $(HDIR)/$(wildcard *.h)

#lien librairie sdl2
LIEN= ${PWD}/lib/SDL2/lib

# Regles
# Regle par defaut
all: $(NOM)

# Regle de creation de l'executable
$(NOM): $(OBJ)
	$(CC) -o $@ $^ $(LDFLAGS)

# Regle de creation des fichiers objets
%.o: %.c $(HDR)
	$(CC) -o $@ -c $< $(CFLAGS)

# Regle de nettoyage
clean:
	rm -rf *.o

# Regle de nettoyage totale
mrproper: clean
	rm -rf $(NOM)

# Regle de creation d'une archive
archive:
	tar -cvzf $(NOM).tar.gz

#ajout de la libraire au PATH
sdl2:
	-export LD_LIBRARY_PATH="${LIEN}"



