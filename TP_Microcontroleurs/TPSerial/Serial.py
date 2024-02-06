import serial
import serial.tools.list_ports
import tkinter as tk
from tkinter import ttk
import threading

def get_com_ports():
    """Fonction pour obtenir la liste des ports COM disponibles."""
    ports = [port.device for port in serial.tools.list_ports.comports()]
    return ports

def on_select(event):
    """Fonction appelée lorsqu'un élément est sélectionné dans le menu déroulant."""
    selected_port = port_var.get()
    status_label.config(text=f"Port COM sélectionné : {selected_port}")

    # Fermer le port série existant s'il y en a un
    if serial_port.isOpen():
        serial_port.close()

    # Ouvrir le nouveau port série sélectionné
    serial_port.port = selected_port
    serial_port.open()

def read_serial_data():
    """Fonction pour lire les données depuis le port série."""
    while serial_port.isOpen():
        try:
            # Lire une ligne de données depuis le port série
            data = serial_port.readline().decode("utf-8")
            # Traitement des données (exemple: diviser la ligne en différentes informations)
            process_data(data)
        except serial.SerialException:
            break

def process_data(data):
    """Fonction pour traiter les données et mettre à jour les informations."""
    # Exemple: Diviser la ligne en différentes parties (séparées par des virgules)
    parts = data.strip().split(',')
    # Mettre à jour les étiquettes avec les informations
    if len(parts) >= 3:
        label1.config(text=f"Info 1: {parts[0]}")
        label2.config(text=f"Info 2: {parts[1]}")
        label3.config(text=f"Info 3: {parts[2]}")

# Création de la fenêtre principale
root = tk.Tk()
root.title("Communication Série")

# Création d'une variable de type StringVar pour stocker le port sélectionné
port_var = tk.StringVar()

# Création du menu déroulant
ports_menu = ttk.Combobox(root, textvariable=port_var, values=get_com_ports())
ports_menu.grid(row=0, column=0, padx=10, pady=10)
ports_menu.bind("<<ComboboxSelected>>", on_select)

# Création d'une étiquette pour afficher le port sélectionné
status_label = ttk.Label(root, text="")
status_label.grid(row=1, column=0, padx=10, pady=10)

# Création d'étiquettes pour afficher les informations
label1 = ttk.Label(root, text="Info 1: ")
label1.grid(row=2, column=0, padx=10, pady=5, sticky=tk.W)

label2 = ttk.Label(root, text="Info 2: ")
label2.grid(row=3, column=0, padx=10, pady=5, sticky=tk.W)

label3 = ttk.Label(root, text="Info 3: ")
label3.grid(row=4, column=0, padx=10, pady=5, sticky=tk.W)

# Création d'un objet de port série
serial_port = serial.Serial()

# Création d'un thread pour la lecture continue des données série
serial_thread = threading.Thread(target=read_serial_data)
serial_thread.daemon = True
serial_thread.start()

# Exécution de la boucle principale de l'interface graphique
root.mainloop()
