from manim import *
import pandas as pd
import os
import numpy as np
import csv

def string_to_vec(str):

    #extract vector from string.
    #could use a more efficient method
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

    x = float(x)
    y = float(y)
    z = float(z)
    
    return (x,y,z)

def change_vec_mag(vec, mag):
    #change the magnitude of a vector
    (x,y,z) = vec
    norm = np.sqrt(np.pow(x, 2) + np.pow(y,2) + np.pow(z, 2))
    sc = mag/norm
    x = x*sc
    y = y*sc
    z = z*sc
    return (x,y,z)
class plot_particle_path(ThreeDScene):
    def construct(self):


        # Simulation configuration and settings
        output_ctxt = False
        show_vecs = True
        vector_scale = 0.03


        # open config file
        config_file = open("config.txt", "r")

        # base settings for the simulation
        sim_time = 0

        #for displaying the sim settings
        data_disp = []
        descp = Text("") # sim description
        author = Text("", font_size=1) # author

        #for storing and then displaying point charges and field vectors
        point_charges = []
        uefs = []
        umfs = []

        title_line1 = "Simulation" #first line of the title
        title_line2 = ""  #second line of the title

        #parsing the config file
        for line in config_file:
            if(line.strip() == "#"):
                break
            if(line.strip() == "TITLE"):
                line = config_file.readline()
                title_line1 = line.strip()
                line = config_file.readline()
                title_line2 = line.strip()
            if(line.strip() == "AUTHOR"):
                line = config_file.readline()
                author = Text(line.strip(), font_size=20)
                self.add_fixed_in_frame_mobjects(author)
            if(line.strip() == "SIM"):
                sim_time = float(config_file.readline())
            if(line.strip() == "CONFIG"):
                line = config_file.readline()
                sim_type = line.strip()
                t = float(config_file.readline())
                line = config_file.readline()
                dt = float(line)
                line = config_file.readline()
                num_method = line.strip()
                
                


                descp = Text(f"{title_line1}\n{title_line2} \n\n\n\t- Simulation Type: {sim_type} \n\n\t- Simulation time: {t} seconds\n\n\t- Simulation time step: {dt} seconds \n\n\t- Animation time: {sim_time} seconds\n\n\t- Numerical method: {num_method}", font_size=20, color=BLUE)
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
                umfs.append(string_to_vec(field))
                # self.play(Write(umf_txt))
                # self.wait(1.2)
                # self.play(FadeOut(umf_txt))
            if(line.strip() == "SUMF"):
                print("sumf")
                line = config_file.readline()
                field = line.strip()

                line = line = config_file.readline()
                c1 = line.strip()
                line = line = config_file.readline()
                c2 = line.strip()
                line = line = config_file.readline()
                c3 = line.strip()
                line = line = config_file.readline()
                c4 = line.strip()
                line = line = config_file.readline()
                c5 = line.strip()
                line = line = config_file.readline()
                c6 = line.strip()
                line = line = config_file.readline()
                c7 = line.strip()
                line = line = config_file.readline()
                c8 = line.strip()

        

                sumf_txt = Text(f"Sectioned Uniform Magnetic Field: \n\n\t- field vector: {field} \n\n\t- corners: \n\n\t\t- {c1} \n\n\t\t- {c2} \n\n\t\t- {c3} \n\n\t\t- {c4} \n\n\t\t- {c5} \n\n\t\t- {c6} \n\n\t\t- {c7} \n\n\t\t- {c8}", font_size=25, color=BLUE)
                data_disp.append(sumf_txt)
                umfs.append(string_to_vec(field))

            if(line.strip() == "UEF"):
                print("uef")
                line = config_file.readline()
                field = line.strip()
        

                uef_txt = Text(f"Uniform Electric Field: \n\n\t- field vector: {field}", font_size=25, color=ORANGE)
                data_disp.append(uef_txt)
                uefs.append(string_to_vec(field))
                # self.play(Write(uef_txt))
                # self.wait(1.2)
                # self.play(FadeOut(uef_txt))

            if(line.strip() == "W"):
                print("wire")
                line = config_file.readline()
                org = line.strip()
                line = config_file.readline()
                dir = line.strip()
                line = config_file.readline()
                i_wire = line.strip()

                wire_txt = Text(f"Wire:\n\n\t- origin: {org}\n\t- direction: {dir}\n\t- current: {i_wire}")
                data_disp.append(wire_txt)

        #always show the description
        self.play(Write(descp), Write(author.to_corner(DR)))
        self.wait(1.4)

        #display the remaining information if necessary
        if(output_ctxt):
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

                    if(len(data_disp)%2 != 0):
                        self.play(ReplacementTransform(g_data_disp[0], data_disp[len(data_disp) - 1]))
                        self.wait(1.2)
                        self.play(FadeOut(data_disp[len(data_disp) - 1]))

                    else: 
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
        else:
            self.play(FadeOut(descp))   

        #run the c++ simulation
        os.system("./compiled_files/compiled_solver")

        #read the c++ simulation output
        data_file = pd.read_csv("data.csv")
        
        #get the number of columns and determine the number of particles
        cols = data_file.columns
        n_cols = len(cols) - 1
        n_particles = int(n_cols/3)
        print(f"particles: {n_particles}")

        #init arrays for storing all the data
        all_x_vals = []
        all_y_vals = []
        all_z_vals = []

        #init vars to store max data points 
        max_x = 0
        max_y = 0
        max_z = 0

        #parse and store all the particle data
        for i in range(n_particles):
            print(f"Creating vals: {i}")
            all_x_vals.append(data_file[f'x{i}'])
            all_y_vals.append(data_file[f'y{i}'])
            all_z_vals.append(data_file[f'z{i}'])

            max_x = max(max_x, np.abs(all_x_vals[i].max()), np.abs(all_x_vals[i].min()))
            max_y = max(max_y, np.abs(all_y_vals[i].max()), np.abs(all_y_vals[i].min()))
            max_z = max(max_z, np.abs(all_z_vals[i].max()), np.abs(all_z_vals[i].min()))
        
        #update maxima for the displayed SPC and vector
        for spc in point_charges:
            (x, y, z) = spc
            print(spc)
            max_x = max(max_x, np.abs(x))
            max_y = max(max_y, np.abs(y))
            max_z = max(max_z, np.abs(z))

        if(show_vecs):
            max_coord = max(max_x,  max_y, max_z)

            for uef in uefs:
                (x,y,z) = change_vec_mag(uef, vector_scale*max_coord)
                max_x = max(max_x, x*2)
                max_y = max(max_y, y*2)
                max_z = max(max_z, z*2)
                
            
            for umf in umfs:
                (x,y,z) = change_vec_mag(umf, vector_scale*max_coord)
                max_x = max(max_x, x*2)
                max_y = max(max_y, y*2)
                max_z = max(max_z, z*2)


        print(f"done making vals. max_x: {max_x} max_y: {max_y} max_z: {max_z}") #user update

        #add a small buffer
        buffer = 1.2
        max_x = buffer * max_x
        max_y = buffer * max_y
        max_z = buffer * max_z

        #manage very small maximum values
        max_x = max(max_x, 0.01)
        max_y = max(max_y, 0.01)
        max_z = max(max_z, 0.01)

        #determine the maximum value of all three
        max_coord = max(max_x,  max_y, max_z)

        #create a scaling factor if the coordinates are too large. Otherwise manim breaks
        # NOT in use at the moment
        # sc_fctr = 1
        # if(max_coord > 10):
        #     sc_fctr = 10/max_coord

        # max_x *= sc_fctr
        # max_y *= sc_fctr
        # max_z *= sc_fctr

        #create the 3D axes
        axes = ThreeDAxes(
            x_range=[-max_x,max_x,0.001],
            y_range=[-max_y,max_y,0.001],
            z_range=[-max_z,max_z ,0.001],
            axis_config={"include_numbers": False, "include_ticks": False}
        )

        print("Done making axes") #user update

        #create the axes labels
        labels = axes.get_axis_labels(
            x_label="x",
            y_label='y',
            z_label='z'
        )

        #init the arrays to store points and lines
        all_points = []
        all_lines = []

        #for each particle, extract all points and create lines and store in the arrays
        for i in range(n_particles):
            all_points.append([axes.c2p(x,y,z) for x,y,z in zip(all_x_vals[i], all_y_vals[i], all_z_vals[i])])
            all_lines.append(VMobject())
            all_lines[i].set_points_smoothly(all_points[i])
            color = RED
            if(n_particles > 1):
                color = interpolate_color(RED, BLUE, i/(n_particles-1))
            all_lines[i].set_color(color)

        #move camera to first position
        self.move_camera(phi=70*DEGREES,theta=-45*DEGREES, run_time = 0.01)

        #begin rotation about the z-axis
        self.begin_ambient_camera_rotation(
            rate=PI/5,about="theta"
        )

        #display the axes and labels
        self.play(FadeIn(axes), FadeIn(labels))

        #display the field vectors if wanted
        if(show_vecs):
            for uef in uefs:
                vec = Vector(direction=axes.c2p(*change_vec_mag(uef, vector_scale*max_coord)), color = ORANGE)
                self.add(vec)
            
            for umf in umfs:
                vec = Vector(direction=axes.c2p(*change_vec_mag(umf, vector_scale*max_coord)), color = BLUE)
                self.add(vec)

        #display the point charges
        for spc in point_charges:
            point = Dot3D(point=axes.c2p(*spc), color=GREEN, radius=0.05)
            self.add(point)

        #draw the particle path
        self.play(
            *[Write(all_lines[i]) for i in range(n_particles)],
            run_time = sim_time)
        
        #keep rotating for a bit longer
        self.wait(5)

        #print data_file for debugging
        print(data_file)


