import customtkinter as ctk
from tkinter import filedialog, messagebox
import subprocess
import os

ctk.set_appearance_mode("system")  # "dark", "light", or "system"
ctk.set_default_color_theme("blue")  # "blue", "dark-blue", "green"

class CubeLauncher(ctk.CTk):
    def __init__(self):
        super().__init__()

        self.title("sillycube.py")
        self.geometry("480x180")
        self.resizable(False, False)

        # Texture Image
        ctk.CTkLabel(self, text="Texture Image (PNG):").grid(row=0, column=0, padx=15, pady=(20,5), sticky="w")
        self.texture_entry = ctk.CTkEntry(self, width=300)
        self.texture_entry.grid(row=0, column=1, padx=5, pady=(20,5))
        self.texture_entry.insert(0, "res/default.png")  # <-- default path here
        ctk.CTkButton(self, text="Browse", width=60, command=self.browse_texture).grid(row=0, column=2, padx=10, pady=(20,5))

        # Cube Size
        ctk.CTkLabel(self, text="Cube Size:").grid(row=1, column=0, padx=15, pady=5, sticky="w")
        self.size_entry = ctk.CTkEntry(self, width=100)
        self.size_entry.grid(row=1, column=1, padx=5, pady=5, sticky="w")
        self.size_entry.insert(0, "1.0")

        # Window Title
        ctk.CTkLabel(self, text="Window Title:").grid(row=2, column=0, padx=15, pady=5, sticky="w")
        self.title_entry = ctk.CTkEntry(self, width=300)
        self.title_entry.grid(row=2, column=1, padx=5, pady=5)
        self.title_entry.insert(0, "sillycube.py")

        # Launch Button
        launch_btn = ctk.CTkButton(self, text="release the sillyness", command=self.launch_cube)
        launch_btn.grid(row=4, column=1, pady=10)

        # Configure grid weights
        self.grid_columnconfigure(1, weight=1)

    def browse_texture(self):
        path = filedialog.askopenfilename(
            filetypes=[("PNG Images", "*.png"), ("All files", "*.*")]
        )
        if path:
            self.texture_entry.delete(0, ctk.END)
            self.texture_entry.insert(0, path)

    def launch_cube(self):
        args = []

        # Adjust this path if your cube executable is elsewhere
        cube_executable = "./cube"
        if not os.path.isfile(cube_executable):
            messagebox.showerror("Error", f"Cube executable not found at:\n{cube_executable}")
            return

        args.append(cube_executable)

        image = self.texture_entry.get().strip()
        if image:
            args.extend(["--image", image])

        size = self.size_entry.get().strip()
        if size:
            args.extend(["--size", size])

        title = self.title_entry.get().strip()
        if title:
            args.extend(["--title", title])


        try:
            subprocess.Popen(args)
        except Exception as e:
            messagebox.showerror("Error", f"Failed to launch cube:\n{e}")

if __name__ == "__main__":
    app = CubeLauncher()
    app.mainloop()
