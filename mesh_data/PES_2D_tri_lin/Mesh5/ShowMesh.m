clear all;
close all;

Nodes = load('Node_2D_tri_lin.dat');
Elements = load('Element_2D_tri_lin.dat');
Solutions = load('result.dat');

% trimesh(Elements,Nodes(:,2),Nodes(:,3))
subplot(121);
trisurf(Elements,Nodes(:,2),Nodes(:,3), Solutions(:,1));
shading interp;

subplot(122);
ZERO = zeros(size(Nodes(:,2)));
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
