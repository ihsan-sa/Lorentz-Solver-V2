import os

# open config file
config_file = open("config.txt", "r")

#define sim type
sim_type = ""

for line in config_file:
    if(line.strip() == "CONFIG"):
        sim_type = config_file.readline().strip()
        break



if(sim_type == "Lorentz Motion"):
    os.system("manim -pql scene.py plot_particle_path")
elif(sim_type == "B Field"):
    os.system("manim -pql scene.py disp_b_vec_field")