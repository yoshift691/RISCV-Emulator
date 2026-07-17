# RISC-V Processor Emulator (C & Python)

Un émulateur fonctionnel de processeur RISC-V capable de décoder et d'exécuter des instructions machine, accompagné d'un banc de test automatisé.

## 📁 Structure du projet
* `/emulator` : Code principal de la machine, de l'émulation et de la boucle d'exécution (main).
* `/exos` : Scripts d'extraction et de décodage des instructions binaires.
* `/tests` : Suite de tests pour valider le comportement de l'émulateur.

## 🛠️ Technologies utilisées
* **Émulateur :** C (Gestion de la mémoire, décodage d'opcodes, registres)
* **Automatisation :** Python (Script de validation de conformité des états du processeur)
* **Build System :** Makefile