#!/usr/bin/env octave -qf

%  Apply Geo Transform
function [Wx, Wy] = Apply_GeoTransform( Px, Py, adfGeoTransform )

    %  Multiply
    Wx = adfGeoTransform(1,2) * Px + adfGeoTransform(1,3) * Py +     adfGeoTransform(1,1);
    Wy = adfGeoTransform(1,5) * Px + adfGeoTransform(1,6) * Py + adfGeoTransform(1,4);

endfunction


function P = Read_File( pathname )

    P = textread( pathname, '%f' );

endfunction


%  Parse and read the file
plist = Read_File( argv(){1} );

%  Get the number of rows
num_points = size(plist)(1)/4;

cnt=1
A = ones(num_points,3);
W = ones(num_points,3);
for p = 1:8
    A(p,1) = plist(cnt);
    cnt += 1;
    A(p,2) = plist(cnt);
    cnt += 1;
    W(p,1) = plist(cnt);
    cnt += 1;
    W(p,2) = plist(cnt);
    cnt += 1;
end


%  Build Output Solution Pairs
Bx = W(:,1);
By = W(:,2);


%   Solve For Inverse x and y
Xi = A \ Bx;
Yi = A \ By;


%   Construct Actual Transform
adfGeoTransform = [Xi(3,1), Xi(1,1), Xi(2,1), Yi(3,1), Yi(1,1), Yi(2,1)];

%   Test Result
diffs = zeros(num_points,1)
for p = 1:num_points
    [Wx, Wy] = Apply_GeoTransform( A(p,1), A(p,2), adfGeoTransform );
    printf('W: %d, %d from %d %d, Expect: %d %d\n', Wx, Wy, A(p,1), A(p,2), W(p,1), W(p,2));
    diffs(p,1) = sqrt( (Wx - W(p,1)) ^ 2 + (Wy - W(p,2)) ^ 2)
end

diffs

printf(' %f %f %f\n %f %f %f\n', adfGeoTransform)

