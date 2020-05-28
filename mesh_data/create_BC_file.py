import sys

if len(sys.argv)< 3:
    raise Exception('Please input an element type and mesh\nExample: $create_BC_file T1 3')


elem_type = sys.argv[1]
mesh_no = sys.argv[2]

if elem_type =='Q1':
	folder = 'PES_2D_quad_lin/Mesh' + mesh_no
	file = folder + '/Node_2D_quad_lin.dat'
elif elem_type == 'Q2':
	folder = 'PES_2D_quad_quad/Mesh' + mesh_no  
	file = folder + '/Node_2D_quad_quad.dat'
elif elem_type =='T1':
	folder = 'PES_2D_tri_lin/Mesh' + mesh_no 
	file = folder + '/Node_2D_tri_lin.dat'
elif elem_type == 'T2':
	folder = 'PES_2D_tri_quad/Mesh' + mesh_no  
	file = folder + '/Node_2D_tri_quad.dat'
else:
	raise 'Unknown element type.\nAccepted types: T1 T2 Q1 Q2'

print('Loading file ' + file)

file_node = open(file,'r')
file_out  = open(folder+'/boundaries.dat','w+')

dirichlet = []
neumann = []

for line in file_node:

	if line == '\n':
		continue
		
	data = line.split()
	X = []
	for i in range(2):
		X.append(float(data[1+i]))

	# Boundary conditions:
	if(X[0] == 0 and X[1]==0):
        #                   Node ID     Value
		dirichlet.append([int(data[0]),  0.0])
	elif(X[0] == 0):
        #                   Node ID     Value
		neumann.append([int(data[0]), -1.0])
	elif(X[0] == 1):
        #                   Node ID     Value
		neumann.append([int(data[0]),  1.0])


if len(dirichlet)>0:
    for node in dirichlet:
        file_out.write('D\t%6d\t%10.5e\n'%(node[0], node[1]))

if len(neumann)>0:
    for node in neumann:
        file_out.write('N\t%6d\t%10.5e\n'%(node[0], node[1]))


file_node.close()
file_out.close()

print('BC file created successfuly')