##TESTS USING AI -- WORKING TOWARDS IMPLEMENTING THIS DIFFERENTLY

class disp_b_vec_field(ThreeDScene):
    def construct(self):
        print("bfield")

        def load_csv_to_dict(csv_file):
            field_data = {}
            with open(csv_file, "r") as csvfile:
                reader = csv.DictReader(csvfile)
                for row in reader:
                    x, y, z = float(row["x"]), float(row["y"]), float(row["z"])
                    xf, yf, zf = float(row["xf"]), float(row["yf"]), float(row["zf"])
                    field_data[(x, y, z)] = np.array([xf, yf, zf])
            return field_data

        # Define the function to retrieve field vectors and convert them to Manim directions
        def csv_field_function_with_directions(pos, field_data):
            key = (round(pos[0], 1), round(pos[1], 1), round(pos[2], 1))  # Round for match
            vector = field_data.get(key, np.array([0, 0, 0]))  # Default to zero vector if not found
            return vector[0] * RIGHT + vector[1] * UP + vector[2] * OUT

        # Example usage
        os.system("./compiled_files/compiled_solver")
        field_data = load_csv_to_dict("data.csv")  # Load the CSV data
        field_func = lambda pos: csv_field_function_with_directions(pos, field_data)  # Define the lambda

                
        func = lambda pos: np.sin(pos[1]) * RIGHT + np.cos(pos[0]) * UP + np.tan(pos[2]) *LEFT 

        axes = ThreeDAxes(
            x_range=[-2,2,0.1],
            y_range=[-2,2,0.1],
            z_range=[-2,2,0.1]
        )
        field = ArrowVectorField(
            field_func, 
            three_dimensions=True, 
            x_range=[-2, 2, 0.2],  # Include the full range of your data
            y_range=[-2, 2, 0.2],
            z_range=[-2, 2, 0.2]
        )        
        self.move_camera(phi=75 * DEGREES, theta=30 * DEGREES, zoom=1.3)

        self.begin_ambient_camera_rotation(
            rate=PI/5,about="theta"
        )
        self.add(axes)
        self.play(Write(field))
        self.wait(10)


