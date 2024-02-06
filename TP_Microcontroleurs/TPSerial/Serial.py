import serial.tools.list_ports
import tkinter as tk
from tkinter import ttk

def get_com_ports():
    """Fonction pour obtenir la liste des ports COM disponibles."""
    ports = [port.device for port in serial.tools.list_ports.comports()]
    return ports

def on_select(event):
    """Fonction appelée lorsqu'un élément est sélectionné dans le menu déroulant."""
    selected_port = port_var.get()
    status_label.config(text=f"Port COM sélectionné : {selected_port}")

# Création de la fenêtre principale
root = tk.Tk()
root.title("Liste des Ports COM")

# Création d'une variable de type StringVar pour stocker le port sélectionné
port_var = tk.StringVar()

# Création du menu déroulant
ports_menu = ttk.Combobox(root, textvariable=port_var, values=get_com_ports())
ports_menu.grid(row=0, column=0, padx=10, pady=10)
ports_menu.bind("<<ComboboxSelected>>", on_select)

# Création d'une étiquette pour afficher le port sélectionné
status_label = ttk.Label(root, text="")
status_label.grid(row=1, column=0, padx=10, pady=10)

# Exécution de la boucle principale de l'interface graphique
root.mainloop()