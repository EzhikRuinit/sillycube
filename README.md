# sillycube
a simple spinning cube project written in C + Python

preview of the program:
![image](https://github.com/user-attachments/assets/47ab4641-40d0-4783-a9b4-b4d714048287)

## how to build?
run 
```bash 
sudo dnf in gcc mesa-libGL-devel glfw-devel glew-devel mesa-libGL-devel glfw-devel glew-devel
./compile.sh
```

you can launch the cube maunally by
```
./cube --image /path/to/image --size x.x --title "Example Title"
```
or with python launcher
```
source .venv/bin/activate
python launcher.py
```
