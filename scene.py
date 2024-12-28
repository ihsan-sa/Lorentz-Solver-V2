from manim import *
import pandas as pd
import os
import numpy as np

def string_to_vec(str):
    x = ""
    y = ""
    z = ""
    str_idx = 1
    while(str[str_idx] != ","):
        x += str[str_idx]
        str_idx = str_idx + 1
    
    str_idx = str_idx + 1
    while(str[str_idx] != ","):
        y += str[str_idx]
        str_idx = str_idx + 1
    
    str_idx = str_idx + 1
    while(str[str_idx] != "]"):
        z += str[str_idx]
        str_idx = str_idx + 1

    x = int(x)
    y = int(y)
    z = int(z)
    
    return (x,y,z)

class graph_data(ThreeDScene):
    def construct(self):

        config_file = open("config.txt", "r")

        sim_time = 0

        data_disp = []
        descp = Text("")

        point_charges = []

        # create a triangle that is rotating
        
        # now we read the file and print the stats
        title = "Simulation"
        t2 = ""
        for line in config_file:
            if(line.strip() == "#"):
                break
            if(line.strip() == "TITLE"):
                line = config_file.readline()
                title = line.strip()
                line = config_file.readline()
                t2 = line.strip()
            if(line.strip() == "SIM"):
                sim_time = float(config_file.readline())
            if(line.strip() == "CONFIG"):
                t = float(config_file.readline())
                dt = float(config_file.readline())
                line = config_file.readline()
                sim_type = line.strip()


                descp = Text(f"{title}\n{t2} \n\n\n\t- Simulation time: {t} seconds\n\n\t- Simulation time step: {dt} seconds \n\n\t- Animation time: {sim_time} seconds\n\n\t- Numerical method: {sim_type}", font_size=20, color=BLUE)
                # self.play(Write(descp))
                # self.wait(1.4)
                # self.play(FadeOut(descp))

            if(line.strip() == "P"):
                print("particle")
                line = config_file.readline()
                pos = line.strip()
                line = config_file.readline()
                vel = line.strip()
                line = config_file.readline()
                q = line.strip()
                line = config_file.readline()
                m = line.strip()

                particle_txt = Text(f"Particle: \n\n\t- pos: {pos}m \n\n\t- vel: {vel}m/s \n\n\t- charge: {q}C \n\n\t- mass: {m}kg", font_size=25, color=RED)
                data_disp.append(particle_txt)
                # self.play(Write(particle_txt))
                # self.wait(1.2)
                # self.play(FadeOut(particle_txt))

            if(line.strip() == "SPC"):
                print("spc")
                line = config_file.readline()
                pos = line.strip()
                line = config_file.readline()
                q = line.strip()

                spc_txt = Text(f"Static Point Charge (SPC): \n\n\t- pos: {pos}m \n\n\t- charge: {q}C", font_size=25, color=GREEN)
                data_disp.append(spc_txt)
                point_charges.append(string_to_vec(pos))
                # self.play(Write(spc_txt))
                # self.wait(1.2)
                # self.play(FadeOut(spc_txt))

            if(line.strip() == "UMF"):
                print("umf")
                line = config_file.readline()
                field = line.strip()
        

                umf_txt = Text(f"Uniform Magnetic Field: \n\n\t- field vector: {field}", font_size=25, color=BLUE)
                data_disp.append(umf_txt)
                # self.play(Write(umf_txt))
                # self.wait(1.2)
                # self.play(FadeOut(umf_txt))
            
            if(line.strip() == "UEF"):
                print("uef")
                line = config_file.readline()
                field = line.strip()
        

                uef_txt = Text(f"Uniform Electric Field: \n\n\t- field vector: {field}", font_size=25, color=ORANGE)
                data_disp.append(uef_txt)
                # self.play(Write(uef_txt))
                # self.wait(1.2)
                # self.play(FadeOut(uef_txt))

        self.play(Write(descp))
        self.wait(1.4)

        g_data_disp = []

        for i in range(int(len(data_disp)/2)):
            g_data_disp.append(VGroup(
                data_disp[2*i].shift(3*LEFT), 
                data_disp[(2*i)+1].shift(3*RIGHT)
            ))
        
        if(len(g_data_disp) != 0):
            self.play(ReplacementTransform(descp, g_data_disp[0]))
            self.wait(1.2)
            if(len(g_data_disp) == 1):
                self.play(FadeOut(g_data_disp[0]))
            else:
                for i in range(len(g_data_disp) - 1):
                    self.play(ReplacementTransform(g_data_disp[i], g_data_disp[i+1]))
                    self.wait(1.2)
                if(len(data_disp)%2 == 0):
                    self.play(FadeOut(g_data_disp[len(g_data_disp) - 1]))
                else:
                    self.play(ReplacementTransform(g_data_disp[len(g_data_disp) - 1], data_disp[len(data_disp) - 1]))
                    self.wait(1.2)
                    self.play(FadeOut(data_disp[len(data_disp) - 1]))
            

        os.system("./a.out")

        file = pd.read_csv("data.csv")

        cols = file.columns
        n_cols = len(cols) - 1
        n_particles = int(n_cols/3)
        print(f"particles: {n_particles}")

        all_x_vals = []
        all_y_vals = []
        all_z_vals = []

        max_x = 0
        max_y = 0
        max_z = 0

        for i in range(n_particles):
            print(f"Creating vals: {i}")
            all_x_vals.append(file[f'x{i}'])
            all_y_vals.append(file[f'y{i}'])
            all_z_vals.append(file[f'z{i}'])

            max_x = max(max_x, np.absolute(all_x_vals[i].max()), np.absolute(all_x_vals[i].min()))
            max_y = max(max_y, np.absolute(all_y_vals[i].max()), np.absolute(all_y_vals[i].min()))
            max_z = max(max_z, np.absolute(all_z_vals[i].max()), np.absolute(all_z_vals[i].min()))
        
        for spc in point_charges:
            (x, y, z) = spc
            print(spc)
            max_x = max(max_x, np.absolute(x))
            max_y = max(max_y, np.absolute(y))
            max_z = max(max_z, np.absolute(z))

        print(f"done making vals. max_x: {max_x} max_y: {max_y} max_z: {max_z}")
        max_x = 1.2 * max_x
        max_y = 1.2* max_y
        max_z = 1.2 * max_z
        axes = ThreeDAxes(
            x_range=[-max_x,max_x,0.1],
            y_range=[-max_y,max_y,0.1],
            z_range=[-max_z,max_z ,0.1],
            axis_config={"include_numbers": False, "include_ticks": False}
        )
        print("Done making axes")

        


        labels = axes.get_axis_labels(
            x_label="x",
            y_label='y',
            z_label='z'
        )
        all_points = []
        all_lines = []
        for i in range(n_particles):
            all_points.append([axes.c2p(x,y,z) for x,y,z in zip(all_x_vals[i], all_y_vals[i], all_z_vals[i])])
            all_lines.append(VMobject())
            all_lines[i].set_points_smoothly(all_points[i])
            color = interpolate_color(RED, BLUE, i/(n_particles-1))
            all_lines[i].set_color(color)

        # line = VMobject()
        # line.set_points_smoothly(points)
        # line.set_color(RED)
        self.move_camera(phi=70*DEGREES,theta=-45*DEGREES, run_time = 0.01)

        self.begin_ambient_camera_rotation(
            rate=PI/5,about="theta"
        )
        self.play(FadeIn(axes), FadeIn(labels))
        for spc in point_charges:
            point = Dot3D(point=axes.c2p(*spc), color=GREEN, radius=0.05)
            self.add(point)

        self.play(
            *[Write(all_lines[i]) for i in range(n_particles)],
            run_time = sim_time)
        
        # self.move_camera(phi=70*DEGREES, theta=2*PI, run_time=4, rate_func = rate_functions.linear)
        self.wait(5)

        print(file)