class VectorField3D(ThreeDScene):
    def construct(self):
        # Set up the axes
        axes = ThreeDAxes(
            x_range=[-3, 3, 1],
            y_range=[-3, 3, 1],
            z_range=[-100, 100, 1],
        )
        self.add(axes)
        self.move_camera(phi=75 * DEGREES, theta=30 * DEGREES, zoom=0.8)

        # Read the CSV file and add arrows
        os.system("./compiled_files/compiled_solver")
        with open("data.csv", "r") as csvfile:
            reader = csv.DictReader(csvfile)
            for row in reader:
                # Parse position and vector components
                x, y, z = float(row["x"]), float(row["y"]), float(row["z"])
                xf, yf, zf = float(row["xf"]), float(row["yf"]), float(row["zf"])

                scaling_factor = 1
                scaled_vector = scaling_factor * np.array([xf, yf, zf])
                if np.linalg.norm(scaled_vector) == 0:
                    continue

                start = axes.c2p(x,y,z)
                end = axes.c2p(x + scaled_vector[0], y + scaled_vector[1], z + scaled_vector[2])

                # Create an arrow for the vector
                arrow = Arrow3D(
                    start=start,
                    end=end,
                    color=BLUE,
                    thickness=0.01,
                )
                self.add(arrow)

        # Set camera angle
        self.begin_ambient_camera_rotation(
            rate=PI/5,about="theta"
        )
        self.wait(10)
