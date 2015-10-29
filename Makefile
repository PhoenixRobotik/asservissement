PROJECT=asservissement
default: asservissement
# Default Options
export ARCH  ?= dsPIC33F
export ROBOT ?= gros
export SDL   ?= yes
export DEBUG ?= _WARNING_

PARENT_DIR = ../

# Constantes de compilation
EXEC    = asser_robot
include $(PARENT_DIR)/hardware/common.mk
################################################################################
# Fichiers du projet

FICHIERS_C =\
	asser.c \
	PID.c \
	odometrie.c \
	trajectoire.c \
	math_precalc.c \
	tests_unitaires.c \

# Fichier de réglages dépendant de la plateforme
REGLAGES_H = reglages.h
ifeq ($(ARCH), PC)
	REGLAGES_H += reglages/$(ARCH).h
else
	REGLAGES_H += reglages/$(ROBOT)_robot.h
endif

FICHIERS_H = hardware.h $(REGLAGES_H) $(FICHIERS_C:.c=.h)

# Fichier de hardware dépendant de l'architecture
HARDWARE_C = hardware_$(ARCH).c
FICHIERS_C+= $(HARDWARE_C)

FICHIERS_O  += $(addprefix $(BUILD_DIR)/, $(FICHIERS_C:.c=.o) )

################################################################################
# Compilation

_libAsser: $(BUILD_DIR)/libAsser.a

$(BUILD_DIR)/libAsser.a: $(FICHIERS_O)

asservissement:$(BUILD_DIR)/$(EXEC)

$(BUILD_DIR)/$(EXEC): $(BUILD_DIR)/main.o libAsser libCommAsser libHardware
	@echo "	CC	$(PROJECT)|$@"
	@$(CC) -o $@ $(BUILD_DIR)/main.o $(CFLAGS) $(LDFLAGS) -lAsser -lCommAsser -lHardware

# Dépendances en headers, pas utile en réalité, mais mieux
$(BUILD_DIR)/asser.o: asser.h odometrie.h PID.h trajectoire.h # $(REGLAGES_H)
$(BUILD_DIR)/PID.o: PID.h $(REGLAGES_H)
$(BUILD_DIR)/odometrie.o: odometrie.h $(REGLAGES_H)
$(BUILD_DIR)/trajectoire.o: asser.h odometrie.h trajectoire.h
$(BUILD_DIR)/tests_unitaires.o: tests_unitaires.h asser.h odometrie.h $(REGLAGES_H)
$(BUILD_DIR)/hardware.o: $(HARDWARE_C) hardware.h

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)
	@mkdir -p $(BUILD_DIR)/reglages
