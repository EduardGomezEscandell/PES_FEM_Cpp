clear all;
close all;

Nodes = load('Node_2D_tri_lin.dat');
Elements = load('Element_2D_tri_lin.dat');
Solutions = load('result.dat');

% trimesh(Elements,Nodes(:,2),Nodes(:,3))
trisurf(Elements,Nodes(:,2),Nodes(:,3), Solutions);
% axis equal;
% shading interp;