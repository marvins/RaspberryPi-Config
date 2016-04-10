#!/usr/bin/env octave -qf


%  For Reference Only
% (161, 353) -> (340,176)
% (101, 107) -> (352,222)
% (320, 206) -> (314,202)
% (634, 113) -> (266,222)
% (623, 358) -> (268,172)


%
%   Main Function
%   
%  Create Sample Inputs
W = [161, 353;
     101, 107;
     320, 206;
     634, 113
     623, 358];

P = [340,176;
     352,222;
     314,202;
     266,222,
     268,172];

%  Build Input Transform (A)
Ai = [P(1,1), P(1,2), 1;
      P(2,1), P(2,2), 1;
      P(3,1), P(3,2), 1;
      P(4,1), P(4,2), 1];

%  Build Output Solution Pairs
Bx = [W(1,1);
      W(2,1);
      W(3,1);
      W(4,1)];

By = [W(1,2);
      W(2,2);
      W(3,2);
      W(4,2)];

%   Solve For Inverse x and y
Xi = Ai \ Bx;
Yi = Ai \ By;

%   Construct Actual Transform
adfGeoTransform = [Xi(3,1), Xi(1,1), Xi(2,1), Yi(3,1), Yi(1,1), Yi(2,1)];

%   Test Result
[Wx1, Wy1] = Apply_GeoTransform( 0, 0, adfGeoTransform );
[Wx2, Wy2] = Apply_GeoTransform(10, 0, adfGeoTransform );
[Wx3, Wy3] = Apply_GeoTransform(10,10, adfGeoTransform );
[Wx4, Wy4] = Apply_GeoTransform( 0,10, adfGeoTransform );
[Wx5, Wy5] = Apply_GeoTransform( 5, 5, adfGeoTransform );

printf('X: %d \n', Xi);
printf('Y: %d \n', Yi);
