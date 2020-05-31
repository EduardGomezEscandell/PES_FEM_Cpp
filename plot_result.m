clearvars;

%% Input

Mesh  = 5;         % 1 through 5
Shape_in = 'Q';    % Q, T
Order_in = 1;      % 1, 2
quadrature = 1;

%% Input interpreter

switch Shape_in
    case 'Q'
        Shape = 'quad';
    case 'T'
        Shape = 'tri';
    otherwise
        error('Invalid element shape');
end

switch Order_in
    case 1
        Order = 'lin';
    case 2
        Order = 'quad';
    otherwise
        error('invalid order');
end

directory = ['../PES_FEM_Cpp/mesh_data/PES_2D_',Shape,'_',Order,'/Mesh',num2str(Mesh),'/'];
problem = ['_2D_',Shape,'_',Order,'.dat'];

%% Execution
argv1 = sprintf('%1d%1c%1d',Mesh, Shape_in, Order_in);
argv2 = num2str(quadrature);
if ~isfile([directory, 'boundaries.dat'])
    system(['python3 create_BC_file.py ', argv1]);
end
system(['./PES_FEM_Cpp ', argv1,' ', argv2]);



%% Output
Nodes     = load([directory, 'Node', problem]);
if Shape_in == 'T'
    Elements  = load([directory, 'Element', problem]);
else
    Elements = delaunay(Nodes(:,2), Nodes(:,3));
end
Solutions = load([directory, 'result.dat']);

ZERO = zeros(size(Nodes(:,2)));

subplot(121);
trisurf(Elements,Nodes(:,2),Nodes(:,3), Solutions(:,1));
shading interp;

subplot(122);
norm_U = sqrt(Solutions(:,2).^2 + Solutions(:,3).^2);
trisurf(Elements,Nodes(:,2),Nodes(:,3), ZERO, norm_U);
shading interp;
hold on
quiver(Nodes(:,2),Nodes(:,3), Solutions(:,2), Solutions(:,3),'r');
hold off
view(2);
c = colorbar('southoutside');
c.Label.String = 'Velocity';
axis([0 1 0 1]);
