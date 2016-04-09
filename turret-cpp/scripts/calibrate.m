#!/usr/bin/env octave -qf

%  Apply Geo Transform
function [Wx, Wy] = Apply_GeoTransform( Px, Py, adfGeoTransform )

    %  Multiply
    Wx = adfGeoTransform(1,2) * Px + adfGeoTransform(1,3) * Py +     adfGeoTransform(1,1);
    Wy = adfGeoTransform(1,5) * Px + adfGeoTransform(1,6) * Py + adfGeoTransform(1,4);

endfunction

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
P = [161, 353;
     101, 107;
     320, 206;
     634, 113
     623, 358];

W = [340,176;
     352,222;
     314,202;
     266,222,
     268,172];

%  Build Input Transform (A)
Ai = [P(1,1), P(1,2) 1;
      P(2,1), P(2,2) 1;
      P(3,1), P(3,2) 1;
      P(4,1), P(4,2) 1];

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

A = [Xi(1,1), Xi(2,1), Xi(3,1);
     Yi(1,1), Yi(2,1), Yi(3,1)];

%   Construct Actual Transform
adfGeoTransform = [Xi(3,1), Xi(1,1), Xi(2,1), Yi(3,1), Yi(1,1), Yi(2,1)];

%   Test Result
[Wx1, Wy1] = Apply_GeoTransform( P(1,1), P(1,2), adfGeoTransform );
[Wx2, Wy2] = Apply_GeoTransform( P(2,1), P(2,2), adfGeoTransform );
[Wx3, Wy3] = Apply_GeoTransform( P(3,1), P(3,2), adfGeoTransform );
[Wx4, Wy4] = Apply_GeoTransform( P(4,1), P(4,2), adfGeoTransform );
[Wx5, Wy5] = Apply_GeoTransform( P(5,1), P(5,2), adfGeoTransform );


printf('W1: %d, %d from %d %d, Expect: %d %d\n', Wx1, Wy1, P(1,1), P(1,2), W(1,1), W(1,2));
printf('W2: %d, %d from %d %d, Expect: %d %d\n', Wx2, Wy2, P(2,1), P(2,2), W(2,1), W(2,2));
printf('W3: %d, %d from %d %d, Expect: %d %d\n', Wx3, Wy3, P(3,1), P(3,2), W(3,1), W(3,2));
printf('W4: %d, %d from %d %d, Expect: %d %d\n', Wx4, Wy4, P(4,1), P(4,2), W(4,1), W(4,2));
printf('W5: %d, %d from %d %d, Expect: %d %d\n', Wx5, Wy5, P(5,1), P(5,2), W(5,1), W(5,2));

printf('%f %f %f %f %f %f', adfGeoTransform)
