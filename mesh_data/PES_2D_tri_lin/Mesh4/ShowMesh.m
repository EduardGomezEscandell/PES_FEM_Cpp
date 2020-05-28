clear all;
close all;

Nodes = load('Node_2D_tri_lin.dat');
Elements = load('Element_2D_tri_lin.dat');

trimesh(Elements,Nodes(:,2),Nodes(:,3))
axis equal;
