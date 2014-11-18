#Gamal DeWeever
#file should generate a skirt and two hemispheres

file_name = "sphere_code.txt";
if(File.exists?(file_name))
	File.delete(file_name)
end
genfile = File.new(file_name, "w")

#position constants
$x_start = 50.0
$y_start = 50.0
$sections = 50.0
$max_temperature = 200

#size constants in MM
$sphere_radius = 20.0
$skirt_radius = $sphere_radius + 10 
$layer_number = 10
$layer_height = 0.3
#represents the current layer we are drawing
$current_layer = 1;

#gen_header: file -> null
#generates the gcode for the makerbot that comes before printing the object
def gen_header(input)
	input.write("Generating GCode for sphere\n")
	#home
	input.write("G28\n")
	#turn off the fan
	input.write("M107\n")
	input.write("G90\n")
	input.write("M82\n")
	input.write("M190 S50\n")
	input.write("M104 T0 S#{$max_temperature}\n")
	input.write("G92 E0\n")
	#wait for the extruder to heat up
	input.write("M109 T0 S#{$max_temperature}\n")
end

#gen_footer: file -> null
#generates the ending of the file to move the head out of the way
#and turn off everything


#gen_coordinate: tuple -> null
#generates the G1 Command for a given set of coordinates
#and writes it to a file
def gen_coordinate(input, coordinates, distance)

	input.write("G1 X#{coordinates[0]} Y#{coordinates[1]} #{distance}")
	return coordinates
end

def gen_circle(input,radius, y_start,x_start)
	circumference = Math::PI*2*radius
	#we want to divide the circle into 50 segments
	point_increment = (circumference/$sections)
	#we want to define a distance for the arc
	arc_distance = ($sections/360.0)*circumference
	final_coord = []
	#do a smooth incrememnt and decrememnt of the skirt
	(1...50).each do |k|
		
		new_x = (Math.cos(Math::PI + k*point_increment)*radius) + x_start
		new_y = Math.sin(0+ k*point_increment) + y_start
		final_coord = gen_coordinate(input, [new_x,new_y], arc_distance)
				end

	return final_coord
end

#gen_skirt: file -> null
#generates the skirt/perimeter for the print 
def gen_skirt(input)
	gen_circle(input,$skirt_radius,$y_start +10,$x_start +10)
	#separate the code so we know where the skirt ends
	input.write("END SKIRT")
end

#gen_bottom: file -> null
#generates the bottom hemisphere of the sphere
#this also incremets $current_layer
def gen_bottom(input)
	(1...$layer_number/2).each do |k|
		next_layer = gen_circle(input,$sphere_radius,$y_start - k * 2, $x_start -k*2)
		puts "swag"
		puts next_layer
		input.write("G0 F9000 X#{next_layer[0]} Y#{next_layer[1]} Z#{$layer_height*$current_layer}")
		$current_layer +=1
	end
end

#gen_bottom: file -> null
#generates the top hemisphere of the sphere
#this also incremets $current_layer
def gen_top(input)
	num_layers = $layer_number/2 + 1
	(1...num_layers).each do |k|
		next_layer = gen_circle(input,$sphere_radius,$y_start + k* 2, $x_start + k * 2)
		input.write("G0 F9000 X#{next_layer[0]} Y#{next_layer[1]} Z#{$layer_height*$current_layer}")
		$current_layer +=1
	end
	
end


#gen_sphere: file -> null
#generates the top and bottom halves of the sphere
#it takes the max radius and delegates an increment based on
#the amount of layers
def gen_sphere(input)
	gen_bottom(input)
	gen_top(input)
end



gen_header(genfile)
gen_skirt(genfile)
gen_sphere(genfile)
genfile.close();