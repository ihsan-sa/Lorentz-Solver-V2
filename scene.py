from manim import *
import pandas as pd
import os
import numpy as np

class graph_data(ThreeDScene):
    def construct(self):

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

        self.add(axes, labels)
        self.begin_ambient_camera_rotation(
            rate=PI/5,about="theta"
        )
        self.play(
            *[Write(all_lines[i]) for i in range(n_particles)],
            run_time = 15)
        
        # self.move_camera(phi=70*DEGREES, theta=2*PI, run_time=4, rate_func = rate_functions.linear)
        self.wait(10)

        print(file)