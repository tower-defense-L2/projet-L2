# Variables
# Nom du programme
NOM = prog

# Nom du compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -Werror -std=c99 -pedantic

# Options de l'editeur de liens
LDFLAGS = -lm

# Liste des fichiers sources
SRC = $(wildcard *.c)

# Liste des fichiers objets
OBJ = $(SRC:.c=.o)

# Liste des fichiers headers
HDR = $(wildcard *.h)

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
