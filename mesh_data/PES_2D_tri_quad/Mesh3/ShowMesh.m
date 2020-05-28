clear all;
close all;

Nodes = load('Node_2D_tri_quad.dat');
Elements = load('Element_2D_tri_quad.dat');

trimesh(Elements,Nodes(:,2),Nodes(:,3))
axis equal;
