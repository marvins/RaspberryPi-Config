#!/usr/bin/env octave -qf

%  Apply Geo Transform
function [Wx, Wy] = Apply_GeoTransform( Px, Py, adfGeoTransform )

    %  Multiply
    Wx = adfGeoTransform(1,2) * Px + adfGeoTransform(1,3) * Py +     adfGeoTransform(1,1);
    Wy = adfGeoTransform(1,5) * Px + adfGeoTransform(1,6) * Py + adfGeoTransform(1,4);

endfunction


function P = Read_File( pathname )

    P = textread( pathname, '%f' )

endfunction


%  Parse and read the file
plist = Read_File( argv(){1} );

%  Get the number of rows
num_points = size(plist)(1)/4;

cnt=1
A = ones(num_points,3)
W = ones(num_points,2)
for p = 1:8
    A(p,1) = plist(cnt)
    cnt += 1
    A(p,2) = plist(cnt)
    cnt += 1
    W(p,1) = plist(cnt)
    cnt += 1
    W(p,2) = plist(cnt)
    cnt += 1
end

A


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


printf('W1: %d, %d from %d %d, Expect: %d %d\n', Wx1, Wy1, P(1,1), P(1,2), W(1,1), W(1,2));
printf('W2: %d, %d from %d %d, Expect: %d %d\n', Wx2, Wy2, P(2,1), P(2,2), W(2,1), W(2,2));
printf('W3: %d, %d from %d %d, Expect: %d %d\n', Wx3, Wy3, P(3,1), P(3,2), W(3,1), W(3,2));
printf('W4: %d, %d from %d %d, Expect: %d %d\n', Wx4, Wy4, P(4,1), P(4,2), W(4,1), W(4,2));

[W1x,W1y] = Apply_GeoTransform( 0,  0, adfGeoTransform )
[W2x,W2y] = Apply_GeoTransform( 0, 32, adfGeoTransform )
printf('P1: %d, %d, -> W1: %d, %d\n', 0,  0, W1x, W1y )
printf('P2: %d, %d, -> W2: %d, %d\n', 0, 32, W2x, W2y )

printf(' %f %f %f\n %f %f %f\n', adfGeoTransform)
