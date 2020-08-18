
clear all;
close all;
clc;

x=importdata("var.txt");
histogram(x) ;xlim([-0.05 1.2]); grid minor;